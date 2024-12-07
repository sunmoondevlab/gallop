// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "cli/translate_args.hpp"

#include "io/file/file.hpp"
#include "util/argsconv/args_converter.hpp"

using namespace gallop::Cli;
using namespace gallop::Compiler;
using namespace gallop::IO;

Args::Args()
    : dumpTokens(false), dumpAst(false), dumpLlvmIr(false), verboseDump(false),
      emitLlvmIr(false), parserOption(Option::Parser()),
      llvmOption(Option::LLVM()), args(std::vector<std::string>()) {};
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
Option::Parser Args::getParserOption() const { return parserOption; };
Option::LLVM Args::getLlvmOption() const { return llvmOption; };
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
void Args::setDstRootDir(const std::string &dstRootDir_) {
  llvmOption.setDstRootDir(dstRootDir_);
};

Args TranslateArgs::translateArgs(int32_t argc, char **argv) {
  Args args = Args();
  for (int32_t i = 1; i < argc; i++) {
    std::string arg(*(argv + i));
    if (std::string_view(arg) == optionDumpTokens) {
      args.setDumpTokens();
    } else if (std::string_view(arg) == optionDumpAst) {
      args.setDumpAst();
    } else if (std::string_view(arg) == optionDumpLlvmIr) {
      args.setDumpLlvmIr();
    } else if (std::string_view(arg) == optionVerboseDump) {
      args.setVerboseDump();
    } else if (std::string_view(arg) == optionEmitLlvmIr) {
      args.setEmitLlvmIr();
    } else if (std::string_view(arg) == optionWithCommentOutAll) {
      args.setWithCommentOutAll();
    } else if (std::string_view(arg) == optionWithCommentOutForDoc) {
      args.setWithCommentOutForDoc();
    } else if (std::string_view(arg) == optionEntryPointId) {
      if (i + 1 < argc) {
        // TODO: will be refactering
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
    } else if (std::string_view(arg) == optionSrcRootDir) {
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
    } else if (std::string_view(arg) == optionDstRootDir) {
      if (i + 1 < argc) {
        std::string dstRootDir = *(argv + i + 1);
        if (dstRootDir[0] == '-') {
          continue;
        }
        dstRootDir = File::absoluteCanonicalPath(dstRootDir);
        args.setDstRootDir(dstRootDir);
        File::mkdir(dstRootDir);
        i++;
      }
    } else {
      args.addArgs(arg);
    }
  }
  return args;
};
