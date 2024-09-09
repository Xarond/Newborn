#pragma once

#include "NewbornPlatformServices_pc.hpp"

namespace Newborn {

NEWBORN_CLASS(SteamDesktopService);

class SteamDesktopService : public DesktopService {
public:
  SteamDesktopService(PcPlatformServicesStatePtr state);

  void openUrl(String const& url) override;
};

}
