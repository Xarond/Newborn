#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(Voice);

namespace LuaBindings {
  LuaCallbacks makeVoiceCallbacks();
}

}
