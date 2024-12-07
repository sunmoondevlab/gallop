// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_LEXER_TOKEN_TYPE_
#define _COMPILER_LEXER_TOKEN_TYPE_
#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {
namespace Lexer {

namespace TokenTypeCategoryEnum {
static const uint8_t commentOut = 1;
static const uint8_t keyword = 2;
static const uint8_t identifier = 3;
static const uint8_t literal = 4;
static const uint8_t symbolCharacter = 5;

} // namespace TokenTypeCategoryEnum
enum class TokenTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  // comment out
  commentOutOneline = (TokenTypeCategoryEnum::commentOut << 24) + 1,
  commentOutOnelineDoc,
  commentOutBlock,
  commentOutBlockDoc,
  // keyword
  keyword = (TokenTypeCategoryEnum::keyword << 24) + 1,
  // identifer
  identifier = (TokenTypeCategoryEnum::identifier << 24) + 1,
  // literal
  literalDecimalNumberIntegralPart = (TokenTypeCategoryEnum::literal << 24) + 1,
  literalDecimalNumberDecimalPart,
  literalDecimalNumberExponentOperator,
  literalNonDecimalNumberExponentOperator,
  literalDecimalNumberExponentPart,
  literalBinaryPrefix,
  literalOctalPrefix,
  literalHexadecimalPrefix,
  literalBinaryNumber,
  literalOctalNumber,
  literalHexadecimalNumber,
  literalCharCode,
  literalString,
  literalEscapeSequence,
  literalRawString,
  literalCharCodeOctalEscapeSequence,
  literalCharCodeHexadecimalEscapeSequence,
  literalCharCodeUnicodePointEscapeSequence,
  // symbolCharacter
  //  : arithmetic ope
  symbolCharacterPlus = (TokenTypeCategoryEnum::symbolCharacter << 24) + 1,
  symbolCharacterPositiveDecimalExponent,
  symbolCharacterPlusPercent,
  symbolCharacterPlusPipeline,
  symbolCharacterPlusEqual,
  symbolCharacterPlusPercentEqual,
  symbolCharacterPlusPipelineEqual,
  symbolCharacterPlusPlus,
  symbolCharacterNegativeDecimalExponent,
  symbolCharacterNegativeDecimal,
  symbolCharacterMinus,
  symbolCharacterMinusPercent,
  symbolCharacterMinusPipeline,
  symbolCharacterMinusEqual,
  symbolCharacterMinusPercentEqual,
  symbolCharacterMinusPipelineEqual,
  symbolCharacterMinusMinus,
  symbolCharacterAsterisk,
  symbolCharacterAsteriskPercent,
  symbolCharacterAsteriskPipeline,
  symbolCharacterAsteriskEqual,
  symbolCharacterAsteriskPercentEqual,
  symbolCharacterAsteriskPipelineEqual,
  symbolCharacterSlash,
  symbolCharacterSlashEqual,
  symbolCharacterPercent,
  symbolCharacterPercentEqual,
  //  : bit ope, logical ope
  symbolCharacterAmpersand,
  symbolCharacterAmpersandEqual,
  symbolCharacterAmpersandAmpersand,
  symbolCharacterAmpersandAmpersandEqual,
  symbolCharacterPipeline,
  symbolCharacterPipelineEqual,
  symbolCharacterPipelinePipeline,
  symbolCharacterPipelinePipelineEqual,
  symbolCharacterCaret,
  symbolCharacterCaretEqual,
  symbolCharacterTilde,
  symbolCharacterExclamation,
  symbolCharacterExclamationEqual,
  symbolCharacterEqual,
  symbolCharacterEqualEqual,
  symbolCharacterLess,
  symbolCharacterLessEqual,
  symbolCharacterLessLess,
  symbolCharacterLessLessEqual,
  symbolCharacterLessLessPipeline,
  symbolCharacterLessLessPipelineEqual,
  symbolCharacterGreater,
  symbolCharacterGreaterEqual,
  symbolCharacterGreaterGreater,
  symbolCharacterGreaterGreaterEqual,
  symbolCharacterGreaterGreaterGreater,
  //  : other symbols
  symbolCharacterDoller,
  symbolCharacterNumbersign,
  symbolCharacterQuestion,
  symbolCharacterAtmark,
  symbolCharacterColon,
  symbolCharacterColonColon,
  symbolCharacterSemicolon,
  symbolCharacterComma,
  symbolCharacterDot,
  symbolCharacterDotDot,
  symbolCharacterDotDotDot,
  symbolCharacterBackslash,
  symbolCharacterUnderline,
  //  : bracket symbols
  symbolCharacterSinglequote,
  symbolCharacterDoublequote,
  symbolCharacterBackquote,
  symbolCharacterLeftparentheses,
  symbolCharacterRightparentheses,
  symbolCharacterLeftcurlybrackets,
  symbolCharacterRightcurlybrackets,
  symbolCharacterLeftsquarebrackets,
  symbolCharacterRightsquarebrackets,
  //  : comment out
  symbolCharacterSlashSlash,
  symbolCharacterSlashSlashLess,
  symbolCharacterSlashSlashGreater,
  symbolCharacterSlashNumbersign,
  symbolCharacterSlashNumbersignLess,
  symbolCharacterSlashNumbersignGreater,
};

class TokenType final {
public:
  TokenType() = delete;
  ~TokenType() = delete;
  static std::string getString(const enum TokenTypeEnum &tokenType);
  static bool isSymbolCharacterToken(const enum TokenTypeEnum &tokenType);
  static bool isCommentOut(const enum TokenTypeEnum &tokenType);
  static bool isCharCodesDelimiter(const enum TokenTypeEnum &tokenType);

private:
  static const std::map<TokenTypeEnum, std::string> _map;
};

} // namespace Lexer
} // namespace Compiler
} // namespace gallop
#endif