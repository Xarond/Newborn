#include "NewbornAssets.hpp"

#include "gtest/gtest.h"

using namespace Newborn;

TEST(AssetsTest, All) {
    EXPECT_EQ(AssetPath::removeDirectives("/foo/bar/baz??::?:??:asdfasdf??D?"), "/foo/bar/baz");
    EXPECT_EQ(AssetPath::directory("/foo/bar/baz"), "/foo/bar/");
    EXPECT_EQ(AssetPath::directory("foo/bar/baz"), "foo/bar/");
    EXPECT_EQ(AssetPath::directory("foo"), "");
    EXPECT_EQ(AssetPath::directory("/foo"), "/");
    EXPECT_EQ(AssetPath::filename(""), "");
    EXPECT_EQ(AssetPath::filename("foo"), "foo");
    EXPECT_EQ(AssetPath::filename("/foo"), "foo");
    EXPECT_EQ(AssetPath::filename("/foo/"), "");
    EXPECT_EQ(AssetPath::filename("/foo/bar"), "bar");



    EXPECT_EQ(
        AssetPath::relativeTo("/foo/bar/baz:baf?whoa?there", "thing:sub?directive"), "/foo/bar/thing:sub?directive");
}