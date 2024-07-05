//*************************
// Jakub Joszko 2024
//*************************

#include "NewbornHash.hpp"

#include "gtest/gtest.h"

TEST(HashTest, All) {
  enum SomeEnum { Foo, Bar };

  std::tuple<int, int, bool> testTuple(1, 2, false);
  std::pair<SomeEnum, int> testPair(SomeEnum::Bar, 10);

  // It's technically possible for the hash to be zero,

  EXPECT_NE(Newborn::hash<decltype(testTuple)>()(testTuple), 0u);
  EXPECT_NE(Newborn::hash<decltype(testPair)>()(testPair), 0u);
}
