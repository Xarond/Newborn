#pragma once

#include "NewbornTerrainDatabase.hpp"

namespace Newborn {

struct MinMaxSelector : TerrainSelector {
  static char const* const Name;

  MinMaxSelector(Json const& config, TerrainSelectorParameters const& parameters, TerrainDatabase const* database);

  float get(int x, int y) const override;

  List<TerrainSelectorConstPtr> m_sources;
};

}