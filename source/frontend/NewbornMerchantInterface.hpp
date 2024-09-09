#pragma once

#include "NewbornWorldClient.hpp"
#include "NewbornPane.hpp"

namespace Newborn {

NEWBORN_CLASS(WorldClient);
NEWBORN_CLASS(ItemBag);
NEWBORN_CLASS(ItemGridWidget);
NEWBORN_CLASS(ListWidget);
NEWBORN_CLASS(TextBoxWidget);
NEWBORN_CLASS(ButtonWidget);
NEWBORN_CLASS(LabelWidget);
NEWBORN_CLASS(TabSetWidget);

NEWBORN_CLASS(MerchantPane);

class MerchantPane : public Pane {
public:
  MerchantPane(WorldClientPtr worldClient, PlayerPtr player, Json const& settings, EntityId sourceEntityId = NullEntityId);

  void displayed() override;
  void dismissed() override;
  PanePtr createTooltip(Vec2I const& screenPosition) override;

  EntityId sourceEntityId() const;

  ItemPtr addItems(ItemPtr const& items);

protected:
  void update(float dt) override;

private:
  void swapSlot();

  void buildItemList();
  void setupWidget(WidgetPtr const& widget, Json const& itemConfig);
  void updateSelection();
  int itemPrice();
  void updateBuyTotal();
  void buy();

  void updateSellTotal();
  void sell();

  int maxBuyCount();
  void countChanged();
  void countTextChanged();

  WorldClientPtr m_worldClient;
  PlayerPtr m_player;
  EntityId m_sourceEntityId;
  Json m_settings;

  GameTimer m_refreshTimer;

  JsonArray m_itemList;
  size_t m_selectedIndex;
  ItemPtr m_selectedItem;

  float m_buyFactor;
  int m_buyTotal;
  float m_sellFactor;
  int m_sellTotal;

  TabSetWidgetPtr m_tabSet;
  ListWidgetPtr m_itemGuiList;
  TextBoxWidgetPtr m_countTextBox;
  LabelWidgetPtr m_buyTotalLabel;
  ButtonWidgetPtr m_buyButton;
  LabelWidgetPtr m_sellTotalLabel;
  ButtonWidgetPtr m_sellButton;

  ItemGridWidgetPtr m_itemGrid;
  ItemBagPtr m_itemBag;

  int m_buyCount;
};

}
