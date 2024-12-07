// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/token_type.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;

class TokenTypeTest : public ::testing::Test {};
TEST_F(TokenTypeTest, TokenString) {
  ASSERT_EQ(TokenType::getString(TokenTypeEnum::unknown), "unknown token");

  ASSERT_EQ(TokenType::getString(TokenTypeEnum::coString),
            "string of comment out");

  ASSERT_EQ(TokenType::getString(TokenTypeEnum::scPlus), "operator(+)");
  ASSERT_EQ(TokenType::getString(TokenTypeEnum::scPlusWrappingAssign),
            "operator(+%=)");

  ASSERT_EQ(TokenType::getString(TokenTypeEnum::scCurlyBracketOpen),
            "curly bracket open'{'");
  ASSERT_EQ(TokenType::getString(TokenTypeEnum::scSquareBracketOpen),
            "square bracket open'['");

  ASSERT_EQ(TokenType::getString(TokenTypeEnum::ltDecimalIntegralPart),
            "decimal number literal(integral part)");
  ASSERT_EQ(TokenType::getString(TokenTypeEnum::ltDecimalFractionalPart),
            "decimal number literal(fractional part)");

  ASSERT_EQ(
      TokenType::getString(TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal),
      "escape sequence UTF-16 hexadecimal code(\\u)");
  ASSERT_EQ(TokenType::getString(TokenTypeEnum::ltRawString),
            "string(raw) literal");
};
TEST_F(TokenTypeTest, IsSymbolCharacterToken) {
  ASSERT_EQ(TokenType::isSymbolCharacterToken(
                TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal),
            false);
  ASSERT_EQ(TokenType::isSymbolCharacterToken(
                TokenTypeEnum::scBlockCommentOutDocClose),
            true);
};
TEST_F(TokenTypeTest, IsCommentOut) {
  ASSERT_EQ(TokenType::isCommentOut(
                TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal),
            false);
  ASSERT_EQ(TokenType::isCommentOut(TokenTypeEnum::coString), true);
};
TEST_F(TokenTypeTest, IsCommentOutOnelineOpen) {
  ASSERT_EQ(
      TokenType::isCommentOutOnelineOpen(TokenTypeEnum::scBlockCommentOutOpen),
      false);
  ASSERT_EQ(
      TokenType::isCommentOutOnelineOpen(TokenTypeEnum::scOnelineCommentOut),
      true);
  ASSERT_EQ(
      TokenType::isCommentOutOnelineOpen(TokenTypeEnum::scOnelineCommentOutDoc),
      true);
  ASSERT_EQ(TokenType::isCommentOutOnelineOpen(
                TokenTypeEnum::scOnelineCommentOutDocTopLevel),
            true);
};
TEST_F(TokenTypeTest, IsCommentOutBlockOpen) {
  ASSERT_EQ(
      TokenType::isCommentOutBlockOpen(TokenTypeEnum::scOnelineCommentOut),
      false);
  ASSERT_EQ(
      TokenType::isCommentOutBlockOpen(TokenTypeEnum::scBlockCommentOutOpen),
      true);
  ASSERT_EQ(
      TokenType::isCommentOutBlockOpen(TokenTypeEnum::scBlockCommentOutDocOpen),
      true);
  ASSERT_EQ(TokenType::isCommentOutBlockOpen(
                TokenTypeEnum::scBlockCommentOutDocOpenTopLevel),
            true);
};
TEST_F(TokenTypeTest, IsCommentOutOpenForDoc) {
  ASSERT_EQ(
      TokenType::isCommentOutOpenForDoc(TokenTypeEnum::scBlockCommentOutOpen),
      false);
  ASSERT_EQ(
      TokenType::isCommentOutOpenForDoc(TokenTypeEnum::scOnelineCommentOutDoc),
      true);
  ASSERT_EQ(TokenType::isCommentOutOpenForDoc(
                TokenTypeEnum::scBlockCommentOutDocOpen),
            true);
};
TEST_F(TokenTypeTest, IsCommentOutOpenForDocTopLevel) {
  ASSERT_EQ(TokenType::isCommentOutOpenForDocTopLevel(
                TokenTypeEnum::scBlockCommentOutOpen),
            false);
  ASSERT_EQ(TokenType::isCommentOutOpenForDocTopLevel(
                TokenTypeEnum::scOnelineCommentOutDocTopLevel),
            true);
  ASSERT_EQ(TokenType::isCommentOutOpenForDocTopLevel(
                TokenTypeEnum::scBlockCommentOutDocOpenTopLevel),
            true);
};
