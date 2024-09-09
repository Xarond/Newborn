#pragma once

#include "NewbornTerrainDatabase.hpp"
#include "NewbornPerlin.hpp"

namespace Newborn {

struct RidgeBlocksSelector : TerrainSelector {
  static char const* const Name;

  RidgeBlocksSelector(Json const& config, TerrainSelectorParameters const& parameters);

  float get(int x, int y) const override;

  float commonality;

  float amplitude;
  float frequency;
  float bias;

  float noiseAmplitude;
  float noiseFrequency;

  PerlinF ridgePerlin1;
  PerlinF ridgePerlin2;
  PerlinF noisePerlin;
};

}
