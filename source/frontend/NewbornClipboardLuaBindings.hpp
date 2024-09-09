#pragma once

#include "NewbornLua.hpp"
#include "NewbornApplicationController.hpp"

namespace Newborn {

namespace LuaBindings {
LuaCallbacks makeClipboardCallbacks(ApplicationControllerPtr appController);
}

}// namespace Newborn
