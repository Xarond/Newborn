#pragma once

#include "NewbornWorldGeometry.hpp"
#include "NewbornParticle.hpp"
#include "NewbornWorldTiles.hpp"

namespace Newborn {

NEWBORN_CLASS(ParticleManager);

class ParticleManager {
public:
  ParticleManager(WorldGeometry const& worldGeometry, ClientTileSectorArrayPtr const& tileSectorArray);

  void add(Particle particle);
  void addParticles(List<Particle> particles);

  size_t count() const;
  void clear();

  void setUndergroundLevel(float undergroundLevel);

  // Updates current particles and spawns new weather particles
  void update(float dt, RectF const& cullRegion, float wind);

  List<Particle> const& particles() const;
  List<pair<Vec2F, Vec3F>> lightSources() const;

private:
  enum class TileType { Colliding, Water, Empty };

  List<Particle> m_particles;
  List<Particle> m_nextParticles;

  WorldGeometry m_worldGeometry;
  float m_undergroundLevel;
  ClientTileSectorArrayPtr m_tileSectorArray;
};

}
