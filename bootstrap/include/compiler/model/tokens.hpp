// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_TOKENS_
#define _COMPILER_MODEL_TOKENS_

#include "compiler/model/token.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {

class Tokens {
public:
  Tokens();
  ~Tokens() {};
  Tokens(const Tokens &rhs);
  Tokens &operator=(const Tokens &rhs);
  void push(Token *const token);
  void deleteLast();
  void deleteLast(const size_t &deleteCount);
  void resetTokens();
  std::vector<Token *> getTokens() const;
  size_t getTokenCount() const;

private:
  std::vector<Token *> tokens;
  size_t tokenCount;
};

} // namespace Compiler
} // namespace gallop
#endif