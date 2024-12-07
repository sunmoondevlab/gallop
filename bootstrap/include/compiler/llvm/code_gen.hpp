#ifndef _COMPILER_LLVM_LLVM_GEN_
#define _COMPILER_LLVM_LLVM_GEN_
#include "compiler/llvm/ir_gen_context.hpp"
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace LLVM {

class CodeGen {
public:
  CodeGen(Parser::Ast *const ast);
  ~CodeGen() {};
  CodeGen(const CodeGen &rhs);
  CodeGen &operator=(const CodeGen &rhs);
  void generateLlvmIr();
  void printLlvmIr();

private:
  Parser::Ast *ast;
  IrGenContext *context;
};

} // namespace LLVM
} // namespace Compiler
} // namespace gallop

#endif