#include "cli/compiler_from_file.hpp"
#include "charset/detector/detector.hpp"
#include "cli/translate_args.hpp"
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/llvm/code_gen.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/module_file.hpp"
#include "compiler/parser/syntax_analyzer.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet;
using namespace gallop::Cli;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

void CompilerFromFile::execute(Args args_) {
  std::vector<std::string> files = args_.getArgs();
  size_t fileCnt = files.size();
  Ast *ast = new Ast(AstNodeTypeEnum::rootFile);
  ast->printAst(args_.isVerboseEmit());
  CodeGen codeGen(ast);
  for (size_t fileIdx = 0; fileIdx < fileCnt; fileIdx++) {
    if (!File::isExists(files[fileIdx])) {
      continue;
    }
    std::vector<char> buf = File::readAllBinary(files[fileIdx]);
    Detector d(buf);
    if (d.getEncodingCharset() != EncodingCharsetEnum::ASCII &&
        d.getEncodingCharset() != EncodingCharsetEnum::UTF8 &&
        d.getEncodingCharset() != EncodingCharsetEnum::UTF8_BOM) {
      continue;
    }
    LexicalAnalyzer lexer(buf);
    Tokens *tokens = lexer.getTokens();
    if (args_.isEmitTokens()) {
      llvm::outs() << "\n";
      llvm::outs() << "-- " << files[fileIdx] << " to tokens --\n";
      tokens->printTokens(args_.isVerboseEmit());
    }
    AstNodeModuleFile *moduleNode = new AstNodeModuleFile(files[fileIdx]);
    SyntaxAnalyzer parser(&lexer, moduleNode, args_.getParserOption());
    ast->getRoot()->putChildNode(moduleNode);
    if (args_.isEmitAst()) {
      llvm::outs() << "\n";
      llvm::outs() << "-- " << files[fileIdx] << " to AST --\n";
      ast->printAst(args_.isVerboseEmit());
    }
  }
  codeGen.generateLlvmIr();
  if (args_.isEmitLlvmIr()) {
    codeGen.printLlvmIr();
  }
};
