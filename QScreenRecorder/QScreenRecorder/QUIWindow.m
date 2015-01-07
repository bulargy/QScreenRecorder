//
//  QUIWindow.m
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import "QUIWindow.h"
#import "QDefines.h"
#import "QRecorder.h"

@implementation QUIWindow

- (void)sharedInit {
  _recordOverlay = [[QUIRecordOverlay alloc] init];
  _recordOverlay.hidden = YES;
  [self addSubview:_recordOverlay];  
  [QUIWindow setWindow:self];
}

static QUIWindow *gWindow = NULL;

+ (void)setWindow:(QUIWindow *)window {
  gWindow = window;
}

+ (QUIWindow *)window {
  return gWindow;
}

+ (void)setDisabled:(BOOL)disabled {
  [[self window] setDisabled:disabled];
}

- (id)initWithFrame:(CGRect)frame {
  if ((self = [super initWithFrame:frame])) {
    [self sharedInit];
  }
  return self;
}

- (id)initWithCoder:(NSCoder *)decoder {
  if ((self = [super initWithCoder:decoder])) {
    [self sharedInit];
  }
  return self;
}

- (void)layoutSubviews {
  [super layoutSubviews];
  _recordOverlay.frame = CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);
  [self bringSubviewToFront:_recordOverlay];
}

- (void)sendEvent:(UIEvent *)event {
  [super sendEvent:event];
  if (_disabled) return;
  [self _gestureEvent:event];  
  [[NSNotificationCenter defaultCenter] postNotificationName:QUIEventNotification object:event];
}

- (void)_gestureRecognized {
  QDebug(@"Gesture recognized");
  _recordOverlay.hidden = NO;
}

- (void)_gestureEvent:(UIEvent *)event {
  if (event.type == UIEventTypeTouches) {
    if ([[event allTouches] count] != 2) return;
    UITouch *touch = [[event allTouches] anyObject];
    if (touch.phase == UITouchPhaseEnded && touch.tapCount >= 3) {
      [self _gestureRecognized];
    }
  }
}

@end

