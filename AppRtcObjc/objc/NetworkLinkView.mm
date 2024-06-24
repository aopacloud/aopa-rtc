#import "NetworkLinkView.h"


@interface MyUITextField2 : UITextField
- (CGRect)textRectForBounds:(CGRect)bounds;
- (CGRect)editingRectForBounds:(CGRect)bounds;
@end
@implementation MyUITextField2
- (CGRect)textRectForBounds:(CGRect)bounds
{
    return CGRectInset(bounds, 10, 0);
}

- (CGRect)editingRectForBounds:(CGRect)bounds
{
    return CGRectInset(bounds, 10, 0);
}
@end

@interface NetworkLinkView ()
@property(nonatomic) UILabel*  lossRateUpLabel;
@property(nonatomic) MyUITextField2*  lossRateUpTextField;
@property(nonatomic) UILabel*  lossRateDownLabel;
@property(nonatomic) MyUITextField2*  lossRateDownTextField;

@property(nonatomic) UILabel*  rttUpLabel;
@property(nonatomic) MyUITextField2*  rttUpTextField;
@property(nonatomic) UILabel*  rttDownLabel;
@property(nonatomic) MyUITextField2*  rttDownTextField;

@property(nonatomic) UILabel*  bandwidthUpLabel;
@property(nonatomic) MyUITextField2*  bandwidthUpTextField;
@property(nonatomic) UILabel*  bandwidthDownLabel;
@property(nonatomic) MyUITextField2*  bandwidthDownTextField;

@property(nonatomic) UIButton* cancelButton;
@property(nonatomic) UIButton* saveButton;

@end
@implementation NetworkLinkView{
    BBRtcEngineKit* _rtcEngine;
}

- (void)loadview:(BBRtcEngineKit*)rtcEngine{
    _rtcEngine = rtcEngine;
    UIView* bkView = self;
    bkView.backgroundColor = [UIColor colorWithRed:200/255.f green:200/255.f blue:200/255.f alpha:1];
    _lossRateUpLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _lossRateUpLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _lossRateUpLabel.font = [UIFont systemFontOfSize:13];
    _lossRateUpLabel.textColor = [UIColor blackColor];
    [_lossRateUpLabel setText:@"上行丢包率"];
    [bkView addSubview:_lossRateUpLabel];
    
    _lossRateUpTextField = [[MyUITextField2 alloc] initWithFrame:CGRectZero];
    _lossRateUpTextField.translatesAutoresizingMaskIntoConstraints = NO;
    _lossRateUpTextField.font = [UIFont systemFontOfSize:13];
    _lossRateUpTextField.text = @"0";
    _lossRateUpTextField.textColor = [UIColor blackColor];
    [_lossRateUpTextField setBackgroundColor: [UIColor whiteColor] ];
    [_lossRateUpTextField setTintColor:[UIColor blackColor]];
    _lossRateUpTextField.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _lossRateUpTextField.layer.borderWidth  = 1;
    _lossRateUpTextField.layer.cornerRadius = 5;
    [bkView addSubview:_lossRateUpTextField];
    
    _lossRateDownLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _lossRateDownLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _lossRateDownLabel.font = [UIFont systemFontOfSize:13];
    _lossRateDownLabel.textColor = [UIColor blackColor];
    [_lossRateDownLabel setText:@"下行丢包率"];
    [bkView addSubview:_lossRateDownLabel];
    
    _lossRateDownTextField = [[MyUITextField2 alloc] initWithFrame:CGRectZero];
    _lossRateDownTextField.translatesAutoresizingMaskIntoConstraints = NO;
    _lossRateDownTextField.font = [UIFont systemFontOfSize:13];
    _lossRateDownTextField.text = @"0";
    _lossRateDownTextField.textColor = [UIColor blackColor];
    [_lossRateDownTextField setBackgroundColor: [UIColor whiteColor] ];
    [_lossRateDownTextField setTintColor:[UIColor blackColor]];
    _lossRateDownTextField.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _lossRateDownTextField.layer.borderWidth  = 1;
    _lossRateDownTextField.layer.cornerRadius = 5;
    [bkView addSubview:_lossRateDownTextField];
    
    _rttUpLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _rttUpLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _rttUpLabel.font = [UIFont systemFontOfSize:13];
    _rttUpLabel.textColor = [UIColor blackColor];
    [_rttUpLabel setText:@"上行时延(ms)"];
    [bkView addSubview:_rttUpLabel];
    
    _rttUpTextField = [[MyUITextField2 alloc] initWithFrame:CGRectZero];
    _rttUpTextField.translatesAutoresizingMaskIntoConstraints = NO;
    _rttUpTextField.font = [UIFont systemFontOfSize:13];
    _rttUpTextField.text = @"0";
    _rttUpTextField.textColor = [UIColor blackColor];
    [_rttUpTextField setBackgroundColor: [UIColor whiteColor] ];
    [_rttUpTextField setTintColor:[UIColor blackColor]];
    _rttUpTextField.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _rttUpTextField.layer.borderWidth  = 1;
    _rttUpTextField.layer.cornerRadius = 5;
    [bkView addSubview:_rttUpTextField];
    
    _rttDownLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _rttDownLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _rttDownLabel.font = [UIFont systemFontOfSize:13];
    _rttDownLabel.textColor = [UIColor blackColor];
    [_rttDownLabel setText:@"下行时延(ms)"];
    [bkView addSubview:_rttDownLabel];
    
    _rttDownTextField = [[MyUITextField2 alloc] initWithFrame:CGRectZero];
    _rttDownTextField.translatesAutoresizingMaskIntoConstraints = NO;
    _rttDownTextField.font = [UIFont systemFontOfSize:13];
    _rttDownTextField.text = @"0";
    _rttDownTextField.textColor = [UIColor blackColor];
    [_rttDownTextField setBackgroundColor: [UIColor whiteColor] ];
    [_rttDownTextField setTintColor:[UIColor blackColor]];
    _rttDownTextField.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _rttDownTextField.layer.borderWidth  = 1;
    _rttDownTextField.layer.cornerRadius = 5;
    [bkView addSubview:_rttDownTextField];
    
    
    
    _bandwidthUpLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _bandwidthUpLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _bandwidthUpLabel.font = [UIFont systemFontOfSize:13];
    _bandwidthUpLabel.textColor = [UIColor blackColor];
    [_bandwidthUpLabel setText:@"上行带宽(kbps)"];
    [bkView addSubview:_bandwidthUpLabel];
    
    _bandwidthUpTextField = [[MyUITextField2 alloc] initWithFrame:CGRectZero];
    _bandwidthUpTextField.translatesAutoresizingMaskIntoConstraints = NO;
    _bandwidthUpTextField.font = [UIFont systemFontOfSize:13];
    _bandwidthUpTextField.text = @"0";
    _bandwidthUpTextField.textColor = [UIColor blackColor];
    [_bandwidthUpTextField setBackgroundColor: [UIColor whiteColor] ];
    [_bandwidthUpTextField setTintColor:[UIColor blackColor]];
    _bandwidthUpTextField.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _bandwidthUpTextField.layer.borderWidth  = 1;
    _bandwidthUpTextField.layer.cornerRadius = 5;
    [bkView addSubview:_bandwidthUpTextField];
    
    _bandwidthDownLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _bandwidthDownLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _bandwidthDownLabel.font = [UIFont systemFontOfSize:13];
    _bandwidthDownLabel.textColor = [UIColor blackColor];
    [_bandwidthDownLabel setText:@"下行带宽(kbps)"];
    [bkView addSubview:_bandwidthDownLabel];
    
    _bandwidthDownTextField = [[MyUITextField2 alloc] initWithFrame:CGRectZero];
    _bandwidthDownTextField.translatesAutoresizingMaskIntoConstraints = NO;
    _bandwidthDownTextField.font = [UIFont systemFontOfSize:13];
    _bandwidthDownTextField.text = @"0";
    _bandwidthDownTextField.textColor = [UIColor blackColor];
    [_bandwidthDownTextField setBackgroundColor: [UIColor whiteColor] ];
    [_bandwidthDownTextField setTintColor:[UIColor blackColor]];
    _bandwidthDownTextField.layer.borderColor  = [UIColor colorWithRed:150/255.f green:150/255.f blue:150/255.f alpha:1].CGColor;
    _bandwidthDownTextField.layer.borderWidth  = 1;
    _bandwidthDownTextField.layer.cornerRadius = 5;
    [bkView addSubview:_bandwidthDownTextField];
    
    
    _cancelButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _cancelButton.translatesAutoresizingMaskIntoConstraints = NO;
    _cancelButton.titleLabel.font = [UIFont systemFontOfSize:15];
    [_cancelButton.layer setMasksToBounds:YES];
    [_cancelButton.layer setCornerRadius:5.0];
    [_cancelButton setTitle:@"取消" forState:UIControlStateNormal];
    [_cancelButton setTintColor:[UIColor whiteColor]];
    [_cancelButton setBackgroundColor: [UIColor colorWithRed:0.1 green:0.1 blue:0.1 alpha:1.0]];
    [_cancelButton addTarget:self action:@selector(onCacel:) forControlEvents:UIControlEventTouchUpInside];
    [bkView addSubview:_cancelButton];
    
    _saveButton = [UIButton buttonWithType:UIButtonTypeSystem];
    _saveButton.translatesAutoresizingMaskIntoConstraints = NO;
    _saveButton.titleLabel.font = [UIFont systemFontOfSize:15];
    [_saveButton.layer setMasksToBounds:YES];
    [_saveButton.layer setCornerRadius:5.0];
    [_saveButton setTitle:@"保存" forState:UIControlStateNormal];
    [_saveButton setTintColor:[UIColor whiteColor]];
    [_saveButton setBackgroundColor: [UIColor colorWithRed:0.1 green:0.1 blue:0.1 alpha:1.0]];
    [_saveButton addTarget:self action:@selector(onSave:) forControlEvents:UIControlEventTouchUpInside];
    [bkView addSubview:_saveButton];
    
    
    UILayoutGuide *margin = bkView.layoutMarginsGuide;
    [_lossRateUpLabel.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:10.0].active = YES;
    [_lossRateUpLabel.topAnchor constraintEqualToAnchor:margin.topAnchor constant:10.0].active = YES;
    [_lossRateUpLabel.widthAnchor constraintEqualToConstant:100].active = YES;
    [_lossRateUpLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_lossRateUpTextField.leftAnchor constraintEqualToAnchor:_lossRateUpLabel.rightAnchor ].active = YES;
    [_lossRateUpTextField.topAnchor constraintEqualToAnchor:_lossRateUpLabel.topAnchor].active = YES;
    [_lossRateUpTextField.widthAnchor constraintEqualToConstant:100].active = YES;
    [_lossRateUpTextField.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_lossRateDownLabel.leftAnchor constraintEqualToAnchor:_lossRateUpLabel.leftAnchor].active = YES;
    [_lossRateDownLabel.topAnchor constraintEqualToAnchor:_lossRateUpLabel.bottomAnchor constant:10.0].active = YES;
    [_lossRateDownLabel.widthAnchor constraintEqualToConstant:100].active = YES;
    [_lossRateDownLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_lossRateDownTextField.leftAnchor constraintEqualToAnchor:_lossRateDownLabel.rightAnchor ].active = YES;
    [_lossRateDownTextField.topAnchor constraintEqualToAnchor:_lossRateDownLabel.topAnchor].active = YES;
    [_lossRateDownTextField.widthAnchor constraintEqualToConstant:100].active = YES;
    [_lossRateDownTextField.heightAnchor constraintEqualToConstant:32].active = YES;
    
    
    [_rttUpLabel.leftAnchor constraintEqualToAnchor:_lossRateDownLabel.leftAnchor].active = YES;
    [_rttUpLabel.topAnchor constraintEqualToAnchor:_lossRateDownLabel.bottomAnchor constant:10.0].active = YES;
    [_rttUpLabel.widthAnchor constraintEqualToConstant:100].active = YES;
    [_rttUpLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_rttUpTextField.leftAnchor constraintEqualToAnchor:_rttUpLabel.rightAnchor ].active = YES;
    [_rttUpTextField.topAnchor constraintEqualToAnchor:_rttUpLabel.topAnchor].active = YES;
    [_rttUpTextField.widthAnchor constraintEqualToConstant:100].active = YES;
    [_rttUpTextField.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_rttDownLabel.leftAnchor constraintEqualToAnchor:_rttUpLabel.leftAnchor ].active = YES;
    [_rttDownLabel.topAnchor constraintEqualToAnchor:_rttUpLabel.bottomAnchor constant:10.0].active = YES;
    [_rttDownLabel.widthAnchor constraintEqualToConstant:100].active = YES;
    [_rttDownLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_rttDownTextField.leftAnchor constraintEqualToAnchor:_rttDownLabel.rightAnchor ].active = YES;
    [_rttDownTextField.topAnchor constraintEqualToAnchor:_rttDownLabel.topAnchor].active = YES;
    [_rttDownTextField.widthAnchor constraintEqualToConstant:100].active = YES;
    [_rttDownTextField.heightAnchor constraintEqualToConstant:32].active = YES;
    
    
    [_bandwidthUpLabel.leftAnchor constraintEqualToAnchor:_rttDownLabel.leftAnchor].active = YES;
    [_bandwidthUpLabel.topAnchor constraintEqualToAnchor:_rttDownLabel.bottomAnchor constant:10.0].active = YES;
    [_bandwidthUpLabel.widthAnchor constraintEqualToConstant:100].active = YES;
    [_bandwidthUpLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_bandwidthUpTextField.leftAnchor constraintEqualToAnchor:_bandwidthUpLabel.rightAnchor ].active = YES;
    [_bandwidthUpTextField.topAnchor constraintEqualToAnchor:_bandwidthUpLabel.topAnchor].active = YES;
    [_bandwidthUpTextField.widthAnchor constraintEqualToConstant:100].active = YES;
    [_bandwidthUpTextField.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_bandwidthDownLabel.leftAnchor constraintEqualToAnchor:_bandwidthUpLabel.leftAnchor ].active = YES;
    [_bandwidthDownLabel.topAnchor constraintEqualToAnchor:_bandwidthUpLabel.bottomAnchor constant:10.0].active = YES;
    [_bandwidthDownLabel.widthAnchor constraintEqualToConstant:100].active = YES;
    [_bandwidthDownLabel.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_bandwidthDownTextField.leftAnchor constraintEqualToAnchor:_bandwidthDownLabel.rightAnchor].active = YES;
    [_bandwidthDownTextField.topAnchor constraintEqualToAnchor:_bandwidthDownLabel.topAnchor].active = YES;
    [_bandwidthDownTextField.widthAnchor constraintEqualToConstant:100].active = YES;
    [_bandwidthDownTextField.heightAnchor constraintEqualToConstant:32].active = YES;
    
    [_cancelButton.leftAnchor constraintEqualToAnchor:margin.leftAnchor constant:50.0].active = YES;
    [_cancelButton.topAnchor constraintEqualToAnchor:_bandwidthDownLabel.bottomAnchor constant:50.0].active = YES;
    [_cancelButton.widthAnchor constraintEqualToConstant:60].active = YES;
    [_cancelButton.heightAnchor constraintEqualToConstant:30].active = YES;
    
    [_saveButton.leftAnchor constraintEqualToAnchor:_cancelButton.rightAnchor constant:20.0].active = YES;
    [_saveButton.topAnchor constraintEqualToAnchor:_cancelButton.topAnchor].active = YES;
    [_saveButton.widthAnchor constraintEqualToConstant:60].active = YES;
    [_saveButton.heightAnchor constraintEqualToConstant:30].active = YES;
    
}


- (IBAction)onCacel:(id)sender {
    [self setHidden:YES];
}

- (IBAction)onSave:(id)sender {
    [_rtcEngine setParameters:[NSString stringWithFormat:@"{\"che.test.lossrate.up\":%@}", _lossRateUpTextField.text]] ;
    [_rtcEngine setParameters:[NSString stringWithFormat:@"{\"che.test.lossrate.down\":%@}", _lossRateDownTextField.text]] ;
    [_rtcEngine setParameters:[NSString stringWithFormat:@"{\"che.test.rtt.up\":%@}", _rttUpTextField.text]] ;
    [_rtcEngine setParameters:[NSString stringWithFormat:@"{\"che.test.rtt.down\":%@}", _rttDownTextField.text]] ;
    [_rtcEngine setParameters:[NSString stringWithFormat:@"{\"che.test.bandwidth.up\":%@}", _bandwidthUpTextField.text]] ;
    [_rtcEngine setParameters:[NSString stringWithFormat:@"{\"che.test.bandwidth.down\":%@}", _bandwidthDownTextField.text]];
    [self setHidden:YES];
}

- (void)show{
    _lossRateUpTextField.text = [NSString stringWithFormat:@"%d", [_rtcEngine setParameters:@"{\"che.test.lossrate.up.get\"}"]];
    _lossRateDownTextField.text = [NSString stringWithFormat:@"%d", [_rtcEngine setParameters:@"{\"che.test.lossrate.down.get\"}"]];
    _rttUpTextField.text = [NSString stringWithFormat:@"%d", [_rtcEngine setParameters:@"{\"che.test.rtt.up.get\"}"]];
    _rttDownTextField.text = [NSString stringWithFormat:@"%d", [_rtcEngine setParameters:@"{\"che.test.rtt.down.get\"}"]];
    _bandwidthUpTextField.text = [NSString stringWithFormat:@"%d", [_rtcEngine setParameters:@"{\"che.test.bandwidth.up.get\"}"]];
    _bandwidthDownTextField.text = [NSString stringWithFormat:@"%d", [_rtcEngine setParameters:@"{\"che.test.bandwidth.down.get\"}"]];
    [self setHidden:NO];
}
@end
