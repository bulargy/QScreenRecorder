//
//  QCameraRecorder.h
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import "QRecordable.h"
#import <AVFoundation/AVFoundation.h>

/*!
 Recorder for the front facing camera.
 */
@interface QCameraRecorder : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate, AVCaptureAudioDataOutputSampleBufferDelegate, QRecordable> {
  AVCaptureSession *_captureSession;
  AVCaptureVideoDataOutput *_videoOutput;
  AVCaptureAudioDataOutput *_audioOutput;
    
  uint8_t *_data; // Data from camera
  size_t _dataSize;
  size_t _width;
  size_t _height;
  size_t _bytesPerRow;
  
  CVImageBufferRef _imageBuffer;
  
  dispatch_queue_t _queue;
}

/*!
 The current audio writer (the microphone).
 */
@property (weak) id<QAudioWriter> audioWriter;

/*!
 The presentation time for the current data buffer.
 */
@property CMTime presentationTime;

@end
