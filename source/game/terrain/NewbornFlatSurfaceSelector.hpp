#pragma once

#include "NewbornTerrainDatabase.hpp"

namespace Newborn {

struct FlatSurfaceSelector : TerrainSelector {
  static char const* const Name;

  FlatSurfaceSelector(Json const& config, TerrainSelectorParameters const& parameters);

  float get(int x, int y) const override;

  float surfaceLevel;
  float adjustment;
  float flip;
};

}
