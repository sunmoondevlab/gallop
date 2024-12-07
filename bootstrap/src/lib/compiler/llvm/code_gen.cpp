// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/llvm/code_gen.hpp"
#include "compiler/llvm/ir_gen_context.hpp"
#include "compiler/parser/ast.hpp"
#include "io/file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <system_error>

using namespace gallop;
using namespace gallop::Compiler::LLVM;
using namespace gallop::Compiler::Parser;
using namespace gallop::IO;

CodeGen::CodeGen(Ast *const ast_, const Option llvmOption_)
    : ast(ast_), context(new IrGenContext(llvmOption_)) {};
CodeGen::CodeGen(const CodeGen &rhs) : ast(rhs.ast), context(rhs.context) {};
CodeGen &CodeGen::operator=(const CodeGen &rhs) {
  ast = rhs.ast;
  context = rhs.context;
  return *this;
};
void CodeGen::generateLlvmIr() {
  AstNode *root = ast->getRoot();
  if (root != nullptr)
    root->generateLlvmIr(context);
};

void CodeGen::dumpLlvmIr() {
  size_t moduleCount = context->getModuleCount();
  for (size_t moduleIdx = 0; moduleIdx < moduleCount; moduleIdx++) {
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

void CodeGen::emitLlvmIr() {
  size_t moduleCount = context->getModuleCount();
  for (size_t moduleIdx = 0; moduleIdx < moduleCount; moduleIdx++) {
    llvm::Module *module = context->getModule(moduleIdx);
    std::string moduleFilename = module->getSourceFileName();
    std::string llvmIrFilename;
    std::string srcRootDir = context->getLlvmOption().getSrcRootDir();
    std::string destRootDir = context->getLlvmOption().getDestRootDir();
    if (moduleFilename == "") {
      llvmIrFilename = File::replacePathDirectory(
          File::absoluteCanonicalPath(module->getModuleIdentifier() + ".ll"),
          srcRootDir, destRootDir);
    } else {
      llvmIrFilename = File::replacePathDirectory(
          File::absoluteCanonicalPath(
              File::replaceExtension(moduleFilename, "ll")),
          srcRootDir, destRootDir);
    }
    std::error_code ec;
    llvm::raw_fd_stream outLlvmIrFd(llvmIrFilename, ec);
    module->print(outLlvmIrFd, nullptr);
  }
};
