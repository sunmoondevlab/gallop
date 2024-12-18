#include "compiler/parser/syntax_analyzer.hpp"
#include "compiler/lexer/token.hpp"

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *const lexicalAnalyzer_,
                               AstNode *const astNode_, Option parserOption_)
    : lexicalAnalyzer((LexicalAnalyzer *)lexicalAnalyzer_), parsedTokenPos(0),
      astNode(astNode_), parserOption(parserOption_) {
  parse();
};
SyntaxAnalyzer::SyntaxAnalyzer(const SyntaxAnalyzer &rhs)
    : lexicalAnalyzer(rhs.lexicalAnalyzer), parsedTokenPos(rhs.parsedTokenPos),
      astNode(rhs.astNode), parserOption(rhs.parserOption) {};
SyntaxAnalyzer &SyntaxAnalyzer::operator=(const SyntaxAnalyzer &rhs) {
  lexicalAnalyzer = rhs.lexicalAnalyzer;
  parsedTokenPos = rhs.parsedTokenPos;
  astNode = rhs.astNode;
  parserOption = rhs.parserOption;
  return *this;
};
LexicalAnalyzer *SyntaxAnalyzer::getLexicalAnalyzer() {
  return lexicalAnalyzer;
};
size_t SyntaxAnalyzer::getParsedTokenPos() const { return parsedTokenPos; };

void SyntaxAnalyzer::parse() {
  size_t tokenCnt = lexicalAnalyzer->getTokens()->getTokenCnt();
  for (size_t pos = parsedTokenPos; pos < tokenCnt;) {

    pos++;
  }
};

void SyntaxAnalyzer::scaningIdentifier() {};
void SyntaxAnalyzer::scaningPackageDef() {};
