#include "compiler/lexer/token_type.hpp"

using namespace gallop::Compiler::Lexer;

const std::map<TokenTypeEnum, std::string> TokenType::_map = {
    // unknown
    {TokenTypeEnum::unknown, "unknown token"},
    // comment out
    {TokenTypeEnum::commentOutOneline, "comment out(oneline)"},
    {TokenTypeEnum::commentOutOnelineDoc, "comment out(oneline for document)"},
    {TokenTypeEnum::commentOutBlock, "comment out(block)"},
    {TokenTypeEnum::commentOutBlockDoc, "comment out(block for document)"},
    // identifer types
    {TokenTypeEnum::identifier, "identifier"},
    // literal
    {TokenTypeEnum::literalDecimalNumberIntegralPart,
     "decimal number literal(integral part)"},
    {TokenTypeEnum::literalDecimalNumberDecimalPart,
     "decimal number literal(decimal part)"},
    {TokenTypeEnum::literalDecimalNumberExponentOperator,
     "decimal number literal(exponent operator[eE])"},
    {TokenTypeEnum::literalDecimalNumberExponentPart,
     "decimal number literal(exponent part)"},
    {TokenTypeEnum::literalBinaryPrefix, "binary number prefix(0[bB])"},
    {TokenTypeEnum::literalOctalPrefix, "octal number prefix(0[oO])"},
    {TokenTypeEnum::literalHexadecimalPrefix,
     "hexadecimal number prefix(0[xX])"},
    {TokenTypeEnum::literalBinaryNumber, "binary number literal"},
    {TokenTypeEnum::literalOctalNumber, "octal number literal"},
    {TokenTypeEnum::literalHexadecimalNumber, "hexadecimal number literal"},
    {TokenTypeEnum::literalRune, "Rune literal"},
    {TokenTypeEnum::literalString, "String literal"},
    {TokenTypeEnum::literalRegularExpressionPattern,
     "regular expression pattern literal"},
    {TokenTypeEnum::literalEscapeSequence, "escape sequence(\\.)"},
    {TokenTypeEnum::literalRuneOctalEscapeSequence,
     "octal number escape sequence(\\o)"},
    {TokenTypeEnum::literalRuneHexadecimalEscapeSequence,
     "hexadecimal number escape sequence(\\x)"},
    {TokenTypeEnum::literalRuneUnicodePointEscapeSequence,
     "unicode codepoint escape sequence(\\u)"},
    // symbolCharacter
    //  : arithmetic ope
    {TokenTypeEnum::symbolCharacterPlus, "operator(+)"},
    {TokenTypeEnum::symbolCharacterPositiveDecimalExponent,
     "operator positive exponent(+)"},
    {TokenTypeEnum::symbolCharacterPlusPercent, "operator(+%)"},
    {TokenTypeEnum::symbolCharacterPlusPipeline, "operator(+|)"},
    {TokenTypeEnum::symbolCharacterPlusEqual, "operator(+=)"},
    {TokenTypeEnum::symbolCharacterPlusPercentEqual, "operator(+%=)"},
    {TokenTypeEnum::symbolCharacterPlusPipelineEqual, "operator(+|=)"},
    {TokenTypeEnum::symbolCharacterPlusPlus, "operator(++)"},
    {TokenTypeEnum::symbolCharacterNegativeDecimalExponent,
     "operator negative exponent(-)"},
    {TokenTypeEnum::symbolCharacterMinus, "operator(-)"},
    {TokenTypeEnum::symbolCharacterMinusPercent, "operator(-%)"},
    {TokenTypeEnum::symbolCharacterMinusPipeline, "operator(-|)"},
    {TokenTypeEnum::symbolCharacterMinusEqual, "operator(-=)"},
    {TokenTypeEnum::symbolCharacterMinusPercentEqual, "operator(-%=)"},
    {TokenTypeEnum::symbolCharacterMinusPipelineEqual, "operator(-|=)"},
    {TokenTypeEnum::symbolCharacterMinusMinus, "operator(--)"},
    {TokenTypeEnum::symbolCharacterAsterisk, "operator(*)"},
    {TokenTypeEnum::symbolCharacterAsteriskPercent, "operator(*%)"},
    {TokenTypeEnum::symbolCharacterAsteriskPipeline, "operator(*|)"},
    {TokenTypeEnum::symbolCharacterAsteriskEqual, "operator(*=)"},
    {TokenTypeEnum::symbolCharacterAsteriskPercentEqual, "operator(*%=)"},
    {TokenTypeEnum::symbolCharacterAsteriskPipelineEqual, "operator(*|=)"},
    {TokenTypeEnum::symbolCharacterSlash, "operator(/)"},
    {TokenTypeEnum::symbolCharacterSlashEqual, "operator(/=)"},
    {TokenTypeEnum::symbolCharacterPercent, "operator(%)"},
    {TokenTypeEnum::symbolCharacterPercentEqual, "operator(%=)"},
    //  : bit ope, logical ope
    {TokenTypeEnum::symbolCharacterAmpersand, "operator(&)"},
    {TokenTypeEnum::symbolCharacterAmpersandEqual, "operator(&=)"},
    {TokenTypeEnum::symbolCharacterAmpersandAmpersand, "operator(&&)"},
    {TokenTypeEnum::symbolCharacterAmpersandAmpersandEqual, "operator(&&=)"},
    {TokenTypeEnum::symbolCharacterPipeline, "operator(|)"},
    {TokenTypeEnum::symbolCharacterPipelineEqual, "operator(|=)"},
    {TokenTypeEnum::symbolCharacterPipelinePipeline, "operator(||)"},
    {TokenTypeEnum::symbolCharacterPipelinePipelineEqual, "operator(||=)"},
    {TokenTypeEnum::symbolCharacterCaret, "operator(^)"},
    {TokenTypeEnum::symbolCharacterCaretEqual, "operator(^=)"},
    {TokenTypeEnum::symbolCharacterTilde, "operator(~)"},
    {TokenTypeEnum::symbolCharacterExclamation, "operator(!)"},
    {TokenTypeEnum::symbolCharacterExclamationEqual, "operator(!=)"},
    {TokenTypeEnum::symbolCharacterEqual, "operator(=)"},
    {TokenTypeEnum::symbolCharacterEqualEqual, "operator(==)"},
    {TokenTypeEnum::symbolCharacterLess, "operator(<)"},
    {TokenTypeEnum::symbolCharacterLessEqual, "operator(<=)"},
    {TokenTypeEnum::symbolCharacterLessLess, "operator(<<)"},
    {TokenTypeEnum::symbolCharacterLessLessEqual, "operator(<<=)"},
    {TokenTypeEnum::symbolCharacterLessLessPipeline, "operator(<<|)"},
    {TokenTypeEnum::symbolCharacterLessLessPipelineEqual, "operator(<<|=)"},
    {TokenTypeEnum::symbolCharacterGreater, "operator(>)"},
    {TokenTypeEnum::symbolCharacterGreaterEqual, "operator(>=)"},
    {TokenTypeEnum::symbolCharacterGreaterGreater, "operator(>>)"},
    {TokenTypeEnum::symbolCharacterGreaterGreaterEqual, "operator(>>=)"},
    //  : other symbols
    {TokenTypeEnum::symbolCharacterDoller, "operator($)"},
    {TokenTypeEnum::symbolCharacterNumbersign, "operator(#)"},
    {TokenTypeEnum::symbolCharacterQuestion, "operator(?)"},
    {TokenTypeEnum::symbolCharacterAtmark, "operator(@)"},
    {TokenTypeEnum::symbolCharacterColon, "operator(:)"},
    {TokenTypeEnum::symbolCharacterColonColon, "operator(::)"},
    {TokenTypeEnum::symbolCharacterSemicolon, "operator(;)"},
    {TokenTypeEnum::symbolCharacterComma, "operator(,)"},
    {TokenTypeEnum::symbolCharacterDot, "operator(.)"},
    {TokenTypeEnum::symbolCharacterDotDot, "operator(..)"},
    {TokenTypeEnum::symbolCharacterDotDotDot, "operator(...)"},
    {TokenTypeEnum::symbolCharacterBackslash, "operator(\\)"},
    {TokenTypeEnum::symbolCharacterUnderline, "operator(_)"},
    //  : bracket symbols
    {TokenTypeEnum::symbolCharacterSinglequote, "Rune literal separator(')"},
    {TokenTypeEnum::symbolCharacterDoublequote, "String literal separotor(\")"},
    {TokenTypeEnum::symbolCharacterBackquote,
     "regular expression separator(`)"},
    {TokenTypeEnum::symbolCharacterLeftparentheses, "parenthese open'('"},
    {TokenTypeEnum::symbolCharacterRightparentheses, "parenthese close')'"},
    {TokenTypeEnum::symbolCharacterLeftcurlybrackets, "curly bracket open'{'"},
    {TokenTypeEnum::symbolCharacterRightcurlybrackets,
     "curly bracket close'}'"},
    {TokenTypeEnum::symbolCharacterLeftsquarebrackets,
     "square bracket open'['"},
    {TokenTypeEnum::symbolCharacterRightsquarebrackets,
     "square bracket close'['"},
    //  : comment out
    {TokenTypeEnum::symbolCharacterSlashSlash,
     "comment out(oneline) open\"//\""},
    {TokenTypeEnum::symbolCharacterSlashSlashLess,
     "comment out(block) open\"//<\""},
    {TokenTypeEnum::symbolCharacterSlashSlashGreater,
     "comment out(block) close\"//>\""},
    {TokenTypeEnum::symbolCharacterSlashNumbersign,
     "comment out(oneline for document) open\"/#\""},
    {TokenTypeEnum::symbolCharacterSlashNumbersignLess,
     "comment out(block for document) open\"/#<\""},
    {TokenTypeEnum::symbolCharacterSlashNumbersignGreater,
     "comment out(block for document) close\"/#>\""},
};
std::string TokenType::getString(const enum TokenTypeEnum &tokenType) {
  if (_map.count(tokenType)) {
    return _map.at(tokenType);
  } else {
    return _map.at(TokenTypeEnum::unknown);
  }
};