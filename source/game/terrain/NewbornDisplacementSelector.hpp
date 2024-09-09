#pragma once

#include "NewbornTerrainDatabase.hpp"
#include "NewbornPerlin.hpp"
#include "NewbornVector.hpp"

namespace Newborn {

struct DisplacementSelector : TerrainSelector {
  static char const* const Name;

  DisplacementSelector(
      Json const& config, TerrainSelectorParameters const& parameters, TerrainDatabase const* database);

  float get(int x, int y) const override;

  PerlinF xDisplacementFunction;
  PerlinF yDisplacementFunction;

  float xXInfluence;
  float xYInfluence;
  float yXInfluence;
  float yYInfluence;

  bool yClamp;
  Vec2F yClampRange;
  float yClampSmoothing;

  float clampY(float v) const;

  TerrainSelectorConstPtr m_source;
};

}
