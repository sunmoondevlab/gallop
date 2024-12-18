#ifndef _CLI_TRANSLATE_ARGS_
#define _CLI_TRANSLATE_ARGS_
#include "compiler/parser/option.hpp"
#include <string>
#include <vector>

using namespace gallop::Compiler;

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
  Parser::Option getParserOption();
  void setEmitTokens(const bool emitTokens_);
  void setEmitAst(const bool emitAst_);
  void setEmitLlvmIr(const bool emitLlvmIr_);
  void setVerboseEmit(const bool verboseEmit_);
  void addArgs(const std::string arg);
  void setWithCommentOutAll(const bool withCommentOutAll_);
  void setWithCommentOutForDoc(const bool withCommentOutForDoc_);

private:
  bool emitTokens;
  bool emitAst;
  bool emitLlvmIr;
  bool verboseEmit;
  Parser::Option parserOption;
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