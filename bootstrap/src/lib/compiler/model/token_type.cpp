// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/token_type.hpp"

using namespace gallop::Compiler;

const std::map<TokenTypeEnum, std::string> TokenType::_map = {
    // unknown
    {TokenTypeEnum::unknown, "unknown token"},
    {TokenTypeEnum::invalidToken, "invalid token"},
    {TokenTypeEnum::invalidEscapeSequence, "invalid escape sequence"},
    {TokenTypeEnum::unableEmptyCharInLtSingleChar,
     "unable set empty character in single character literal"},
    {TokenTypeEnum::unableLineBreakCharInLtSingleChar,
     "unable set raw line break character(\\r,\\n) in single character "
     "literal"},
    {TokenTypeEnum::unableMultipleCharInLtSingleChar,
     "unable set multiple characters in single character literal"},
    {TokenTypeEnum::notClosedLtSingleChar,
     "single character literal is not closed"},
    {TokenTypeEnum::notClosedLtUtfCharCode,
     "UTF character code literal is not closed"},
    {TokenTypeEnum::invalidUtf8CharCodeOctal,
     "invalid UTF-8 octal character code"},
    {TokenTypeEnum::invalidUtf8CharCodeHexadecimal,
     "invalid UTF-8 hexadecimal character code"},
    {TokenTypeEnum::invalidUtf16CharCodeHexadecimal,
     "invalid UTF-16 hexadecimal character code"},
    {TokenTypeEnum::invalidUtf32CharCodeHexadecimal,
     "invalid UTF-32 hexadecimal character code"},
    // comment out
    {TokenTypeEnum::coString, "string of comment out"},
    {TokenTypeEnum::coSpace, "space of comment out"},
    {TokenTypeEnum::coLineBreak, "line break(\\r,\\n) of comment out"},
    {TokenTypeEnum::coDocLineBreak,
     "line break(\\r,\\n) of documentation comment out"},
    {TokenTypeEnum::coDocTag, "tag for documentation comment"},
    // reserved word
    {TokenTypeEnum::reservedWord, "reserved word"},
    // identifer
    {TokenTypeEnum::identifier, "identifier"},
    // literal
    {TokenTypeEnum::ltDecimalIntegralPart,
     "decimal number literal(integral part)"},
    {TokenTypeEnum::ltDecimalFractionalPart,
     "decimal number literal(fractional part)"},
    {TokenTypeEnum::ltDecimalExponentOperator,
     "decimal number literal(exponent operator[eE])"},
    {TokenTypeEnum::ltExponentPart,
     "non decimal number literal(exponent operator[pP])"},
    {TokenTypeEnum::ltExponentPart, "decimal number literal(exponent part)"},
    {TokenTypeEnum::ltBinaryPrefix, "binary number prefix(0[bB])"},
    {TokenTypeEnum::ltOctalPrefix, "octal number prefix(0[oO])"},
    {TokenTypeEnum::ltHexadecimalPrefix, "hexadecimal number prefix(0[xX])"},
    {TokenTypeEnum::ltBinaryIntegralPart,
     "binary number literal(integral part)"},
    {TokenTypeEnum::ltBinaryFractionalPart,
     "binary number literal(fractional part)"},
    {TokenTypeEnum::ltOctalIntegralPart, "octal number literal(integral part)"},
    {TokenTypeEnum::ltOctalFractionalPart,
     "octal number literal(fractional part)"},
    {TokenTypeEnum::ltHexadecimalIntegralPart,
     "hexadecimal number literal(integral part)"},
    {TokenTypeEnum::ltHexadecimalFractionalPart,
     "hexadecimal number literal(fractional part)"},
    {TokenTypeEnum::ltSingleCharacter, "single character literal"},
    {TokenTypeEnum::ltString, "string literal"},
    {TokenTypeEnum::ltRawString, "string(raw) literal"},
    {TokenTypeEnum::ltEscapeSequenceNullChar, "escape sequence null char(\\0)"},
    {TokenTypeEnum::ltEscapeSequenceSingleQuotation,
     "escape sequence single quotation(\\')"},
    {TokenTypeEnum::ltEscapeSequenceDoubleQuotation,
     "escape sequence double quotation(\\\")"},
    {TokenTypeEnum::ltEscapeSequenceBackQuotation,
     "escape sequence back quotation(\\`)"},
    {TokenTypeEnum::ltEscapeSequenceBellAlert,
     "escape sequence bell alert(\\a)"},
    {TokenTypeEnum::ltEscapeSequenceBackspace,
     "escape sequence backspace(\\b)"},
    {TokenTypeEnum::ltEscapeSequenceHorizontalTab,
     "escape sequence horizontal tab(\\t)"},
    {TokenTypeEnum::ltEscapeSequenceLineFeed, "escape sequence line feed(\\n)"},
    {TokenTypeEnum::ltEscapeSequenceVerticalTab,
     "escape sequence vertical tab(\\v)"},
    {TokenTypeEnum::ltEscapeSequenceFormFeed, "escape sequence form feed(\\f)"},
    {TokenTypeEnum::ltEscapeSequenceCarriageReturn,
     "escape sequence carriage return(\\r)"},
    {TokenTypeEnum::ltEscapeSequenceAnsiEscape,
     "escape sequence ansi escape(\\e)"},
    {TokenTypeEnum::ltEscapeSequenceBackSlash,
     "escape sequence back slash(\\\\)"},
    {TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal,
     "escape sequence UTF-8 octal code(\\o)"},
    {TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal,
     "escape sequence UTF-8 hexadecimal code(\\x)"},
    {TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal,
     "escape sequence UTF-16 hexadecimal code(\\u)"},
    {TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal,
     "escape sequence UTF-32 hexadecimal code(\\U)"},
    {TokenTypeEnum::ltUtfCodeNullChar,
     "UTF code null char(\\o0,\\x0,\\u0,\\U0)"},
    {TokenTypeEnum::ltUtfCodeBellAlert,
     "UTF code bell alert(\\o7, \\x7, \\u7, \\U7)"},
    {TokenTypeEnum::ltUtfCodeBackspace,
     "UTF code backspace(\\o10, \\x8, \\u8, \\U8)"},
    {TokenTypeEnum::ltUtfCodeHorizontalTab,
     "UTF code horizontal tab(\\o11, \\x9, \\u9, \\U9)"},
    {TokenTypeEnum::ltUtfCodeLineFeed,
     "UTF code line feed(\\o12, \\xa, \\ua, \\Ua)"},
    {TokenTypeEnum::ltUtfCodeVerticalTab,
     "UTF code vertical tab(\\o13, \\xb, \\ub, \\Ub)"},
    {TokenTypeEnum::ltUtfCodeFormFeed,
     "UTF code form feed(\\o14, \\xc, \\uc, \\Uc)"},
    {TokenTypeEnum::ltUtfCodeCarriageReturn,
     "UTF code carriage return(\\o15, \\xd, \\ud, \\Ud)"},
    {TokenTypeEnum::ltUtfCodeAnsiEscape,
     "UTF code ansi escape(\\o33, \\x1b, \\u1b, \\U1b)"},
    {TokenTypeEnum::ltUtf8CodeOctal, "UTF-8 octal code(\\o)"},
    {TokenTypeEnum::ltUtf8CodeHexadecimal, "UTF-8 hexadecimal code(\\x)"},
    {TokenTypeEnum::ltUtf16CodeHexadecimal, "UTF-16 hexadecimal code(\\u)"},
    {TokenTypeEnum::ltUtf32CodeHexadecimal, "UTF-32 hexadecimal code(\\U)"},
    {TokenTypeEnum::ltUtfCodeOpen, "UTF code open'{'"},
    {TokenTypeEnum::ltUtfCodeClose, "UTF code close'}'"},
    {TokenTypeEnum::ltStringLineBreak, "line break(\\r,\\n) of string literal"},
    {TokenTypeEnum::ltRawStringLineBreak,
     "line break(\\r,\\n) of string(raw) literal"},
    // symbolCharacter
    //  : arithmetic ope
    {TokenTypeEnum::scPlus, "operator(+)"},
    {TokenTypeEnum::scPositiveDecimalExponent, "operator positive exponent(+)"},
    {TokenTypeEnum::scPlusWrapping, "operator(+%)"},
    {TokenTypeEnum::scPlusSaturating, "operator(+|)"},
    {TokenTypeEnum::scPlusAssign, "operator(+=)"},
    {TokenTypeEnum::scPlusWrappingAssign, "operator(+%=)"},
    {TokenTypeEnum::scPlusSaturatingAssign, "operator(+|=)"},
    {TokenTypeEnum::scIncrement, "operator(++)"},
    {TokenTypeEnum::scNegativeDecimal, "operator negative decimal(-)"},
    {TokenTypeEnum::scNegativeDecimalExponent, "operator negative exponent(-)"},
    {TokenTypeEnum::scMinus, "operator(-)"},
    {TokenTypeEnum::scMinusWrapping, "operator(-%)"},
    {TokenTypeEnum::scMinusSaturating, "operator(-|)"},
    {TokenTypeEnum::scMinusAssign, "operator(-=)"},
    {TokenTypeEnum::scMinusWrappingAssign, "operator(-%=)"},
    {TokenTypeEnum::scMinusSaturatingAssign, "operator(-|=)"},
    {TokenTypeEnum::scDecrement, "operator(--)"},
    {TokenTypeEnum::scMemberAccessArrow, "operator(->)"},
    {TokenTypeEnum::scMultiple, "operator(*)"},
    {TokenTypeEnum::scMultipleWrapping, "operator(*%)"},
    {TokenTypeEnum::scMultipleSaturating, "operator(*|)"},
    {TokenTypeEnum::scMultipleAssign, "operator(*=)"},
    {TokenTypeEnum::scMultipleWrappingAssign, "operator(*%=)"},
    {TokenTypeEnum::scMultipleSaturatingAssign, "operator(*|=)"},
    {TokenTypeEnum::scPower, "operator(**)"},
    {TokenTypeEnum::scPowerWrapping, "operator(**%)"},
    {TokenTypeEnum::scPowerSaturating, "operator(**|)"},
    {TokenTypeEnum::scPowerAssign, "operator(**=)"},
    {TokenTypeEnum::scPowerWrappingAssign, "operator(**%=)"},
    {TokenTypeEnum::scPowerSaturatingAssign, "operator(**|=)"},
    {TokenTypeEnum::scDivide, "operator(/)"},
    {TokenTypeEnum::scDivideAssign, "operator(/=)"},
    {TokenTypeEnum::scModulo, "operator(%)"},
    {TokenTypeEnum::scModuloAssign, "operator(%=)"},
    //  : bit ope, logical ope
    {TokenTypeEnum::scBitAnd, "operator(&)"},
    {TokenTypeEnum::scBitAndAssign, "operator(&=)"},
    {TokenTypeEnum::scLogicalAnd, "operator(&&)"},
    {TokenTypeEnum::scLogicalAndAssign, "operator(&&=)"},
    {TokenTypeEnum::scBitOr, "operator(|)"},
    {TokenTypeEnum::scBitOrAssign, "operator(|=)"},
    {TokenTypeEnum::scLogicalOr, "operator(||)"},
    {TokenTypeEnum::scLogicalOrAssign, "operator(||=)"},
    {TokenTypeEnum::scBitExOr, "operator(^)"},
    {TokenTypeEnum::scBitExOrAssign, "operator(^=)"},
    {TokenTypeEnum::scLogicalExOr, "operator(^)"},
    {TokenTypeEnum::scBitExOrAssign, "operator(^=)"},
    {TokenTypeEnum::scLogicalExOr, "operator(^^)"},
    {TokenTypeEnum::scLogicalExOrAssign, "operator(^^=)"},
    {TokenTypeEnum::scBitNot, "operator(~)"},
    {TokenTypeEnum::scBitNotAssign, "operator(~=)"},
    {TokenTypeEnum::scLogicalNotUnary, "operator(!)"},
    {TokenTypeEnum::scLogicalNotEqual, "operator(!=)"},
    {TokenTypeEnum::scAssignment, "operator(=)"},
    {TokenTypeEnum::scLogicalEqual, "operator(==)"},
    {TokenTypeEnum::scLessThan, "operator(<)"},
    {TokenTypeEnum::scLessThanEqual, "operator(<=)"},
    {TokenTypeEnum::scBitShiftLeft, "operator(<<)"},
    {TokenTypeEnum::scBitShiftLeftAssign, "operator(<<=)"},
    {TokenTypeEnum::scBitShiftLeftSaturating, "operator(<<|)"},
    {TokenTypeEnum::scBitShiftLeftSaturatingAssign, "operator(<<|=)"},
    {TokenTypeEnum::scGreaterThan, "operator(>)"},
    {TokenTypeEnum::scGreaterThanEqual, "operator(>=)"},
    {TokenTypeEnum::scArithmeticBitShiftRight, "operator(>>)"},
    {TokenTypeEnum::scArithmeticBitShiftRightAssign, "operator(>>=)"},
    {TokenTypeEnum::scLogicalBitShiftRight, "operator(>>>)"},
    {TokenTypeEnum::scLogicalBitShiftRightAssign, "operator(>>>=)"},
    //  : other symbols
    {TokenTypeEnum::scDollar, "operator($)"},
    {TokenTypeEnum::scIdentifierPrefix, "identifier prefix($)"},
    {TokenTypeEnum::scNumberSign, "operator(#)"},
    {TokenTypeEnum::scQuestion, "operator(?)"},
    {TokenTypeEnum::scAtSign, "operator(@)"},
    {TokenTypeEnum::scDocTagOpen, "doc tag open in commentout(@)"},
    {TokenTypeEnum::scColon, "operator(:)"},
    {TokenTypeEnum::scNameSpaceSeparater, "operator(::)"},
    {TokenTypeEnum::scSemiColon, "operator(;)"},
    {TokenTypeEnum::scComma, "operator(,)"},
    {TokenTypeEnum::scDot, "operator(.)"},
    {TokenTypeEnum::scDotDot, "operator(..)"},
    {TokenTypeEnum::scDotDotDot, "operator(...)"},
    {TokenTypeEnum::scBackSlash, "operator(\\)"},
    {TokenTypeEnum::scUnderline, "operator(_)"},
    //  : bracket symbols
    {TokenTypeEnum::scSingleQuotation, "single character literal separator(')"},
    {TokenTypeEnum::scDoubleQuotation, "string literal separotor(\")"},
    {TokenTypeEnum::scBackQuotation, "raw string separator(`)"},
    {TokenTypeEnum::scParenthesesOpen, "parenthese open'('"},
    {TokenTypeEnum::scParenthesesClose, "parenthese close')'"},
    {TokenTypeEnum::scCurlyBracketOpen, "curly bracket open'{'"},
    {TokenTypeEnum::scCurlyBracketClose, "curly bracket close'}'"},
    {TokenTypeEnum::scSquareBracketOpen, "square bracket open'['"},
    {TokenTypeEnum::scSquareBracketClose, "square bracket close'['"},
    //  : comment out
    {TokenTypeEnum::scOnelineCommentOut, "comment out(oneline) open\"//\""},
    {TokenTypeEnum::scBlockCommentOutOpen, "comment out(block) open\"//<\""},
    {TokenTypeEnum::scBlockCommentOutClose, "comment out(block) close\"//>\""},
    {TokenTypeEnum::scOnelineCommentOutDoc,
     "comment out(oneline for document) open\"/#\""},
    {TokenTypeEnum::scOnelineCommentOutDocTopLevel,
     "comment out(oneline for document top level) open\"/#!\""},
    {TokenTypeEnum::scBlockCommentOutDocOpenTopLevel,
     "comment out(block for document top level) open\"/#!<\""},
    {TokenTypeEnum::scBlockCommentOutDocOpen,
     "comment out(block for document) open\"/#<\""},
    {TokenTypeEnum::scBlockCommentOutDocClose,
     "comment out(block for document) close\"/#>\""},
};
std::string TokenType::getString(const enum TokenTypeEnum &tokenType_) {
  if (_map.count(tokenType_)) {
    return _map.at(tokenType_);
  } else {
    return _map.at(TokenTypeEnum::unknown);
  }
};
bool TokenType::isSymbolCharacterToken(const enum TokenTypeEnum &tokenType_) {
  return (uint32_t(tokenType_) >> ConstForTypeEnum::BitShift) ==
         static_cast<uint8_t>(TokenTypeCategoryEnum::symbolCharacter);
};
bool TokenType::isCommentOutOnelineOpen(const enum TokenTypeEnum &tokenType_) {
  return tokenType_ == TokenTypeEnum::scOnelineCommentOut ||
         tokenType_ == TokenTypeEnum::scOnelineCommentOutDoc ||
         tokenType_ == TokenTypeEnum::scOnelineCommentOutDocTopLevel;
};
bool TokenType::isCommentOutBlockOpen(const enum TokenTypeEnum &tokenType_) {
  return tokenType_ == TokenTypeEnum::scBlockCommentOutOpen ||
         tokenType_ == TokenTypeEnum::scBlockCommentOutDocOpen ||
         tokenType_ == TokenTypeEnum::scBlockCommentOutDocOpenTopLevel;
};
bool TokenType::isCommentOutOpenForDoc(const enum TokenTypeEnum &tokenType_) {
  return tokenType_ == TokenTypeEnum::scOnelineCommentOutDoc ||
         tokenType_ == TokenTypeEnum::scBlockCommentOutDocOpen;
};
bool TokenType::isCommentOutOpenForDocTopLevel(
    const enum TokenTypeEnum &tokenType_) {
  return tokenType_ == TokenTypeEnum::scOnelineCommentOutDocTopLevel ||
         tokenType_ == TokenTypeEnum::scBlockCommentOutDocOpenTopLevel;
};
bool TokenType::isCommentOut(const enum TokenTypeEnum &tokenType_) {
  return (uint32_t(tokenType_) >> ConstForTypeEnum::BitShift) ==
         static_cast<uint8_t>(TokenTypeCategoryEnum::commentOut);
};

bool TokenType::isLineBreak(const enum TokenTypeEnum &tokenType_) {
  return tokenType_ == TokenTypeEnum::coLineBreak ||
         tokenType_ == TokenTypeEnum::coDocLineBreak ||
         tokenType_ == TokenTypeEnum::ltStringLineBreak ||
         tokenType_ == TokenTypeEnum::ltRawStringLineBreak;
};
