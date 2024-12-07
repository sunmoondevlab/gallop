// // Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
// #include "cli/compiler_from_stdin.hpp"
// #include "char_set/detector/detector.hpp"
// #include "cli/translate_args.hpp"
// #include "compiler/lexer/lexical_analyzer.hpp"
// #include "compiler/parser/ast.hpp"
// #include "compiler/parser/ast_node/module_stdin.hpp"

// using namespace gallop::CharSet;
// using namespace gallop::Cli;
// using namespace gallop::Compiler::Lexer;
// using namespace gallop::Compiler::Parser;

// void CompilerFromStdin::execute(Args args_) {
//   Ast *ast = new Ast(AstNodeTypeEnum::rootStdin);
//   AstNodeModuleStdin *moduleNode = new AstNodeModuleStdin();
//   ast->getRoot()->setChild(moduleNode);

//   std::vector<char> buf;
//   while (std::cin) {
//     std::string str;
//     getline(std::cin, str);
//     std::copy(str.begin(), str.end(), std::back_inserter(buf));
//     if (str.size() > 0) {
//       buf.push_back('\n');
//     }
//   }
//   Detector d(buf);
//   if (d.encodingCharSet() != EncodingCharsetEnum::ASCII &&
//       d.encodingCharSet() != EncodingCharsetEnum::UTF8 &&
//       d.encodingCharSet() != EncodingCharsetEnum::UTF8_BOM) {
//     std::cerr << "Unsupport charcter set\n";
//     return;
//   }
//   ast->printAst(args_.isVerboseDump());
// };
