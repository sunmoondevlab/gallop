#include "compiler/parser/ast_node_type.hpp"

using namespace gallop::Compiler::Parser;

const std::map<AstNodeTypeEnum, std::string> AstNodeType::_map = {
    // unknown
    {AstNodeTypeEnum::unknown, "Unknown"},
    // root node
    {AstNodeTypeEnum::rootFile, "Root(File)"},
    {AstNodeTypeEnum::rootStdin, "Root(Stdin)"},
    {AstNodeTypeEnum::rootInterpreter, "Root(Interpreter)"},
    // module
    {AstNodeTypeEnum::moduleFile, "Module(File)"},
    {AstNodeTypeEnum::moduleStdin, "Module(Stdin)"},
    {AstNodeTypeEnum::moduleInterpreter, "Module(Interpreter)"},
    // comment out
    {AstNodeTypeEnum::commentOutOneline, "CommentOut"},
    {AstNodeTypeEnum::commentOutOnelineDoc, "CommentOut For Doc"},
    {AstNodeTypeEnum::commentOutBlock, "CommentOut"},
    {AstNodeTypeEnum::commentOutBlockDoc, "CommentOut For Doc"},
    // block fmain
    {AstNodeTypeEnum::blockFmain, "fmain"},

};
std::map<AstNodeTypeEnum, std::string> map = {
    // unknown
    {AstNodeTypeEnum::unknown, "unknown token"},
    // comment out
    {AstNodeTypeEnum::commentOutOneline, "comment out(oneline)"},
    {AstNodeTypeEnum::commentOutOnelineDoc,
     "comment out(oneline for document)"},
    {AstNodeTypeEnum::commentOutBlock, "comment out(block)"},
    {AstNodeTypeEnum::commentOutBlockDoc, "comment out(block for document)"},
    // identifer types
    {AstNodeTypeEnum::identifier, "identifier"},
    {AstNodeTypeEnum::builtinTypesBool, "builtin type(bool)"},
    {AstNodeTypeEnum::builtinTypesI4, "builtin type(i4)"},
    {AstNodeTypeEnum::builtinTypesU4, "builtin type(u4)"},
    {AstNodeTypeEnum::builtinTypesI8, "builtin type(i8)"},
    {AstNodeTypeEnum::builtinTypesU8, "builtin type(u8)"},
    {AstNodeTypeEnum::builtinTypesI16, "builtin type(i16)"},
    {AstNodeTypeEnum::builtinTypesU16, "builtin type(u16)"},
    {AstNodeTypeEnum::builtinTypesI32, "builtin type(i32)"},
    {AstNodeTypeEnum::builtinTypesU32, "builtin type(u32)"},
    {AstNodeTypeEnum::builtinTypesI64, "builtin type(i64)"},
    {AstNodeTypeEnum::builtinTypesU64, "builtin type(u64)"},
    {AstNodeTypeEnum::builtinTypesF32, "builtin type(f32)"},
    {AstNodeTypeEnum::builtinTypesF64, "builtin type(f64)"},
    {AstNodeTypeEnum::builtinTypesRune, "builtin type(Rune)"},
    {AstNodeTypeEnum::builtinTypesString, "builtin type(String)"},
    {AstNodeTypeEnum::reservedWordsFmain, "reserved words: fmain"},
    {AstNodeTypeEnum::reservedWordsExit, "reserved words: exit"},
    {AstNodeTypeEnum::reservedWordsStatic, "reserved words: static"},
    {AstNodeTypeEnum::reservedWordsPublic, "reserved words: public"},
    {AstNodeTypeEnum::reservedWordsProtected, "reserved words: protected"},
    {AstNodeTypeEnum::reservedWordsStruct, "reserved words: struct"},
    {AstNodeTypeEnum::reservedWordsEnum, "reserved words: enum"},
    {AstNodeTypeEnum::reservedWordsTypeof, "reserved words: typeof"},
    {AstNodeTypeEnum::reservedWordsTypedef, "reserved words: typedef"},
    {AstNodeTypeEnum::reservedWordsFunc, "reserved words: func"},
    {AstNodeTypeEnum::reservedWordsReturn, "reserved words: return"},
    {AstNodeTypeEnum::reservedWordsImport, "reserved words: import"},
    {AstNodeTypeEnum::reservedWordsIf, "reserved words: if"},
    {AstNodeTypeEnum::reservedWordsElse, "reserved words: else"},
    {AstNodeTypeEnum::reservedWordsSwitch, "reserved words: switch"},
    {AstNodeTypeEnum::reservedWordsCase, "reserved words: case"},
    {AstNodeTypeEnum::reservedWordsDefault, "reserved words: default"},
    {AstNodeTypeEnum::reservedWordsFor, "reserved words: for"},
    {AstNodeTypeEnum::reservedWordsWhile, "reserved words: while"},
    {AstNodeTypeEnum::reservedWordsBreak, "reserved words: break"},
    {AstNodeTypeEnum::reservedWordsContinue, "reserved words: continue"},
    {AstNodeTypeEnum::reservedWordsTrue, "reserved words: true"},
    {AstNodeTypeEnum::reservedWordsFalse, "reserved words: false"},
    // literal
    {AstNodeTypeEnum::literalDecimalNumberIntegralPart,
     "decimal number literal(integral part)"},
    {AstNodeTypeEnum::literalDecimalNumberDecimalPart,
     "decimal number literal(decimal part)"},
    {AstNodeTypeEnum::literalDecimalNumberExponentOperator,
     "decimal number literal(exponent operator[eE])"},
    {AstNodeTypeEnum::literalDecimalNumberExponentPart,
     "decimal number literal(exponent part)"},
    {AstNodeTypeEnum::literalBinaryPrefix, "binary number prefix(0[bB])"},
    {AstNodeTypeEnum::literalOctalPrefix, "octal number prefix(0[oO])"},
    {AstNodeTypeEnum::literalHexadecimalPrefix,
     "hexadecimal number prefix(0[xX])"},
    {AstNodeTypeEnum::literalBinaryNumber, "binary number literal"},
    {AstNodeTypeEnum::literalOctalNumber, "octal number literal"},
    {AstNodeTypeEnum::literalHexadecimalNumber, "hexadecimal number literal"},
    {AstNodeTypeEnum::literalRune, "Rune literal"},
    {AstNodeTypeEnum::literalString, "String literal"},
    {AstNodeTypeEnum::literalRegularExpressionPattern,
     "regular expression pattern literal"},
    {AstNodeTypeEnum::literalEscapeSequence, "escape sequence(\\.)"},
    {AstNodeTypeEnum::literalRuneOctalEscapeSequence,
     "octal number escape sequence(\\o)"},
    {AstNodeTypeEnum::literalRuneHexadecimalEscapeSequence,
     "hexadecimal number escape sequence(\\x)"},
    {AstNodeTypeEnum::literalRuneUnicodePointEscapeSequence,
     "unicode codepoint escape sequence(\\u)"},
    // symbolCharacter
    //  : arithmetic ope
    {AstNodeTypeEnum::symbolCharacterPlus, "operator(+)"},
    {AstNodeTypeEnum::symbolCharacterPositiveDecimalExponent,
     "operator positive exponent(+)"},
    {AstNodeTypeEnum::symbolCharacterPlusPercent, "operator(+%)"},
    {AstNodeTypeEnum::symbolCharacterPlusPipeline, "operator(+|)"},
    {AstNodeTypeEnum::symbolCharacterPlusEqual, "operator(+=)"},
    {AstNodeTypeEnum::symbolCharacterPlusPercentEqual, "operator(+%=)"},
    {AstNodeTypeEnum::symbolCharacterPlusPipelineEqual, "operator(+|=)"},
    {AstNodeTypeEnum::symbolCharacterPlusPlus, "operator(++)"},
    {AstNodeTypeEnum::symbolCharacterNegativeDecimalNumber,
     "operator negative number(-)"},
    {AstNodeTypeEnum::symbolCharacterNegativeDecimalExponent,
     "operator negative exponent(-)"},
    {AstNodeTypeEnum::symbolCharacterMinus, "operator(-)"},
    {AstNodeTypeEnum::symbolCharacterMinusPercent, "operator(-%)"},
    {AstNodeTypeEnum::symbolCharacterMinusPipeline, "operator(-|)"},
    {AstNodeTypeEnum::symbolCharacterMinusEqual, "operator(-=)"},
    {AstNodeTypeEnum::symbolCharacterMinusPercentEqual, "operator(-%=)"},
    {AstNodeTypeEnum::symbolCharacterMinusPipelineEqual, "operator(-|=)"},
    {AstNodeTypeEnum::symbolCharacterMinusMinus, "operator(--)"},
    {AstNodeTypeEnum::symbolCharacterAsterisk, "operator(*)"},
    {AstNodeTypeEnum::symbolCharacterAsteriskPercent, "operator(*%)"},
    {AstNodeTypeEnum::symbolCharacterAsteriskPipeline, "operator(*|)"},
    {AstNodeTypeEnum::symbolCharacterAsteriskEqual, "operator(*=)"},
    {AstNodeTypeEnum::symbolCharacterAsteriskPercentEqual, "operator(*%=)"},
    {AstNodeTypeEnum::symbolCharacterAsteriskPipelineEqual, "operator(*|=)"},
    {AstNodeTypeEnum::symbolCharacterSlash, "operator(/)"},
    {AstNodeTypeEnum::symbolCharacterSlashEqual, "operator(/=)"},
    {AstNodeTypeEnum::symbolCharacterPercent, "operator(%)"},
    {AstNodeTypeEnum::symbolCharacterPercentEqual, "operator(%=)"},
    //  : bit ope, logical ope
    {AstNodeTypeEnum::symbolCharacterAmpersand, "operator(&)"},
    {AstNodeTypeEnum::symbolCharacterAmpersandEqual, "operator(&=)"},
    {AstNodeTypeEnum::symbolCharacterAmpersandAmpersand, "operator(&&)"},
    {AstNodeTypeEnum::symbolCharacterAmpersandAmpersandEqual, "operator(&&=)"},
    {AstNodeTypeEnum::symbolCharacterPipeline, "operator(|)"},
    {AstNodeTypeEnum::symbolCharacterPipelineEqual, "operator(|=)"},
    {AstNodeTypeEnum::symbolCharacterPipelinePipeline, "operator(||)"},
    {AstNodeTypeEnum::symbolCharacterPipelinePipelineEqual, "operator(||=)"},
    {AstNodeTypeEnum::symbolCharacterCaret, "operator(^)"},
    {AstNodeTypeEnum::symbolCharacterCaretEqual, "operator(^=)"},
    {AstNodeTypeEnum::symbolCharacterTilde, "operator(~)"},
    {AstNodeTypeEnum::symbolCharacterExclamation, "operator(!)"},
    {AstNodeTypeEnum::symbolCharacterExclamationEqual, "operator(!=)"},
    {AstNodeTypeEnum::symbolCharacterEqual, "operator(=)"},
    {AstNodeTypeEnum::symbolCharacterEqualEqual, "operator(==)"},
    {AstNodeTypeEnum::symbolCharacterLess, "operator(<)"},
    {AstNodeTypeEnum::symbolCharacterLessEqual, "operator(<=)"},
    {AstNodeTypeEnum::symbolCharacterLessLess, "operator(<<)"},
    {AstNodeTypeEnum::symbolCharacterLessLessEqual, "operator(<<=)"},
    {AstNodeTypeEnum::symbolCharacterLessLessPipeline, "operator(<<|)"},
    {AstNodeTypeEnum::symbolCharacterLessLessPipelineEqual, "operator(<<|=)"},
    {AstNodeTypeEnum::symbolCharacterGreater, "operator(>)"},
    {AstNodeTypeEnum::symbolCharacterGreaterEqual, "operator(>=)"},
    {AstNodeTypeEnum::symbolCharacterGreaterGreater, "operator(>>)"},
    {AstNodeTypeEnum::symbolCharacterGreaterGreaterEqual, "operator(>>=)"},
    //  : other symbols
    {AstNodeTypeEnum::symbolCharacterDoller, "operator($)"},
    {AstNodeTypeEnum::symbolCharacterNumbersign, "operator(#)"},
    {AstNodeTypeEnum::symbolCharacterQuestion, "operator(?)"},
    {AstNodeTypeEnum::symbolCharacterAtmark, "operator(@)"},
    {AstNodeTypeEnum::symbolCharacterColon, "operator(:)"},
    {AstNodeTypeEnum::symbolCharacterColonColon, "operator(::)"},
    {AstNodeTypeEnum::symbolCharacterSemicolon, "operator(;)"},
    {AstNodeTypeEnum::symbolCharacterComma, "operator(,)"},
    {AstNodeTypeEnum::symbolCharacterDot, "operator(.)"},
    {AstNodeTypeEnum::symbolCharacterDotDot, "operator(..)"},
    {AstNodeTypeEnum::symbolCharacterDotDotDot, "operator(...)"},
    {AstNodeTypeEnum::symbolCharacterBackslash, "operator(\\)"},
    //  : bracket symbols
    {AstNodeTypeEnum::symbolCharacterSinglequote, "Rune literal separator(')"},
    {AstNodeTypeEnum::symbolCharacterDoublequote,
     "String literal separotor(\")"},
    {AstNodeTypeEnum::symbolCharacterBackquote,
     "regular expression separator(`)"},
    {AstNodeTypeEnum::symbolCharacterLeftparentheses, "parenthese open'('"},
    {AstNodeTypeEnum::symbolCharacterRightparentheses, "parenthese close')'"},
    {AstNodeTypeEnum::symbolCharacterLeftcurlybrackets,
     "curly bracket open'{'"},
    {AstNodeTypeEnum::symbolCharacterRightcurlybrackets,
     "curly bracket close'}'"},
    {AstNodeTypeEnum::symbolCharacterLeftsquarebrackets,
     "square bracket open'['"},
    {AstNodeTypeEnum::symbolCharacterRightsquarebrackets,
     "square bracket close'['"},
    //  : comment out
    {AstNodeTypeEnum::symbolCharacterSlashSlash,
     "comment out(oneline) open\"//\""},
    {AstNodeTypeEnum::symbolCharacterSlashSlashLess,
     "comment out(block) open\"//<\""},
    {AstNodeTypeEnum::symbolCharacterSlashSlashGreater,
     "comment out(block) close\"//>\""},
    {AstNodeTypeEnum::symbolCharacterSlashNumbersign,
     "comment out(oneline for document) open\"/#\""},
    {AstNodeTypeEnum::symbolCharacterSlashNumbersignLess,
     "comment out(block for document) open\"/#<\""},
    {AstNodeTypeEnum::symbolCharacterSlashNumbersignGreater,
     "comment out(block for document) close\"/#>\""},
};
std::string AstNodeType::getString(const enum AstNodeTypeEnum &tokenType) {
  if (_map.count(tokenType)) {
    return _map.at(tokenType);
  } else {
    return _map.at(AstNodeTypeEnum::unknown);
  }
};

const std::map<std::string, AstNodeTypeEnum> AstNodeType::_builtinTypeMap{
    {"bool", AstNodeTypeEnum::builtinTypesBool},
    {"i4", AstNodeTypeEnum::builtinTypesI4},
    {"u4", AstNodeTypeEnum::builtinTypesU4},
    {"i8", AstNodeTypeEnum::builtinTypesI8},
    {"u8", AstNodeTypeEnum::builtinTypesU8},
    {"i16", AstNodeTypeEnum::builtinTypesI16},
    {"u16", AstNodeTypeEnum::builtinTypesU16},
    {"i32", AstNodeTypeEnum::builtinTypesI32},
    {"u32", AstNodeTypeEnum::builtinTypesU32},
    {"i64", AstNodeTypeEnum::builtinTypesI64},
    {"u64", AstNodeTypeEnum::builtinTypesU64},
    {"f32", AstNodeTypeEnum::builtinTypesF32},
    {"f64", AstNodeTypeEnum::builtinTypesF64},
    {"Rune", AstNodeTypeEnum::builtinTypesRune},
    {"String", AstNodeTypeEnum::builtinTypesString},
};

int AstNodeType::getBuiltinTypeEnum(const std::string &AstNode) {
  if (_builtinTypeMap.count(AstNode) == 0) {
    return -1;
  } else {
    return int(_builtinTypeMap.at(AstNode));
  }
};

const std::map<std::string, AstNodeTypeEnum> AstNodeType::_reservedWordsMap{
    {"fmain", AstNodeTypeEnum::reservedWordsFmain},
    {"exit", AstNodeTypeEnum::reservedWordsExit},
    {"static", AstNodeTypeEnum::reservedWordsStatic},
    {"public", AstNodeTypeEnum::reservedWordsPublic},
    {"protected", AstNodeTypeEnum::reservedWordsProtected},
    {"struct", AstNodeTypeEnum::reservedWordsStruct},
    {"enum", AstNodeTypeEnum::reservedWordsEnum},
    {"typeof", AstNodeTypeEnum::reservedWordsTypeof},
    {"typedef", AstNodeTypeEnum::reservedWordsTypedef},
    {"func", AstNodeTypeEnum::reservedWordsFunc},
    {"return", AstNodeTypeEnum::reservedWordsReturn},
    {"import", AstNodeTypeEnum::reservedWordsImport},
    {"if", AstNodeTypeEnum::reservedWordsIf},
    {"else", AstNodeTypeEnum::reservedWordsElse},
    {"switch", AstNodeTypeEnum::reservedWordsSwitch},
    {"case", AstNodeTypeEnum::reservedWordsCase},
    {"default", AstNodeTypeEnum::reservedWordsDefault},
    {"for", AstNodeTypeEnum::reservedWordsFor},
    {"while", AstNodeTypeEnum::reservedWordsWhile},
    {"break", AstNodeTypeEnum::reservedWordsBreak},
    {"continue", AstNodeTypeEnum::reservedWordsContinue},
    {"goto", AstNodeTypeEnum::reservedWordsGoto},
    {"true", AstNodeTypeEnum::reservedWordsTrue},
    {"false", AstNodeTypeEnum::reservedWordsFalse},
};

int AstNodeType::getReserveWordsEnum(const std::string &AstNode) {
  if (_reservedWordsMap.count(AstNode) == 0) {
    return -1;
  } else {
    return int(_reservedWordsMap.at(AstNode));
  }
};
