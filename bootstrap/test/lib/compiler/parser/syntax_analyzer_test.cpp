#include "compiler/parser/ast_node/module_file.hpp"
#include "compiler/parser/ast_node/module_interpreter.hpp"
#include "compiler/parser/ast_node/module_stdin.hpp"
#include "compiler/parser/option.hpp"
#include "compiler/parser/syntax_analyzer.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;
using namespace gallop::Compiler::Parser;

class SyntaxAnalyzerTest : public ::testing::Test {};
TEST_F(SyntaxAnalyzerTest, FmainCheck) {
  std::vector<char> buf;
  // interpreter default
  SyntaxAnalyzer s(new LexicalAnalyzer(), new AstNodeModuleInterpreter(),
                   Option());
  EXPECT_EQ(s.getParsedTokenPos(), 0ul);

  // compiler from stdin
  std::string str = "";
  str = "";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  s = SyntaxAnalyzer(new LexicalAnalyzer(buf), new AstNodeModuleStdin(),
                     Option());
  EXPECT_EQ(s.getParsedTokenPos(), 0ul);

  str = "fmain{}";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  s = SyntaxAnalyzer(new LexicalAnalyzer(buf), new AstNodeModuleStdin(),
                     Option());
  EXPECT_EQ(s.getParsedTokenPos(), 0ul);

  // compiler from file
  str = "fmain{}";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  s = SyntaxAnalyzer(new LexicalAnalyzer(buf, "test.trot"),
                     new AstNodeModuleFile("test.trot"), Option());
  EXPECT_EQ(s.getParsedTokenPos(), 0ul);
};
