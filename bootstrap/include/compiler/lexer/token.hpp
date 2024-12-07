#ifndef _COMPILER_LEXER_TOKEN_
#define _COMPILER_LEXER_TOKEN_
#include "compiler/common/location.hpp"
#include "compiler/lexer/token_type.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Lexer {

class Token {
public:
  Token();
  Token(const Location location_);
  Token(const Location location_, const TokenTypeEnum tokenType_,
        const std::string token_);
  ~Token() {};
  Token(const Token &rhs);
  Token &operator=(const Token &rhs);
  Location getLocation();
  std::string getTokenTypeString();
  TokenTypeEnum getTokenType();
  std::string getToken();
  size_t getTokenLen();
  void setTokenVal(const enum TokenTypeEnum tokenType_,
                   const std::string &tokenStr_);
  size_t countNewLineInToken(size_t *colLoc_);

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
  void push(const Tokens &rhs);
  void push(Token *const token_);
  void popDelete();
  void popDeleteFromPos(const size_t pos);
  Token get(const size_t pos);
  size_t getTokenCnt();
  TokenTypeEnum getLastTokenType();
  void printTokens(const bool isVerbose);

private:
  size_t tokenCnt;
  std::vector<Token *> tokenPtrs;
};

} // namespace Lexer
} // namespace Compiler
} // namespace gallop
#endif