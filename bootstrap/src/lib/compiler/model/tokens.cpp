// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/tokens.hpp"

#include "compiler/model/location.hpp"
#include "compiler/model/token_type.hpp"

using namespace gallop::Compiler;

Tokens::Tokens() : tokens(std::vector<Token *>()), tokenCount(0) {};
Tokens::Tokens(const Tokens &rhs)
    : tokens(rhs.tokens), tokenCount(rhs.tokenCount) {};

Tokens &Tokens::operator=(const Tokens &rhs) {
  tokens = rhs.tokens;
  tokenCount = rhs.tokenCount;
  return *this;
};
void Tokens::push(Token *const token_) {
  tokens.push_back((Token *)token_);
  tokenCount++;
};
void Tokens::deleteLast() {
  if (tokenCount == 0) {
    return;
  }
  Token *token = tokens.back();
  delete token;
  tokens.pop_back();
  tokenCount--;
  return;
};
void Tokens::deleteLast(const size_t &deleteCount_) {
  if (deleteCount_ == 0) {
    return;
  }
  if (tokenCount == 0) {
    return;
  }
  size_t afterTokenCnt = 0;
  Token **tokensPtr = tokens.data();
  if (deleteCount_ < tokenCount) {
    afterTokenCnt = tokenCount - deleteCount_;
  }
  for (size_t i = afterTokenCnt; i < tokenCount; i++) {
    Token *token = *(tokensPtr + i);
    delete token;
  }
  tokens.erase(tokens.begin() + afterTokenCnt, tokens.end());
  tokenCount = afterTokenCnt;
  return;
};
void Tokens::resetTokens() {
  if (tokenCount == 0) {
    return;
  }
  Token **tokensPtr = tokens.data();
  for (size_t i = 0; i < tokenCount; i++) {
    Token *token = *(tokensPtr + i);
    delete token;
  }
  tokens.erase(tokens.begin(), tokens.end());
  tokenCount = 0;
  return;
};
;
std::vector<Token *> Tokens::getTokens() const { return tokens; };
size_t Tokens::getTokenCount() const { return tokenCount; };
