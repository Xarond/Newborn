#pragma once

#include "NewbornLayout.hpp"

namespace Newborn {

// Super simple, only supports left to right, top to bottom flow layouts
// currently
NEWBORN_CLASS(FlowLayout);
class FlowLayout : public Layout {
public:
  FlowLayout();
  virtual void update(float dt) override;
  void setSpacing(Vec2I const& spacing);
  void setWrapping(bool wrap);

private:
  Vec2I m_spacing;
  bool m_wrap;
};

}
