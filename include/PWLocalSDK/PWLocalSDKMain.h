//
//  PWLocalSDK.h
//  PWLocalSDK
//
//  Created by Tien Nhat Vu on 4/18/17.
//  Copyright © 2017 Paymentwall. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class PWLocalResponse;
@class PWLocalStatusResponse;

//#define AUSTREME
#define MASON

@protocol PWLocalSDKDelegate <NSObject>

@optional
-(void) pwLocalResponse:(PWLocalResponse* _Nonnull) response;

@end

typedef NS_ENUM(int, apiType) {
    VIRTUAL_CURRENCY,
    DIGITAL_GOODS_FLEXIBLE,
    DIGITAL_GOODS_DEFAULT,
    CART
};

@interface PWLocalSDK : NSObject

/*!
 @brief Show PWLocal ViewController with params.
 @discussion The method use <b>params</b> to create request for display PWLocal payment form in webview.
 
 @param parentViewController The viewController you want to present PWLocal view controller on.
 @param delegate Set to receive response from SDK for success/fail/cancel payment.
 @param paymentType Can be VIRTUAL_CURRENCY / DIGITAL_GOODS / CART.
 @param params Can be Dictionary or any of the defined class, refer their headers for required property or [PWLocal docs]: https://www.paymentwall.com/en/documentation/Digital-Goods-API/710 "PWLocal params".
 @param secretKey Set this if you want the SDK to calculate signature for your params, It's suggest that you calculate signature by your server for more secure and leave this param nil.
 */
+(void)showPWLocalViewControllerWithViewController:(UIViewController * _Nonnull)parentViewController delegate:(id _Nullable)delegate type:(apiType)paymentType params:(id _Nonnull)params secretKey:(NSString * _Nullable)secretKey;

/**
 Check payment status, SUPPORT DIGITAL GOODS FLEXIBLE WIDGET ONLY

 @param key Public project key
 @param agExternalId Merchant's product SKU ID
 @param uid ID of the end-user in merchant's system
 @param signVersion Sign version of project
 @param secret Secret project key
 @param completionBlock Do after response fetched
 */
+(void)checkPaymentStatusWithKey:(NSString * _Nonnull) key agExternalId:(NSString* _Nonnull) agExternalId uid:(NSString* _Nonnull) uid signVersion:(int)signVersion andSecretKey:(NSString* _Nullable) secret completion:(void (^_Nullable)(PWLocalStatusResponse * _Nullable response))completionBlock;

/**
 @brief Create string to sign from your params.
 @discussion If you don't use "success_url", default will be "pwlocal://paymentsuccessful", you can track this value on your webview's "shouldStartLoadWithRequest" or similar to close webview if you decide to use your own webview.
 
 @param params Can be Dictionary or object: DigitalGoodsDefautWidget / DigitalGoodsFlexibleWidget / VirtualCurrency / CartDefaultWidget.
 @return NSString Combine this string with your secret key to calculate the signature.
 */
+(NSString *_Nonnull) getStringToSign:(id _Nonnull)params;

@end
