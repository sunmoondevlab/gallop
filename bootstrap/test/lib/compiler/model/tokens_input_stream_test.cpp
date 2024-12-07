// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/tokens_input_stream.hpp"
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

using namespace gallop::Compiler;

class TokensInputStreamTest : public ::testing::Test {};
TEST_F(TokensInputStreamTest, TokensOperate) {
  Tokens tokens;
  Token *token = nullptr;
  TokensInputStream tis(tokens);
  ASSERT_EQ(tis.hasReadable(), false);
  ASSERT_EQ(tis.readable(), 0);

  tokens.push(
      new Token(Location(0, 1, 1), TokenTypeEnum::scOnelineCommentOut, U"//"));
  tokens.push(
      new Token(Location(3, 1, 4), TokenTypeEnum::coString, U"コメントアウト"));
  tokens.push(
      new Token(Location(13, 2, 2), TokenTypeEnum::reservedWord, U"fn"));
  tokens.push(new Token(Location(18, 2, 7), TokenTypeEnum::scDollar, U"$"));
  tokens.push(
      new Token(Location(19, 2, 8), TokenTypeEnum::identifier, U"nopFunc"));
  tokens.push(
      new Token(Location(27, 2, 26), TokenTypeEnum::scParenthesesOpen, U"("));
  tokens.push(
      new Token(Location(29, 2, 28), TokenTypeEnum::scParenthesesClose, U")"));
  tokens.push(
      new Token(Location(32, 3, 2), TokenTypeEnum::scCurlyBracketOpen, U"{"));
  tokens.push(new Token(Location(38, 4, 5), TokenTypeEnum::scSemiColon, U";"));
  tokens.push(
      new Token(Location(41, 5, 1), TokenTypeEnum::scCurlyBracketClose, U"}"));

  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 10);
  token = tis.read();
  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 9);
  ASSERT_EQ(token->getLocation().getLine(), 1ul);
  ASSERT_EQ(token->getLocation().getColumn(), 1ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");
  token = tis.read();
  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 8);
  ASSERT_EQ(token->getLocation().getLine(), 1ul);
  ASSERT_EQ(token->getLocation().getColumn(), 4ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"コメントアウト");
  token = tis.current();
  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 8);
  ASSERT_EQ(token->getLocation().getLine(), 2ul);
  ASSERT_EQ(token->getLocation().getColumn(), 2ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  ASSERT_EQ(token->getToken(), U"fn");
  token = tis.undo();
  ASSERT_EQ(tis.readable(), 9);
  ASSERT_EQ(token->getToken(), U"コメントアウト");
  token = tis.ahead();
  ASSERT_EQ(tis.readable(), 9);
  ASSERT_EQ(token->getToken(), U"fn");
  token = tis.ahead(1ul);
  ASSERT_EQ(tis.readable(), 9);
  ASSERT_EQ(token->getToken(), U"$");
  token = tis.ahead(7ul);
  ASSERT_EQ(tis.readable(), 9);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.ahead(8ul);
  ASSERT_EQ(tis.readable(), 9);
  ASSERT_EQ(token, nullptr);
  tis.rewind();
  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 10);
  tis.rewind(3ul);
  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 10);
  tis.skip();
  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 9);
  tis.skip(3ul);
  ASSERT_EQ(tis.hasReadable(), true);
  ASSERT_EQ(tis.readable(), 6);
  tis.markCurrent();
  tis.skip(3ul);
  tis.rewindToMark();
  token = tis.read();
  ASSERT_EQ(tis.readable(), 5);
  ASSERT_EQ(token->getToken(), U"nopFunc");
  tis.markAt(4ul);
  tis.rewindToMark();
  token = tis.read();
  ASSERT_EQ(tis.readable(), 5);
  ASSERT_EQ(token->getToken(), U"nopFunc");
  token = tis.current();
  ASSERT_EQ(tis.readable(), 5);
  ASSERT_EQ(token->getToken(), U"(");
  tis.resetMark();
  tis.rewindToMark();
  token = tis.read();
  ASSERT_EQ(tis.readable(), 9);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");
  tis.markAt(11ul);
  tis.rewindToMark();
  token = tis.read();
  ASSERT_EQ(token->getLocation().getLine(), 5ul);
  ASSERT_EQ(token->getLocation().getColumn(), 1ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scCurlyBracketClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.tail();
  ASSERT_EQ(token->getLocation().getLine(), 5ul);
  ASSERT_EQ(token->getLocation().getColumn(), 1ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scCurlyBracketClose);
  ASSERT_EQ(token->getToken(), U"}");
  ASSERT_EQ(tis.tailTokenType(), TokenTypeEnum::scCurlyBracketClose);
  token = tis.tail(1ul);
  ASSERT_EQ(token->getLocation().getLine(), 4ul);
  ASSERT_EQ(token->getLocation().getColumn(), 5ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSemiColon);
  ASSERT_EQ(token->getToken(), U";");
  ASSERT_EQ(tis.tailTokenType(1ul), TokenTypeEnum::scSemiColon);
  token = tis.tail(10ul);
  ASSERT_EQ(token->getLocation().getLine(), 1ul);
  ASSERT_EQ(token->getLocation().getColumn(), 1ul);
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");
  ASSERT_EQ(tis.tailTokenType(10ul), TokenTypeEnum::scOnelineCommentOut);

  std::vector<Token *> tokensData = tis.data();
  ASSERT_EQ(tokensData.size(), 10ul);
};
TEST_F(TokensInputStreamTest, DumpTokens) {
  Tokens tokens;
  TokensInputStream tis(tokens);

  ASSERT_EQ(tis.toStringPrintTokens(), "[]\n");
  testing::internal::CaptureStdout();
  tis.printTokens();
  ASSERT_EQ(std::string(testing::internal::GetCapturedStdout().c_str()),
            "[]\n");

  tokens.push(new Token(Location(0, 1, 1), TokenTypeEnum::scMinus, U"-"));
  tokens.push(new Token(Location(1, 1, 2), TokenTypeEnum::ltDecimalIntegralPart,
                        U"123456"));
  ASSERT_EQ(tis.toStringPrintTokens(),
            "[\n"
            "  operator(-),\n"
            "  decimal number literal(integral part): 123456 ,\n"
            "]\n");
  testing::internal::CaptureStdout();
  tis.printTokens();
  ASSERT_EQ(std::string(testing::internal::GetCapturedStdout().c_str()),
            "[\n"
            "  operator(-),\n"
            "  decimal number literal(integral part): 123456 ,\n"
            "]\n");
  ASSERT_EQ(
      tis.toStringPrintTokens(true),
      "[\n"
      "  operator(-), location::[1,1],\n"
      "  decimal number literal(integral part): 123456 , location::[1,2],\n"
      "]\n");
  testing::internal::CaptureStdout();
  tis.printTokens(true);
  ASSERT_EQ(
      std::string(testing::internal::GetCapturedStdout().c_str()),
      "[\n"
      "  operator(-), location::[1,1],\n"
      "  decimal number literal(integral part): 123456 , location::[1,2],\n"
      "]\n");

  tokens.resetTokens();
  tokens.push(
      new Token(Location("a.trot", 0, 1, 1), TokenTypeEnum::scMinus, U"-"));
  tokens.push(new Token(Location("a.trot", 1, 1, 2),
                        TokenTypeEnum::ltDecimalIntegralPart, U"123456"));
  tokens.push(new Token(Location("a.trot", 10, 1, 3),
                        TokenTypeEnum::scOnelineCommentOut, U"//"));
  tokens.push(new Token(Location("a.trot", 13, 1, 6), TokenTypeEnum::coString,
                        U"コメントアウト"));
  ASSERT_EQ(tis.toStringPrintTokens(),
            "[\n"
            "  operator(-),\n"
            "  decimal number literal(integral part): 123456 ,\n"
            "  comment out(oneline) open\"//\",\n"
            "  string of comment out: \"コメントアウト\" ,\n"
            "]\n");
  testing::internal::CaptureStdout();
  tis.printTokens();
  ASSERT_EQ(std::string(testing::internal::GetCapturedStdout().c_str()),
            "[\n"
            "  operator(-),\n"
            "  decimal number literal(integral part): 123456 ,\n"
            "  comment out(oneline) open\"//\",\n"
            "  string of comment out: \"コメントアウト\" ,\n"
            "]\n");
  ASSERT_EQ(
      tis.toStringPrintTokens(true),
      "[\n"
      "  operator(-), location::[1,1],\n"
      "  decimal number literal(integral part): 123456 , location::[1,2],\n"
      "  comment out(oneline) open\"//\", location::[1,3],\n"
      "  string of comment out: \"コメントアウト\" , location::[1,6],\n"
      "]\n");
  testing::internal::CaptureStdout();
  tis.printTokens(true);
  ASSERT_EQ(
      std::string(testing::internal::GetCapturedStdout().c_str()),
      "[\n"
      "  operator(-), location::[1,1],\n"
      "  decimal number literal(integral part): 123456 , location::[1,2],\n"
      "  comment out(oneline) open\"//\", location::[1,3],\n"
      "  string of comment out: \"コメントアウト\" , location::[1,6],\n"
      "]\n");
};
