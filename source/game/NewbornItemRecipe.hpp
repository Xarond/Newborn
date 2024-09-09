#pragma once

#include "NewbornItemDescriptor.hpp"
#include "NewbornGameTypes.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(RecipeException, NewbornException);

struct ItemRecipe {
  Json toJson() const;

  bool isNull() const;

  bool operator==(ItemRecipe const& rhs) const;
  bool operator!=(ItemRecipe const& rhs) const;

  StringMap<uint64_t> currencyInputs;
  List<ItemDescriptor> inputs;
  ItemDescriptor output;
  float duration;
  StringSet groups;
  Rarity outputRarity;
  String guiFilterString;
  StringMap<String> collectables;
  bool matchInputParameters;
};

template <>
struct hash<ItemRecipe> {
  size_t operator()(ItemRecipe const& v) const;
};

std::ostream& operator<<(std::ostream& os, ItemRecipe const& recipe);
}

template <> struct fmt::formatter<Newborn::ItemRecipe> : ostream_formatter {};
