#include "cli/translate_args.hpp"
#include "compiler/parser/option.hpp"

using namespace gallop::Cli;
using namespace gallop::Compiler;

Args::Args()
    : emitTokens(false), emitAst(false), emitLlvmIr(false), verboseEmit(false),
      parserOption(Parser::Option()), llvmOption(LLVM::Option()),
      args(std::vector<std::string>()) {};
Args::Args(const Args &rhs)
    : emitTokens(rhs.emitTokens), emitAst(rhs.emitAst),
      emitLlvmIr(rhs.emitLlvmIr), verboseEmit(rhs.verboseEmit),
      parserOption(rhs.parserOption), llvmOption(rhs.llvmOption),
      args(rhs.args) {};
Args &Args::operator=(const Args &rhs) {
  emitTokens = rhs.emitTokens;
  emitAst = rhs.emitAst;
  emitLlvmIr = rhs.emitLlvmIr;
  verboseEmit = rhs.verboseEmit;
  parserOption = rhs.parserOption;
  llvmOption=rhs.llvmOption;
  args = rhs.args;
  return *this;
};
bool Args::isEmitTokens() const { return emitTokens; };
bool Args::isEmitAst() const { return emitAst; };
bool Args::isEmitLlvmIr() const { return emitLlvmIr; };
bool Args::isVerboseEmit() const { return verboseEmit; };
Parser::Option Args::getParserOption() const { return parserOption; };
LLVM::Option Args::getLlvmOption() const { return llvmOption; };

std::vector<std::string> Args::getArgs() const { return args; };
void Args::setEmitTokens(const bool emitTokens_) { emitTokens = emitTokens_; };
void Args::setEmitAst(const bool emitAst_) { emitAst = emitAst_; };
void Args::setEmitLlvmIr(const bool emitLlvmIr_) { emitLlvmIr = emitLlvmIr_; };
void Args::setVerboseEmit(const bool verboseEmit_) {
  verboseEmit = verboseEmit_;
};
void Args::addArgs(const std::string arg_) { args.push_back(arg_); };
void Args::setWithCommentOutAll(const bool withCommentOutAll_) {
  parserOption.setWithCommentOutAll(withCommentOutAll_);
};
void Args::setWithCommentOutForDoc(const bool withCommentOutForDoc_) {
  parserOption.setWithCommentOutForDoc(withCommentOutForDoc_);
};
  void Args::setEntryPointId(const std::string entryPointId_) {
    llvmOption.setEntryPointId(entryPointId_);
  };

Args TranslateArgs::translateArgs(int argc, char **argv) {
  Args args = Args();
  for (int i = 1; i < argc; i++) {
    std::string arg = *(argv + i);
    if (arg == "--emit-tokens") {
      args.setEmitTokens(true);
    } else if (arg == "--emit-ast") {
      args.setEmitAst(true);
    } else if (arg == "--emit-llvm-ir") {
      args.setEmitLlvmIr(true);
    } else if (arg == "--verbose-emit") {
      args.setVerboseEmit(true);
    } else if (arg == "--with-commentout-all") {
      args.setWithCommentOutAll(true);
    } else if (arg == "--with-commentout-for-doc") {
      args.setWithCommentOutForDoc(true);
    } else {
      args.addArgs(arg);
    }
  }
  return args;
};
