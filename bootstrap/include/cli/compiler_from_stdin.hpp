#ifndef _CLI_COMPILER_STDIN_
#define _CLI_COMPILER_STDIN_
#include "cli/translate_args.hpp"
#include <iostream>

namespace gallop {
namespace Cli {
class CompilerFromStdin {
public:
  void execute(Args args);
};
} // namespace Cli
} // namespace gallop

#endif
