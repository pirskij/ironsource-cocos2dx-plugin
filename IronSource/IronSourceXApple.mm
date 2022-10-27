//
//  IronSourceXApple.mm
//  Iron Source Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "IronSourceXApple.h"
#include "IronSourceX.h"
#import <IronSource/IronSource.h>

namespace {
    static bool s_bIsVideoAdAvailable = false;
};

using namespace iron;

@interface IronSourceXAppleDelegate: NSObject<ISInitializationDelegate,ISRewardedVideoDelegate>
@end

@implementation IronSourceXAppleDelegate

#pragma mark -ISInitializationDelegate
// Invoked after init mediation completed
- (void)initializationDidComplete {
    IronSourceXApple::setIsInited(true);
    
    if (IronSourceX::getCallbacks().onInitedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
            IronSourceX::getCallbacks().onInitedClb();
        });
    }
}

#pragma mark - ISRewardedVideoDelegate
//Called after a rewarded video has changed its availability.
//@param available The new rewarded video availability. YES if available //and ready to be shown, NO otherwise.
- (void)rewardedVideoHasChangedAvailability:(BOOL)available {
     //Change the in-app 'Traffic Driver' state according to availability.
    
    s_bIsVideoAdAvailable = available;
    
    if (IronSourceX::getCallbacks().onVideoAvailabilityChangedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
            IronSourceX::getCallbacks().onVideoAvailabilityChangedClb(s_bIsVideoAdAvailable);
        });
    }
}
// Invoked when the user completed the video and should be rewarded.
// If using server-to-server callbacks you may ignore this events and wait *for the callback from the ironSource server.
//
// @param placementInfo An object that contains the placement's reward name and amount.
//
- (void)didReceiveRewardForPlacement:(ISPlacementInfo *)placementInfo {
    std::string strPlace = [[placementInfo placementName] UTF8String];
    std::string strReward = [[placementInfo rewardName] UTF8String];
    auto amount = [[placementInfo rewardAmount] intValue];
    
    if (IronSourceX::getCallbacks().onVideoAdRewardedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([strPlace, strReward, amount]() {
            IronSourceX::getCallbacks().onVideoAdRewardedClb(strPlace, strReward, amount);
        });
    }
}
//Called after a rewarded video has attempted to show but failed.
//@param error The reason for the error
- (void)rewardedVideoDidFailToShowWithError:(NSError *)error {
    std::string strTmp = [[error localizedDescription] UTF8String];
    
    if (IronSourceX::getCallbacks().onVideoAdShowFailedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([strTmp]() {
            IronSourceX::getCallbacks().onVideoAdShowFailedClb(strTmp);
        });
    }
}
//Called after a rewarded video has been opened.
- (void)rewardedVideoDidOpen {
    if (IronSourceX::getCallbacks().onVideoAdOpenedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
            IronSourceX::getCallbacks().onVideoAdOpenedClb();
        });
    }
}
//Called after a rewarded video has been dismissed.
- (void)rewardedVideoDidClose {
    if (IronSourceX::getCallbacks().onVideoAdClosedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
            IronSourceX::getCallbacks().onVideoAdClosedClb();
        });
    }
}
//Invoked when the end user clicked on the RewardedVideo ad
- (void)didClickRewardedVideo:(ISPlacementInfo *)placementInfo {
    std::string strTmp = [[placementInfo placementName] UTF8String];

    if (IronSourceX::getCallbacks().onVideoAdClickedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([strTmp]() {
            IronSourceX::getCallbacks().onVideoAdClickedClb(strTmp);
        });
    }
}
//Note: the events DidStart & DidEnd below are not available for all supported rewarded video ad networks.
//Check which events are available per ad network you choose to include in your build.
//We recommend only using events which register to ALL ad networks you include in your build.
//Called after a rewarded video has started playing.
- (void)rewardedVideoDidStart {
    if (IronSourceX::getCallbacks().onVideoAdStartedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
            IronSourceX::getCallbacks().onVideoAdStartedClb();
        });
    }
}
//Called after a rewarded video has finished playing.
- (void)rewardedVideoDidEnd {
    if (IronSourceX::getCallbacks().onVideoAdEndedClb)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
            IronSourceX::getCallbacks().onVideoAdEndedClb();
        });
    }
}
@end

/* Null, because instance will be initialized on demand. */
IronSourceXApple* IronSourceXApple::s_instance = nullptr;

IronSourceXApple* IronSourceXApple::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new IronSourceXApple();
    }
    
    return s_instance;
}

IronSourceXApple::IronSourceXApple() {}

void IronSourceXApple::setAdaptersDebug(bool bDebug)
{
    [IronSource setAdaptersDebug: bDebug];
}

void IronSourceXApple::setIsInited(bool bInited)
{
    IronSourceXApple::getInstance()->m_bInited = bInited;
}

bool IronSourceXApple::isInited()
{
    return IronSourceXApple::getInstance()->m_bInited;
}

bool IronSourceXApple::init(std::string_view key)
{
    static dispatch_once_t onceToken;
    static IronSourceXApple* instance = nil;
    static IronSourceXAppleDelegate* delegate = nil;
    
    dispatch_once(&onceToken, ^{
        
        instance = IronSourceXApple::getInstance();
        delegate = [[IronSourceXAppleDelegate alloc] init];

        instance->m_delegate = delegate;
        /*[[NSNotificationCenter defaultCenter] addObserverForName: UIApplicationDidBecomeActiveNotification
         object: nil
         queue: nil
         usingBlock: ^ (NSNotification * note) {
         }];*/
    });

    [IronSource initWithAppKey:[NSString stringWithUTF8String:key.data()]
                       adUnits:@[IS_REWARDED_VIDEO]
                      delegate:delegate];

    [IronSource setRewardedVideoDelegate:delegate];
    
    [IronSource shouldTrackReachability:YES];

    return true;
}

void IronSourceXApple::onPause()
{
    ;
}

void IronSourceXApple::onResume()
{
    ;
}

void IronSourceXApple::setUserId(std::string_view userId)
{
    [IronSource setUserId:[NSString stringWithUTF8String:userId.data()]];
}

void IronSourceXApple::validateIntegration()
{
    [ISIntegrationHelper validateIntegration];
}

bool IronSourceXApple::isVideoAdAvailable()
{
    if (!s_bIsVideoAdAvailable)
        s_bIsVideoAdAvailable = [IronSource hasRewardedVideo];
    
    return s_bIsVideoAdAvailable;
}

void IronSourceXApple::loadVideoAd()
{
    [IronSource loadRewardedVideo];
}

bool IronSourceXApple::showVideoAd()
{
    [IronSource showRewardedVideoWithViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
    
    return true;
}

bool IronSourceXApple::showVideoAd(std::string_view placement)
{
    if (placement.empty())
        return showVideoAd();

    [IronSource showRewardedVideoWithViewController:[UIApplication sharedApplication].keyWindow.rootViewController
                                          placement:[NSString stringWithUTF8String:placement.data()]];
    
    return true;
}
