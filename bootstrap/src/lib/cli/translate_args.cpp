// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "cli/translate_args.hpp"
#include "compiler/parser/option.hpp"
#include "io/file/file.hpp"

using namespace gallop::Cli;
using namespace gallop::Compiler;
using namespace gallop::IO;

Args::Args()
    : dumpTokens(false), dumpAst(false), dumpLlvmIr(false), verboseDump(false),
      emitLlvmIr(false), parserOption(Parser::Option()),
      llvmOption(LLVM::Option()), args(std::vector<std::string>()) {};
Args::Args(const Args &rhs)
    : dumpTokens(rhs.dumpTokens), dumpAst(rhs.dumpAst),
      dumpLlvmIr(rhs.dumpLlvmIr), verboseDump(rhs.verboseDump),
      emitLlvmIr(rhs.emitLlvmIr), parserOption(rhs.parserOption),
      llvmOption(rhs.llvmOption), args(rhs.args) {};
Args &Args::operator=(const Args &rhs) {
  dumpTokens = rhs.dumpTokens;
  dumpAst = rhs.dumpAst;
  dumpLlvmIr = rhs.dumpLlvmIr;
  verboseDump = rhs.verboseDump;
  emitLlvmIr = rhs.emitLlvmIr;
  parserOption = rhs.parserOption;
  llvmOption = rhs.llvmOption;
  args = rhs.args;
  return *this;
};
bool Args::isDumpTokens() const { return dumpTokens; };
bool Args::isDumpAst() const { return dumpAst; };
bool Args::isDumpLlvmIr() const { return dumpLlvmIr; };
bool Args::isVerboseDump() const { return verboseDump; };
bool Args::isEmitLlvmIr() const { return emitLlvmIr; };
Parser::Option Args::getParserOption() const { return parserOption; };
LLVM::Option Args::getLlvmOption() const { return llvmOption; };

std::vector<std::string> Args::getArgs() const { return args; };
void Args::addArgs(const std::string &arg_) { args.push_back(arg_); };
void Args::setDumpTokens() { dumpTokens = true; };
void Args::setDumpAst() { dumpAst = true; };
void Args::setDumpLlvmIr() { dumpLlvmIr = true; };
void Args::setVerboseDump() { verboseDump = true; };
void Args::setEmitLlvmIr() { emitLlvmIr = true; };
void Args::setWithCommentOutAll() { parserOption.setWithCommentOutAll(); };
void Args::setWithCommentOutForDoc() {
  parserOption.setWithCommentOutForDoc();
};
void Args::setEntryPointId(const std::string &entryPointId_) {
  llvmOption.setEntryPointId(entryPointId_);
};
void Args::setSrcRootDir(const std::string &srcRootDir_) {
  llvmOption.setSrcRootDir(srcRootDir_);
};
void Args::setDestRootDir(const std::string &destRootDir_) {
  llvmOption.setDestRootDir(destRootDir_);
};

Args TranslateArgs::translateArgs(int32_t argc, char **argv) {
  Args args = Args();
  for (int32_t i = 1; i < argc; i++) {
    std::string arg(*(argv + i));
    if (arg == "--dump-tokens") {
      args.setDumpTokens();
    } else if (arg == "--dump-ast") {
      args.setDumpAst();
    } else if (arg == "--dump-llvm-ir") {
      args.setDumpLlvmIr();
    } else if (arg == "--verbose-dump") {
      args.setVerboseDump();
    } else if (arg == "--emit-llvm-ir") {
      args.setEmitLlvmIr();
    } else if (arg == "--with-commentout-all") {
      args.setWithCommentOutAll();
    } else if (arg == "--with-commentout-for-doc") {
      args.setWithCommentOutForDoc();
    } else if (arg == "--entry-point-id") {
      if (i + 1 < argc) {
        // TODO will be refactering
        std::string entryPointId = std::string(*(argv + i + 1));
        size_t j = 0;
        size_t epIdLen = entryPointId.size();
        bool isEpIdHexDecDigitStart = false;
        bool hasEpIdNonHexDecDigit = false;
        for (; j < epIdLen; j++) {
          if (!(('0' <= entryPointId[j] && entryPointId[j] <= '9') ||
                ('A' <= entryPointId[j] && entryPointId[j] <= 'Z') ||
                ('a' <= entryPointId[j] && entryPointId[j] <= 'z') ||
                '.' == entryPointId[j] || '_' == entryPointId[j])) {
            break;
          }
          if (('0' <= entryPointId[j] && entryPointId[j] <= '9') ||
              ('A' <= entryPointId[j] && entryPointId[j] <= 'F') ||
              ('a' <= entryPointId[j] && entryPointId[j] <= 'f')) {
            if (j == 0) {
              isEpIdHexDecDigitStart = true;
            }
          } else {
            hasEpIdNonHexDecDigit = true;
          }
        }
        if (j == epIdLen) {
          args.setEntryPointId(entryPointId);
          i++;
          continue;
        }
      }
    } else if (arg == "--src-root-dir") {
      if (i + 1 < argc) {
        std::string srcRootDir = *(argv + i + 1);
        if (srcRootDir[0] == '-') {
          continue;
        }
        if (File::isDirectory(srcRootDir)) {
          args.setSrcRootDir(File::absoluteCanonicalPath(srcRootDir));
          i++;
          continue;
        }
      }
    } else if (arg == "--dest-root-dir") {
      if (i + 1 < argc) {
        std::string destRootDir = *(argv + i + 1);
        if (destRootDir[0] == '-') {
          continue;
        }
        destRootDir = File::absoluteCanonicalPath(destRootDir);
        args.setDestRootDir(destRootDir);
        File::mkdir(destRootDir);
        i++;
      }
    } else {
      args.addArgs(arg);
    }
  }
  return args;
};
