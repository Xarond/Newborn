#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(TeamClient);

namespace LuaBindings {
  LuaCallbacks makeTeamClientCallbacks(TeamClient* teamClient);
}
}