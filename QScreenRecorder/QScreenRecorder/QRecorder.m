//
//  QRecorder.m
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//
#import "QRecorder.h"
#import "QUIViewRecorder.h"
#import "QSpringBoardRecorder.h"
#import "QCameraRecorder.h"
#import "QUtils.h"
#import "QUIWindow.h"

@implementation QRecorder

- (id)init {
  if ((self = [super init])) {
    _options = QRecorderOptionUserCameraRecording|QRecorderOptionUserAudioRecording|QRecorderOptionTouchRecording;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(_onEvent:) name:QUIEventNotification object:nil];
  }
  return self;
}

- (void)dealloc {
  [[NSNotificationCenter defaultCenter] removeObserver:self];
}

+ (QRecorder *)sharedRecorder {
  static dispatch_once_t once;
  static id sharedInstance;
  dispatch_once(&once, ^{
    sharedInstance = [[self alloc] init];
  });
  return sharedInstance;
}

- (void)setOptions:(QRecorderOptions)options {
  if (self.isRecording) [NSException raise:QException format:@"You can't set recording options while recording is in progress."];
  _options = options;
}

- (BOOL)isRecording {
  return (_videoWriter && _videoWriter.isRecording);
}

- (void)_alert:(NSString *)message {
  UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil message:message delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
  [alertView show];
}

- (BOOL)start:(NSError **)error {  
  if ([[QUtils machine] hasPrefix:@"iPhone5"] && [UIScreen mainScreen].bounds.size.height <= 480) {
    [self _alert:@"Recording only works with full size app on iPhone 5."];
    return NO;
  }
  
#if TARGET_IPHONE_SIMULATOR
  UIWindow *window = [QUIWindow window];
  if (!window) {
    [NSException raise:QException format:@"No window for recording has been setup. This probably means you are using the simulator and no QUIWindow has been constructed. See documentation for help on setting up the QUIWindow."];
  }
  QUIViewRecorder *viewRecoder = [[QUIViewRecorder alloc] initWithView:window size:window.frame.size];
#else
  QSpringBoardRecorder *viewRecoder = [[QSpringBoardRecorder alloc] init];
#endif
    
  _videoWriter = [[QVideoWriter alloc] initWithRecordable:viewRecoder options:_options];
    
  if ([_videoWriter start:error]) {
    [[NSNotificationCenter defaultCenter] postNotificationName:QRecorderDidStartNotification object:self];
    return YES;
  }
  return NO;
}

- (void)_stopForUnregistered {
  [self stop:nil];
}

- (BOOL)stop:(NSError **)error {
  BOOL stopped = [_videoWriter stop:error];
  [[NSNotificationCenter defaultCenter] postNotificationName:QRecorderDidStopNotification object:self];
  return stopped;
}

- (void)saveVideoToAlbumWithResultBlock:(QRecorderSaveResultBlock)resultBlock failureBlock:(QRecorderSaveFailureBlock)failureBlock {
  return [_videoWriter saveToAlbumWithName:_albumName resultBlock:resultBlock failureBlock:failureBlock];
}

- (void)saveVideoToAlbumWithName:(NSString *)name resultBlock:(QRecorderSaveResultBlock)resultBlock failureBlock:(QRecorderSaveFailureBlock)failureBlock {
  return [_videoWriter saveToAlbumWithName:name resultBlock:resultBlock failureBlock:failureBlock];
}

- (BOOL)discardVideo:(NSError **)error {
  return [_videoWriter discard:error];
}

#pragma mark Delegates (QUIWindow)

- (void)_onEvent:(NSNotification *)notification {
  UIEvent *event = [notification object];
  if ([_videoWriter isRecording]) {
    //[_eventRecorder recordEvent:event];
    [_videoWriter setEvent:event];
  }
}

@end
