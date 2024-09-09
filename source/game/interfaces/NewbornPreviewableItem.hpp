#pragma once

#include "NewbornDrawable.hpp"

namespace Newborn {

NEWBORN_CLASS(Player);
NEWBORN_CLASS(PreviewableItem);

class PreviewableItem {
public:
  virtual ~PreviewableItem() {}
  virtual List<Drawable> preview(PlayerPtr const& viewer = {}) const = 0;
};

}
