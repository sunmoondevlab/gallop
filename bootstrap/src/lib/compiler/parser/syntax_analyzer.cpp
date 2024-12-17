#include "compiler/parser/syntax_analyzer.hpp"
#include "compiler/lexer/token.hpp"

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *const lexicalAnalyzer_,
                               AstNode *const astNode_)
    : lexicalAnalyzer((LexicalAnalyzer *)lexicalAnalyzer_), parsedTokenPos(0),
      astNode(astNode_) {};
SyntaxAnalyzer::SyntaxAnalyzer(const SyntaxAnalyzer &rhs)
    : lexicalAnalyzer(rhs.lexicalAnalyzer), parsedTokenPos(rhs.parsedTokenPos),
      astNode(rhs.astNode) {};
SyntaxAnalyzer &SyntaxAnalyzer::operator=(const SyntaxAnalyzer &rhs) {
  lexicalAnalyzer = rhs.lexicalAnalyzer;
  parsedTokenPos = rhs.parsedTokenPos;
  astNode = rhs.astNode;
  return *this;
};
LexicalAnalyzer *SyntaxAnalyzer::getLexicalAnalyzer() {
  return lexicalAnalyzer;
};
size_t SyntaxAnalyzer::getParsedTokenPos() { return parsedTokenPos; };
