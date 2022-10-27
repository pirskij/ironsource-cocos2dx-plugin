//  IronSourceX.h
//  Iron Source Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "IronSourceX.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "IronSourceXAndroid.h"

#define COCOS2D_DEBUG 1

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IronSourceXApple.h"
#endif

using namespace iron;

IronSourceXCallbacks IronSourceX::s_clbs;

void IronSourceX::setAdaptersDebug(bool bDebug)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IronSourceXAndroid::setAdaptersDebug(bDebug);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IronSourceXApple::setAdaptersDebug(bDebug);
#endif
}

bool IronSourceX::isInited()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return IronSourceXAndroid::isInited();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return IronSourceXApple::isInited();
#else
	return true;
#endif
}

bool IronSourceX::init(std::string_view key)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return IronSourceXAndroid::init(key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return IronSourceXApple::init(key);
#else
	return true;
#endif
}

void IronSourceX::onPause()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IronSourceXAndroid::onPause();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IronSourceXApple::onPause();
#endif
}

void IronSourceX::onResume()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IronSourceXAndroid::onResume();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IronSourceXApple::onResume();
#endif
}

void IronSourceX::setUserId(std::string_view userId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IronSourceXAndroid::setUserId(userId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IronSourceXApple::setUserId(userId);
#endif
}

void IronSourceX::validateIntegration()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IronSourceXAndroid::validateIntegration();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IronSourceXApple::validateIntegration();
#endif
}

bool IronSourceX::isVideoAdAvailable()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return IronSourceXAndroid::isVideoAdAvailable();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return IronSourceXApple::isVideoAdAvailable();
#else
	return true;
#endif
}

void IronSourceX::loadVideoAd()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IronSourceXAndroid::loadVideoAd();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IronSourceXApple::loadVideoAd();
#endif
}

bool IronSourceX::showVideoAd()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return IronSourceXAndroid::showVideoAd();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return IronSourceXApple::showVideoAd();
#else
	return true;
#endif
}

bool IronSourceX::showVideoAd(std::string_view placement)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return IronSourceXAndroid::showVideoAd(placement);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return IronSourceXApple::showVideoAd(placement);
#else
	return true;
#endif
}

void IronSourceX::setOnInitializationCompletedCallback(OnInitializationCompletedClb const& clb) noexcept
{
	s_clbs.onInitedClb = clb;
}

void IronSourceX::setOnRewardedVideoAdOpenedCallback(OnRewardedVideoAdOpenedClb const& clb) noexcept
{
	s_clbs.onVideoAdOpenedClb = clb;
}

void IronSourceX::setOnRewardedVideoAdClosedCallback(OnRewardedVideoAdClosedClb const& clb) noexcept
{
	s_clbs.onVideoAdClosedClb = clb;
}

void IronSourceX::setOnRewardedVideoAvailabilityChangedCallback(OnRewardedVideoAvailabilityChangedClb const& clb) noexcept
{
	s_clbs.onVideoAvailabilityChangedClb = clb;
}

void IronSourceX::setOnRewardedVideoAdStartedCallback(OnRewardedVideoAdStartedClb const& clb) noexcept
{
	s_clbs.onVideoAdStartedClb = clb;
}

void IronSourceX::setOnRewardedVideoAdEndedCallback(OnRewardedVideoAdEndedClb const& clb) noexcept
{
	s_clbs.onVideoAdEndedClb = clb;
}

void IronSourceX::setOnRewardedVideoAdRewardedCallback(OnRewardedVideoAdRewardedClb const& clb) noexcept
{
	s_clbs.onVideoAdRewardedClb = clb;
}

void IronSourceX::setOnRewardedVideoAdShowFailedCallback(OnRewardedVideoAdShowFailedClb const& clb) noexcept
{
	s_clbs.onVideoAdShowFailedClb = clb;
}

void IronSourceX::setOnRewardedVideoAdClickedCallback(OnRewardedVideoAdClickedClb const& clb) noexcept
{
	s_clbs.onVideoAdClickedClb = clb;
}

void IronSourceX::clearAllCallbacks() noexcept
{
	s_clbs = IronSourceXCallbacks();
}
