//
//  UserViewCell.h
//  AopaRtcObjc
//
//  Created by bhb on 2020/4/27.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol UserViewDelegate <NSObject>
@optional
-(void) onMuteClick:(NSUInteger)uid mute:(BOOL)mute;
-(void) onVolumeChange:(NSUInteger)uid volume:(int)volume;
-(void) onVideoStreamChange:(NSUInteger)uid type:(int)type;
@end

@interface UserViewCell : UICollectionViewCell
- (instancetype)initWithFrame:(CGRect)frame;
- (id)initWithUser:(CGRect)frame delegate:(id<UserViewDelegate> _Nullable)delegate uid:(NSUInteger)uid;
- (void)setMuteEnable:(BOOL)mute;
- (void)setRealTimeVolume:(int)volume;
- (void)setRemoteMute:(BOOL)mute;
- (void)setStreamType:(int)type;
- (void)setUserId:(NSUInteger)userId;
- (NSUInteger)getUserId;
- (UIView*)getVideoView;
- (void)setIndex:(int)idx;
- (int)getIndex;
@property (nonatomic, assign) id<UserViewDelegate>  _Nullable delegate;

@end

NS_ASSUME_NONNULL_END
