#pragma once

#include "NewbornPane.hpp"
#include "NewbornWarping.hpp"
#include "NewbornPlayerUniverseMap.hpp"
#include "NewbornBookmarkInterface.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(PaneManager);

class TeleportDialog : public Pane {
public:
  TeleportDialog(UniverseClientPtr client,
      PaneManager* paneManager,
      Json config,
      EntityId sourceEntityId,
      TeleportBookmark currentLocation);

  void tick(float dt) override;

  void selectDestination();
  void teleport();
  void editBookmark();

private:
  EntityId m_sourceEntityId;
  UniverseClientPtr m_client;
  PaneManager* m_paneManager;
  List<pair<WarpAction, bool>> m_destinations;
  TeleportBookmark m_currentLocation;
};

}
