// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _ERROR_COMMON_ERRORS_
#define _ERROR_COMMON_ERRORS_

#include <cstdint>
#include <exception>
#include <string>

namespace gallop {
namespace Error {

class InvalidArgumentError : public std::exception {
public:
  InvalidArgumentError(const std::string &message);
  ~InvalidArgumentError() {};
  InvalidArgumentError(const InvalidArgumentError &rhs);
  InvalidArgumentError &operator=(const InvalidArgumentError &rhs);
  char const *what() const noexcept override { return message.c_str(); };

private:
  std::string message;
};

class IOError : public std::exception {
public:
  IOError(const std::string &message);
  ~IOError() {};
  IOError(const IOError &rhs);
  IOError &operator=(const IOError &rhs);
  char const *what() const noexcept override { return message.c_str(); };

private:
  std::string message;
};

} // namespace Error
} // namespace gallop
#endif