#pragma once

#include "NewbornTerrainDatabase.hpp"
#include "NewbornPerlin.hpp"

namespace Newborn {

struct PerlinSelector : TerrainSelector {
  static char const* const Name;

  PerlinSelector(Json const& config, TerrainSelectorParameters const& parameters);

  float get(int x, int y) const override;

  PerlinF function;

  float xInfluence;
  float yInfluence;
};

}
