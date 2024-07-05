//*************************
// Jakub Joszko 2024
//*************************
#include "NewbornPerlin.hpp"

namespace Newborn {

EnumMap<PerlinType> const PerlinTypeNames{
  {PerlinType::Uninitialized, "uninitialized"},
  {PerlinType::Perlin, "perlin"},
  {PerlinType::Billow, "billow"},
  {PerlinType::RidgedMulti, "ridgedMulti"},
};

}
