Pod::Spec.new do |s|
  s.name         = "PWLocalSDK"
  s.version      = "2.0"
  s.summary      = "PWLocal widget for iOS."
  s.description  = "PWLocal widget for iOS, for more info, please visit https://www.paymentwall.com/en/documentation/PWLocal-iOS-SDK/3358."

  s.homepage     = "https://www.paymentwall.com/"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "tien.vu" => "tien@paymentwall.com" }
  s.platform     = :ios, "8.0"
  s.source       = { :git => "https://github.com/paymentwall/paymentwall-pwlocal-ios.git", :tag => "#{s.version}" }

  # s.source_files  = "Classes", "Classes/**/*.{h,m}"
  # s.exclude_files = "Classes/Exclude"
  # s.public_header_files = "*.h"

  s.vendored_libraries   = "libPWLocalSDK.a"
end
