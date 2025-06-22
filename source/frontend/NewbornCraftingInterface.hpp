#pragma once

#include "NewbornWorldPainter.hpp"
#include "NewbornWorldClient.hpp"
#include "NewbornItemRecipe.hpp"
#include "NewbornPane.hpp"

namespace Newborn {

NEWBORN_CLASS(WorldClient);
NEWBORN_CLASS(PlayerBlueprints);
NEWBORN_CLASS(ListWidget);
NEWBORN_CLASS(TextBoxWidget);
NEWBORN_CLASS(ButtonWidget);
NEWBORN_CLASS(LabelWidget);
NEWBORN_CLASS(AudioInstance);

NEWBORN_CLASS(CraftingPane);

class CraftingPane : public Pane {
public:
  CraftingPane(
      WorldClientPtr worldClient, PlayerPtr player, Json const& settings, EntityId sourceEntityId = NullEntityId);

  void displayed() override;
  void dismissed() override;
  PanePtr createTooltip(Vec2I const& screenPosition) override;

  EntityId sourceEntityId() const;

private:
  void upgradeTable();

  List<ItemRecipe> determineRecipes();

  virtual void update(float dt) override;
  void updateCraftButtons();
  void updateAvailableRecipes();
  bool consumeIngredients(ItemRecipe& recipe, int count);
  void stopCrafting();
  void toggleCraft();
  void craft(int count);
  void countChanged();
  void countTextChanged();
  int maxCraft();
  void setupList(WidgetPtr widget, ItemRecipe const& recipe);
  ItemRecipe recipeFromSelectedWidget() const;
  void setupWidget(WidgetPtr const& widget, ItemRecipe const& recipe, HashMap<ItemDescriptor, uint64_t> const& normalizedBag);

  PanePtr setupTooltip(ItemRecipe const& recipe);

  size_t itemCount(List<ItemPtr> const& store, ItemDescriptor const& item);

  WorldClientPtr m_worldClient;
  PlayerPtr m_player;
  PlayerBlueprintsPtr m_blueprints;

  bool m_crafting;
  GameTimer m_craftTimer;
  AudioInstancePtr m_craftingSound;
  int m_count;
  List<ItemRecipe> m_recipes;
  BiHashMap<ItemRecipe, WidgetPtr> m_recipesWidgetMap; // maps ItemRecipe to guiList WidgetPtrs

  ListWidgetPtr m_guiList;
  TextBoxWidgetPtr m_textBox;
  ButtonWidgetPtr m_filterHaveMaterials;
  size_t m_displayedRecipe;

  StringSet m_filter;

  int m_maxSpinCount;

  int m_recipeAutorefreshCooldown;

  HashMap<ItemDescriptor, ItemPtr> m_itemCache;

  EntityId m_sourceEntityId;
  Json m_settings;

  Maybe<ItemRecipe> m_upgradeRecipe;
};

}
