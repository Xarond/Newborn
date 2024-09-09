#pragma once

#include "NewbornWidget.hpp"

namespace Newborn {

// VERY simple base class for a layout container object.
class Layout : public Widget {
public:
  Layout();
  virtual void update(float dt) override;
};

}
