// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "cli/compiler_from_file.hpp"
#include "charset/detector/detector.hpp"
#include "cli/translate_args.hpp"
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/llvm/code_gen.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/module_file.hpp"
#include "compiler/parser/syntax_analyzer.hpp"
#include "io/file/file.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet;
using namespace gallop::Cli;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;
using namespace gallop::IO;

void CompilerFromFile::execute(Args args_) {
  std::vector<std::string> files = args_.getArgs();
  size_t fileCount = files.size();
  Ast *ast = new Ast(AstNodeTypeEnum::rootFile);
  CodeGen codeGen(ast, args_.getLlvmOption());
  for (size_t fileIdx = 0; fileIdx < fileCount; fileIdx++) {
    if (!File::exists(files[fileIdx])) {
      continue;
    }
    std::vector<char> buf = File::readAllBinary(files[fileIdx]);
    Detector d(buf);
    if (d.encodingCharSet() != EncodingCharsetEnum::ASCII &&
        d.encodingCharSet() != EncodingCharsetEnum::UTF8 &&
        d.encodingCharSet() != EncodingCharsetEnum::UTF8_BOM) {
      continue;
    }
    LexicalAnalyzer lexer;
    Tokens *tokens = lexer.getTokens();
    if (args_.isDumpTokens()) {
      llvm::outs() << "\n";
      llvm::outs() << "-- " << files[fileIdx] << " to tokens --\n";
      tokens->printTokens(args_.isVerboseDump());
    }
    AstNodeModuleFile *moduleNode = new AstNodeModuleFile(files[fileIdx]);
    ast->getRoot()->setChild(moduleNode);
    try {
      SyntaxAnalyzer parser(&lexer, moduleNode, args_.getParserOption());
    } catch (...) {
      llvm::outs() << "\n";
    }
  }
  if (args_.isDumpAst()) {
    llvm::outs() << "\n-- to AST --\n";
    ast->printAst(args_.isVerboseDump());
  }
  codeGen.generateLlvmIr();
  if (args_.isDumpLlvmIr()) {
    codeGen.dumpLlvmIr();
  }
  if (args_.isEmitLlvmIr()) {
    codeGen.emitLlvmIr();
  }
};
