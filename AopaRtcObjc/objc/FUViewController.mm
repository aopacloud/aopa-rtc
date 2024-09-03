//
//  FUViewController.m
//
//  Created by LSP on 2021/12/20.
//  Copyright © 2021 banban. All rights reserved.
//

#import "FUViewController.h"
#import "NADAppDelegate.h"
#import "UserViewCell.h"
#include "stats/StatsManager.h"
#import "VideoFileParser.h"
@interface FUViewController () <BBRtcEngineDelegate, UserViewDelegate, BBRtcVideoSourceProtocol, ReadVideoFrameDelegate>

@property (nonatomic, strong) UIView *topView;
@property (nonatomic, strong) UIView *localView;
@property (nonatomic, strong) UIView *remoteView;
@property (nonatomic, strong) UITextView *statsView;
@property (nonatomic, strong) UITextView *localText;
@property (nonatomic, strong) UIButton *switchBtn;
@property (nonatomic, strong) UIButton *remoteMirrorBtn;
@property (nonatomic, strong) UIButton *streamTypeBtn;
@property (nonatomic, strong) UIView *missingAuthpackLabel;
@property (nonatomic, strong) UIButton *muteAudioBtn;
@property (nonatomic, strong) UIButton *backBtn;
@property (nonatomic, strong) BBRtcVideoCanvas *videoCanvas;
@property (nonatomic, assign) BBRtcVideoMirrorMode localVideoMirrored;
@property (nonatomic, assign) BBRtcVideoMirrorMode remoteVideoMirrored;
@property(nonatomic) VideoFileParser* videoFileParser;
@end

@implementation FUViewController {
    UIView* view_;
    BBRtcEngineKit* sharedEngine_;
    int remoteId_;
    StatsManager statsManager_;
    NSTimer* statsTimer_;
    int streamType_;
}
@synthesize consumer = _consumer;
- (void)initView {
    view_ = [[UIView alloc] initWithFrame:CGRectZero];
    [view_ setBackgroundColor: [UIColor blackColor]];
    self.view = view_;
    
    _remoteView = [[UIView alloc] initWithFrame:CGRectZero];
    _remoteView.translatesAutoresizingMaskIntoConstraints = NO;
    [_remoteView setBackgroundColor: [[UIColor blackColor] colorWithAlphaComponent:0.2]];
    [view_ addSubview:_remoteView];
    
    _localView = [[UIView alloc] initWithFrame:CGRectZero];
    _localView.translatesAutoresizingMaskIntoConstraints = NO;
    [_localView setBackgroundColor: [[UIColor blackColor] colorWithAlphaComponent:0.0]];
    [view_ addSubview:_localView];
    
    _statsView = [[UITextView alloc] initWithFrame:CGRectZero];
    _statsView.translatesAutoresizingMaskIntoConstraints = NO;
    [_statsView setBackgroundColor: [[UIColor blackColor] colorWithAlphaComponent:0.0]];
    [view_ addSubview:_statsView];

    _topView = [[UIView alloc] initWithFrame:CGRectZero];
    _topView.translatesAutoresizingMaskIntoConstraints = NO;
    [view_ addSubview:_topView];
    
    _backBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    _backBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [_backBtn setBackgroundColor: [[UIColor blackColor] colorWithAlphaComponent:0.1]];
    [_backBtn setTitle:@"EXIT" forState:UIControlStateNormal];
    [_backBtn addTarget:self action:@selector(backBtnClick:) forControlEvents:UIControlEventTouchUpInside];
    [_topView addSubview:_backBtn];
    
    _switchBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    _switchBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [_switchBtn setBackgroundColor: [[UIColor blackColor] colorWithAlphaComponent:0.1]];
    [_switchBtn setTitle:@"Camera" forState:UIControlStateNormal];
    [_switchBtn addTarget:self action:@selector(switchCamera:) forControlEvents:UIControlEventTouchUpInside];
    [_topView addSubview:_switchBtn];
    
    _streamTypeBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    _streamTypeBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [_streamTypeBtn setBackgroundColor: [[UIColor blackColor] colorWithAlphaComponent:0.1]];
    [_streamTypeBtn setTitle:@"Auto" forState:UIControlStateNormal];
    [_streamTypeBtn addTarget:self action:@selector(streamSwitch:) forControlEvents:UIControlEventTouchUpInside];
    [_topView addSubview:_streamTypeBtn];
    
    
    _localText = [[UITextView alloc] initWithFrame:CGRectZero];
    _localText.translatesAutoresizingMaskIntoConstraints = NO;
    _localText.text = @"";
    _localText.textAlignment = NSTextAlignmentCenter;
    _localText.font = [UIFont systemFontOfSize:24];
    [_localText setBackgroundColor: [[UIColor whiteColor] colorWithAlphaComponent:0.0]];
    [_topView addSubview:_localText];

    [_topView.leftAnchor constraintEqualToAnchor:view_.leftAnchor].active = YES;
    [_topView.rightAnchor constraintEqualToAnchor:view_.rightAnchor].active = YES;
    [_topView.topAnchor constraintEqualToAnchor:view_.topAnchor constant:20].active = YES;
    [_topView.heightAnchor constraintEqualToConstant:55].active = YES;
    
    [_backBtn.leftAnchor constraintEqualToAnchor:_topView.leftAnchor constant:10].active = YES;
    [_backBtn.topAnchor constraintEqualToAnchor:_topView.topAnchor constant:20].active = YES;
    [_backBtn.widthAnchor constraintEqualToConstant:55].active = YES;
    [_backBtn.heightAnchor constraintEqualToConstant:55].active = YES;
    
    [_switchBtn.leftAnchor constraintEqualToAnchor:_backBtn.rightAnchor constant:10].active = YES;
    [_switchBtn.topAnchor constraintEqualToAnchor:_topView.topAnchor constant:20].active = YES;
    [_switchBtn.widthAnchor constraintEqualToConstant:55].active = YES;
    [_switchBtn.heightAnchor constraintEqualToConstant:55].active = YES;
    
    [_streamTypeBtn.leftAnchor constraintEqualToAnchor:_switchBtn.rightAnchor constant:10].active = YES;
    [_streamTypeBtn.topAnchor constraintEqualToAnchor:_topView.topAnchor constant:20].active = YES;
    [_streamTypeBtn.widthAnchor constraintEqualToConstant:55].active = YES;
    [_streamTypeBtn.heightAnchor constraintEqualToConstant:55].active = YES;
    
    [_localText.leftAnchor constraintEqualToAnchor:_streamTypeBtn.rightAnchor constant:10].active = YES;
    [_localText.topAnchor constraintEqualToAnchor:_topView.topAnchor constant:20].active = YES;
    [_localText.widthAnchor constraintEqualToConstant:120].active = YES;
    [_localText.heightAnchor constraintEqualToConstant:50].active = YES;

    [_remoteView.leftAnchor constraintEqualToAnchor:view_.leftAnchor].active = YES;
    [_remoteView.topAnchor constraintEqualToAnchor:view_.topAnchor].active = YES;
    [_remoteView.rightAnchor constraintEqualToAnchor:view_.rightAnchor].active = YES;
    [_remoteView.bottomAnchor constraintEqualToAnchor:view_.bottomAnchor].active = YES;

   [_localView.topAnchor constraintEqualToAnchor:view_.topAnchor].active = YES;
   [_localView.rightAnchor constraintEqualToAnchor:view_.rightAnchor].active = YES;
   [_localView.widthAnchor constraintEqualToConstant:120].active = YES;
   [_localView.heightAnchor constraintEqualToConstant:200].active = YES;
    
    [_statsView.leftAnchor constraintEqualToAnchor:view_.leftAnchor].active = YES;
    [_statsView.bottomAnchor constraintEqualToAnchor:view_.bottomAnchor].active = YES;
    [_statsView.widthAnchor constraintEqualToConstant:120].active = YES;
    [_statsView.heightAnchor constraintEqualToConstant:160].active = YES;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initView];
    
    statsTimer_ = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self
        selector:@selector(updateStats:) userInfo:nil repeats:YES];
    
    self.localView.hidden = YES;
    self.remoteView.hidden = YES;
    remoteId_ = -1;
    streamType_ = 2;

    NSString* servers[] = {
        @"{\"signaling\":\"wss://rtc-sg-gateway.aopacloud.sg:6080/rtc/channel\",\"rtconfig\":\"https://rtc-sg-gateway.aopacloud.sg:6080/rtc/get_rtc_config\",\"log\":\"https://rtc-sg-gateway.aopacloud.sg:6080/ali/v1/get_upload_url\",\"quic\":\"rtc-sg-gateway.aopacloud.sg:6081\",\"report\":\"https://rtc-sg-gateway.aopacloud.sg:6080/rtc/rtc_event_report\"}",
        @"{\"signaling\":\"wss://rtc-gateway.hxty-agent.com:6080/rtc/channel\",\"rtconfig\":\"https://rtc-gateway.hxty-agent.com:6080/rtc/get_rtc_config\",\"log\":\"https://rtc-gateway.hxty-agent.com:6080/ali/v1/get_upload_url\",\"quic\":\"rtc-gateway.hxty-agent.com:6081\",\"report\":\"https://rtc-gateway.hxty-agent.com:6080/rtc/rtc_event_report\"}",
        @"{\"signaling\":\"ws://47.114.166.11:6080/rtc/channel\",\"rtconfig\":\"http://47.114.166.11:6080/rtc/get_rtc_config\",\"log\":\"http://47.114.166.11:6080/ali/v1/get_upload_url\",\"quic\":\"47.114.166.11:10000\",\"report\":\"http://47.114.166.11:6080/rtc/rtc_event_report\"}",
        @"{\"signaling\":\"ws://192.168.11.47:6092/channel\",\"rtconfig\":\"http://47.114.166.11:6080/rtc/get_rtc_config\",\"log\":\"http://47.114.166.11:6080/ali/v1/get_upload_url\",\"quic\":\"192.168.11.47:6093\",\"report\":\"http://192.168.11.47:6080/rtc/rtc_event_report\"}",
        @"{\"signaling\":\"ws://192.168.132.153:6092/channel\",\"rtconfig\":\"\",\"log\":\"\",\"quic\":\"172.19.20.100:6093\"}",
        @"{\"signaling\":\"ws://47.114.166.11:6080/rtc_p2p/channel\",\"rtconfig\":\"http://47.114.166.11:6080/rtc/get_rtc_config\",\"log\":\"\",\"quic\":\"\"}"
    };
    
    NSString* serverAddr = nil;
    if (self.serverType == 4) {
        serverAddr = servers[3];
        serverAddr = [serverAddr stringByReplacingOccurrencesOfString:@"192.168.11.47" withString:self.customAddr];
    } else {
        serverAddr = servers[self.serverType];
    }
    
    [BBRtcEngineKit setRtcServerAddress:serverAddr];
    sharedEngine_ = [BBRtcEngineKit sharedEngineWithAppId:self.appId delegate:nil];
    if (!sharedEngine_) {
        return;
    }
    sharedEngine_.delegate = self;

    NSString * docsdir = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    [sharedEngine_ setLogFilter:BBRtcLogFilterDebug];
    [sharedEngine_ setDelegate:self];
    [sharedEngine_ setDumpOutputDirectory:docsdir];
    [sharedEngine_ enableMainQueueDispatch:YES];
    [sharedEngine_ setRemoteDefaultVideoStreamType:BBRtcVideoStreamTypeAuto];
    [sharedEngine_ setDefaultMuteAllRemoteVideoStreams:NO];
    [sharedEngine_ setChannelProfile:BBRtcChannelProfileLiveBroadcasting];
    [sharedEngine_ setAudioProfile:(BBRtcAudioProfile)_audioType scenario:BBRtcAudioScenarioGameStreaming];
    [sharedEngine_ enableAudio];
    [sharedEngine_ enableVideo];
    
    if (self.userRole == BBRtcClientRoleBroadcaster) {
        [sharedEngine_ setClientRole:BBRtcClientRoleBroadcaster];
        BBRtcVideoEncoderConfiguration* videoConfig = [[BBRtcVideoEncoderConfiguration alloc] init];
        if(_videoProfile == 0){
           videoConfig.dimensions = CGSizeMake(360, 640);
        }else if(_videoProfile == 1){
           videoConfig.dimensions = CGSizeMake(480, 640);
        }else if(_videoProfile == 2){
           videoConfig.dimensions = CGSizeMake(540, 960);  
        }else if(_videoProfile == 3){
           videoConfig.dimensions = CGSizeMake(720, 1280);
        }else if(_videoProfile == 4){
           videoConfig.dimensions = CGSizeMake(1080, 1920);
        }
        videoConfig.frameRate = 15;
        videoConfig.minFrameRate = 5;
        videoConfig.orientationMode = BBRtcVideoOutputOrientationModeFixedPortrait;
        videoConfig.mirrorMode = BBRtcVideoMirrorModeAuto;
        videoConfig.degradationPreference = BBRtcDegradationMaintainFramerate;
        [sharedEngine_ setVideoEncoderConfiguration:videoConfig];
    } else {
        [sharedEngine_ setClientRole:BBRtcClientRoleAudience];
    }
    if(_videoSourceEnabled)
        [sharedEngine_ setVideoSource:self];
    [sharedEngine_ enableInEarMonitoring:YES];
    [sharedEngine_ enableLocalAudio:YES];
    [sharedEngine_ enableLocalVideo:_videoEnabled];
    [sharedEngine_ setEnableSpeakerphone:_speakerEnabled];
    [sharedEngine_ setParameters:@"{\"che.audio.keep.audiosession\":true}"];
    if(_quicEnabled)
        [sharedEngine_ setParameters:@"{\"che.network.enable.quic\":true}"];
    else
        [sharedEngine_ setParameters:@"{\"che.network.enable.quic\":false}"];
    if(_detachStreamEnabled) 
        [sharedEngine_ setParameters:@"{\"che.media.detach\":true}"];
    else
        [sharedEngine_ setParameters:@"{\"che.media.detach\":false}"];
    if(self.serverType == 5){
        [sharedEngine_ setParameters:@"{\"che.p2p.enable\":true}"];
    }
    [sharedEngine_ enableDualStreamMode:_simulcastStreamEnabled];
    if([sharedEngine_ joinChannelByToken:_token channelId:self.channelId
        info:@"" uid:self.userId joinSuccess:nil] != BBRtcErrorCodeNoError) {
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}

- (void)viewDidLayoutSubviews {
}

- (void)dealloc {
    statsManager_.clearAllData();
}

- (IBAction)switchCamera:(UIButton *)button
{
    [sharedEngine_ switchCamera];
}

- (IBAction)streamSwitch:(id)sender{
   if(remoteId_ == -1)
       return;
  streamType_ = ++streamType_ % 3;
   if(streamType_ == 0){
       [sharedEngine_ setRemoteVideoStream:remoteId_ type:BBRtcVideoStreamTypeHigh];
       [_streamTypeBtn setTitle:@"High" forState:UIControlStateNormal];
   }
   else if(streamType_ == 1){
       [sharedEngine_ setRemoteVideoStream:remoteId_ type:BBRtcVideoStreamTypeLow];
       [_streamTypeBtn setTitle:@"Low" forState:UIControlStateNormal];
   }
   else if(streamType_ == 2){
       [sharedEngine_ setRemoteVideoStream:remoteId_ type:BBRtcVideoStreamTypeAuto];
       [_streamTypeBtn setTitle:@"Auto" forState:UIControlStateNormal];
   }
}

- (IBAction)muteAudioBtn:(UIButton *)sender {
    sender.selected = !sender.selected;
    if (sender.selected) {
        [sender setTitleColor:[UIColor blueColor] forState:(UIControlStateSelected)];
    }
    [sharedEngine_ muteLocalAudioStream:sender.selected];
}

- (IBAction)backBtnClick:(UIButton *)sender {
    if (sharedEngine_) {
        [sharedEngine_ stopPreview];
        [sharedEngine_ leaveChannel:nil];
        [self dismissViewControllerAnimated:YES completion:nil];
    } else{
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}

- (void)rtcEngine:(BBRtcEngineKit *)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size: (CGSize)size elapsed:(NSInteger)elapsed {
}

#pragma mark - AopaRtcEngineDelegate
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed {
    NSLog(@"didJoinChannel uid:%tu", uid);
    [_localText setText:[NSString stringWithFormat: @"%tu", uid]];
    if (uid == (NSUInteger)(self.userId) && self.userRole == BBRtcClientRoleBroadcaster) {
        self.localView.hidden = NO;
        
        BBRtcVideoCanvas* videoCanvas = [[BBRtcVideoCanvas alloc] init];
        videoCanvas.uid = uid;
        videoCanvas.view = self.localView;
        videoCanvas.mirrorMode = BBRtcVideoMirrorModeAuto;
        videoCanvas.renderMode = BBRtcVideoRenderModeHidden;
        [sharedEngine_ setupLocalVideo:videoCanvas];
        
        statsManager_.addUserStats((int)uid, true);
    }
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed {
    NSLog(@"didJoinedOfUid uid:%tu", uid);
    if(remoteId_ == -1){
        remoteId_ = (int)uid;
        BBRtcVideoCanvas *videoCanvas = [[BBRtcVideoCanvas alloc] init];
        videoCanvas.uid = remoteId_;
        videoCanvas.view = self.remoteView;
        videoCanvas.mirrorMode = BBRtcVideoMirrorModeAuto;
        videoCanvas.renderMode = BBRtcVideoRenderModeHidden;
        [engine setupRemoteVideo:videoCanvas];
        statsManager_.addUserStats((int)uid, false);
        statsManager_.enableStats(true);
        self.remoteView.hidden = NO;
    }
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOfflineOfUid:(NSUInteger)uid reason:(BBRtcUserOfflineReason)reason {
    NSLog(@"didOfflineOfUid uid:%tu", uid);
    if ((int)uid == remoteId_) {
        remoteId_ = -1;
        statsManager_.removeUserStats(uid);
        BBRtcVideoCanvas *videoCanvas = [[BBRtcVideoCanvas alloc] init];
        videoCanvas.uid = remoteId_;
        videoCanvas.view = nil;
        videoCanvas.mirrorMode = BBRtcVideoMirrorModeAuto;
        videoCanvas.renderMode = BBRtcVideoRenderModeHidden;
        [engine setupRemoteVideo:videoCanvas];
        self.remoteView.hidden = YES;
    }
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(BBRtcVideoRemoteState)state reason:(BBRtcVideoRemoteStateReason)reason
          elapsed:(NSInteger)elapsed {

    NSLog(@"remoteVideoStateChangedOfUid remote video uid:%tu state:%tu", uid, state);
  
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine
    reportRtcStats:(BBRtcChannelStats * _Nonnull)stats {
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine
    localVideoStats:(BBRtcLocalVideoStats * _Nonnull)stats {
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine
    localAudioStats:(BBRtcLocalAudioStats * _Nonnull)stats {
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine
    remoteVideoStats:(BBRtcRemoteVideoStats * _Nonnull)stats {
    RemoteStatsData* data = (RemoteStatsData*)statsManager_.getStatsData(stats.uid);
    if (data == nullptr) return;
    data->setWidth(stats.width);
    data->setHeight(stats.height);
    data->setFramerate(stats.rendererOutputFrameRate);
    data->setVideoRx(stats.receivedBitrate);
    data->setFrozenTime((int)stats.frozenRate);
    data->setVideoDelay(stats.delay);
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine
    remoteAudioStats:(BBRtcRemoteAudioStats * _Nonnull)stats {
    RemoteStatsData* data = (RemoteStatsData*)statsManager_.getStatsData(stats.uid);
    if (data == nullptr) return;
    data->setAudioRx(stats.receivedBitrate);
    data->setAudioNetDelay(stats.networkTransportDelay);
    data->setAudioNetJitter(stats.jitterBufferDelay);
    data->setAudioLoss(stats.audioLossRate);
    data->setAudioQuality(statsManager_.qualityToString(stats.quality));
}

- (void)refreshStats {
    dispatch_queue_t queue;
    queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), queue, ^{
        if (statsManager_.isEnabled()) {
            StatsData* data = statsManager_.getStatsData(remoteId_);
            std::string info = data != nullptr ? data->toString() : std::string("");
            NSString* text = [NSString stringWithCString:info.c_str()
                                        encoding:[NSString defaultCStringEncoding]];
            [self refreshStats];
        }
    });
}

- (void)updateStats:(id)sender {
    if (statsManager_.isEnabled()) {
        StatsData* data = statsManager_.getStatsData(remoteId_);
        std::string info = data != nullptr ? data->toString() : std::string("");
        NSString* text = [NSString stringWithCString:info.c_str()
                                    encoding:[NSString defaultCStringEncoding]];
        [_statsView setText:text];
    }
}


- (BOOL)shouldInitialize {
    NSLog(@"Custom video source shouldInitialize");
    return YES;
}

- (void)shouldStart {
    NSLog(@"Custom video source shouldStart enter");
    if(!self.videoFileParser){
        NSString *path = [[NSBundle mainBundle] pathForResource:@"22" ofType:@"h264"];
        if(path == nil)
            return;
        self.videoFileParser = [[VideoFileParser alloc] init];
        self.videoFileParser.delegate = self;
        [self.videoFileParser open:path fps:15];
    }
    NSLog(@"Custom video source shouldStart exit");
}

- (void)shouldStop {
    if(self.videoFileParser){
        [self.videoFileParser close];
        self.videoFileParser = nil;
    }
    NSLog(@"Custom video source shouldStop");
}

- (void)shouldDispose {
    NSLog(@"Custom video source shouldDispose");
}
 
- (BBRtcVideoBufferType)bufferType {
    return BBRtcVideoBufferTypeRawData;
}

-(void)onReadVideoFrame:(CVPixelBufferRef _Nullable )pixelbuffer{
    if(_consumer){
        static CMTimeValue timesmaple = 0;
        CMTime timestamp = CMTimeMake(timesmaple, 15);
        [_consumer consumePixelBuffer:pixelbuffer withTimestamp:timestamp rotation:(BBRtcVideoRotation)0];
        timesmaple += 1000;
    }
}

@end
