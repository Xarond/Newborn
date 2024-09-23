#pragma once

#include "NewbornThread.hpp"
#include "NewbornTcp.hpp"
#include "NewbornMap.hpp"
#include "NewbornServerRconClient.hpp"

namespace Newborn {

NEWBORN_CLASS(UniverseServer);
NEWBORN_CLASS(ServerRconThread);

class ServerRconThread : public Thread {
public:
  ServerRconThread(UniverseServer* universe, HostAddressWithPort const& address);
  ~ServerRconThread();

  void start();
  void stop();

protected:
  virtual void run();

private:
  void clearClients(bool all = false);

  UniverseServer* m_universe;
  TcpServer m_rconServer;
  bool m_stop;
  HashMap<HostAddress, ServerRconClientPtr> m_clients;
};

}
