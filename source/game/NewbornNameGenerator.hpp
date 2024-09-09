#pragma once

#include "NewbornJson.hpp"
#include "NewbornRandom.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(NameGeneratorException, NewbornException);

NEWBORN_CLASS(PatternedNameGenerator);

struct MarkovSource {
  size_t prefixSize;
  size_t endSize;
  StringList starts;
  StringMap<StringList> chains;
  StringSet ends;
};

class PatternedNameGenerator {
public:
  PatternedNameGenerator();

  String generateName(String const& rulesAsset) const;
  String generateName(String const& rulesAsset, uint64_t seed) const;
  String generateName(String const& rulesAsset, RandomSource& random) const;

private:
  String processRule(JsonArray const& rule, RandomSource& random) const;

  bool isProfane(String const& name) const;

  MarkovSource makeMarkovSource(size_t prefixSize, size_t endSize, StringList sourceNames);

  StringMap<MarkovSource> m_markovSources;
  StringSet m_profanityFilter;
};

}
