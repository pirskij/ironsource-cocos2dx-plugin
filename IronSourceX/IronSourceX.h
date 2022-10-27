//
//  IronSourceX.h
//  Iron Source Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#pragma once

#include <cocos2d.h>
#include <iostream>
#include "ForwardDeclare.h"

namespace iron {
	class IronSourceX {
	public:
		static void setAdaptersDebug(bool bDebug);
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

		static void setOnInitializationCompletedCallback(OnInitializationCompletedClb const& clb) noexcept;
		static void setOnRewardedVideoAdOpenedCallback(OnRewardedVideoAdOpenedClb const& clb) noexcept;
		static void setOnRewardedVideoAdClosedCallback(OnRewardedVideoAdClosedClb const& clb) noexcept;
		static void setOnRewardedVideoAvailabilityChangedCallback(OnRewardedVideoAvailabilityChangedClb const& clb) noexcept;
		static void setOnRewardedVideoAdStartedCallback(OnRewardedVideoAdStartedClb const& clb) noexcept;
		static void setOnRewardedVideoAdEndedCallback(OnRewardedVideoAdEndedClb const& clb) noexcept;
		static void setOnRewardedVideoAdRewardedCallback(OnRewardedVideoAdRewardedClb const& clb) noexcept;
		static void setOnRewardedVideoAdShowFailedCallback(OnRewardedVideoAdShowFailedClb const& clb) noexcept;
		static void setOnRewardedVideoAdClickedCallback(OnRewardedVideoAdClickedClb const& clb) noexcept;

		static void clearAllCallbacks() noexcept;
		static IronSourceXCallbacks const& getCallbacks() noexcept { return s_clbs; }

	private:
		static IronSourceXCallbacks s_clbs;
	};
} // namespace iron
