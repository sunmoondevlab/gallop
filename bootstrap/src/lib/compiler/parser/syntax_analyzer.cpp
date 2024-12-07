#include "compiler/parser/syntax_analyzer.hpp"
#include "compiler/lexer/token.hpp"
#include "compiler/parser/ast_node/comment_out.hpp"
#include "compiler/parser/ast_node/module.hpp"

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *const lexicalAnalyzer_,
                               AstNode *const moduleNode_, Option parserOption_)
    : lexicalAnalyzer((LexicalAnalyzer *)lexicalAnalyzer_), parsedTokenPos(0),
      moduleNode(moduleNode_), currentNode(moduleNode_),
      parserOption(parserOption_) {
  parse();
};
SyntaxAnalyzer::SyntaxAnalyzer(const SyntaxAnalyzer &rhs)
    : lexicalAnalyzer(rhs.lexicalAnalyzer), parsedTokenPos(rhs.parsedTokenPos),
      moduleNode(rhs.moduleNode), currentNode(rhs.currentNode),
      parserOption(rhs.parserOption) {};
SyntaxAnalyzer &SyntaxAnalyzer::operator=(const SyntaxAnalyzer &rhs) {
  lexicalAnalyzer = rhs.lexicalAnalyzer;
  parsedTokenPos = rhs.parsedTokenPos;
  moduleNode = rhs.moduleNode;
  currentNode = rhs.currentNode;
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
    if (tokenType == TokenTypeEnum::symbolCharacterSlashSlash ||
        tokenType == TokenTypeEnum::symbolCharacterSlashNumbersign ||
        tokenType == TokenTypeEnum::symbolCharacterSlashSlashLess ||
        tokenType == TokenTypeEnum::symbolCharacterSlashNumbersignLess) {
      pos += scanningCommentOut(pos);
      continue;
    } else if (tokenType == TokenTypeEnum::identifier) {
      pos += scanningIdentifier(pos);
      continue;
    }
    pos++;
  }
};

bool SyntaxAnalyzer::isNodeAtBlockFirst() const {
  AstNodeTypeEnum nodeType = currentNode->getAstNodeType();
  return nodeType == AstNodeTypeEnum::moduleFile ||
         nodeType == AstNodeTypeEnum::moduleInterpreter ||
         nodeType == AstNodeTypeEnum::moduleStdin;
};

size_t SyntaxAnalyzer::scanningCommentOut(const size_t pos_) {
  size_t skipTokenCnt = 0;
  std::string body = "";
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCnt = tokens->getTokenCnt();
  Token tokenCoBegin = tokens->get(pos_);
  TokenTypeEnum tokenType = tokenCoBegin.getTokenType();
  skipTokenCnt++;
  if (tokenType == TokenTypeEnum::symbolCharacterSlashSlash ||
      tokenType == TokenTypeEnum::symbolCharacterSlashNumbersign) {
    // oneline
    Token tokenCo = tokens->get(pos_ + skipTokenCnt);
    TokenTypeEnum tokenTypeCo = tokenCo.getTokenType();
    if (tokenTypeCo == TokenTypeEnum::commentOutOneline ||
        tokenTypeCo == TokenTypeEnum::commentOutOnelineDoc) {
      body = tokenCo.getToken();
      skipTokenCnt++;
    }
    if ((tokenType == TokenTypeEnum::symbolCharacterSlashSlash &&
         parserOption.isWithCommentOutAll()) ||
        (tokenType == TokenTypeEnum::symbolCharacterSlashNumbersign &&
         (parserOption.isWithCommentOutAll() ||
          parserOption.isWithCommentOutForDoc()))) {
      AstNodeCommentOut *coNode = new AstNodeCommentOut(
          tokenType == TokenTypeEnum::symbolCharacterSlashSlash
              ? AstNodeTypeEnum::commentOutOneline
              : AstNodeTypeEnum::commentOutOnelineDoc,
          tokenCoBegin.getLocation());
      coNode->setBody(body);
      if (isNodeAtBlockFirst()) {
        currentNode->putChildNode(coNode);
        coNode->putParentNode(currentNode);
      } else {
        currentNode->putNextNode(coNode);
        coNode->putPrevNode(currentNode);
        coNode->putParentNode(currentNode->parentNode());
      }
      currentNode = coNode;
    }
  } else {
    // block
    Token tokenCo;
    TokenTypeEnum tokenTypeCo;
    size_t pos = pos_ + skipTokenCnt;
    for (tokenCo = tokens->get(pos), tokenTypeCo = tokenCo.getTokenType();
         tokenTypeCo == TokenTypeEnum::commentOutBlock ||
         tokenTypeCo == TokenTypeEnum::commentOutBlockDoc;
         pos++, skipTokenCnt++, tokenCo = tokens->get(pos),
        tokenTypeCo = tokenCo.getTokenType()) {
      body += tokenCo.getToken();
    }
    Token tokenCoEnd = tokens->get(pos);
    skipTokenCnt++;
    if ((tokenType == TokenTypeEnum::symbolCharacterSlashSlashLess &&
         parserOption.isWithCommentOutAll()) ||
        (tokenType == TokenTypeEnum::symbolCharacterSlashNumbersignLess &&
         (parserOption.isWithCommentOutAll() ||
          parserOption.isWithCommentOutForDoc()))) {
      AstNodeCommentOut *coNode = new AstNodeCommentOut(
          tokenType == TokenTypeEnum::symbolCharacterSlashSlashLess
              ? AstNodeTypeEnum::commentOutBlock
              : AstNodeTypeEnum::commentOutBlockDoc,
          tokenCoBegin.getLocation());
      coNode->setBody(body);
      Location endLoc = tokenCoEnd.getLocation();
      endLoc.addColumn(3);
      coNode->setBegenEndLocation(tokenCoBegin.getLocation(), endLoc);
      if (isNodeAtBlockFirst()) {
        currentNode->putChildNode(coNode);
        coNode->putParentNode(currentNode);
      } else {
        currentNode->putNextNode(coNode);
        coNode->putPrevNode(currentNode);
        coNode->putParentNode(currentNode->parentNode());
      }
      currentNode = coNode;
    }
  }
  return skipTokenCnt;
};

size_t SyntaxAnalyzer::scanningIdentifier(const size_t pos_) {
  size_t skipTokenCnt = 0;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCnt = tokens->getTokenCnt();
  Token tokenId = tokens->get(pos_);
  std::string identifier = tokenId.getToken();
  if (identifier == "pkgdef") {
    skipTokenCnt = scanningPackageDef(pos_);
  } else if (identifier == "moddef") {
    skipTokenCnt = scanningModuleDef(pos_);
  } else {
    skipTokenCnt++;
  }
  return skipTokenCnt;
};

size_t SyntaxAnalyzer::scanningPackageDef(const size_t pos_) {
  size_t skipTokenCnt = 0;
  skipTokenCnt++;
  size_t pos = pos_ + skipTokenCnt;
  std::string packageName = "";
  Token tokenPkgNm;
  TokenTypeEnum tokenTypePkg;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  tokenPkgNm = tokens->get(pos);
  tokenTypePkg = tokenPkgNm.getTokenType();
  if (tokenTypePkg == TokenTypeEnum::identifier) {
    for (pos = pos_ + skipTokenCnt, tokenPkgNm = tokens->get(pos),
        tokenTypePkg = tokenPkgNm.getTokenType();
         tokenTypePkg == TokenTypeEnum::identifier ||
         tokenTypePkg == TokenTypeEnum::symbolCharacterDot;
         pos++, skipTokenCnt++, tokenPkgNm = tokens->get(pos),
        tokenTypePkg = tokenPkgNm.getTokenType()) {
      packageName += tokenPkgNm.getToken();
    }
    tokenPkgNm = tokens->get(pos);
    tokenTypePkg = tokenPkgNm.getTokenType();
    if (tokenTypePkg != TokenTypeEnum::symbolCharacterSemicolon) {
      Location loc = tokenPkgNm.getLocation();
      throw "invalid package name. loc: " + loc.getString();
    }
    skipTokenCnt++;

    AstNodeModule *modNode = (AstNodeModule *)(currentNode->moduleNode());
    if (!modNode->isDefinedPkgName()) {
      modNode->replacePackageName(packageName);
    }
  } else {
    Location loc = tokenPkgNm.getLocation();
    throw "invalid package name. loc: " + loc.getString();
  }
  return skipTokenCnt;
};

size_t SyntaxAnalyzer::scanningModuleDef(const size_t pos_) {
  size_t skipTokenCnt = 0;
  skipTokenCnt++;
  size_t pos = pos_ + skipTokenCnt;
  std::string moduleName = "";
  Token tokenModNm;
  TokenTypeEnum tokenTypeMod;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  tokenModNm = tokens->get(pos);
  tokenTypeMod = tokenModNm.getTokenType();
  if (tokenTypeMod == TokenTypeEnum::identifier) {
    moduleName += tokenModNm.getToken();
    skipTokenCnt++;
    pos = pos_ + skipTokenCnt;
    tokenModNm = tokens->get(pos);
    tokenTypeMod = tokenModNm.getTokenType();
    if (tokenTypeMod != TokenTypeEnum::symbolCharacterSemicolon) {
      Location loc = tokenModNm.getLocation();
      throw "invalid module name. loc: " + loc.getString();
    }
    skipTokenCnt++;

    AstNodeModule *modNode = (AstNodeModule *)(currentNode->moduleNode());
    if (!modNode->isDefinedModName()) {
      modNode->replaceModuleName(moduleName);
    }
  } else {
    Location loc = tokenModNm.getLocation();
    throw "invalid module name. loc: " + loc.getString();
  }
  return skipTokenCnt;
};
