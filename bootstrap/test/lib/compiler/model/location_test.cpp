// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/location.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;

class LocationTest : public ::testing::Test {};

TEST_F(LocationTest, Constructor) {
  Location loc("test.trot", 1ul, 1ul, 2ul);
  ASSERT_EQ(loc.getFilename(), "test.trot");
  ASSERT_EQ(loc.getString(), "test.trot:1:2");
  ASSERT_EQ(loc.getBufferPos(), 1ul);
  ASSERT_EQ(loc.getLine(), 1ul);
  ASSERT_EQ(loc.getColumn(), 2ul);

  loc = Location("test.trot", 0ul, 1ul, 0ul);
  ASSERT_EQ(loc.getFilename(), "test.trot");
  ASSERT_EQ(loc.getString(), "test.trot:1:1");
  ASSERT_EQ(loc.getBufferPos(), 0ul);
  ASSERT_EQ(loc.getLine(), 1ul);
  ASSERT_EQ(loc.getColumn(), 1ul);

  loc = Location("test.trot", 0ul, 0ul, 1ul);
  ASSERT_EQ(loc.getFilename(), "test.trot");
  ASSERT_EQ(loc.getString(), "test.trot:1:1");
  ASSERT_EQ(loc.getBufferPos(), 0ul);
  ASSERT_EQ(loc.getLine(), 1ul);
  ASSERT_EQ(loc.getColumn(), 1ul);

  loc = Location(3ul, 2ul, 1ul);
  ASSERT_EQ(loc.getFilename(), "");
  ASSERT_EQ(loc.getString(), ":2:1");
  ASSERT_EQ(loc.getBufferPos(), 3ul);
  ASSERT_EQ(loc.getLine(), 2ul);
  ASSERT_EQ(loc.getColumn(), 1ul);

  loc = Location(0ul, 1ul, 0ul);
  ASSERT_EQ(loc.getFilename(), "");
  ASSERT_EQ(loc.getString(), ":1:1");
  ASSERT_EQ(loc.getBufferPos(), 0ul);
  ASSERT_EQ(loc.getLine(), 1ul);
  ASSERT_EQ(loc.getColumn(), 1ul);

  loc = Location(0ul, 0ul, 1ul);
  ASSERT_EQ(loc.getFilename(), "");
  ASSERT_EQ(loc.getString(), ":1:1");
  ASSERT_EQ(loc.getBufferPos(), 0ul);
  ASSERT_EQ(loc.getLine(), 1ul);
  ASSERT_EQ(loc.getColumn(), 1ul);

  loc = Location();
  ASSERT_EQ(loc.getFilename(), "");
  ASSERT_EQ(loc.getString(), ":1:1");
  ASSERT_EQ(loc.getBufferPos(), 0ul);
  ASSERT_EQ(loc.getLine(), 1ul);
  ASSERT_EQ(loc.getColumn(), 1ul);

  loc = Location("test.trot");
  ASSERT_EQ(loc.getFilename(), "test.trot");
  ASSERT_EQ(loc.getString(), "test.trot:1:1");
  ASSERT_EQ(loc.getBufferPos(), 0ul);
  ASSERT_EQ(loc.getLine(), 1ul);
  ASSERT_EQ(loc.getColumn(), 1ul);
};
