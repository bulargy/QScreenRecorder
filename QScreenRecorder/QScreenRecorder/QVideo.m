//
//  QVideo.m
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import "QVideo.h"
#import "QDefines.h"
#import "QUtils.h"
#import <AVFoundation/AVFoundation.h>

@interface QVideo ()
@property (readwrite) CMTime presentationTimeStart;
@property (readwrite) CMTime presentationTimeStop;
@property (strong) NSURL *recordingFileURL;
@property (strong) NSURL *assetURL;
@end

@implementation QVideo

- (id)init {
  if ((self = [super init])) {
    _presentationTimeStart = kCMTimeNegativeInfinity;
    _presentationTimeStop = kCMTimeNegativeInfinity;
  }
  return self;
}

- (NSTimeInterval)timeInterval {
  if (CMTIME_IS_NEGATIVE_INFINITY(_presentationTimeStart)) return -1;
  if (CMTIME_IS_NEGATIVE_INFINITY(_presentationTimeStop)) return -1;
  return (NSTimeInterval)(CMTimeGetSeconds(_presentationTimeStop) - CMTimeGetSeconds(_presentationTimeStart));
}

- (NSURL *)recordingFileURL:(NSError **)error {
  if (!self.recordingFileURL) {
    NSString *tempFile = [QUtils cr_temporaryFile:@"output.mp4" deleteIfExists:YES error:error];
    if (!tempFile) {
      QSetError(error, 0, @"Can't create temp video file.");
      return nil;
    }
    QDebug(@"File: %@", tempFile);
    self.recordingFileURL = [NSURL fileURLWithPath:tempFile];
  }
  return self.recordingFileURL;
}

- (BOOL)start {
  if (_status != QVideoStatusNone) return NO;
  [self setStatus:QVideoStatusStarted];
  return YES;
}

- (BOOL)startSessionWithPresentationTime:(CMTime)presentationTime {
  if (_status != QVideoStatusStarted) return NO;
  _presentationTimeStart = presentationTime;
  return YES;
}

- (BOOL)stopWithPresentationTime:(CMTime)presentationTime {
  if (_status != QVideoStatusStarted) return NO;
  _presentationTimeStop = presentationTime;
  [self setStatus:QVideoStatusStopped];
  return YES;
}

- (void)setStatus:(QVideoStatus)status {
  _status = status;
  [[NSNotificationCenter defaultCenter] postNotificationName:QVideoDidChangeNotification object:self];
}

- (void)saveToAlbumWithName:(NSString *)name resultBlock:(QRecorderSaveResultBlock)resultBlock failureBlock:(QRecorderSaveFailureBlock)failureBlock {
  if (_status == QVideoStatusNone) {
    if (failureBlock) failureBlock([QUtils cr_errorWithDomain:QErrorDomain code:QErrorCodeInvalidVideo localizedDescription:@"No recording to save."]);
    return;
  }
  
  if (_status == QVideoStatusStarted) {
    if (failureBlock) failureBlock([QUtils cr_errorWithDomain:QErrorDomain code:QErrorCodeInvalidState localizedDescription:@"You must stop recording to save the video."]);
    return;
  }
  
  if (_status == QVideoStatusSaving) {
    if (failureBlock) failureBlock([QUtils cr_errorWithDomain:QErrorDomain code:QErrorCodeInvalidState localizedDescription:@"Video is saving."]);
    return;
  }
  
  if (_status == QVideoStatusDiscarded) {
    if (failureBlock) failureBlock([QUtils cr_errorWithDomain:QErrorDomain code:QErrorCodeInvalidVideo localizedDescription:@"Video has been discarded."]);
    return;
  }
  
  self.assetURL = nil;
  [self setStatus:QVideoStatusSaving];
  
  ALAssetsLibrary *library = [QVideo sharedAssetsLibrary];
  
  [library writeVideoAtPathToSavedPhotosAlbum:self.recordingFileURL completionBlock:^(NSURL *assetURL, NSError *error) {
    if (error) {
      [self setStatus:QVideoStatusStopped];
      if (failureBlock) failureBlock(error);
      return;
    }
    self.assetURL = assetURL;
    
    if (name) {
      [self _findOrCreateAlbumWithName:name resultBlock:^(ALAssetsGroup *group) {
        [library assetForURL:assetURL resultBlock:^(ALAsset *asset) {
          QDebug(@"Adding asset to group: %@ (editable=%d)", group, group.isEditable);
          if (![group addAsset:asset]) {
            QWarn(@"Failed to add asset to group");
          }
          QDebug(@"Saved to album: %@", asset);
          [self setStatus:QVideoStatusSaved];
          if (resultBlock) resultBlock(assetURL);
        } failureBlock:^(NSError *error) {
          [self setStatus:QVideoStatusStopped];
          if (failureBlock) failureBlock(error);
        }];
      } failureBlock:^(NSError *error) {
        [self setStatus:QVideoStatusStopped];
        if (failureBlock) failureBlock(error);
      }];
    } else {
      [self setStatus:QVideoStatusSaved];
      if (resultBlock) resultBlock(assetURL);
    }
  }];
}

- (BOOL)discard:(NSError **)error {
  if (_status == QVideoStatusNone) {
    return YES;
  }
  
  if (!self.recordingFileURL) {
    return YES;
  }
  
  if (_status == QVideoStatusStarted) {
    QSetError(error, QErrorCodeInvalidState, @"You must stop recording to save the video.");
    return NO;
  }
  
  if (_status == QVideoStatusSaving) {
    QSetError(error, QErrorCodeInvalidState, @"Video is saving.");
    return NO;
  }
  
  NSString *filePath = [self.recordingFileURL absoluteString];
  BOOL success = YES;
  if ([QUtils cr_exist:filePath]) {
    success = [[NSFileManager defaultManager] removeItemAtPath:filePath error:error];
  }
  self.recordingFileURL = nil;
  [self setStatus:QVideoStatusDiscarded];
  return success;
}

+ (ALAssetsLibrary *)sharedAssetsLibrary {
  static dispatch_once_t pred = 0;
  static ALAssetsLibrary *library = nil;
  dispatch_once(&pred, ^{
    library = [[ALAssetsLibrary alloc] init];
  });
  return library;
}

- (void)_findOrCreateAlbumWithName:(NSString *)name resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock {
  
  ALAssetsLibrary *library = [QVideo sharedAssetsLibrary];
  
  __block BOOL foundAlbum = NO;
  [library enumerateGroupsWithTypes:ALAssetsGroupAlbum usingBlock:^(ALAssetsGroup *group, BOOL *stop) {
    if ([name compare:[group valueForProperty:ALAssetsGroupPropertyName]] == NSOrderedSame) {
      QDebug(@"Found album: %@ (%@)", name, group);
      foundAlbum = YES;
      *stop = YES;
      if (resultBlock) resultBlock(group);
      return;
    }
    
    // When group is nil its the end of the enumeration
    if (!group && !foundAlbum) {
      QDebug(@"Creating album: %@", name);
      [library addAssetsGroupAlbumWithName:name resultBlock:resultBlock failureBlock:failureBlock];
    }
  } failureBlock:failureBlock];
}

@end
