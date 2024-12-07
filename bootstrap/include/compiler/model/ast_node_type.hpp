// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_AST_NODE_TYPE_
#define _COMPILER_MODEL_AST_NODE_TYPE_

#include "compiler/model/const_for_type_enum.hpp"

#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {

enum class AstNodeTypeCategoryEnum : uint8_t {
  root = 1,
  inModule,
  commentOut,
  declareFunction,
  codeBlock,
  declareStatement,
  valueLiteral,
};
enum class AstNodeTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  // root node
  rootFile = (static_cast<uint8_t>(AstNodeTypeCategoryEnum::root)
              << ConstForTypeEnum::BitShift) +
             1,
  rootStdin,
  rootInterpreter,
  // compile module node
  moduleFile = (static_cast<uint8_t>(AstNodeTypeCategoryEnum::inModule)
                << ConstForTypeEnum::BitShift) +
               1,
  moduleStdin,
  moduleInterpreter,
  // comment out
  coString = (static_cast<uint8_t>(AstNodeTypeCategoryEnum::commentOut)
              << ConstForTypeEnum::BitShift) +
             1,
  coStringDoc,
  // declare fn block
  declareFmain = (static_cast<uint8_t>(AstNodeTypeCategoryEnum::declareFunction)
                  << ConstForTypeEnum::BitShift) +
                 1,
  declareFn,
  declareFnClosure,
  // declare for block(etc: fmain, fn, if, while , global...)
  // block
  controlBlock = (static_cast<uint8_t>(AstNodeTypeCategoryEnum::codeBlock)
                  << ConstForTypeEnum::BitShift) +
                 1,
  // declare statement
  returnStatement =
      (static_cast<uint8_t>(AstNodeTypeCategoryEnum::declareStatement)
       << ConstForTypeEnum::BitShift) +
      1,
  // value literal
  stringLiteral = (static_cast<uint8_t>(AstNodeTypeCategoryEnum::valueLiteral)
                   << ConstForTypeEnum::BitShift) +
                  1,
  charCodeLiteral,
  decimalNumberLiteral,
  binaryNumberLiteral,
  octalNumberLiteral,
  hexadecimalNumberLiteral,
  // identifer types
  identifier = 0x22 << ConstForTypeEnum::BitShift,
  builtinTypesBool = 0x23 << ConstForTypeEnum::BitShift,
  builtinTypesI4,
  builtinTypesU4,
  builtinTypesI8,
  builtinTypesU8,
  builtinTypesI16,
  builtinTypesU16,
  builtinTypesI32,
  builtinTypesU32,
  builtinTypesI64,
  builtinTypesU64,
  builtinTypesF32,
  builtinTypesF64,
  builtinTypesCharCode,
  builtinTypesString,
  reservedWordsFmain = 0x24 << ConstForTypeEnum::BitShift,
  reservedWordsExit,
  reservedWordsStatic,
  reservedWordsPublic,
  reservedWordsProtected,
  reservedWordsStruct,
  reservedWordsEnum,
  reservedWordsTypeof,
  reservedWordsTypedef,
  reservedWordsFunc,
  reservedWordsReturn,
  reservedWordsImport,
  reservedWordsIf,
  reservedWordsElse,
  reservedWordsSwitch,
  reservedWordsCase,
  reservedWordsDefault,
  reservedWordsFor,
  reservedWordsWhile,
  reservedWordsBreak,
  reservedWordsContinue,
  reservedWordsGoto,
  reservedWordsTrue,
  reservedWordsFalse,
  // literal
  ltDecimalIntegralPart = 0x25 << ConstForTypeEnum::BitShift,
  ltDecimalFractionalPart,
  ltDecimalExponentOperator,
  ltExponentPart,
  ltBinaryPrefix,
  ltOctalPrefix,
  ltHexadecimalPrefix,
  ltBinaryIntegralPart,
  ltOctalIntegralPart,
  ltHexadecimalIntegralPart,
  ltSingleCharacter,
  ltString,
  ltEscapeSequence,
  ltRawString,
  ltEscapeSequenceUtf8CodeOctal,
  ltEscapeSequenceUtf8CodeHexadecimal,
  ltEscapeSequenceUtf16CodeHexadecimal,
  // symbolCharacter
  //  : arithmetic ope
  scPlus = 0x26 << ConstForTypeEnum::BitShift,
  scPositiveDecimalExponent,
  scPlusWrapping,
  scPlusSaturating,
  scPlusAssign,
  scPlusWrappingAssign,
  scPlusSaturatingAssign,
  scIncrement,
  scNegativeDecimalNumber,
  scNegativeDecimalExponent,
  scMinus,
  scMinusWrapping,
  scMinusSaturating,
  scMinusAssign,
  scMinusWrappingAssign,
  scMinusSaturatingAssign,
  scDecrement,
  scMultiple,
  scMultipleWrapping,
  scMultipleSaturating,
  scMultipleAssign,
  scMultipleWrappingAssign,
  scMultipleSaturatingAssign,
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
  scBitNot,
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
  //  : other symbols
  scDollar,
  scNumberSign,
  scQuestion,
  scAtSign,
  scColon,
  scNameSpaceSeparater,
  scSemiColon,
  scComma,
  scDot,
  scDotDot,
  scDotDotDot,
  scBackSlash,
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
  scBlockCommentOutDocOpen,
  scBlockCommentOutDocClose,
};

class AstNodeType final {
public:
  AstNodeType() = delete;
  ~AstNodeType() = delete;
  static std::string getString(const enum AstNodeTypeEnum &AstNodeType);
  static bool matchSubtype(const enum AstNodeTypeEnum &nodeTypeL,
                           const enum AstNodeTypeEnum &nodeTypeR);
  static bool isRoot(const enum AstNodeTypeEnum &nodeType);
  static bool isModule(const enum AstNodeTypeEnum &nodeType);
  static bool isTopLevelChildOfModule(const enum AstNodeTypeEnum &nodeType);
  static bool isLeafType(const enum AstNodeTypeEnum &nodeType);
  static bool isCommentOut(const enum AstNodeTypeEnum &nodeType);
  static bool isCommentOutOneline(const enum AstNodeTypeEnum &nodeType);
  static bool isCommentOutBlock(const enum AstNodeTypeEnum &nodeType);
  static bool isCommentOutForDoc(const enum AstNodeTypeEnum &nodeType);
  static bool isDeclareFunction(const enum AstNodeTypeEnum &nodeType);
  static bool isDeclareFunctionGlobal(const enum AstNodeTypeEnum &nodeType);
  static bool isCodeBlock(const enum AstNodeTypeEnum &nodeType);
  static bool isValueLiteral(const enum AstNodeTypeEnum &nodeType_);

private:
  static const std::map<AstNodeTypeEnum, std::string> _map;
};

} // namespace Compiler
} // namespace gallop
#endif