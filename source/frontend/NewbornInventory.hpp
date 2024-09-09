#pragma once

#include "NewbornPane.hpp"
#include "NewbornInventoryTypes.hpp"
#include "NewbornItemDescriptor.hpp"
#include "NewbornPlayerTech.hpp"
#include "NewbornGameTimers.hpp"
#include "NewbornContainerInteractor.hpp"

namespace Newborn {

NEWBORN_CLASS(MainInterface);
NEWBORN_CLASS(UniverseClient);
NEWBORN_CLASS(Player);
NEWBORN_CLASS(Item);
NEWBORN_CLASS(ItemSlotWidget);
NEWBORN_CLASS(ItemGridWidget);
NEWBORN_CLASS(ImageWidget);
NEWBORN_CLASS(Widget);
NEWBORN_CLASS(InventoryPane);

class InventoryPane : public Pane {
public:
  InventoryPane(MainInterface* parent, PlayerPtr player, ContainerInteractorPtr containerInteractor);

  void displayed() override;
  PanePtr createTooltip(Vec2I const& screenPosition) override;

  bool giveContainerResult(ContainerResult result);

  // update only item grids, to see if they have had their slots changed
  // this is a little hacky and should probably be checked in the player inventory instead
  void updateItems();
  bool containsNewItems() const;
  void clearChangedSlots();

protected:
  virtual void update(float dt) override;
  void selectTab(String const& selected);

private:
  MainInterface* m_parent;
  PlayerPtr m_player;
  ContainerInteractorPtr m_containerInteractor;

  bool m_expectingSwap;
  InventorySlot m_containerSource;

  GameTimer m_trashBurn;
  ItemSlotWidgetPtr m_trashSlot;

  Map<String, ItemGridWidgetPtr> m_itemGrids;
  Map<String, String> m_tabButtonData;

  Map<String, WidgetPtr> m_newItemMarkers;
  String m_selectedTab;

  StringList m_pickUpSounds;
  StringList m_putDownSounds;
  StringList m_someUpSounds;
  StringList m_someDownSounds;
  Maybe<ItemDescriptor> m_currentSwapSlotItem;

  List<ImageWidgetPtr> m_disabledTechOverlays;
};

}
