#include "cli/translate_args.hpp"
#include <functional>
#include <gtest/gtest.h>

using namespace gallop::Cli;

class TranslateArgsTest : public ::testing::Test {};
TEST_F(TranslateArgsTest, TranslateArgsTestCheck) {
  std::vector<std::string> argvV = {"galop0",         "--emit-ast",
                                    "--emit-llvm-ir", "--emit-tokens",
                                    "--verbose-emit", "test.trot"};
  std::vector<char *> argvVc;
  for (size_t i = 0; i < argvV.size(); i++) {
    argvVc.push_back(const_cast<char *>(argvV[i].c_str()));
  }

  Args args =
      TranslateArgs::translateArgs(argvVc.size(), (char **)(argvVc.data()));
  EXPECT_EQ(args.isEmitAst(), true);
  EXPECT_EQ(args.isEmitTokens(), true);
  EXPECT_EQ(args.isEmitLlvmIr(), true);
  EXPECT_EQ(args.isVerboseEmit(), true);
  EXPECT_EQ(args.getArgs()[0], "test.trot");
};
