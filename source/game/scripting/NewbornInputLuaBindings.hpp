#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(Input);

namespace LuaBindings {
  LuaCallbacks makeInputCallbacks();
}

}
