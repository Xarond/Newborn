#pragma once

#include "NewbornGameTypes.hpp"
#include "NewbornDrawable.hpp"

namespace Newborn {

NEWBORN_CLASS(PointableItem);

class PointableItem {
public:
  virtual ~PointableItem() {}

  virtual float getAngleDir(float aimAngle, Direction facingDirection);
  virtual float getAngle(float angle);
  virtual List<Drawable> drawables() const = 0;
};

}
