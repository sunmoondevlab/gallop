#ifndef _COMPILER_LLVM_LLVM_GEN_
#define _COMPILER_LLVM_LLVM_GEN_
#include "compiler/parser/ast.hpp"
#include <llvm/IR/ConstantFolder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <vector>

namespace gallop {
namespace Compiler {
namespace LLVM {
class CodeGen {
public:
  CodeGen(Parser::Ast *const ast_);
  ~CodeGen() {};
  CodeGen(const CodeGen &rhs);
  CodeGen &operator=(const CodeGen &rhs);
  CodeGen *generateLLVM();

private:
  llvm::LLVMContext *context;
  llvm::IRBuilder<> *builder;
  std::vector<llvm::Module *> modules;
  Parser::Ast *ast;
};
} // namespace LLVM
} // namespace Compiler
} // namespace gallop

#endif