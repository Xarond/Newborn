#pragma once

#include "NewbornLua.hpp"
#include "NewbornPoly.hpp"
#include "NewbornColor.hpp"

namespace Newborn {

NEWBORN_CLASS(NetworkedAnimator);

namespace LuaBindings {
  LuaCallbacks makeNetworkedAnimatorCallbacks(NetworkedAnimator* networkedAnimator);
}

}
