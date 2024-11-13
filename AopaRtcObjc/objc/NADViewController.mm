/*
 *  Copyright 2018 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#include <vector>
#include <map>
#import "NADViewController.h"
#import "NADAppDelegate.h"
#import "UserViewCell.h"
#import <AVFoundation/AVFoundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import "LMJDropdownMenu.h"
#import "VideoFileParser.h"
#import "NetworkLinkView.h"
#define VIDEO_VIEW_WIDTH  [UIScreen mainScreen].bounds.size.width / 2 - 15
#define VIDEO_VIEW_HEIGHT 200

@interface NADViewController ()<BBRtcEngineDelegate, UserViewDelegate,
MPMediaPickerControllerDelegate, UICollectionViewDataSource,
UICollectionViewDelegate, UICollectionViewDelegateFlowLayout,
LMJDropdownMenuDataSource, LMJDropdownMenuDelegate,
BBRtcAudioDataFrameProtocol,
BBRtcVideoSourceProtocol, BBRtcVideoDataFrameProtocol,
ReadVideoFrameDelegate>
@property(nonatomic) UIView *videoView;
@property(nonatomic) UIView *stateView;
@property(nonatomic) UIView *vadStateView;
@property(nonatomic) UIView *bottomView;
@property(nonatomic) UIView *leftView;
@property(nonatomic) UIView *rightView;
@property(nonatomic) UIView *musicView;

@property(nonatomic) UIView *gridLineView;
@property(nonatomic) UIView *gridLineView2;
@property(nonatomic) UILabel* stateLabel;

@property(nonatomic) UIButton* roleSwitchBnt;
@property(nonatomic) UIButton *voiceButton;
@property(nonatomic) UIButton *videoButton;
@property(nonatomic) UIButton *cameraSwitchButton;
@property(nonatomic) UIButton *relayMediaButton;
@property(nonatomic) UIButton *hangUpButton;

@property(nonatomic) UISlider * recordSilder;
@property(nonatomic) UILabel*  recordVolumeTitile;
@property(nonatomic) UILabel*  recordVolumeLabel;

@property(nonatomic) UISlider * playoutSilder;
@property(nonatomic) UILabel*  playoutVolumeTitile;
@property(nonatomic) UILabel*  playoutVolumeLabel;

@property(nonatomic) UISlider * musicVolmueSilder;
@property(nonatomic) UILabel*   musicVolumeTitile;
@property(nonatomic) UILabel*   musicVolumeLabel;

@property(nonatomic) UISlider * musicSilder;
@property(nonatomic) UITextField *   musicNameLabel;
@property(nonatomic) UIButton * musicSelectButton;
@property(nonatomic) UIButton * musicPauseButton;
@property(nonatomic) UIButton * musicPlayButton;
@property(nonatomic) UILabel *   musicTotalTimeLabel;
@property(nonatomic) UILabel *   musicNowTimeLabel;
@property(nonatomic) NSTimer *   musicTimer;
@property(nonatomic, strong) NSString *   musicFilePath;
@property(nonatomic) UICollectionView *   collectionView;

@property(nonatomic) UILabel* audioProfileLabel;
@property(nonatomic) LMJDropdownMenu* audioProfileMenu;
@property(nonatomic) UILabel* chorusRoleLabel;
@property(nonatomic) LMJDropdownMenu* chorusRoleMenu;

@property(nonatomic) VideoFileParser* videoFileParser;
@property(nonatomic, strong) AVAudioPlayer* audioPlayer;

@property(nonatomic) UIButton *netLinkButton;
@property(nonatomic) NetworkLinkView* networkLinkView;

@property (strong, nonatomic) NSTimer *vadTimer;
@end

@implementation NADViewController {
    UIView* view_;
    BOOL refresh_;
    uint32_t userId_;
    BOOL videoOpen_;
    BOOL voiceOpen_;
    BOOL isAnchor_;
    BOOL musicPause_;
    BOOL musicPlay_;
    int musicTotalTimeMs_;
    BOOL relayMedia_;
    BBRtcEngineKit* sharedEngine_;
    NSArray* audioOptionTitles_;
    NSArray* chorusRoleTitles_;
    std::vector<NSUInteger> userList_;
    std::map<NSUInteger, UserViewCell*> allCellMap_;
}

@synthesize hangUpButton = _hangUpButton;
@synthesize consumer = _consumer;

#pragma mark - View controller lifecycle

- (void)loadView {
    audioOptionTitles_ = [[NSArray alloc]initWithObjects:@"default", @"speechmono",@"musicmono", @"musicstero", @"musicmonoHighqulity", @"musicSteroHighQuality", nil];
    chorusRoleTitles_ = [[NSArray alloc]initWithObjects:@"INVALID", @"MAIN", @"DEPUTY", nil];
    view_ = [[UIView alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)];
    [view_ setBackgroundColor: [UIColor blackColor] ];
    _videoView = [[UIView alloc] initWithFrame:CGRectZero];
    _videoView.translatesAutoresizingMaskIntoConstraints = NO;
    [_videoView setBackgroundColor: [UIColor blackColor] ];
    [view_ addSubview:_videoView];
    
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    layout.headerReferenceSize = CGSizeMake(0, 0);
    layout.itemSize = CGSizeMake(110, 160);
    
    _collectionView = [[UICollectionView alloc] initWithFrame:_videoView.frame collectionViewLayout:layout];
    _collectionView.translatesAutoresizingMaskIntoConstraints = NO;
    _collectionView.delegate = self;
    _collectionView.dataSource = self;
    [_videoView addSubview:_collectionView];
    [_collectionView setBackgroundColor: [UIColor clearColor] ];
    [_collectionView registerClass:[UserViewCell class] forCellWithReuseIdentifier:@"cellId"];
    [_collectionView registerClass:[UICollectionReusableView class] forSupplementaryViewOfKind:UICollectionElementKindSectionHeader withReuseIdentifier:@"reusableView"];
    
    _stateView = [[UIView alloc] initWithFrame:CGRectZero];
    _stateView.translatesAutoresizingMaskIntoConstraints = NO;
    _stateView.backgroundColor = [UIColor colorWithRed:64/255.f green:64/255.f blue:64/255.f alpha:0.7];
    [view_ addSubview:_stateView];
    
    _bottomView = [[UIView alloc] initWithFrame:CGRectZero];
    _bottomView.translatesAutoresizingMaskIntoConstraints = NO;
    [_bottomView setBackgroundColor: [UIColor colorWithRed:80/255.f green:80/255.f blue:80/255.f alpha:1]];
    [view_ addSubview:_bottomView];
    
    _gridLineView = [[UIView alloc] initWithFrame:CGRectZero];
    _gridLineView.translatesAutoresizingMaskIntoConstraints = NO;
    [_gridLineView setBackgroundColor: [UIColor colorWithRed:200/255.f green:200/255.f blue:200/255.f alpha:1]];
    [_bottomView addSubview:_gridLineView];
    
    _gridLineView2 = [[UIView alloc] initWithFrame:CGRectZero];
    _gridLineView2.translatesAutoresizingMaskIntoConstraints = NO;
    [_gridLineView2 setBackgroundColor: [UIColor colorWithRed:200/255.f green:200/255.f blue:200/255.f alpha:1]];
    [_bottomView addSubview:_gridLineView2];
    
    _rightView = [[UIView alloc] initWithFrame:CGRectZero];
    _rightView.translatesAutoresizingMaskIntoConstraints = NO;
    [_rightView setBackgroundColor: [UIColor colorWithRed:80/255.f green:80/255.f blue:80/255.f alpha:1]];
    [_bottomView addSubview:_rightView];
    
    _musicView = [[UIView alloc] initWithFrame:CGRectZero];
    _musicView.translatesAutoresizingMaskIntoConstraints = NO;
    [_musicView setBackgroundColor: [UIColor colorWithRed:80/255.f green:80/255.f blue:80/255.f alpha:1]];
    [_bottomView addSubview:_musicView];
    
    _leftView = [[UIView alloc] initWithFrame:CGRectZero];
    _leftView.translatesAutoresizingMaskIntoConstraints = NO;
    [_leftView setBackgroundColor: [UIColor colorWithRed:80/255.f green:80/255.f blue:0/255.f alpha:1]];
    [_bottomView addSubview:_leftView];
    
    _vadStateView = [[UIView alloc] initWithFrame:CGRectZero];
    _vadStateView.translatesAutoresizingMaskIntoConstraints = NO;
    [_vadStateView setBackgroundColor: [UIColor whiteColor]];
    _vadStateView.layer.cornerRadius = 8;
    [_stateView addSubview:_vadStateView];
    
    
    _stateLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _stateLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _stateLabel.font = [UIFont systemFontOfSize:12];
    _stateLabel.textColor = [UIColor redColor];
    _stateLabel.textAlignment = NSTextAlignmentLeft;
    _stateLabel.text = @"";
    [_stateView addSubview:_stateLabel];
    
    _hangUpButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _hangUpButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_hangUpButton setTitle:@"leave" forState:UIControlStateNormal];
    [_hangUpButton addTarget:self action:@selector(hangUp:)
            forControlEvents:UIControlEventTouchUpInside];
    [_rightView addSubview:_hangUpButton];
    
    _videoButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _videoButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_videoButton setTitle:@"video off" forState:UIControlStateNormal];
    [_videoButton addTarget:self action:@selector(videoSwitch:)
           forControlEvents:UIControlEventTouchUpInside];
    [_rightView addSubview:_videoButton];
    
    _voiceButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _voiceButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_voiceButton setTitle:@"voice off" forState:UIControlStateNormal];
    [_voiceButton addTarget:self action:@selector(voiceSwitch:)
           forControlEvents:UIControlEventTouchUpInside];
    [_rightView addSubview:_voiceButton];
    
    _roleSwitchBnt = [UIButton buttonWithType:UIButtonTypeSystem];
    _roleSwitchBnt.translatesAutoresizingMaskIntoConstraints = NO;
    [_roleSwitchBnt addTarget:self action:@selector(roleSwitch:)
             forControlEvents:UIControlEventTouchUpInside];
    [_rightView addSubview:_roleSwitchBnt];
    
    _cameraSwitchButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _cameraSwitchButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_cameraSwitchButton setTitle:@"camera switch" forState:UIControlStateNormal];
    [_cameraSwitchButton addTarget:self action:@selector(cameraSwitch:)
                  forControlEvents:UIControlEventTouchUpInside];
    [_rightView addSubview:_cameraSwitchButton];
    
    
    _relayMediaButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _relayMediaButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_relayMediaButton setTitle:@"start relay" forState:UIControlStateNormal];
    [_relayMediaButton addTarget:self action:@selector(relayMedia:)
                forControlEvents:UIControlEventTouchUpInside];
    [_rightView addSubview:_relayMediaButton];
    
    _recordSilder = [[UISlider alloc] initWithFrame:CGRectZero];
    _recordSilder.translatesAutoresizingMaskIntoConstraints = NO;
    _recordSilder.minimumValue = 0;
    _recordSilder.maximumValue = 200;
    _recordSilder.value = 100;
    _recordSilder.continuous = YES;
    [_recordSilder setThumbImage:[UIImage imageNamed:@"slider_normal"] forState:UIControlStateNormal];
    [_recordSilder setThumbImage:[UIImage imageNamed:@"slider_active"] forState:UIControlStateHighlighted];
    [_recordSilder addTarget:self action:@selector(recordSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_leftView addSubview:_recordSilder];
    
    _recordVolumeTitile = [[UILabel alloc] initWithFrame:CGRectZero];
    _recordVolumeTitile.translatesAutoresizingMaskIntoConstraints = NO;
    _recordVolumeTitile.font = [UIFont systemFontOfSize:12];
    _recordVolumeTitile.textColor = [UIColor whiteColor];
    _recordVolumeTitile.textAlignment = NSTextAlignmentLeft;
    [_recordVolumeTitile setText:@"record"];
    [_leftView addSubview:_recordVolumeTitile];
    
    _recordVolumeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _recordVolumeLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _recordVolumeLabel.font = [UIFont systemFontOfSize:12];
    _recordVolumeLabel.textColor = [UIColor whiteColor];
    _recordVolumeLabel.textAlignment = NSTextAlignmentCenter;
    [_recordVolumeLabel setText:@"100"];
    [_leftView addSubview:_recordVolumeLabel];
    
    
    _playoutSilder = [[UISlider alloc] initWithFrame:CGRectZero];
    _playoutSilder.translatesAutoresizingMaskIntoConstraints = NO;
    _playoutSilder.minimumValue = 0;
    _playoutSilder.maximumValue = 200;
    _playoutSilder.value = 100;
    _playoutSilder.continuous = YES;
    [_playoutSilder setThumbImage:[UIImage imageNamed:@"slider_normal"] forState:UIControlStateNormal];
    [_playoutSilder setThumbImage:[UIImage imageNamed:@"slider_active"] forState:UIControlStateHighlighted];
    
    [_playoutSilder addTarget:self action:@selector(playoutSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_leftView addSubview:_playoutSilder];
    
    _playoutVolumeTitile = [[UILabel alloc] initWithFrame:CGRectZero];
    _playoutVolumeTitile.translatesAutoresizingMaskIntoConstraints = NO;
    _playoutVolumeTitile.font = [UIFont systemFontOfSize:12];
    _playoutVolumeTitile.textColor = [UIColor whiteColor];
    _playoutVolumeTitile.textAlignment = NSTextAlignmentLeft;
    [_playoutVolumeTitile setText:@"playout"];
    [_leftView addSubview:_playoutVolumeTitile];
    
    
    _playoutVolumeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _playoutVolumeLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _playoutVolumeLabel.font = [UIFont systemFontOfSize:12];
    _playoutVolumeLabel.textColor = [UIColor whiteColor];
    _playoutVolumeLabel.textAlignment = NSTextAlignmentCenter;
    [_playoutVolumeLabel setText:@"100"];
    [_leftView addSubview:_playoutVolumeLabel];
    
    _musicVolmueSilder = [[UISlider alloc] initWithFrame:CGRectZero];
    _musicVolmueSilder.translatesAutoresizingMaskIntoConstraints = NO;
    _musicVolmueSilder.minimumValue = 0;
    _musicVolmueSilder.maximumValue = 200;
    _musicVolmueSilder.value = 100;
    _musicVolmueSilder.continuous = YES;
    [_musicVolmueSilder setThumbImage:[UIImage imageNamed:@"slider_normal"] forState:UIControlStateNormal];
    [_musicVolmueSilder setThumbImage:[UIImage imageNamed:@"slider_active"] forState:UIControlStateHighlighted];
    
    [_musicVolmueSilder addTarget:self action:@selector(musicVolumeSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_leftView addSubview:_musicVolmueSilder];
    
    _musicVolumeTitile = [[UILabel alloc] initWithFrame:CGRectZero];
    _musicVolumeTitile.translatesAutoresizingMaskIntoConstraints = NO;
    _musicVolumeTitile.font = [UIFont systemFontOfSize:12];
    _musicVolumeTitile.textColor = [UIColor whiteColor];
    _musicVolumeTitile.textAlignment = NSTextAlignmentLeft;
    [_musicVolumeTitile setText:@"music"];
    [_leftView addSubview:_musicVolumeTitile];
    
    
    _musicVolumeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _musicVolumeLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _musicVolumeLabel.font = [UIFont systemFontOfSize:12];
    _musicVolumeLabel.textColor = [UIColor whiteColor];
    _musicVolumeLabel.textAlignment = NSTextAlignmentCenter;
    [_musicVolumeLabel setText:@"100"];
    [_leftView addSubview:_musicVolumeLabel];
    
    
    _musicSilder = [[UISlider alloc] initWithFrame:CGRectZero];
    _musicSilder.translatesAutoresizingMaskIntoConstraints = NO;
    _musicSilder.minimumValue = 0;
    _musicSilder.maximumValue = 1;
    _musicSilder.value = 0;
    _musicSilder.continuous = NO;
    [_musicSilder setThumbImage:[UIImage imageNamed:@"slider_normal"] forState:UIControlStateNormal];
    [_musicSilder setThumbImage:[UIImage imageNamed:@"slider_active"] forState:UIControlStateHighlighted];
    [_musicSilder addTarget:self action:@selector(musicSliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    [_musicView addSubview:_musicSilder];
    
    _musicNameLabel = [[UITextField alloc] initWithFrame:CGRectZero];
    _musicNameLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _musicNameLabel.font = [UIFont systemFontOfSize:13];
    _musicNameLabel.textColor = [UIColor blackColor];
    [_musicNameLabel textRectForBounds:CGRectMake(2, 0, 0, 0)];
    [_musicNameLabel setBackgroundColor: [UIColor whiteColor] ];
    [_musicNameLabel setTintColor:[UIColor blackColor]];
    _musicNameLabel.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _musicNameLabel.layer.borderWidth  = 1;
    _musicNameLabel.layer.cornerRadius = 3;
    NSArray<NSString *> *musics= @[@"https://rtc-resouce.oss-ap-southeast-1.aliyuncs.com/music/%E5%80%92%E6%95%B0.mp3",
                                   @"https://rtc-resouce.oss-ap-southeast-1.aliyuncs.com/music/%E5%8F%A5%E5%8F%B7.mp3",
                                   @"https://rtc-resouce.oss-ap-southeast-1.aliyuncs.com/music/%E5%91%8A%E7%99%BD%E6%B0%94%E7%90%83.mp3",
                                   @"https://rtc-resouce.oss-ap-southeast-1.aliyuncs.com/music/%E5%96%9C%E6%AC%A2%E4%BD%A0.mp3",
                                   @"https://rtc-resouce.oss-ap-southeast-1.aliyuncs.com/music/%E6%99%B4%E5%A4%A9.mp3",
                                   @"https://rtc-resouce.oss-ap-southeast-1.aliyuncs.com/music/%E7%94%BB.mp3",
                                   @"https://xs-voice.oss-cn-hangzhou.aliyuncs.com/upload/music/de29ca47f33a997ac6ecf8bdcff1a095.mp3"];
    int index = arc4random() % [musics count];
    _musicNameLabel.text = musics[index];
    [_musicView addSubview:_musicNameLabel];
    [_musicNameLabel setEnabled:YES];
    [_musicNameLabel setMultipleTouchEnabled:NO];
    
    _musicSelectButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _musicSelectButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_musicSelectButton setTitle:@"local" forState:UIControlStateNormal];
    [_musicSelectButton addTarget:self action:@selector(onMusicSelectClick:)
                 forControlEvents:UIControlEventTouchUpInside];
    [_musicView addSubview:_musicSelectButton];
    
    _musicPauseButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _musicPauseButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_musicPauseButton setTitle:@"pause" forState:UIControlStateNormal];
    [_musicPauseButton addTarget:self action:@selector(onMusicPauseClick:)
                forControlEvents:UIControlEventTouchUpInside];
    [_musicView addSubview:_musicPauseButton];
    
    _musicPlayButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _musicPlayButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_musicPlayButton setTitle:@"play" forState:UIControlStateNormal];
    [_musicPlayButton addTarget:self action:@selector(onMusicPlayClick:)
               forControlEvents:UIControlEventTouchUpInside];
    [_musicView addSubview:_musicPlayButton];
    
    _musicTotalTimeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _musicTotalTimeLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _musicTotalTimeLabel.font = [UIFont systemFontOfSize:12];
    _musicTotalTimeLabel.textColor = [UIColor whiteColor];
    _musicTotalTimeLabel.textAlignment = NSTextAlignmentCenter;
    _musicTotalTimeLabel.text = @"00:00";
    [_musicView addSubview:_musicTotalTimeLabel];
    
    _musicNowTimeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _musicNowTimeLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _musicNowTimeLabel.font = [UIFont systemFontOfSize:12];
    _musicNowTimeLabel.textColor = [UIColor whiteColor];
    _musicNowTimeLabel.textAlignment = NSTextAlignmentCenter;
    _musicNowTimeLabel.text = @"00:00";
    [_musicView addSubview:_musicNowTimeLabel];
    
    _audioProfileLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _audioProfileLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _audioProfileLabel.font = [UIFont systemFontOfSize:12];
    _audioProfileLabel.textColor = [UIColor whiteColor];
    _audioProfileLabel.textAlignment = NSTextAlignmentLeft;
    [_audioProfileLabel setText:@"profile"];
    [_leftView addSubview:_audioProfileLabel];
    
    _audioProfileMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_audioProfileMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _audioProfileMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _audioProfileMenu.dataSource = self;
    _audioProfileMenu.delegate   = self;
    _audioProfileMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _audioProfileMenu.layer.borderWidth  = 1;
    _audioProfileMenu.layer.cornerRadius = 5;
    [_leftView addSubview:_audioProfileMenu];
    
    _audioProfileMenu.title           = audioOptionTitles_[_audioType];
    _audioProfileMenu.titleFont       = [UIFont systemFontOfSize:12];
    _audioProfileMenu.optionTextColor = [UIColor blackColor];
    _audioProfileMenu.titleColor      = [UIColor whiteColor];
    _audioProfileMenu.titleAlignment  = NSTextAlignmentLeft;
    _audioProfileMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 5, 0, 0);
    
    _chorusRoleLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _chorusRoleLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _chorusRoleLabel.font = [UIFont systemFontOfSize:12];
    _chorusRoleLabel.textColor = [UIColor whiteColor];
    _chorusRoleLabel.textAlignment = NSTextAlignmentLeft;
    [_chorusRoleLabel setText:@"chorus"];
    [_leftView addSubview:_chorusRoleLabel];
    
    _chorusRoleMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_chorusRoleMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _chorusRoleMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _chorusRoleMenu.dataSource = self;
    _chorusRoleMenu.delegate   = self;
    _chorusRoleMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _chorusRoleMenu.layer.borderWidth  = 1;
    _chorusRoleMenu.layer.cornerRadius = 5;
    [_leftView addSubview:_chorusRoleMenu];
    
    _chorusRoleMenu.title           = chorusRoleTitles_[0];
    _chorusRoleMenu.titleFont       = [UIFont systemFontOfSize:12];
    _chorusRoleMenu.optionTextColor = [UIColor blackColor];
    _chorusRoleMenu.titleColor      = [UIColor whiteColor];
    _chorusRoleMenu.titleAlignment  = NSTextAlignmentLeft;
    _chorusRoleMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 5, 0, 0);
    
    
    [_videoView.leftAnchor constraintEqualToAnchor:view_.leftAnchor constant:1].active = YES;
    [_videoView.topAnchor constraintEqualToAnchor:view_.topAnchor].active = YES;
    [_videoView.rightAnchor constraintEqualToAnchor:view_.rightAnchor].active = YES;
    [_videoView.bottomAnchor constraintEqualToAnchor:_stateView.topAnchor ].active = YES;
    
    [_collectionView.leftAnchor constraintEqualToAnchor:_videoView.leftAnchor].active = YES;
    [_collectionView.topAnchor constraintEqualToAnchor:_videoView.topAnchor].active = YES;
    [_collectionView.rightAnchor constraintEqualToAnchor:_videoView.rightAnchor].active = YES;
    [_collectionView.bottomAnchor constraintEqualToAnchor:_videoView.bottomAnchor ].active = YES;
    
    [_stateView.leftAnchor constraintEqualToAnchor:view_.leftAnchor constant:0].active = YES;
    [_stateView.rightAnchor constraintEqualToAnchor:view_.rightAnchor].active = YES;
    [_stateView.bottomAnchor constraintEqualToAnchor:_bottomView.topAnchor constant:0].active = YES;
    [_stateView.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_bottomView.leftAnchor constraintEqualToAnchor:view_.leftAnchor].active = YES;
    [_bottomView.rightAnchor constraintEqualToAnchor:view_.rightAnchor].active = YES;
    [_bottomView.bottomAnchor constraintEqualToAnchor:view_.bottomAnchor].active = YES;
    [_bottomView.heightAnchor constraintEqualToConstant:260].active = YES;
    
    [_stateLabel.leftAnchor constraintEqualToAnchor:_stateView.leftAnchor constant:5].active = YES;
    [_stateLabel.rightAnchor constraintEqualToAnchor:_vadStateView.leftAnchor].active = YES;
    [_stateLabel.topAnchor constraintEqualToAnchor:_stateView.topAnchor].active = YES;
    [_stateLabel.bottomAnchor constraintEqualToAnchor:_stateView.bottomAnchor ].active = YES;
    
    [_vadStateView.rightAnchor constraintEqualToAnchor:_stateView.rightAnchor constant:-5.0].active =
    YES;
    [_vadStateView.topAnchor constraintEqualToAnchor:_stateView.topAnchor constant:4].active =
    YES;
    [_vadStateView.widthAnchor constraintEqualToConstant:16].active = YES;
    [_vadStateView.heightAnchor constraintEqualToConstant:16].active = YES;
    
    [_leftView.leftAnchor constraintEqualToAnchor:_bottomView.leftAnchor].active = YES;
    [_leftView.rightAnchor constraintEqualToAnchor:_gridLineView.leftAnchor].active = YES;
    [_leftView.topAnchor constraintEqualToAnchor:_bottomView.topAnchor].active = YES;
    [_leftView.heightAnchor constraintEqualToConstant:180].active = YES;
    
    [_gridLineView.rightAnchor constraintEqualToAnchor:_rightView.leftAnchor].active = YES;
    [_gridLineView.widthAnchor constraintEqualToConstant:1].active = YES;
    [_gridLineView.topAnchor constraintEqualToAnchor:_bottomView.topAnchor].active = YES;
    [_gridLineView.heightAnchor constraintEqualToConstant:150].active = YES;
    
    [_rightView.rightAnchor constraintEqualToAnchor:_bottomView.rightAnchor].active = YES;
    [_rightView.widthAnchor constraintEqualToConstant:120].active = YES;
    [_rightView.topAnchor constraintEqualToAnchor:_bottomView.topAnchor].active = YES;
    [_rightView.heightAnchor constraintEqualToConstant:180].active = YES;
    
    [_gridLineView2.leftAnchor constraintEqualToAnchor:_bottomView.leftAnchor].active = YES;
    [_gridLineView2.rightAnchor constraintEqualToAnchor:_bottomView.rightAnchor].active = YES;
    [_gridLineView2.heightAnchor constraintEqualToConstant:1].active = YES;
    [_gridLineView2.topAnchor constraintEqualToAnchor:_leftView.bottomAnchor].active = YES;
    
    [_musicView.leftAnchor constraintEqualToAnchor:_bottomView.leftAnchor].active = YES;
    [_musicView.rightAnchor constraintEqualToAnchor:_bottomView.rightAnchor].active = YES;
    [_musicView.topAnchor constraintEqualToAnchor:_gridLineView2.bottomAnchor].active = YES;
    [_musicView.bottomAnchor constraintEqualToAnchor:_bottomView.bottomAnchor].active = YES;
    
    [_roleSwitchBnt.leftAnchor constraintEqualToAnchor:_rightView.leftAnchor constant:10].active =
    YES;
    [_roleSwitchBnt.topAnchor constraintEqualToAnchor:_rightView.topAnchor constant:3].active =
    YES;
    [_roleSwitchBnt.widthAnchor constraintEqualToConstant:100].active = YES;
    [_roleSwitchBnt.heightAnchor constraintEqualToConstant:26].active = YES;
    
    [_voiceButton.leftAnchor constraintEqualToAnchor:_roleSwitchBnt.leftAnchor ].active =
    YES;
    [_voiceButton.rightAnchor constraintEqualToAnchor:_roleSwitchBnt.rightAnchor].active =
    YES;
    [_voiceButton.topAnchor constraintEqualToAnchor:_roleSwitchBnt.bottomAnchor constant:3].active =
    YES;
    [_voiceButton.heightAnchor constraintEqualToConstant:26].active = YES;
    
    [_videoButton.leftAnchor constraintEqualToAnchor:_roleSwitchBnt.leftAnchor ].active =
    YES;
    [_videoButton.rightAnchor constraintEqualToAnchor:_roleSwitchBnt.rightAnchor].active =
    YES;
    [_videoButton.topAnchor constraintEqualToAnchor:_voiceButton.bottomAnchor constant:3].active =
    YES;
    [_videoButton.heightAnchor constraintEqualToConstant:26].active = YES;
    
    [_cameraSwitchButton.leftAnchor constraintEqualToAnchor:_videoButton.leftAnchor ].active =
    YES;
    [_cameraSwitchButton.rightAnchor constraintEqualToAnchor:_videoButton.rightAnchor].active =
    YES;
    [_cameraSwitchButton.topAnchor constraintEqualToAnchor:_videoButton.bottomAnchor constant:3].active =
    YES;
    [_cameraSwitchButton.heightAnchor constraintEqualToConstant:26].active = YES;
    
    [_relayMediaButton.leftAnchor constraintEqualToAnchor:_roleSwitchBnt.leftAnchor ].active =
    YES;
    [_relayMediaButton.rightAnchor constraintEqualToAnchor:_roleSwitchBnt.rightAnchor].active =
    YES;
    [_relayMediaButton.topAnchor constraintEqualToAnchor:_cameraSwitchButton.bottomAnchor constant:3].active =
    YES;
    [_relayMediaButton.heightAnchor constraintEqualToConstant:26].active = YES;
    
    [_hangUpButton.leftAnchor constraintEqualToAnchor:_roleSwitchBnt.leftAnchor ].active =
    YES;
    [_hangUpButton.rightAnchor constraintEqualToAnchor:_roleSwitchBnt.rightAnchor].active =
    YES;
    [_hangUpButton.topAnchor constraintEqualToAnchor:_relayMediaButton.bottomAnchor constant:3].active =
    YES;
    [_hangUpButton.heightAnchor constraintEqualToConstant:26].active = YES;
    
    [_chorusRoleLabel.leftAnchor constraintEqualToAnchor:_leftView.leftAnchor constant:4].active =
    YES;
    [_chorusRoleLabel.topAnchor constraintEqualToAnchor:_leftView.topAnchor constant:10].active =
    YES;
    [_chorusRoleLabel.widthAnchor constraintEqualToConstant:48].active = YES;
    [_chorusRoleLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_chorusRoleMenu.leftAnchor constraintEqualToAnchor:_chorusRoleLabel.rightAnchor].active =
    YES;
    [_chorusRoleMenu.topAnchor constraintEqualToAnchor:_chorusRoleLabel.topAnchor constant:-4].active =
    YES;
    [_chorusRoleMenu.rightAnchor constraintEqualToAnchor:_leftView.rightAnchor constant:-6].active =
    YES;
    [_chorusRoleMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioProfileLabel.leftAnchor constraintEqualToAnchor:_leftView.leftAnchor constant:4].active =
    YES;
    [_audioProfileLabel.topAnchor constraintEqualToAnchor:_chorusRoleLabel.bottomAnchor constant:10].active =
    YES;
    [_audioProfileLabel.widthAnchor constraintEqualToConstant:48].active = YES;
    [_audioProfileLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_audioProfileMenu.leftAnchor constraintEqualToAnchor:_audioProfileLabel.rightAnchor].active =
    YES;
    [_audioProfileMenu.topAnchor constraintEqualToAnchor:_audioProfileLabel.topAnchor constant:-4].active =
    YES;
    [_audioProfileMenu.rightAnchor constraintEqualToAnchor:_leftView.rightAnchor constant:-6].active =
    YES;
    [_audioProfileMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_playoutVolumeTitile.leftAnchor constraintEqualToAnchor:_leftView.leftAnchor constant:4].active =
    YES;
    [_playoutVolumeTitile.topAnchor constraintEqualToAnchor:_audioProfileLabel.bottomAnchor constant:10].active =
    YES;
    [_playoutVolumeTitile.widthAnchor constraintEqualToConstant:50].active = YES;
    [_playoutVolumeTitile.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_playoutVolumeLabel.rightAnchor constraintEqualToAnchor:_leftView.rightAnchor ].active =
    YES;
    [_playoutVolumeLabel.topAnchor constraintEqualToAnchor:_playoutVolumeTitile.topAnchor].active =
    YES;
    [_playoutVolumeLabel.widthAnchor constraintEqualToConstant:36].active = YES;
    [_playoutVolumeLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_playoutSilder.leftAnchor constraintEqualToAnchor:_playoutVolumeTitile.rightAnchor].active =
    YES;
    [_playoutSilder.topAnchor constraintEqualToAnchor:_playoutVolumeTitile.topAnchor].active =
    YES;
    [_playoutSilder.rightAnchor constraintEqualToAnchor:_playoutVolumeLabel.leftAnchor ].active =
    YES;
    [_playoutSilder.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_recordVolumeTitile.leftAnchor constraintEqualToAnchor:_playoutVolumeTitile.leftAnchor].active =
    YES;
    [_recordVolumeTitile.topAnchor constraintEqualToAnchor:_playoutVolumeTitile.bottomAnchor constant:10].active =
    YES;
    [_recordVolumeTitile.widthAnchor constraintEqualToConstant:50].active = YES;
    [_recordVolumeTitile.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_recordVolumeLabel.rightAnchor constraintEqualToAnchor:_playoutVolumeLabel.rightAnchor ].active =
    YES;
    [_recordVolumeLabel.topAnchor constraintEqualToAnchor:_recordVolumeTitile.topAnchor].active =
    YES;
    [_recordVolumeLabel.widthAnchor constraintEqualToConstant:36].active = YES;
    [_recordVolumeLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_recordSilder.leftAnchor constraintEqualToAnchor:_recordVolumeTitile.rightAnchor].active =
    YES;
    [_recordSilder.topAnchor constraintEqualToAnchor:_recordVolumeTitile.topAnchor constant:0].active =
    YES;
    [_recordSilder.rightAnchor constraintEqualToAnchor:_recordVolumeLabel.leftAnchor ].active =
    YES;
    [_recordSilder.heightAnchor constraintEqualToConstant:24].active = YES;
    
    
    [_musicVolumeTitile.leftAnchor constraintEqualToAnchor:_playoutVolumeTitile.leftAnchor].active =
    YES;
    [_musicVolumeTitile.topAnchor constraintEqualToAnchor:_recordVolumeTitile.bottomAnchor constant:10].active =
    YES;
    [_musicVolumeTitile.widthAnchor constraintEqualToConstant:50].active = YES;
    [_musicVolumeTitile.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_musicVolumeLabel.rightAnchor constraintEqualToAnchor:_recordVolumeLabel.rightAnchor ].active =
    YES;
    [_musicVolumeLabel.topAnchor constraintEqualToAnchor:_musicVolumeTitile.topAnchor].active =
    YES;
    [_musicVolumeLabel.widthAnchor constraintEqualToConstant:36].active = YES;
    [_musicVolumeLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_musicVolmueSilder.leftAnchor constraintEqualToAnchor:_musicVolumeTitile.rightAnchor].active =
    YES;
    [_musicVolmueSilder.topAnchor constraintEqualToAnchor:_musicVolumeTitile.topAnchor].active =
    YES;
    [_musicVolmueSilder.rightAnchor constraintEqualToAnchor:_musicVolumeLabel.leftAnchor ].active =
    YES;
    [_musicVolmueSilder.heightAnchor constraintEqualToConstant:24].active = YES;
    
    
    [_musicNameLabel.rightAnchor constraintEqualToAnchor:_musicSelectButton.leftAnchor constant:-5].active =
    YES;
    [_musicNameLabel.topAnchor constraintEqualToAnchor:_musicView.topAnchor constant:10].active =YES;
    [_musicNameLabel.leftAnchor constraintEqualToAnchor:_musicView.leftAnchor constant:4].active =
    YES;
    [_musicNameLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    YES;
    [_musicSelectButton.topAnchor constraintEqualToAnchor:_musicNameLabel.topAnchor].active =YES;
    [_musicSelectButton.rightAnchor constraintEqualToAnchor:_musicView.rightAnchor constant:-5].active =
    YES;
    [_musicSelectButton.widthAnchor constraintEqualToConstant:50].active = YES;
    [_musicSelectButton.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_musicPauseButton.topAnchor constraintEqualToAnchor:_musicPlayButton.topAnchor].active =YES;
    [_musicPauseButton.rightAnchor constraintEqualToAnchor:_musicPlayButton.leftAnchor].active = YES;
    [_musicPauseButton.widthAnchor constraintEqualToConstant:50].active = YES;
    [_musicPauseButton.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_musicPlayButton.topAnchor  constraintEqualToAnchor:_musicNameLabel.bottomAnchor constant:15].active =YES;
    [_musicPlayButton.rightAnchor constraintEqualToAnchor:_musicView.rightAnchor constant:-2].active =
    YES;
    [_musicPlayButton.widthAnchor constraintEqualToConstant:50].active = YES;
    [_musicPlayButton.heightAnchor constraintEqualToConstant:24].active = YES;
    
    
    [_musicNowTimeLabel.topAnchor  constraintEqualToAnchor:_musicNameLabel.bottomAnchor constant:15].active =YES;
    [_musicNowTimeLabel.leftAnchor constraintEqualToAnchor:_musicView.leftAnchor ].active =
    YES;
    [_musicNowTimeLabel.widthAnchor constraintEqualToConstant:48].active = YES;
    [_musicNowTimeLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    
    [_musicTotalTimeLabel.topAnchor  constraintEqualToAnchor:_musicNowTimeLabel.topAnchor].active =YES;
    [_musicTotalTimeLabel.rightAnchor constraintEqualToAnchor:_musicPauseButton.leftAnchor constant:-4].active =
    YES;
    [_musicTotalTimeLabel.widthAnchor constraintEqualToConstant:48].active = YES;
    [_musicTotalTimeLabel.heightAnchor constraintEqualToConstant:24].active = YES;
    
    [_musicSilder.topAnchor  constraintEqualToAnchor:_musicTotalTimeLabel.topAnchor].active =YES;
    [_musicSilder.leftAnchor constraintEqualToAnchor:_musicNowTimeLabel.rightAnchor].active = YES;
    [_musicSilder.rightAnchor constraintEqualToAnchor:_musicTotalTimeLabel.leftAnchor].active =
    YES;
    [_musicSilder.heightAnchor constraintEqualToConstant:24].active = YES;
    
    self.view = view_;
}

- (void) addNetworkLinkView{
    
    _netLinkButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _netLinkButton.translatesAutoresizingMaskIntoConstraints = NO;
    [_netLinkButton setTitle:@"settings" forState:UIControlStateNormal];
    [_netLinkButton addTarget:self action:@selector(netSetting:)
             forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_netLinkButton];
    
    _networkLinkView = [[NetworkLinkView alloc] initWithFrame:CGRectZero];
    _networkLinkView.translatesAutoresizingMaskIntoConstraints = NO;
    _networkLinkView.hidden = YES;
    [_networkLinkView loadview:sharedEngine_];
    [self.view addSubview:_networkLinkView];
    
    UILayoutGuide *margin = view_.layoutMarginsGuide;
    [_networkLinkView.centerXAnchor constraintEqualToAnchor:margin.centerXAnchor ].active = YES;
    [_networkLinkView.topAnchor constraintEqualToAnchor:margin.topAnchor constant:0.0].active = YES;
    [_networkLinkView.widthAnchor constraintEqualToConstant:250].active = YES;
    [_networkLinkView.heightAnchor constraintEqualToConstant:360].active = YES;
    
    [_netLinkButton.rightAnchor constraintEqualToAnchor:_vadStateView.leftAnchor constant:-20.0].active =
    YES;
    [_netLinkButton.topAnchor constraintEqualToAnchor:_stateView.topAnchor constant:0].active =
    YES;
    [_netLinkButton.widthAnchor constraintEqualToConstant:60].active = YES;
    [_netLinkButton.heightAnchor constraintEqualToConstant:24].active = YES;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    refresh_ = NO;
    [self joinRoom];
    [_collectionView reloadData];
    [self addNetworkLinkView];
}

- (void)joinRoom{
    NSString* testAppId = @"6MHg9hZqMMcKjNyiauSyU8H5b3eTr4qM"; //Test appid
    sharedEngine_ = [BBRtcEngineKit sharedEngineWithAppId:testAppId delegate:nil];
    sharedEngine_.delegate = self;
    [sharedEngine_ setLogFilter:BBRtcLogFilterDebug];
    [sharedEngine_ enableMainQueueDispatch:YES];
    [sharedEngine_ enableAudio];
    if(_videoEnabled){
        [sharedEngine_ enableVideo];
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
        if(_videoSourceEnabled){
            [sharedEngine_ setVideoSource:self];
        }
    }
    else{
        [sharedEngine_ disableVideo];
    }
    [sharedEngine_ setClientRole:(BBRtcClientRole)_userRole];
    [sharedEngine_ setChannelProfile:BBRtcChannelProfileLiveBroadcasting];
    [sharedEngine_ setAudioProfile:(BBRtcAudioProfile)_audioType scenario:(BBRtcAudioScenario)_scenarioType];
    [sharedEngine_ setEnableSpeakerphone:_speakerEnabled];
    if([sharedEngine_ joinChannelByToken:_token channelId:self.channelId info:@"" uid:userId_ joinSuccess:nil] != BBRtcErrorCodeNoError){
        [self dismissViewControllerAnimated:YES completion:nil];
        return;
    }
    [sharedEngine_ enableAudioVolumeIndication:500 smooth:3 report_vad:YES];
    if(_userRole == BBRtcClientRoleBroadcaster){
        isAnchor_ = YES;
        [_roleSwitchBnt setTitle:@"down" forState:UIControlStateNormal];
    }
    else{
        isAnchor_ = NO;
        [_roleSwitchBnt setTitle:@"up" forState:UIControlStateNormal];
    }
    userId_ = self.userId;
    [self addUserView:userId_];
    voiceOpen_ = YES;
    musicPause_ = NO;
    musicPlay_ = NO;
    videoOpen_ = _videoEnabled;
    relayMedia_ = NO;
    self.vadTimer = [NSTimer scheduledTimerWithTimeInterval:10.0
                                                     target:self
                                                   selector:@selector(timerFired)
                                                   userInfo:nil
                                                    repeats:YES];
}
- (void)dealloc{
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view endEditing:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)timerFired {
    [sharedEngine_ getVoiceDuration];
}

-(void) addUserView:(NSUInteger)uid {
    auto ite = std::find(userList_.begin(), userList_.end(), uid);
    if (ite == userList_.end()) {
        if (uid == (int)userId_) {
            userList_.insert(userList_.begin(), uid);
        } else {
            userList_.push_back(uid);
        }
        [self.collectionView reloadData];
    }
}

-(void) removeUserView:(NSUInteger)uid {
    auto ite = std::find(userList_.begin(), userList_.end(), uid);
    if (ite != userList_.end()) {
        userList_.erase(ite);
    }
    [self.collectionView reloadData];
}

-(void) updateUserView {
    int size = (int)userList_.size();
    auto it = allCellMap_.begin();
    for (int i = 0; i < size && it != allCellMap_.end(); i++, it++) {
        NSUInteger uid = userList_[i];
        UserViewCell* cell = it->second;
        NSUInteger cellUid = [cell getUserId];
        if (cellUid != uid) {
            cell = [cell initWithUser:CGRectZero delegate:self uid:uid];
            BBRtcVideoCanvas* canvas = [[BBRtcVideoCanvas alloc] init];
            canvas.view = [cell getVideoView];
            canvas.uid = uid;
            canvas.mirrorMode = BBRtcVideoMirrorModeAuto;
            canvas.renderMode = BBRtcVideoRenderModeHidden;
            if (uid == userId_) {
                [sharedEngine_ setupLocalVideo:canvas];
            }
            else {
                [sharedEngine_ setupRemoteVideo:canvas];
            }
        }
        [cell setHidden:NO];
    }
}

-(void) viewClean {
    allCellMap_.clear();
}

-(void) onMuteClick:(NSUInteger)uid mute:(BOOL)mute{
    [sharedEngine_ muteRemoteAudioStream:uid mute:mute];
}

-(void) onVolumeChange:(NSUInteger)uid volume:(int)volume{
    [sharedEngine_ adjustUserPlaybackSignalVolume:uid volume:volume];
}

-(void) setStatus:(NSString*) text{
    [_stateLabel setText:text];
}

-(void) onVideoStreamChange:(NSUInteger)uid type:(int)type{
    if(sharedEngine_){
        [sharedEngine_ setRemoteVideoStream:uid type:(BBRtcVideoStreamType)type];
    }
}

#pragma mark - Actions

- (IBAction)netSetting:(id)sender {
    [_networkLinkView show];
}

- (IBAction)hangUp:(id)sender {
    if(sharedEngine_){
        [self stopMixerMusic];
        [sharedEngine_ enableLocalVideo:NO];
        [sharedEngine_ leaveChannel:nil];
        [self viewClean];
        [self dismissViewControllerAnimated:YES completion:nil];
    }else{
        [self dismissViewControllerAnimated:YES completion:nil];
    }
    if ([self.vadTimer isValid]) {
        [self.vadTimer invalidate];
    }
    self.vadTimer = nil;
    [BBRtcEngineKit destroy];
}

- (IBAction)videoSwitch:(id)sender {
    videoOpen_ = !videoOpen_;
    if(!videoOpen_){
        [sharedEngine_ muteLocalVideoStream:YES];
        [_videoButton setTitle:@"video on" forState:UIControlStateNormal];
    }
    else{
        [sharedEngine_ muteLocalVideoStream:NO];
        [_videoButton setTitle:@"video off" forState:UIControlStateNormal];
    }
}

- (IBAction)cameraSwitch:(id)sender {
    if(videoOpen_)
        [sharedEngine_ switchCamera];
}

- (IBAction)voiceSwitch:(id)sender {
    voiceOpen_ = !voiceOpen_;
    if(!voiceOpen_){
        [sharedEngine_ muteLocalAudioStream:YES];
        [_voiceButton setTitle:@"voice on" forState:UIControlStateNormal];
    }
    else{
        [sharedEngine_ muteLocalAudioStream:NO];
        [_voiceButton setTitle:@"voice off" forState:UIControlStateNormal];
    }
}

- (IBAction)roleSwitch:(id)sender {
    isAnchor_ = !isAnchor_;
    if(!isAnchor_){
        [sharedEngine_ setClientRole:(BBRtcClientRole)2];
        [_roleSwitchBnt setTitle:@"up" forState:UIControlStateNormal];
    }
    else{
        [self addUserView:userId_];
        [sharedEngine_ setClientRole:(BBRtcClientRole)1];
        [sharedEngine_ enableLocalVideo:_videoEnabled];
        [_roleSwitchBnt setTitle:@"down" forState:UIControlStateNormal];
    }
    [_chorusRoleMenu selectItme:0];
}

- (IBAction)relayMedia:(id)sender {
    if(!relayMedia_){
        [self startRelayMedia];
    }
    else{
        [self stopRelayMedia];
    }
}

- (void) startRelayMedia{
    //提示框添加文本输入框
    UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"relay"
                                                                   message:@"please insert roomid"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* okAction = [UIAlertAction actionWithTitle:@"sure" style:UIAlertActionStyleDefault
                                                     handler:^(UIAlertAction * action) {
        for(UITextField *text in alert.textFields){
            if ([text.text length] == 0) {
                return;
            }
            NSString* name = text.text;
            BBRtcChannelMediaRelayConfiguration* configs = [[BBRtcChannelMediaRelayConfiguration alloc] init];
            BBRtcChannelMediaRelayInfo * info = [[BBRtcChannelMediaRelayInfo alloc] init];
            info.channelName = name;
            info.token = @"";
            info.uid = 0;
            [configs setDestinationInfo:info forChannelName:name];
            if([self->sharedEngine_ startChannelMediaRelay:configs] == 0){
                [self->_relayMediaButton setTitle:@"stop relay" forState:UIControlStateNormal];
                self->relayMedia_ = YES;
            }
        }
    }];
    UIAlertAction* cancelAction = [UIAlertAction actionWithTitle:@"cancel" style:UIAlertActionStyleCancel
                                                         handler:^(UIAlertAction * action) {
        
    }];
    [alert addTextFieldWithConfigurationHandler:^(UITextField *textField) {
        textField.placeholder = @"roomid";
        textField.secureTextEntry = YES;
    }];
    
    [alert addAction:okAction];
    [alert addAction:cancelAction];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void) stopRelayMedia{
    [_relayMediaButton setTitle:@"start relay" forState:UIControlStateNormal];
    [sharedEngine_ stopChannelMediaRelay];
    relayMedia_ = NO;
}

- (void)playoutSliderValueChanged:(id)sender {
    UISlider *slider = (UISlider *)sender;
    _playoutVolumeLabel.text = [NSString stringWithFormat:@"%d", (int)slider.value];
    [sharedEngine_ adjustPlaybackSignalVolume:(int)slider.value];
}

- (void)recordSliderValueChanged:(id)sender {
    UISlider *slider = (UISlider *)sender;
    _recordVolumeLabel.text = [NSString stringWithFormat:@"%d", (int)slider.value];
    [sharedEngine_ adjustRecordingSignalVolume:(int)slider.value];
}

- (void)musicVolumeSliderValueChanged:(id)sender {
    UISlider *slider = (UISlider *)sender;
    _musicVolumeLabel.text = [NSString stringWithFormat:@"%d", (int)slider.value];
    [sharedEngine_ adjustAudioMixingVolume:(int)slider.value];
}

- (IBAction)onMusicSelectClick:(id)sender {
    [self presentiTunesMediaPickerController];
}

- (IBAction)onMusicPauseClick:(id)sender {
    if(!musicPlay_)
        return;
    musicPause_ = !musicPause_;
    if (musicPause_) {
        [sharedEngine_ pauseAudioMixing];
        [_musicPauseButton setTitle:@"resume" forState:UIControlStateNormal];
    }
    else{
        [sharedEngine_ resumeAudioMixing];
        [_musicPauseButton setTitle:@"pause" forState:UIControlStateNormal];
    }
}

- (IBAction)onMusicPlayClick:(id)sender {
    NSString* filepath = _musicNameLabel.text;
    if (musicPlay_) {
        [self stopMixerMusic];
    }
    else{
        _musicFilePath = filepath;
        [self startMixerMusic];
    }
}

- (void)musicSliderValueChanged:(id)sender {
    if(!musicPlay_)
        return;
    UISlider *slider = (UISlider *)sender;
    int pos = (int)(musicTotalTimeMs_ * slider.value);
    _musicNowTimeLabel.text = [NSString stringWithFormat:@"%02d:%02d", pos/1000/60, pos/1000%60];
    [sharedEngine_ setAudioMixingPosition:pos];
}

//////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark -使用系统自带的控制器

- (void)presentiTunesMediaPickerController
{
    MPMediaPickerController *controller = [[MPMediaPickerController alloc] initWithMediaTypes:MPMediaTypeMusic | MPMediaTypeMovie | MPMediaTypeMusicVideo];
    //2.是否支持多选,默认为no
    controller.allowsPickingMultipleItems = NO;
    //在导航栏的上方添加一个提示文本
    controller.prompt = @"choose music";
    //3.设置代理（代理比较简单，只有两个方法，完成选取和取消选取）
    controller.delegate = self;
    //4.弹出媒体选择器
    [self presentViewController:controller animated:YES completion:nil];
}

#pragma mark -只获取iTunes中的数据，界面自定义
- (void)getiTuneLibrary
{
    // 1.创建媒体选择队列（从ipod库中读出音乐文件）
    MPMediaQuery *everything = [[MPMediaQuery alloc] init];
    // 2.创建读取条件(类似于对数据做一个筛选) Value：作用等同于MPMediaType枚举值
    MPMediaPropertyPredicate *albumNamePredicate =
    [MPMediaPropertyPredicate predicateWithValue:[NSNumber numberWithInt:MPMediaTypeMusic ] forProperty: MPMediaItemPropertyMediaType];
    //3.给队列添加读取条件
    [everything addFilterPredicate:albumNamePredicate];
    //4.从队列中获取符合条件的数组集合
    NSArray *itemsFromGenericQuery = [everything items];
    //5.便利解析数据
    for (MPMediaItem *song in itemsFromGenericQuery) {
        [self resolverMediaItem:song];
    }
}

#pragma mark -解析iTune音乐数据
- (void)resolverMediaItem:(MPMediaItem *)song{
    //歌名
    NSString *name = [song valueForProperty: MPMediaItemPropertyTitle];
    //歌曲路径
    NSURL *url = [song valueForProperty: MPMediaItemPropertyAssetURL];
    AVURLAsset *songAsset = [AVURLAsset URLAssetWithURL:url options:nil];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSArray *dirs = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectoryPath = [dirs objectAtIndex:0];
    AVAssetExportSession* exporter = [[AVAssetExportSession alloc]
                                      initWithAsset: songAsset
                                      presetName: AVAssetExportPresetAppleM4A];
    exporter.outputFileType = @"com.apple.m4a-audio";
    // 建立本地音乐文件
    NSString *filePath = [documentsDirectoryPath stringByAppendingPathComponent:@"LocationMusic"];
    if (![fileManager fileExistsAtPath:filePath]) {
        // 创建文件夹
        [fileManager createDirectoryAtPath:filePath withIntermediateDirectories:YES attributes:nil error:nil];
    }
    NSString *exportFile = [filePath stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.m4a",name]];
    if([fileManager fileExistsAtPath:exportFile]){
        _musicFilePath = exportFile;
        [self startMixerMusic];
        return;
    }
    NSError *error1;
    if([fileManager fileExistsAtPath:exportFile]) {
        [fileManager removeItemAtPath:exportFile error:&error1];
    }
    NSURL* exportURL = [NSURL fileURLWithPath:exportFile];
    exporter.outputURL = exportURL;
    __block __typeof(self)weakSelf = self;
    [exporter exportAsynchronouslyWithCompletionHandler:^(){
        if (exporter.status == AVAssetExportSessionStatusCompleted) {
            NSLog(@"\nsong name：%@ \n song path：%@ \n", name, exportFile);
            dispatch_async(dispatch_get_main_queue(), ^{
                weakSelf.musicFilePath = [NSString stringWithFormat:@"%@", exportFile];
                [weakSelf startMixerMusic];
            });
        } else {
            NSLog(@"AVAssetExportSessionStatusFail");
            
        }
    }];
}

- (BOOL) startMixerMusic{
    if(musicPlay_)
        [self stopMixerMusic];
    if([sharedEngine_ startAudioMixing:_musicFilePath loopback:NO replace:NO cycle:100] != 0){
        NSLog(@"startAudioMixing error...\n");
        return NO;
    }
    musicPlay_ = YES;
    musicPause_ = NO;
    _musicTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(timeAction:) userInfo:nil repeats:YES];
    [_musicPlayButton setTitle:@"stop" forState:UIControlStateNormal];
    [_musicPauseButton setTitle:@"pause" forState:UIControlStateNormal];
    _musicNameLabel.text = _musicFilePath;
    return YES;
}

- (void) stopMixerMusic{
    if(!musicPlay_)
        return;
    musicPlay_ = NO;
    musicPause_ = NO;
    if(_musicTimer){
        [_musicTimer invalidate];
        _musicTimer = nil;
    }
    [_musicPlayButton setTitle:@"play" forState:UIControlStateNormal];
    [_musicPauseButton setTitle:@"pause" forState:UIControlStateNormal];
    [_musicSilder setValue:0];
    _musicNowTimeLabel.text = @"00:00";
    [sharedEngine_ stopAudioMixing];
}

- (void)timeAction:(NSTimer *)sender {
    if(!musicPlay_ || musicTotalTimeMs_ == 0)
        return;
    int pos = [sharedEngine_ getAudioMixingCurrentPosition];
    [_musicSilder setValue: pos*1.0f/musicTotalTimeMs_];
    _musicNowTimeLabel.text = [NSString stringWithFormat:@"%02d:%02d", pos/1000/60, pos/1000%60];
}


- (UserViewCell*) getUserView:(NSInteger)uid {
    int index = 0;
    for (int i = 0; i < (int)userList_.size(); ++i) {
        if (userList_[i] == uid) {
            index = i;
            break;
        }
    }
    auto it = allCellMap_.begin();
    for(; it != allCellMap_.end(); ++it) {
        UserViewCell* cell = it->second;
        if(uid == [cell getUserId] && index == [cell getIndex]) {
            return (UserViewCell*)cell;
        }
    }
    return nil;
}

- (void) setRemoteAudioMuteState:(NSInteger)uid mute:(BOOL)mute{
    UserViewCell* view = [self getUserView:uid];
    if(view){
        [view setRemoteMute:mute];
    }
}

#pragma mark -MPMediaPickerControllerDelegate

- (void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection
{
    for (MPMediaItem *song in mediaItemCollection.items) {
        [self resolverMediaItem:song];
    }
    [mediaPicker dismissViewControllerAnimated:YES completion:nil];
}

- (void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker
{
    [mediaPicker dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark collectionView代理方法

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    return 1;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return userList_.size();
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    UserViewCell* cell = (UserViewCell *)[collectionView
                                          dequeueReusableCellWithReuseIdentifier:@"cellId"
                                          forIndexPath:indexPath];
    NSInteger index = indexPath.row;
    [cell setIndex:(int)index];
    allCellMap_[index] = cell;
    if (index + 1 == userList_.size()) {
        [self updateUserView];
    }
    return cell;
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath
{
    int width = VIDEO_VIEW_WIDTH;
    int height = (int)(4.f/3.f * width);
    return CGSizeMake(width, height);
}

- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section
{
    return UIEdgeInsetsMake(0, 10, 0, 10);
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section
{
    return 5;
}

- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section
{
    return 5;
}

- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath
{
    UICollectionReusableView *headerView = [collectionView dequeueReusableSupplementaryViewOfKind:UICollectionElementKindSectionHeader withReuseIdentifier:@"reusableView" forIndexPath:indexPath];
    headerView.backgroundColor =[UIColor blackColor];
    return headerView;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
}

- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath
{
}

#pragma mark -RtcSDK代理方法
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOccurWarning:(BBRtcWarningCode)warningCode{
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOccurError:(BBRtcErrorCode)errorCode{
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didApiCallExecute:(NSInteger)error api:(NSString * _Nonnull)api result:(NSString * _Nonnull)result{
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed{
    NSLog(@"Join channel ok");
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed{
    NSLog(@"Rejoin channel ok");
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didLeaveChannelWithStats:(BBRtcChannelStats * _Nonnull)stats{
    NSLog(@"Leave channel ok");
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didRegisteredLocalUser:(NSString * _Nonnull)userAccount withUid:(NSUInteger)uid{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didUpdatedUserInfo:(BBRtcUserInfo * _Nonnull)userInfo withUid:(NSUInteger)uid{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didClientRoleChanged:(BBRtcClientRole)oldRole newRole:(BBRtcClientRole)newRole{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed{
    [self addUserView:uid];
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOfflineOfUid:(NSUInteger)uid reason:(BBRtcUserOfflineReason)reason{
    [self removeUserView:uid];
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine connectionChangedToState:(BBRtcConnectionStateType)state reason:(BBRtcConnectionChangedReason)reason{
    switch(state){
        case BBRtcConnectionStateDisconnected:
        {
            switch (reason) {
                case BBRtcConnectionChangedInterrupted:
                    [self setStatus:@"disconnect, network error"];
                    break;
                case BBRtcConnectionChangedJoinFailed:
                    [self setStatus:@"disconnect, failed to join the room"];
                    break;
                case BBRtcConnectionChangedLeaveChannel:
                    [self setStatus:@"disconnect, leave room "];
                    break;
                case BBRtcConnectionChangedInvalidChannelName:
                    [self setStatus:@"disconnect, invalid roomid"];
                    break;
                case BBRtcConnectionChangedBannedByServer:
                    [self setStatus:@"disconnect, kicked out"];
                    break;
                case BBRtcConnectionChangedKeepAliveTimeout:
                    [self setStatus:@"disconnect, heartbeat timeout"];
                    break;
                default:
                    [self setStatus:@"disconnect"];
                    break;
            }
        }break;
        case BBRtcConnectionStateConnecting:
            switch (reason) {
                case BBRtcConnectionChangedJoinSuccess:
                    [self setStatus:@"connecting ice"];
                    break;
                default:
                    [self setStatus:@"connencting..."];
                    break;
            }
            break;
        case BBRtcConnectionStateConnected:
        {
            [self setStatus:@"join success"];
            break;
        }
        case BBRtcConnectionStateReconnecting:
            [self setStatus:@"connecting..."];
            break;
        case BBRtcConnectionStateFailed:
            [self setStatus:@"connect failed"];
            [sharedEngine_ leaveChannel:nil];
            break;
    }
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine networkTypeChangedToType:(BBRtcNetworkType)type{
    
}
- (void)rtcEngineConnectionDidLost:(BBRtcEngineKit * _Nonnull)engine{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine tokenPrivilegeWillExpire:(NSString *_Nonnull)token{
    
}
- (void)rtcEngineRequestToken:(BBRtcEngineKit * _Nonnull)engine{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<BBRtcAudioVolumeInfo *> * _Nonnull)speakers totalVolume:(NSInteger)totalVolume{
    for (BBRtcAudioVolumeInfo* info in speakers) {
        UserViewCell* view = [self getUserView:(int)info.uid];
        if(view){
            [view setRealTimeVolume:(int)info.volume];
        }
    }
    if(speakers.count && speakers[0].vad){
        [_vadStateView setBackgroundColor: [UIColor redColor]];
    }else{
        [_vadStateView setBackgroundColor: [UIColor whiteColor]];
    }
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine reportLocalAudioVolumeIndication:(BBRtcAudioVolumeInfo * _Nonnull)speaker {
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine activeSpeaker:(NSUInteger)speakerUid{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstLocalAudioFrame:(NSInteger)elapsed{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteAudioStateChangedOfUid:(NSUInteger)uid state:(BBRtcAudioRemoteState)state reason:(BBRtcAudioRemoteStateReason)reason elapsed:(NSInteger)elapsed{
    NSLog(@"remoteAudioStateChange uid:%tu, state:%tu, reason:%tu\n", uid, state, reason);
    switch(state){
        case BBRtcAudioRemoteStateStopped:
            if (reason == BBRtcAudioRemoteReasonLocalMuted) {
                UserViewCell* view = [self getUserView:uid];
                if(view){
                    [view setRealTimeVolume:0];
                }
            } else if(reason == BBRtcAudioRemoteReasonRemoteMuted){
                [self setRemoteAudioMuteState:uid mute:YES];
            }
            else if(reason == BBRtcAudioRemoteReasonRemoteOffline){
                [self setRemoteAudioMuteState:uid mute:NO];
            }
            break;
        case BBRtcAudioRemoteStateStarting:
            
            break;
        case BBRtcAudioRemoteStateDecoding:
            if (reason == BBRtcAudioRemoteReasonNetworkRecovery){
                
            }
            else if(reason == BBRtcAudioRemoteReasonLocalUnmuted){
                
            }
            else if(reason == BBRtcAudioRemoteReasonRemoteUnmuted){
                [self setRemoteAudioMuteState:uid mute:NO];
            }
            break;
        case BBRtcAudioRemoteStateFrozen:
            break;
        case BBRtcAudioRemoteStateFailed:
            break;
    }
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localAudioStateChange:(BBRtcAudioLocalState)state error:(BBRtcAudioLocalError)error{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didAudioRouteChanged:(BBRtcAudioOutputRouting)routing{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine reportRtcStats:(BBRtcChannelStats * _Nonnull)stats{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine lastmileQuality:(BBRtcNetworkQuality)quality{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine networkQuality:(NSUInteger)uid txQuality:(BBRtcNetworkQuality)txQuality rxQuality:(BBRtcNetworkQuality)rxQuality{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localAudioStats:(BBRtcLocalAudioStats * _Nonnull)stats{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteAudioStats:(BBRtcRemoteAudioStats * _Nonnull)stats{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstRemoteAudioFrameOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstRemoteAudioFrameDecodedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSUInteger)uid{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine audioTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didMicrophoneEnabled:(BOOL)enabled{
    
}
- (void)rtcEngineConnectionDidInterrupted:(BBRtcEngineKit * _Nonnull)engine{
    
}
- (void)rtcEngineConnectionDidBanned:(BBRtcEngineKit * _Nonnull)engine{
    
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine audioQualityOfUid:(NSUInteger)uid quality:(BBRtcNetworkQuality)quality delay:(NSUInteger)delay lost:(NSUInteger)lost{
    
}

- (void)rtcEngineLocalAudioMixingDidFinish:(BBRtcEngineKit * _Nonnull)engine{
    [self stopMixerMusic];
    [self setStatus:@"play music end"];
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localAudioMixingStateDidChanged:(BBRtcAudioMixingStateCode)state errorCode:(BBRtcAudioMixingReasonCode)errorCode{
    switch (state) {
        case BBRtcAudioMixingStatePlaying:
            [self setStatus:@"play music suc"];
            musicTotalTimeMs_ = [sharedEngine_ getAudioMixingDuration];
            _musicTotalTimeLabel.text = [NSString stringWithFormat:@"%02d:%02d", musicTotalTimeMs_/1000/60, musicTotalTimeMs_/1000%60];
            break;
        case BBRtcAudioMixingStatePaused:
            [self setStatus:@"play music pause"];
            break;
        case BBRtcAudioMixingStateStopped:
            [self setStatus:@"play music end"];
            break;
        case BBRtcAudioMixingStateFailed:
            switch (errorCode) {
                case BBRtcAudioMixingReasonCanNotOpen:
                    [self setStatus:@"music open failed"];
                    [self stopMixerMusic];
                    break;
                case BBRtcAudioMixingReasonTooFrequentCall:
                    [self setStatus:@"call too frequency"];
                    break;
                case BBRtcAudioMixingReasonInterruptedEOF:
                    [self setStatus:@"music play interruption"];
                    [self stopMixerMusic];
                    break;
                default:
                    break;
            }
            break;
    }
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine channelMediaRelayStateDidChange:(BBRtcChannelMediaRelayState)state error:(BBRtcChannelMediaRelayError)error{
    NSLog(@"channelMediaRelayStateDidChange state:%td, error:%td\n", state, error);
    if (state == BBRtcChannelMediaRelayStateRunning && error == BBRtcChannelMediaRelayErrorNone) {
        [self setStatus:@"relay suc"];
    }
    else if(state == BBRtcChannelMediaRelayStateFailure){
        [self setStatus:[NSString stringWithFormat:@"relay failed, code:%td", error]];
        [self stopRelayMedia];
    }
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didReceiveChannelMediaRelayEvent:(BBRtcChannelMediaRelayEvent)event{
    NSLog(@"didReceiveChannelMediaRelayEvent event:%td\n", event);
    if (event == BBRtcChannelMediaRelayEventUpdateDestinationChannelIsNil) {
        [self setStatus:@"relay failed by room not exit"];
        [self stopRelayMedia];
    }
    else{
        [self setStatus:[NSString stringWithFormat:@"relay event, event:%td", event]];
    }
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed{
    NSLog(@"firstLocalVideoFrameWithSize w:%f, h:%f\n", size.width, size.height);
}
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstRemoteVideoFrameOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed{
    NSLog(@"firstRemoteVideoFrameOfUid:%td, w:%f, h:%f\n", uid, size.width, size.height);
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(BBRtcVideoRemoteState)state reason:(BBRtcVideoRemoteStateReason)reason elapsed:(NSInteger)elapsed{
    NSLog(@"remoteVideoStateChangedOfUid:%td, state:%td, reason:%td\n", uid, state, reason);
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine receiveStreamMessageFromUid:(NSUInteger)uid streamId:(NSInteger)streamId data:(NSData * _Nonnull)data {
    NSString* text = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
    NSLog(@"receiveStreamMessageFromUid uid:%td text:%@", uid, text);
}

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOccurStreamMessageErrorFromUid:(NSUInteger)uid streamId:(NSInteger)streamId error:(NSInteger)error missed:(NSInteger)missed cached:(NSInteger)cached {
    NSLog(@"didOccurStreamMessageErrorFromUid uid:%td\n", uid);
}


- (void)rtcEngineDidAudioEffectFinish:(BBRtcEngineKit * _Nonnull)engine soundId:(NSInteger)soundId{
    NSLog(@"rtcEngineDidAudioEffectFinish soundId:%td\n", soundId);
}

- (void)rtcEngine:(BBRtcEngineKit* _Nonnull)engine didAudioSubscribeStateChange:(NSString* _Nonnull)channel withUid:(NSUInteger)uid oldState:(BBRtcStreamSubscribeState)oldState newState:(BBRtcStreamSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState{
    NSLog(@"didAudioSubscribeStateChange uid:%td, oldState:%td, newState:%td, tm:%td\n", uid, oldState, newState, elapseSinceLastState);
}

- (void)rtcEngine:(BBRtcEngineKit* _Nonnull)engine didVideoSubscribeStateChange:(NSString* _Nonnull)channel withUid:(NSUInteger)uid oldState:(BBRtcStreamSubscribeState)oldState newState:(BBRtcStreamSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState{
    NSLog(@"didVideoSubscribeStateChange uid:%td, oldState:%td, newState:%td, tm:%td\n", uid, oldState, newState, elapseSinceLastState);
}

- (void)rtcEngineChorusStart:(BBRtcEngineKit * _Nonnull)engine{
    [self setStatus:@"chorus start"];
}
- (void)rtcEngineChorusStop:(BBRtcEngineKit * _Nonnull)engine{
    [self setStatus:@"chorus stop"];
}
#pragma mark - LMJDropdownMenu DataSource
- (NSUInteger)numberOfOptionsInDropdownMenu:(LMJDropdownMenu *)menu{
    if (_audioProfileMenu == menu) {
        return audioOptionTitles_.count;
    } else if (_chorusRoleMenu == menu) {
        return chorusRoleTitles_.count;
    }
    return 0;
}
- (CGFloat)dropdownMenu:(LMJDropdownMenu *)menu heightForOptionAtIndex:(NSUInteger)index{
    return 30;
}
- (NSString *)dropdownMenu:(LMJDropdownMenu *)menu titleForOptionAtIndex:(NSUInteger)index{
    if (_audioProfileMenu == menu) {
        return audioOptionTitles_[index];
    }  else if (_chorusRoleMenu == menu) {
        return chorusRoleTitles_[index];
    }
    return @"";
}
- (UIImage *)dropdownMenu:(LMJDropdownMenu *)menu iconForOptionAtIndex:(NSUInteger)index{
    return nil;
}
#pragma mark - LMJDropdownMenu Delegate
- (void)dropdownMenu:(LMJDropdownMenu *)menu didSelectOptionAtIndex:(NSUInteger)index optionTitle:(NSString *)title{
    if (_audioProfileMenu == menu) {
        if (sharedEngine_) {
            _audioType = (int)index;
            [sharedEngine_ setAudioProfile:(BBRtcAudioProfile)_audioType scenario:(BBRtcAudioScenario)_scenarioType];
        }
    } else if (_chorusRoleMenu == menu) {
        if (sharedEngine_) {
            [sharedEngine_ setChorusRole:(BBRtcChorusRole)index];
        }
    }
}

- (BBRtcAudioFramePosition)getObservedAudioFramePosition{
    return BBRtcAudioFramePositionRecord;
}

- (BBRtcAudioParam * _Nonnull)getMixedAudioParams {
    return nil;
}


- (BBRtcAudioParam * _Nonnull)getPlaybackAudioParams {
    return nil;
}


- (BBRtcAudioParam * _Nonnull)getRecordAudioParams {
    return nil;
}


- (BOOL)isMultipleChannelFrameWanted {
    return NO;
}


- (BOOL)onMixedAudioFrame:(BBRtcAudioFrame * _Nonnull)frame {
    return NO;
}


- (BOOL)onPlaybackAudioFrame:(BBRtcAudioFrame * _Nonnull)frame {
    return NO;
}


- (BOOL)onPlaybackAudioFrameBeforeMixing:(BBRtcAudioFrame * _Nonnull)frame uid:(NSUInteger)uid {
    return NO;
}


- (BOOL)onPlaybackAudioFrameBeforeMixingEx:(BBRtcAudioFrame * _Nonnull)frame channelId:(NSString * _Nonnull)channelId uid:(NSUInteger)uid {
    return NO;
}


- (BOOL)onRecordAudioFrame:(BBRtcAudioFrame * _Nonnull)frame {
    return NO;
}


- (BBRtcVideoFrameType)getVideoFormatPreference {
    return BBRtcVideoFrameTypeYUV420;
}

- (BBRtcVideoFramePosition)getObservedFramePosition {
    return BBRtcVideoFramePositionPostCapture;
}

- (BOOL)onRenderVideoFrameEx:(BBRtcVideoFrame*)frame forUid:(unsigned int)uid inChannel:(NSString*)channelId {
    return YES;
}

- (BOOL)getMirrorApplied {
    return NO;
}


- (BOOL)getRotationApplied {
    return NO;
}


- (BOOL)onCaptureVideoFrame:(BBRtcVideoFrame *)frame {
    return NO;
}


- (BOOL)onPreEncodeVideoFrame:(BBRtcVideoFrame *)frame {
    return NO;
}


- (BOOL)onRenderVideoFrame:(BBRtcVideoFrame *)frame forUid:(unsigned int)uid {
    return NO;
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

- (void)encodeWithCoder:(nonnull NSCoder *)coder {
}

- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection {
}

- (void)preferredContentSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container {
}

- (CGSize)sizeForChildContentContainer:(nonnull id<UIContentContainer>)container withParentContainerSize:(CGSize)parentSize {
    return parentSize;
}

- (void)systemLayoutFittingSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container {
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator {
}

- (void)willTransitionToTraitCollection:(nonnull UITraitCollection *)newCollection withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator{
}

- (void)didUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context withAnimationCoordinator:(nonnull UIFocusAnimationCoordinator *)coordinator {
}

- (void)setNeedsFocusUpdate {
}

- (BOOL)shouldUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context {
    return NO;;
}

- (void)updateFocusIfNeeded {
}

@end
