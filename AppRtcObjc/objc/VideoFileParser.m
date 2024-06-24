#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "VideoFileParser.h"

const uint8_t KStartCode[4] = {0, 0, 0, 1};
const uint8_t KStartCode2[3] = {0, 0, 1};
const int kDefaultFps = 30;
@implementation VideoPacket
- (instancetype)initWithSize:(NSInteger)size
{
    self = [super init];
    self.buffer = malloc(size);
    self.size = size;
    return self;
}

-(void)dealloc{
    if(self.buffer)
       free(self.buffer);
}
@end

@interface VideoFileParser ()
{
    uint8_t *_buffer;
    NSInteger _bufferSize;
    NSInteger _bufferCap;
    uint8_t *_sps;
    NSInteger _spsSize;
    uint8_t *_pps;
    NSInteger _ppsSize;
    VTDecompressionSessionRef _deocderSession;
    CMVideoFormatDescriptionRef _decoderFormatDescription;
    NSInteger _readFps;
    NSInteger _currentFps;
    BOOL threadExit;
}

@property(nonatomic, strong) NSString* fileName;
@property(nonatomic) NSInputStream* fileStream;
@property(nonatomic) dispatch_source_t timer;
@property(nonatomic) NSThread *thread;
@property(nonatomic) NSCondition *conditon;
@end

 void didDecompress( void *decompressionOutputRefCon, void *sourceFrameRefCon, OSStatus status, VTDecodeInfoFlags infoFlags, CVImageBufferRef pixelBuffer, CMTime presentationTimeStamp, CMTime presentationDuration ){
    if(status != noErr) return;
    if(decompressionOutputRefCon && pixelBuffer){
        VideoFileParser* pSelf = (__bridge VideoFileParser*)decompressionOutputRefCon;
        [pSelf.delegate onReadVideoFrame:pixelBuffer];
    }
}

@implementation VideoFileParser

-(BOOL)open:(NSString *)fileName fps:(NSInteger)fps
{
    _bufferSize = 0;
    _bufferCap = 512 * 1024;
    _buffer = malloc(_bufferCap);
    _readFps = fps;
    _currentFps = 0;
    self.fileName = fileName;
    self.fileStream = [NSInputStream inputStreamWithFileAtPath:fileName];
    [self.fileStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [self.fileStream open];
    [self startTimer];
    return YES;
}

-(void)close
{
    if(self.thread){
        [self.thread cancel];
        [self.conditon signal];
        while (!threadExit) {
            usleep(1000);
        }
        self.thread = nil;
        self.conditon = nil;
    }
    if(self.fileStream){
        [self.fileStream close];
        self.fileStream = nil;
    }
    if(_buffer){
        free(_buffer);
        _buffer = NULL;
    }
    if(_sps){
        free(_sps);
        _sps = NULL;
    }
    if(_pps){
        free(_pps);
        _pps = NULL;
    }
    _spsSize = _ppsSize = 0;
    [self clearH264Deocder];
}

-(void)dealloc{
}

-(NSTimeInterval)currentTimer{
    NSDate* date = [NSDate dateWithTimeIntervalSinceNow:0];
    return [date timeIntervalSince1970]*1000;
}

-(void)threadRun{
    threadExit = NO;
    while (![[NSThread currentThread] isCancelled]) {
        int index = 0;
        BOOL drop = NO;
        float r = _readFps / (kDefaultFps - _readFps);
        NSTimeInterval startTm = [self currentTimer];
        do{
            VideoPacket* vp = [self nextPacket];
            if(vp){
                uint32_t nalSize = (uint32_t)(vp.size - 4);
                uint8_t *pNalSize = (uint8_t*)(&nalSize);
                vp.buffer[0] = *(pNalSize + 3);
                vp.buffer[1] = *(pNalSize + 2);
                vp.buffer[2] = *(pNalSize + 1);
                vp.buffer[3] = *(pNalSize);
                
                int nalType = vp.buffer[4] & 0x1F;
                switch (nalType) {
                    case 0x05:
                       // NSLog(@"Nal type is IDR frame");
                        if([self initFormat]) {
                            [self decode:vp dropped:drop];
                        }
                        _currentFps++;
                        drop = YES;
                        break;
                    case 0x06:
                        break;
                    case 0x07:
                       // NSLog(@"Nal type is SPS");
                        _spsSize = vp.size - 4;
                        _sps = realloc(_sps, _spsSize);
                        memcpy(_sps, vp.buffer + 4, _spsSize);
                        break;
                    case 0x08:
                      //  NSLog(@"Nal type is PPS");
                        _ppsSize = vp.size - 4;
                        _pps = realloc(_pps, _ppsSize);
                        memcpy(_pps, vp.buffer + 4, _ppsSize);
                        break;
                        
                    default:
                       // NSLog(@"Nal type is B/P frame nalType:%d\n", nalType);
                        [self decode:vp dropped:drop];
                        _currentFps++;
                        drop = YES;
                        break;
                }
               // NSLog(@"+++ _currentFps:%td\n", _currentFps);
            }
            else{
                break;
            }
        }while(!drop || (r > 1 ? _currentFps % (int)r == 0 : index++ < (int)(1/r)));

        if(![self.fileStream hasBytesAvailable]){
            [self.fileStream close];
            self.fileStream = [NSInputStream inputStreamWithFileAtPath:self.fileName];
            [self.fileStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
            [self.fileStream open];
        }
        NSTimeInterval endTm = [self currentTimer];
        float offset = (1000.f/_readFps - (endTm - startTm) - 2)/1000;
        [self.conditon waitUntilDate:[NSDate dateWithTimeIntervalSinceNow:offset]];
    }
    threadExit = YES;
}

- (void)startTimer{
    self.conditon = [[NSCondition alloc] init];
    self.thread=[[NSThread alloc]initWithTarget:self selector:@selector(threadRun) object:nil];
    [self.thread setName:@"ReadFileThread"];
    [self.thread start];
}

-(VideoPacket*)nextPacket
{
    if(_bufferSize < _bufferCap && self.fileStream.hasBytesAvailable) {
        NSInteger readBytes = [self.fileStream read:_buffer + _bufferSize maxLength:_bufferCap - _bufferSize];
        _bufferSize += readBytes;
    }
    
    bool bSlow = (memcmp(_buffer, KStartCode2, sizeof(KStartCode2)) == 0);
    if(memcmp(_buffer, KStartCode, sizeof(KStartCode)) != 0 && !bSlow) {
        return nil;
    }
    
    if(_bufferSize >= 5) {
        uint8_t *bufferBegin = _buffer + 4;
        uint8_t *bufferEnd = _buffer + _bufferSize;
        while(bufferBegin != bufferEnd) {
            if(*bufferBegin == 0x01) {
                if(memcmp(bufferBegin - 3, KStartCode, sizeof(KStartCode)) == 0 ) {
                    if(bSlow){
                        NSInteger packetSize = bufferBegin - _buffer - 3;
                        VideoPacket *vp = [[VideoPacket alloc] initWithSize:packetSize + 1];
                        memcpy(vp.buffer + 1, _buffer, packetSize);
                        memmove(_buffer, _buffer + packetSize, _bufferSize - packetSize);
                        _bufferSize -= packetSize;
                        return vp;
                    }
                    else{
                        NSInteger packetSize = bufferBegin - _buffer - 3;
                        VideoPacket *vp = [[VideoPacket alloc] initWithSize:packetSize];
                        memcpy(vp.buffer, _buffer, packetSize);
                        
                        memmove(_buffer, _buffer + packetSize, _bufferSize - packetSize);
                        _bufferSize -= packetSize;
                        return vp;
                    }
                }
                else if(memcmp(bufferBegin - 2, KStartCode2, sizeof(KStartCode2)) == 0){
                    if(bSlow){
                        NSInteger packetSize = bufferBegin - _buffer - 2;
                        VideoPacket *vp = [[VideoPacket alloc] initWithSize:packetSize + 1];
                        memcpy(vp.buffer + 1, _buffer, packetSize);
                        memmove(_buffer, _buffer + packetSize, _bufferSize - packetSize);
                        _bufferSize -= packetSize;
                        return vp;
                    }
                    else{
                        NSInteger packetSize = bufferBegin - _buffer - 2;
                        VideoPacket *vp = [[VideoPacket alloc] initWithSize:packetSize];
                        memcpy(vp.buffer, _buffer, packetSize);
                        
                        memmove(_buffer, _buffer + packetSize, _bufferSize - packetSize);
                        _bufferSize -= packetSize;
                        return vp;
                    }
                }
            }
            ++bufferBegin;
        }
    }

    return nil;
}

static CFDictionaryRef CreateCFTypeDictionary(CFTypeRef* keys,
                                              CFTypeRef* values,
                                              size_t size) {
  return CFDictionaryCreate(kCFAllocatorDefault, keys, values, size,
                            &kCFTypeDictionaryKeyCallBacks,
                            &kCFTypeDictionaryValueCallBacks);
}


    
- (BOOL) initFormat{
    CMVideoFormatDescriptionRef videoFromat;
    const uint8_t* const parameterSetPointers[2] = { _sps, _pps };
    const size_t parameterSetSizes[2] = { _spsSize, _ppsSize };
    OSStatus status = CMVideoFormatDescriptionCreateFromH264ParameterSets(kCFAllocatorDefault,
                                                                              2, //param count
                                                                              parameterSetPointers,
                                                                              parameterSetSizes,
                                                                              4, //nal start code size
                                                                              &videoFromat);
    if(status != noErr) return NO;
    if (!_decoderFormatDescription || !CMFormatDescriptionEqual(videoFromat, _decoderFormatDescription)) {
        [self clearH264Deocder];
        _decoderFormatDescription = videoFromat;
       return [self initH264Decoder];
    }
    return YES;
}
    
-(BOOL)initH264Decoder {
    if(_deocderSession) {
        return YES;
    }
    _deocderSession = nil;
    static size_t const attributesSize = 3;
    CFTypeRef keys[attributesSize] = {
      kCVPixelBufferOpenGLESCompatibilityKey,
      kCVPixelBufferIOSurfacePropertiesKey,
      kCVPixelBufferPixelFormatTypeKey
    };
    CFDictionaryRef ioSurfaceValue = CreateCFTypeDictionary(NULL, NULL, 0);
    int64_t nv12type = kCVPixelFormatType_420YpCbCr8BiPlanarFullRange;
    CFNumberRef pixelFormat = CFNumberCreate(NULL, kCFNumberLongType, &nv12type);
    CFTypeRef values[attributesSize] = {kCFBooleanTrue, ioSurfaceValue, pixelFormat};
    CFDictionaryRef attributes = CreateCFTypeDictionary(keys, values, attributesSize);
    if (ioSurfaceValue) {
      CFRelease(ioSurfaceValue);
      ioSurfaceValue = NULL;
    }
    if (pixelFormat) {
      CFRelease(pixelFormat);
      pixelFormat = NULL;
    }
    VTDecompressionOutputCallbackRecord record = {
        didDecompress, (__bridge void *)self,
    };
    OSStatus status = VTDecompressionSessionCreate(
        NULL, _decoderFormatDescription, NULL, attributes, &record, &_deocderSession);
    return YES;
}

-(void)clearH264Deocder {
    if(_deocderSession) {
        if ([[[UIDevice currentDevice] systemVersion] floatValue] > 11.0) {
          VTDecompressionSessionWaitForAsynchronousFrames(_deocderSession);
        }
        VTDecompressionSessionInvalidate(_deocderSession);
        CFRelease(_deocderSession);
        _deocderSession = NULL;
    }
    
    if(_decoderFormatDescription) {
        CFRelease(_decoderFormatDescription);
        _decoderFormatDescription = NULL;
    }
    
   
}

-(void)decode:(VideoPacket*)vp dropped:(BOOL)dropped {
    CMBlockBufferRef blockBuffer = NULL;
    OSStatus status  = CMBlockBufferCreateWithMemoryBlock(kCFAllocatorDefault,
                                                          (void*)vp.buffer, vp.size,
                                                          kCFAllocatorNull,
                                                          NULL, 0, vp.size,
                                                          0, &blockBuffer);
    if(status == kCMBlockBufferNoErr &&  blockBuffer) {
        CMSampleBufferRef sampleBuffer = NULL;
        const size_t sampleSizeArray[] = {vp.size};
        status = CMSampleBufferCreateReady(kCFAllocatorDefault,
                                           blockBuffer,
                                           _decoderFormatDescription ,
                                           1, 0, NULL, 1, sampleSizeArray,
                                           &sampleBuffer);
        if (status == kCMBlockBufferNoErr && sampleBuffer) {
            VTDecodeFrameFlags flags = kVTDecodeFrame_EnableAsynchronousDecompression;
            VTDecodeInfoFlags flagOut = 0;
            flags |=  dropped ? kVTDecodeFrame_DoNotOutputFrame : 0;
            OSStatus decodeStatus = VTDecompressionSessionDecodeFrame(_deocderSession,
                                                                      sampleBuffer,
                                                                      flags,
                                                                      NULL,
                                                                      &flagOut);
            
            if(decodeStatus == kVTInvalidSessionErr) {
                NSLog(@"IOS8VT: Invalid session, reset decoder session");
            } else if(decodeStatus == kVTVideoDecoderBadDataErr) {
                NSLog(@"IOS8VT: decode failed status=%d(Bad data)", decodeStatus);
            } else if(decodeStatus != noErr) {
                NSLog(@"IOS8VT: decode failed status=%d", decodeStatus);
            }
            
            CFRelease(sampleBuffer);
        }
        CFRelease(blockBuffer);
    }

}


@end
