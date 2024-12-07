// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_TOKEN_TYPE_
#define _COMPILER_MODEL_TOKEN_TYPE_

#include "compiler/model/const_for_type_enum.hpp"

#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {

enum class TokenTypeCategoryEnum : uint8_t {
  commentOut = 1,
  reservedWord,
  identifier,
  literal,
  symbolCharacter,
};
enum class TokenTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  invalidToken,
  invalidEscapeSequence,
  unableEmptyCharInLtSingleChar,
  unableLineBreakCharInLtSingleChar,
  unableMultipleCharInLtSingleChar,
  notClosedLtSingleChar,
  notClosedLtUtfCharCode,
  invalidUtf8CharCodeOctal,
  invalidUtf8CharCodeHexadecimal,
  invalidUtf16CharCodeHexadecimal,
  invalidUtf32CharCodeHexadecimal,
  // comment out
  coString = (static_cast<uint8_t>(TokenTypeCategoryEnum::commentOut)
              << ConstForTypeEnum::BitShift) +
             1,
  coSpace,
  coDocLineBreak,
  coLineBreak,
  coDocTag,
  // reserved word
  reservedWord = (static_cast<uint8_t>(TokenTypeCategoryEnum::reservedWord)
                  << ConstForTypeEnum::BitShift) +
                 1,
  // identifer
  identifier = (static_cast<uint8_t>(TokenTypeCategoryEnum::identifier)
                << ConstForTypeEnum::BitShift) +
               1,
  // literal
  ltDecimalIntegralPart = (static_cast<uint8_t>(TokenTypeCategoryEnum::literal)
                           << ConstForTypeEnum::BitShift) +
                          1,
  ltDecimalFractionalPart,
  ltDecimalExponentOperator,
  ltNonDecimalExponentOperator,
  ltExponentPart,
  ltBinaryPrefix,
  ltOctalPrefix,
  ltHexadecimalPrefix,
  ltBinaryIntegralPart,
  ltBinaryFractionalPart,
  ltOctalIntegralPart,
  ltOctalFractionalPart,
  ltHexadecimalIntegralPart,
  ltHexadecimalFractionalPart,
  ltSingleCharacter,
  ltString,
  ltRawString,
  ltEscapeSequenceNullChar,
  ltEscapeSequenceSingleQuotation,
  ltEscapeSequenceDoubleQuotation,
  ltEscapeSequenceBackQuotation,
  ltEscapeSequenceBellAlert,
  ltEscapeSequenceBackspace,
  ltEscapeSequenceHorizontalTab,
  ltEscapeSequenceLineFeed,
  ltEscapeSequenceVerticalTab,
  ltEscapeSequenceFormFeed,
  ltEscapeSequenceCarriageReturn,
  ltEscapeSequenceAnsiEscape,
  ltEscapeSequenceBackSlash,
  ltEscapeSequenceUtf8CodeOctal,
  ltEscapeSequenceUtf8CodeHexadecimal,
  ltEscapeSequenceUtf16CodeHexadecimal,
  ltEscapeSequenceUtf32CodeHexadecimal,
  ltUtfCodeNullChar,
  ltUtfCodeBellAlert,
  ltUtfCodeBackspace,
  ltUtfCodeHorizontalTab,
  ltUtfCodeLineFeed,
  ltUtfCodeVerticalTab,
  ltUtfCodeFormFeed,
  ltUtfCodeCarriageReturn,
  ltUtfCodeAnsiEscape,
  ltUtf8CodeOctal,
  ltUtf8CodeHexadecimal,
  ltUtf16CodeHexadecimal,
  ltUtf32CodeHexadecimal,
  ltUtfCodeOpen,
  ltUtfCodeClose,
  ltStringLineBreak,
  ltRawStringLineBreak,
  // symbolCharacter
  //  : arithmetic ope
  scPlus = (static_cast<uint8_t>(TokenTypeCategoryEnum::symbolCharacter)
            << ConstForTypeEnum::BitShift) +
           1,
  scPositiveDecimalExponent,
  scPlusWrapping,
  scPlusSaturating,
  scPlusAssign,
  scPlusWrappingAssign,
  scPlusSaturatingAssign,
  scIncrement,
  scNegativeDecimal,
  scNegativeDecimalExponent,
  scMinus,
  scMinusWrapping,
  scMinusSaturating,
  scMinusAssign,
  scMinusWrappingAssign,
  scMinusSaturatingAssign,
  scDecrement,
  scMemberAccessArrow,
  scMultiple,
  scMultipleWrapping,
  scMultipleSaturating,
  scMultipleAssign,
  scMultipleWrappingAssign,
  scMultipleSaturatingAssign,
  scPower,
  scPowerWrapping,
  scPowerSaturating,
  scPowerAssign,
  scPowerWrappingAssign,
  scPowerSaturatingAssign,
  scDivide,
  scDivideAssign,
  scModulo,
  scModuloAssign,
  //  : bit ope, logical ope
  scBitAnd,
  scBitAndAssign,
  scLogicalAnd,
  scLogicalAndAssign,
  scBitOr,
  scBitOrAssign,
  scLogicalOr,
  scLogicalOrAssign,
  scBitExOr,
  scBitExOrAssign,
  scLogicalExOr,
  scLogicalExOrAssign,
  scBitNot,
  scBitNotAssign,
  scLogicalNotUnary,
  scLogicalNotEqual,
  scAssignment,
  scLogicalEqual,
  scLessThan,
  scLessThanEqual,
  scBitShiftLeft,
  scBitShiftLeftAssign,
  scBitShiftLeftSaturating,
  scBitShiftLeftSaturatingAssign,
  scGreaterThan,
  scGreaterThanEqual,
  scArithmeticBitShiftRight,
  scArithmeticBitShiftRightAssign,
  scLogicalBitShiftRight,
  scLogicalBitShiftRightAssign,
  //  : other symbols
  scDollar,
  scIdentifierPrefix,
  scNumberSign,
  scQuestion,
  scAtSign,
  scDocTagOpen,
  scColon,
  scNameSpaceSeparater,
  scSemiColon,
  scComma,
  scDot,
  scDotDot,
  scDotDotDot,
  scBackSlash,
  scUnderline,
  //  : bracket symbols
  scSingleQuotation,
  scDoubleQuotation,
  scBackQuotation,
  scParenthesesOpen,
  scParenthesesClose,
  scCurlyBracketOpen,
  scCurlyBracketClose,
  scSquareBracketOpen,
  scSquareBracketClose,
  //  : comment out
  scOnelineCommentOut,
  scBlockCommentOutOpen,
  scBlockCommentOutClose,
  scOnelineCommentOutDoc,
  scOnelineCommentOutDocTopLevel,
  scBlockCommentOutDocOpenTopLevel,
  scBlockCommentOutDocOpen,
  scBlockCommentOutDocClose,
};

class TokenType final {
public:
  TokenType() = delete;
  ~TokenType() = delete;
  static std::string getString(const enum TokenTypeEnum &tokenType);
  static bool isSymbolCharacterToken(const enum TokenTypeEnum &tokenType);
  static bool isCommentOutOnelineOpen(const enum TokenTypeEnum &tokenType);
  static bool isCommentOutBlockOpen(const enum TokenTypeEnum &tokenType);
  static bool isCommentOutOpenForDoc(const enum TokenTypeEnum &tokenType);
  static bool
  isCommentOutOpenForDocTopLevel(const enum TokenTypeEnum &tokenType);
  static bool isCommentOut(const enum TokenTypeEnum &tokenType);
  static bool isLineBreak(const enum TokenTypeEnum &tokenType);

private:
  static const std::map<TokenTypeEnum, std::string> _map;
};

} // namespace Compiler
} // namespace gallop
#endif