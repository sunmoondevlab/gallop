#ifndef _COMPILER_PARSER_SYNTAX_ANALYZER_
#define _COMPILER_PARSER_SYNTAX_ANALYZER_
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/lexer/token.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/option.hpp"
#include <set>
#include <string>

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
  uint64_t saContFlags;
  uint32_t saDecFlags;

  enum SaContFlags : uint64_t {
    SaContFlagsInLiteralRune = 0x1l,
    SaContFlagsInLiteralString = 0x1l << 1,
    SaContFlagsInLiteralRegularExpressionPattern = 0x1l << 2,
    SaContFlagsInCommentOutOneline = 0x1l << 3,
    SaContFlagsInCommentOutBlock = 0x1l << 4,
    SaContFlagsInCommentOutBlockDoc = 0x1l << 5,
  };

  void parse();
  bool isNodeAtBlockFirst() const;

  size_t scanningCommentOut(const size_t pos);

  size_t scanningIdentifier(const size_t pos);
  size_t scanningPackageDef(const size_t pos);
  size_t scanningModuleDef(const size_t pos);
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif