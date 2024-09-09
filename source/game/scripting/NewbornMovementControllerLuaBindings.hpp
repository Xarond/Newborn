#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(MovementController);

namespace LuaBindings {
  LuaCallbacks makeMovementControllerCallbacks(MovementController* movementController);
}
}
