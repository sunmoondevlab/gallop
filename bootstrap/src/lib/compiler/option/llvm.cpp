// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/option/llvm.hpp"

using namespace gallop::Compiler::Option;
using namespace gallop::IO;

LLVM::LLVM()
    : entryPointId(""), srcRootDir(File::getCurrentDir()),
      dstRootDir(File::getCurrentDir()) {};
LLVM::LLVM(const LLVM &rhs)
    : entryPointId(rhs.entryPointId), srcRootDir(rhs.srcRootDir),
      dstRootDir(rhs.dstRootDir) {};
LLVM &LLVM::operator=(const LLVM &rhs) {
  entryPointId = rhs.entryPointId;
  srcRootDir = rhs.srcRootDir;
  dstRootDir = rhs.dstRootDir;
  return *this;
};
std::string LLVM::getEntryPointId() const { return entryPointId; };
std::string LLVM::getSrcRootDir() const { return srcRootDir; };
std::string LLVM::getDstRootDir() const { return dstRootDir; };
void LLVM::setEntryPointId(const std::string entryPointId_) {
  entryPointId = entryPointId_;
};
void LLVM::setSrcRootDir(const std::string srcRootDir_) {
  srcRootDir = srcRootDir_;
};
void LLVM::setDstRootDir(const std::string dstRootDir_) {
  dstRootDir = dstRootDir_;
};
