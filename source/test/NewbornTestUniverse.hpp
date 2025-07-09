#include "NewbornPlayer.hpp"
#include "NewbornRoot.hpp"
#include "NewbornUniverseClient.hpp"
#include "NewbornUniverseServer.hpp"

namespace Newborn {

class TestUniverse {
public:
  TestUniverse(Vec2U clientWindowSize);
  ~TestUniverse();

  void warpPlayer(WorldId worldId);
  WorldId currentPlayerWorld() const;

  void update(unsigned times = 1);

  List<Drawable> currentClientDrawables();

private:
  Vec2U m_clientWindowSize;
  String m_storagePath;
  UniverseServerPtr m_server;
  UniverseClientPtr m_client;
  PlayerPtr m_mainPlayer;
};

}
