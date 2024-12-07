#include "main/main.hpp"
#include "cli/compiler_from_file.hpp"
#include "cli/compiler_from_stdin.hpp"
#include "cli/interpreter.hpp"
#include "cli/translate_args.hpp"

namespace gallop {
namespace Main {
int main(int argc, char **argv) {
  Cli::Args args = Cli::TranslateArgs::translateArgs(argc, argv);
  bool stdinTtyFlag = isatty(fileno(stdin)) > 0;
  if (stdinTtyFlag && args.getArgs().size() == 0) {
    Cli::Interpreter i;
    i.execute(args);
  } else if (stdinTtyFlag) {
    Cli::CompilerFromFile cf;
    cf.execute(args);
  } else {
    Cli::CompilerFromStdin cs;
    cs.execute(args);
  }
  return 0;
};
} // namespace Main
} // namespace gallop