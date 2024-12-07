#ifndef _CLI_TRANSLATE_ARGS_
#define _CLI_TRANSLATE_ARGS_
#include "compiler/llvm/option.hpp"
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
  bool isEmitTokens() const;
  bool isEmitAst() const;
  bool isEmitLlvmIr() const;
  bool isVerboseEmit() const;
  std::vector<std::string> getArgs() const;
  Parser::Option getParserOption() const;
  LLVM::Option getLlvmOption() const;
  void setEmitTokens(const bool emitTokens);
  void setEmitAst(const bool emitAst);
  void setEmitLlvmIr(const bool emitLlvmIr);
  void setVerboseEmit(const bool verboseEmit);
  void addArgs(const std::string arg);
  void setWithCommentOutAll(const bool withCommentOutAll);
  void setWithCommentOutForDoc(const bool withCommentOutForDoc);
  void setEntryPointId(const std::string entryPointId);

private:
  bool emitTokens;
  bool emitAst;
  bool emitLlvmIr;
  bool verboseEmit;
  Parser::Option parserOption;
  LLVM::Option llvmOption;
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