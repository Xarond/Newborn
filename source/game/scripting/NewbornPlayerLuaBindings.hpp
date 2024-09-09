#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(Player);

namespace LuaBindings {
  LuaCallbacks makePlayerCallbacks(Player* player);
}
}
