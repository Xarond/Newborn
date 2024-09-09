#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

namespace LuaBindings {
  LuaCallbacks makeConfigCallbacks(function<Json(String const&, Json const&)> getParameter);
}
}
