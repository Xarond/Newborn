#pragma once

#include "NewbornNetElementSystem.hpp"
#include "NewbornJsonRpc.hpp"
#include "NewbornGameTypes.hpp"
#include "NewbornDamageTypes.hpp"
#include "NewbornCelestialCoordinate.hpp"
#include "NewbornWarping.hpp"
#include "NewbornWorldStorage.hpp"
#include "NewbornPlayerTypes.hpp"

namespace Newborn {

NEWBORN_CLASS(CelestialLog);
NEWBORN_CLASS(ClientContext);

class ClientContext {
public:
  ClientContext(Uuid serverUuid, Uuid playerUuid);

  Uuid serverUuid() const;
  // The player Uuid can differ from the mainPlayer's Uuid
  //  if the player has swapped character - use this for ship saving.
  Uuid playerUuid() const;

  // The coordinate for the world which the player's ship is currently
  // orbiting.
  CelestialCoordinate shipCoordinate() const;

  Maybe<pair<WarpAction, WarpMode>> orbitWarpAction() const;

  // The current world id of the player
  WorldId playerWorldId() const;

  bool isAdmin() const;
  EntityDamageTeam team() const;

  JsonRpcInterfacePtr rpcInterface() const;

  WorldChunks newShipUpdates();
  ShipUpgrades shipUpgrades() const;

  void readUpdate(ByteArray data);
  ByteArray writeUpdate();

  void setConnectionId(ConnectionId connectionId);
  ConnectionId connectionId() const;

private:
  Uuid m_serverUuid;
  Uuid m_playerUuid;
  ConnectionId m_connectionId = 0;

  JsonRpcPtr m_rpc;

  NetElementTopGroup m_netGroup;
  NetElementData<Maybe<pair<WarpAction, WarpMode>>> m_orbitWarpActionNetState;
  NetElementData<WorldId> m_playerWorldIdNetState;
  NetElementBool m_isAdminNetState;
  NetElementData<EntityDamageTeam> m_teamNetState;
  NetElementData<ShipUpgrades> m_shipUpgrades;
  NetElementData<CelestialCoordinate> m_shipCoordinate;

  WorldChunks m_newShipUpdates;
};

}
