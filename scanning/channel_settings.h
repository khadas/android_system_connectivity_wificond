/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WIFICOND_SCANNING_CHANNEL_SETTINGS_H_
#define WIFICOND_SCANNING_CHANNEL_SETTINGS_H_

#include <binder/Parcel.h>
#include <binder/Parcelable.h>

namespace android {
namespace net {
namespace wifi {
namespace wificond {

class ChannelSettings : public ::android::Parcelable {
 public:
  ChannelSettings()
      : frequency_(0) {}
  bool operator==(const ChannelSettings& rhs) const {
    return frequency_ == rhs.frequency_;
  }
  ::android::status_t writeToParcel(::android::Parcel* parcel) const override;
  ::android::status_t readFromParcel(const ::android::Parcel* parcel) override;

  int32_t frequency_;
};

}  // namespace wificond
}  // namespace wifi
}  // namespace net
}  // namespace android

#endif  // WIFICOND_SCANNING_CHANNEL_SETTINGS_H_