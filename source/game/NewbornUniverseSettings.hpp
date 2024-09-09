#pragma once

#include "NewbornThread.hpp"
#include "NewbornJson.hpp"
#include "NewbornUuid.hpp"
#include "NewbornGameTypes.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseSettings);

struct PlaceDungeonFlagAction {
  String dungeonId;
  String targetInstance;
  Vec2I targetPosition;
};

typedef MVariant<PlaceDungeonFlagAction> UniverseFlagAction;

UniverseFlagAction parseUniverseFlagAction(Json const& json);

class UniverseSettings {
public:
  UniverseSettings();
  UniverseSettings(Json const& json);

  Json toJson() const;

  Uuid uuid() const;
  StringSet flags() const;
  void setFlag(String const& flag);
  Maybe<List<UniverseFlagAction>> pullPendingFlagActions();
  List<UniverseFlagAction> currentFlagActions() const;
  List<UniverseFlagAction> currentFlagActionsForInstanceWorld(String const& instanceName) const;
  void resetFlags();

private:
  void loadFlagActions();

  mutable Mutex m_lock;

  Uuid m_uuid;
  StringSet m_flags;

  StringMap<List<UniverseFlagAction>> m_flagActions;
  List<UniverseFlagAction> m_pendingFlagActions;
};

}
