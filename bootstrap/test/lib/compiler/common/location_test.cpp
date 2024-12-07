#if 0
#include "compiler/common/location.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;

class LocationTest : public ::testing::Test {};

TEST_F(LocationTest, ConstructorCheck) {
  Location p("test.trot", 1, 2ul);
  EXPECT_EQ(p.getFilename(), "test.trot");
  EXPECT_EQ(p.getLine(), 1ul);
  EXPECT_EQ(p.getColumn(), 2ul);
  EXPECT_EQ(p.getString(), "test.trot:1:2");

  p = Location("", 2, 1ul);
  EXPECT_EQ(p.getFilename(), "");
  EXPECT_EQ(p.getLine(), 2ul);
  EXPECT_EQ(p.getColumn(), 1ul);
  EXPECT_EQ(p.getString(), ":2:1");

  p = Location("test.trot", 0, 0ul);
  EXPECT_EQ(p.getString(), "test.trot");

  p = Location("", 0, 0ul);
  EXPECT_EQ(p.getString(), "");
};

#endif