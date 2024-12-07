// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/token.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"
#include "char_set/string/utf32_string.hpp"
#include "io/stream/utf32_input_stream.hpp"

using namespace gallop::CharSet;
using namespace gallop::Compiler;

class TokenTest : public ::testing::Test {};
TEST_F(TokenTest, TokenTypeString) {
  Token token(Location(0, 1, 1), TokenTypeEnum::unknown, U"");
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
  ASSERT_EQ(token.getTokenTypeString(), "unknown token");
  token =
      Token(Location(0, 1, 1), TokenTypeEnum::ltDecimalIntegralPart, U"123");
  ASSERT_EQ(token.getTokenTypeString(),
            "decimal number literal(integral part)");
  ASSERT_EQ(token.preParseEscapeUtf32CharCode(), nullptr);

  token = Token(Location(0, 1, 1), TokenTypeEnum::scOnelineCommentOut, U"//");
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token.getTokenTypeString(), "comment out(oneline) open\"//\"");

  token = Token(Location(0, 1, 1), TokenTypeEnum::coString, U"comment");
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token.getTokenTypeString(), "string of comment out");

  token = Token(Location(0, 1, 1), TokenTypeEnum::scPlusAssign, U"+=");
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scPlusAssign);
  ASSERT_EQ(token.getTokenTypeString(), "operator(+=)");

  token = Token(Location(0, 1, 1), TokenTypeEnum::scCurlyBracketOpen, U"{");
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scCurlyBracketOpen);
  ASSERT_EQ(token.getTokenTypeString(), "curly bracket open'{'");
};

TEST_F(TokenTest, Token) {
  Token token(Location(0, 1, 1), TokenTypeEnum::unknown, U"");
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
  ASSERT_EQ(token.getToken(), U"");
  ASSERT_EQ(token.getTokenU8(), "");

  token =
      Token(Location(0, 1, 1), TokenTypeEnum::ltDecimalIntegralPart, U"123");
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltDecimalIntegralPart);
  ASSERT_EQ(token.getToken(), U"123");
  ASSERT_EQ(token.getTokenU8(), "123");

  token = Token(Location(4, 2, 1), TokenTypeEnum::coString,
                U"comment for doc\nthis comment is test\rtest comment\r\ndo");
  size_t column = 1;
  ASSERT_EQ(token.getLocation().getBufferPos(), 4ul);
  ASSERT_EQ(token.countLineBreakInToken(column), 3ul);
  ASSERT_EQ(column, 3ul);

  token = Token(Location("test.trot", 0, 1, 1), TokenTypeEnum::coString,
                U"comment for doc\nthis comment is test\rtest comment\r\ndo");
  column = 1;
  ASSERT_EQ(token.getLocation().getFilename(), "test.trot");
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);
  ASSERT_EQ(token.countLineBreakInToken(column), 3ul);
  ASSERT_EQ(column, 3ul);

  token = Token(Location(5, 5, 1), TokenTypeEnum::coString, U"コメントアウト");
  ASSERT_EQ(token.getToken(), U"コメントアウト");
  ASSERT_EQ(token.getTokenLen(), 7ul);
  ASSERT_EQ(token.getTokenU8(), "コメントアウト");
  ASSERT_EQ(token.getTokenLenU8(), 21ul);
};

TEST_F(TokenTest, EscapeCharCode) {
  Token token(Location(0, 1, 1), TokenTypeEnum::ltEscapeSequenceLineFeed,
              U"\\n", static_cast<int32_t>(CharCode::UtfAsciiTable::LineFeed));
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequenceLineFeed);
  int32_t *escapeCharCode = token.preParseEscapeUtf32CharCode();
  ASSERT_EQ(*escapeCharCode,
            static_cast<int32_t>(CharCode::UtfAsciiTable::LineFeed));
  delete escapeCharCode;
};