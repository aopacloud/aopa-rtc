//
//  NADLoginController.m
//  sources
//
//  Created by ; on 2020/4/13.
//
#import <AVFoundation/AVFoundation.h>
#import "NADLoginController.h"
#import "NADViewController.h"
#import "LMJDropdownMenu.h"
#import "NADAppDelegate.h"
#import "NADCheckBox.h"

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
@property(nonatomic) UILabel* audioProfileLabel;
@property(nonatomic) LMJDropdownMenu* audioProfileMenu;
@property(nonatomic) UILabel* audioScenarioLabel;
@property(nonatomic) LMJDropdownMenu* audioScenarioMenu;
@property(nonatomic) UILabel* videoProfileLabel;
@property(nonatomic) LMJDropdownMenu* videoProfileMenu;
@property(nonatomic) UILabel* userRoleLabel;
@property(nonatomic) LMJDropdownMenu* userRoleMenu;
@property(nonatomic) NADCheckBox* videoCheckBox;
@property(nonatomic) NADCheckBox* videoSourceCheckBox;
@property(nonatomic) NADCheckBox* speakerCheckBox;
@end

@implementation NADLoginController{
    UIView *_view;
    NSArray * _audioOptionTitles;
    NSArray * _userOptionTitles;
    NSArray * _scenarioOptionTitles;
    NSArray * _videoProfileOptionTitles;
}



- (void)viewDidLoad {
    [super viewDidLoad];
    
    _audioOptionTitles = [[NSArray alloc]initWithObjects:@"default", @"speechmono",
                          @"musicmono", @"musicstero", @"musicmonoHighqulity", @"musicSteroHighQuality", nil];
    _userOptionTitles = [[NSArray alloc]initWithObjects:@"broadcaster", @"audience", nil];
    _scenarioOptionTitles = [[NSArray alloc]initWithObjects:@"ShowRoom", @"GameStreaming", @"Chorus", nil];
    _videoProfileOptionTitles = [[NSArray alloc]initWithObjects:@"360x640", @"480x640", @"540x960", @"720x1280", @"1080x1920", nil];
    
    _view = [[UIView alloc] initWithFrame:CGRectZero];
    [_view setBackgroundColor: [UIColor whiteColor] ];
    
    _roomIdLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _roomIdLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _roomIdLabel.font = [UIFont systemFontOfSize:13];
    _roomIdLabel.textColor = [UIColor blackColor];
    [_roomIdLabel setText:@"roomId"];
    [_view addSubview:_roomIdLabel];
    
    _roomIdText = [[MyUITextField alloc] initWithFrame:CGRectZero];
    _roomIdText.translatesAutoresizingMaskIntoConstraints = NO;
    _roomIdText.font = [UIFont systemFontOfSize:13];
    _roomIdText.text = @"room888";
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
    _userIdText.text = [NSString stringWithFormat:@"%d", arc4random() % 100000];
    _userIdText.textColor = [UIColor blackColor];
    [_userIdText textRectForBounds:CGRectMake(2, 0, 0, 0)];
    [_userIdText setBackgroundColor: [UIColor whiteColor] ];
    [_userIdText setTintColor:[UIColor blackColor]];
    _userIdText.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _userIdText.layer.borderWidth  = 1;
    _userIdText.layer.cornerRadius = 5;
    [_view addSubview:_userIdText];
    
    
    _joinButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _joinButton.translatesAutoresizingMaskIntoConstraints = NO;
    _joinButton.titleLabel.font = [UIFont systemFontOfSize:15];
    [_joinButton.layer setMasksToBounds:YES];
    [_joinButton.layer setCornerRadius:5.0];
    [_joinButton setTitle:@"JOIN" forState:UIControlStateNormal];
    [_joinButton setTintColor:[UIColor whiteColor]];
    [_joinButton setBackgroundColor: [UIColor colorWithRed:192/255.f green:62/255.f blue:42/255.f alpha:1.0]];
    [_joinButton addTarget:self action:@selector(join:) forControlEvents:UIControlEventTouchUpInside];
    [_view addSubview:_joinButton];
    
    _videoCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"open video"] columns:1];
    _videoCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _videoCheckBox.isMulti = YES;
    _videoCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_videoCheckBox setItemSelected:NO index:0];
    [_videoCheckBox setFrame:CGRectMake(0, 0, 100, 40)];
    [_videoCheckBox setNormalImage:[UIImage imageNamed:@"icon_check_n"]];
    [_videoCheckBox setSelectedImage:[UIImage imageNamed:@"icon_check_s"]];
    [_view addSubview:_videoCheckBox];
    
    _videoSourceCheckBox = [[NADCheckBox alloc]initWithItemTitleArray:@[@"local source"] columns:1];
    _videoSourceCheckBox.translatesAutoresizingMaskIntoConstraints = NO;
    _videoSourceCheckBox.isMulti = YES;
    _videoSourceCheckBox.alignment = UIControlContentHorizontalAlignmentLeft;
    [_videoSourceCheckBox setItemSelected:NO index:0];
    [_videoSourceCheckBox setFrame:CGRectMake(0, 0, 150, 40)];
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
    [_audioProfileLabel setText:@"quality"];
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
    
    [_view addSubview:_userRoleMenu];
    [_view addSubview:_videoProfileMenu];
    [_view addSubview:_audioScenarioMenu];
    [_view addSubview:_audioProfileMenu];
    
    
    const int verticalInterval = 20;
    UILayoutGuide *margin = _view.layoutMarginsGuide;
    [_roomIdLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_roomIdLabel.centerYAnchor constraintEqualToAnchor:margin.centerYAnchor constant:-300.0].active = YES;
    [_roomIdLabel.widthAnchor constraintEqualToConstant:70].active = YES;
    [_roomIdLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_roomIdText.leftAnchor constraintEqualToAnchor:_roomIdLabel.layoutMarginsGuide.rightAnchor ].active = YES;
    [_roomIdText.centerYAnchor constraintEqualToAnchor:margin.centerYAnchor constant:-300.0].active = YES;
    [_roomIdText.rightAnchor constraintEqualToAnchor:margin.rightAnchor constant:-20.0].active = YES;
    [_roomIdText.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_userIdLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_userIdLabel.topAnchor constraintEqualToAnchor:_roomIdLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_userIdLabel.widthAnchor constraintEqualToConstant:70].active = YES;
    [_userIdLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_userIdText.leftAnchor constraintEqualToAnchor:_roomIdText.leftAnchor].active = YES;
    [_userIdText.topAnchor constraintEqualToAnchor:_userIdLabel.topAnchor].active = YES;
    [_userIdText.rightAnchor constraintEqualToAnchor:_roomIdText.rightAnchor].active = YES;
    [_userIdText.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioProfileLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_audioProfileLabel.topAnchor constraintEqualToAnchor:_userIdLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_audioProfileLabel.widthAnchor constraintEqualToConstant:70].active = YES;
    [_audioProfileLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioProfileMenu.leftAnchor constraintEqualToAnchor:_userIdText.leftAnchor].active = YES;
    [_audioProfileMenu.topAnchor constraintEqualToAnchor:_audioProfileLabel.topAnchor].active = YES;
    [_audioProfileMenu.rightAnchor constraintEqualToAnchor:_userIdText.rightAnchor].active = YES;
    [_audioProfileMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioScenarioLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_audioScenarioLabel.topAnchor constraintEqualToAnchor:_audioProfileLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_audioScenarioLabel.widthAnchor constraintEqualToConstant:70].active = YES;
    [_audioScenarioLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_audioScenarioMenu.leftAnchor constraintEqualToAnchor:_userIdText.leftAnchor].active = YES;
    [_audioScenarioMenu.topAnchor constraintEqualToAnchor:_audioScenarioLabel.topAnchor].active = YES;
    [_audioScenarioMenu.rightAnchor constraintEqualToAnchor:_userIdText.rightAnchor].active = YES;
    [_audioScenarioMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    
    [_videoProfileLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_videoProfileLabel.topAnchor constraintEqualToAnchor:_audioScenarioLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_videoProfileLabel.widthAnchor constraintEqualToConstant:70].active = YES;
    [_videoProfileLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_videoProfileMenu.leftAnchor constraintEqualToAnchor:_userIdText.leftAnchor].active = YES;
    [_videoProfileMenu.topAnchor constraintEqualToAnchor:_videoProfileLabel.topAnchor].active = YES;
    [_videoProfileMenu.rightAnchor constraintEqualToAnchor:_userIdText.rightAnchor].active = YES;
    [_videoProfileMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    
    [_userRoleLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_userRoleLabel.topAnchor constraintEqualToAnchor:_videoProfileLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_userRoleLabel.widthAnchor constraintEqualToConstant:70].active = YES;
    [_userRoleLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_userRoleMenu.leftAnchor constraintEqualToAnchor:_roomIdText.leftAnchor].active = YES;
    [_userRoleMenu.topAnchor constraintEqualToAnchor:_userRoleLabel.topAnchor].active = YES;
    [_userRoleMenu.rightAnchor constraintEqualToAnchor:_roomIdText.rightAnchor].active = YES;
    [_userRoleMenu.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_speakerCheckBox.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:30.0].active = YES;
    [_speakerCheckBox.topAnchor constraintEqualToAnchor:_userRoleLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_speakerCheckBox.widthAnchor constraintEqualToConstant:70].active = YES;
    [_speakerCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_videoCheckBox.leftAnchor constraintEqualToAnchor:_speakerCheckBox.rightAnchor constant:30.0].active = YES;
    [_videoCheckBox.topAnchor constraintEqualToAnchor:_userRoleLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_videoCheckBox.widthAnchor constraintEqualToConstant:70].active = YES;
    [_videoCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_videoSourceCheckBox.leftAnchor constraintEqualToAnchor:_videoCheckBox.rightAnchor constant:30.0].active = YES;
    [_videoSourceCheckBox.topAnchor constraintEqualToAnchor:_userRoleLabel.bottomAnchor constant:verticalInterval].active = YES;
    [_videoSourceCheckBox.widthAnchor constraintEqualToConstant:100].active = YES;
    [_videoSourceCheckBox.heightAnchor constraintEqualToConstant:32].active = YES;
    
    
    [_joinButton.centerXAnchor constraintEqualToAnchor:margin.centerXAnchor ].active = YES;
    [_joinButton.topAnchor constraintEqualToAnchor:_videoCheckBox.bottomAnchor constant:150.0].active = YES;
    [_joinButton.widthAnchor constraintEqualToConstant:120].active = YES;
    [_joinButton.heightAnchor constraintEqualToConstant:50].active = YES;
    
    self.view = _view;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

- (IBAction)join:(id)sender {
    int scenarioType;
    if([_audioScenarioMenu getSelcetedIndex] == 0){
        scenarioType = BBRtcAudioScenarioShowRoom;
    }else if([_audioScenarioMenu getSelcetedIndex] == 1){
        scenarioType = BBRtcAudioScenarioGameStreaming;
    }else {
        scenarioType = BBRtcAudioScenarioChorus;
    }
    NADViewController *nadView = [[NADViewController alloc] init];
    nadView.modalPresentationStyle = UIModalPresentationFullScreen;
    nadView.channelId = _roomIdText.text;
    nadView.audioType = [_audioProfileMenu getSelcetedIndex];
    nadView.scenarioType = scenarioType;
    nadView.userRole = [_userRoleMenu getSelcetedIndex] == 0 ? BBRtcClientRoleBroadcaster : BBRtcClientRoleAudience;
    nadView.userId = [_userIdText.text intValue];
    nadView.token = @"";
    nadView.speakerEnabled = [_speakerCheckBox getItemSelectedAtIndex:0];
    nadView.videoEnabled = [_videoCheckBox getItemSelectedAtIndex:0];
    nadView.videoSourceEnabled = [_videoSourceCheckBox getItemSelectedAtIndex:0];
    nadView.videoProfile = [_videoProfileMenu getSelcetedIndex];
    [self presentViewController:nadView animated:YES completion:nil];
    
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
    else if(_audioScenarioMenu == menu){
        return _scenarioOptionTitles.count;
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

@end
