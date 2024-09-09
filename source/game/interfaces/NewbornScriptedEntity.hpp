#pragma once

#include "NewbornEntity.hpp"
#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(ScriptedEntity);

// All ScriptedEntity methods should only be called on master entities
class ScriptedEntity : public virtual Entity {
public:
  // Call a script function directly with the given arguments, should return
  // nothing only on failure.
  virtual Maybe<LuaValue> callScript(String const& func, LuaVariadic<LuaValue> const& args) = 0;

  // Execute the given code directly in the underlying context, return nothing
  // on failure.
  virtual Maybe<LuaValue> evalScript(String const& code) = 0;
};

}
