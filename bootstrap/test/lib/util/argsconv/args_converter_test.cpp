// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "util/argsconv/args_converter.hpp"
#include <gtest/gtest.h>

namespace gallop::Util {
class ArgsConverterTest : public ::testing::Test {};
TEST_F(ArgsConverterTest, ConvertArgs) {
  std::vector<std::string> args;
  std::vector<char *> argvV;
  argvV = ArgsConverter::convertArgs(args);
  ASSERT_EQ(argvV.size(), (size_t)0);
  args = {"./bin/gallop_test", "--dump-tokens"};
  argvV = ArgsConverter::convertArgs(args);
  char **argv = argvV.data();
  ASSERT_EQ(argvV.size(), (size_t)2);
  ASSERT_EQ(std::string(*(argv)), "./bin/gallop_test");
  ASSERT_EQ(std::string(*(argv + 1)), "--dump-tokens");
};

} // namespace gallop::Util
