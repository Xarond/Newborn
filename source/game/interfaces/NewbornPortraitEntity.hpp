#pragma once

#include "NewbornDrawable.hpp"
#include "NewbornEntity.hpp"

namespace Newborn {

NEWBORN_CLASS(PortraitEntity);

class PortraitEntity : public virtual Entity {
public:
  virtual List<Drawable> portrait(PortraitMode mode) const = 0;
  virtual String name() const = 0;
};

}
