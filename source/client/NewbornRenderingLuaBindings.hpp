#pragma once

#include "NewbornLua.hpp"

namespace Newborn {
  
NEWBORN_CLASS(ClientApplication);

namespace LuaBindings {
  LuaCallbacks makeRenderingCallbacks(ClientApplication* app);
}

}
