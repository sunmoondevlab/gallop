#include "cli/translate_args.hpp"

using namespace gallop::Cli;

Args::Args()
    : emitTokens(false), emitAst(false), emitLlvmIr(false), verboseEmit(false),
      args(std::vector<std::string>()) {};
Args::Args(const Args &rhs)
    : emitTokens(rhs.emitTokens), emitAst(rhs.emitAst),
      emitLlvmIr(rhs.emitLlvmIr), verboseEmit(rhs.verboseEmit),
      args(rhs.args) {};
Args &Args::operator=(const Args &rhs) {
  emitTokens = rhs.emitTokens;
  emitAst = rhs.emitAst;
  emitLlvmIr = rhs.emitLlvmIr;
  verboseEmit = rhs.verboseEmit;
  args = rhs.args;
  return *this;
};
bool Args::isEmitTokens() { return emitTokens; };
bool Args::isEmitAst() { return emitAst; };
bool Args::isEmitLlvmIr() { return emitLlvmIr; };
bool Args::isVerboseEmit() { return verboseEmit; };
std::vector<std::string> Args::getArgs() { return args; };
void Args::setEmitTokens(const bool emitTokens_) { emitTokens = emitTokens_; };
void Args::setEmitAst(const bool emitAst_) { emitAst = emitAst_; };
void Args::setEmitLlvmIr(const bool emitLlvmIr_) { emitLlvmIr = emitLlvmIr_; };
void Args::setVerboseEmit(const bool verboseEmit_) {
  verboseEmit = verboseEmit_;
};
void Args::addArgs(const std::string arg) { args.push_back(arg); };

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
    } else {
      args.addArgs(arg);
    }
  }
  return args;
};
