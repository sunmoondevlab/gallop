// Copyright © 2024- Sunmoon development laboratory. Allexer Rights Reserved.
#include "compiler/controller/lexical_analyzer.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"
#include "char_set/string/utf32_string.hpp"
#include "error/compile_errors.hpp"

using namespace gallop::CharSet;
using namespace gallop::Compiler;
using namespace gallop::Error;
using namespace gallop::Compiler::Controller;
using namespace gallop::IO::Stream;

class LexicalAnalyzerTest : public ::testing::Test {};

TEST_F(LexicalAnalyzerTest, Constructor) {
  // interpreter default
  SrcLines lines;
  LexicalAnalyzer lexer(lines, CompilerModeEnum::interpreter);
  ASSERT_EQ(lexer.isInterpreter(), true);
  ASSERT_EQ(lexer.isFromFile(), false);
  ASSERT_EQ(lexer.getLineCount(), 0ul);
  ASSERT_EQ(lexer.getLineString(1), "");

  // compiler from stdin
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  ASSERT_EQ(lexer.isInterpreter(), false);
  ASSERT_EQ(lexer.isFromFile(), false);
  ASSERT_EQ(lexer.getLineCount(), 0ul);
  ASSERT_EQ(lexer.getLineString(1), "");

  lines = SrcLines("a.trot");
  // compiler from stdin
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromFile);
  ASSERT_EQ(lexer.isInterpreter(), false);
  ASSERT_EQ(lexer.isFromFile(), true);
  ASSERT_EQ(lexer.getFilename(), "a.trot");
  ASSERT_EQ(lexer.getLineCount(), 0ul);
  ASSERT_EQ(lexer.getLineString(1), "");
};

TEST_F(LexicalAnalyzerTest, TokenizeInterpreter) {
  //   std::vector<char> buf;
  //   Tokens *tokens;
  //   Token token;
  // interpreter default
  SrcLines lines;
  LexicalAnalyzer lexer(lines, CompilerModeEnum::interpreter);
  ASSERT_EQ(lexer.isInterpreter(), true);
  ASSERT_EQ(lexer.isFromFile(), false);
  ASSERT_EQ(lexer.getLineCount(), 0ul);
  ASSERT_EQ(lexer.getLineString(1), "");

  // str = U"a:i32=1;\nfmain{\n exit 0;\n}";
  // lexer = LexicalAnalyzer(std::vector<int32_t>(str.begin(), str.end()));
  // ASSERT_EQ(lexer.isInterpreter(), false);
  // ASSERT_EQ(lexer.getLineCount(), 4ul);
  // ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  // ASSERT_EQ(lexer.getLineString(4), "}");
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);

  //   str = U"a:i32=1;\nfmain{\n exit 0;\n}\n";
  //   buf = std::vector<int32_t>(str.begin(), str.end());
  //     //   lexer = LexicalAnalyzer(buf);
  //   ASSERT_EQ(lexer.isInterpreter(), false);
  //   ASSERT_EQ(lexer.getLineCount(), 4ul);
  //   ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  //   ASSERT_EQ(lexer.getLineString(4), "}\n");
  //   tis = lexer.getTokensInputStream();
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);

  //   // compiler from file
  //   str = U"a:i32=1;\nfmain{\n exit 0;\n}";
  //   buf = std::vector<int32_t>(str.begin(), str.end());
  //     //   lexer = LexicalAnalyzer(buf, "test.trot");
  //   ASSERT_EQ(lexer.isInterpreter(), false);
  //   ASSERT_EQ(lexer.getLineCount(), 4ul);
  //   ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  //   ASSERT_EQ(lexer.getLineString(4), "}");
  //   tis = lexer.getTokensInputStream();
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "test.trot");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);

  //   // interpreter
  //   str = U"a:i32=1;\n";
  //   buf = std::vector<int32_t>(str.begin(), str.end());
  //     //   lexer = LexicalAnalyzer(lines,
  //     CompilerModeEnum::compilerFromStdin)
  //   tis = lexer.getTokensInputStream();
  //   ASSERT_EQ(lexer.isInterpreter(), true);
  //   ASSERT_EQ(lexer.getLineCount(), 1ul);
  //   ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);
};

TEST_F(LexicalAnalyzerTest, TokenizeInConstructer) {
  //   std::vector<char> buf;
  //   Tokens *tokens;
  //   Token token;
  // interpreter default
  SrcLines lines;
  LexicalAnalyzer lexer(lines, CompilerModeEnum::interpreter);
  ASSERT_EQ(lexer.isInterpreter(), true);
  ASSERT_EQ(lexer.isFromFile(), false);
  ASSERT_EQ(lexer.getLineCount(), 0ul);
  ASSERT_EQ(lexer.getLineString(1), "");

  // compiler from stdin
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  ASSERT_EQ(lexer.isInterpreter(), false);
  ASSERT_EQ(lexer.isFromFile(), false);
  ASSERT_EQ(lexer.getLineCount(), 0ul);
  ASSERT_EQ(lexer.getLineString(1), "");

  lines = SrcLines("a.trot");
  // compiler from stdin
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromFile);
  ASSERT_EQ(lexer.isInterpreter(), false);
  ASSERT_EQ(lexer.isFromFile(), true);
  ASSERT_EQ(lexer.getFilename(), "a.trot");
  ASSERT_EQ(lexer.getLineCount(), 0ul);
  ASSERT_EQ(lexer.getLineString(1), "");

  // str = U"a:i32=1;\nfmain{\n exit 0;\n}";
  // lexer = LexicalAnalyzer(std::vector<int32_t>(str.begin(), str.end()));
  // ASSERT_EQ(lexer.isInterpreter(), false);
  // ASSERT_EQ(lexer.getLineCount(), 4ul);
  // ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  // ASSERT_EQ(lexer.getLineString(4), "}");
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);

  //   str = U"a:i32=1;\nfmain{\n exit 0;\n}\n";
  //   buf = std::vector<int32_t>(str.begin(), str.end());
  //     //   lexer = LexicalAnalyzer(buf);
  //   ASSERT_EQ(lexer.isInterpreter(), false);
  //   ASSERT_EQ(lexer.getLineCount(), 4ul);
  //   ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  //   ASSERT_EQ(lexer.getLineString(4), "}\n");
  //   tis = lexer.getTokensInputStream();
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);

  //   // compiler from file
  //   str = U"a:i32=1;\nfmain{\n exit 0;\n}";
  //   buf = std::vector<int32_t>(str.begin(), str.end());
  //     //   lexer = LexicalAnalyzer(buf, "test.trot");
  //   ASSERT_EQ(lexer.isInterpreter(), false);
  //   ASSERT_EQ(lexer.getLineCount(), 4ul);
  //   ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  //   ASSERT_EQ(lexer.getLineString(4), "}");
  //   tis = lexer.getTokensInputStream();
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "test.trot");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);

  //   // interpreter
  //   str = U"a:i32=1;\n";
  //   buf = std::vector<int32_t>(str.begin(), str.end());
  //     //   lexer = LexicalAnalyzer(lines,
  //     CompilerModeEnum::compilerFromStdin)
  //   tis = lexer.getTokensInputStream();
  //   ASSERT_EQ(lexer.isInterpreter(), true);
  //   ASSERT_EQ(lexer.getLineCount(), 1ul);
  //   ASSERT_EQ(lexer.getLineString(1), "a:i32=1;\n");
  //    tis = lexer.getTokensInputStream();
  //   token = tis.read();
  //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
  //   ASSERT_EQ(token->getToken(), U"a");
  //   ASSERT_EQ(token->getLocation().getFilename(), "");
  //   ASSERT_EQ(token->getLocation().getLine(), 1ul);
  //   ASSERT_EQ(token->getLocation().getColumn(), 1ul);
};

TEST_F(LexicalAnalyzerTest, ToNextToken) {
  SrcLines lines("a.trot");
  std::u32string str = U"  fn";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromFile);
  ASSERT_EQ(lexer.isInterpreter(), false);
  ASSERT_EQ(lexer.isFromFile(), true);
  ASSERT_EQ(lexer.getLineCount(), 1ul);
  ASSERT_EQ(lexer.getLineString(1), "  fn");
  TokensInputStream tis = lexer.getTokensInputStream();
  ASSERT_EQ(tis.size(), 1ul);
  Token *token = tis.read();
  Location location = token->getLocation();
  ASSERT_EQ(location.getBufferPos(), 2ul);
  ASSERT_EQ(location.getLine(), 1ul);
  ASSERT_EQ(location.getColumn(), 3ul);

  lines.resetBuffer();
  str = U"\r\n\n\rfn";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromFile);
  ASSERT_EQ(lexer.isInterpreter(), false);
  ASSERT_EQ(lexer.isFromFile(), true);
  ASSERT_EQ(lexer.getLineCount(), 4ul);
  ASSERT_EQ(lexer.getLineString(4), "fn");
  tis = lexer.getTokensInputStream();
  ASSERT_EQ(tis.size(), 1ul);
  token = tis.read();
  location = token->getLocation();
  ASSERT_EQ(location.getBufferPos(), 4ul);
  ASSERT_EQ(location.getLine(), 4ul);
  ASSERT_EQ(location.getColumn(), 1ul);
};

// TEST_F(LexicalAnalyzerTest, Identifier) {
// SrcLines lines("a.trot");
// std::u32string str = U"  fn";
// std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
//
//   std::vector<char> buf;
//   Token token;
//   std::string str = U"$_simple\n";
//   //   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"_simple");
//   ASSERT_EQ(token->getTokenLen(), 7ul);
//
//   str = U"$16bin\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"16bin");
//   ASSERT_EQ(token->getTokenLen(), 5ul);
//
//   str = U"-0e.0simple\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0e");
//   ASSERT_EQ(token->getTokenLen(), 2ul);
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"0simple");
//   ASSERT_EQ(token->getTokenLen(), 7ul);
//
//   str = U"0.0simple\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"0simple");
//   ASSERT_EQ(token->getTokenLen(), 7ul);
// };

// TEST_F(LexicalAnalyzerTest, DecimalNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = U"1234\n";
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tis.read();
//   ASSERT_EQ(token->getLocation().getLine(), 1ul);
//   ASSERT_EQ(token->getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"1234");

//   str = U"-12345\r\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tis.read();
//   ASSERT_EQ(token->getLocation().getLine(), 1ul);
//   ASSERT_EQ(token->getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token->getToken(), U"-");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getLocation().getLine(), 1ul);
//   ASSERT_EQ(token->getLocation().getColumn(), 2ul);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"12345");

//   str = U"0\r";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tis.read();
//   ASSERT_EQ(token->getLocation().getLine(), 1ul);
//   ASSERT_EQ(token->getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"0");

//   str = U"   \t -0\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tis.read();
//   ASSERT_EQ(token->getLocation().getLine(), 1ul);
//   ASSERT_EQ(token->getLocation().getColumn(), 6ul);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token->getToken(), U"-");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getLocation().getLine(), 1ul);
//   ASSERT_EQ(token->getLocation().getColumn(), 7ul);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"0");

//   str = U"1";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"1");

//   str = U"-1";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token->getToken(), U"-");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"1");

//   str = U"-0.1\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token->getToken(), U"-");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"0");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token->getToken(), U"1");

//   str = U"10.001\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token->getToken(), U"001");

//   str = U"10.\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");

//   str = U"10.e+1\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 5ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token->getToken(), U"e");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scPositiveDecimalExponent);
//   ASSERT_EQ(token->getToken(), U"+");
//   token = tokens->get(4);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token->getToken(), U"1");

//   str = U"10.0e-2\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token->getToken(), U"0");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token->getToken(), U"e");
//   token = tokens->get(4);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scNegativeDecimalExponent);
//   ASSERT_EQ(token->getToken(), U"-");
//   token = tokens->get(5);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token->getToken(), U"2");

//   str = U"10.01e-2\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token->getToken(), U"01");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token->getToken(), U"e");
//   token = tokens->get(4);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scNegativeDecimalExponent);
//   ASSERT_EQ(token->getToken(), U"-");
//   token = tokens->get(5);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token->getToken(), U"2");

//   str = U"10.01e+2\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token->getToken(), U"01");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token->getToken(), U"e");
//   token = tokens->get(4);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scPositiveDecimalExponent);
//   ASSERT_EQ(token->getToken(), U"+");
//   token = tokens->get(5);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token->getToken(), U"2");

//   str = U"10.001e+2\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token->getToken(), U"001");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token->getToken(), U"e");
//   token = tokens->get(4);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::scPositiveDecimalExponent);
//   ASSERT_EQ(token->getToken(), U"+");
//   token = tokens->get(5);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token->getToken(), U"2");

//   str = U"10.001e+\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"001e");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPlus);
//   ASSERT_EQ(token->getToken(), U"+");

//   str = U"10.001e-\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"001e");
//   token = tokens->get(3);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMinus);
//   ASSERT_EQ(token->getToken(), U"-");

//   str = U"10.001e\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"001e");

//   str = U"10.001ea\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"001ea");

//   str = U"10.001a\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"10");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token->getToken(), U"001a");

//   str = U"10a0_01a\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"10a0_01a");

//   str = U"100_01";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"100_01");

//   str = U"100_01.001001_0101";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"100_01");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token->getToken(), U".");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token->getToken(), U"001001_0101");
// };

// TEST_F(LexicalAnalyzerTest, BinaryNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = U"0b01001_0101\n";
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltBinaryPrefix);
//   ASSERT_EQ(token->getToken(), U"0b");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltBinaryIntegralPart);
//   ASSERT_EQ(token->getToken(), U"01001_0101");

//   str = U"0B01001_0101";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltBinaryPrefix);
//   ASSERT_EQ(token->getToken(), U"0B");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltBinaryIntegralPart);
//   ASSERT_EQ(token->getToken(), U"01001_0101");

//   str = U"0b";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0b");

//   str = U"0b2a\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0b2a");

//   str = U"0b012\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0b012");
// };

// TEST_F(LexicalAnalyzerTest, OctalNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = U"0o07422_263\n";
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalPrefix);
//   ASSERT_EQ(token->getToken(), U"0o");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"07422_263");

//   str = U"0O07422_263";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalPrefix);
//   ASSERT_EQ(token->getToken(), U"0O");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"07422_263");

//   str = U"0o";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0o");

//   str = U"0o738617\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalPrefix);
//   ASSERT_EQ(token->getToken(), U"0o");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"73");
//   token = tokens->get(2);
//   ASSERT_EQ(token->getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"8617");

//   str = U"0o8617\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0o8617");

//   str = U"0o78617\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0o78617");
// };

// TEST_F(LexicalAnalyzerTest, HexadecimalNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = U"0x91f7a74_38e4f\n";
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltHexadecimalPrefix);
//   ASSERT_EQ(token->getToken(), U"0x");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltHexadecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"91f7a74_38e4f");

//   str = U"0X91F7A74_38E4F";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltHexadecimalPrefix);
//   ASSERT_EQ(token->getToken(), U"0X");
//   token = tokens->get(1);
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltHexadecimalIntegralPart);
//   ASSERT_EQ(token->getToken(), U"91F7A74_38E4F");

//   str = U"0x";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0x");

//   str = U"0xfeG8437f\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0xfeG8437f");

//   str = U"0xG8437f\n";
//   buf = std::vector<int32_t>(str.begin(), str.end());
//   //   lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);//
//   tis = lexer.getTokensInputStream();
//    tis = lexer.getTokensInputStream();
//   token = tis.read();
//   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token->getToken(), U"0xG8437f");
// };

// TEST_F(LexicalAnalyzerTest, SingleCharacter) {
//   LexicalAnalyzer l;
//   Tokens *tokens;
// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = U"''";
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'1\\\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"'1\\\r\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"'1\\\r\n";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   str = U"1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"'1.\\\r";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1.");
// //   str = U"1'.";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token->getToken(), U"'");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token->getToken(), U".");

// //   str = U"'1\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1\n1");

// //   str = U"'1\r\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1\r\n1");

// //   str = U"'1\r\n";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1\r\n");
// //   str = U"1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"'1.\r";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1.\r");
// //   str = U"1'.";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token->getToken(), U"'");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token->getToken(), U".");

// //   str = U"'\\r'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'\\n'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'\\t'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'\\\\'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'\\''";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\'");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'\\o017371_3977'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
// //   ASSERT_EQ(token->getToken(), U"\\o");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"017371");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"_3977");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token->getToken(), U"'");

// //   str = U"'\\x2f6a9bcf_fg839'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
// //   ASSERT_EQ(token->getToken(), U"\\x");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token->getToken(), U"'");

// //   str = U"'\\u2f6a9bcf_fg839'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
// //   ASSERT_EQ(token->getToken(), U"\\u");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token->getToken(), U"'");

// //   str = U"''";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'⮕'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = U"'鼻'";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token->getToken(), U"鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// // };

// // TEST_F(LexicalAnalyzerTest, String) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = U"\"\"";
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"1\\\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"\"1\\\r\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"\"1\\\r\n";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   str = U"1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"\"1.\\\r";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1.");
// //   str = U"1\".";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token->getToken(), U"\"");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token->getToken(), U".");

// //   str = U"\"1\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1\n1");

// //   str = U"\"1\r\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1\r\n1");

// //   str = U"\"1\r\n";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1\r\n");
// //   str = U"1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"\"1.\r";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1.\r");
// //   str = U"1\".";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token->getToken(), U"\"");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token->getToken(), U".");

// //   str = U"\"\\r\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"\\n\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"\\t\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"\\\\\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"\\\"\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\\"");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"\\o017371_3977\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
// //   ASSERT_EQ(token->getToken(), U"\\o");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"017371");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"_3977");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token->getToken(), U"\"");

// //   str = U"\"\\x2f6a9bcf_fg839\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
// //   ASSERT_EQ(token->getToken(), U"\\x");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token->getToken(), U"\"");

// //   str = U"\"\\u2f6a9bcf_fg839\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
// //   ASSERT_EQ(token->getToken(), U"\\u");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token->getToken(), U"\"");

// //   str = U"\"\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"⮕\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = U"\"鼻\"";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token->getToken(), U"鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// // };

// // TEST_F(LexicalAnalyzerTest, RawString) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = U"``";
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`1\\\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"`1\\\r\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"`1\\\r\n";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   str = U"1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"`1.\\\r";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1.");
// //   str = U"1`.";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token->getToken(), U"`");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token->getToken(), U".");

// //   str = U"`1\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1\n1");

// //   str = U"`1\r\n1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1\r\n1");

// //   str = U"`1\r\n";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1\r\n");
// //   str = U"1";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");

// //   str = U"`1.\r";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1.\r");
// //   str = U"1`.";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token->getToken(), U"1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token->getToken(), U"`");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token->getToken(), U".");

// //   str = U"`\\r`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`\\n`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`\\t`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`\\\\`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`\\``";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token->getToken(), U"\\`");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`\\o017371_3977`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
// //   ASSERT_EQ(token->getToken(), U"\\o");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"017371");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"_3977");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token->getToken(), U"`");

// //   str = U"`\\x2f6a9bcf_fg839`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
// //   ASSERT_EQ(token->getToken(), U"\\x");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token->getToken(), U"`");

// //   str = U"`\\u2f6a9bcf_fg839`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
// //   ASSERT_EQ(token->getToken(), U"\\u");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token->getToken(), U"2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token->getToken(), U"`");

// //   str = U"``";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`⮕`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = U"`鼻`";
// //   buf = std::vector<int32_t>(str.begin(), str.end());
// //   // //   lexer = LexicalAnalyzer(lines,
// CompilerModeEnum::compilerFromStdin)
// //   tis = lexer.getTokensInputStream();
// //    tis = lexer.getTokensInputStream();
// //   token = tis.read();
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token->getToken(), U"鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token->getTokenType(),
// TokenTypeEnum::scBackQuotation);
// // };

#include "./lexical_analyzer_test.cpp.symbol_characters.inc"

#include "./lexical_analyzer_test.cpp.comment_out_oneline.inc"

#include "./lexical_analyzer_test.cpp.comment_out_block.inc"

#include "./lexical_analyzer_test.cpp.single_char.inc"

#include "./lexical_analyzer_test.cpp.string.inc"

#include "./lexical_analyzer_test.cpp.raw_string.inc"
