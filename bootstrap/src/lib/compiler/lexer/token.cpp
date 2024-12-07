// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
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
  size_t newLineCount = 0;
  size_t pos = 0;
  for (pos = 0, chr0 = *(tokenPtr + pos); chr0 != '\0';
       pos++, chr0 = *(tokenPtr + pos), (*column_)++) {
    if (chr0 == '\r') {
      chr1 = *(tokenPtr + pos + 1);
      newLineCount++;
      *column_ = 0;
      if (chr1 == '\n') {
        pos++;
      }
    } else if (chr0 == '\n') {
      *column_ = 0;
      newLineCount++;
    }
  }
  return newLineCount;
};

Tokens::Tokens()
    : tokenCount{0}, parsableTokenCount(0), tokens(std::vector<Token *>()) {};
Tokens::Tokens(const Tokens &rhs)
    : tokenCount(rhs.tokenCount), parsableTokenCount(rhs.parsableTokenCount),
      tokens(rhs.tokens) {};
Tokens &Tokens::operator=(const Tokens &rhs) {
  tokenCount = rhs.tokenCount;
  parsableTokenCount = rhs.parsableTokenCount;
  tokens = rhs.tokens;
  return *this;
};
void Tokens::push(Token *const token_, const bool isContinueAnalyze_) {
  tokens.push_back((Token *)token_);
  tokenCount++;
  if (!isContinueAnalyze_) {
    parsableTokenCount = tokenCount;
  }
};

void Tokens::popDelete() {
  if (tokenCount == 0) {
    return;
  }
  tokens.pop_back();
  tokenCount--;
  return;
};

void Tokens::popDeleteFromPos(const size_t pos_) {
  if (pos_ + 1 > tokenCount) {
    return;
  }
  size_t popCount = tokenCount - pos_;
  for (size_t i = 0; i < popCount; i++) {
    tokens.pop_back();
    tokenCount--;
  }
  return;
};

Token Tokens::get(const size_t pos_) const {
  if (pos_ >= 0 && pos_ < parsableTokenCount) {
    return *(tokens[pos_]);
  }
  return {};
};

size_t Tokens::getTokenCount() const { return tokenCount; };
size_t Tokens::getParsableTokenCount() const { return parsableTokenCount; };
TokenTypeEnum Tokens::getLastTokenType(const ssize_t pos_) const {
  ssize_t pos = pos_;
  if (parsableTokenCount == 0) {
    return TokenTypeEnum::unknown;
  }
  if (pos > 0) {
    pos = 0;
  }
  if ((ssize_t)(parsableTokenCount - 1 + pos) < 0) {
    pos = -(parsableTokenCount - 1);
  }
  ssize_t lastPos = parsableTokenCount + pos - 1;
  return (tokens[parsableTokenCount - lastPos])->getTokenType();
};
TokenTypeEnum Tokens::getLastTokenType() const {
  if (parsableTokenCount == 0) {
    return TokenTypeEnum::unknown;
  }
  return (tokens[parsableTokenCount - 1])->getTokenType();
};

void Tokens::printTokens(const bool isVerbose_) {
  llvm::outs() << "[\n";
  for (size_t i = 0; i < parsableTokenCount; i++) {
    TokenTypeEnum tokenType = tokens[i]->getTokenType();
    llvm::outs() << "  " << tokens[i]->getTokenTypeString();
    if (!TokenType::isSymbolCharacterToken(tokenType)) {
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
};
