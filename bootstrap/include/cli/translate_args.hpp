// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CLI_TRANSLATE_ARGS_
#define _CLI_TRANSLATE_ARGS_

#include "compiler/option/llvm.hpp"
#include "compiler/option/parser.hpp"

#include <cstdint>
#include <string>
#include <string_view>
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
  Option::Parser getParserOption() const;
  Option::LLVM getLlvmOption() const;
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
  void setDstRootDir(const std::string &dstRootDir);

private:
  bool dumpTokens;
  bool dumpAst;
  bool dumpLlvmIr;
  bool verboseDump;
  bool emitLlvmIr;
  Option::Parser parserOption;
  Option::LLVM llvmOption;
  std::vector<std::string> args;
};

class TranslateArgs {
public:
  TranslateArgs() = delete;
  ~TranslateArgs() = delete;
  static Args translateArgs(int32_t argc, char **argv);

private:
  static constexpr std::string_view optionDumpTokens = "--dump-tokens";
  static constexpr std::string_view optionDumpAst = "--dump-ast";
  static constexpr std::string_view optionDumpLlvmIr = "--dump-llvm-ir";
  static constexpr std::string_view optionVerboseDump = "--verbose-dump";
  static constexpr std::string_view optionEmitLlvmIr = "--emit-llvm-ir";
  static constexpr std::string_view optionWithCommentOutAll =
      "--with-commentout-all";
  static constexpr std::string_view optionWithCommentOutForDoc =
      "--with-commentout-for-doc";
  static constexpr std::string_view optionEntryPointId = "--entry-point-id";
  static constexpr std::string_view optionSrcRootDir = "--src-root-dir";
  static constexpr std::string_view optionDstRootDir = "--dst-root-dir";
};

} // namespace Cli
} // namespace gallop
#endif