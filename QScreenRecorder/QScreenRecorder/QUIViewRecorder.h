//
//  QUIViewRecorder.h
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QRecordable.h"

/*!
 Recorder for a UIView.
 */
@interface QUIViewRecorder : NSObject <QRecordable> {
  UIView *_view;
  CGSize _size;
}

/*!
 Create UIView recorder of size.
 @param view View
 @param size Size
 */
- (id)initWithView:(UIView *)view size:(CGSize)size;

@end
