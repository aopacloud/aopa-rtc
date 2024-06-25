//
//  NADLoginController.m
//  sources
//
//  Created by ; on 2020/4/13.
//
#import <AVFoundation/AVFoundation.h>
#import "NADLoginController.h"
#import "NADViewController.h"
#import "FUViewController.h"
#import "LMJDropdownMenu.h"
#import "NADAppDelegate.h"
#import "NADCheckBox.h"

struct LoginConfig{
  char roomId[128];
  char customServer[128];
  int audioProfile;
  int audioScenario;
  int videoProfile;
  int role;
  int serverIndex;
  int appIndex;
  bool quic;
  bool speaker;
  bool simulcast;
  bool videoEnabled;
  bool localVideoSource;
  bool detachStream;
};

@interface MyUITextField : UITextField
- (CGRect)textRectForBounds:(CGRect)bounds;
- (CGRect)editingRectForBounds:(CGRect)bounds;
@end
@implementation MyUITextField
- (CGRect)textRectForBounds:(CGRect)bounds
{
    return CGRectInset(bounds, 10, 0);
}

- (CGRect)editingRectForBounds:(CGRect)bounds
{
    return CGRectInset(bounds, 10, 0);
}
@end

@interface NADLoginController ()<LMJDropdownMenuDataSource,LMJDropdownMenuDelegate>

@property(nonatomic) UILabel* roomIdLabel;
@property(nonatomic) MyUITextField* roomIdText;
@property(nonatomic) UILabel *  userIdLabel;
@property(nonatomic) MyUITextField* userIdText;
@property(nonatomic) UIButton* joinButton;
@property(nonatomic) UIButton* singleButton;
@property(nonatomic) UILabel* audioProfileLabel;
@property(nonatomic) LMJDropdownMenu* audioProfileMenu;
@property(nonatomic) UILabel* audioScenarioLabel;
@property(nonatomic) LMJDropdownMenu* audioScenarioMenu;
@property(nonatomic) UILabel* videoProfileLabel;
@property(nonatomic) LMJDropdownMenu* videoProfileMenu;
@property(nonatomic) UILabel* userRoleLabel;
@property(nonatomic) LMJDropdownMenu* userRoleMenu;
@property(nonatomic) UILabel* serverTypeLabel;
@property(nonatomic) LMJDropdownMenu* serverTypeMenu;
@property(nonatomic) UILabel* appIdLabel;
@property(nonatomic) LMJDropdownMenu* appIdMenu;
@property(nonatomic) UILabel* serverAddrLabel;
@property(nonatomic) MyUITextField* serverAddrText;
@property(nonatomic) NADCheckBox* quicCheckBox;
@property(nonatomic) NADCheckBox* videoCheckBox;
@property(nonatomic) NADCheckBox* videoSourceCheckBox;
@property(nonatomic) NADCheckBox* speakerCheckBox;
@property(nonatomic) NADCheckBox* simulcastStreamCheckBox;
@property(nonatomic) NADCheckBox* detachStreamCheckBox;
@end

@implementation NADLoginController{
    UIView *_view;
    NSArray * _appIdList;
    NSArray * _appIds;
    NSArray * _audioOptionTitles;
    NSArray * _userOptionTitles;
    NSArray * _serverOptionTitles;
    NSArray * _scenarioOptionTitles;
    NSArray * _videoProfileOptionTitles;
    int _userId;
    NSString* _token;
    BOOL _singleJoin;
    struct LoginConfig _config;
}



- (void)viewDidLoad {
    [super viewDidLoad];
    _appIds = [[NSArray alloc] initWithObjects:
                      @"6MHg9hZqMMcKjNyiauSyU8H5b3eTr4qM",
                      nil];
    
    _appIdList = [[NSArray alloc] initWithObjects:
                  @"PT",
                  nil];
    _audioOptionTitles = [[NSArray alloc]initWithObjects:@"default", @"speechmono",
                          @"musicmono", @"musicstero", @"musicmonoHighqulity", @"musicSteroHighQuality", nil];
    _userOptionTitles = [[NSArray alloc]initWithObjects:@"broadcaster", @"audience", nil];
    _serverOptionTitles = [[NSArray alloc]initWithObjects:@"Aopa formal env", nil];
    _scenarioOptionTitles = [[NSArray alloc]initWithObjects:@"ShowRoom", @"GameStreaming", @"Chorus", nil];
    _videoProfileOptionTitles = [[NSArray alloc]initWithObjects:@"360x640", @"480x640", @"540x960", @"720x1280", @"1080x1920", nil];
    _userId = arc4random() % 100000;
    NSString* roomId = @"room888";
    _view = [[UIView alloc] initWithFrame:CGRectZero];
    [_view setBackgroundColor: [UIColor whiteColor] ];
    
    _roomIdLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _roomIdLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _roomIdLabel.font = [UIFont systemFontOfSize:13];
    _roomIdLabel.textColor = [UIColor blackColor];
    [_roomIdLabel setText:@"roomid"];
    [_view addSubview:_roomIdLabel];

    _roomIdText = [[MyUITextField alloc] initWithFrame:CGRectZero];
    _roomIdText.translatesAutoresizingMaskIntoConstraints = NO;
    _roomIdText.font = [UIFont systemFontOfSize:13];
    _roomIdText.text = roomId;
    _roomIdText.textColor = [UIColor blackColor];
    [_roomIdText textRectForBounds:CGRectMake(2, 0, 0, 0)];
    [_roomIdText setBackgroundColor: [UIColor whiteColor] ];
    [_roomIdText setTintColor:[UIColor blackColor]];
    _roomIdText.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _roomIdText.layer.borderWidth  = 1;
    _roomIdText.layer.cornerRadius = 5;
    [_view addSubview:_roomIdText];
    
    _userIdLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _userIdLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _userIdLabel.font = [UIFont systemFontOfSize:13];
    _userIdLabel.textColor = [UIColor blackColor];
    [_userIdLabel setText:@"userID"];
    [_view addSubview:_userIdLabel];
       
    _userIdText = [[MyUITextField alloc] initWithFrame:CGRectZero];
    _userIdText.translatesAutoresizingMaskIntoConstraints = NO;
    _userIdText.font = [UIFont systemFontOfSize:13];
    _userIdText.text = [NSString stringWithFormat:@"%d", _userId];
    _userIdText.textColor = [UIColor blackColor];
    [_userIdText textRectForBounds:CGRectMake(2, 0, 0, 0)];
    [_userIdText setBackgroundColor: [UIColor whiteColor] ];
    [_userIdText setTintColor:[UIColor blackColor]];
    _userIdText.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _userIdText.layer.borderWidth  = 1;
    _userIdText.layer.cornerRadius = 5;
    [_view addSubview:_userIdText];

    _serverAddrLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _serverAddrLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _serverAddrLabel.font = [UIFont systemFontOfSize:13];
    _serverAddrLabel.textColor = [UIColor blackColor];
    [_serverAddrLabel setText:@"self define ip"];
    [_view addSubview:_serverAddrLabel];

    _serverAddrText = [[MyUITextField alloc] initWithFrame:CGRectZero];
    _serverAddrText.translatesAutoresizingMaskIntoConstraints = NO;
    _serverAddrText.font = [UIFont systemFontOfSize:13];
    _serverAddrText.text = @"172.19.45.93";
    _serverAddrText.textColor = [UIColor blackColor];
    [_serverAddrText textRectForBounds:CGRectMake(2, 0, 0, 0)];
    [_serverAddrText setBackgroundColor: [UIColor whiteColor] ];
    [_serverAddrText setTintColor:[UIColor blackColor]];
    _serverAddrText.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _serverAddrText.layer.borderWidth  = 1;
    _serverAddrText.layer.cornerRadius = 5;
    [_view addSubview:_serverAddrText];

    _joinButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _joinButton.translatesAutoresizingMaskIntoConstraints = NO;
    _joinButton.titleLabel.font = [UIFont systemFontOfSize:15];
    [_joinButton.layer setMasksToBounds:YES];
    [_joinButton.layer setCornerRadius:5.0];
    [_joinButton setTitle:@"multi vudei" forState:UIControlStateNormal];
    [_joinButton setTintColor:[UIColor whiteColor]];
    [_joinButton setBackgroundColor: [UIColor colorWithRed:0.1 green:0.1 blue:0.1 alpha:1.0]]; 
    [_joinButton addTarget:self action:@selector(join:) forControlEvents:UIControlEventTouchUpInside];
    [_view addSubview:_joinButton];

    _singleButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _singleButton.translatesAutoresizingMaskIntoConstraints = NO;
    _singleButton.titleLabel.font = [UIFont systemFontOfSize:15];
    [_singleButton.layer setMasksToBounds:YES];
    [_singleButton.layer setCornerRadius:5.0];
    [_singleButton setTitle:@"single video" forState:UIControlStateNormal];
    [_singleButton setTintColor:[UIColor whiteColor]];
    [_singleButton setBackgroundColor: [UIColor colorWithRed:0.1 green:0.1 blue:0.1 alpha:1.0]];
    [_singleButton addTarget:self action:@selector(joinSingle:) forControlEvents:UIControlEventTouchUpInside];
    [_view addSubview:_singleButton];

    _quicCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"QUIC"] columns:1];
    _quicCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _quicCheckBox.isMulti = YES;
    _quicCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_quicCheckBox setItemSelected:NO index:0];
    [_quicCheckBox setFrame:CGRectMake(0, 0, 80, 40)];
    [_quicCheckBox setNormalImage:[UIImage imageNamed:@"icon_check_n"]];
    [_quicCheckBox setSelectedImage:[UIImage imageNamed:@"icon_check_s"]];
    [_view addSubview:_quicCheckBox];

    _videoCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"open video"] columns:1];
    _videoCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _videoCheckBox.isMulti = YES;
    _videoCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_videoCheckBox setItemSelected:NO index:0];
    [_videoCheckBox setFrame:CGRectMake(0, 0, 80, 40)];
    [_videoCheckBox setNormalImage:[UIImage imageNamed:@"icon_check_n"]];
    [_videoCheckBox setSelectedImage:[UIImage imageNamed:@"icon_check_s"]];
    [_view addSubview:_videoCheckBox];

    _videoSourceCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"locvsource"] columns:1];
    _videoSourceCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _videoSourceCheckBox.isMulti = YES;
    _videoSourceCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_videoSourceCheckBox setItemSelected:NO index:0];
    [_videoSourceCheckBox setFrame:CGRectMake(0, 0, 80, 40)];
    [_videoSourceCheckBox setNormalImage:[UIImage imageNamed:@"icon_check_n"]];
    [_videoSourceCheckBox setSelectedImage:[UIImage imageNamed:@"icon_check_s"]];
    [_view addSubview:_videoSourceCheckBox];

    _speakerCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"speaker"] columns:1];
    _speakerCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _speakerCheckBox.isMulti = YES;
    _speakerCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_speakerCheckBox setFrame:CGRectMake(0, 0, 80, 40)];
    [_speakerCheckBox setNormalImage:[UIImage imageNamed:@"icon_check_n"]];
    [_speakerCheckBox setSelectedImage:[UIImage imageNamed:@"icon_check_s"]];
    [_view addSubview:_speakerCheckBox];

    _simulcastStreamCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"simucast"] columns:1];
    _simulcastStreamCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _simulcastStreamCheckBox.isMulti = YES;
    _simulcastStreamCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_simulcastStreamCheckBox setItemSelected:NO index:0];
    [_simulcastStreamCheckBox setFrame:CGRectMake(0, 0, 80, 40)];
    [_simulcastStreamCheckBox setNormalImage:[UIImage imageNamed:@"icon_check_n"]];
    [_simulcastStreamCheckBox setSelectedImage:[UIImage imageNamed:@"icon_check_s"]];
    [_view addSubview:_simulcastStreamCheckBox];

    _detachStreamCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"stream detach"] columns:1];
    _detachStreamCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _detachStreamCheckBox.isMulti = YES;
    _detachStreamCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_detachStreamCheckBox setItemSelected:NO index:0];
    [_detachStreamCheckBox setFrame:CGRectMake(0, 0, 120, 40)];
    [_detachStreamCheckBox setNormalImage:[UIImage imageNamed:@"icon_check_n"]];
    [_detachStreamCheckBox setSelectedImage:[UIImage imageNamed:@"icon_check_s"]];
    [_view addSubview:_detachStreamCheckBox];
    

    _serverTypeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _serverTypeLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _serverTypeLabel.font = [UIFont systemFontOfSize:13];
    _serverTypeLabel.textColor = [UIColor blackColor];
    [_serverTypeLabel setText:@"server"];
    [_view addSubview:_serverTypeLabel];
    
    _serverTypeMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_serverTypeMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _serverTypeMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _serverTypeMenu.dataSource = self;
    _serverTypeMenu.delegate   = self;
    _serverTypeMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _serverTypeMenu.layer.borderWidth  = 1;
    _serverTypeMenu.layer.cornerRadius = 5;

    
    _serverTypeMenu.title           = @"aopa formal env";
    _serverTypeMenu.titleBgColor    = [UIColor colorWithRed:255/255.f green:255/255.f blue:255/255.f alpha:1];
    _serverTypeMenu.titleFont       = [UIFont systemFontOfSize:13];
    _serverTypeMenu.titleColor      = [UIColor blackColor];
    _serverTypeMenu.titleAlignment  = NSTextAlignmentLeft;
    _serverTypeMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 8, 0, 0);
    
    _appIdLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _appIdLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _appIdLabel.font = [UIFont systemFontOfSize:13];
    _appIdLabel.textColor = [UIColor blackColor];
    [_appIdLabel setText:@"APP ID"];
    [_view addSubview:_appIdLabel];
        
    _appIdMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_appIdMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _appIdMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _appIdMenu.dataSource = self;
    _appIdMenu.delegate   = self;
    _appIdMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _appIdMenu.layer.borderWidth  = 1;
    _appIdMenu.layer.cornerRadius = 5;

    _appIdMenu.title           = _appIdList[0];
    _appIdMenu.titleBgColor    = [UIColor colorWithRed:255/255.f green:255/255.f blue:255/255.f alpha:1];
    _appIdMenu.titleFont       = [UIFont systemFontOfSize:13];
    _appIdMenu.titleColor      = [UIColor blackColor];
    _appIdMenu.titleAlignment  = NSTextAlignmentLeft;
    _appIdMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 8, 0, 0);

    _userRoleLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _userRoleLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _userRoleLabel.font = [UIFont systemFontOfSize:13];
    _userRoleLabel.textColor = [UIColor blackColor];
    [_userRoleLabel setText:@"role"];
    [_view addSubview:_userRoleLabel];
    
    _userRoleMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_userRoleMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _userRoleMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _userRoleMenu.dataSource = self;
    _userRoleMenu.delegate   = self;
    _userRoleMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _userRoleMenu.layer.borderWidth  = 1;
    _userRoleMenu.layer.cornerRadius = 5;
    
    _userRoleMenu.title           = @"broadcaster";
    _userRoleMenu.titleBgColor    = [UIColor colorWithRed:255/255.f green:255/255.f blue:255/255.f alpha:1];
    _userRoleMenu.titleFont       = [UIFont systemFontOfSize:13];
    _userRoleMenu.titleColor      = [UIColor blackColor];
    _userRoleMenu.titleAlignment  = NSTextAlignmentLeft;
    _userRoleMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 8, 0, 0);
    
    _audioProfileLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _audioProfileLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _audioProfileLabel.font = [UIFont systemFontOfSize:13];
    _audioProfileLabel.textColor = [UIColor blackColor];
    [_audioProfileLabel setText:@"audioquality"];
    [_view addSubview:_audioProfileLabel];
    
    _audioProfileMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_audioProfileMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _audioProfileMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _audioProfileMenu.dataSource = self;
    _audioProfileMenu.delegate   = self;
    _audioProfileMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _audioProfileMenu.layer.borderWidth  = 1;
    _audioProfileMenu.layer.cornerRadius = 5;

    _audioProfileMenu.title           = @"music stero";
    _audioProfileMenu.titleBgColor    = [UIColor colorWithRed:255/255.f green:255/255.f blue:255/255.f alpha:1];
    _audioProfileMenu.titleFont       = [UIFont systemFontOfSize:13];
    _audioProfileMenu.titleColor      = [UIColor blackColor];
    _audioProfileMenu.titleAlignment  = NSTextAlignmentLeft;
    _audioProfileMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 8, 0, 0);
    
    _audioScenarioLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _audioScenarioLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _audioScenarioLabel.font = [UIFont systemFontOfSize:13];
    _audioScenarioLabel.textColor = [UIColor blackColor];
    [_audioScenarioLabel setText:@"scene"];
    [_view addSubview:_audioScenarioLabel];
    
    _audioScenarioMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_audioScenarioMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _audioScenarioMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _audioScenarioMenu.dataSource = self;
    _audioScenarioMenu.delegate   = self;
    _audioScenarioMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _audioScenarioMenu.layer.borderWidth  = 1;
    _audioScenarioMenu.layer.cornerRadius = 5;
    
    _audioScenarioMenu.title           = @"GameStreaming";
    _audioScenarioMenu.titleBgColor    = [UIColor colorWithRed:255/255.f green:255/255.f blue:255/255.f alpha:1];
    _audioScenarioMenu.titleFont       = [UIFont systemFontOfSize:13];
    _audioScenarioMenu.titleColor      = [UIColor blackColor];
    _audioScenarioMenu.titleAlignment  = NSTextAlignmentLeft;
    _audioScenarioMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 8, 0, 0);

   
    _videoProfileLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _videoProfileLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _videoProfileLabel.font = [UIFont systemFontOfSize:13];
    _videoProfileLabel.textColor = [UIColor blackColor];
    [_videoProfileLabel setText:@"resolution"];
    [_view addSubview:_videoProfileLabel];
    
    _videoProfileMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectZero];
    [_videoProfileMenu setFrame:CGRectMake(20, 80, 150, 32)];
    _videoProfileMenu.translatesAutoresizingMaskIntoConstraints = NO;
    _videoProfileMenu.dataSource = self;
    _videoProfileMenu.delegate   = self;
    _videoProfileMenu.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _videoProfileMenu.layer.borderWidth  = 1;
    _videoProfileMenu.layer.cornerRadius = 5;

    _videoProfileMenu.title           = @"480x640";
    _videoProfileMenu.titleBgColor    = [UIColor colorWithRed:255/255.f green:255/255.f blue:255/255.f alpha:1];
    _videoProfileMenu.titleFont       = [UIFont systemFontOfSize:13];
    _videoProfileMenu.titleColor      = [UIColor blackColor];
    _videoProfileMenu.titleAlignment  = NSTextAlignmentLeft;
    _videoProfileMenu.titleEdgeInsets = UIEdgeInsetsMake(3, 8, 0, 0);



    [_view addSubview:_serverTypeMenu];
    [_view addSubview:_appIdMenu];
    [_view addSubview:_userRoleMenu];
    [_view addSubview:_videoProfileMenu];
    [_view addSubview:_audioScenarioMenu];
    [_view addSubview:_audioProfileMenu];
    

    const int verticalInterval = 10;
    
    UILayoutGuide *margin = _view.layoutMarginsGuide;
    [_roomIdLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_roomIdLabel.centerYAnchor constraintEqualToAnchor:margin.centerYAnchor constant:-300.0].active = YES;
    [_roomIdLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_roomIdLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_roomIdText.leftAnchor constraintEqualToAnchor:_roomIdLabel.layoutMarginsGuide.rightAnchor ].active = YES;
    [_roomIdText.centerYAnchor constraintEqualToAnchor:margin.centerYAnchor constant:-300.0].active = YES;
    [_roomIdText.rightAnchor constraintEqualToAnchor:margin.rightAnchor constant:-20.0].active = YES;
    [_roomIdText.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_userIdLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_userIdLabel.topAnchor constraintEqualToAnchor:_roomIdLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_userIdLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_userIdLabel.heightAnchor constraintEqualToConstant:32].active = YES;
       
    [_userIdText.leftAnchor constraintEqualToAnchor:_roomIdText.leftAnchor].active = YES;
    [_userIdText.topAnchor constraintEqualToAnchor:_userIdLabel.topAnchor].active = YES;
    [_userIdText.rightAnchor constraintEqualToAnchor:_roomIdText.rightAnchor].active = YES;
    [_userIdText.heightAnchor constraintEqualToConstant:32].active = YES;

    [_audioProfileLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_audioProfileLabel.topAnchor constraintEqualToAnchor:_userIdLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_audioProfileLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_audioProfileLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioProfileMenu.leftAnchor constraintEqualToAnchor:_userIdText.leftAnchor].active = YES;
    [_audioProfileMenu.topAnchor constraintEqualToAnchor:_audioProfileLabel.topAnchor].active = YES;
    [_audioProfileMenu.rightAnchor constraintEqualToAnchor:_userIdText.rightAnchor].active = YES;
    [_audioProfileMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioScenarioLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_audioScenarioLabel.topAnchor constraintEqualToAnchor:_audioProfileLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_audioScenarioLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_audioScenarioLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioScenarioMenu.leftAnchor constraintEqualToAnchor:_userIdText.leftAnchor].active = YES;
    [_audioScenarioMenu.topAnchor constraintEqualToAnchor:_audioScenarioLabel.topAnchor].active = YES;
    [_audioScenarioMenu.rightAnchor constraintEqualToAnchor:_userIdText.rightAnchor].active = YES;
    [_audioScenarioMenu.heightAnchor constraintEqualToConstant:32].active = YES;

     
    [_videoProfileLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_videoProfileLabel.topAnchor constraintEqualToAnchor:_audioScenarioLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_videoProfileLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_videoProfileLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_videoProfileMenu.leftAnchor constraintEqualToAnchor:_userIdText.leftAnchor].active = YES;
    [_videoProfileMenu.topAnchor constraintEqualToAnchor:_videoProfileLabel.topAnchor].active = YES;
    [_videoProfileMenu.rightAnchor constraintEqualToAnchor:_userIdText.rightAnchor].active = YES;
    [_videoProfileMenu.heightAnchor constraintEqualToConstant:32].active = YES;

    
    [_userRoleLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_userRoleLabel.topAnchor constraintEqualToAnchor:_videoProfileLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_userRoleLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_userRoleLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_userRoleMenu.leftAnchor constraintEqualToAnchor:_roomIdText.leftAnchor].active = YES;
    [_userRoleMenu.topAnchor constraintEqualToAnchor:_userRoleLabel.topAnchor].active = YES;
    [_userRoleMenu.rightAnchor constraintEqualToAnchor:_roomIdText.rightAnchor].active = YES;
    [_userRoleMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_appIdLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_appIdLabel.topAnchor constraintEqualToAnchor:_userRoleLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_appIdLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_appIdLabel.heightAnchor constraintEqualToConstant:32].active = YES;
       
    [_appIdMenu.leftAnchor constraintEqualToAnchor:_roomIdText.leftAnchor].active = YES;
    [_appIdMenu.topAnchor constraintEqualToAnchor:_appIdLabel.topAnchor].active = YES;
    [_appIdMenu.rightAnchor constraintEqualToAnchor:_roomIdText.rightAnchor].active = YES;
    [_appIdMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_serverTypeLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_serverTypeLabel.topAnchor constraintEqualToAnchor:_appIdLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_serverTypeLabel.widthAnchor constraintEqualToConstant:60].active = YES;
    [_serverTypeLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_serverTypeMenu.leftAnchor constraintEqualToAnchor:_roomIdText.leftAnchor].active = YES;
    [_serverTypeMenu.topAnchor constraintEqualToAnchor:_serverTypeLabel.topAnchor].active = YES;
    [_serverTypeMenu.rightAnchor constraintEqualToAnchor:_roomIdText.rightAnchor].active = YES;
    [_serverTypeMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_serverAddrLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_serverAddrLabel.topAnchor constraintEqualToAnchor:_serverTypeLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_serverAddrLabel.widthAnchor constraintEqualToConstant:70].active = YES;
    [_serverAddrLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_serverAddrText.leftAnchor constraintEqualToAnchor:_serverAddrLabel.rightAnchor constant:10.0].active = YES;
    [_serverAddrText.topAnchor constraintEqualToAnchor:_serverAddrLabel.topAnchor].active = YES;
    [_serverAddrText.rightAnchor constraintEqualToAnchor:_roomIdText.rightAnchor].active = YES;
    [_serverAddrText.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_quicCheckBox.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:30.0].active = YES;
    [_quicCheckBox.topAnchor constraintEqualToAnchor:_serverAddrLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_quicCheckBox.widthAnchor constraintEqualToConstant:70].active = YES;
    [_quicCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
   
    [_speakerCheckBox.leftAnchor constraintEqualToAnchor:_quicCheckBox.rightAnchor constant:30.0].active = YES;
    [_speakerCheckBox.topAnchor constraintEqualToAnchor:_serverAddrLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_speakerCheckBox.widthAnchor constraintEqualToConstant:70].active = YES;
    [_speakerCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_videoCheckBox.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:30.0].active = YES;
    [_videoCheckBox.topAnchor constraintEqualToAnchor:_quicCheckBox.bottomAnchor constant:verticalInterval].active = YES;
    [_videoCheckBox.widthAnchor constraintEqualToConstant:70].active = YES;
    [_videoCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
   
    [_videoSourceCheckBox.leftAnchor constraintEqualToAnchor:_videoCheckBox.rightAnchor constant:30.0].active = YES;
    [_videoSourceCheckBox.topAnchor constraintEqualToAnchor:_quicCheckBox.bottomAnchor constant:verticalInterval].active = YES;
    [_videoSourceCheckBox.widthAnchor constraintEqualToConstant:70].active = YES;
    [_videoSourceCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_simulcastStreamCheckBox.leftAnchor constraintEqualToAnchor:_speakerCheckBox.rightAnchor constant:30.0].active = YES;
    [_simulcastStreamCheckBox.topAnchor constraintEqualToAnchor:_serverAddrLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_simulcastStreamCheckBox.widthAnchor constraintEqualToConstant:70].active = YES;
    [_simulcastStreamCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_detachStreamCheckBox.leftAnchor constraintEqualToAnchor:_videoSourceCheckBox.rightAnchor constant:30.0].active = YES;
    [_detachStreamCheckBox.topAnchor constraintEqualToAnchor:_quicCheckBox.bottomAnchor constant:verticalInterval].active = YES;
    [_detachStreamCheckBox.widthAnchor constraintEqualToConstant:120].active = YES;
    [_detachStreamCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;

    [_joinButton.centerXAnchor constraintEqualToAnchor:margin.centerXAnchor ].active = YES;
    [_joinButton.topAnchor constraintEqualToAnchor:_videoCheckBox.bottomAnchor constant:20.0].active = YES;
    [_joinButton.widthAnchor constraintEqualToConstant:100].active = YES;
    [_joinButton.heightAnchor constraintEqualToConstant:40].active = YES;
    
    [_singleButton.centerXAnchor constraintEqualToAnchor:margin.centerXAnchor ].active = YES;
    [_singleButton.topAnchor constraintEqualToAnchor:_joinButton.bottomAnchor constant:10.0].active = YES;
    [_singleButton.widthAnchor constraintEqualToConstant:100].active = YES;
    [_singleButton.heightAnchor constraintEqualToConstant:40].active = YES;
    
    self.view = _view;
    _token = @"";
    _singleJoin = YES;
    [self LoadConfig];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
  //  [self join:nil];
}

- (IBAction)join:(id)sender {
    _singleJoin = NO;
    _userId = [_userIdText.text intValue];
    if([_token compare:@""] == 0){
        [self getToken];
        return;
    }
    int scenarioType;
    if([_audioScenarioMenu getSelcetedIndex] == 0){
        scenarioType = 4;
    }else if([_audioScenarioMenu getSelcetedIndex] == 1){
        scenarioType = 3;
    }else {
        scenarioType = 7;
    }
    NADViewController *nadView = [[NADViewController alloc] init];
    nadView.modalPresentationStyle = UIModalPresentationFullScreen;
    nadView.channelId = _roomIdText.text;
    nadView.audioType = [_audioProfileMenu getSelcetedIndex];
    nadView.scenarioType = scenarioType;
    nadView.userRole = [_userRoleMenu getSelcetedIndex] + 1;
    nadView.serverType = [_serverTypeMenu getSelcetedIndex];
    nadView.userId = _userId;
    nadView.token = _token;
    nadView.appId = [_appIds objectAtIndex:[_appIdMenu getSelcetedIndex]];
    nadView.customAddr = _serverAddrText.text;
    nadView.quicEnabled = [_quicCheckBox getItemSelectedAtIndex:0];
    nadView.speakerEnabled = [_speakerCheckBox getItemSelectedAtIndex:0];
    nadView.videoEnabled = [_videoCheckBox getItemSelectedAtIndex:0];
    nadView.videoSourceEnabled = [_videoSourceCheckBox getItemSelectedAtIndex:0];
    nadView.simulcastStreamEnabled = [_simulcastStreamCheckBox getItemSelectedAtIndex:0];
    nadView.videoProfile = [_videoProfileMenu getSelcetedIndex];
    nadView.detachStreamEnabled = [_detachStreamCheckBox getItemSelectedAtIndex:0];
    [self presentViewController:nadView animated:YES completion:^{
        _token = @"";
        [self saveConfig];
    }];
    
}

- (IBAction)joinSingle:(id)sender {
    _singleJoin = YES;
    if([_token compare:@""] == 0){
        [self getToken];
        return;
    }
    FUViewController* view = [[FUViewController alloc] init];
    view.modalPresentationStyle = UIModalPresentationFullScreen;
    view.channelId = _roomIdText.text;
    view.audioType = [_audioProfileMenu getSelcetedIndex];
    view.userRole = [_userRoleMenu getSelcetedIndex] + 1;
    view.serverType = [_serverTypeMenu getSelcetedIndex];
    view.userId = _userId;
    view.token = _token;
    view.appId = [_appIds objectAtIndex:[_appIdMenu getSelcetedIndex]];
    view.customAddr = _serverAddrText.text;
    view.quicEnabled = [_quicCheckBox getItemSelectedAtIndex:0];
    view.speakerEnabled = [_speakerCheckBox getItemSelectedAtIndex:0];
    view.videoEnabled = [_videoCheckBox getItemSelectedAtIndex:0];
    view.videoSourceEnabled = [_videoSourceCheckBox getItemSelectedAtIndex:0];
    view.simulcastStreamEnabled = [_simulcastStreamCheckBox getItemSelectedAtIndex:0];
    view.videoProfile = [_videoProfileMenu getSelcetedIndex];
    view.detachStreamEnabled = [_detachStreamCheckBox getItemSelectedAtIndex:0];
    [self presentViewController:view animated:YES completion:^{
        _token = @"";
        [self saveConfig];
    }];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view endEditing:YES];
}

#pragma mark - LMJDropdownMenu DataSource
- (NSUInteger)numberOfOptionsInDropdownMenu:(LMJDropdownMenu *)menu{
    if(_audioProfileMenu == menu){
        return _audioOptionTitles.count;
    }
    else if(_userRoleMenu == menu){
        return _userOptionTitles.count;
    }
    else if(_serverTypeMenu == menu){
        return _serverOptionTitles.count;
    }
    else if(_audioScenarioMenu == menu){
        return _scenarioOptionTitles.count;
    }
    else if(_appIdMenu == menu){
        return _appIdList.count;
    }
    else if(_videoProfileMenu == menu){
        return _videoProfileOptionTitles.count;
    }
    return 0;
}
- (CGFloat)dropdownMenu:(LMJDropdownMenu *)menu heightForOptionAtIndex:(NSUInteger)index{
    return 30;
}
- (NSString *)dropdownMenu:(LMJDropdownMenu *)menu titleForOptionAtIndex:(NSUInteger)index{
    if(_audioProfileMenu == menu){
        return _audioOptionTitles[index];
    }
    else if(_userRoleMenu == menu){
        return _userOptionTitles[index];
    }
    else if(_serverTypeMenu == menu){
        return _serverOptionTitles[index];
    }
    else if(_appIdMenu == menu){
        return _appIdList[index];
    }
    else if(_audioScenarioMenu == menu){
        return _scenarioOptionTitles[index];
    }
    else if(_videoProfileMenu == menu){
        return _videoProfileOptionTitles[index];
    }
    return @"";
}
- (UIImage *)dropdownMenu:(LMJDropdownMenu *)menu iconForOptionAtIndex:(NSUInteger)index{
    return nil;
}
#pragma mark - LMJDropdownMenu Delegate
- (void)dropdownMenu:(LMJDropdownMenu *)menu didSelectOptionAtIndex:(NSUInteger)index optionTitle:(NSString *)title{
    
}

- (void)dropdownMenuWillShow:(LMJDropdownMenu *)menu{
    
}
- (void)dropdownMenuDidShow:(LMJDropdownMenu *)menu{
    
}

- (void)dropdownMenuWillHidden:(LMJDropdownMenu *)menu{
    
}
- (void)dropdownMenuDidHidden:(LMJDropdownMenu *)menu{
    
}

- (void)getToken{
    NSString *strURL = @"https://rtc-dev-gateway.aopacloud.net:6080/bbrtc/sign/getToken";
    NSURL *url = [NSURL URLWithString:strURL];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    request.timeoutInterval = 5;
    request.HTTPMethod = @"POST";
    [request setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    NSString *param = [NSString stringWithFormat:@"appName=%@&channel=%@&role=%@&uid=%u",
                       [_serverTypeMenu getSelcetedIndex] <= 1 ? @"online" : @"bbrtc",
                       _roomIdText.text,
                       [_userRoleMenu getSelcetedIndex] == 0 ? @"broadcaster" : @"audience",
                       _userId];
    request.HTTPBody = [param dataUsingEncoding:NSUTF8StringEncoding];
    NSURLSession *session = [NSURLSession sharedSession];
    [[session dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable connectionError) {

        NSHTTPURLResponse *resp = (NSHTTPURLResponse *)response;
        NSString *msg = [NSHTTPURLResponse localizedStringForStatusCode:resp.statusCode];
        NSLog(@"%td %@ %@",resp.statusCode, msg, resp.allHeaderFields);
        //这个block会在请求完毕的时候自动调用
        if (connectionError || data == nil) {
            return;
        }
        //解析服务器返回的JSON数据
        NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableLeaves error:nil];
        NSString* code = dict[@"code"];
        if ([code intValue] == 200) {
            _token = dict[@"token"];
            dispatch_sync(dispatch_get_main_queue(), ^{
                if (_singleJoin) {
                    [self joinSingle:nil];
                } else {
                    [self join:nil];
                }
            });
        }
        else{
            NSLog(@"++++ get token failed..\n");
        }
    }] resume];
}

- (void)LoadConfig{
   NSString * docsdir = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
   docsdir = [docsdir stringByAppendingString:@"/login_config"];
   FILE* pf = fopen([docsdir UTF8String], "rb");
   if(!pf){
     return;
   }
   memset(&_config, 0, sizeof(_config));
   int len = fread(&_config, 1, sizeof(_config), pf);
   fclose(pf);
   if(len != sizeof(_config))
     return;
   _roomIdText.text = [NSString stringWithUTF8String:_config.roomId];
    _serverAddrText.text = [NSString stringWithUTF8String:_config.customServer];
    [_audioProfileMenu selectItme:_config.audioProfile];
    [_audioScenarioMenu selectItme:_config.audioScenario];
    [_userRoleMenu selectItme:_config.role];
    [_serverTypeMenu selectItme:_config.serverIndex];
    [_appIdMenu selectItme:_config.appIndex];
    [_quicCheckBox setItemSelected:_config.quic index:0];
    [_speakerCheckBox setItemSelected:_config.speaker index:0];
    [_videoCheckBox setItemSelected:_config.videoEnabled index:0];
    [_videoSourceCheckBox setItemSelected:_config.localVideoSource index:0];
    [_simulcastStreamCheckBox setItemSelected:_config.simulcast index:0];
    [_videoProfileMenu selectItme:_config.videoProfile];
    [_detachStreamCheckBox setItemSelected:_config.detachStream index:0];
}

- (void)saveConfig{
    NSString * docsdir = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    docsdir = [docsdir stringByAppendingString:@"/login_config"];
    FILE* pf = fopen([docsdir UTF8String], "wb");
    if(!pf){
      return;
    }
     strcpy(_config.roomId, [_roomIdText.text UTF8String]);
     strcpy(_config.customServer, [_serverAddrText.text UTF8String]);
    _config.audioProfile = [_audioProfileMenu getSelcetedIndex];
    _config.audioScenario = [_audioScenarioMenu getSelcetedIndex];
    _config.role = [_userRoleMenu getSelcetedIndex];
    _config.serverIndex = [_serverTypeMenu getSelcetedIndex];
    _config.appIndex = [_appIdMenu getSelcetedIndex];
    _config.quic = [_quicCheckBox getItemSelectedAtIndex:0];
    _config.speaker = [_speakerCheckBox getItemSelectedAtIndex:0];
    _config.videoEnabled = [_videoCheckBox getItemSelectedAtIndex:0];
    _config.localVideoSource = [_videoSourceCheckBox getItemSelectedAtIndex:0];
    _config.simulcast = [_simulcastStreamCheckBox getItemSelectedAtIndex:0];
    _config.videoProfile = [_videoProfileMenu getSelcetedIndex];
    _config.detachStream = [_detachStreamCheckBox getItemSelectedAtIndex:0];
    fwrite(&_config, 1, sizeof(_config), pf);
    fclose(pf);
}
@end
