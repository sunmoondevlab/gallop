// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_TOKENS_INPUT_STREAM_
#define _COMPILER_MODEL_TOKENS_INPUT_STREAM_

#include "compiler/model/tokens.hpp"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {

class TokensInputStream {
public:
  TokensInputStream(const Tokens &tokens);
  ~TokensInputStream() {};
  TokensInputStream(const TokensInputStream &rhs);
  TokensInputStream &operator=(const TokensInputStream &rhs);
  std::vector<Token *> data();
  Token *current();
  Token *read();
  Token *undo();
  Token *ahead();
  Token *ahead(const size_t &offset);
  Token *tail();
  Token *tail(const size_t &backOffset);
  void skip();
  void skip(const size_t &skipSize);
  void markCurrent();
  void markAt(const size_t &markPos);
  void resetMark();
  void rewind();
  void rewind(const size_t &rewindSize);
  void rewindToMark();
  bool hasReadable() const;
  int64_t readable() const;
  size_t size() const;
  TokenTypeEnum tailTokenType();
  TokenTypeEnum tailTokenType(const size_t &backOffset);
  std::string toStringPrintTokens();
  std::string toStringPrintTokens(const bool &isVerbose);
  void printTokens();
  void printTokens(const bool &isVerbose);

private:
  Tokens &tokens;
  size_t pos;
  size_t mark;
};

} // namespace Compiler
} // namespace gallop
#endif