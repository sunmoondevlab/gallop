// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/tokens.hpp"
#include <gtest/gtest.h>

#include "compiler/model/location.hpp"
#include "compiler/model/token_type.hpp"

using namespace gallop::Compiler;

class TokensTest : public ::testing::Test {};
TEST_F(TokensTest, Tokens) {
  Tokens tokens;
  Token **tokensPtr = nullptr;
  Token *token = nullptr;
  ASSERT_EQ(tokens.getTokenCount(), 0ul);

  tokens.push(
      new Token(Location(0, 1, 1), TokenTypeEnum::scOnelineCommentOut, U"//"));
  ASSERT_EQ(tokens.getTokenCount(), 1ul);
  tokensPtr = tokens.getTokens().data();
  token = *(tokensPtr);
  ASSERT_EQ(token->getLocation().getLine(), 1ul);
  ASSERT_EQ(token->getLocation().getColumn(), 1ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");

  tokens.push(
      new Token(Location(3, 1, 4), TokenTypeEnum::coString, U"コメントアウト"));

  tokens.push(
      new Token(Location(13, 2, 2), TokenTypeEnum::reservedWord, U"fn"));

  tokensPtr = tokens.getTokens().data();
  token = *(tokensPtr + 2);
  ASSERT_EQ(token->getLocation().getLine(), 2ul);
  ASSERT_EQ(token->getLocation().getColumn(), 2ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  ASSERT_EQ(token->getToken(), U"fn");

  ASSERT_EQ(tokens.getTokenCount(), 3ul);

  tokens.push(new Token(Location(18, 2, 7), TokenTypeEnum::scDollar, U"$"));
  tokens.push(
      new Token(Location(19, 2, 8), TokenTypeEnum::identifier, U"nopFunc"));
  ASSERT_EQ(tokens.getTokenCount(), 5ul);
  tokensPtr = tokens.getTokens().data();
  token = *(tokensPtr + 4);
  ASSERT_EQ(token->getLocation().getLine(), 2ul);
  ASSERT_EQ(token->getLocation().getColumn(), 8ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token->getToken(), U"nopFunc");

  tokens.deleteLast();
  ASSERT_EQ(tokens.getTokenCount(), 4ul);
  tokens.deleteLast((size_t)2);
  ASSERT_EQ(tokens.getTokenCount(), 2ul);
  tokens.resetTokens();

  ASSERT_EQ(tokens.getTokenCount(), 0ul);
};
