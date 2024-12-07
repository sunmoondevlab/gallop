#ifndef _CLI_COMPILER_FILE_
#define _CLI_COMPILER_FILE_
#include "cli/translate_args.hpp"
#include <iostream>

namespace gallop {
namespace Cli {
class CompilerFromFile {
public:
  void execute(Args args);
};
} // namespace Cli
} // namespace gallop

#endif