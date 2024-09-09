#pragma once

#include "NewbornEntityRendering.hpp"

namespace Newborn {

  NEWBORN_CLASS(RenderableItem);

  class RenderableItem {
  public:
    virtual ~RenderableItem() {}

    virtual void render(RenderCallback* renderCallback, EntityRenderLayer renderLayer) = 0;
  };

}
