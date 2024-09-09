#pragma once

#include "NewbornPane.hpp"
#include "NewbornLuaComponents.hpp"
#include "NewbornGuiReader.hpp"

namespace Newborn {

NEWBORN_CLASS(CanvasWidget);
NEWBORN_CLASS(BaseScriptPane);

// A more 'raw' script pane that doesn't depend on a world being present.
// Requires a derived class to provide a Lua root.
// Should maybe move into windowing?

class BaseScriptPane : public Pane {
public:
  BaseScriptPane(Json config);

  virtual void show() override;
  void displayed() override;
  void dismissed() override;

  void tick(float dt) override;

  bool sendEvent(InputEvent const& event) override;
  
  Json const& config() const;
  Json const& rawConfig() const;

  bool interactive() const override;

  PanePtr createTooltip(Vec2I const& screenPosition) override;
  Maybe<String> cursorOverride(Vec2I const& screenPosition) override;
protected:
  virtual GuiReaderPtr reader() override;
  Json m_config;
  Json m_rawConfig;

  GuiReaderPtr m_reader;

  Map<CanvasWidgetPtr, String> m_canvasClickCallbacks;
  Map<CanvasWidgetPtr, String> m_canvasKeyCallbacks;

  bool m_interactive;

  bool m_callbacksAdded;
  LuaUpdatableComponent<LuaBaseComponent> m_script;
};

}
