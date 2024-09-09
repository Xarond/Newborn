#pragma once

#include "NewbornConfig.hpp"

namespace Newborn {

NEWBORN_CLASS(DurabilityItem);

class DurabilityItem {
public:
  virtual ~DurabilityItem() {}
  virtual float durabilityStatus() = 0;
};

}
