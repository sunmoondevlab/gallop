// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_LLVM_LLVM_IR_GEN_CONTEXT_
#define _COMPILER_LLVM_LLVM_IR_GEN_CONTEXT_
#include "compiler/llvm/option.hpp"
#include <llvm/IR/ConstantFolder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <vector>

namespace gallop {
namespace Compiler {
namespace LLVM {

class IrGenContext {
public:
  IrGenContext(const Option llvmOption);
  ~IrGenContext() {};
  IrGenContext(const IrGenContext &rhs);
  IrGenContext &operator=(const IrGenContext &rhs);
  void pushModule(llvm::Module *const module);
  llvm::LLVMContext *getContext();
  llvm::IRBuilder<> *getBuilder();
  size_t getModuleCount() const;
  llvm::Module *getModule(const size_t pos);
  Option getLlvmOption() const;
  bool isExecutableBinary() const;
  void setExecutableBinary();

private:
  llvm::LLVMContext *context;
  llvm::IRBuilder<> *builder;
  size_t moduleCount;
  std::vector<llvm::Module *> modules;
  Option llvmOption;
  bool executableBinary;
};

} // namespace LLVM
} // namespace Compiler
} // namespace gallop
#endif