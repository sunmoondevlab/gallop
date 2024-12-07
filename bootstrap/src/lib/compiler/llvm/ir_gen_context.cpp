#include "compiler/llvm/ir_gen_context.hpp"

using namespace gallop::Compiler::LLVM;

IrGenContext::IrGenContext()
    : context(new llvm::LLVMContext()),
      builder(new llvm::IRBuilder<>(*context, llvm::ConstantFolder(),
                                    llvm::IRBuilderDefaultInserter())),
      moduleCnt(0), modules(std::vector<llvm::Module *>()) {};
IrGenContext::IrGenContext(const IrGenContext &rhs)
    : context(rhs.context), builder(rhs.builder), moduleCnt(rhs.moduleCnt),
      modules(rhs.modules) {};
IrGenContext &IrGenContext::operator=(const IrGenContext &rhs) {
  context = rhs.context;
  builder = rhs.builder;
  moduleCnt = rhs.moduleCnt;
  modules = rhs.modules;
  return *this;
};

void IrGenContext::pushModule(llvm::Module *const module_) {
  modules.push_back(module_);
  moduleCnt++;
};
llvm::LLVMContext *IrGenContext::getContext() { return context; };
llvm::IRBuilder<> *IrGenContext::getBuilder() { return builder; };
size_t IrGenContext::getModuleCnt() const { return moduleCnt; };
llvm::Module *IrGenContext::getModule(const size_t pos_) {
  if (pos_ >= 0 && pos_ < moduleCnt) {
    return modules[pos_];
  }
  return nullptr;
};
