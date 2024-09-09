#pragma once

#include "NewbornLua.hpp"
#include "NewbornGameTypes.hpp"
#include "NewbornRpcThreadPromise.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseServer);

namespace LuaBindings {
  LuaCallbacks makeUniverseServerCallbacks(UniverseServer* universe);

  namespace UniverseServerCallbacks {
    List<ConnectionId> clientIds(UniverseServer* universe);
    size_t numberOfClients(UniverseServer* universe);
    bool isConnectedClient(UniverseServer* universe, ConnectionId arg1);
    String clientNick(UniverseServer* universe, ConnectionId arg1);
    Maybe<ConnectionId> findNick(UniverseServer* universe, String const& arg1);
    void adminBroadcast(UniverseServer* universe, String const& arg1);
    void adminWhisper(UniverseServer* universe, ConnectionId arg1, String const& arg2);
    bool isAdmin(UniverseServer* universe, ConnectionId arg1);
    bool isPvp(UniverseServer* universe, ConnectionId arg1);
    void setPvp(UniverseServer* universe, ConnectionId arg1, Maybe<bool> arg2);
    bool isWorldActive(UniverseServer* universe, String const& worldId);
    StringList activeWorlds(UniverseServer* universe);
    RpcThreadPromise<Json> sendWorldMessage(UniverseServer* universe, String const& worldId, String const& message, LuaVariadic<Json> args);
    bool sendPacket(UniverseServer* universe, ConnectionId clientId, String const& packetTypeName, Json const& args);
    String clientWorld(UniverseServer* universe, ConnectionId clientId);
  }
}
}
