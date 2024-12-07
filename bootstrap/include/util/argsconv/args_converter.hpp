// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _UTIL_ARGSCONV_ARGS_CONVERTER_
#define _UTIL_ARGSCONV_ARGS_CONVERTER_

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

namespace gallop {
namespace Util {
class ArgsConverter {
public:
  ArgsConverter() = delete;
  ~ArgsConverter() = delete;
  static std::vector<char *> convertArgs(const std::vector<std::string> &args);
};
} // namespace Util
} // namespace gallop
#endif