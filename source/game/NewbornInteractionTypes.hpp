#pragma once

#include "NewbornGameTypes.hpp"
#include "NewbornJson.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(InteractActionException, NewbornException);

struct InteractRequest {
  EntityId sourceId;
  Vec2F sourcePosition;
  EntityId targetId;
  Vec2F interactPosition;
};

DataStream& operator>>(DataStream& ds, InteractRequest& ir);
DataStream& operator<<(DataStream& ds, InteractRequest const& ir);

enum class InteractActionType {
  None,
  OpenContainer,
  SitDown,
  OpenCraftingInterface,
  OpenSongbookInterface,
  OpenNpcCraftingInterface,
  OpenMerchantInterface,
  OpenAiInterface,
  OpenTeleportDialog,
  ShowPopup,
  ScriptPane,
  Message
};
extern EnumMap<InteractActionType> const InteractActionTypeNames;

struct InteractAction {
  InteractAction();
  InteractAction(InteractActionType type, EntityId entityId, Json data);
  InteractAction(String const& typeName, EntityId entityId, Json data);

  explicit operator bool() const;

  InteractActionType type;
  EntityId entityId;
  Json data;
};

DataStream& operator>>(DataStream& ds, InteractAction& ir);
DataStream& operator<<(DataStream& ds, InteractAction const& ir);

}
