#pragma once

#include "NewbornWiring.hpp"
#include "NewbornTileEntity.hpp"

namespace Newborn {

NEWBORN_CLASS(WireEntity);

class WireEntity : public virtual TileEntity {
public:
  virtual ~WireEntity() {}

  virtual size_t nodeCount(WireDirection direction) const = 0;
  virtual Vec2I nodePosition(WireNode wireNode) const = 0;
  virtual List<WireConnection> connectionsForNode(WireNode wireNode) const = 0;
  virtual bool nodeState(WireNode wireNode) const = 0;

  virtual void addNodeConnection(WireNode wireNode, WireConnection nodeConnection) = 0;
  virtual void removeNodeConnection(WireNode wireNode, WireConnection nodeConnection) = 0;

  virtual void evaluate(WireCoordinator* coordinator) = 0;
};

}
