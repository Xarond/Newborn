#pragma once

#include "NewbornString.hpp"

namespace Newborn {

NEWBORN_CLASS(EffectSourceItem);

class EffectSourceItem {
public:
  virtual ~EffectSourceItem() {}
  virtual StringSet effectSources() const = 0;
};

}
