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

Location Token::getLocation() const { return location; };
TokenTypeEnum Token::getTokenType() const { return tokenType; };
std::string Token::getTokenTypeString() const {
  return TokenType::getString(tokenType);
};

std::string Token::getToken() const { return token; };
size_t Token::getTokenLen() const { return tokenLen; };
void Token::setTokenVal(const enum TokenTypeEnum tokenType_,
                        const std::string &tokenStr_) {
  tokenType = tokenType_;
  token = tokenStr_;
  tokenLen = token.length();
};

size_t Token::countNewLineInToken(size_t *column_) {
  const char *tokenPtr = token.c_str();
  char chr0 = 0, chr1 = 0;
  size_t newLineCnt = 0;
  size_t pos = 0;
  for (pos = 0, chr0 = *(tokenPtr + pos); chr0 != '\0';
       pos++, chr0 = *(tokenPtr + pos), (*column_)++) {
    if (chr0 == '\r') {
      chr1 = *(tokenPtr + pos + 1);
      newLineCnt++;
      *column_ = 0;
      if (chr1 == '\n') {
        pos++;
      }
    } else if (chr0 == '\n') {
      *column_ = 0;
      newLineCnt++;
    }
  }
  return newLineCnt;
};

Tokens::Tokens() : tokenCnt{0}, tokens(std::vector<Token *>()) {};
Tokens::Tokens(const Tokens &rhs)
    : tokenCnt(rhs.tokenCnt), tokens(rhs.tokens) {};
Tokens &Tokens::operator=(const Tokens &rhs) {
  tokenCnt = rhs.tokenCnt;
  tokens = rhs.tokens;
  return *this;
};

void Tokens::push(const Tokens &rhs) {
  for (size_t i = 0; i < rhs.tokenCnt; i++) {
    Token *token =
        new Token(rhs.tokens[i]->getLocation(), rhs.tokens[i]->getTokenType(),
                  rhs.tokens[i]->getToken());
    push(token);
  }
};

void Tokens::push(Token *const token_) {
  tokens.push_back((Token *)token_);
  tokenCnt++;
};

void Tokens::popDelete() {
  if (tokenCnt == 0) {
    return;
  }
  tokens.pop_back();
  tokenCnt--;
  return;
}

void Tokens::popDeleteFromPos(const size_t pos_) {
  if (pos_ + 1 > tokenCnt) {
    return;
  }
  size_t popCnt = tokenCnt - pos_;
  for (size_t i = 0; i < popCnt; i++) {
    tokens.pop_back();
    tokenCnt--;
  }
  return;
}

Token Tokens::get(const size_t pos_) const {
  if (pos_ >= 0 && pos_ < tokenCnt) {
    return *(tokens[pos_]);
  }
  return {};
};

size_t Tokens::getTokenCnt() const { return tokenCnt; };
TokenTypeEnum Tokens::getLastTokenType() const {
  if (tokenCnt == 0) {
    return TokenTypeEnum::unknown;
  }
  return (tokens[tokenCnt - 1])->getTokenType();
};

void Tokens::printTokens(const bool isVerbose_) {
  llvm::outs() << "[\n";
  for (size_t i = 0; i < tokenCnt; i++) {
    TokenTypeEnum tokenType = tokens[i]->getTokenType();
    llvm::outs() << "  " << tokens[i]->getTokenTypeString();
    if ((uint32_t(tokenType) >> 24) != 4) {
      llvm::outs() << ": " << tokens[i]->getToken() << " ";
    }
    if (isVerbose_) {
      Location loc = tokens[i]->getLocation();
      llvm::outs() << ", location::[" << loc.getLine() << "," << loc.getColumn()
                   << "],\n";
    } else {
      llvm::outs() << ",\n";
    }
  }
  llvm::outs() << "]\n";
}
