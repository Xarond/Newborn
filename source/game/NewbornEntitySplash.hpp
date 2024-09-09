#pragma once

#include "NewbornJson.hpp"
#include "NewbornParticle.hpp"

namespace Newborn {

NEWBORN_CLASS(World);
NEWBORN_STRUCT(EntitySplashConfig);
NEWBORN_CLASS(EntitySplashHelper);

struct EntitySplashConfig {
  EntitySplashConfig();
  EntitySplashConfig(Json const& config);
  float splashSpeedMin;
  Vec2F splashBottomSensor;
  Vec2F splashTopSensor;
  float splashMinWaterLevel;
  int numSplashParticles;
  Particle splashParticle;
  Particle splashParticleVariance;
  float splashYVelocityFactor;

  List<Particle> doSplash(Vec2F position, Vec2F velocity, World* world) const;
};

}
