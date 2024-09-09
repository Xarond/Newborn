#pragma once

#include "NewbornTerrainDatabase.hpp"

namespace Newborn {

struct ConstantSelector : TerrainSelector {
  static char const* const Name;

  ConstantSelector(Json const& config, TerrainSelectorParameters const& parameters);

  float get(int x, int y) const override;

  float m_value;
};

}
