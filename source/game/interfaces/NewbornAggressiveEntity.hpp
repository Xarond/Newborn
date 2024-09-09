#pragma once

#include "NewbornEntity.hpp"

namespace Newborn {

NEWBORN_CLASS(AggressiveEntity);

class AggressiveEntity : public virtual Entity {
public:
  virtual bool aggressive() const = 0;
};

}
