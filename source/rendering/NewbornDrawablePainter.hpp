#pragma once

#include "NewbornDrawable.hpp"
#include "NewbornRenderer.hpp"
#include "NewbornAssetTextureGroup.hpp"

namespace Newborn {

NEWBORN_CLASS(DrawablePainter);

class DrawablePainter {
public:
  DrawablePainter(RendererPtr renderer, AssetTextureGroupPtr textureGroup);

  void drawDrawable(Drawable const& drawable);

  void cleanup(int64_t textureTimeout);

private:
  RendererPtr m_renderer;
  AssetTextureGroupPtr m_textureGroup;
};

}
