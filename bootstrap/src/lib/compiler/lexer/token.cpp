#include "compiler/lexer/token.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;

Token::Token()
    : location(Location(0, 0)), tokenType(TokenTypeEnum::unknown), token(""),
      tokenLen(0) {};
Token::Token(const Location location_)
    : location(location_), tokenType(TokenTypeEnum::unknown), token(""),
      tokenLen(0) {};
Token::Token(const Location location_, const TokenTypeEnum tokenType_,
             const std::string token_)
    : location(location_), tokenType(tokenType_), token(token_),
      tokenLen(token_.length()) {};
Token::Token(const Token &rhs)
    : location(rhs.location), tokenType(rhs.tokenType), token(rhs.token),
      tokenLen(rhs.tokenLen) {};
Token &Token::operator=(const Token &rhs) {
  location = rhs.location;
  tokenType = rhs.tokenType;
  token = std::string(rhs.token.begin(), rhs.token.end());
  tokenLen = rhs.tokenLen;
  return *this;
};

Location Token::getLocation() { return location; };
TokenTypeEnum Token::getTokenType() { return tokenType; };
std::string Token::getTokenTypeString() {
  return TokenType::getString(tokenType);
};

std::string Token::getToken() { return token; };
size_t Token::getTokenLen() { return tokenLen; };
void Token::setTokenVal(const enum TokenTypeEnum tokenType_,
                        const std::string &tokenStr_) {
  tokenType = tokenType_;
  token = tokenStr_;
  tokenLen = token.length();
};

size_t Token::countNewLineInToken(size_t *colLoc_) {
  const char *tokenPtr = token.c_str();
  char chr0 = 0, chr1 = 0;
  size_t newLineCnt = 0;
  size_t pos = 0;
  for (pos = 0, chr0 = *(tokenPtr + pos); chr0 != '\0';
       pos++, chr0 = *(tokenPtr + pos), (*colLoc_)++) {
    if (chr0 == '\r') {
      chr1 = *(tokenPtr + pos + 1);
      newLineCnt++;
      *colLoc_ = 0;
      if (chr1 == '\n') {
        pos++;
      }
    } else if (chr0 == '\n') {
      *colLoc_ = 0;
      newLineCnt++;
    }
  }
  return newLineCnt;
};

Tokens::Tokens() : tokenCnt{0}, tokenPtrs(std::vector<Token *>()) {};
Tokens::Tokens(const Tokens &rhs)
    : tokenCnt(rhs.tokenCnt), tokenPtrs(rhs.tokenPtrs) {};
Tokens &Tokens::operator=(const Tokens &rhs) {
  tokenCnt = rhs.tokenCnt;
  tokenPtrs = rhs.tokenPtrs;
  return *this;
};

void Tokens::push(const Tokens &rhs) {
  for (size_t i = 0; i < rhs.tokenCnt; i++) {
    Token *token = new Token(rhs.tokenPtrs[i]->getLocation(),
                             rhs.tokenPtrs[i]->getTokenType(),
                             rhs.tokenPtrs[i]->getToken());
    push(token);
  }
};

void Tokens::push(Token *const token_) {
  tokenPtrs.push_back((Token *)token_);
  tokenCnt++;
};

void Tokens::popDelete() {
  if (tokenCnt == 0) {
    return;
  }
  tokenPtrs.pop_back();
  tokenCnt--;
  return;
}

void Tokens::popDeleteFromPos(const size_t pos) {
  if (pos + 1 > tokenCnt) {
    return;
  }
  size_t popCnt = tokenCnt - pos;
  for (size_t i = 0; i < popCnt; i++) {
    tokenPtrs.pop_back();
    tokenCnt--;
  }
  return;
}

Token Tokens::get(const size_t pos) {
  if (pos >= 0 && pos < tokenCnt) {
    return *(tokenPtrs[pos]);
  }
  return {};
};

size_t Tokens::getTokenCnt() { return tokenCnt; };
TokenTypeEnum Tokens::getLastTokenType() {
  if (tokenCnt == 0) {
    return TokenTypeEnum::unknown;
  }
  return (tokenPtrs[tokenCnt - 1])->getTokenType();
};

void Tokens::printTokens(const bool isVerbose) {
  llvm::outs() << "[\n";
  for (size_t i = 0; i < tokenCnt; i++) {
    TokenTypeEnum tokenType = tokenPtrs[i]->getTokenType();
    llvm::outs() << "  " << tokenPtrs[i]->getTokenTypeString();
    if ((int(tokenType) >> 24) != 0x4) {
      llvm::outs() << ": " << tokenPtrs[i]->getToken() << " ";
    }
    if (isVerbose) {
      Location loc = tokenPtrs[i]->getLocation();
      llvm::outs() << ", location::[" << loc.getLineLoc() << ","
                   << loc.getColLoc() << "],\n";
    } else {
      llvm::outs() << ",\n";
    }
  }
  llvm::outs() << "]\n";
}
