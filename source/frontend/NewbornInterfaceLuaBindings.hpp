#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(MainInterface);
NEWBORN_CLASS(UniverseClient);

namespace LuaBindings {
  LuaCallbacks makeInterfaceCallbacks(MainInterface* mainInterface);
  LuaCallbacks makeChatCallbacks(MainInterface* mainInterface, UniverseClient* client);
}

}
