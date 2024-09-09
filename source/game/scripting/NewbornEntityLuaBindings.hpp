#pragma once

#include "NewbornLua.hpp"
#include "NewbornEntity.hpp"

namespace Newborn {

namespace LuaBindings {
  LuaCallbacks makeEntityCallbacks(Entity const* entity);

  namespace EntityCallbacks {
    EntityId id(Entity const* entity);
    LuaTable damageTeam(Entity const* entity, LuaEngine& engine);
    bool isValidTarget(Entity const* entity, EntityId entityId);
    Vec2F distanceToEntity(Entity const* entity, EntityId entityId);
    bool entityInSight(Entity const* entity, EntityId entityId);
  }
}
}
