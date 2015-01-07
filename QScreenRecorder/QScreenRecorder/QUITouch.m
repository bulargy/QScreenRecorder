//
//  QUITouch.m
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import "QUITouch.h"

@implementation QUITouch

- (id)initWithPoint:(CGPoint)point {
  if ((self = [super init])) {
    _point = point;
    _time = [NSDate timeIntervalSinceReferenceDate];
  }
  return self;
}

@end
