// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "cli/translate_args.hpp"
#include "io/file/file.hpp"
#include "util/argsconv/args_converter.hpp"
#include <functional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
using ::testing::EndsWith;
using ::testing::HasSubstr;

using namespace gallop::Cli;
using namespace gallop::Util;
using namespace gallop::IO;

class TranslateArgsTest : public ::testing::Test {};
TEST_F(TranslateArgsTest, TranslateArgs) {
  int argc = 0;
  std::vector<std::string> argsV;
  std::vector<char *> argvV;
  char **argv = nullptr;
  argsV = std::vector<std::string>{"galop0",         "--dump-ast",
                                   "--dump-llvm-ir", "--dump-tokens",
                                   "--verbose-dump", "test.trot"};
  argvV = ArgsConverter::convertArgs(argsV);
  argc = argvV.size();
  argv = argvV.data();
  Args args = TranslateArgs::translateArgs(argc, argv);
  ASSERT_EQ(args.isDumpAst(), true);
  ASSERT_EQ(args.isDumpTokens(), true);
  ASSERT_EQ(args.isDumpLlvmIr(), true);
  ASSERT_EQ(args.isVerboseDump(), true);
  ASSERT_EQ(args.getArgs()[0], "test.trot");
  argsV = std::vector<std::string>{
      "galop0",
      "--emit-llvm-ir",
      "--with-commentout-all",
      "--with-commentout-for-doc",
      "--entry-point-id",
      "entry.entry.link",
      "--src-root-dir",
      ".",
      "--dest-root-dir",
      "../example/test_dest_root",
  };
  ASSERT_EQ(File::isDirectory("../example/test_dest_root"), false);
  argvV = ArgsConverter::convertArgs(argsV);
  argc = argvV.size();
  argv = argvV.data();
  args = TranslateArgs::translateArgs(argc, argv);
  ASSERT_EQ(args.isDumpAst(), false);
  ASSERT_EQ(args.isDumpTokens(), false);
  ASSERT_EQ(args.isDumpLlvmIr(), false);
  ASSERT_EQ(args.isVerboseDump(), false);
  ASSERT_EQ(args.isEmitLlvmIr(), true);
  ASSERT_EQ(args.getParserOption().isWithCommentOutAll(), true);
  ASSERT_EQ(args.getParserOption().isWithCommentOutForDoc(), true);
  ASSERT_EQ(args.getLlvmOption().getEntryPointId(), "entry.entry.link");
  ASSERT_THAT(args.getLlvmOption().getSrcRootDir(),
              EndsWith("/gallop/bootstrap"));
  ASSERT_THAT(args.getLlvmOption().getDestRootDir(),
              EndsWith("/gallop/example/test_dest_root"));
  ASSERT_EQ(args.getArgs().size(), (size_t)0);
  ASSERT_EQ(File::isDirectory("../example/test_dest_root"), true);
  ASSERT_EQ(File::rmdir("../example/test_dest_root"), true);
};
