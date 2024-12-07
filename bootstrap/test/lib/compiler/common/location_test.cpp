#if 0
#include "compiler/common/location.hpp"
#include <gtest/gtest.h>

namespace gallop {
namespace Compiler {
class LocationTest : public ::testing::Test {};

TEST_F(LocationTest, ConstructorCheck) {
  Location p("test.trot", 1, 2ul);
  EXPECT_EQ(p.getFilename(), "test.trot");
  EXPECT_EQ(p.getLineLoc(), 1ul);
  EXPECT_EQ(p.getColLoc(), 2ul);
  EXPECT_EQ(p.getString(), "test.trot:1:2");

  p = Location("", 2, 1ul);
  EXPECT_EQ(p.getFilename(), "");
  EXPECT_EQ(p.getLineLoc(), 2ul);
  EXPECT_EQ(p.getColLoc(), 1ul);
  EXPECT_EQ(p.getString(), ":2:1");

  p = Location("test.trot", 0, 0ul);
  EXPECT_EQ(p.getString(), "test.trot");

  p = Location("", 0, 0ul);
  EXPECT_EQ(p.getString(), "");
};
} // namespace Compiler
} // namespace gallop
#endif