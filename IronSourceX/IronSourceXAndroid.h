//  IronSourceXAndroid.h
//  Iron Source Cocos2dx SDK
//
// Created by Andrey Pirskiy.
//

#pragma once
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
# include <jni.h>
#endif
#include <cocos2d.h>
#include "ForwardDeclare.h"

namespace iron {
    class IronSourceXAndroid {
    private:
        static bool s_bInited;

        /* Here will be the instance stored. */
        static IronSourceXAndroid *instance;

        /* Private constructor to prevent instancing. */
        IronSourceXAndroid();

    public:

        static IronSourceXAndroid *getInstance();

        static void setAdaptersDebug(bool bDebug);
        static void setIsInited(bool bInited);
        static bool isInited();
        static bool init(std::string_view key);
        static void onPause();
        static void onResume();
        static void setUserId(std::string_view userId);
        static void validateIntegration();
        static bool isVideoAdAvailable();
        static void loadVideoAd();
        static bool showVideoAd();
        static bool showVideoAd(std::string_view placement);
    };
} // namespace iron

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXInitializationCallback_onInitializationCompleteNative
    (JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdOpenedNative
    (JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdClosedNative
    (JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAvailabilityChangedNative
    (JNIEnv* env, jobject thiz, bool isAvailable);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdStartedNative
    (JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdEndedNative
    (JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdRewardedNative
    (JNIEnv *env, jobject thiz, jstring placement, jstring reward, int amount);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdShowFailedNative
    (JNIEnv *env, jobject thiz, jstring error);
JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdClickedNative
    (JNIEnv *env, jobject thiz, jstring placement);
}
#endif
