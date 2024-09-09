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


class P2PSocket {
public:
  virtual ~P2PSocket() = default;

  virtual bool isOpen() = 0;
  virtual bool sendMessage(ByteArray const& message) = 0;
  virtual Maybe<ByteArray> receiveMessage() = 0;
};

strong_typedef(String, P2PNetworkingPeerId);

class P2PNetworkingService {
public:
  virtual ~P2PNetworkingService() = default;

  virtual void setJoinUnavailable() = 0;
  virtual void setJoinLocal(uint32_t capacity) = 0;
  virtual void setJoinRemote(HostAddressWithPort location) = 0;
  virtual void setActivityData(const char* title, const char* details, int64_t startTime, Maybe<pair<uint16_t, uint16_t>>) = 0;

  virtual MVariant<P2PNetworkingPeerId, HostAddressWithPort> pullPendingJoin() = 0;
  virtual Maybe<pair<String, RpcPromiseKeeper<P2PJoinRequestReply>>> pullJoinRequest() = 0;

  virtual void setAcceptingP2PConnections(bool acceptingP2PConnections) = 0;
  virtual List<P2PSocketUPtr> acceptP2PConnections() = 0;
  virtual void update() = 0;

  virtual Either<String, P2PSocketUPtr> connectToPeer(P2PNetworkingPeerId peerId) = 0;
};

};
