// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/ast_node_type.hpp"

using namespace gallop::Compiler;

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
    {AstNodeTypeEnum::coString, "CommentOut"},
    {AstNodeTypeEnum::coStringDoc, "CommentOut For Doc"},
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
    {AstNodeTypeEnum::coString, "comment out(oneline)"},
    {AstNodeTypeEnum::coStringDoc, "comment out(oneline for document)"},
    {AstNodeTypeEnum::coString, "comment out(block)"},
    {AstNodeTypeEnum::coStringDoc, "comment out(block for document)"},
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
    {AstNodeTypeEnum::reservedWordsFunc, "reserved words: fn"},
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
    {AstNodeTypeEnum::ltDecimalIntegralPart,
     "decimal number literal(integral part)"},
    {AstNodeTypeEnum::ltDecimalFractionalPart,
     "decimal number literal(fractional part)"},
    {AstNodeTypeEnum::ltDecimalExponentOperator,
     "decimal number literal(exponent operator[eE])"},
    {AstNodeTypeEnum::ltExponentPart, "decimal number literal(exponent part)"},
    {AstNodeTypeEnum::ltBinaryPrefix, "binary number prefix(0[bB])"},
    {AstNodeTypeEnum::ltOctalPrefix, "octal number prefix(0[oO])"},
    {AstNodeTypeEnum::ltHexadecimalPrefix, "hexadecimal number prefix(0[xX])"},
    {AstNodeTypeEnum::ltBinaryIntegralPart, "binary number literal"},
    {AstNodeTypeEnum::ltOctalIntegralPart, "octal number literal"},
    {AstNodeTypeEnum::ltHexadecimalIntegralPart, "hexadecimal number literal "},
    {AstNodeTypeEnum::ltSingleCharacter, " single character literal "},
    {AstNodeTypeEnum::ltString, "string literal"},
    {AstNodeTypeEnum::ltRawString, "raw string pattern literal"},
    {AstNodeTypeEnum::ltEscapeSequence, "escape sequence(\\.)"},
    {AstNodeTypeEnum::ltEscapeSequenceUtf8CodeOctal,
     "escape sequence utf8 octal number(\\o)"},
    {AstNodeTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal,
     "escape sequence utf8 hexadecimal number(\\x)"},
    {AstNodeTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal,
     "escape sequence utf16 hexadecimal number(\\u)"},
    // symbolCharacter
    //  : arithmetic ope
    {AstNodeTypeEnum::scPlus, "operator(+)"},
    {AstNodeTypeEnum::scPositiveDecimalExponent,
     "operator positive exponent(+)"},
    {AstNodeTypeEnum::scPlusWrapping, "operator(+%)"},
    {AstNodeTypeEnum::scPlusSaturating, "operator(+|)"},
    {AstNodeTypeEnum::scPlusAssign, "operator(+=)"},
    {AstNodeTypeEnum::scPlusWrappingAssign, "operator(+%=)"},
    {AstNodeTypeEnum::scPlusSaturatingAssign, "operator(+|=)"},
    {AstNodeTypeEnum::scIncrement, "operator(++)"},
    {AstNodeTypeEnum::scNegativeDecimalNumber, "operator negative number(-)"},
    {AstNodeTypeEnum::scNegativeDecimalExponent,
     "operator negative exponent(-)"},
    {AstNodeTypeEnum::scMinus, "operator(-)"},
    {AstNodeTypeEnum::scMinusWrapping, "operator(-%)"},
    {AstNodeTypeEnum::scMinusSaturating, "operator(-|)"},
    {AstNodeTypeEnum::scMinusAssign, "operator(-=)"},
    {AstNodeTypeEnum::scMinusWrappingAssign, "operator(-%=)"},
    {AstNodeTypeEnum::scMinusSaturatingAssign, "operator(-|=)"},
    {AstNodeTypeEnum::scDecrement, "operator(--)"},
    {AstNodeTypeEnum::scMultiple, "operator(*)"},
    {AstNodeTypeEnum::scMultipleWrapping, "operator(*%)"},
    {AstNodeTypeEnum::scMultipleSaturating, "operator(*|)"},
    {AstNodeTypeEnum::scMultipleAssign, "operator(*=)"},
    {AstNodeTypeEnum::scMultipleWrappingAssign, "operator(*%=)"},
    {AstNodeTypeEnum::scMultipleSaturatingAssign, "operator(*|=)"},
    {AstNodeTypeEnum::scDivide, "operator(/)"},
    {AstNodeTypeEnum::scDivideAssign, "operator(/=)"},
    {AstNodeTypeEnum::scModulo, "operator(%)"},
    {AstNodeTypeEnum::scModuloAssign, "operator(%=)"},
    //  : bit ope, logical ope
    {AstNodeTypeEnum::scBitAnd, "operator(&)"},
    {AstNodeTypeEnum::scBitAndAssign, "operator(&=)"},
    {AstNodeTypeEnum::scLogicalAnd, "operator(&&)"},
    {AstNodeTypeEnum::scLogicalAndAssign, "operator(&&=)"},
    {AstNodeTypeEnum::scBitOr, "operator(|)"},
    {AstNodeTypeEnum::scBitOrAssign, "operator(|=)"},
    {AstNodeTypeEnum::scLogicalOr, "operator(||)"},
    {AstNodeTypeEnum::scLogicalOrAssign, "operator(||=)"},
    {AstNodeTypeEnum::scBitExOr, "operator(^)"},
    {AstNodeTypeEnum::scBitExOrAssign, "operator(^=)"},
    {AstNodeTypeEnum::scBitNot, "operator(~)"},
    {AstNodeTypeEnum::scLogicalNotUnary, "operator(!)"},
    {AstNodeTypeEnum::scLogicalNotEqual, "operator(!=)"},
    {AstNodeTypeEnum::scAssignment, "operator(=)"},
    {AstNodeTypeEnum::scLogicalEqual, "operator(==)"},
    {AstNodeTypeEnum::scLessThan, "operator(<)"},
    {AstNodeTypeEnum::scLessThanEqual, "operator(<=)"},
    {AstNodeTypeEnum::scBitShiftLeft, "operator(<<)"},
    {AstNodeTypeEnum::scBitShiftLeftAssign, "operator(<<=)"},
    {AstNodeTypeEnum::scBitShiftLeftSaturating, "operator(<<|)"},
    {AstNodeTypeEnum::scBitShiftLeftSaturatingAssign, "operator(<<|=)"},
    {AstNodeTypeEnum::scGreaterThan, "operator(>)"},
    {AstNodeTypeEnum::scGreaterThanEqual, "operator(>=)"},
    {AstNodeTypeEnum::scArithmeticBitShiftRight, "operator(>>)"},
    {AstNodeTypeEnum::scArithmeticBitShiftRightAssign, "operator(>>=)"},
    //  : other symbols
    {AstNodeTypeEnum::scDollar, "operator($)"},
    {AstNodeTypeEnum::scNumberSign, "operator(#)"},
    {AstNodeTypeEnum::scQuestion, "operator(?)"},
    {AstNodeTypeEnum::scAtSign, "operator(@)"},
    {AstNodeTypeEnum::scColon, "operator(:)"},
    {AstNodeTypeEnum::scNameSpaceSeparater, "operator(::)"},
    {AstNodeTypeEnum::scSemiColon, "operator(;)"},
    {AstNodeTypeEnum::scComma, "operator(,)"},
    {AstNodeTypeEnum::scDot, "operator(.)"},
    {AstNodeTypeEnum::scDotDot, "operator(..)"},
    {AstNodeTypeEnum::scDotDotDot, "operator(...)"},
    {AstNodeTypeEnum::scBackSlash, "operator(\\)"},
    //  : bracket symbols
    {AstNodeTypeEnum::scSingleQuotation,
     "single character literal separator(')"},
    {AstNodeTypeEnum::scDoubleQuotation, "string literal separotor(\")"},
    {AstNodeTypeEnum::scBackQuotation, "raw string separator(`)"},
    {AstNodeTypeEnum::scParenthesesOpen, "parenthese open'('"},
    {AstNodeTypeEnum::scParenthesesClose, "parenthese close ')' "},
    {AstNodeTypeEnum::scCurlyBracketOpen, "curly bracket open'{'"},
    {AstNodeTypeEnum::scCurlyBracketClose, "curly bracket close'}'"},
    {AstNodeTypeEnum::scSquareBracketOpen, "square bracket open'['"},
    {AstNodeTypeEnum::scSquareBracketClose, "square bracket close'['"},
    //  : comment out
    {AstNodeTypeEnum::scOnelineCommentOut, "comment out(oneline) open\"//\""},
    {AstNodeTypeEnum::scBlockCommentOutOpen, "comment out(block) open\"//<\""},
    {AstNodeTypeEnum::scBlockCommentOutClose,
     "comment out(block) close\"//>\""},
    {AstNodeTypeEnum::scOnelineCommentOutDoc,
     "comment out(oneline for document) open\"/#\""},
    {AstNodeTypeEnum::scBlockCommentOutDocOpen,
     "comment out(block for document) open\"/#<\""},
    {AstNodeTypeEnum::scBlockCommentOutDocClose,
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
  return (ntlVal & ConstForTypeEnum::MaskSubType) ==
         (ntrVal & ConstForTypeEnum::MaskSubType);
};
bool AstNodeType::isRoot(const enum AstNodeTypeEnum &nodeType_) {
  return (uint32_t(nodeType_) >> ConstForTypeEnum::BitShift) ==
         static_cast<uint8_t>(AstNodeTypeCategoryEnum::root);
};
bool AstNodeType::isModule(const enum AstNodeTypeEnum &nodeType_) {
  return (uint32_t(nodeType_) >> ConstForTypeEnum::BitShift) ==
         static_cast<uint8_t>(AstNodeTypeCategoryEnum::inModule);
};
bool AstNodeType::isTopLevelChildOfModule(
    const enum AstNodeTypeEnum &nodeType_) {
  return isCommentOut(nodeType_) || isDeclareFunction(nodeType_);
};
bool AstNodeType::isLeafType(const enum AstNodeTypeEnum &nodeType_) {
  return isCommentOut(nodeType_) || isValueLiteral(nodeType_);
};
bool AstNodeType::isCommentOut(const enum AstNodeTypeEnum &nodeType_) {
  return (uint32_t(nodeType_) >> ConstForTypeEnum::BitShift) ==
         static_cast<uint8_t>(AstNodeTypeCategoryEnum::commentOut);
};
bool AstNodeType::isCommentOutOneline(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::coString ||
         nodeType_ == AstNodeTypeEnum::coStringDoc;
};
bool AstNodeType::isCommentOutBlock(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::coString ||
         nodeType_ == AstNodeTypeEnum::coStringDoc;
};
bool AstNodeType::isCommentOutForDoc(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::coStringDoc ||
         nodeType_ == AstNodeTypeEnum::coStringDoc;
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
  return (uint32_t(nodeType_) >> ConstForTypeEnum::BitShift) ==
         static_cast<uint8_t>(AstNodeTypeCategoryEnum::codeBlock);
};
bool AstNodeType::isValueLiteral(const enum AstNodeTypeEnum &nodeType_) {
  return nodeType_ == AstNodeTypeEnum::stringLiteral ||
         nodeType_ == AstNodeTypeEnum::charCodeLiteral;
};
