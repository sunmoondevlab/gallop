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
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCnt = tokens->getTokenCnt();
  for (size_t pos = parsedTokenPos; pos < tokenCnt;) {
    TokenTypeEnum tokenType = tokens->get(pos).getTokenType();
    if (tokenType == TokenTypeEnum::commentOutOneline ||
        tokenType == TokenTypeEnum::commentOutOnelineDoc ||
        tokenType == TokenTypeEnum::commentOutBlock ||
        tokenType == TokenTypeEnum::commentOutBlockDoc) {
      pos += scaningCommentOut(pos);
      continue;
    }
    pos++;
  }
};

size_t SyntaxAnalyzer::scaningCommentOut(const size_t pos_) {
  size_t skipTokenCnt = 0;
  std::string commentOutBody = "";

  return skipTokenCnt;
};
void SyntaxAnalyzer::scaningIdentifier() {};
void SyntaxAnalyzer::scaningPackageDef() {};
