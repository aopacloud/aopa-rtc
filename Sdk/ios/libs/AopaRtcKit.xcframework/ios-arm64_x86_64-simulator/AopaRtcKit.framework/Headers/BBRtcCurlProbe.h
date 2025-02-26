//
//  BBRtcCurlProbe.h
//  sources
//
//  Created by bhb on 2024/1/22.
//  Copyright © 2024 aopa. All rights reserved.
//
#import <Foundation/Foundation.h>

__attribute__((visibility("default"))) @interface BBRtcCurlProbo : NSObject

@property(nonatomic, assign) double namelookup_time;
@property(nonatomic, assign) double connect_time;
@property(nonatomic, assign) double appconnect_time;
@property(nonatomic, assign) double redirect_time;
@property(nonatomic, assign) double pretransfer_time;
@property(nonatomic, assign) double starttransfer_time;
@property(nonatomic, assign) double total_time;
@property(nonatomic, strong) NSString* body;

- (int) testNetworkByUrl:(NSString*) url;
@end
