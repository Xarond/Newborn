#pragma once

#include "NewbornVector.hpp"
#include "NewbornSet.hpp"
#include "NewbornMap.hpp"
#include "NewbornRandom.hpp"
#include "NewbornGameTypes.hpp"
#include "NewbornWorldTiles.hpp"

namespace Newborn {

NEWBORN_CLASS(MaterialDatabase);
NEWBORN_CLASS(FallingBlocksFacade);
NEWBORN_CLASS(FallingBlocksAgent);

enum class FallingBlockType {
  Immovable,
  Falling,
  Cascading,
  Open
};

class FallingBlocksFacade {
public:
  virtual ~FallingBlocksFacade() = default;

  virtual FallingBlockType blockType(Vec2I const& pos) = 0;
  virtual void moveBlock(Vec2I const& from, Vec2I const& to) = 0;
};

class FallingBlocksAgent {
public:
  FallingBlocksAgent(FallingBlocksFacadePtr worldFacade);

  void update();

  void visitLocation(Vec2I const& location);
  void visitRegion(RectI const& region);

private:
  FallingBlocksFacadePtr m_facade;
  float m_immediateUpwardPropagateProbability;
  HashSet<Vec2I> m_pending;
  RandomSource m_random;
};

}
