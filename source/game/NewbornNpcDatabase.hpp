#pragma once

#include "NewbornThread.hpp"
#include "NewbornHumanoid.hpp"
#include "NewbornDamageTypes.hpp"
#include "NewbornStatusTypes.hpp"
#include "NewbornEntitySplash.hpp"
#include "NewbornItemDescriptor.hpp"

namespace Newborn {

NEWBORN_CLASS(Item);
NEWBORN_CLASS(Npc);
NEWBORN_CLASS(NpcDatabase);

NEWBORN_EXCEPTION(NpcException, NewbornException);

struct NpcVariant {
  String species;
  String typeName;
  float level;
  uint64_t seed;

  Json overrides;

  StringList scripts;
  unsigned initialScriptDelta;
  Json scriptConfig;

  HumanoidIdentity humanoidIdentity;
  Json humanoidConfig;

  Json movementParameters;
  Json statusControllerSettings;
  List<PersistentStatusEffect> innateStatusEffects;
  Json touchDamageConfig;

  StringMap<ItemDescriptor> items;

  StringList dropPools;
  bool disableWornArmor;

  bool persistent;
  bool keepAlive;

  TeamType damageTeamType;
  uint8_t damageTeam;

  Vec3B nametagColor;

  EntitySplashConfig splashConfig;
};

class NpcDatabase {
public:
  NpcDatabase();

  NpcVariant generateNpcVariant(String const& species, String const& typeName, float level) const;
  NpcVariant generateNpcVariant(String const& species, String const& typeName, float level, uint64_t seed, Json const& overrides) const;

  ByteArray writeNpcVariant(NpcVariant const& variant) const;
  NpcVariant readNpcVariant(ByteArray const& data) const;

  Json writeNpcVariantToJson(NpcVariant const& variant) const;
  NpcVariant readNpcVariantFromJson(Json const& data) const;

  NpcPtr createNpc(NpcVariant const& npcVariant) const;
  NpcPtr diskLoadNpc(Json const& diskStoree) const;
  NpcPtr netLoadNpc(ByteArray const& netStore) const;

  List<Drawable> npcPortrait(NpcVariant const& npcVariant, PortraitMode mode) const;

  Json buildConfig(String const& typeName, Json const& overrides = Json()) const;

private:
  // Recursively merges maps and lets any non-null merger (including lists)
  // override any base value
  Json mergeConfigValues(Json const& base, Json const& merger) const;

  StringMap<Json> m_npcTypes;
};

}
