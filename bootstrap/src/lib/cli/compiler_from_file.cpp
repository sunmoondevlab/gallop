#include "cli/compiler_from_file.hpp"
#include "charset/detector/detector.hpp"
#include "cli/translate_args.hpp"
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/module_file.hpp"
#include "compiler/parser/syntax_analyzer.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet;
using namespace gallop::Cli;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

void CompilerFromFile::execute(Args args) {
  std::vector<std::string> files = args.getArgs();
  size_t fileCnt = files.size();
  Ast *ast = new Ast(AstNodeTypeEnum::rootFile);
  ast->printAst(args.isVerboseEmit());
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
    if (args.isEmitTokens()) {
      llvm::outs() << "-- " << files[fileIdx] << " to tokens --\n";
      tokens->printTokens(args.isVerboseEmit());
    }
    AstNodeModuleFile *moduleNode = new AstNodeModuleFile(files[fileIdx]);
    SyntaxAnalyzer parser(&lexer, moduleNode);
    ast->getRoot()->putChildNode(moduleNode);
    ast->printAst(args.isVerboseEmit());
  }
};
