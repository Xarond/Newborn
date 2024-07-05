#include "NewbornLuaConverters.hpp"
#include "NewbornColor.hpp"

namespace Newborn {

LuaValue LuaConverter<Color>::from(LuaEngine& engine, Color const& c) {
  if (c.alpha() == 255)
    return engine.createArrayTable(initializer_list<uint8_t>{c.red(), c.green(), c.blue()});
  else
    return engine.createArrayTable(initializer_list<uint8_t>{c.red(), c.green(), c.blue(), c.alpha()});
}

Maybe<Color> LuaConverter<Color>::to(LuaEngine& engine, LuaValue const& v) {
  if (auto t = v.ptr<LuaTable>()) {
    Color c = Color::rgba(0, 0, 0, 255);
    Maybe<int> r = engine.luaMaybeTo<int>(t->get(1));
    Maybe<int> g = engine.luaMaybeTo<int>(t->get(2));
    Maybe<int> b = engine.luaMaybeTo<int>(t->get(3));
    if (!r || !g || !b)
      return {};

    c.setRed(*r);
    c.setGreen(*g);
    c.setBlue(*b);

    if (Maybe<int> a = engine.luaMaybeTo<int>(t->get(4))) {
      if (!a)
        return {};
      c.setAlpha(*a);
    }

    return c;
  } else if (auto s = v.ptr<LuaString>()) {
    try {
      return Color(s->ptr());
    } catch (ColorException const&) {}
  }

  return {};
}

LuaValue LuaConverter<LuaCallbacks>::from(LuaEngine& engine, LuaCallbacks const& c) {
  auto table = engine.createTable(0, c.callbacks().size());
  for (auto& callback : c.callbacks())
    table.set(callback.first, engine.createWrappedFunction(callback.second));

  return table;
}

Maybe<LuaCallbacks> LuaConverter<LuaCallbacks>::to(LuaEngine&, LuaValue const&) {
  return {};
}

}
