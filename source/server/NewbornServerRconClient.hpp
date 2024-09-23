#pragma once

#include "NewbornThread.hpp"
#include "NewbornTcp.hpp"
#include "NewbornMap.hpp"
#include "NewbornDataStreamDevices.hpp"

namespace Newborn {

class UniverseServer;

class ServerRconClient : public Thread {
public:
  static const uint32_t SERVERDATA_AUTH = 0x03;
  static const uint32_t SERVERDATA_EXECCOMMAND = 0x02;
  static const uint32_t SERVERDATA_RESPONSE_VALUE = 0x00;
  static const uint32_t SERVERDATA_AUTH_RESPONSE = 0x02;
  static const uint32_t SERVERDATA_AUTH_FAILURE = 0xffffffff;
  ServerRconClient(UniverseServer* universe, TcpSocketPtr socket);
  ~ServerRconClient();

  void start();
  void stop();

protected:
  virtual void run();

private:
  static size_t const MaxPacketSize = 4096;
  NEWBORN_EXCEPTION(NoMoreRequests, NewbornException);

  void receive(size_t size);
  void send(uint32_t requestId, uint32_t cmd, String str = "");
  void sendAuthFailure();
  void sendCmdResponse(uint32_t requestId, String response);
  void closeSocket();
  void processRequest();
  String handleCommand(String commandLine);

  UniverseServer* m_universe;
  TcpSocketPtr m_socket;
  DataStreamBuffer m_packetBuffer;
  bool m_stop;
  bool m_authed;
  String m_rconPassword;
};
typedef shared_ptr<ServerRconClient> ServerRconClientPtr;
}
