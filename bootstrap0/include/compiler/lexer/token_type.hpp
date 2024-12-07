#ifndef _COMPILER_LEXER_TOKEN_TYPE_
#define _COMPILER_LEXER_TOKEN_TYPE_
#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {
namespace Lexer {

enum class TokenTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  // comment out
  commentOutOneline = 0x1 << 24,
  commentOutOnelineDoc,
  commentOutBlock,
  commentOutBlockDoc,
  // identifer types
  identifier = 0x2 << 24,
  // literal
  literalDecimalNumberIntegralPart = 0x3 << 24,
  literalDecimalNumberDecimalPart,
  literalDecimalNumberExponentOperator,
  literalDecimalNumberExponentPart,
  literalBinaryPrefix,
  literalOctalPrefix,
  literalHexadecimalPrefix,
  literalBinaryNumber,
  literalOctalNumber,
  literalHexadecimalNumber,
  literalRune,
  literalString,
  literalEscapeSequence,
  literalRegularExpressionPattern,
  literalRuneOctalEscapeSequence,
  literalRuneHexadecimalEscapeSequence,
  literalRuneUnicodePointEscapeSequence,
  // symbolCharacter
  //  : arithmetic ope
  symbolCharacterPlus = 0x4 << 24,
  symbolCharacterPositiveDecimalExponent,
  symbolCharacterPlusPercent,
  symbolCharacterPlusPipeline,
  symbolCharacterPlusEqual,
  symbolCharacterPlusPercentEqual,
  symbolCharacterPlusPipelineEqual,
  symbolCharacterPlusPlus,
  symbolCharacterNegativeDecimalExponent,
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

private:
  static const std::map<TokenTypeEnum, std::string> _map;
};

} // namespace Lexer
} // namespace Compiler
} // namespace gallop
#endif