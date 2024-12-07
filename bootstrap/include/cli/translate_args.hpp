// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CLI_TRANSLATE_ARGS_
#define _CLI_TRANSLATE_ARGS_
#include "compiler/llvm/option.hpp"
#include "compiler/parser/option.hpp"
#include <cstdint>
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
  bool isDumpTokens() const;
  bool isDumpAst() const;
  bool isDumpLlvmIr() const;
  bool isVerboseDump() const;
  bool isEmitLlvmIr() const;
  std::vector<std::string> getArgs() const;
  Parser::Option getParserOption() const;
  LLVM::Option getLlvmOption() const;
  void addArgs(const std::string &arg);
  void setDumpTokens();
  void setDumpAst();
  void setDumpLlvmIr();
  void setVerboseDump();
  void setEmitLlvmIr();
  void setWithCommentOutAll();
  void setWithCommentOutForDoc();
  void setEntryPointId(const std::string &entryPointId);
  void setSrcRootDir(const std::string &srcRootDir);
  void setDestRootDir(const std::string &destRootDir);

private:
  bool dumpTokens;
  bool dumpAst;
  bool dumpLlvmIr;
  bool verboseDump;
  bool emitLlvmIr;
  Parser::Option parserOption;
  LLVM::Option llvmOption;
  std::vector<std::string> args;
};

class TranslateArgs {
public:
  TranslateArgs() = delete;
  ~TranslateArgs() = delete;
  static Args translateArgs(int32_t argc, char **argv);
};

} // namespace Cli
} // namespace gallop
#endif