// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_NODE_TYPE_
#define _COMPILER_PARSER_AST_NODE_TYPE_
#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {
namespace Parser {

namespace AstNodeTypeCategoryEnum {
static const uint8_t root = 1;
static const uint8_t inModule = 2;
static const uint8_t commentOut = 3;
static const uint8_t declareFunction = 4;
static const uint8_t codeBlock = 10;
static const uint8_t declareStatement = 11;
static const uint8_t valueLiteral = 12;

} // namespace AstNodeTypeCategoryEnum
enum class AstNodeTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  // root node
  rootFile = (AstNodeTypeCategoryEnum::root << 24) + 1,
  rootStdin,
  rootInterpreter,
  // compile module node
  moduleFile = (AstNodeTypeCategoryEnum::inModule << 24) + 1,
  moduleStdin,
  moduleInterpreter,
  // comment out
  commentOutOneline = (AstNodeTypeCategoryEnum::commentOut << 24) + 1,
  commentOutOnelineDoc,
  commentOutBlock,
  commentOutBlockDoc,
  // declare func block
  declareFmain = (AstNodeTypeCategoryEnum::declareFunction << 24) + 1,
  declareFn,
  declareFnClosure,
  // declare for block(etc: fmain, fn, if, while , global...)
  // block
  controlBlock = (AstNodeTypeCategoryEnum::codeBlock << 24) + 1,
  // declare statement
  returnStatement = (AstNodeTypeCategoryEnum::declareStatement << 24) + 1,
  // value literal
  stringLiteral = (AstNodeTypeCategoryEnum::valueLiteral << 24) + 1,
  charCodeLiteral,
  decimalNumberLiteral,
  binaryNumberLiteral,
  octalNumberLiteral,
  hexadecimalNumberLiteral,
  // identifer types
  identifier = 0x22 << 24,
  builtinTypesBool = 0x23 << 24,
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
  reservedWordsFmain = 0x24 << 24,
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
  literalDecimalNumberIntegralPart = 0x25 << 24,
  literalDecimalNumberDecimalPart,
  literalDecimalNumberExponentOperator,
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
  symbolCharacterPlus = 0x26 << 24,
  symbolCharacterPositiveDecimalExponent,
  symbolCharacterPlusPercent,
  symbolCharacterPlusPipeline,
  symbolCharacterPlusEqual,
  symbolCharacterPlusPercentEqual,
  symbolCharacterPlusPipelineEqual,
  symbolCharacterPlusPlus,
  symbolCharacterNegativeDecimalNumber,
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

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif