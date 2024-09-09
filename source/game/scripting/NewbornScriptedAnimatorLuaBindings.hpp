#pragma once

#include "NewbornLua.hpp"
#include "NewbornNetworkedAnimator.hpp"

namespace Newborn {

namespace LuaBindings {
  LuaCallbacks makeScriptedAnimatorCallbacks(const NetworkedAnimator* animator, function<Json(String const&, Json const&)> getParameter);
}
}
