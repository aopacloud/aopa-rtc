#include <objc/NSObject.h>
#import <VideoToolbox/VideoToolbox.h>

@protocol ReadVideoFrameDelegate <NSObject>
@optional
-(void) onReadVideoFrame:(CVPixelBufferRef _Nullable )pixelbuffer;
@end

@interface VideoPacket : NSObject
@property uint8_t* _Nullable buffer;
@property NSInteger size;

@end

@interface VideoFileParser : NSObject

-(BOOL)open:(NSString*_Nullable)fileName fps:(NSInteger)fps;
-(VideoPacket *_Nullable)nextPacket;
-(void)close;
@property (nonatomic, assign) id<ReadVideoFrameDelegate>  _Nullable delegate;
@end
