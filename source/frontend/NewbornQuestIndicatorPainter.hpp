#pragma once

#include "NewbornWorldCamera.hpp"
#include "NewbornWorldClient.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(QuestIndicatorPainter);

class QuestIndicatorPainter {
public:
  QuestIndicatorPainter(UniverseClientPtr const& client);

  void update(float dt, WorldClientPtr const& world, WorldCamera const& camera);
  void render();

private:
  struct Indicator {
    Drawable render(float pixelRatio) const;

    EntityId entityId;
    Vec2F screenPos;
    String indicatorName;
    AnimationPtr animation;
  };

  UniverseClientPtr m_client;
  WorldCamera m_camera;
  Map<EntityId, Indicator> m_indicators;
};

}
