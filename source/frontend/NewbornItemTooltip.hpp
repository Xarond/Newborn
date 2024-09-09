#pragma once

#include "NewbornString.hpp"
#include "NewbornStatusTypes.hpp"

namespace Newborn {

NEWBORN_CLASS(Item);
NEWBORN_CLASS(Widget);
NEWBORN_CLASS(ListWidget);
NEWBORN_CLASS(Augment);
NEWBORN_CLASS(Pane);
NEWBORN_CLASS(Player);

namespace ItemTooltipBuilder {
  PanePtr buildItemTooltip(ItemPtr const& item, PlayerPtr const& viewer = {});

  void buildItemDescription(WidgetPtr const& container, ItemPtr const& item);
  void buildItemDescriptionInner(
      WidgetPtr const& container, ItemPtr const& item, String const& tooltipKind, String& title, String& subtitle, PlayerPtr const& viewer = {});

  void describePersistentEffect(ListWidgetPtr const& container, PersistentStatusEffect const& effect);
};

}
