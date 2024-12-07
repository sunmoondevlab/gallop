// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "error/compile_errors.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;
using namespace gallop::Error;

void throwTokenizeError(const Token &token_, std::string srcLine_) {
  throw new TokenizeError(token_, srcLine_);
};

class TokenizeErrorTest : public ::testing::Test {};
TEST_F(TokenizeErrorTest, TokenizeError) {
  try {
    throwTokenizeError(Token(Location("a.trot", 6, 1, 7),
                             TokenTypeEnum::invalidEscapeSequence, U"\\"),
                       "     '\\'");
    FAIL();
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at a.trot:1:7\n"
                 "     '\\'\n"
                 "      ^\n",
                 err->what());
    delete err;
  }
};
