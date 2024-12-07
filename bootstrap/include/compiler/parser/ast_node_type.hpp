#ifndef _COMPILER_PARSER_AST_NODE_TYPE_
#define _COMPILER_PARSER_AST_NODE_TYPE_
#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {
namespace Parser {

enum class AstNodeTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  // root node
  rootFile = (1 << 24) + 1,
  rootStdin,
  rootInterpreter,
  // compile module node
  moduleFile = (2 << 24) + 1,
  moduleStdin,
  moduleInterpreter,
  // comment out
  commentOutOneline = (3 << 24) + 1,
  commentOutOnelineDoc,
  commentOutBlock,
  commentOutBlockDoc,
  // fmain
  blockFmain = (4 << 24) + 1,
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
  builtinTypesRune,
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
  literalRune,
  literalString,
  literalEscapeSequence,
  literalRegularExpressionPattern,
  literalRuneOctalEscapeSequence,
  literalRuneHexadecimalEscapeSequence,
  literalRuneUnicodePointEscapeSequence,
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
  static int getBuiltinTypeEnum(const std::string &AstNode);
  static int getReserveWordsEnum(const std::string &AstNode);

private:
  static const std::map<AstNodeTypeEnum, std::string> _map;
  static const std::map<std::string, AstNodeTypeEnum> _builtinTypeMap;
  static const std::map<std::string, AstNodeTypeEnum> _reservedWordsMap;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif