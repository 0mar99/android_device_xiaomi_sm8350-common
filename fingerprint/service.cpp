/*
 * Copyright (C) 2017 The Android Open Source Project
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

#define LOG_TAG "android.hardware.biometrics.fingerprint@2.1-service.xiaomi_sm8350"

#include <android/log.h>
#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include <android/hardware/biometrics/fingerprint/2.1/IBiometricsFingerprint.h>
#include <android/hardware/biometrics/fingerprint/2.1/types.h>
#include "BiometricsFingerprint.h"

using android::hardware::biometrics::fingerprint::V2_1::IBiometricsFingerprint;
using android::hardware::biometrics::fingerprint::V2_1::implementation::BiometricsFingerprint;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;
#ifdef USE_EXTENSION
using vendor::xiaomi::hardware::fingerprintextension::V1_0::IXiaomiFingerprint;
#endif

int main() {
    android::sp<IBiometricsFingerprint> biometricsFingerprint = BiometricsFingerprint::getInstance();
#ifdef USE_EXTENSION
    android::sp<IXiaomiFingerprint> xiaomiFingerprint = BiometricsFingerprint::getInstance();
#endif

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (biometricsFingerprint != nullptr) {
        if (::android::OK != biometricsFingerprint->registerAsService()) {
            return 1;
        }
    } else {
        ALOGE("Can't create instance of BiometricsFingerprint, nullptr");
    }

#ifdef USE_EXTENSION
    if (xiaomiFingerprint != nullptr) {
        if (::android::OK != xiaomiFingerprint->registerAsService()) {
            return 1;
        }
    } else {
        ALOGE("Can't create instance of XiaomiFingerprint, nullptr");
    }
#endif

    joinRpcThreadpool();

    return 0; // should never get here
}
