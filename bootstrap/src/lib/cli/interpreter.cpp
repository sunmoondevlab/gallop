// // Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
// #include "cli/interpreter.hpp"
// #include "char_set/detector/detector.hpp"
// #include "cli/translate_args.hpp"
// #include "compiler/lexer/lexical_analyzer.hpp"
// #include "compiler/parser/ast.hpp"
// #include "compiler/parser/ast_node/module_interpreter.hpp"

// using namespace gallop::CharSet;
// using namespace gallop::Cli;
// using namespace gallop::Compiler::Lexer;
// using namespace gallop::Compiler::Parser;

// void Interpreter::execute(Args args_) {
//   Ast *ast = new Ast(AstNodeTypeEnum::rootInterpreter);
//   AstNodeModuleInterpreter *moduleNode = new AstNodeModuleInterpreter();
//   ast->getRoot()->setChild(moduleNode);
//   LexicalAnalyzer lexer;
//   size_t prevParsableTokenCnt = 0;
//   while (std::cin) {
//     std::cout << "> ";
//     std::string str;
//     getline(std::cin, str);
//     std::vector<char> buf;
//     std::copy(str.begin(), str.end(), std::back_inserter(buf));
//     buf.push_back('\n');
//     Detector d(buf);
//     if (d.encodingCharSet() != EncodingCharsetEnum::ASCII &&
//         d.encodingCharSet() != EncodingCharsetEnum::UTF8 &&
//         d.encodingCharSet() != EncodingCharsetEnum::UTF8_BOM) {
//       std::cerr << "Unsupport charcter set\n";
//       continue;
//     }
//     lexer.tokenizeNextBuffer(buf);
//     Tokens *tokens = lexer.getTokens();
//     size_t parsableTokenCnt = tokens->getParsableTokenCount();
//     bool isAnalyzeContinue = prevParsableTokenCnt == parsableTokenCnt;
//     if (args_.isDumpTokens() && !isAnalyzeContinue) {
//       llvm::outs() << "\n";
//       llvm::outs() << "--  to tokens --\n";
//       tokens->printTokens(args_.isVerboseDump());
//     }
//     prevParsableTokenCnt = parsableTokenCnt;
//   }
// };
