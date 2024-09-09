#pragma once

#include "NewbornJson.hpp"
#include "NewbornRect.hpp"
#include "NewbornGameTypes.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(WorldStructureException, NewbornException);

NEWBORN_CLASS(WorldStructure);

class WorldStructure {
public:
  struct Overlay {
    Vec2F min;
    String image;
    bool fullbright;
  };

  struct Block {
    Vec2I position;
    MaterialId materialId;
    // If the material here should not be removed on upgrade, this flag will be
    // set to true.
    bool residual;
  };

  struct Object {
    Vec2I position;
    String name;
    Direction direction;
    Json parameters;
    // If an object is not designed to be removed on upgrade, this flag will be
    // set to true.
    bool residual;
  };

  WorldStructure();
  WorldStructure(String const& configPath);
  WorldStructure(Json const& store);

  Json configValue(String const& name) const;

  List<Overlay> const& backgroundOverlays() const;
  List<Overlay> const& foregroundOverlays() const;

  List<Block> const& backgroundBlocks() const;
  List<Block> const& foregroundBlocks() const;

  List<Object> const& objects() const;

  List<Vec2I> flaggedBlocks(String const& flag) const;

  RectI region() const;
  Vec2I anchorPosition() const;

  void setAnchorPosition(Vec2I const& anchorPosition);
  void translate(Vec2I const& distance);

  Json store() const;

private:
  struct BlockKey {
    bool anchor;
    bool foregroundBlock;
    MaterialId foregroundMat;
    bool foregroundResidual;
    bool backgroundBlock;
    MaterialId backgroundMat;
    bool backgroundResidual;
    String object;
    Direction objectDirection;
    Json objectParameters;
    bool objectResidual;
    StringList flags;
  };

  RectI m_region;
  Vec2I m_anchorPosition;
  Json m_config;

  List<Overlay> m_backgroundOverlays;
  List<Overlay> m_foregroundOverlays;

  List<Block> m_backgroundBlocks;
  List<Block> m_foregroundBlocks;

  List<Object> m_objects;
  StringMap<List<Vec2I>> m_flaggedBlocks;
};

}
