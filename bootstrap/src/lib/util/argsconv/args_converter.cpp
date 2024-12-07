// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "util/argsconv/args_converter.hpp"

using namespace gallop::Util;

std::vector<char *>
ArgsConverter::convertArgs(const std::vector<std::string> &args) {
  size_t argc = args.size();
  std::vector<char *> argv;
  if (argc > 0) {
    const std::string *argsPtr = args.data();
    for (size_t pos = 0; pos < argc; pos++) {
      argv.push_back(const_cast<char *>((argsPtr + pos)->c_str()));
    }
  }
  return argv;
};