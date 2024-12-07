#include "main/main.hpp"
#include "cli/compiler_from_file.hpp"
#include "cli/compiler_from_stdin.hpp"
#include "cli/interpreter.hpp"
#include "cli/translate_args.hpp"

using namespace gallop::Cli;

namespace gallop::Main {

int main(int argc, char **argv) {
  Args args = TranslateArgs::translateArgs(argc, argv);
  bool stdinTtyFlag = isatty(fileno(stdin)) > 0;
  if (stdinTtyFlag && args.getArgs().size() == 0) {
    Interpreter i;
    i.execute(args);
  } else if (stdinTtyFlag) {
    CompilerFromFile cf;
    cf.execute(args);
  } else {
    CompilerFromStdin cs;
    cs.execute(args);
  }
  return 0;
};

} // namespace gallop::Main