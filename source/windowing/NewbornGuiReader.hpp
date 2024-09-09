#pragma once

#include "NewbornWidgetParsing.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(GUIBuilderException, NewbornException);
NEWBORN_CLASS(GuiReader);

class GuiReader : public WidgetParser {
public:
  GuiReader();

protected:
  WidgetConstructResult titleHandler(String const& _unused, Json const& config);
  WidgetConstructResult paneFeatureHandler(String const& _unused, Json const& config);
  WidgetConstructResult backgroundHandler(String const& _unused, Json const& config);
};

}
