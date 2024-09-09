#pragma once

#include "NewbornImage.hpp"
#include "NewbornWorldTiles.hpp"
#include "NewbornEntityRenderingTypes.hpp"
#include "NewbornSkyRenderData.hpp"
#include "NewbornParallax.hpp"
#include "NewbornParticle.hpp"
#include "NewbornWeatherTypes.hpp"
#include "NewbornEntity.hpp"
#include "NewbornThread.hpp"
#include "NewbornCellularLighting.hpp"

namespace Newborn {

struct EntityDrawables {
  EntityHighlightEffect highlightEffect;
  Map<EntityRenderLayer, List<Drawable>> layers;
};


struct WorldRenderData {
  void clear();

  WorldGeometry geometry;

  Vec2I tileMinPosition;
  RenderTileArray tiles;
  Vec2I lightMinPosition;
  Lightmap lightMap;

  List<EntityDrawables> entityDrawables;
  List<Particle> const* particles;

  List<OverheadBar> overheadBars;
  List<Drawable> nametags;

  List<Drawable> backgroundOverlays;
  List<Drawable> foregroundOverlays;

  List<ParallaxLayer> parallaxLayers;

  SkyRenderData skyRenderData;

  bool isFullbright = false;
  float dimLevel = 0.0f;
  Vec3B dimColor;
};

inline void WorldRenderData::clear() {
  tiles.resize({0, 0}); // keep reserved

  entityDrawables.clear();
  particles = nullptr;
  overheadBars.clear();
  nametags.clear();
  backgroundOverlays.clear();
  foregroundOverlays.clear();
  parallaxLayers.clear();
}

}
