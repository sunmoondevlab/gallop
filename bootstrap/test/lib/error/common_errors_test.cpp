// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "error/common_errors.hpp"
#include <gtest/gtest.h>

using namespace gallop::Error;

void throwInvalidArgumentError(std::string message_) {
  throw new InvalidArgumentError(message_);
};

void throwIOError(std::string message_) { throw new IOError(message_); };

class InvalidArgumentErrorTest : public ::testing::Test {};
TEST_F(InvalidArgumentErrorTest, InvalidArgumentError) {
  try {
    throwInvalidArgumentError(
        "invalid radix for string to big natural number. radix=37.\n");
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix for string to big natural number. radix=37.\n",
                 err->what());
    delete err;
  }
};

class IOErrorTest : public ::testing::Test {};
TEST_F(IOErrorTest, IOError) {
  try {
    throwIOError("file not found. file=a.trot.\n");
    FAIL();
  } catch (IOError *err) {
    // check exception
    ASSERT_STREQ("file not found. file=a.trot.\n", err->what());
    delete err;
  }
};
