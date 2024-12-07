// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/llvm/ir_gen_context.hpp"

using namespace gallop::Compiler::LLVM;

IrGenContext::IrGenContext(const Option llvmOption_)
    : context(new llvm::LLVMContext()),
      builder(new llvm::IRBuilder<>(*context, llvm::ConstantFolder(),
                                    llvm::IRBuilderDefaultInserter())),
      moduleCount(0), modules(std::vector<llvm::Module *>()),
      llvmOption(llvmOption_), executableBinary(false) {};
IrGenContext::IrGenContext(const IrGenContext &rhs)
    : context(rhs.context), builder(rhs.builder), moduleCount(rhs.moduleCount),
      modules(rhs.modules), llvmOption(rhs.llvmOption),
      executableBinary(rhs.executableBinary) {};
IrGenContext &IrGenContext::operator=(const IrGenContext &rhs) {
  context = rhs.context;
  builder = rhs.builder;
  moduleCount = rhs.moduleCount;
  modules = rhs.modules;
  llvmOption = rhs.llvmOption;
  executableBinary = rhs.executableBinary;
  return *this;
};

void IrGenContext::pushModule(llvm::Module *const module_) {
  modules.push_back(module_);
  moduleCount++;
};
llvm::LLVMContext *IrGenContext::getContext() { return context; };
llvm::IRBuilder<> *IrGenContext::getBuilder() { return builder; };
size_t IrGenContext::getModuleCount() const { return moduleCount; };
llvm::Module *IrGenContext::getModule(const size_t &pos_) {
  if (pos_ >= 0 && pos_ < moduleCount) {
    return modules[pos_];
  }
  return nullptr;
};
Option IrGenContext::getLlvmOption() const { return llvmOption; };
bool IrGenContext::isExecutableBinary() const { return executableBinary; };
void IrGenContext::setExecutableBinary() { executableBinary = true; };
