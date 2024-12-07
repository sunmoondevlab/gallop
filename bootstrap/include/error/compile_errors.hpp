// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _ERROR_COMPILE_ERRORS_
#define _ERROR_COMPILE_ERRORS_

#include "compiler/model/token.hpp"

#include <cstdint>
#include <exception>
#include <string>

using namespace gallop::Compiler;

namespace gallop {
namespace Error {

class TokenizeError : public std::exception {
public:
  TokenizeError(const Token &token, const std::string &srcLineStr);
  ~TokenizeError() {};
  TokenizeError(const TokenizeError &rhs);
  TokenizeError &operator=(const TokenizeError &rhs);
  char const *what() const noexcept override { return message.c_str(); };

private:
  Token &token;
  std::string &srcLineStr;
  std::string message;
  void initializeMessage();
};

} // namespace Error
} // namespace gallop
#endif