#include "NewbornDesktopService_pc_steam.hpp"

namespace Newborn {

SteamDesktopService::SteamDesktopService(PcPlatformServicesStatePtr) {}

void SteamDesktopService::openUrl(String const& url) {
  SteamFriends()->ActivateGameOverlayToWebPage(url.utf8Ptr());
}

}
