//
//  QUIRecordOverlay.h
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//
#import "QUIButton.h"

@interface QUIRecordOverlay : UIView {
  QUIButton *_recordBackground;
  QUIButton *_startButton;
  //QUIButton *_pauseButton;
  //QUIButton *_resumeButton;
  QUIButton *_stopButton;
  QUIButton *_closeButton;
  
  QUIButton *_saveBackground;
  UILabel *_saveLabel;
  QUIButton *_saveButton;
  QUIButton *_discardButton;
}

@end