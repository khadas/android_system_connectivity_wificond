/*
 * Copyright (C) 2016, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>

#include <gtest/gtest.h>

#include "wificond/scanning/channel_settings.h"
#include "wificond/scanning/hidden_network.h"
#include "wificond/scanning/single_scan_settings.h"

using ::com::android::server::wifi::wificond::ChannelSettings;
using ::com::android::server::wifi::wificond::HiddenNetwork;
using ::com::android::server::wifi::wificond::SingleScanSettings;
using std::vector;

namespace android {
namespace wificond {

namespace {

const uint8_t kFakeSsid[] =
    {'G', 'o', 'o', 'g', 'l', 'e', 'G', 'u', 'e', 's', 't'};

constexpr bool kFakeIsFullScan = false;
constexpr uint32_t kFakeFrequency = 5260;
constexpr uint32_t kFakeFrequency1 = 2460;
constexpr uint32_t kFakeFrequency2 = 2500;

}  // namespace

class ScanSettingsTest : public ::testing::Test {
};

TEST_F(ScanSettingsTest, ChannelSettingsParcelableTest) {
  ChannelSettings channel_settings;
  channel_settings.frequency_ = kFakeFrequency;

  Parcel parcel;
  EXPECT_EQ(::android::OK, channel_settings.writeToParcel(&parcel));

  ChannelSettings channel_settings_copy;
  parcel.setDataPosition(0);
  EXPECT_EQ(::android::OK, channel_settings_copy.readFromParcel(&parcel));

  EXPECT_EQ(channel_settings, channel_settings_copy);
}

TEST_F(ScanSettingsTest, HiddenNetworkParcelableTest) {
  HiddenNetwork hidden_network;
  hidden_network.ssid_ =
      vector<uint8_t>(kFakeSsid, kFakeSsid + sizeof(kFakeSsid));

  Parcel parcel;
  EXPECT_EQ(::android::OK, hidden_network.writeToParcel(&parcel));

  HiddenNetwork hidden_network_copy;
  parcel.setDataPosition(0);
  EXPECT_EQ(::android::OK, hidden_network_copy.readFromParcel(&parcel));

  EXPECT_EQ(hidden_network, hidden_network_copy);
}

TEST_F(ScanSettingsTest, SingleScanSettingsParcelableTest) {
  SingleScanSettings scan_settings;
  scan_settings.is_full_scan_ = kFakeIsFullScan;

  ChannelSettings channel, channel1, channel2;
  channel.frequency_ = kFakeFrequency;
  channel1.frequency_ = kFakeFrequency1;
  channel2.frequency_ = kFakeFrequency2;

  HiddenNetwork network;
  network.ssid_ =
      vector<uint8_t>(kFakeSsid, kFakeSsid + sizeof(kFakeSsid));

  scan_settings.channel_settings_ = {channel, channel1, channel2};
  scan_settings.hidden_networks_ = {network};

  Parcel parcel;
  EXPECT_EQ(::android::OK, scan_settings.writeToParcel(&parcel));

  SingleScanSettings scan_settings_copy;
  parcel.setDataPosition(0);
  EXPECT_EQ(::android::OK, scan_settings_copy.readFromParcel(&parcel));

  EXPECT_EQ(scan_settings, scan_settings_copy);
}

}  // namespace wificond
}  // namespace android