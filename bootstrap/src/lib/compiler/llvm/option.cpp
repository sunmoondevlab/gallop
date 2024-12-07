// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/llvm/option.hpp"

#include "io/file/file.hpp"

using namespace gallop::Compiler::LLVM;
using namespace gallop::IO;

Option::Option()
    : entryPointId(""), srcRootDir(File::getCurrentDir()),
      dstRootDir(File::getCurrentDir()) {};
Option::Option(const Option &rhs)
    : entryPointId(rhs.entryPointId), srcRootDir(rhs.srcRootDir),
      dstRootDir(rhs.dstRootDir) {};
Option &Option::operator=(const Option &rhs) {
  entryPointId = rhs.entryPointId;
  srcRootDir = rhs.srcRootDir;
  dstRootDir = rhs.dstRootDir;
  return *this;
};
std::string Option::getEntryPointId() const { return entryPointId; };
std::string Option::getSrcRootDir() const { return srcRootDir; };
std::string Option::getDstRootDir() const { return dstRootDir; };
void Option::setEntryPointId(const std::string entryPointId_) {
  entryPointId = entryPointId_;
};
void Option::setSrcRootDir(const std::string srcRootDir_) {
  srcRootDir = srcRootDir_;
};
void Option::setDstRootDir(const std::string dstRootDir_) {
  dstRootDir = dstRootDir_;
};
