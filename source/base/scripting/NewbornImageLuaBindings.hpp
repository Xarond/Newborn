#pragma once

#include "NewbornLua.hpp"

namespace Newborn {

NEWBORN_CLASS(Image);

template <>
struct LuaConverter<Image> : LuaUserDataConverter<Image> {};

template <>
struct LuaUserDataMethods<Image> {
  static LuaMethods<Image> make();
};

}
