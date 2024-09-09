#pragma once

#include "NewbornStatusTypes.hpp"

namespace Newborn {

NEWBORN_CLASS(StatusEffectItem);

class StatusEffectItem {
public:
  virtual ~StatusEffectItem() {}
  virtual List<PersistentStatusEffect> statusEffects() const = 0;
};

}
