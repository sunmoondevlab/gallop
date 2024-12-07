// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/syntax_analyzer.hpp"
#include "compiler/lexer/token.hpp"
#include "compiler/parser/ast_node/char_code_literal.hpp"
#include "compiler/parser/ast_node/comment_out.hpp"
#include "compiler/parser/ast_node/control_block.hpp"
#include "compiler/parser/ast_node/declare_fmain.hpp"
#include "compiler/parser/ast_node/module.hpp"
#include "compiler/parser/ast_node/root.hpp"
#include "compiler/parser/ast_node/string_literal.hpp"

#include <cmath>
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *const lexicalAnalyzer_,
                               AstNode *const moduleNode_, Option parserOption_)
    : lexicalAnalyzer((LexicalAnalyzer *)lexicalAnalyzer_), parsedTokenPos(0),
      moduleNode(moduleNode_), currentNode(moduleNode_),
      parserOption(parserOption_), blockDepthInModule(0) {
  if (moduleNode_->getAstNodeType() != AstNodeTypeEnum::moduleInterpreter) {
    parse();
  }
};
SyntaxAnalyzer::SyntaxAnalyzer(const SyntaxAnalyzer &rhs)
    : lexicalAnalyzer(rhs.lexicalAnalyzer), parsedTokenPos(rhs.parsedTokenPos),
      moduleNode(rhs.moduleNode), currentNode(rhs.currentNode),
      parserOption(rhs.parserOption),
      blockDepthInModule(rhs.blockDepthInModule) {};
SyntaxAnalyzer &SyntaxAnalyzer::operator=(const SyntaxAnalyzer &rhs) {
  lexicalAnalyzer = rhs.lexicalAnalyzer;
  parsedTokenPos = rhs.parsedTokenPos;
  moduleNode = rhs.moduleNode;
  currentNode = rhs.currentNode;
  parserOption = rhs.parserOption;
  blockDepthInModule = rhs.blockDepthInModule;
  return *this;
};
LexicalAnalyzer *SyntaxAnalyzer::getLexicalAnalyzer() {
  return lexicalAnalyzer;
};
size_t SyntaxAnalyzer::getParsedTokenPos() const { return parsedTokenPos; };

void SyntaxAnalyzer::parse() {
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCount = tokens->getParsableTokenCount();
  for (size_t pos = parsedTokenPos; pos < tokenCount;) {
    TokenTypeEnum tokenType = tokens->get(pos).getTokenType();
    if (TokenType::isCommentOut(tokenType)) {
      pos += scanningCommentOut(pos);
      parsedTokenPos = pos;
      continue;
    } else if (tokenType == TokenTypeEnum::keyword) {
      pos += scanningKeyword(pos);
      parsedTokenPos = pos;
      continue;
    } else if (tokenType == TokenTypeEnum::symbolCharacterLeftcurlybrackets) {
      if (currentNode->getAstNodeType() == AstNodeTypeEnum::declareFmain) {
        pos += scanningControlBlock(pos);
        parsedTokenPos = pos;
        continue;
      }
    }
    pos++;
    parsedTokenPos = pos;
  }
};

size_t SyntaxAnalyzer::scanningCommentOut(const size_t pos_) {
  size_t skipTokenCount = 0;
  std::string body = "";
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCount = tokens->getParsableTokenCount();
  Token tokenCoBegin = tokens->get(pos_);
  TokenTypeEnum tokenType = tokenCoBegin.getTokenType();
  skipTokenCount++;
  if (tokenType == TokenTypeEnum::symbolCharacterSlashSlash ||
      tokenType == TokenTypeEnum::symbolCharacterSlashNumbersign) {
    // oneline
    Token tokenCo = tokens->get(pos_ + skipTokenCount);
    TokenTypeEnum tokenTypeCo = tokenCo.getTokenType();
    if (tokenTypeCo == TokenTypeEnum::commentOutOneline ||
        tokenTypeCo == TokenTypeEnum::commentOutOnelineDoc) {
      body = tokenCo.getToken();
      skipTokenCount++;
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
          tokenCoBegin.getLocation(), body);
      pushNode(coNode);
    }
  } else {
    // block
    Token tokenCo;
    TokenTypeEnum tokenTypeCo;
    size_t pos = pos_ + skipTokenCount;
    for (tokenCo = tokens->get(pos), tokenTypeCo = tokenCo.getTokenType();
         pos < tokenCount && (tokenTypeCo == TokenTypeEnum::commentOutBlock ||
                              tokenTypeCo == TokenTypeEnum::commentOutBlockDoc);
         pos++, skipTokenCount++, tokenCo = tokens->get(pos),
        tokenTypeCo = tokenCo.getTokenType()) {
      body += tokenCo.getToken();
    }
    Token tokenCoEnd = tokens->get(pos);
    skipTokenCount++;
    if ((tokenType == TokenTypeEnum::symbolCharacterSlashSlashLess &&
         parserOption.isWithCommentOutAll()) ||
        (tokenType == TokenTypeEnum::symbolCharacterSlashNumbersignLess &&
         (parserOption.isWithCommentOutAll() ||
          parserOption.isWithCommentOutForDoc()))) {
      Location endLoc = tokenCoEnd.getLocation();
      endLoc.addColumn(2);
      AstNodeCommentOut *coNode = new AstNodeCommentOut(
          tokenType == TokenTypeEnum::symbolCharacterSlashSlashLess
              ? AstNodeTypeEnum::commentOutBlock
              : AstNodeTypeEnum::commentOutBlockDoc,
          tokenCoBegin.getLocation(), endLoc, body);
      pushNode(coNode);
    }
  }
  return skipTokenCount;
};

void SyntaxAnalyzer::pushNode(AstNode *childNode_) {
  if (!currentNode->hasChild() &&
      !AstNodeType::isLeafType(currentNode->getAstNodeType())) {
    currentNode->setChild(childNode_);
    childNode_->setParent(currentNode);
  } else {
    currentNode->setNext(childNode_);
    childNode_->setPrev(currentNode);
    childNode_->setParent(currentNode->getParent());
  }
  currentNode = childNode_;
};

size_t SyntaxAnalyzer::scanningKeyword(const size_t pos_) {
  size_t skipTokenCount = 0;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  Token tokenId = tokens->get(pos_);
  std::string keyword = tokenId.getToken();
  if (keyword == "pkgdef") {
    skipTokenCount = scanningPackageDef(pos_);
  } else if (keyword == "moddef") {
    skipTokenCount = scanningModuleDef(pos_);
  } else if (keyword == "fmain") {
    skipTokenCount = scanningDeclareFmain(pos_);
  } else {
    skipTokenCount++;
  }
  return skipTokenCount;
};

size_t SyntaxAnalyzer::scanningPackageDef(const size_t pos_) {
  size_t skipTokenCount = 0;
  skipTokenCount++;
  size_t pos = pos_ + skipTokenCount;
  std::string packageName = "";
  Token tokenPkgNm;
  TokenTypeEnum tokenTypePkg;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCount = tokens->getParsableTokenCount();
  tokenPkgNm = tokens->get(pos);
  tokenTypePkg = tokenPkgNm.getTokenType();
  if (tokenTypePkg == TokenTypeEnum::symbolCharacterDoller) {
    pos++;
    skipTokenCount++;
    tokenPkgNm = tokens->get(pos);
    tokenTypePkg = tokenPkgNm.getTokenType();
  } else {
    Location loc = tokenPkgNm.getLocation();
    llvm::outs() << "invalid package name. loc: " + loc.getString();
    throw "";
  }
  if (tokenTypePkg == TokenTypeEnum::identifier) {
    for (pos = pos_ + skipTokenCount, tokenPkgNm = tokens->get(pos),
        tokenTypePkg = tokenPkgNm.getTokenType();
         pos < tokenCount &&
         (tokenTypePkg == TokenTypeEnum::identifier ||
          tokenTypePkg == TokenTypeEnum::symbolCharacterDot);
         pos++, skipTokenCount++, tokenPkgNm = tokens->get(pos),
        tokenTypePkg = tokenPkgNm.getTokenType()) {
      packageName += tokenPkgNm.getToken();
    }
    tokenPkgNm = tokens->get(pos);
    tokenTypePkg = tokenPkgNm.getTokenType();
    if (tokenTypePkg != TokenTypeEnum::symbolCharacterSemicolon) {
      Location loc = tokenPkgNm.getLocation();
      llvm::outs() << "invalid package name. loc: " + loc.getString();
      llvm::outs() << "";
      ;
      throw "";
    }
    skipTokenCount++;

    AstNodeModule *modNode = (AstNodeModule *)(currentNode->getModule());
    if (!modNode->isDefinedPackageName()) {
      modNode->replacePackageName(packageName);
    }
  } else {
    Location loc = tokenPkgNm.getLocation();
    llvm::outs() << "invalid package name. loc: " + loc.getString();
    throw "";
  }
  return skipTokenCount;
};

size_t SyntaxAnalyzer::scanningModuleDef(const size_t pos_) {
  size_t skipTokenCount = 0;
  skipTokenCount++;
  size_t pos = pos_ + skipTokenCount;
  std::string moduleName = "";
  Token tokenModNm;
  TokenTypeEnum tokenTypeMod;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  tokenModNm = tokens->get(pos);
  tokenTypeMod = tokenModNm.getTokenType();
  if (tokenTypeMod == TokenTypeEnum::symbolCharacterDoller) {
    pos++;
    skipTokenCount++;
    tokenModNm = tokens->get(pos);
    tokenTypeMod = tokenModNm.getTokenType();
  } else {
    Location loc = tokenModNm.getLocation();
    llvm::outs() << "invalid module name. loc: " + loc.getString();
    throw "";
  }
  if (tokenTypeMod == TokenTypeEnum::identifier) {
    moduleName += tokenModNm.getToken();
    skipTokenCount++;
    pos = pos_ + skipTokenCount;
    tokenModNm = tokens->get(pos);
    tokenTypeMod = tokenModNm.getTokenType();
    if (tokenTypeMod != TokenTypeEnum::symbolCharacterSemicolon) {
      Location loc = tokenModNm.getLocation();
      llvm::outs() << "invalid module name. loc: " + loc.getString();
      throw "";
    }
    skipTokenCount++;

    AstNodeModule *modNode = (AstNodeModule *)(currentNode->getModule());
    if (!modNode->isDefinedModuleName()) {
      modNode->replaceModuleName(moduleName);
    }
  } else {
    Location loc = tokenModNm.getLocation();
    llvm::outs() << "invalid module name. loc: " + loc.getString();
    throw "";
  }
  return skipTokenCount;
};

size_t SyntaxAnalyzer::scanningDeclareFmain(const size_t pos_) {
  size_t skipTokenCount = 0;
  skipTokenCount++;
  size_t pos = pos_ + skipTokenCount;
  std::string entryPointId = "";
  Token tokenEntryPointId;
  TokenTypeEnum tokenTypeEpId;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  Token tokenDeclareFmain = tokens->get(pos_);
  tokenEntryPointId = tokens->get(pos);
  tokenTypeEpId = tokenEntryPointId.getTokenType();
  if (tokenTypeEpId == TokenTypeEnum::symbolCharacterDoller) {
    pos++;
    skipTokenCount++;
    tokenEntryPointId = tokens->get(pos);
    tokenTypeEpId = tokenEntryPointId.getTokenType();
    if (tokenTypeEpId == TokenTypeEnum::identifier) {
      entryPointId = tokenEntryPointId.getToken();
      skipTokenCount++;
      if (tokens->get(pos + 1).getTokenType() !=
              TokenTypeEnum::symbolCharacterLeftcurlybrackets &&
          tokens->get(pos + 1).getTokenType() !=
              TokenTypeEnum::symbolCharacterSemicolon) {
        llvm::outs() << "invalid declare fmain format";
        ;
        throw "";
      }
      if (moduleNode->getAstNodeType() == AstNodeTypeEnum::moduleInterpreter) {
        llvm::outs() << "cannot declare fmain in interpreter";
        ;
        throw "";
      };
      AstNodeDeclareFmain *fmainNode = new AstNodeDeclareFmain(
          tokenDeclareFmain.getLocation(), entryPointId);
      pushNode(fmainNode);
      ((AstNodeRoot *)(moduleNode->getRoot()))->setEntoryPoint(fmainNode);
    } else {
      Location loc = tokenEntryPointId.getLocation();
      llvm::outs() << "invalid declare fmain format. loc: " + loc.getString();
      throw "";
    }
  } else if (tokenTypeEpId == TokenTypeEnum::symbolCharacterLeftcurlybrackets ||
             tokenTypeEpId == TokenTypeEnum::symbolCharacterSemicolon) {
    if (moduleNode->getAstNodeType() == AstNodeTypeEnum::moduleInterpreter) {
      llvm::outs() << "cannot declare fmain in interpreter";
      ;
      throw "";
    };
    AstNodeDeclareFmain *fmainNode =
        new AstNodeDeclareFmain(tokenDeclareFmain.getLocation());
    pushNode(fmainNode);
    ((AstNodeRoot *)(moduleNode->getRoot()))->setEntoryPoint(fmainNode);
    if (tokenTypeEpId == TokenTypeEnum::symbolCharacterSemicolon) {
      skipTokenCount++;
    }
  } else {
    Location loc = tokenEntryPointId.getLocation();
    llvm::outs() << "invalid declare fmain format. loc: " + loc.getString();
    throw "";
  }
  return skipTokenCount;
};

size_t SyntaxAnalyzer::scanningControlBlock(const size_t pos_) {
  size_t skipTokenCount = 0;
  skipTokenCount++;
  blockDepthInModule++;
  // size_t currentBlockDepthInModule = blockDepthInModule;
  size_t pos = pos_ + skipTokenCount;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCount = tokens->getParsableTokenCount();
  Token tokenBeginBlock = tokens->get(pos_);
  AstNodeTypeEnum nodeType = currentNode->getAstNodeType();
  AstNodeTypeEnum blockNodeType = nodeType;
  if (!(AstNodeType::isDeclareFunction(blockNodeType) ||
        nodeType == AstNodeTypeEnum::controlBlock)) {
    blockNodeType = currentNode->getParent()->getAstNodeType();
  }
  AstNodeControlBlock *blockNode =
      new AstNodeControlBlock(tokenBeginBlock.getLocation(), blockNodeType);
  pushNode(blockNode);
  Token tokenInBlock;
  TokenTypeEnum tokenTypeInBlock;
  for (pos = pos_ + skipTokenCount, tokenInBlock = tokens->get(pos),
      tokenTypeInBlock = tokenInBlock.getTokenType();
       pos < tokenCount &&
       tokenTypeInBlock != TokenTypeEnum::symbolCharacterRightcurlybrackets;
       tokenInBlock = tokens->get(pos),
      tokenTypeInBlock = tokenInBlock.getTokenType()) {
    if (TokenType::isCommentOut(tokenTypeInBlock)) {
      size_t skipTokenCountCo = scanningCommentOut(pos);
      skipTokenCount += skipTokenCountCo;
      pos += skipTokenCountCo;
      parsedTokenPos = pos;
      continue;
    } else if (TokenType::isCharCodesDelimiter(tokenTypeInBlock)) {
      size_t skipTokenCountCharCodes = scanningCharCodes(pos);
      skipTokenCount += skipTokenCountCharCodes;
      pos += skipTokenCountCharCodes;
      parsedTokenPos = pos;
      continue;
    } else if (tokenTypeInBlock ==
                   TokenTypeEnum::literalDecimalNumberIntegralPart ||
               tokenTypeInBlock ==
                   TokenTypeEnum::symbolCharacterNegativeDecimal) {
      size_t skipTokenCountNumber = scanningDecimalNumber(pos);
      skipTokenCount += skipTokenCountNumber;
      pos += skipTokenCountNumber;
      parsedTokenPos = pos;
      continue;
    }
    pos++;
    skipTokenCount++;
  }
  if (tokenTypeInBlock == TokenTypeEnum::symbolCharacterRightcurlybrackets) {
    Token tokenEndBlock = tokenInBlock;
    ((AstNodeControlBlock *)(blockNode))
        ->setEndLocation(tokenEndBlock.getLocation());
    currentNode = currentNode->getParent();
    blockDepthInModule--;
  }
  return skipTokenCount;
};

size_t SyntaxAnalyzer::scanningDecimalNumber(const size_t pos_) {
  size_t skipTokenCount = 0;
  std::string charCodes = "";
  Tokens *tokens = lexicalAnalyzer->getTokens();
  Token decimalToken = tokens->get(pos_);
  bool isNegative = false;
  size_t pos = pos_;

  std::string integralDigitStr = "";
  size_t integralDigitStrLen = 0;
  const char *integralDigitStrPtr;
  std::string integralStr = "";
  // negative
  if (decimalToken.getTokenType() ==
      TokenTypeEnum::symbolCharacterNegativeDecimal) {
    isNegative = true;
    skipTokenCount++;
    pos++;
    decimalToken = tokens->get(pos);
  }
  // get integral str
  integralDigitStr = decimalToken.getToken();
  pos++;
  skipTokenCount++;
  integralDigitStrPtr = integralDigitStr.c_str();
  integralDigitStrLen = integralDigitStr.length();
  integralStr.reserve(integralDigitStrLen);
  // trim padding 0
  // skip underscore
  for (size_t integralDigitPos = 0; integralDigitPos < integralDigitStrLen;
       integralDigitPos++) {
    if (*(integralDigitStrPtr + integralDigitPos) == '_') {
      continue;
    }
    if (integralStr.length() == 0 &&
        *(integralDigitStrPtr + integralDigitPos) == '0') {
      continue;
    }
    integralStr.push_back(*(integralDigitStrPtr + integralDigitPos));
  }
  if (integralStr == "") {
    integralStr = "0";
  }

  decimalToken = tokens->get(pos);
  std::string decimalDigitStr = "";
  size_t decimalDigitStrLen = 0;
  const char *decimalDigitStrPtr;
  std::string decimalStr = "";
  // get decimal str
  if (decimalToken.getTokenType() == TokenTypeEnum::symbolCharacterDot) {
    pos++;
    skipTokenCount++;
    decimalToken = tokens->get(pos);
    if (decimalToken.getTokenType() ==
        TokenTypeEnum::literalDecimalNumberDecimalPart) {
      decimalDigitStr = decimalToken.getToken();
      pos++;
      skipTokenCount++;
      decimalDigitStrLen = decimalDigitStr.length();
      decimalDigitStrPtr = decimalDigitStr.c_str();
      decimalStr.reserve(decimalDigitStrLen);
      // skip underscore
      for (size_t decimalDigitPos = 0; decimalDigitPos < decimalDigitStrLen;
           decimalDigitPos++) {
        if (*(decimalDigitStrPtr + decimalDigitPos) == '_') {
          continue;
        }
        decimalStr.push_back(*(decimalDigitStrPtr + decimalDigitPos));
      }
    }
  }

  decimalToken = tokens->get(pos);
  std::string exponentDigitStr = "";
  size_t exponentDigitStrLen = 0;
  const char *exponentDigitStrPtr;
  std::string exponentStr = "";
  bool isExponent = false;
  bool isExponentNegative = false;
  // get exponent str
  if (decimalToken.getTokenType() ==
      TokenTypeEnum::literalDecimalNumberExponentOperator) {
    pos++;
    skipTokenCount++;
    decimalToken = tokens->get(pos);
    isExponent = true;
    if (decimalToken.getTokenType() ==
        TokenTypeEnum::symbolCharacterPositiveDecimalExponent) {
      pos++;
      skipTokenCount++;
      decimalToken = tokens->get(pos);
    } else if (decimalToken.getTokenType() ==
               TokenTypeEnum::symbolCharacterPositiveDecimalExponent) {
      pos++;
      skipTokenCount++;
      decimalToken = tokens->get(pos);
      isExponentNegative = true;
    }
    exponentDigitStr = decimalToken.getToken();
    pos++;
    skipTokenCount++;
    exponentDigitStrLen = exponentDigitStr.length();
    exponentDigitStrPtr = exponentDigitStr.c_str();
    exponentStr.reserve(exponentDigitStrLen);
    // trim padding 0
    for (size_t exponentDigitPos = 0; exponentDigitPos < exponentDigitStrLen;
         exponentDigitPos++) {
      if (exponentStr.length() == 0 &&
          *(exponentDigitStrPtr + exponentDigitPos) == '0') {
        continue;
      }
      exponentStr.push_back(*(exponentDigitStrPtr + exponentDigitPos));
    }
    if (exponentStr == "") {
      exponentStr = "0";
    }
  } else if (decimalToken.getTokenType() == TokenTypeEnum::identifier) {
    std::string identifierStr = decimalToken.getToken();
    if (identifierStr == "e" || identifierStr == "E") {
      llvm::outs() << "has not exponent digit";
      throw "";
    } else {
      llvm::outs() << "invalid decimal number";
      throw "";
    }
  }
  llvm::outs() << "decimal number:";
  if (isNegative) {
    llvm::outs() << "-";
  }
  llvm::outs() << integralStr;
  if (decimalStr != "") {
    llvm::outs() << "." << decimalStr;
  }
  if (isExponent) {
    llvm::outs() << "e";
    if (isExponentNegative) {
      llvm::outs() << "-";
    };
    llvm::outs() << exponentStr;
  }
  llvm::outs() << "\n";

  return skipTokenCount;
};

uint16_t
gallop::Compiler::Parser::SyntaxAnalyzer::getBitLength(uint64_t decimalNumber) {
  uint16_t bitLength = maxBits;
  if (decimalNumber > 0) {
    for (; bitLength > 0; bitLength--) {
      if ((decimalNumber & ((uint64_t)((uint64_t)1 << (bitLength - 1)))) > 0) {
        break;
      }
    }
  } else {
    bitLength = 1;
  }
  return bitLength;
};

size_t SyntaxAnalyzer::scanningCharCodes(const size_t pos_) {
  size_t skipTokenCount = 0;
  std::string charCodes = "";
  uint32_t utf32code = 0;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  size_t tokenCount = tokens->getParsableTokenCount();
  Token charCodeTokenBegin = tokens->get(pos_);
  TokenTypeEnum delimiterTokenType = charCodeTokenBegin.getTokenType();
  AstNodeTypeEnum nodeType = AstNodeTypeEnum::charCodeLiteral;
  char tokenDelimiter = '\'';
  if (delimiterTokenType != TokenTypeEnum::symbolCharacterSinglequote) {
    nodeType = AstNodeTypeEnum::stringLiteral;
    if (delimiterTokenType == TokenTypeEnum::symbolCharacterDoublequote) {
      tokenDelimiter = '"';
    } else {
      tokenDelimiter = '`';
    }
  }
  skipTokenCount++;
  Token tokenCharCodes;
  TokenTypeEnum tokenTypeCharCodes;
  size_t pos = pos_ + skipTokenCount;
  size_t charCodesBufferSize = 0;
  for (tokenCharCodes = tokens->get(pos),
      tokenTypeCharCodes = tokenCharCodes.getTokenType();
       pos < tokenCount && tokenTypeCharCodes != delimiterTokenType;
       pos++, tokenCharCodes = tokens->get(pos),
      tokenTypeCharCodes = tokenCharCodes.getTokenType()) {
    charCodesBufferSize += tokenCharCodes.getTokenLen();
  }
  charCodes.reserve(charCodesBufferSize);
  pos = pos_ + skipTokenCount;
  bool isTerminate = false;
  for (tokenCharCodes = tokens->get(pos),
      tokenTypeCharCodes = tokenCharCodes.getTokenType();
       pos < tokenCount && tokenTypeCharCodes != delimiterTokenType;
       pos++, skipTokenCount++, tokenCharCodes = tokens->get(pos),
      tokenTypeCharCodes = tokenCharCodes.getTokenType()) {
    if (isTerminate) {
      continue;
    }
    if (delimiterTokenType == TokenTypeEnum::symbolCharacterBackquote) {
      if (tokenTypeCharCodes == TokenTypeEnum::literalEscapeSequence) {
        std::string esStr = tokenCharCodes.getToken();
        uint8_t esChar = esStr[1];
        switch (esChar) {
        case '\\':
          if (pos + 1 < tokenCount) {
            Token nextCharCodeToken = tokens->get(pos + 1);
            std::string nextCharCodeStr = nextCharCodeToken.getToken();
            uint8_t nextCharCodeChar = nextCharCodeStr[0];
            if (nextCharCodeToken.getTokenType() ==
                    TokenTypeEnum::literalRawString &&
                (nextCharCodeChar == '\r' || nextCharCodeChar == '\n')) {
              charCodes.push_back('\\');
            } else {
              charCodes += tokenCharCodes.getToken();
            }
          } else {
            charCodes += tokenCharCodes.getToken();
          }
          break;
        default:
          if (esChar == tokenDelimiter) {
            charCodes.push_back(tokenDelimiter);
          } else {
            charCodes += tokenCharCodes.getToken();
          }
        }
      } else {
        charCodes += tokenCharCodes.getToken();
      }
    } else {
      if (tokenTypeCharCodes == TokenTypeEnum::literalEscapeSequence) {
        std::string esStr = tokenCharCodes.getToken();
        char esChar = esStr[1];
        switch (esChar) {
        case 'a':
          charCodes.push_back('\a');
          break;
        case 'f':
          charCodes.push_back('\f');
          break;
        case 'n':
          charCodes.push_back('\n');
          break;
        case 'r':
          charCodes.push_back('\r');
          break;
        case 't':
          charCodes.push_back('\t');
          break;
        case 'v':
          charCodes.push_back('\v');
          break;
        case '\\':
          charCodes.push_back('\\');
          break;
        case 'e':
          charCodes.push_back(static_cast<char>(0x1b));
          break;
        case 'b':
          charCodes.pop_back();
          break;
        case '0':
          isTerminate = true;
          break;
        default:
          if (esChar == tokenDelimiter) {
            charCodes.push_back(tokenDelimiter);
          } else {
            charCodes += tokenCharCodes.getToken();
          }
        }
      } else if (tokenTypeCharCodes ==
                 TokenTypeEnum::literalCharCodeOctalEscapeSequence) {
        if (pos + 1 < tokenCount) {
          Token tokenCharCode = tokens->get(pos + 1);
          TokenTypeEnum tokenTypeCharCode = tokenCharCode.getTokenType();
          if (tokenTypeCharCode != TokenTypeEnum::literalOctalNumber) {
            charCodes += tokenCharCodes.getToken();
          } else {
            std::string ccToken = tokenCharCode.getToken();
            std::string codeString, otherString;
            std::tie(codeString, utf32code, otherString, isTerminate) =
                parseCharCodeOctalDigit(ccToken);
            if (!isTerminate) {
              charCodes += (codeString + otherString);
            }
            pos++;
            skipTokenCount++;
          }
        } else {
          charCodes += tokenCharCodes.getToken();
        }
      } else if (tokenTypeCharCodes ==
                 TokenTypeEnum::literalCharCodeHexadecimalEscapeSequence) {
        if (pos + 1 < tokenCount) {
          Token tokenCharCode = tokens->get(pos + 1);
          TokenTypeEnum tokenTypeCharCode = tokenCharCode.getTokenType();
          if (tokenTypeCharCode != TokenTypeEnum::literalHexadecimalNumber) {
            charCodes += tokenCharCodes.getToken();
          } else {
            std::string ccToken = tokenCharCode.getToken();
            std::string codeString, otherString;
            std::tie(codeString, utf32code, otherString, isTerminate) =
                parseCharCodeHexadecimal(ccToken);
            if (!isTerminate) {
              charCodes += (codeString + otherString);
            }
            pos++;
            skipTokenCount++;
          }
        } else {
          charCodes += tokenCharCodes.getToken();
        }
      } else if (tokenTypeCharCodes ==
                 TokenTypeEnum::literalCharCodeUnicodePointEscapeSequence) {
        if (pos + 1 < tokenCount) {
          Token tokenCharCode = tokens->get(pos + 1);
          TokenTypeEnum tokenTypeCharCode = tokenCharCode.getTokenType();
          if (tokenTypeCharCode != TokenTypeEnum::literalHexadecimalNumber) {
            charCodes += tokenCharCodes.getToken();
          } else {
            std::string ccToken = tokenCharCode.getToken();
            std::string codeString, otherString;
            std::tie(codeString, utf32code, otherString, isTerminate) =
                parseCharCodeUnicodePoint(ccToken);
            if (!isTerminate) {
              charCodes += (codeString + otherString);
            }
            pos++;
            skipTokenCount++;
          }
        } else {
          charCodes += tokenCharCodes.getToken();
        }
      } else {
        charCodes += tokenCharCodes.getToken();
      }
    }
  }
  Token charCodeTokenEnd = tokens->get(pos);
  skipTokenCount++;
  if (nodeType == AstNodeTypeEnum::charCodeLiteral) {
    if (charCodes != "") {
      AstNodeCharCodeLiteral *charCodeNode = new AstNodeCharCodeLiteral(
          charCodeTokenBegin.getLocation(), charCodeTokenEnd.getLocation(),
          utf32code, charCodes);
      pushNode(charCodeNode);
    } else {
      AstNodeCharCodeLiteral *charCodeNode = new AstNodeCharCodeLiteral(
          charCodeTokenBegin.getLocation(), charCodeTokenEnd.getLocation(),
          static_cast<uint32_t>(0), charCodes);
      pushNode(charCodeNode);
    }
  } else {
    AstNodeStringLiteral *strNode =
        new AstNodeStringLiteral(charCodeTokenBegin.getLocation(),
                                 charCodeTokenEnd.getLocation(), charCodes);
    pushNode(strNode);
  }
  return skipTokenCount;
};

std::tuple<std::string, uint32_t, std::string, bool>
SyntaxAnalyzer::parseCharCodeOctalDigit(const std::string octalDigitStr_) {
  std::string codeString = "";
  std::string postString = "";
  const char *octalDigitStrPtr = octalDigitStr_.c_str();
  size_t pos = 0, paddingDigitStrLen = 0,
         octalDigitStrStrLen = octalDigitStr_.length(),
         parseDigitStrLen = octalDigitStrStrLen;
  if (parseDigitStrLen > 11) {
    parseDigitStrLen = 11;
  }
  if (parseDigitStrLen == 11 && *(octalDigitStrPtr) > '3') {
    parseDigitStrLen--;
  }
  for (; paddingDigitStrLen < parseDigitStrLen &&
         *(octalDigitStrPtr + paddingDigitStrLen) == '0';
       paddingDigitStrLen++, pos++)
    ;
  if (paddingDigitStrLen == octalDigitStrStrLen || paddingDigitStrLen > 2) {
    // null char terminate
    return std::forward_as_tuple(codeString, static_cast<uint32_t>(0),
                                 postString, true);
  }
  // to utf8 binary
  size_t parseBitCount = paddingDigitStrLen * 3;
  uint32_t charCodeUtf8 = 0;
  uint32_t charCodeUtf32 = 0;
  bool isUtf8 = false;
  switch (*(octalDigitStrPtr + pos)) {
  case '1':
    parseBitCount++;
    if (paddingDigitStrLen > 0) {
      parseBitCount++;
    }
    charCodeUtf8 = *(octalDigitStrPtr + pos) - '0';
    break;
  case '2':
  case '3':
    parseBitCount += 2;
    charCodeUtf8 = *(octalDigitStrPtr + pos) - '0';
    break;
  case '4':
  case '5':
  case '6':
  case '7':
    parseBitCount += 3;
    if (paddingDigitStrLen > 0) {
      parseBitCount--;
    }
    charCodeUtf8 = *(octalDigitStrPtr + pos) - '0';
    break;
  }
  pos++;
  for (; pos < parseDigitStrLen; pos++) {
    uint8_t codeDigit = *(octalDigitStrPtr + pos) - '0';
    charCodeUtf8 = charCodeUtf8 << 3 | codeDigit;
    parseBitCount += 3;
  }
  // trim the remaining part in 8-bit units
  ssize_t surplusBitCount = (ssize_t)parseBitCount;
  if (parseBitCount > 8) {
    while (surplusBitCount >= 8) {
      surplusBitCount -= 8;
    }
    while (surplusBitCount > 0) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 3;
      parseBitCount -= 3;
      surplusBitCount -= 3;
    }
  }
  // to UTF-8 string
  if (((charCodeUtf8 & static_cast<uint32_t>(0xf8c0c0c0)) ==
       static_cast<uint32_t>(0xf0808080))) {
    // 4byte
    // 0xf0808080/0o36040100200 <= chr <= 0xf4bfbfbf/36457737677
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0xff000000)) >>
                         24);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x00ff0000)) >>
                         16);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x0000ff00)) >>
                         8);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x000000ff)));
    charCodeUtf32 = (charCodeUtf8 & static_cast<uint32_t>(0x07000000)) >> 6;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x003f0000)) >> 4;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x00003f00)) >> 2;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x0000003f));
    isUtf8 = true;
  } else if (parseBitCount > 24) {
    while (parseBitCount > 24) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 3;
      parseBitCount -= 3;
    }
  }
  if (!isUtf8 && ((charCodeUtf8 & static_cast<uint32_t>(0x00f0c0c0)) ==
                  static_cast<uint32_t>(0x00e08080))) {
    // 3byte
    // 0xe08080/0o70100200 <= chr <= 0xefbfbf/0o73737677
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x00ff0000)) >>
                         16);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x0000ff00)) >>
                         8);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x000000ff)));
    charCodeUtf32 = (charCodeUtf8 & static_cast<uint32_t>(0x000f0000)) >> 4;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x00003f00)) >> 2;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x0000003f));
    isUtf8 = true;
  } else if (!isUtf8 && parseBitCount > 16) {
    while (parseBitCount > 16) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 3;
      parseBitCount -= 3;
    }
  }
  if (!isUtf8 && ((charCodeUtf8 & static_cast<uint32_t>(0x0000e0c0)) ==
                  static_cast<uint32_t>(0x0000c080))) {
    // 2byte
    // 0xc280/0o141200 <= chr <= 0xdfbf/0o157677
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x0000ff00)) >>
                         8);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x000000ff)));
    charCodeUtf32 = (charCodeUtf8 & static_cast<uint32_t>(0x00001f00)) >> 2;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x0000003f));
    isUtf8 = true;
  } else if (!isUtf8 && parseBitCount > 8) {
    while (parseBitCount > 8) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 3;
      parseBitCount -= 3;
    }
  }
  if (!isUtf8 && parseBitCount <= 8 &&
      ((charCodeUtf8 & static_cast<uint32_t>(0xffffff80)) >
       static_cast<uint32_t>(0x00000000))) {
    while (parseBitCount > 7) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 3;
      parseBitCount -= 3;
    }
    codeString.push_back(charCodeUtf8);
    charCodeUtf32 = charCodeUtf8;
  } else if (!isUtf8 && parseBitCount <= 8) {
    // 1byte
    // 0x00/0o000 <= chr <= 0x7f0o177
    codeString.push_back(charCodeUtf8);
    charCodeUtf32 = charCodeUtf8;
  }
  if (parseDigitStrLen != octalDigitStrStrLen) {
    postString.append(octalDigitStr_.substr(
        parseDigitStrLen, octalDigitStrStrLen - parseDigitStrLen));
  }
  return std::forward_as_tuple(codeString, charCodeUtf32, postString, false);
};

std::tuple<std::string, uint32_t, std::string, bool>
SyntaxAnalyzer::parseCharCodeHexadecimal(
    const std::string hexadecimalDigitStr_) {
  std::string codeString = "";
  std::string postString = "";
  const char *hexadecimalDigitStrPtr = hexadecimalDigitStr_.c_str();
  size_t pos = 0, paddingDigitStrLen = 0,
         hexadecimalDigitStrStrLen = hexadecimalDigitStr_.length(),
         parseDigitStrLen = hexadecimalDigitStrStrLen;
  if (parseDigitStrLen > 8) {
    parseDigitStrLen = 8;
  }
  for (; paddingDigitStrLen < parseDigitStrLen &&
         *(hexadecimalDigitStrPtr + paddingDigitStrLen) == '0';
       paddingDigitStrLen++, pos++)
    ;
  if (paddingDigitStrLen == hexadecimalDigitStrStrLen ||
      paddingDigitStrLen > 1) {
    // null char terminate
    return std::forward_as_tuple(codeString, static_cast<uint32_t>(0),
                                 postString, true);
  }
  // to utf8 binary
  size_t parseBitCount = paddingDigitStrLen * 4;
  uint32_t charCodeUtf8 = 0;
  uint32_t charCodeUtf32 = 0;
  bool isUtf8 = false;
  for (; pos < parseDigitStrLen; pos++) {
    uint8_t codeDigit = *(hexadecimalDigitStrPtr + pos);
    if ('0' <= codeDigit && codeDigit <= '9') {
      codeDigit -= '0';
    } else if ('A' <= codeDigit && codeDigit <= 'F') {
      codeDigit -= 'A';
      codeDigit += 10;
    } else {
      codeDigit -= 'a';
      codeDigit += 10;
    }
    charCodeUtf8 = charCodeUtf8 << 4 | codeDigit;
    parseBitCount += 4;
  }
  // trim the remaining part in 8-bit units
  ssize_t surplusBitCount = (ssize_t)parseBitCount;
  if (parseBitCount > 8) {
    while (surplusBitCount >= 8) {
      surplusBitCount -= 8;
    }
    if (surplusBitCount > 0) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 4;
      parseBitCount -= 4;
      surplusBitCount -= 4;
    }
  }
  // to UTF-8 string
  if (((charCodeUtf8 & static_cast<uint32_t>(0xf8c0c0c0)) ==
       static_cast<uint32_t>(0xf0808080))) {
    // 4byte
    // 0xf0808080/0o36040100200 <= chr <= 0xf4bfbfbf/36457737677
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0xff000000)) >>
                         24);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x00ff0000)) >>
                         16);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x0000ff00)) >>
                         8);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x000000ff)));
    charCodeUtf32 = (charCodeUtf8 & static_cast<uint32_t>(0x07000000)) >> 6;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x003f0000)) >> 4;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x00003f00)) >> 2;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x0000003f));
    isUtf8 = true;
  } else if (parseBitCount > 24) {
    while (parseBitCount > 24) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 4;
      parseBitCount -= 4;
    }
  }
  if (!isUtf8 && ((charCodeUtf8 & static_cast<uint32_t>(0x00f0c0c0)) ==
                  static_cast<uint32_t>(0x00e08080))) {
    // 3byte
    // 0xe08080/0o70100200 <= chr <= 0xefbfbf/0o73737677
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x00ff0000)) >>
                         16);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x0000ff00)) >>
                         8);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x000000ff)));
    charCodeUtf32 = (charCodeUtf8 & static_cast<uint32_t>(0x000f0000)) >> 4;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x00003f00)) >> 2;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x0000003f));
    isUtf8 = true;
  } else if (!isUtf8 && parseBitCount > 16) {
    while (parseBitCount > 16) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 4;
      parseBitCount -= 4;
    }
  }
  if (!isUtf8 && ((charCodeUtf8 & static_cast<uint32_t>(0x0000e0c0)) ==
                  static_cast<uint32_t>(0x0000c080))) {
    // 2byte
    // 0xc280/0o141200 <= chr <= 0xdfbf/0o157677
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x0000ff00)) >>
                         8);
    codeString.push_back((charCodeUtf8 & static_cast<uint32_t>(0x000000ff)));
    charCodeUtf32 = (charCodeUtf8 & static_cast<uint32_t>(0x00001f00)) >> 2;
    charCodeUtf32 |= (charCodeUtf8 & static_cast<uint32_t>(0x0000003f));
    isUtf8 = true;
  } else if (!isUtf8 && parseBitCount > 8) {
    while (parseBitCount > 8) {
      parseDigitStrLen--;
      charCodeUtf8 = charCodeUtf8 >> 4;
      parseBitCount -= 4;
    }
  }
  if (!isUtf8 && parseBitCount <= 8 &&
      ((charCodeUtf8 & static_cast<uint32_t>(0xffffff80)) >
       static_cast<uint32_t>(0x00000000))) {
    parseDigitStrLen--;
    charCodeUtf8 = charCodeUtf8 >> 4;
    parseBitCount -= 4;
    codeString.push_back(charCodeUtf8);
    charCodeUtf32 = charCodeUtf8;
  } else if (!isUtf8 && parseBitCount <= 8) {
    // 1byte
    // 0x00/0o000 <= chr <= 0x7f0o177
    codeString.push_back(charCodeUtf8);
    charCodeUtf32 = charCodeUtf8;
  }
  if (parseDigitStrLen != hexadecimalDigitStrStrLen) {
    postString.append(hexadecimalDigitStr_.substr(
        parseDigitStrLen, hexadecimalDigitStrStrLen - parseDigitStrLen));
  }
  return std::forward_as_tuple(codeString, charCodeUtf32, postString, false);
};

std::tuple<std::string, uint32_t, std::string, bool>
SyntaxAnalyzer::parseCharCodeUnicodePoint(
    const std::string unicodePointDigitStr_) {
  std::string codeString = "";
  std::string postString = "";
  const char *unicodePointDigitStrPtr = unicodePointDigitStr_.c_str();
  size_t pos = 0, paddingDigitStrLen = 0,
         unicodePointDigitStrStrLen = unicodePointDigitStr_.length(),
         parseDigitStrLen = unicodePointDigitStrStrLen;
  if (parseDigitStrLen > 6) {
    parseDigitStrLen = 6;
  }
  for (; paddingDigitStrLen < parseDigitStrLen &&
         *(unicodePointDigitStrPtr + paddingDigitStrLen) == '0';
       paddingDigitStrLen++, pos++)
    ;
  if (paddingDigitStrLen == unicodePointDigitStrStrLen ||
      paddingDigitStrLen > 4) {
    // null char terminate
    return std::forward_as_tuple(codeString, static_cast<uint32_t>(0),
                                 postString, true);
  }
  // to utf32 binary
  size_t parseBitCount = paddingDigitStrLen * 4;
  uint32_t charCodeUtf32 = 0;
  for (; pos < parseDigitStrLen; pos++) {
    uint8_t codeDigit = *(unicodePointDigitStrPtr + pos);
    if ('0' <= codeDigit && codeDigit <= '9') {
      codeDigit -= '0';
    } else if ('A' <= codeDigit && codeDigit <= 'F') {
      codeDigit -= 'A';
      codeDigit += 10;
    } else {
      codeDigit -= 'a';
      codeDigit += 10;
    }
    charCodeUtf32 = charCodeUtf32 << 4 | codeDigit;
    parseBitCount += 4;
  }
  bool isUtf32 = false;
  // trim the remaining part in 8-bit units
  ssize_t surplusBitCount = (ssize_t)parseBitCount;
  if (parseBitCount > 8) {
    while (surplusBitCount >= 8) {
      surplusBitCount -= 8;
    }
    if (surplusBitCount > 0) {
      parseDigitStrLen--;
      charCodeUtf32 = charCodeUtf32 >> 4;
      parseBitCount -= 4;
      surplusBitCount -= 4;
    }
  }
  // to UTF-8 string
  if (static_cast<uint32_t>(0x00010000) <= charCodeUtf32 &&
      charCodeUtf32 <= static_cast<uint32_t>(0x0010ffff)) {
    // 4byte
    // U+010000 <= chr <= U+10FFFF
    // 0xf0808080/0o36040100200 <= chr <= 0xf4bfbfbf/36457737677
    codeString.push_back(static_cast<char>(0xf0) | (char)(charCodeUtf32 >> 18));
    codeString.push_back(
        static_cast<char>(0x80) |
        ((char)(charCodeUtf32 >> 12) & static_cast<char>(0x3f)));
    codeString.push_back(static_cast<char>(0x80) | ((char)(charCodeUtf32 >> 6) &
                                                    static_cast<char>(0x3f)));
    codeString.push_back(static_cast<char>(0x80) |
                         ((char)(charCodeUtf32) & static_cast<char>(0x3f)));
    isUtf32 = true;
  } else if (parseBitCount > 16) {
    while (parseBitCount > 16) {
      parseDigitStrLen--;
      charCodeUtf32 = charCodeUtf32 >> 4;
      parseBitCount -= 4;
    }
  }
  if (static_cast<uint32_t>(0x00000800) <= charCodeUtf32 &&
      charCodeUtf32 <= static_cast<uint32_t>(0x0000ffff) &&
      !(static_cast<uint32_t>(0x0000d800) <= charCodeUtf32 &&
        charCodeUtf32 <= static_cast<uint32_t>(0x0000dfff))) {
    // 3byte
    // U+000800 <= chr <= U+00FFFF
    // 0xe08080/0o70100200 <= chr <= 0xefbfbf/0o73737677
    codeString.push_back(static_cast<char>(0xe0) | (char)(charCodeUtf32 >> 12));
    codeString.push_back(static_cast<char>(0x80) | ((char)(charCodeUtf32 >> 6) &
                                                    static_cast<char>(0x3f)));
    codeString.push_back(static_cast<char>(0x80) |
                         ((char)(charCodeUtf32) & static_cast<char>(0x3f)));
    isUtf32 = true;
  } else if (!isUtf32 && parseBitCount > 12) {
    while (parseBitCount > 12) {
      parseDigitStrLen--;
      charCodeUtf32 = charCodeUtf32 >> 4;
      parseBitCount -= 4;
    }
  }
  if (static_cast<uint32_t>(0x00000080) <= charCodeUtf32 &&
      charCodeUtf32 <= static_cast<uint32_t>(0x000007ff)) {
    // 2byte
    // U+000080 <= chr <= U+0007FF
    // 0xc280/0o141200 <= chr <= 0xdfbf/0o157677
    codeString.push_back(static_cast<char>(0xc0) | (char)(charCodeUtf32 >> 6));
    codeString.push_back(static_cast<char>(0x80) |
                         ((char)(charCodeUtf32) & static_cast<char>(0x3f)));
    isUtf32 = true;
  } else if (!isUtf32 && parseBitCount > 8) {
    while (parseBitCount > 8) {
      parseDigitStrLen--;
      charCodeUtf32 = charCodeUtf32 >> 4;
      parseBitCount -= 4;
    }
  }
  if (!isUtf32 && static_cast<uint32_t>(0x00000080) <= charCodeUtf32) {
    parseDigitStrLen--;
    charCodeUtf32 = charCodeUtf32 >> 4;
    parseBitCount -= 4;
    codeString.push_back(charCodeUtf32);
  } else if (!isUtf32) {
    // 1byte
    // U+000000 <= chr <= U+0007F
    // 0x00/0o000 <= chr <= 0x7f0o177
    codeString.push_back((char)charCodeUtf32);
  }
  if (parseDigitStrLen != unicodePointDigitStrStrLen) {
    postString.append(unicodePointDigitStr_.substr(
        parseDigitStrLen, unicodePointDigitStrStrLen - parseDigitStrLen));
  }
  return std::forward_as_tuple(codeString, charCodeUtf32, postString, false);
};

size_t SyntaxAnalyzer::scanningIdentifier(const size_t pos_) {
  size_t skipTokenCount = 0;
  Tokens *tokens = lexicalAnalyzer->getTokens();
  Token tokenId = tokens->get(pos_);
  std::string identifier = tokenId.getToken();
  if (identifier == "pkgdef") {
    skipTokenCount = scanningPackageDef(pos_);
  } else if (identifier == "moddef") {
    skipTokenCount = scanningModuleDef(pos_);
  } else if (identifier == "fmain") {
    skipTokenCount = scanningDeclareFmain(pos_);
  } else {
    skipTokenCount++;
  }
  return skipTokenCount;
};
