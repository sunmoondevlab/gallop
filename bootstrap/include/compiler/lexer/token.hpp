// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_LEXER_TOKEN_
#define _COMPILER_LEXER_TOKEN_
#include "compiler/lexer/token_type.hpp"
#include "compiler/model/location.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Lexer {

class Token {
public:
  Token();
  Token(const Location location);
  Token(const Location location, const TokenTypeEnum tokenType,
        const std::string token);
  ~Token() {};
  Token(const Token &rhs);
  Token &operator=(const Token &rhs);
  Location getLocation() const;
  std::string getTokenTypeString() const;
  TokenTypeEnum getTokenType() const;
  std::string getToken() const;
  size_t getTokenLen() const;
  void setTokenVal(const enum TokenTypeEnum tokenType,
                   const std::string &tokenStr);
  size_t countNewLineInToken(size_t *column);

private:
  Location location;
  TokenTypeEnum tokenType;
  std::string token;
  size_t tokenLen;
};

class Tokens {
public:
  Tokens();
  ~Tokens() {};
  Tokens(const Tokens &rhs);
  Tokens &operator=(const Tokens &rhs);
  void push(Token *const token, const bool isContinueAnalyze);
  void popDelete();
  void popDeleteFromPos(const size_t pos);
  Token get(const size_t pos) const;
  size_t getTokenCount() const;
  size_t getParsableTokenCount() const;
  TokenTypeEnum getLastTokenType(const ssize_t pos) const;
  TokenTypeEnum getLastTokenType() const;
  void printTokens(const bool isVerbose);

private:
  size_t tokenCount;
  size_t parsableTokenCount;
  std::vector<Token *> tokens;
};

} // namespace Lexer
} // namespace Compiler
} // namespace gallop
#endif