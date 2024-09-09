#pragma once

#include "NewbornWiring.hpp"

namespace Newborn {

NEWBORN_CLASS(WireEntity);
NEWBORN_CLASS(WorldStorage);

NEWBORN_CLASS(WireProcessor);

// Propogates WireEntity signals, and keeps networks of WireEntities alive
// together.
class WireProcessor : public WireCoordinator {
public:
  WireProcessor(WorldStoragePtr worldStorage);

  void process();

  bool readInputConnection(WireConnection const& connection) override;

private:
  struct WireEntityState {
    WireEntity* wireEntity;
    List<bool> outputStates;
    bool networkLoaded;
  };

  // Add the given WireEntity to the working entities set, populating inbound /
  // outbound nodes and states.
  void populateWorking(WireEntity* wireEntity);
  // Scans a wire network, starting at an entity at the given position, while
  // also loading any unloaded entries in the network and marking each entry as
  // now having been 'networkLoaded'.
  void loadNetwork(Vec2I tilePosition);

  WorldStoragePtr m_worldStorage;
  StableHashMap<Vec2I, WireEntityState> m_workingWireEntities;
};

}
