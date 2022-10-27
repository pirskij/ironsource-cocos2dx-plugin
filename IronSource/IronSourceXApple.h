//
//  IronSourceXApple.h
//  Iron Source Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#pragma once

#include <cocos2d.h>
#include "ForwardDeclare.h"

namespace iron {
    class IronSourceXApple {
    private:
        /* Here will be the instance stored. */
        static IronSourceXApple* s_instance;
        bool m_bInited = false;

        /* Private constructor to prevent instancing. */
        IronSourceXApple();

        void* m_delegate = nullptr;
    public:
        static IronSourceXApple* getInstance();

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
