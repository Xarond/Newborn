#pragma once

#include "NewbornConfig.hpp"

namespace Newborn {

NEWBORN_CLASS(ActivatableItem);

class ActivatableItem {
public:
  virtual ~ActivatableItem() {}
  virtual bool active() const = 0;
  virtual void setActive(bool active) = 0;
  virtual bool usable() const = 0;
  virtual void activate() = 0;
};

}