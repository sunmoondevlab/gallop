// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_TOKEN_
#define _COMPILER_MODEL_TOKEN_

#include "compiler/model/location.hpp"
#include "compiler/model/pre_parse_value.hpp"
#include "compiler/model/token_type.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {

class Token {
public:
  Token();
  Token(const Location &location);
  Token(const Location &location, const TokenTypeEnum &tokenType,
        const std::u32string &token);
  Token(const Location &location, const TokenTypeEnum &tokenType,
        const std::u32string &token, const int32_t &escapeCharCode);
  ~Token() {};
  Token(const Token &rhs);
  Token &operator=(const Token &rhs);
  Location getLocation() const;
  std::string getTokenTypeString() const;
  TokenTypeEnum getTokenType() const;
  std::u32string getToken() const;
  size_t getTokenLen() const;
  std::string getTokenU8() const;
  size_t getTokenLenU8() const;
  size_t countLineBreakInToken(size_t &column);
  int32_t *preParseEscapeUtf32CharCode();

private:
  Location location;
  TokenTypeEnum tokenType;
  std::u32string token;
  size_t tokenSize;
  PreParseValue preParseValue;
};

} // namespace Compiler
} // namespace gallop
#endif