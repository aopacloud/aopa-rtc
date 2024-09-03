//
//  NADCheckBox.h
//  products
//
//  Created by bhb on 2021/12/31.
//


#import <UIKit/UIKit.h>

@class NADCheckBox;
@protocol CheckBoxDelegate <NSObject>
/**
 *  
 *
 */
-(void)checkBoxItemdidSelected:(UIButton *)item atIndex:(NSUInteger)index checkBox:(NADCheckBox *)checkbox;
@end


@interface NADCheckBox : UIView
@property(nonatomic, assign) BOOL       isMulti;        
@property(nonatomic, assign) BOOL       isBottomLine;   
@property(nonatomic, strong) UIImage    *normalImage;   
@property(nonatomic, strong) UIImage    *selectedImage; 
@property(nonatomic, assign) NSUInteger columnCount;    
@property(nonatomic, strong) UIColor    *textColor;     
@property(nonatomic, strong) UIFont     *textFont;      
@property(nonatomic, assign) UIControlContentHorizontalAlignment alignment;

@property (nonatomic, assign) id<CheckBoxDelegate>   delegate;

/**
 *  
 *
 *  @param titleArray  
 *  @param columnCount 
 *
 *  @return self
 */
- (instancetype)initWithItemTitleArray:(NSArray *)titleArray columns:(NSUInteger)columnCount;



- (instancetype)initWithItemTitleArray:(NSArray *)titleArray columns:(NSUInteger)columnCount isBottomLine:(BOOL)isBottomLine;


/**
 *  
 *
 *  @param titleArray 
 */
- (void)setItemTitleWithArray:(NSArray *)titleArray;

/**
 *  
 *
 *  @param isSelected YES or NO
 *  @param index      
 */
- (void)setItemSelected:(BOOL)isSelected index:(NSUInteger)index;

/**
 *  
 *
 *  @param index 
 *
 *  @return YES or NO
 */
- (BOOL)getItemSelectedAtIndex:(NSUInteger)index;

/**
 *  
 *
 *  @return 
 */
- (NSArray *)getSelectedItemIndexs;
- (NSArray *)getSelectedItemIndexsStartAtOne;
@end
