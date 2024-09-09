#pragma once

#include "NewbornCelestialParameters.hpp"
#include "NewbornCelestialCoordinate.hpp"
#include "NewbornSystemWorld.hpp"
#include "NewbornNetPackets.hpp"

namespace Newborn {

NEWBORN_CLASS(CelestialDatabase);
NEWBORN_CLASS(PlayerUniverseMap);
NEWBORN_CLASS(Celestial);
NEWBORN_CLASS(Clock);
NEWBORN_CLASS(ClientContext);

class SystemWorldClient : public SystemWorld {
public:
  SystemWorldClient(ClockConstPtr universeClock, CelestialDatabasePtr celestialDatabase, PlayerUniverseMapPtr clientContext);

  CelestialCoordinate currentSystem() const;

  Maybe<Vec2F> shipPosition() const;
  SystemLocation shipLocation() const;
  SystemLocation shipDestination() const;
  bool flying() const;

  void update(float dt);

  List<SystemObjectPtr> objects() const override;
  List<Uuid> objectKeys() const override;
  SystemObjectPtr getObject(Uuid const& uuid) const override;

  List<SystemClientShipPtr> ships() const;
  SystemClientShipPtr getShip(Uuid const& uuid) const;

  Uuid spawnObject(String typeName, Maybe<Vec2F> position = {}, Maybe<Uuid> const& uuid = {}, JsonObject parameters = {});

  // returns whether the packet was handled
  bool handleIncomingPacket(PacketPtr packet);
  List<PacketPtr> pullOutgoingPackets();
private:
  SystemObjectPtr netLoadObject(ByteArray netStore);
  SystemClientShipPtr netLoadShip(ByteArray netStore);

  // m_ship can be a null pointer, indicating that the system is not initialized
  SystemClientShipPtr m_ship;
  HashMap<Uuid, SystemObjectPtr> m_objects;
  HashMap<Uuid, SystemClientShipPtr> m_clientShips;

  PlayerUniverseMapPtr m_universeMap;

  List<PacketPtr> m_outgoingPackets;
};


}
