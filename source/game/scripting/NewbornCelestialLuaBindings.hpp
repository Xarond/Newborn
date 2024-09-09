#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(Root);
NEWBORN_CLASS(UniverseClient);

namespace LuaBindings {
  LuaCallbacks makeCelestialCallbacks(UniverseClient* client);
}
}
