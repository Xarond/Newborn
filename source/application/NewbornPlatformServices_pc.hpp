#pragma once

#include "NewbornThread.hpp"
#include "NewbornApplication.hpp"
#include "NewbornStatisticsService.hpp"
#include "NewbornP2PNetworkingService.hpp"
#include "NewbornUserGeneratedContentService.hpp"
#include "NewbornDesktopService.hpp"

#ifdef NEWBORN_ENABLE_STEAM_INTEGRATION
#include "steam/steam_api.h"
#endif


#ifdef NEWBORN_ENABLE_DISCORD_INTEGRATION
#include "discord/discord.h"
#endif

namespace Newborn {

NEWBORN_CLASS(PcPlatformServices);
NEWBORN_STRUCT(PcPlatformServicesState);

struct PcPlatformServicesState {
  PcPlatformServicesState();
  ~PcPlatformServicesState();

#ifdef NEWBORN_ENABLE_STEAM_INTEGRATION
  STEAM_CALLBACK(PcPlatformServicesState, onGameOverlayActivated, GameOverlayActivated_t, callbackGameOverlayActivated);

  bool steamAvailable = false;
#endif

#ifdef NEWBORN_ENABLE_DISCORD_INTEGRATION
  bool discordAvailable = false;

  // Must lock discordMutex before accessing any of the managers when not inside
  // a discord callback.
  Mutex discordMutex;

  unique_ptr<discord::Core> discordCore;
  
  Maybe<discord::User> discordCurrentUser;
  ThreadFunction<void> discordEventThread;
  atomic<bool> discordEventShutdown;
#endif

  bool overlayActive = false;
};


class PcPlatformServices {
public:

  static PcPlatformServicesUPtr create(String const& path, StringList platformArguments);

  StatisticsServicePtr statisticsService() const;
  P2PNetworkingServicePtr p2pNetworkingService() const;
  UserGeneratedContentServicePtr userGeneratedContentService() const;
  DesktopServicePtr desktopService() const;


  bool overlayActive() const;

  void update();

private:
  PcPlatformServices() = default;

  PcPlatformServicesStatePtr m_state;

  StatisticsServicePtr m_statisticsService;
  P2PNetworkingServicePtr m_p2pNetworkingService;
  UserGeneratedContentServicePtr m_userGeneratedContentService;
  DesktopServicePtr m_desktopService;
};

}
