#include "compiler/llvm/llvm_gen.hpp"

using namespace gallop::Compiler::LLVM;
using namespace gallop::Compiler::Parser;

CodeGen::CodeGen(Ast *const ast_)
    : context(new llvm::LLVMContext()),
      builder(new llvm::IRBuilder<>(*context, llvm::ConstantFolder(),
                                    llvm::IRBuilderDefaultInserter())),
      modules(std::vector<llvm::Module *>()), ast(ast_) {};
CodeGen::CodeGen(const CodeGen &rhs)
    : context(rhs.context), builder(rhs.builder), modules(rhs.modules),
      ast(rhs.ast) {};
CodeGen &CodeGen::operator=(const CodeGen &rhs) {
  context = rhs.context;
  builder = rhs.builder;
  modules = rhs.modules;
  ast = rhs.ast;
  return *this;
};
CodeGen *CodeGen::generateLLVM() {
  AstNode *node = ast->getRoot();
  if (node != nullptr) {
  }
  return this;
};
