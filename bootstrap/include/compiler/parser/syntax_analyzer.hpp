// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_SYNTAX_ANALYZER_
#define _COMPILER_PARSER_SYNTAX_ANALYZER_
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/lexer/token.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/option.hpp"
#include <set>
#include <string>
#include <tuple>

namespace gallop {
namespace Compiler {
namespace Parser {

class SyntaxAnalyzer {
public:
  SyntaxAnalyzer(Lexer::LexicalAnalyzer *const lexicalAnalyzer,
                 AstNode *const moduleNode, Option parserOption);
  SyntaxAnalyzer(const SyntaxAnalyzer &rhs);
  SyntaxAnalyzer &operator=(const SyntaxAnalyzer &rhs);
  ~SyntaxAnalyzer() {};
  Lexer::LexicalAnalyzer *getLexicalAnalyzer();
  size_t getParsedTokenPos() const;

private:
  Lexer::LexicalAnalyzer *lexicalAnalyzer;
  size_t parsedTokenPos;
  AstNode *moduleNode;
  AstNode *currentNode;
  Option parserOption;
  std::set<std::string> includeFilenames;
  std::set<std::string> importModules;
  size_t blockDepthInModule;

  void parse();
  void pushNode(AstNode *childNode);

  size_t scanningCommentOut(const size_t pos);
  size_t scanningKeyword(const size_t pos);
  size_t scanningPackageDef(const size_t pos);
  size_t scanningModuleDef(const size_t pos);
  size_t scanningDeclareFmain(const size_t pos);
  size_t scanningControlBlock(const size_t pos);
  size_t scanningDecimalNumber(const size_t pos);
  uint16_t getBitLength(uint64_t decimalNumber);
  size_t scanningCharCodes(const size_t pos);
  std::tuple<std::string, uint32_t, std::string, bool>
  parseCharCodeOctalDigit(const std::string octalDigitStr);
  std::tuple<std::string, uint32_t, std::string, bool>
  parseCharCodeHexadecimal(const std::string hexadecimalDigitStr);
  std::tuple<std::string, uint32_t, std::string, bool>
  parseCharCodeUnicodePoint(const std::string unicodePointDigitStr);
  const uint16_t maxBits = 64;
  size_t scanningIdentifier(const size_t pos);
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif