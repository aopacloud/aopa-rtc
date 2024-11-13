/*
 *  Copyright 2018 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#import <UIKit/UIKit.h>

@interface NADViewController : UIViewController
@property(nonatomic, strong) NSString* channelId;
@property(nonatomic) int audioType;
@property(nonatomic) int scenarioType;
@property(nonatomic) int userRole;
@property(nonatomic) int userId;
@property(nonatomic, strong) NSString* token;
@property(nonatomic, assign) BOOL videoEnabled;
@property(nonatomic, assign) BOOL speakerEnabled;
@property(nonatomic, assign) BOOL videoSourceEnabled;
@property(nonatomic) int videoProfile;

@end
