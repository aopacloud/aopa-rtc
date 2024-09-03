//
//  LMJDropdownMenu.h
//
//  Created by Jerry LMJ on 15/5/4.
//  Copyright (c) 2015年 LMJ. All rights reserved.
//

#import <UIKit/UIKit.h>

@class LMJDropdownMenu;

NS_ASSUME_NONNULL_BEGIN
@protocol LMJDropdownMenuDataSource <NSObject>
@required
- (NSUInteger)numberOfOptionsInDropdownMenu:(LMJDropdownMenu *)menu;
- (CGFloat)dropdownMenu:(LMJDropdownMenu *)menu heightForOptionAtIndex:(NSUInteger)index;
- (NSString *)dropdownMenu:(LMJDropdownMenu *)menu titleForOptionAtIndex:(NSUInteger)index;
@optional
- (UIImage *)dropdownMenu:(LMJDropdownMenu *)menu iconForOptionAtIndex:(NSUInteger)index;
@end


@protocol LMJDropdownMenuDelegate <NSObject>
@optional
- (void)dropdownMenuWillShow:(LMJDropdownMenu *)menu;    
- (void)dropdownMenuDidShow:(LMJDropdownMenu *)menu;    
- (void)dropdownMenuWillHidden:(LMJDropdownMenu *)menu;  
- (void)dropdownMenuDidHidden:(LMJDropdownMenu *)menu;   

- (void)dropdownMenu:(LMJDropdownMenu *)menu didSelectOptionAtIndex:(NSUInteger)index optionTitle:(NSString *)title; 
@end




@interface LMJDropdownMenu : UIView <UITableViewDataSource,UITableViewDelegate>

@property (nonatomic, assign) id <LMJDropdownMenuDataSource>  _Nullable dataSource;
@property (nonatomic, assign) id <LMJDropdownMenuDelegate> _Nullable delegate;


@property(nonatomic,copy)   NSString        * title;
@property(nonatomic,strong) UIColor         * titleBgColor;
@property(nonatomic,strong) UIFont          * titleFont;
@property(nonatomic,strong) UIColor         * titleColor;
@property(nonatomic)        NSTextAlignment   titleAlignment;
@property(nonatomic)        UIEdgeInsets      titleEdgeInsets;

@property(nonatomic,strong) UIImage         * rotateIcon;
@property(nonatomic,assign) CGSize            rotateIconSize;


@property(nonatomic,strong) UIColor         * optionBgColor;
@property(nonatomic,strong) UIFont          * optionFont;
@property(nonatomic,strong) UIColor         * optionTextColor;
@property(nonatomic)        NSTextAlignment   optionTextAlignment;
@property(nonatomic)        NSInteger         optionNumberOfLines;
@property(nonatomic,strong) UIColor         * optionLineColor; 
@property(nonatomic,assign) CGSize            optionIconSize;  // default:(15,15)


@property(nonatomic,assign) CGFloat animateTime;   


- (void)reloadOptionsData;

- (void)showDropDown; 
- (void)hideDropDown; 

- (void)selectItme:(int)index;
- (int)getSelcetedIndex;
@end

NS_ASSUME_NONNULL_END
