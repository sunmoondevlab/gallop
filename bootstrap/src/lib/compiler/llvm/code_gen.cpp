#include "compiler/llvm/code_gen.hpp"
#include "compiler/llvm/ir_gen_context.hpp"
#include "compiler/parser/ast.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler::LLVM;
using namespace gallop::Compiler::Parser;

CodeGen::CodeGen(Ast *const ast_) : ast(ast_), context(new IrGenContext()) {};
CodeGen::CodeGen(const CodeGen &rhs) : ast(rhs.ast), context(rhs.context) {};
CodeGen &CodeGen::operator=(const CodeGen &rhs) {
  ast = rhs.ast;
  context = rhs.context;
  return *this;
};
void CodeGen::generateLlvmIr() {
  std::vector<AstNodeQueue> queue = AstNodeQueue::queueingAstNode(ast, context);
  for (AstNodeQueue node : queue) {
    node.generateLlvmIr(context);
  }
};

void CodeGen::printLlvmIr() {
  size_t moduleCnt = context->getModuleCnt();
  for (size_t moduleIdx = 0; moduleIdx < moduleCnt; moduleIdx++) {
    llvm::Module *module = context->getModule(moduleIdx);
    std::string moduleFilename = module->getSourceFileName();
    llvm::outs() << "\n";
    if (moduleFilename != "") {
      llvm::outs() << "-- " << moduleFilename << " to LLVM IR --\n";
    } else {
      llvm::outs() << "-- to LLVM IR --\n";
    }
    module->print(llvm::outs(), nullptr);
  }
};
