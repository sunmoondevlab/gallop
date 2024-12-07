#include "cli/interpreter.hpp"
#include "charset/detector/detector.hpp"
#include "cli/translate_args.hpp"
#include "compiler/lexer/lexical_analyzer.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/module_interpreter.hpp"

using namespace gallop::CharSet;
using namespace gallop::Cli;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

void Interpreter::execute(Args args_) {
  Ast *ast = new Ast(AstNodeTypeEnum::rootInterpreter);
  AstNodeModuleInterpreter *moduleNode = new AstNodeModuleInterpreter();
  ast->getRoot()->putChildNode(moduleNode);
  // size_t line = 1, column = 1;
  // Parser::LexicalAnalyzer l(buf, line, 0l);
  ast->printAst(args_.isVerboseEmit());
  while (std::cin) {
    std::cout << "> ";
    std::string str;
    getline(std::cin, str);
    std::vector<char> buf;
    std::copy(str.begin(), str.end(), std::back_inserter(buf));
    buf.push_back('\n');
    Detector d(buf);
    if (d.getEncodingCharset() != EncodingCharsetEnum::ASCII &&
        d.getEncodingCharset() != EncodingCharsetEnum::UTF8 &&
        d.getEncodingCharset() != EncodingCharsetEnum::UTF8_BOM) {
      std::cerr << "Unsupport charcter set\n";
      continue;
    }
    ast->printAst(args_.isVerboseEmit());
    // l.tokenize();
    // line = l.getLine();
    // column = l.getColumn();
  }
};
