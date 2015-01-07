//
//  QRecorder.h
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//
#import "QVideoWriter.h"
#import "QDefines.h"

/*!
 The QRecorder records the screen, user input and audio.
 */
@interface QRecorder : NSObject {
  QVideoWriter *_videoWriter;
  QRecorderOptions _options;
  NSString *_albumName;
}

/*!
 The album name for the camera roll, where videos are saved. 
 Defaults to nil, the default Camera Roll.
 */
@property (strong) NSString *albumName;

/*!
 @result Recorder.
 */
+ (QRecorder *)sharedRecorder;

/*!
 Start the recording.
 @param error Out error
 @result YES if started succesfully, NO otherwise
 */
- (BOOL)start:(NSError **)error;

/*!
 Stop the recording.
 @param error Out error
 @result YES if started succesfully, NO otherwise
*/
- (BOOL)stop:(NSError **)error;

/*!
 @result YES if recording, NO otherwise
 */
- (BOOL)isRecording;

/*!
 Set recording options. Throws an exception if recording is in progress.
 @param options Recording options
 @exception QException If recording, an exception is thrown.
 */
- (void)setOptions:(QRecorderOptions)options;

/*!
 Save the video to the camera roll.
 
 Video can only be saved if it exists; the writer was started and stopped.
 
 @param resultBlock After successfully saving the video
 @param failureBlock If there is a failure
 */
- (void)saveVideoToAlbumWithResultBlock:(QRecorderSaveResultBlock)resultBlock failureBlock:(QRecorderSaveFailureBlock)failureBlock;

/*!
 Save the video to the album with name.
 If the album doesn't exist, it is created.
 
 The video is also saved to the camera roll.
 
 @param name Album name
 @param resultBlock After successfully saving the video
 @param failureBlock If there is a failure
 */
- (void)saveVideoToAlbumWithName:(NSString *)name resultBlock:(QRecorderSaveResultBlock)resultBlock failureBlock:(QRecorderSaveFailureBlock)failureBlock;

/*!
 Discard the video.
 @param error Out error
 @result YES if discarded, NO if there was an error
 */
- (BOOL)discardVideo:(NSError **)error;

@end
