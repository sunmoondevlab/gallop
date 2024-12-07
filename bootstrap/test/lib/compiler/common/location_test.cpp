// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/location.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;

class LocationTest : public ::testing::Test {};

TEST_F(LocationTest, Constructor) {
  Location p("test.trot", 1, 2ul);
  ASSERT_EQ(p.getFilename(), "test.trot");
  ASSERT_EQ(p.getLine(), 1ul);
  ASSERT_EQ(p.getColumn(), 2ul);
  ASSERT_EQ(p.getString(), "test.trot:1:2");

  p = Location("", 2, 1ul);
  ASSERT_EQ(p.getFilename(), "");
  ASSERT_EQ(p.getLine(), 2ul);
  ASSERT_EQ(p.getColumn(), 1ul);
  ASSERT_EQ(p.getString(), ":2:1");

  p = Location("test.trot", 0, 0ul);
  ASSERT_EQ(p.getString(), "test.trot");

  p = Location("", 0, 0ul);
  ASSERT_EQ(p.getString(), "");
};
