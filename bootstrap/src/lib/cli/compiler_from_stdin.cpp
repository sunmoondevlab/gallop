#include "cli/compiler_from_stdin.hpp"
#include "charset/detector/detector.hpp"
#include "cli/translate_args.hpp"
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/module_stdin.hpp"

using namespace gallop::CharSet;
using namespace gallop::Cli;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

void CompilerFromStdin::execute(Args args_) {
  Ast *ast = new Ast(AstNodeTypeEnum::rootStdin);
  AstNodeModuleStdin *moduleNode = new AstNodeModuleStdin();
  ast->getRoot()->putChildNode(moduleNode);

  ast->printAst(args_.isVerboseEmit());
  std::vector<char> buf;
  while (std::cin) {
    std::string str;
    getline(std::cin, str);
    std::copy(str.begin(), str.end(), std::back_inserter(buf));
    if (str.size() > 0) {
      buf.push_back('\n');
    }
  }
  Detector d(buf);
  if (d.getEncodingCharset() != EncodingCharsetEnum::ASCII &&
      d.getEncodingCharset() != EncodingCharsetEnum::UTF8 &&
      d.getEncodingCharset() != EncodingCharsetEnum::UTF8_BOM) {
    std::cerr << "Unsupport charcter set\n";
    return;
  }
  ast->printAst(args_.isVerboseEmit());
};
