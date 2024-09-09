#pragma once

#include "NewbornLruCache.hpp"
#include "NewbornPerlin.hpp"
#include "NewbornTerrainDatabase.hpp"

namespace Newborn {

struct IslandColumn {
  float topLevel;
  float bottomLevel;
};

struct IslandSurfaceSelector : TerrainSelector {
  static char const* const Name;

  IslandSurfaceSelector(Json const& config, TerrainSelectorParameters const& parameters);

  float get(int x, int y) const override;

  IslandColumn generateColumn(int x) const;

  mutable HashLruCache<int, IslandColumn> columnCache;

  PerlinF islandHeight;
  PerlinF islandDepth;
  PerlinF islandDecision;

  float islandTaperPoint;
  float islandElevation;

  float layerBaseHeight;
  int worldWidth;
};

}
