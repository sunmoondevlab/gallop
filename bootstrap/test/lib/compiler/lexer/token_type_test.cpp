#if 0
#include "compiler/lexer/token_type.hpp"
#include <gtest/gtest.h>

namespace gallop {
namespace Compiler {
namespace Lexer {

class TokenTypeTest : public ::testing::Test {};
TEST_F(TokenTypeTest, TokenStringCheck) {
  EXPECT_EQ(TokenType::getString(TokenTypeEnum::unknown), "unknown token");

  EXPECT_EQ(TokenType::getString(TokenTypeEnum::commentOutOneline),
            "comment out(oneline)");
  EXPECT_EQ(TokenType::getString(TokenTypeEnum::commentOutBlock),
            "comment out(block)");

  EXPECT_EQ(TokenType::getString(TokenTypeEnum::symbolCharacterPlus),
            "operator(+)");
  EXPECT_EQ(
      TokenType::getString(TokenTypeEnum::symbolCharacterPlusPercentEqual),
      "operator(+%=)");

  EXPECT_EQ(
      TokenType::getString(TokenTypeEnum::symbolCharacterLeftcurlybrackets),
      "curly bracket open'{'");
  EXPECT_EQ(
      TokenType::getString(TokenTypeEnum::symbolCharacterLeftsquarebrackets),
      "square bracket open'['");

  EXPECT_EQ(
      TokenType::getString(TokenTypeEnum::literalDecimalNumberIntegralPart),
      "decimal number literal(integral part)");
  EXPECT_EQ(
      TokenType::getString(TokenTypeEnum::literalDecimalNumberDecimalPart),
      "decimal number literal(decimal part)");
};

} // namespace Lexer
} // namespace Compiler
} // namespace gallop
#endif