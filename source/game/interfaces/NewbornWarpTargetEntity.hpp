#pragma once

#include "NewbornWarping.hpp"
#include "NewbornTileEntity.hpp"

namespace Newborn {

NEWBORN_CLASS(WarpTargetEntity);

class WarpTargetEntity : public virtual TileEntity {
public:
  // Foot position for things teleporting onto this entity, relative to root
  // position.
  virtual Vec2F footPosition() const = 0;
};

}
