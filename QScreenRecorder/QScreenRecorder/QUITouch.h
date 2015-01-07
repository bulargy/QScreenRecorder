//
//  QUITouch.h
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

@interface QUITouch : NSObject

@property CGPoint point;
@property NSTimeInterval time;

- (id)initWithPoint:(CGPoint)point;

@end
