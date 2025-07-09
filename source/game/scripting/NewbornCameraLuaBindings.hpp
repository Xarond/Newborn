#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(WorldCamera);

namespace LuaBindings {
  LuaCallbacks makeCameraCallbacks(WorldCamera* camera);
}
}
