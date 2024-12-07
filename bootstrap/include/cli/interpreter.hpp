// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CLI_INTERPRETER_
#define _CLI_INTERPRETER_
#include "cli/translate_args.hpp"
#include <iostream>

namespace gallop {
namespace Cli {
class Interpreter {
public:
  void execute(Args args);
};
} // namespace Cli
} // namespace gallop
#endif
