#ifndef _COMPILER_PARSER_SYNTAX_ANALYZER_
#define _COMPILER_PARSER_SYNTAX_ANALYZER_
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/lexer/token.hpp"
#include "compiler/parser/ast.hpp"
#include <set>
#include <string>

namespace gallop {
namespace Compiler {
namespace Parser {

class SyntaxAnalyzer {
public:
  SyntaxAnalyzer(Lexer::LexicalAnalyzer *const lexicalAnalyzer_,
                 AstNode *const astNode_);
  SyntaxAnalyzer(const SyntaxAnalyzer &rhs);
  SyntaxAnalyzer &operator=(const SyntaxAnalyzer &rhs);
  ~SyntaxAnalyzer() {};
  Lexer::LexicalAnalyzer *getLexicalAnalyzer();
  size_t getParsedTokenPos();

private:
  Lexer::LexicalAnalyzer *lexicalAnalyzer;
  size_t parsedTokenPos;
  AstNode *astNode;
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

  void scaningIdentifier();
  void scaningPackageDef();
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif