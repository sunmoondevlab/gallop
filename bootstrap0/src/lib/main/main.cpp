#include "main/main.hpp"
#include "cli/compiler_from_file.hpp"
#include "cli/compiler_from_stdin.hpp"
#include "cli/interpreter.hpp"

namespace gallop {
namespace Main {
int main(int argc, char **argv) {
  bool stdinTtyFlag = isatty(fileno(stdin)) > 0;
  if (stdinTtyFlag) {
    Cli::Interpreter i;
    i.execute();
  } else {
    Cli::CompilerFromStdin c;
    c.execute();
  }
  return 0;
};
} // namespace Main
} // namespace gallop