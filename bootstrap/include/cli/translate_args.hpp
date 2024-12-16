#ifndef _CLI_TRANSLATE_ARGS_
#define _CLI_TRANSLATE_ARGS_
#include <string>
#include <vector>
namespace gallop {
namespace Cli {

class Args {
public:
  Args();
  ~Args() {};
  Args(const Args &rhs);
  Args &operator=(const Args &rhs);
  bool isEmitTokens();
  bool isEmitAst();
  bool isEmitLlvmIr();
  bool isVerboseEmit();
  std::vector<std::string> getArgs();
  void setEmitTokens(const bool emitTokens_);
  void setEmitAst(const bool emitAst_);
  void setEmitLlvmIr(const bool emitLlvmIr_);
  void setVerboseEmit(const bool verboseEmit_);
  void addArgs(const std::string arg);

private:
  bool emitTokens;
  bool emitAst;
  bool emitLlvmIr;
  bool verboseEmit;
  std::vector<std::string> args;
};

class TranslateArgs {
public:
  TranslateArgs() = delete;
  ~TranslateArgs() = delete;
  static Args translateArgs(int argc, char **argv);
};

} // namespace Cli
} // namespace gallop
#endif