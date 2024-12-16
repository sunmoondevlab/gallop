#include "compiler/parser/ast_node_type.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler::Parser;

class AstNodeTypeTest : public ::testing::Test {};
TEST_F(AstNodeTypeTest, AstNodeTypeStringCheck) {
  EXPECT_EQ(AstNodeType::getString(AstNodeTypeEnum::unknown), "Unknown");

  EXPECT_EQ(AstNodeType::getString(AstNodeTypeEnum::rootFile), "Root(File)");
  EXPECT_EQ(AstNodeType::getString(AstNodeTypeEnum::rootStdin), "Root(Stdin)");
  EXPECT_EQ(AstNodeType::getString(AstNodeTypeEnum::rootInterpreter),
            "Root(Interpreter)");
};
