#include "NewbornUniverseServer.hpp"
#include "NewbornRoot.hpp"

#include "gtest/gtest.h"

using namespace Newborn;

TEST(ServerTest, Run) {
  UniverseServer server(Root::singleton().toStoragePath("universe"));
  server.start();
  server.stop();
  server.join();
}
