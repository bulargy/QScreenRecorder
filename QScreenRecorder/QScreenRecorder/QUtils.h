//
//  QUtils.h
//  CaptureRecord
//
//  Created by Jolin He on 14-1-2.
//  Copyright (c) 2014年 Jolin He. All rights reserved.
//
//
#import <Foundation/Foundation.h>

@interface QUtils : NSObject
+ (NSString *)cr_rot13:(NSString *)str;
+ (BOOL)cr_exist:(NSString *)filePath;
+ (NSString *)cr_temporaryFile:(NSString *)appendPath deleteIfExists:(BOOL)deleteIfExists error:(NSError **)error;
+ (NSError *)cr_errorWithDomain:(NSString *)domain code:(NSInteger)code localizedDescription:(NSString *)localizedDescription;
+ (NSString *)machine;
@end

void QDispatch(dispatch_block_t block);
void QDispatchAfter(NSTimeInterval seconds, dispatch_block_t block);