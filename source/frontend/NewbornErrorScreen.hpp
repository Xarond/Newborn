#pragma once

#include "NewbornVector.hpp"
#include "NewbornString.hpp"
#include "NewbornInterfaceCursor.hpp"
#include "NewbornInputEvent.hpp"

namespace Newborn {

NEWBORN_CLASS(Pane);
NEWBORN_CLASS(PaneManager);
NEWBORN_CLASS(GuiContext);

NEWBORN_CLASS(ErrorScreen);

class ErrorScreen {
public:
  ErrorScreen();

  // Resets accepted
  void setMessage(String const& message);

  bool accepted();

  void render(bool useBackdrop = false);

  bool handleInputEvent(InputEvent const& event);
  void update(float dt);

private:
  void renderCursor();

  float interfaceScale() const;
  unsigned windowHeight() const;
  unsigned windowWidth() const;

  GuiContext* m_guiContext;
  PaneManagerPtr m_paneManager;
  PanePtr m_errorPane;

  bool m_accepted;
  Vec2I m_cursorScreenPos;
  InterfaceCursor m_cursor;
};

}
