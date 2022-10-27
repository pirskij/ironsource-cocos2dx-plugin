//  IronSourceXAndroid.cpp
//  Iron Source Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <util/helpers/android/AndroidHelper.h>
#include "IronSourceXAndroid.h"
#include "IronSourceX.h"

using namespace iron;

bool IronSourceXAndroid::s_bInited = false;

namespace {
    static bool s_bIsVideoAdAvailable = false;
    static bool s_bIsRewardedVideoCallbackInitialized = false;

    /*
 * Get application context
 *  */
    cocos2d::JniMethodInfo _getContext()
    {
        cocos2d::JniMethodInfo jmiGetContext;
        if (!cocos2d::JniHelper::getStaticMethodInfo(jmiGetContext,
                                                    "org/cocos2dx/lib/Cocos2dxActivity",
                                                    "getContext", "()Landroid/content/Context;"))
        {
            CCLOGERROR("%s", "IronSourceXAndroid::_getContext() - Can`t get application context");
        }
        return jmiGetContext;
    }

    /*
 * Get Iron Source any static method
 *  */
    cocos2d::JniMethodInfo _getIronSourceStaticMethod(const char* method, const char* params)
    {
        cocos2d::JniMethodInfo jmiStaticMethod;

        if (!cocos2d::JniHelper::getStaticMethodInfo(jmiStaticMethod,
                                                     "com/ironsource/mediationsdk/IronSource",
                                                     method, params))
        {
            CCLOGERROR("IronSourceXAndroid::_getIronSourceStaticMethod() - Unable to get static method: %s with params: %s", method, params);
        }

        return jmiStaticMethod;
    }

    bool _registerRewardedVideoCallback()
    {
        if (s_bIsRewardedVideoCallbackInitialized)
            return true;

        cocos2d::JniMethodInfo jmiInit;
        // get 'new IronSource2dXRewardedVideoCallback()'
        if (!cocos2d::JniHelper::getMethodInfo(jmiInit,
                                               "com/ironsource/mediationsdk/sdk/IronSource2dXRewardedVideoCallback",
                                               "<init>", "()V")) {
            CCLOGERROR("%s", "IronSourceXAndroid::registerRewardedVideoCallback() - Can`t get IronSource2dXRewardedVideoCallback create method");
            return s_bIsRewardedVideoCallbackInitialized;
        }

        // instance of 'new IronSource2dXRewardedVideoCallback()'
        auto jCallbackProxy = jmiInit.env->NewObject(jmiInit.classID, jmiInit.methodID);

        auto jmiSetListener = _getIronSourceStaticMethod("setRewardedVideoListener",
                                                         "(Lcom/ironsource/mediationsdk/sdk/RewardedVideoListener;)V");
        jmiSetListener.env->CallStaticVoidMethod(jmiSetListener.classID, jmiSetListener.methodID, jCallbackProxy);

        jmiInit.env->DeleteLocalRef(jCallbackProxy);
        jmiInit.env->DeleteLocalRef(jmiInit.classID);
        jmiSetListener.env->DeleteLocalRef(jmiSetListener.classID);

        s_bIsRewardedVideoCallbackInitialized = true;

        return s_bIsRewardedVideoCallbackInitialized;
    }
}

void IronSourceXAndroid::setAdaptersDebug(bool bDebug)
{
    auto jmiTmp = _getIronSourceStaticMethod("setAdaptersDebug", "(Z)V");

    jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID, bDebug);

    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);
}

void IronSourceXAndroid::setIsInited(bool bInited)
{
    s_bInited = bInited;
}

bool IronSourceXAndroid::isInited()
{
    return s_bInited;
}

bool IronSourceXAndroid::init(std::string_view key)
{
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto jmiInit = _getIronSourceStaticMethod("init",
                                              "(Landroid/app/Activity;Ljava/lang/String;Lcom/ironsource/mediationsdk/sdk/InitializationListener;)V");

    auto jstrKey = jmiInit.env->NewStringUTF(key.data());

    cocos2d::JniMethodInfo jmiCreateListener;
    // get 'new IronSource2dXRewardedVideoCallback()'
    if (!cocos2d::JniHelper::getMethodInfo(jmiCreateListener,
                                           "com/ironsource/mediationsdk/sdk/IronSource2dXInitializationCallback",
                                           "<init>", "()V")) {
        CCLOGERROR("%s", "IronSourceXAndroid::init() - Can`t get IronSource2dXInitializationCallback create method");
    }

    // instance of 'new IronSource2dXInitializationCallback()'
    auto jCallbackProxy = jmiCreateListener.env->NewObject(jmiCreateListener.classID, jmiCreateListener.methodID);

    jmiInit.env->CallStaticVoidMethod(jmiInit.classID, jmiInit.methodID, joContext, jstrKey, jCallbackProxy);

    jmiCreateListener.env->DeleteLocalRef(jCallbackProxy);
    jmiCreateListener.env->DeleteLocalRef(jmiCreateListener.classID);
    jmiInit.env->DeleteLocalRef(jstrKey);
    jmiInit.env->DeleteLocalRef(jmiInit.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);

    return _registerRewardedVideoCallback();
}

void IronSourceXAndroid::onPause()
{
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto jmiTmp = _getIronSourceStaticMethod("onPause", "(Landroid/app/Activity;)V");

    jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID, joContext);

    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

void IronSourceXAndroid::onResume()
{
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto jmiTmp = _getIronSourceStaticMethod("onResume", "(Landroid/app/Activity;)V");

    jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID, joContext);

    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

void IronSourceXAndroid::setUserId(std::string_view userId)
{
    auto jmiTmp = _getIronSourceStaticMethod("setUserId", "(Ljava/lang/String;)V");

    auto jstrUserId = jmiTmp.env->NewStringUTF(userId.data());

    if (jstrUserId != nullptr)
        jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID, jstrUserId);

    jmiTmp.env->DeleteLocalRef(jstrUserId);
    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);
}

void IronSourceXAndroid::validateIntegration()
{
    cocos2d::JniMethodInfo jmiTmp;
    if (!cocos2d::JniHelper::getStaticMethodInfo(jmiTmp,
                                           "com/ironsource/mediationsdk/integration/IntegrationHelper",
                                           "validateIntegration", "(Landroid/app/Activity;)V")) {
        CCLOGERROR("%s", "IronSourceXAndroid::validateIntegration() - Can`t get validateIntegration method");
        return;
    }

    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID, joContext);

    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

bool IronSourceXAndroid::isVideoAdAvailable()
{
    if (!s_bIsVideoAdAvailable) {

        auto jmiTmp = _getIronSourceStaticMethod("isRewardedVideoAvailable", "()Z");

        s_bIsVideoAdAvailable = jmiTmp.env->CallStaticBooleanMethod(jmiTmp.classID, jmiTmp.methodID);

        jmiTmp.env->DeleteLocalRef(jmiTmp.classID);
    }
    return s_bIsVideoAdAvailable;
}

void IronSourceXAndroid::loadVideoAd()
{
    auto jmiTmp = _getIronSourceStaticMethod("loadRewardedVideo", "()V");

    jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID);

    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);
}

bool IronSourceXAndroid::showVideoAd()
{
    if (!_registerRewardedVideoCallback())
        return false;

    auto jmiTmp = _getIronSourceStaticMethod("showRewardedVideo", "()V");

    jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID);

    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);

    return true;
}

bool IronSourceXAndroid::showVideoAd(std::string_view placement)
{
    if (placement.empty())
        return showVideoAd();

    if (!_registerRewardedVideoCallback())
        return false;

    auto jmiTmp = _getIronSourceStaticMethod("showRewardedVideo", "(Ljava/lang/String;)V");


    auto jstrPlacement = jmiTmp.env->NewStringUTF(placement.data());

    jmiTmp.env->CallStaticVoidMethod(jmiTmp.classID, jmiTmp.methodID, jstrPlacement);

    jmiTmp.env->DeleteLocalRef(jstrPlacement);
    jmiTmp.env->DeleteLocalRef(jmiTmp.classID);

    return true;
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXInitializationCallback_onInitializationCompleteNative
    (JNIEnv *env, jobject thiz)
    {
        CCLOG("%s","IronSourceXAndroid::onInitializationCompleteNative is called");

        iron::IronSourceXAndroid::setIsInited(true);

        if (IronSourceX::getCallbacks().onInitedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
                IronSourceX::getCallbacks().onInitedClb();
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdOpenedNative
    (JNIEnv *env, jobject thiz)
    {
        CCLOG("%s","IronSourceXAndroid::onRewardedVideoAdOpenedNative is called");

        if (IronSourceX::getCallbacks().onVideoAdOpenedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
                IronSourceX::getCallbacks().onVideoAdOpenedClb();
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdClosedNative
    (JNIEnv *env, jobject thiz)
    {
        CCLOG("%s","IronSourceXAndroid::onRewardedVideoAdClosedNative is called");

        if (IronSourceX::getCallbacks().onVideoAdClosedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
                IronSourceX::getCallbacks().onVideoAdClosedClb();
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAvailabilityChangedNative
    (JNIEnv* env, jobject thiz, bool isAvailable)
    {
        CCLOG("%s %s","IronSourceXAndroid::onRewardedVideoAvailabilityChangedNative is called - isAvailable =", isAvailable ? "TRUE" : "FALSE");

        s_bIsVideoAdAvailable = isAvailable;

        if (IronSourceX::getCallbacks().onVideoAvailabilityChangedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([isAvailable]() {
                IronSourceX::getCallbacks().onVideoAvailabilityChangedClb(isAvailable);
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdStartedNative
    (JNIEnv *env, jobject thiz)
    {
        CCLOG("%s","IronSourceXAndroid::onRewardedVideoAdStartedNative is called");

        if (IronSourceX::getCallbacks().onVideoAdStartedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
                IronSourceX::getCallbacks().onVideoAdStartedClb();
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdEndedNative
    (JNIEnv *env, jobject thiz)
    {
        CCLOG("%s","IronSourceXAndroid::onRewardedVideoAdEndedNative is called");

        if (IronSourceX::getCallbacks().onVideoAdEndedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
                IronSourceX::getCallbacks().onVideoAdEndedClb();
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdRewardedNative
    (JNIEnv *env, jobject thiz, jstring placement, jstring reward, int amount)
    {
        auto strPlace = cocos2d::JniHelper::jstring2string(placement);
        auto strReward = cocos2d::JniHelper::jstring2string(reward);

        CCLOG("%s%s - REWARD:%s = %d","IronSourceXAndroid::onRewardedVideoAdRewardedNative is called - PLACE:", strPlace.c_str(), strReward.c_str(), amount);

        if (IronSourceX::getCallbacks().onVideoAdRewardedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([strPlace, strReward, amount]() {
                IronSourceX::getCallbacks().onVideoAdRewardedClb(strPlace, strReward, amount);
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdShowFailedNative
    (JNIEnv *env, jobject thiz, jstring error)
    {
        auto strTmp = cocos2d::JniHelper::jstring2string(error);

        CCLOG("%s %s","IronSourceXAndroid::onRewardedVideoAdShowFailedNative is called - MSG:", strTmp.c_str());

        if (IronSourceX::getCallbacks().onVideoAdShowFailedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([strTmp]() {
                IronSourceX::getCallbacks().onVideoAdShowFailedClb(strTmp);
            });
        }
    }

    JNIEXPORT void JNICALL Java_com_ironsource_mediationsdk_sdk_IronSource2dXRewardedVideoCallback_onRewardedVideoAdClickedNative
    (JNIEnv *env, jobject thiz, jstring placement)
    {
        auto strTmp = cocos2d::JniHelper::jstring2string(placement);

        CCLOG("%s %s","IronSourceXAndroid::onRewardedVideoAdClickedNative is called - PLACE:", strTmp.c_str());

        if (IronSourceX::getCallbacks().onVideoAdClickedClb)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([strTmp]() {
                IronSourceX::getCallbacks().onVideoAdClickedClb(strTmp);
            });
        }
    }
}
#endif
