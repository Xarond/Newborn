#pragma once

#include "NewbornLua.hpp"
#include "NewbornGuiReader.hpp"

namespace Newborn {

NEWBORN_CLASS(Widget);
NEWBORN_CLASS(CanvasWidget);

template <>
struct LuaConverter<CanvasWidgetPtr> : LuaUserDataConverter<CanvasWidgetPtr> {};

template <>
struct LuaUserDataMethods<CanvasWidgetPtr> {
  static LuaMethods<CanvasWidgetPtr> make();
};

namespace LuaBindings {
  LuaCallbacks makeWidgetCallbacks(Widget* parentWidget, GuiReaderPtr reader = {});
}

}
