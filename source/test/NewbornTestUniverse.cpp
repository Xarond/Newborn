#include "NewbornTestUniverse.hpp"
#include "NewbornFile.hpp"
#include "NewbornQuests.hpp"
#include "NewbornPlayerFactory.hpp"
#include "NewbornPlayerStorage.hpp"
#include "NewbornStatistics.hpp"
#include "NewbornStatisticsService.hpp"
#include "NewbornPlayer.hpp"
#include "NewbornAssets.hpp"
#include "NewbornWorldClient.hpp"

namespace Newborn {

TestUniverse::TestUniverse(Vec2U clientWindowSize) {
  auto& root = Root::singleton();

  m_clientWindowSize = clientWindowSize;

  m_storagePath = File::temporaryDirectory();
  auto playerStorage = make_shared<PlayerStorage>(File::relativeTo(m_storagePath, "player"));
  auto statistics = make_shared<Statistics>(File::relativeTo(m_storagePath, "statistics"));
  m_server = make_shared<UniverseServer>(File::relativeTo(m_storagePath, "universe"));
  m_client = make_shared<UniverseClient>(playerStorage, statistics);

  m_server->start();

  m_mainPlayer = root.playerFactory()->create();
  m_mainPlayer->finalizeCreation();
  m_mainPlayer->setAdmin(true);
  m_mainPlayer->setModeType(PlayerMode::Survival);
  m_client->setMainPlayer(m_mainPlayer);
  m_client->connect(m_server->addLocalClient(), "test", "");
}

TestUniverse::~TestUniverse() {
  m_client = {};
  m_server = {};
  m_mainPlayer = {};
  File::removeDirectoryRecursive(m_storagePath);
}

void TestUniverse::warpPlayer(WorldId worldId) {
  m_client->warpPlayer(WarpToWorld(worldId), true);
  while (m_mainPlayer->isTeleporting() || m_client->playerWorld().empty()) {
    m_client->update(0.016f);
    Thread::sleep(16);
  }
}

WorldId TestUniverse::currentPlayerWorld() const {
  return m_client->clientContext()->playerWorldId();
}

void TestUniverse::update(unsigned times) {
  for (unsigned i = 0; i < times; ++i) {
    m_client->update(0.016f);
    Thread::sleep(16);
  }
}

List<Drawable> TestUniverse::currentClientDrawables() {
  WorldRenderData renderData;
  auto worldClient = m_client->worldClient();
  worldClient->centerClientWindowOnPlayer(m_clientWindowSize);
  worldClient->render(renderData, 0);

  List<Drawable> drawables;
  for (auto& ed : renderData.entityDrawables) {
    for (auto& p : ed.layers)
      drawables.appendAll(std::move(p.second));
  }

  return drawables;
}

}
