//
//  QUIViewRecorder.m
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import "QUIViewRecorder.h"
#import <QuartzCore/QuartzCore.h>

@implementation QUIViewRecorder

- (id)initWithView:(UIView *)view size:(CGSize)size {
  if ((self = [super init])) {
    _view = view;
    _size = size;
  }
  return self;
}

- (CGSize)size {
  return _size;
}

- (void)renderInContext:(CGContextRef)context videoSize:(CGSize)videoSize {
  CGContextSaveGState(context);
  CGContextConcatCTM(context, CGAffineTransformMake(1, 0, 0, -1, 0, _size.height));
  CGContextTranslateCTM(context, _view.center.x, _view.center.y);
  CGContextConcatCTM(context,  _view.transform);
  CGContextTranslateCTM(context, -_view.bounds.size.width * _view.layer.anchorPoint.x, -_view.bounds.size.height * _view.layer.anchorPoint.y);
  [_view.layer renderInContext:context];
  CGContextRestoreGState(context);
}

@end
