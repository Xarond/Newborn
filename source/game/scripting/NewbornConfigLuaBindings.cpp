#include "NewbornConfigLuaBindings.hpp"
#include "NewbornJsonExtra.hpp"
#include "NewbornLuaGameConverters.hpp"

namespace Newborn {

LuaCallbacks LuaBindings::makeConfigCallbacks(function<Json(String const&, Json const&)> getParameter) {
  LuaCallbacks callbacks;

  callbacks.registerCallback("getParameter", getParameter);

  return callbacks;
}

}
