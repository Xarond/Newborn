//*************************
// Jakub Joszko 2024
//*************************
#pragma once

#include "NewbornJson.hpp"
#include "NewbornByteArray.hpp"
#include "NewbornRpcPromise.hpp"

namespace Newborn {

NEWBORN_CLASS(JsonRpcInterface);
NEWBORN_CLASS(JsonRpc);

NEWBORN_EXCEPTION(JsonRpcException, NewbornException);

typedef function<Json(Json const&)> JsonRpcRemoteFunction;

typedef StringMap<JsonRpcRemoteFunction> JsonRpcHandlers;

// Simple interface to just the method invocation part of JsonRpc.
class JsonRpcInterface {
public:
  virtual ~JsonRpcInterface();
  virtual RpcPromise<Json> invokeRemote(String const& handler, Json const& arguments) = 0;
};

// Simple class to handle remote methods based on Json types.  Does not
// handle any of the network details, simply turns rpc calls into ByteArray
// messages to be sent and received.
class JsonRpc : public JsonRpcInterface {
public:
  JsonRpc();

  void registerHandler(String const& handler, JsonRpcRemoteFunction func);
  void registerHandlers(JsonRpcHandlers const& handlers);

  void removeHandler(String const& handler);
  void clearHandlers();

  RpcPromise<Json> invokeRemote(String const& handler, Json const& arguments) override;

  bool sendPending() const;
  ByteArray send();
  void receive(ByteArray const& inbuffer);

private:
  JsonRpcHandlers m_handlers;
  Map<uint64_t, RpcPromiseKeeper<Json>> m_pendingResponse;
  List<Json> m_pending;
  uint64_t m_requestId;
};

}
