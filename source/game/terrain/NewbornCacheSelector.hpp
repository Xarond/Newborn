#pragma once

#include "NewbornTerrainDatabase.hpp"
#include "NewbornLruCache.hpp"
#include "NewbornVector.hpp"

namespace Newborn {

struct CacheSelector : TerrainSelector {
  static char const* const Name;

  CacheSelector(Json const& config, TerrainSelectorParameters const& parameters, TerrainDatabase const* database);

  float get(int x, int y) const override;

  TerrainSelectorConstPtr m_source;
  mutable HashLruCache<Vec2I, float> m_cache;
};

}
