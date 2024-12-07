// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
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
    // declare for block
    {AstNodeTypeEnum::declareFmain, "fmain"},
    {AstNodeTypeEnum::declareFn, "fn"},
    {AstNodeTypeEnum::declareFnClosure, "fn(Closure)"},
    // block
    {AstNodeTypeEnum::controlBlock, "Control block"},
    // value literal
    {AstNodeTypeEnum::stringLiteral, "string"},
    {AstNodeTypeEnum::charCodeLiteral, "charCode"},
    {AstNodeTypeEnum::decimalNumberLiteral, "decimal number"},
    {AstNodeTypeEnum::binaryNumberLiteral, "binary number"},
    {AstNodeTypeEnum::octalNumberLiteral, "octal number"},
    {AstNodeTypeEnum::hexadecimalNumberLiteral, "hexadecimal number"},
    // control statement
    {AstNodeTypeEnum::returnStatement, "return"},

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
    {AstNodeTypeEnum::builtinTypesCharCode, "builtin type(CharCode)"},
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
    {AstNodeTypeEnum::literalCharCode, "char code literal"},
    {AstNodeTypeEnum::literalString, "string literal"},
    {AstNodeTypeEnum::literalRawString, "raw string pattern literal"},
    {AstNodeTypeEnum::literalEscapeSequence, "escape sequence(\\.)"},
    {AstNodeTypeEnum::literalCharCodeOctalEscapeSequence,
     "octal number escape sequence(\\o)"},
    {AstNodeTypeEnum::literalCharCodeHexadecimalEscapeSequence,
     "hexadecimal number escape sequence(\\x)"},
    {AstNodeTypeEnum::literalCharCodeUnicodePointEscapeSequence,
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
    {AstNodeTypeEnum::symbolCharacterSinglequote,
     "char code literal separator(')"},
    {AstNodeTypeEnum::symbolCharacterDoublequote,
     "string literal separotor(\")"},
    {AstNodeTypeEnum::symbolCharacterBackquote, "raw string separator(`)"},
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
bool AstNodeType::matchSubtype(const enum AstNodeTypeEnum &nodeTypeL_,
                               const enum AstNodeTypeEnum &nodeTypeR_) {
  uint32_t ntlVal = uint32_t(nodeTypeL_);
  uint32_t ntrVal = uint32_t(nodeTypeR_);
  return (ntlVal & 0x00ffffff) == (ntrVal & 0x00ffffff);
};
bool AstNodeType::isRoot(const enum AstNodeTypeEnum &nodeType_) {
  return (uint32_t(nodeType_) >> 24) == AstNodeTypeCategoryEnum::root;
};
bool AstNodeType::isModule(const enum AstNodeTypeEnum &nodeType_) {
  return (uint32_t(nodeType_) >> 24) == AstNodeTypeCategoryEnum::inModule;
};
bool AstNodeType::isTopLevelChildOfModule(
    const enum AstNodeTypeEnum &nodeType_) {
  return isCommentOut(nodeType_) || isDeclareFunction(nodeType_);
};
bool AstNodeType::isLeafType(const enum AstNodeTypeEnum &nodeType_) {
  return isCommentOut(nodeType_) || isValueLiteral(nodeType_);
};
bool AstNodeType::isCommentOut(const enum AstNodeTypeEnum &nodeType_) {
  return (uint32_t(nodeType_) >> 24) == AstNodeTypeCategoryEnum::commentOut;
};
bool AstNodeType::isCommentOutOneline(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::commentOutOneline ||
         nodeType_ == AstNodeTypeEnum::commentOutOnelineDoc;
};
bool AstNodeType::isCommentOutBlock(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::commentOutBlock ||
         nodeType_ == AstNodeTypeEnum::commentOutBlockDoc;
};
bool AstNodeType::isCommentOutForDoc(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::commentOutOnelineDoc ||
         nodeType_ == AstNodeTypeEnum::commentOutBlockDoc;
};
bool AstNodeType::isDeclareFunction(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::declareFmain ||
         nodeType_ == AstNodeTypeEnum::declareFn ||
         nodeType_ == AstNodeTypeEnum::declareFnClosure;
};
bool AstNodeType::isDeclareFunctionGlobal(
    const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::declareFmain ||
         nodeType_ == AstNodeTypeEnum::declareFn;
};
bool AstNodeType::isCodeBlock(const enum AstNodeTypeEnum &nodeType_) {
  return (uint32_t(nodeType_) >> 24) == AstNodeTypeCategoryEnum::codeBlock;
};
bool AstNodeType::isValueLiteral(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::stringLiteral ||
         nodeType_ == AstNodeTypeEnum::charCodeLiteral;
};
