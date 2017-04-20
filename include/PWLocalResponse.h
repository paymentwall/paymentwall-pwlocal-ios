//
//  PWLocalResponse.h
//  PWLocalSDK
//
//  Created by Cong Tran on 6/15/15.
//  Copyright (c) 2015 Paymentwall. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(int, PWLocalResponseCode) {
    PWLOCAL_SUCCESSFUL,
    PWLOCAL_FAILED,
    PWLOCAL_CANCELED
};

extern NSString *const PWLOCAL_PAYMENT_SUCCESSFUL;
extern NSString *const PWLOCAL_PAYMENT_FAIL;
extern NSString *const PWLOCAL_PAYMENT_CANCELED;

@interface PWLocalResponse : NSObject

@property (nonatomic, assign) PWLocalResponseCode code;
@property (nonatomic, strong) NSString *message;

@end
