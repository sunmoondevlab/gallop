#ifndef _COMPILER_LLVM_LLVM_IR_GEN_CONTEXT_
#define _COMPILER_LLVM_LLVM_IR_GEN_CONTEXT_
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
  IrGenContext();
  ~IrGenContext() {};
  IrGenContext(const IrGenContext &rhs);
  IrGenContext &operator=(const IrGenContext &rhs);
  void pushModule(llvm::Module *const module);
  llvm::LLVMContext *getContext();
  llvm::IRBuilder<> *getBuilder();
  size_t getModuleCnt() const;
  llvm::Module *getModule(const size_t pos);

private:
  llvm::LLVMContext *context;
  llvm::IRBuilder<> *builder;
  size_t moduleCnt;
  std::vector<llvm::Module *> modules;
};

} // namespace LLVM
} // namespace Compiler
} // namespace gallop

#endif