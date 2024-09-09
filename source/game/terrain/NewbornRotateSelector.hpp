#pragma once

#include "NewbornTerrainDatabase.hpp"
#include "NewbornVector.hpp"

namespace Newborn {

struct RotateSelector : TerrainSelector {
  static char const* const Name;

  RotateSelector(Json const& config, TerrainSelectorParameters const& parameters, TerrainDatabase const* database);

  float get(int x, int y) const override;

  float rotation;
  Vec2F rotationCenter;

  TerrainSelectorConstPtr m_source;
};

}
