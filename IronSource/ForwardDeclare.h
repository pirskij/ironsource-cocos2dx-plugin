#pragma once

#include <functional>

namespace iron
{
	using OnInitializationCompletedClb = std::function<void()>;
	using OnRewardedVideoAdOpenedClb = std::function<void()>;
	using OnRewardedVideoAdClosedClb = std::function<void()>;
	using OnRewardedVideoAvailabilityChangedClb = std::function<void(bool)>;
	using OnRewardedVideoAdStartedClb = std::function<void()>;
	using OnRewardedVideoAdEndedClb = std::function<void()>;
	using OnRewardedVideoAdRewardedClb = std::function<void(std::string_view, std::string_view, int)>;
	using OnRewardedVideoAdShowFailedClb = std::function<void(std::string_view)>;
	using OnRewardedVideoAdClickedClb = std::function<void(std::string_view)>;

	struct IronSourceXCallbacks
	{
		OnInitializationCompletedClb onInitedClb;
		OnRewardedVideoAdOpenedClb onVideoAdOpenedClb;
		OnRewardedVideoAdClosedClb onVideoAdClosedClb;
		OnRewardedVideoAvailabilityChangedClb onVideoAvailabilityChangedClb;
		OnRewardedVideoAdStartedClb onVideoAdStartedClb;
		OnRewardedVideoAdEndedClb onVideoAdEndedClb;
		OnRewardedVideoAdRewardedClb onVideoAdRewardedClb;
		OnRewardedVideoAdShowFailedClb onVideoAdShowFailedClb;
		OnRewardedVideoAdClickedClb onVideoAdClickedClb;
	};
} // namespace iron
