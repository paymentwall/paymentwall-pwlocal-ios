# PWLocal iOS SDK
## Introduction
Do you need to have an ability to accept payments from mobile users in different countries, considering which payment methods  fit best? PWLocal is a global payment gateway that makes it easy to accept payments from customers in more than 200 countries with 100+ alternative payment options. 
PWLocal iOS SDK will become a native part of your application, it eliminates the necessity to open a web browser for payments, as a result you will receive a higher conversions rate.
All you have to do is import the library into your iOS project and start using our SDK to accept in-app payments. It is quick and easy! We'll guide you through the process here.

## How does it work ?	
1. The customer clicks on the **Buy** button inside your application.
2. The PWLocal SDK is called at this moment and opens application dialog with the list of payment systems.
3. User chooses a payment system and clicks on **Buy**. After it, a new application dialog opens. It would be a "thank you" screen or a dialog for providing payment details, such as credit card number, if needed.
4. The payment is completed and your callback function is triggered to handle its result. Your backend will be also notified about it.

## Credentials
Your mobile integration requires a Project key.  
You can obtain these Paymentwall API credentials in the application settings of your Merchant Account at [Paymentwall](https://www.paymentwall.com/)

## Add SDK to your project
### Manually:
1. In the menubar click "File" then "Add file to YOUR_PROJECT".
2. Select the "PWLocalSDK" directory in the downloaded repository.
3. Make sure 'Copy items into destination group's folder (if needed)' is checked.
4. Click "Add"
5. Click on your project, in Targets tab click in "Build Settings"
6. In the "Header Search Paths" add link to include file of SDK such as "$SOURCE_ROOT/PWLocalSDK/include"
7. In the "Library Search Paths" add link to file "libPWLocalSDK.a"

### With Cocoapods:
1. Add `pod 'PWLocalSDK'` into your podfile
2. Run `pod install` in your terminal
3. If you are using Swift : Create a `Project-Bridging-Header.h` and add it in your Build settings's `Objective-C Bridging Header`

## Accepting your first payment
### Import
###### Objective-C
```objective-c
#import "PWLocalSDK.h"
```
###### Swift
Add this command to your `Bridging-Header.h` file

```objective-c
#import "PWLocalSDK.h"
```

### Create PWLocal request
We have 4 types of PWLocal payment request: `VirtualCurrency`, `DigitalGoodsDefautWidget`, `DigitalGoodsFlexibleWidget` and `CartDefaultWidget`
We support 3 API type: `VIRTUAL_CURRENCY`, `DIGITAL_GOODS_FLEXIBLE`, `DIGITAL_GOODS_DEFAULT`, `CART`
For more information, please refer to:
https://www.paymentwall.com/en/documentation/Digital-Goods-API/710
#### Defined request
We defined 4 types request: `VirtualCurrency`, `DigitalGoodsDefautWidget`, `DigitalGoodsFlexibleWidget` and `CartDefaultWidget`. You can simply use setters to set required parameters. Please note that all the parameters are changed from under_score to camelCase format.
##### Example
###### Objective-C
```objective-c
DigitalGoodsDefautWidget *digitalGoodsdefaultWidget = [DigitalGoodsDefautWidget new];
digitalGoodsdefaultWidget.key = PROJECT_KEY;
digitalGoodsdefaultWidget.uid = USER_ID;
digitalGoodsdefaultWidget.widget = WIDGET_TYPE;
```
###### Swift
```swift
let digitalGoodsdefaultWidget = DigitalGoodsDefautWidget()
digitalGoodsdefaultWidget.key = PROJECT_KEY
digitalGoodsdefaultWidget.uid = USER_ID
digitalGoodsdefaultWidget.widget = WIDGET_TYPE
```
#### Custom request
If our defined request does not match your need. We also supported NSDictionary with key and value you can handler it by yourself. It follows the parameters in https://www.paymentwall.com/en/documentation/Digital-Goods-API/710
##### Example
###### Objective-C
```objective-c
NSMutableDictionary *customSetting = [NSMutableDictionary new];
[customSetting setObject: PROJECT_KEY forKey:@"key"];
[customSetting setObject: USER_ID forKey:@"uid"];
[customSetting setObject: WIDGET_TYPE forKey:@"widget"];
```
###### Swift
```swift
var customSetting = [String: String]()
customSetting["key"] = PROJECT_KEY
customSetting["uid"] = USER_ID
customSetting["widget"] = WIDGET_TYPE
```
### Start PWLocal dialog
#### Defined request
###### Objective-C
```objective-c
[PWLocalSDK showPWLocalViewControllerWithViewController:self
                                               delegate:self
                                                   type:DIGITAL_GOODS_FLEXIBLE
                                                 params:digitalGoodsdefaultWidget
                                              secretKey:SECRET_KEY];
```
###### Swift
```swift
PWLocalSDK.showPWLocalViewController(with: self,
                                     delegate: self,
                                     type: .DIGITAL_GOODS_FLEXIBLE,
                                     params: digitalGoodsdefaultWidget,
                                     secretKey: SECRET_KEY)
```

#### Custom request
###### Objective-C
```objective-c
[PWLocalSDK showPWLocalViewControllerWithViewController:self
                                               delegate:self
                                                   type:DIGITAL_GOODS_FLEXIBLE
                                                 params:customSetting
                                              secretKey:SECRET_KEY];
```
###### Swfit
```swift
PWLocalSDK.showPWLocalViewController(with: self,
                                     delegate: self,
                                     type: .DIGITAL_GOODS_FLEXIBLE,
                                     params: customSetting,
                                     secretKey: SECRET_KEY)
```

#### Custom signing
Storing `secretKey` on your own backend lower your risk of exposing it. Signing your request remotely is recommended to secure your project. You can use this method to get the complete sorted string, you will only need to add secret key at the end to calculate the signature, `params` can be Dictionary or any of the pre-made class:

###### Objective-C
```objective-c
NSString *stringToSign = [PWLocalSDK getStringToSign:params];
```

###### Swift
```swift
let stringToSign = PWLocalSDK.getStringToSign(params)
```
>Note:  Param `"success_url"="pwlocal://paymentsuccessful"` is added by default by this function if your `params` doesn't have it included, if you use your own webView, track this value to close your webView

#### Extra headers
Please note that if you want to use your own webview to show the widget, there are few extra headers you have to add to your request, use this method to get them and add to your mutable request with `[request setValue:value forHTTPHeaderField:key]`:

###### Objective-C
```objective-c
NSDictionary *extra = [PWLocalSDK getExtraHeaders];
```

###### Swift
```swift
let extra = PWLocalSDK.getExtraHeaders()
```

### Handle result
You have to add PWLocalSDKDelegate to your ViewController
###### Objective-C
```objective-c
@interface YourViewController : UIViewController <PWLocalSDKDelegate>
```
###### Swift
```swift
class YourViewController: UIViewController, PWLocalSDKDelegate
```
You can handle payment results by defining your callback function. We recommend syncing up with your server  at this point to sync up user's balance, confirm purchased item etc. See the example:

###### Objective-C
```objective-c
#pragma mark - PWLocal Response
-(void)pwLocalResponse:(PWLocalResponse *)response {
    switch (response.code) {
        case PWLOCAL_SUCCESSFUL:
            break;
        case PWLOCAL_FAILED:
            break;
        case PWLOCAL_CANCELED:
            break;
        default:
            break;
    }
}
```
###### Swift
```swift
// MARK: - PWLocal Response
func pwLocalResponse(response: PWLocalResponse!) {
        switch response.code {
        case .PWLOCAL_SUCCESSFUL:
            break
        case .PWLOCAL_CANCELED:
            break
        case .PWLOCAL_FAILED:
            break
        }
}
```

`response.code` code can have one of the following values:

`PWLOCAL_SUCCESSFUL `: the user has completed the payment

`PWLOCAL_CANCELED `: the user has aborted the payment

`PWLOCAL_FAILED `: the payment cannot be done due to some error:
- Network error
- Invalid supplying request

## Payment Status API utils
Our SDK also support [Payment Status API.](https://www.paymentwall.com/en/documentation/Payment-Status-API/3019)
### Get payment status
#### Unsigned call
###### Objective-C
```objective-c
#pragma mark - PWLocal Get Payment Status
[PWLocalSDK checkPaymentStatusWithKey:PROJECT_KEY
                         agExternalId:A_EXTERNAL_ID
                                  uid:UID
                          signVersion:0
                         andSecretKey:@""
                           completion:^(PWLocalStatusResponse *response) {
                               if(response.code == PWLOCAL_STAUTS_SUCCESSFUL) {
                                   if(response.dataResponse.count > 0)
                                        PaymentStatus *paymentStatus = response.dataResponse.firstObject;
                                   }
                               }
                               else
                                   NSLog(@"%@", response.message);
                           }];
```
###### Swift
```swift
// MARK: - PWLocal Get Payment Status
PWLocalSDK.checkPaymentStatusWithKey(PROJECT_KEY, agExternalId: A_EXTERNAL_ID, uid: UID, signVersion: 0, andSecretKey: "", completion: {
            (response) -> Void in
            
        })
```
#### Signed call
###### Objective-C
```objective-c
#pragma mark - PWLocal Get Payment Status
[PWLocalSDK checkPaymentStatusWithKey:PROJECT_KEY
                         agExternalId:A_EXTERNAL_ID
                                  uid:UID
                          signVersion:SIGN_VERSION
                         andSecretKey:SECRET_KEY
                           completion:^(PWLocalStatusResponse *response) {
                               if(response.code == PWLOCAL_STAUTS_SUCCESSFUL) {
                                   if(response.dataResponse.count > 0)
                                        PaymentStatus *paymentStatus = response.dataResponse.firstObject;
                                   }
                               }
                               else
                                   NSLog(@"%@", response.message);
                           }];
```
###### Swift
```swift
// MARK: - PWLocal Get Payment Status
PWLocalSDK.checkPaymentStatusWithKey(PROJECT_KEY, agExternalId: A_EXTERNAL_ID, uid: UID, signVersion: SIGN_VERSION, andSecretKey: SECRET_KEY, completion: {
            (response) -> Void in
            
        })
```

## Server notification handling
After each successful payment we will notify your server about it. We recommend to use this feature as it is the most reliable way to know when the payment went through. Even if your application crashes for some reason, your server will still be notified, so you can sync up later.
Please use [pingback processing documentation](https://www.paymentwall.com/en/documentation/Digital-Goods-API/710#pingback_processing) for more information. 
## Appendix
### Supported parameters
Here's the list of supported parameters in defined requests
#### Parameters of VirtualCurrency
<table><tbody><tr><td><strong>Data type</strong></td><td><strong>Parameter</strong></td></tr><tr><td>NSString</td><td>key</td></tr><tr><td>NSString</td><td>uid</td></tr><tr><td>NSString</td><td>widget</td></tr><tr><td>NSString</td><td>ps</td></tr><tr><td> NSString </td><td>sign_version</td></tr><tr><td>NSString</td><td>birthday</td></tr><tr><td>NSString</td><td>email</td></tr><tr><td>NSString</td><td>sex</td></tr><tr><td>NSString</td><td>evaluation</td></tr><tr><td>NSString</td><td>location_city</td></tr><tr><td>NSString</td><td>location_state</td></tr><tr><td>NSString</td><td>location_address</td></tr><tr><td>NSString</td><td>location_country</td></tr><tr><td>NSString</td><td>location_zip</td></tr><tr><td>NSString</td><td>country_code</td></tr><tr><td>NSString</td><td>rv</td></tr><tr><td>NSString</td><td>th</td></tr><tr><td>NSString</td><td>tm</td></tr><tr><td>NSString</td><td>pingback_url</td></tr><tr><td>NSString</td><td>success_url</td></tr></tbody></table>

#### Parameters of DigitalGoodsDefautWidget
<table><tbody><tr><td><strong>Data type</strong></td><td><strong>Parameter</strong></td></tr><tr><td>NSString</td><td>key</td></tr><tr><td>NSString</td><td>uid</td></tr><tr><td>NSString</td><td>widget</td></tr><tr><td>NSString</td><td>ps</td></tr><tr><td> NSString </td><td>ts</td></tr><tr><td> NSString </td><td>sign_version</td></tr><tr><td>NSString</td><td>birthday</td></tr> <tr><td>NSString</td><td>country_code</td></tr> <tr><td>NSString</td><td>email</td></tr><tr><td>NSString</td><td>sex</td></tr><tr><td>NSString</td><td>evaluation</td></tr><tr><td>NSString</td><td>firstname</td></tr><tr><td>NSString</td><td>lang</td></tr><tr><td>NSString</td><td>lastname</td></tr><tr><td>NSString</td><td>location_city</td></tr><tr><td>NSString</td><td>location_state</td></tr><tr><td>NSString</td><td>location_address</td></tr><tr><td>NSString</td><td>location_country</td></tr><tr><td>NSString</td><td>location_zip</td></tr><tr><td>NSString</td><td>default_goodsid</td></tr><tr><td>NSString</td><td>display_goodsid</td></tr><tr><td>NSArray</td><td>hide_goodsid</td></tr><tr><td>NSString</td><td>pingback_url</td></tr><tr><td>NSString</td><td>success_url</td></tr></tbody></table>

#### Parameters of DigitalGoodsFlexibleWidget
<table><tbody><tr><td><strong>Data type</strong></td><td><strong>Parameter</strong></td></tr><tr><td>NSString</td><td>key</td></tr><tr><td>NSString</td><td>uid</td></tr><tr><td>NSString</td><td>widget</td></tr><tr><td>NSString</td><td>amount</td></tr><tr><td>NSString</td><td>currencyCode</td></tr><tr><td>NSString</td><td>ps</td></tr><tr><td> NSString </td><td>ts</td></tr><tr><td> NSString </td><td>ag_name</td></tr><tr><td> NSString </td><td>ag_external_id</td></tr><tr><td> NSString </td><td>ag_type</td></tr><tr><td> NSString </td><td>ag_period_length</td></tr><tr><td> NSString </td><td>ag_period_type</td></tr><tr><td> NSString </td><td>ag_recurring</td></tr><tr><td> NSString </td><td>ag_promo</td></tr><tr><tr><td> NSString </td><td>ag_trial</td></tr> <tr><td> NSString </td><td>ag_post_trial_period_length</td></tr><tr><td> NSString </td><td>ag_post_trial_period_type</td></tr> <tr><td> NSString </td><td>ag_post_trial_external_id</td></tr><tr><td> NSString </td><td>post_trial_amount</td></tr><tr><td> NSString </td><td>post_trial_currencyCode</td></tr><tr><td> NSString </td><td>ag_post_trial_name</td></tr><tr><td> NSString </td><td>hide_post_trial_good</td></tr><tr><td> NSString </td><td>sign_version</td></tr><tr><td>NSString</td><td>birthday</td></tr> <tr><td>NSString</td><td>country_code</td></tr> <tr><td>NSString</td><td>email</td></tr><tr><td>NSString</td><td>sex</td></tr><tr><td>NSString</td><td>evaluation</td></tr><tr><td>NSString</td><td>firstname</td></tr><tr><td>NSString</td><td>lang</td></tr><tr><td>NSString</td><td>lastname</td></tr><tr><td>NSString</td><td>location_city</td></tr><tr><td>NSString</td><td>location_state</td></tr><tr><td>NSString</td><td>location_address</td></tr><tr><td>NSString</td><td>location_country</td></tr><tr><td>NSString</td><td>location_zip</td></tr><tr><td>NSString</td><td>show_trial_non_recurring</td></tr><tr><td>NSString</td><td>show_trial_recurring</td></tr><tr><td>NSString</td><td>show_post_trial_non_recurring</td></tr><tr><td>NSString</td><td>show_post_trial_recurring</td></tr><tr><td>NSString</td><td>pingback_url</td></tr><tr><td>NSString</td><td>success_url</td></tr></tbody></table>

#### Parameters of CartDefaultWidget
<table><tbody><tr><td><strong>Data type</strong></td><td><strong>Parameter</strong></td></tr><tr><td>NSString</td><td>key</td></tr><tr><td>NSString</td><td>uid</td></tr><tr><td>NSString</td><td>widget</td></tr><tr><td>NSString</td><td>external_ids</td></tr><tr><td>NSString</td><td>prices</td></tr><tr><td>NSString</td><td>currencies</td></tr><tr><td>NSString</td><td>firstname</td></tr><tr><td>NSString</td><td>lastname</td></tr><tr><td> NSString </td><td>sign_version</td></tr><tr><td>NSString</td><td>birthday</td></tr><tr><td>NSString</td><td>email</td></tr><tr><td>NSString</td><td>sex</td></tr><tr><td>NSString</td><td>evaluation</td></tr><tr><td>NSString</td><td>location_city</td></tr><tr><td>NSString</td><td>location_state</td></tr><tr><td>NSString</td><td>location_address</td></tr><tr><td>NSString</td><td>location_country</td></tr><tr><td>NSString</td><td>location_zip</td></tr><tr><td>NSString</td><td>pingback_url</td></tr></tbody></table>

