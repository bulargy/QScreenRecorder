//
//  QUIWindow.h
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QUIButton.h"
#import "QUIRecordOverlay.h"

@class QUIWindow;

/*!
 Window for the recording.
 */
@interface QUIWindow : UIWindow {
  QUIRecordOverlay *_recordOverlay;
}

/*!
 Disable all controls and event listeners.
 */
@property BOOL disabled;

/*!
 The current window instance.
 
 This is automatically set for most recent constructed QUIWindow.
 */
+ (QUIWindow *)window;

/*!
 Disable all controls and event listeners for the window.
 @param disabled Disable
 */
+ (void)setDisabled:(BOOL)disabled;

@end
