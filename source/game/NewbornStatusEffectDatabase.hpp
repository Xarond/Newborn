#pragma once

#include "NewbornThread.hpp"
#include "NewbornStatusTypes.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(StatusEffectDatabaseException, NewbornException);

NEWBORN_CLASS(StatusEffectDatabase);

// Named, unique, unstackable scripted effects.
struct UniqueStatusEffectConfig {
  String name;
  Maybe<String> blockingStat;
  Json effectConfig;
  float defaultDuration;
  StringList scripts;
  unsigned scriptDelta;
  Maybe<String> animationConfig;

  String label;
  String description;
  Maybe<String> icon;
};

class StatusEffectDatabase {
public:
  StatusEffectDatabase();

  bool isUniqueEffect(UniqueStatusEffect const& effect) const;

  UniqueStatusEffectConfig uniqueEffectConfig(UniqueStatusEffect const& effect) const;

private:
  UniqueStatusEffectConfig parseUniqueEffect(Json const& config, String const& path) const;

  HashMap<UniqueStatusEffect, UniqueStatusEffectConfig> m_uniqueEffects;
};

}
