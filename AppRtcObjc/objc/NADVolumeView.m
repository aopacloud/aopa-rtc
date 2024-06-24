//
//  NADVolumeView.m
//  sources
//
//  Created by bhb on 2020/5/7.
//

#import "NADVolumeView.h"

@implementation NADVolumeView{
    int _volume;
    BOOL _mute;
}


-(void) setVolume:(int)vaule{
    _volume = vaule;
    [self setNeedsDisplay];
}

- (void) setMute:(BOOL)mute{
    _mute = mute;
    [self setNeedsDisplay];
}

- (void)drawRect:(CGRect)rect {
    int line = _volume/25;
    CGContextRef context = UIGraphicsGetCurrentContext();
    [self.backgroundColor  setStroke];
    CGContextFillRect(context, self.bounds);
    CGContextSetLineWidth(context, 3.0);
    for (int i = 0; i < 10; i++) {
        if (i < line) {
            [[UIColor greenColor] setStroke];
        }else{
            [[UIColor grayColor] setStroke];
        }
        CGContextMoveToPoint(context, 0, rect.size.height - i * 6 - 4);
        CGContextAddLineToPoint(context, rect.size.width, rect.size.height - i * 6 - 4);
        CGContextStrokePath(context);
    }
    if(_mute){
        CGContextSetLineWidth(context, 2.0);
        [[UIColor redColor] setStroke];
        CGContextMoveToPoint(context, 0, rect.size.height - 4);
        CGContextAddLineToPoint(context, rect.size.width, rect.size.height - 58);
        CGContextMoveToPoint(context, rect.size.width, rect.size.height - 4);
        CGContextAddLineToPoint(context, 0, rect.size.height - 58);
        CGContextStrokePath(context);
    }
    
}

@end
