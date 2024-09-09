#pragma once

#include "NewbornBiomePlacement.hpp"
#include "NewbornSpawner.hpp"

namespace Newborn {

NEWBORN_STRUCT(AmbientNoisesDescription);
NEWBORN_CLASS(Parallax);
NEWBORN_STRUCT(BiomePlaceables);
NEWBORN_STRUCT(Biome);

struct BiomePlaceables {
  BiomePlaceables();
  explicit BiomePlaceables(Json const& json);

  Json toJson() const;

  // If any of the item distributions contain trees, this returns the first
  // tree type.
  Maybe<TreeVariant> firstTreeType() const;

  ModId grassMod;
  float grassModDensity;
  ModId ceilingGrassMod;
  float ceilingGrassModDensity;

  List<BiomeItemDistribution> itemDistributions;
};

struct Biome {
  Biome();
  explicit Biome(Json const& store);

  Json toJson() const;

  String baseName;
  String description;

  MaterialId mainBlock;
  List<MaterialId> subBlocks;
  // Pairs the ore type with the commonality multiplier.
  List<pair<ModId, float>> ores;

  float hueShift;
  MaterialHue materialHueShift;

  BiomePlaceables surfacePlaceables;
  BiomePlaceables undergroundPlaceables;

  SpawnProfile spawnProfile;

  ParallaxPtr parallax;

  AmbientNoisesDescriptionPtr ambientNoises;
  AmbientNoisesDescriptionPtr musicTrack;
};

}
