#include "NewbornScriptPane.hpp"
#include "NewbornRoot.hpp"
#include "NewbornAssets.hpp"
#include "NewbornGuiReader.hpp"
#include "NewbornJsonExtra.hpp"
#include "NewbornConfigLuaBindings.hpp"
#include "NewbornPlayerLuaBindings.hpp"
#include "NewbornStatusControllerLuaBindings.hpp"
#include "NewbornCelestialLuaBindings.hpp"
#include "NewbornLuaGameConverters.hpp"
#include "NewbornWorldClient.hpp"
#include "NewbornPlayer.hpp"
#include "NewbornUniverseClient.hpp"
#include "NewbornWidgetLuaBindings.hpp"
#include "NewbornInterfaceLuaBindings.hpp"
#include "NewbornCanvasWidget.hpp"
#include "NewbornItemTooltip.hpp"
#include "NewbornItemGridWidget.hpp"
#include "NewbornSimpleTooltip.hpp"
#include "NewbornImageWidget.hpp"

namespace Newborn {

ScriptPane::ScriptPane(UniverseClientPtr client, Json config, EntityId sourceEntityId) : BaseScriptPane(config) {
  auto& root = Root::singleton();
  auto assets = root.assets();

  m_client = std::move(client);
  m_sourceEntityId = sourceEntityId;

  m_script.addCallbacks("player", LuaBindings::makePlayerCallbacks(m_client->mainPlayer().get()));
  m_script.addCallbacks("status", LuaBindings::makeStatusControllerCallbacks(m_client->mainPlayer()->statusController()));
  m_script.addCallbacks("celestial", LuaBindings::makeCelestialCallbacks(m_client.get()));
}

void ScriptPane::displayed() {
  auto world = m_client->worldClient();
  if (world && world->inWorld()) {
    m_script.setLuaRoot(world->luaRoot());
    m_script.addCallbacks("world", LuaBindings::makeWorldCallbacks(world.get()));
  }
  BaseScriptPane::displayed();
}

void ScriptPane::dismissed() {
  BaseScriptPane::dismissed();
  m_script.removeCallbacks("world");
}

void ScriptPane::tick(float dt) {
  if (m_sourceEntityId != NullEntityId && !m_client->worldClient()->playerCanReachEntity(m_sourceEntityId))
    dismiss();

  BaseScriptPane::tick(dt);
}

PanePtr ScriptPane::createTooltip(Vec2I const& screenPosition) {
  auto result = m_script.invoke<Json>("createTooltip", screenPosition);
  if (result && !result.value().isNull()) {
    if (result->type() == Json::Type::String) {
      return SimpleTooltipBuilder::buildTooltip(result->toString());
    } else {
      PanePtr tooltip = make_shared<Pane>();
      m_reader->construct(*result, tooltip.get());
      return tooltip;
    }
  } else {
    ItemPtr item;
    if (auto child = getChildAt(screenPosition)) {
      if (auto itemSlot = as<ItemSlotWidget>(child))
        item = itemSlot->item();
      if (auto itemGrid = as<ItemGridWidget>(child))
        item = itemGrid->itemAt(screenPosition);
    }
    if (item)
      return ItemTooltipBuilder::buildItemTooltip(item, m_client->mainPlayer());
    return {};
  }
}

LuaCallbacks ScriptPane::makePaneCallbacks() {
  LuaCallbacks callbacks = BaseScriptPane::makePaneCallbacks();
  callbacks.registerCallback("sourceEntity", [this]() { return m_sourceEntityId; });
  return callbacks;
}

bool ScriptPane::openWithInventory() const {
  return m_config.getBool("openWithInventory", false);
}

bool ScriptPane::closeWithInventory() const {
  return m_config.getBool("closeWithInventory", openWithInventory());
}

EntityId ScriptPane::sourceEntityId() const {
  return m_sourceEntityId;
}

}
