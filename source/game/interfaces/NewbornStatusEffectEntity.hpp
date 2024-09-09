#pragma once

#include "NewbornEntity.hpp"

namespace Newborn {

NEWBORN_CLASS(StatusEffectEntity);

class StatusEffectEntity : public virtual Entity {
public:
  virtual List<PersistentStatusEffect> statusEffects() const = 0;
  virtual PolyF statusEffectArea() const = 0;
};

}
