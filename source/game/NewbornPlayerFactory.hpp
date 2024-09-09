#pragma once

#include "NewbornItemDescriptor.hpp"
#include "NewbornHumanoid.hpp"
#include "NewbornEntitySplash.hpp"

namespace Newborn {

NEWBORN_CLASS(Player);
NEWBORN_STRUCT(PlayerConfig);
NEWBORN_CLASS(PlayerFactory);

NEWBORN_EXCEPTION(PlayerException, NewbornException);

// The player has a large number of shared config states, so this is a shared
// config object to hold them.
struct PlayerConfig {
  PlayerConfig(JsonObject const& cfg);

  HumanoidIdentity defaultIdentity;
  Humanoid::HumanoidTiming humanoidTiming;

  List<ItemDescriptor> defaultItems;
  List<ItemDescriptor> defaultBlueprints;

  RectF metaBoundBox;

  Json movementParameters;
  Json zeroGMovementParameters;
  Json statusControllerSettings;

  float footstepTiming;
  Vec2F footstepSensor;

  Vec2F underwaterSensor;
  float underwaterMinWaterLevel;

  String effectsAnimator;

  float teleportInTime;
  float teleportOutTime;

  float deployInTime;
  float deployOutTime;

  String bodyMaterialKind;

  EntitySplashConfig splashConfig;

  Json companionsConfig;

  Json deploymentConfig;

  StringMap<String> genericScriptContexts;
};

class PlayerFactory {
public:
  PlayerFactory();

  PlayerPtr create() const;
  PlayerPtr diskLoadPlayer(Json const& diskStore) const;
  PlayerPtr netLoadPlayer(ByteArray const& netStore) const;

private:
  PlayerConfigPtr m_config;
};

}
