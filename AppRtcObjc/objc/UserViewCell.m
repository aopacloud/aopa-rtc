//
//  UserViewCell.m
//  AppRtcObjc
//
//  Created by bhb on 2020/4/27.
//

#import "UserViewCell.h"
#import "NADVolumeView.h"
@interface UserViewCell ()
@property(nonatomic) UIView *  bkView;
@property(nonatomic) UIView *  videoView;
@property(nonatomic) UIView *  controlView;
@property(nonatomic) UILabel*  titleLabel;
@property(nonatomic) UIButton *  voiceMuteBnt;
@property(nonatomic) UIButton *  videoDoubleBnt;
@property(nonatomic) UILabel*  realTimeVolumeLabel;
@property(nonatomic) UISlider*  volumeSlider;
@property(nonatomic) NADVolumeView*  realTimeVolumeView;
@end

@implementation UserViewCell{
    uint32_t uid_;
    int index_;
}

- (instancetype)initWithFrame:(CGRect)frame {
    uid_ = 0xFFFFFFFF;
    index_ = -1;
    self = [super initWithFrame:frame];
    return self;
}

- (id) initWithUser:(CGRect)frame delegate:(id<UserViewDelegate> _Nullable)delegate uid:(uint32_t)uid{
    [self loadview];
    self.delegate = delegate;
    uid_ = uid;
    [_titleLabel setText:[NSString stringWithFormat:@"%d", uid]];
    return self;
}

-(void) loadview {
    if(_videoView != nil)
        return;
    _videoView = [[UIView alloc] initWithFrame:CGRectZero];
    _videoView.translatesAutoresizingMaskIntoConstraints = NO;
    [_videoView setBackgroundColor: [UIColor blackColor] ];
    [self.contentView addSubview:_videoView];
    
    _bkView = [[UIView alloc] initWithFrame:CGRectZero];
    _bkView.translatesAutoresizingMaskIntoConstraints = NO;
    [_bkView setBackgroundColor: [UIColor clearColor] ];
    [self.contentView addSubview:_bkView];
    
    _controlView = [[UIView alloc] initWithFrame:CGRectZero];
    _controlView.translatesAutoresizingMaskIntoConstraints = NO;
    _controlView.backgroundColor = [UIColor colorWithRed:64/255.f green:64/255.f blue:64/255.f alpha:1];
    [self.contentView addSubview:_controlView];
    
    _titleLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _titleLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _titleLabel.font = [UIFont systemFontOfSize:12];
    _titleLabel.textColor = [UIColor whiteColor];
    _titleLabel.textAlignment = NSTextAlignmentCenter;
    _titleLabel.backgroundColor = [UIColor colorWithRed:128/255.f green:128/255.f blue:128/255.f alpha:0.5];
    [_titleLabel setText:@"0"];
    [_bkView addSubview:_titleLabel];

    _voiceMuteBnt = [UIButton buttonWithType:UIButtonTypeSystem];
    _voiceMuteBnt.translatesAutoresizingMaskIntoConstraints = NO;
    _voiceMuteBnt.tintColor = [UIColor whiteColor];
    [_voiceMuteBnt setTitle:@"mute" forState:UIControlStateNormal];
    [_voiceMuteBnt addTarget:self action:@selector(onMute:)
            forControlEvents:UIControlEventTouchUpInside];
    [_voiceMuteBnt setTag:0];
    [_controlView addSubview:_voiceMuteBnt];
    
    _videoDoubleBnt = [UIButton buttonWithType:UIButtonTypeSystem];
    _videoDoubleBnt.translatesAutoresizingMaskIntoConstraints = NO;
    _videoDoubleBnt.tintColor = [UIColor whiteColor];
    [_videoDoubleBnt setTitle:@"high" forState:UIControlStateNormal];
    [_videoDoubleBnt addTarget:self action:@selector(onDoubleStream:)
            forControlEvents:UIControlEventTouchUpInside];
    [_videoDoubleBnt setTag:0];
    [_controlView addSubview:_videoDoubleBnt];
    
    _volumeSlider = [[UISlider alloc] initWithFrame:CGRectZero];
    _volumeSlider.translatesAutoresizingMaskIntoConstraints = NO;
    _volumeSlider.minimumValue = 0;
    _volumeSlider.maximumValue = 100;
    _volumeSlider.value = _volumeSlider.maximumValue;
    _volumeSlider.continuous = YES;
    [_volumeSlider setThumbImage:[UIImage imageNamed:@"slider_normal"] forState:UIControlStateNormal];
    [_volumeSlider setThumbImage:[UIImage imageNamed:@"slider_active"] forState:UIControlStateHighlighted];
    [_volumeSlider addTarget:self action:@selector(volumeSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_controlView addSubview:_volumeSlider];
    

    _realTimeVolumeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _realTimeVolumeLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _realTimeVolumeLabel.font = [UIFont systemFontOfSize:12];
    _realTimeVolumeLabel.textColor = [UIColor greenColor];
    _realTimeVolumeLabel.textAlignment = NSTextAlignmentCenter;
    [_bkView addSubview:_realTimeVolumeLabel];
    
    _realTimeVolumeView = [[NADVolumeView alloc] initWithFrame:CGRectZero];
    _realTimeVolumeView.translatesAutoresizingMaskIntoConstraints = NO;
    [_bkView addSubview:_realTimeVolumeView];
    
    [_bkView.topAnchor constraintEqualToAnchor:self.topAnchor].active = YES;
    [_bkView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor].active = YES;
    [_bkView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor].active = YES;
    [_bkView.bottomAnchor constraintEqualToAnchor:_controlView.topAnchor].active = YES;
    
    [_videoView.topAnchor constraintEqualToAnchor:self.topAnchor].active = YES;
    [_videoView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor].active = YES;
    [_videoView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor].active = YES;
    [_videoView.bottomAnchor constraintEqualToAnchor:_controlView.topAnchor ].active = YES;
    
    
    [_controlView.topAnchor constraintEqualToAnchor:self.bottomAnchor constant:-30.0].active = YES;
    [_controlView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor].active = YES;
    [_controlView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor].active = YES;
    [_controlView.bottomAnchor constraintEqualToAnchor:self.bottomAnchor].active = YES;
    
    
    [_titleLabel.topAnchor constraintEqualToAnchor:_videoView.topAnchor].active = YES;
    [_titleLabel.leftAnchor constraintEqualToAnchor:_videoView.leftAnchor].active = YES;
    [_titleLabel.rightAnchor constraintEqualToAnchor:_videoView.rightAnchor].active = YES;
    [_titleLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    
    [_voiceMuteBnt.leftAnchor constraintEqualToAnchor:_controlView.leftAnchor constant:1.0].active =
    YES;
    [_voiceMuteBnt.topAnchor constraintEqualToAnchor:_controlView.topAnchor constant:1.0].active =
    YES;
    [_voiceMuteBnt.widthAnchor constraintEqualToConstant:36].active = YES;
    [_voiceMuteBnt.heightAnchor constraintEqualToConstant:28].active = YES;
    
    [_videoDoubleBnt.leftAnchor constraintEqualToAnchor:_voiceMuteBnt.rightAnchor constant:1.0].active =
    YES;
    [_videoDoubleBnt.topAnchor constraintEqualToAnchor:_controlView.topAnchor constant:1.0].active =
    YES;
    [_videoDoubleBnt.widthAnchor constraintEqualToConstant:36].active = YES;
    [_videoDoubleBnt.heightAnchor constraintEqualToConstant:28].active = YES;
    
    [_volumeSlider.leftAnchor constraintEqualToAnchor:_videoDoubleBnt.rightAnchor constant:2].active =
     YES;
    [_volumeSlider.rightAnchor constraintEqualToAnchor:_controlView.rightAnchor constant:-5].active =
    YES;
    [_volumeSlider.topAnchor constraintEqualToAnchor:_controlView.topAnchor constant:7.0].active =
    YES;
    [_volumeSlider.heightAnchor constraintEqualToConstant:20].active = YES;
    
    [_realTimeVolumeLabel.rightAnchor constraintEqualToAnchor:_videoView.rightAnchor].active =
    YES;
    [_realTimeVolumeLabel.topAnchor constraintEqualToAnchor:_titleLabel.bottomAnchor constant:10.0].active =
    YES;
    [_realTimeVolumeLabel.widthAnchor constraintEqualToConstant:28].active = YES;
    [_realTimeVolumeLabel.heightAnchor constraintEqualToConstant:16].active = YES;
    
    [_realTimeVolumeView.rightAnchor constraintEqualToAnchor:_videoView.rightAnchor constant:-5.0].active =
      YES;
    [_realTimeVolumeView.topAnchor constraintEqualToAnchor:_realTimeVolumeLabel.bottomAnchor].active =
      YES;
    [_realTimeVolumeView.widthAnchor constraintEqualToConstant:16].active = YES;
    [_realTimeVolumeView.heightAnchor constraintEqualToConstant:64].active = YES;
}

- (IBAction) onMute:(id)sender {
    [self.delegate onMuteClick:uid_ mute:![_voiceMuteBnt tag]];
    [self setMuteEnable:![_voiceMuteBnt tag]];
}

- (IBAction) onDoubleStream:(id)sender {
    [self.delegate onVideoStreamChange:uid_ type:![_videoDoubleBnt tag]];
    [self setStreamType:![_videoDoubleBnt tag]];
}

- (void) setMuteEnable:(BOOL)mute{
    if(mute){
        [_voiceMuteBnt setTag:1];
        [_voiceMuteBnt setTitle:@"play" forState:UIControlStateNormal];
    }
    else{
        [_voiceMuteBnt setTag:0];
        [_voiceMuteBnt setTitle:@"mute" forState:UIControlStateNormal];
    }
}

- (void) setStreamType:(int)type{
    if(type){
        [_videoDoubleBnt setTag:1];
        [_videoDoubleBnt setTitle:@"low" forState:UIControlStateNormal];
    }
    else{
        [_videoDoubleBnt setTag:0];
        [_videoDoubleBnt setTitle:@"high" forState:UIControlStateNormal];
    }
}

- (void) volumeSliderValueChanged:(id)sender {
    UISlider *slider = (UISlider *)sender;
    int volume = (int)slider.value;
    [self.delegate onVolumeChange:uid_ volume:volume];
}

- (void) setRealTimeVolume:(int)volume{
    [_realTimeVolumeView setVolume:volume];
    [_realTimeVolumeLabel setText:[NSString stringWithFormat:@"%d", volume]];
}

- (void) setRemoteMute:(BOOL)mute{
    [_realTimeVolumeView setMute:mute];
    [self setRealTimeVolume:0];
}

- (void) setUserId:(uint32_t)userId {
    uid_ = userId;
}

- (uint32_t) getUserId{
    return uid_;
}

- (UIView*) getVideoView{
    return _videoView;
}

- (void) setIndex:(int)idx {
    index_ = idx;
}

- (int) getIndex {
    return index_;
}

@end
