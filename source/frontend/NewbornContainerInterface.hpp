#pragma once

#include "NewbornPane.hpp"
#include "NewbornLuaComponents.hpp"
#include "NewbornContainerInteractor.hpp"
#include "NewbornGuiReader.hpp"

namespace Newborn {

NEWBORN_CLASS(ContainerEntity);
NEWBORN_CLASS(Player);
NEWBORN_CLASS(WorldClient);
NEWBORN_CLASS(Item);
NEWBORN_CLASS(ItemGridWidget);
NEWBORN_CLASS(ItemBag);
NEWBORN_CLASS(ContainerPane);

class ContainerPane : public Pane {
public:
  ContainerPane(WorldClientPtr worldClient, PlayerPtr player, ContainerInteractorPtr containerInteractor);

  void displayed() override;
  void dismissed() override;
  PanePtr createTooltip(Vec2I const& screenPosition) override;

  bool giveContainerResult(ContainerResult result);

protected:
  void update(float dt) override;

private:
  enum class ExpectingSwap {
    None,
    Inventory,
    SwapSlot,
    SwapSlotStack
  };

  void swapSlot(ItemGridWidget* grid);
  void startCrafting();
  void stopCrafting();
  void toggleCrafting();
  void clear();
  void burn();

  WorldClientPtr m_worldClient;
  PlayerPtr m_player;
  ContainerInteractorPtr m_containerInteractor;
  ItemBagPtr m_itemBag;

  ExpectingSwap m_expectingSwap;

  GuiReader m_reader;

  Maybe<LuaWorldComponent<LuaUpdatableComponent<LuaBaseComponent>>> m_script;
};

}
