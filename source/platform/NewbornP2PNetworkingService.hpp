#pragma once

#include "NewbornEither.hpp"
#include "NewbornHostAddress.hpp"
#include "NewbornStrongTypedef.hpp"
#include "NewbornRpcPromise.hpp"

namespace Newborn {

NEWBORN_CLASS(P2PSocket);
NEWBORN_CLASS(P2PNetworkingService);
  
enum class P2PJoinRequestReply {
  No,
  Yes,
  Ignore,
};

// P2P networking is assumed to be guaranteed in order delivery of arbitrarily
// sized messages.  Neither the P2PSocket or the P2PNetworkingService are
// assumed to be thread safe interfaces, but access to independent P2PSockets
// from different threads or access to a P2PSocket and the P2PNetworkingService
// from different threads is assumed to be safe.
class P2PSocket {
public:
  virtual ~P2PSocket() = default;

  virtual bool isOpen() = 0;
  virtual bool sendMessage(ByteArray const& message) = 0;
  virtual Maybe<ByteArray> receiveMessage() = 0;
};

strong_typedef(String, P2PNetworkingPeerId);

// API for platform specific peer to peer multiplayer services.
class P2PNetworkingService {
public:
  virtual ~P2PNetworkingService() = default;

  // P2P friends cannot join this player
  virtual void setJoinUnavailable() = 0;
  // P2P friends can join this player's local game
  virtual void setJoinLocal(uint32_t capacity) = 0;
  // P2P friends can join this player at the given remote server
  virtual void setJoinRemote(HostAddressWithPort location) = 0;
  // Updates rich presence activity info
  virtual void setActivityData(const char* title, const char* details, int64_t startTime, Maybe<pair<uint16_t, uint16_t>>) = 0;

  // If this player joins another peer's game using the P2P UI, this will return
  // a pending join location
  virtual MVariant<P2PNetworkingPeerId, HostAddressWithPort> pullPendingJoin() = 0;
  // This will return a username and a promise keeper to respond to the join request
  virtual Maybe<pair<String, RpcPromiseKeeper<P2PJoinRequestReply>>> pullJoinRequest() = 0;

  virtual void setAcceptingP2PConnections(bool acceptingP2PConnections) = 0;
  virtual List<P2PSocketUPtr> acceptP2PConnections() = 0;
  virtual void update() = 0;

  virtual Either<String, P2PSocketUPtr> connectToPeer(P2PNetworkingPeerId peerId) = 0;
};

};
