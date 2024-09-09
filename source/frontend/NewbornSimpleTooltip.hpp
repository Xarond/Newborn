#pragma once

#include "NewbornString.hpp"

namespace Newborn {

NEWBORN_CLASS(Pane);

namespace SimpleTooltipBuilder {
  PanePtr buildTooltip(String const& text);
};

}
