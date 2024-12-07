// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_LLVM_LLVM_GEN_
#define _COMPILER_LLVM_LLVM_GEN_
#include "compiler/llvm/ir_gen_context.hpp"
#include "compiler/llvm/option.hpp"
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace LLVM {

class CodeGen {
public:
  CodeGen(Parser::Ast *const ast, const Option llvmOption);
  ~CodeGen() {};
  CodeGen(const CodeGen &rhs);
  CodeGen &operator=(const CodeGen &rhs);
  void generateLlvmIr();
  void dumpLlvmIr();
  void emitLlvmIr();

private:
  Parser::Ast *ast;
  IrGenContext *context;
};

} // namespace LLVM
} // namespace Compiler
} // namespace gallop
#endif