#pragma once

#include "NewbornLua.hpp"
#include "NewbornBehaviorState.hpp"

namespace Newborn {

NEWBORN_CLASS(Root);
NEWBORN_CLASS(UniverseClient);

namespace LuaBindings {
  LuaCallbacks makeBehaviorLuaCallbacks(List<BehaviorStatePtr>* list);
}
}
