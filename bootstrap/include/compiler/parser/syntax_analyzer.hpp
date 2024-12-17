#ifndef _COMPILER_PARSER_SYNTAX_ANALYZER_
#define _COMPILER_PARSER_SYNTAX_ANALYZER_
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/lexer/token.hpp"
#include "compiler/parser/ast.hpp"

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
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif