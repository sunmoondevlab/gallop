// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/lexer/token.hpp"
#include <gtest/gtest.h>

// using namespace gallop::Compiler;
// using namespace gallop::Compiler::Lexer;

// class TokenTest : public ::testing::Test {};
// TEST_F(TokenTest, TokenTypeString) {
//   Token token(Location(1, 1));
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
//   ASSERT_EQ(token.getTokenTypeString(), "unknown token");
//   token.setTokenVal(TokenTypeEnum::literalDecimalNumberIntegralPart, "123");
//   ASSERT_EQ(token.getTokenTypeString(),
//             "decimal number literal(integral part)");

//   token.setTokenVal(TokenTypeEnum::symbolCharacterSlashSlash, "//");
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getTokenTypeString(), "comment out(oneline) open\"//\"");

//   token.setTokenVal(TokenTypeEnum::commentOutOneline, "comment");
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
//   ASSERT_EQ(token.getTokenTypeString(), "comment out(oneline)");

//   token.setTokenVal(TokenTypeEnum::symbolCharacterPlusEqual, "+=");
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusEqual);
//   ASSERT_EQ(token.getTokenTypeString(), "operator(+=)");

//   token.setTokenVal(TokenTypeEnum::symbolCharacterLeftcurlybrackets, "{");
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterLeftcurlybrackets);
//   ASSERT_EQ(token.getTokenTypeString(), "curly bracket open'{'");
// };

// TEST_F(TokenTest, Token) {
//   Token token(Location(1, 1));
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
//   ASSERT_EQ(token.getToken(), "");
//   token.setTokenVal(TokenTypeEnum::literalDecimalNumberIntegralPart, "123");
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalDecimalNumberIntegralPart);
//   ASSERT_EQ(token.getToken(), "123");

//   token = Token(Location(2, 1), TokenTypeEnum::commentOutBlock,
//                 "comment for doc\nthis comment is test\rtest comment\r\ndo");
//   size_t column = 1;
//   ASSERT_EQ(token.countNewLineInToken(&column), 3ul);
//   ASSERT_EQ(column, 3ul);

//   token = Token(Location("test.trot", 1, 1), TokenTypeEnum::commentOutBlock,
//                 "comment for doc\nthis comment is test\rtest comment\r\ndo");
//   column = 1;
//   ASSERT_EQ(token.getLocation().getFilename(), "test.trot");
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token.countNewLineInToken(&column), 3ul);
//   ASSERT_EQ(column, 3ul);
// };

// class TokensTest : public ::testing::Test {};
// TEST_F(TokensTest, Tokens) {
//   Tokens tokens;
//   Token token = tokens.get(0);
//   ASSERT_EQ(token.getLocation().getLine(), 0ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 0ul);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
//   ASSERT_EQ(token.getToken(), "");
//   ASSERT_EQ(tokens.getLastTokenType(), TokenTypeEnum::unknown);

//   tokens.push(
//       new Token(Location(1, 1), TokenTypeEnum::symbolCharacterMinus, "-"));
//   token = tokens.get(0);
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
//   ASSERT_EQ(tokens.getLastTokenType(), TokenTypeEnum::symbolCharacterMinus);
//   ASSERT_EQ(token.getToken(), "-");

//   tokens.push(new Token(Location(1, 2),
//                         TokenTypeEnum::literalDecimalNumberIntegralPart,
//                         "123456"));
//   tokens.push(new Token(
//       Location(2, 4), TokenTypeEnum::literalDecimalNumberIntegralPart,
//       "112"));

//   Token token1 = tokens.get(2);
//   ASSERT_EQ(token1.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token1.getLocation().getColumn(), 4ul);
//   ASSERT_EQ(token1.getTokenType(),
//             TokenTypeEnum::literalDecimalNumberIntegralPart);
//   ASSERT_EQ(tokens.getLastTokenType(),
//             TokenTypeEnum::literalDecimalNumberIntegralPart);
//   ASSERT_EQ(token1.getToken(), "112");

//   ASSERT_EQ(tokens.getTokenCount(), 3ul);

//   Tokens tokens2;
//   tokens2.push(new Token(
//       Location(3, 4), TokenTypeEnum::literalDecimalNumberIntegralPart,
//       "111"));
//   tokens2.push(new Token(
//       Location(4, 1), TokenTypeEnum::literalDecimalNumberIntegralPart,
//       "124"));

//   tokens.push(tokens2);
//   ASSERT_EQ(tokens.getTokenCount(), 5ul);
//   Token token2 = tokens.get(4);
//   ASSERT_EQ(token2.getLocation().getLine(), 4ul);
//   ASSERT_EQ(token2.getLocation().getColumn(), 1ul);

//   tokens.popDelete();
//   ASSERT_EQ(tokens.getTokenCount(), 4ul);

//   tokens.popDeleteFromPos(2);
//   ASSERT_EQ(tokens.getTokenCount(), 2ul);

//   tokens.popDeleteFromPos(0);
//   ASSERT_EQ(tokens.getTokenCount(), 0ul);
// };
