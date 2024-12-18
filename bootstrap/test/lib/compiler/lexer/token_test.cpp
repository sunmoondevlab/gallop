#if 0
#include "compiler/lexer/token.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;

class TokenTest : public ::testing::Test {};
TEST_F(TokenTest, TokenTypeStringCheck) {
  Token token(Location(1, 1));
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
  EXPECT_EQ(token.getTokenTypeString(), "unknown token");
  token.setTokenVal(TokenTypeEnum::literalDecimalNumberIntegralPart, "123");
  EXPECT_EQ(token.getTokenTypeString(),
            "decimal number literal(integral part)");

  token.setTokenVal(TokenTypeEnum::symbolCharacterSlashSlash, "//");
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getTokenTypeString(), "comment out(oneline) open\"//\"");

  token.setTokenVal(TokenTypeEnum::commentOutOneline, "comment");
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
  EXPECT_EQ(token.getTokenTypeString(), "comment out(oneline)");

  token.setTokenVal(TokenTypeEnum::symbolCharacterPlusEqual, "+=");
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusEqual);
  EXPECT_EQ(token.getTokenTypeString(), "operator(+=)");

  token.setTokenVal(TokenTypeEnum::symbolCharacterLeftcurlybrackets, "{");
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterLeftcurlybrackets);
  EXPECT_EQ(token.getTokenTypeString(), "curly bracket open'{'");
};

TEST_F(TokenTest, TokenCheck) {
  Token token(Location(1, 1));
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
  EXPECT_EQ(token.getToken(), "");
  token.setTokenVal(TokenTypeEnum::literalDecimalNumberIntegralPart, "123");
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "123");

  token = Token(Location(2, 1), TokenTypeEnum::commentOutBlock,
                "comment for doc\nthis comment is test\rtest comment\r\ndo");
  size_t column = 1;
  EXPECT_EQ(token.countNewLineInToken(&column), 3ul);
  EXPECT_EQ(column, 3ul);

  token = Token(Location("test.trot", 1, 1), TokenTypeEnum::commentOutBlock,
                "comment for doc\nthis comment is test\rtest comment\r\ndo");
  column = 1;
  EXPECT_EQ(token.getLocation().getFilename(), "test.trot");
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);
  EXPECT_EQ(token.countNewLineInToken(&column), 3ul);
  EXPECT_EQ(column, 3ul);
};

class TokensTest : public ::testing::Test {};
TEST_F(TokensTest, TokensCheck) {
  Tokens tokens;
  Token token = tokens.get(0);
  EXPECT_EQ(token.getLocation().getLine(), 0ul);
  EXPECT_EQ(token.getLocation().getColumn(), 0ul);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::unknown);
  EXPECT_EQ(token.getToken(), "");
  EXPECT_EQ(tokens.getLastTokenType(), TokenTypeEnum::unknown);

  tokens.push(
      new Token(Location(1, 1), TokenTypeEnum::symbolCharacterMinus, "-"));
  token = tokens.get(0);
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(tokens.getLastTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(token.getToken(), "-");

  tokens.push(new Token(Location(1, 2),
                        TokenTypeEnum::literalDecimalNumberIntegralPart,
                        "123456"));
  tokens.push(new Token(
      Location(2, 4), TokenTypeEnum::literalDecimalNumberIntegralPart, "112"));

  Token token1 = tokens.get(2);
  EXPECT_EQ(token1.getLocation().getLine(), 2ul);
  EXPECT_EQ(token1.getLocation().getColumn(), 4ul);
  EXPECT_EQ(token1.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(tokens.getLastTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token1.getToken(), "112");

  EXPECT_EQ(tokens.getTokenCnt(), 3ul);

  Tokens tokens2;
  tokens2.push(new Token(
      Location(3, 4), TokenTypeEnum::literalDecimalNumberIntegralPart, "111"));
  tokens2.push(new Token(
      Location(4, 1), TokenTypeEnum::literalDecimalNumberIntegralPart, "124"));

  tokens.push(tokens2);
  EXPECT_EQ(tokens.getTokenCnt(), 5ul);
  Token token2 = tokens.get(4);
  EXPECT_EQ(token2.getLocation().getLine(), 4ul);
  EXPECT_EQ(token2.getLocation().getColumn(), 1ul);

  tokens.popDelete();
  EXPECT_EQ(tokens.getTokenCnt(), 4ul);

  tokens.popDeleteFromPos(2);
  EXPECT_EQ(tokens.getTokenCnt(), 2ul);

  tokens.popDeleteFromPos(0);
  EXPECT_EQ(tokens.getTokenCnt(), 0ul);
};

#endif