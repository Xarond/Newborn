#pragma once

#include "NewbornPane.hpp"

namespace Newborn {

NEWBORN_CLASS(PopupInterface);
class PopupInterface : public Pane {
public:
  PopupInterface();

  virtual ~PopupInterface() {}

  void displayMessage(String const& message, String const& title, String const& subtitle, Maybe<String> const& onShowSound = {});

private:
};

}
