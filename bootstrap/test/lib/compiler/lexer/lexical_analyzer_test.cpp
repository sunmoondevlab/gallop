// // Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
// #include "compiler/lexer/lexical_analyzer.hpp"
// #include <gtest/gtest.h>

// using namespace gallop::Compiler;
// using namespace gallop::Compiler::Lexer;

// class LexicalAnalyzerTest : public ::testing::Test {};

// TEST_F(LexicalAnalyzerTest, Constructor) {
//   std::vector<char> buf;
//   Tokens *tokens;
//   Token token;
//   // interpreter default
//   LexicalAnalyzer l;
//   ASSERT_EQ(l.isInterpreter(), true);
//   ASSERT_EQ(l.getLineCount(), 0ul);
//   ASSERT_EQ(l.getLineString(1), "");

//   // compiler from stdin
//   std::string str = "";
//   str = "";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer(buf);
//   ASSERT_EQ(l.isInterpreter(), false);
//   ASSERT_EQ(l.getLineCount(), 0ul);
//   ASSERT_EQ(l.getLineString(1), "");

//   str = "a:i32=1;\nfmain{\n exit 0;\n}";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer(buf);
//   ASSERT_EQ(l.isInterpreter(), false);
//   ASSERT_EQ(l.getLineCount(), 4ul);
//   ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
//   ASSERT_EQ(l.getLineString(4), "}");
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "a");
//   ASSERT_EQ(token.getLocation().getFilename(), "");
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);

//   str = "a:i32=1;\nfmain{\n exit 0;\n}\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer(buf);
//   ASSERT_EQ(l.isInterpreter(), false);
//   ASSERT_EQ(l.getLineCount(), 4ul);
//   ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
//   ASSERT_EQ(l.getLineString(4), "}\n");
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "a");
//   ASSERT_EQ(token.getLocation().getFilename(), "");
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);

//   // compiler from file
//   str = "a:i32=1;\nfmain{\n exit 0;\n}";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer(buf, "test.trot");
//   ASSERT_EQ(l.isInterpreter(), false);
//   ASSERT_EQ(l.getLineCount(), 4ul);
//   ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
//   ASSERT_EQ(l.getLineString(4), "}");
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "a");
//   ASSERT_EQ(token.getLocation().getFilename(), "test.trot");
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);

//   // interpreter
//   str = "a:i32=1;\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   ASSERT_EQ(l.isInterpreter(), true);
//   ASSERT_EQ(l.getLineCount(), 1ul);
//   ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "a");
//   ASSERT_EQ(token.getLocation().getFilename(), "");
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);
// };

// TEST_F(LexicalAnalyzerTest, Identifier) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = "$_simple\n";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "_simple");
//   ASSERT_EQ(token.getTokenLen(), 7ul);

//   str = "$16bin\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "16bin");
//   ASSERT_EQ(token.getTokenLen(), 5ul);

//   str = "-0e.0simple\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0e");
//   ASSERT_EQ(token.getTokenLen(), 2ul);
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "0simple");
//   ASSERT_EQ(token.getTokenLen(), 7ul);

//   str = "0.0simple\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "0simple");
//   ASSERT_EQ(token.getTokenLen(), 7ul);
// };

// // TEST_F(LexicalAnalyzerTest, SymbolCharacters) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   // arithmetic
// //   std::vector<char> buf;
// //   Token token;
// //   std::string str = "+";
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scPlus);
// //   ASSERT_EQ(token.getToken(), "+");

// //   str = "+%";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scPlusWrapping);
// //   ASSERT_EQ(token.getToken(), "+%");

// //   str = "+|";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scPlusSaturating); ASSERT_EQ(token.getToken(),
// //   "+|");

// //   str = "+=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scPlusAssign);
// //   ASSERT_EQ(token.getToken(), "+=");

// //   str = "+%=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scPlusWrappingAssign);
// //   ASSERT_EQ(token.getToken(), "+%=");

// //   str = "+|=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scPlusSaturatingAssign);
// //   ASSERT_EQ(token.getToken(), "+|=");

// //   str = "++";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scIncrement);
// //   ASSERT_EQ(token.getToken(), "++");

// //   str = "-";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scMinus);
// //   ASSERT_EQ(token.getToken(), "-");

// //   str = "-%";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scMinusWrapping); ASSERT_EQ(token.getToken(),
// //   "-%");

// //   str = "-|";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scMinusSaturating);
// ASSERT_EQ(token.getToken(),
// //   "-|");

// //   str = "-=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scMinusAssign);
// //   ASSERT_EQ(token.getToken(), "-=");

// //   str = "-%=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scMinusWrappingAssign);
// //   ASSERT_EQ(token.getToken(), "-%=");

// //   str = "-|=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scMinusSaturatingAssign);
// //   ASSERT_EQ(token.getToken(), "-|=");

// //   str = "--";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDecrement);
// //   ASSERT_EQ(token.getToken(), "--");

// //   str = "*";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scMultiple);
// //   ASSERT_EQ(token.getToken(), "*");

// //   str = "*%";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scMultipleWrapping);
// //   ASSERT_EQ(token.getToken(), "*%");

// //   str = "*|";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scMultipleSaturating);
// //   ASSERT_EQ(token.getToken(), "*|");

// //   str = "*=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scMultipleAssign);
// ASSERT_EQ(token.getToken(),
// //   "*=");

// //   str = "*%=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scMultipleWrappingAssign);
// //   ASSERT_EQ(token.getToken(), "*%=");

// //   str = "*|=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scMultipleSaturatingAssign);
// //   ASSERT_EQ(token.getToken(), "*|=");

// //   str = "*%=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scMultipleWrappingAssign);
// //   ASSERT_EQ(token.getToken(), "*%=");

// //   str = "/";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDivide);
// //   ASSERT_EQ(token.getToken(), "/");

// //   str = "/=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDivideAssign);
// //   ASSERT_EQ(token.getToken(), "/=");

// //   str = "%";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scModulo);
// //   ASSERT_EQ(token.getToken(), "%");

// //   str = "%=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scModuloAssign); ASSERT_EQ(token.getToken(),
// //   "%=");

// //   // bit , logical
// //   str = "&";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBitAnd);
// //   ASSERT_EQ(token.getToken(), "&");

// //   str = "&=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBitAndAssign);
// ASSERT_EQ(token.getToken(),
// //   "&=");

// //   str = "&&";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scLogicalAnd);
// //   ASSERT_EQ(token.getToken(), "&&");

// //   str = "&&=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scLogicalAndAssign);
// //   ASSERT_EQ(token.getToken(), "&&=");

// //   str = "|";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scBitOr);
// //   ASSERT_EQ(token.getToken(), "|");

// //   str = "|=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBitOrAssign);
// ASSERT_EQ(token.getToken(),
// //   "|=");

// //   str = "||";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scLogicalOr);
// //   ASSERT_EQ(token.getToken(), "||");

// //   str = "||=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scLogicalOrAssign);
// //   ASSERT_EQ(token.getToken(), "||=");

// //   str = "^";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scBitExOr);
// //   ASSERT_EQ(token.getToken(), "^");

// //   str = "^=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBitExOrAssign);
// //   ASSERT_EQ(token.getToken(), "^=");

// //   str = "~";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scBitNot);
// //   ASSERT_EQ(token.getToken(), "~");

// //   str = "!";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scLogicalNotUnary);
// //   ASSERT_EQ(token.getToken(), "!");

// //   str = "!=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scLogicalNotEqual);
// //   ASSERT_EQ(token.getToken(), "!=");

// //   str = "=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scAssignment);
// //   ASSERT_EQ(token.getToken(), "=");

// //   str = "==";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scLogicalEqual);
// //   ASSERT_EQ(token.getToken(), "==");

// //   str = "<";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scLessThan);
// //   ASSERT_EQ(token.getToken(), "<");

// //   str = "<=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scLessThanEqual);
// //   ASSERT_EQ(token.getToken(), "<=");

// //   str = "<<";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scBitShiftLeft);
// //   ASSERT_EQ(token.getToken(), "<<");

// //   str = "<<=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBitShiftLeftAssign);
// ASSERT_EQ(token.getToken(),
// //   "<<=");

// //   str = "<<|";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBitShiftLeftSaturating);
// //   ASSERT_EQ(token.getToken(), "<<|");

// //   str = "<<|=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBitShiftLeftSaturatingAssign);
// //   ASSERT_EQ(token.getToken(), "<<|=");

// //   str = ">";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scGreaterThan);
// //   ASSERT_EQ(token.getToken(), ">");

// //   str = ">=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scGreaterThanEqual); ASSERT_EQ(token.getToken(),
// //   ">=");

// //   str = ">>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scArithmeticBitShiftRight);
// ASSERT_EQ(token.getToken(),
// //   ">>");

// //   str = ">>=";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scArithmeticBitShiftRightAssign);
// //   ASSERT_EQ(token.getToken(), ">>=");

// //   // other
// //   str = "$";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDollar);
// //   ASSERT_EQ(token.getToken(), "$");

// //   str = "#";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scNumberSign);
// //   ASSERT_EQ(token.getToken(), "#");

// //   str = "?";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scQuestion);
// //   ASSERT_EQ(token.getToken(), "?");

// //   str = "@";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scAtSign);
// //   ASSERT_EQ(token.getToken(), "@");

// //   str = ":";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scColon);
// //   ASSERT_EQ(token.getToken(), ":");

// //   str = "::";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scNameSpaceSeparater);
// //   ASSERT_EQ(token.getToken(), "::");

// //   str = ";";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSemiColon);
// //   ASSERT_EQ(token.getToken(), ";");

// //   str = ",";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scComma);
// //   ASSERT_EQ(token.getToken(), ",");

// //   str = ".";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "..";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDotDot);
// //   ASSERT_EQ(token.getToken(), "..");

// //   str = "...";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDotDotDot);
// //   ASSERT_EQ(token.getToken(), "...");

// //   str = "\\";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackSlash);
// //   ASSERT_EQ(token.getToken(), "\\");

// //   str = "'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token.getToken(), "'");

// //   str = "\"\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token.getToken(), "\"");

// //   str = "`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token.getToken(), "`");

// //   str = "(";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scParenthesesOpen);
// //   ASSERT_EQ(token.getToken(), "(");

// //   str = ")";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scParenthesesClose);
// //   ASSERT_EQ(token.getToken(), ")");

// //   str = "{";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scCurlyBracketOpen);
// //   ASSERT_EQ(token.getToken(), "{");

// //   str = "}";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scCurlyBracketClose);
// //   ASSERT_EQ(token.getToken(), "}");

// //   str = "[";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scSquareBracketOpen);
// //   ASSERT_EQ(token.getToken(), "[");

// //   str = "]";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scSquareBracketClose);
// //   ASSERT_EQ(token.getToken(), "]");

// //   str = "//";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scOnelineCommentOut);
// //   ASSERT_EQ(token.getToken(), "//");

// //   str = "//<";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen);
// ASSERT_EQ(token.getToken(),
// //   "//<");

// //   str = "//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);
// //   ASSERT_EQ(token.getToken(), "//>");

// //   str = "/#";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scOnelineCommentOutDoc);
// //   ASSERT_EQ(token.getToken(), "/#");

// //   str = "/#<";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   ASSERT_EQ(token.getToken(), "/#<");

// //   str = "/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);
// //   ASSERT_EQ(token.getToken(), "/#>");
// // };

// TEST_F(LexicalAnalyzerTest, DecimalNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = "1234\n";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "1234");

//   str = "-12345\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token.getToken(), "-");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 2ul);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "12345");

//   str = "0\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 1ul);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "0");

//   str = "   \t -0\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 6ul);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token.getToken(), "-");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getLocation().getLine(), 1ul);
//   ASSERT_EQ(token.getLocation().getColumn(), 7ul);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "0");

//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "-1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token.getToken(), "-");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "-0.1\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scNegativeDecimal);
//   ASSERT_EQ(token.getToken(), "-");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "0");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "10.001\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token.getToken(), "001");

//   str = "10.\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "10.e+1\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 5ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token.getToken(), "e");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scPositiveDecimalExponent);
//   ASSERT_EQ(token.getToken(), "+");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "10.0e-2\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token.getToken(), "0");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token.getToken(), "e");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scNegativeDecimalExponent);
//   ASSERT_EQ(token.getToken(), "-");
//   token = tokens->get(5);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token.getToken(), "2");

//   str = "10.01e-2\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token.getToken(), "01");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token.getToken(), "e");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scNegativeDecimalExponent);
//   ASSERT_EQ(token.getToken(), "-");
//   token = tokens->get(5);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token.getToken(), "2");

//   str = "10.01e+2\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token.getToken(), "01");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token.getToken(), "e");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scPositiveDecimalExponent);
//   ASSERT_EQ(token.getToken(), "+");
//   token = tokens->get(5);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token.getToken(), "2");

//   str = "10.001e+2\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token.getToken(), "001");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalExponentOperator);
//   ASSERT_EQ(token.getToken(), "e");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::scPositiveDecimalExponent);
//   ASSERT_EQ(token.getToken(), "+");
//   token = tokens->get(5);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltExponentPart);
//   ASSERT_EQ(token.getToken(), "2");

//   str = "10.001e+\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "001e");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scPlus);
//   ASSERT_EQ(token.getToken(), "+");

//   str = "10.001e-\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "001e");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scMinus);
//   ASSERT_EQ(token.getToken(), "-");

//   str = "10.001e\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "001e");

//   str = "10.001ea\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "001ea");

//   str = "10.001a\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "10");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
//   ASSERT_EQ(token.getToken(), "001a");

//   str = "10a0_01a\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "10a0_01a");

//   str = "100_01";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "100_01");

//   str = "100_01.001001_0101";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "100_01");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
//   ASSERT_EQ(token.getToken(), ".");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalFractionalPart);
//   ASSERT_EQ(token.getToken(), "001001_0101");
// };

// TEST_F(LexicalAnalyzerTest, BinaryNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = "0b01001_0101\n";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltBinaryPrefix);
//   ASSERT_EQ(token.getToken(), "0b");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltBinaryIntegralPart);
//   ASSERT_EQ(token.getToken(), "01001_0101");

//   str = "0B01001_0101";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltBinaryPrefix);
//   ASSERT_EQ(token.getToken(), "0B");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltBinaryIntegralPart);
//   ASSERT_EQ(token.getToken(), "01001_0101");

//   str = "0b";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0b");

//   str = "0b2a\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0b2a");

//   str = "0b012\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0b012");
// };

// TEST_F(LexicalAnalyzerTest, OctalNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = "0o07422_263\n";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalPrefix);
//   ASSERT_EQ(token.getToken(), "0o");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
//   ASSERT_EQ(token.getToken(), "07422_263");

//   str = "0O07422_263";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalPrefix);
//   ASSERT_EQ(token.getToken(), "0O");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
//   ASSERT_EQ(token.getToken(), "07422_263");

//   str = "0o";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0o");

//   str = "0o738617\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalPrefix);
//   ASSERT_EQ(token.getToken(), "0o");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
//   ASSERT_EQ(token.getToken(), "73");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::ltDecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "8617");

//   str = "0o8617\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0o8617");

//   str = "0o78617\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0o78617");
// };

// TEST_F(LexicalAnalyzerTest, HexadecimalNumber) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = "0x91f7a74_38e4f\n";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltHexadecimalPrefix);
//   ASSERT_EQ(token.getToken(), "0x");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltHexadecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "91f7a74_38e4f");

//   str = "0X91F7A74_38E4F";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltHexadecimalPrefix);
//   ASSERT_EQ(token.getToken(), "0X");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltHexadecimalIntegralPart);
//   ASSERT_EQ(token.getToken(), "91F7A74_38E4F");

//   str = "0x";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0x");

//   str = "0xfeG8437f\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0xfeG8437f");

//   str = "0xG8437f\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);
//   ASSERT_EQ(token.getToken(), "0xG8437f");
// };

// // TEST_F(LexicalAnalyzerTest, CharCode) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = "''";
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'1\\\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "'1\\\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "'1\\\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "'1.\\\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   str = "1'.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token.getToken(), "'");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "'1\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1\n1");

// //   str = "'1\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1\r\n1");

// //   str = "'1\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "'1.\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   str = "1'.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token.getToken(), "'");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "'\\r'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'\\n'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'\\t'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'\\\\'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'\\''";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\'");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'\\o017371_3977'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
// //   ASSERT_EQ(token.getToken(), "\\o");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "017371");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "_3977");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token.getToken(), "'");

// //   str = "'\\x2f6a9bcf_fg839'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
// //   ASSERT_EQ(token.getToken(), "\\x");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token.getToken(), "'");

// //   str = "'\\u2f6a9bcf_fg839'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
// //   ASSERT_EQ(token.getToken(), "\\u");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   ASSERT_EQ(token.getToken(), "'");

// //   str = "''";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'⮕'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);

// //   str = "'鼻'";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltSingleCharacter);
// //   ASSERT_EQ(token.getToken(), "鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scSingleQuotation);
// // };

// // TEST_F(LexicalAnalyzerTest, String) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = "\"\"";
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"1\\\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "\"1\\\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "\"1\\\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "\"1.\\\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   str = "1\".";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token.getToken(), "\"");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "\"1\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1\n1");

// //   str = "\"1\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1\r\n1");

// //   str = "\"1\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "\"1.\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   str = "1\".";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token.getToken(), "\"");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "\"\\r\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"\\n\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"\\t\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"\\\\\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"\\\"\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\\"");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"\\o017371_3977\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
// //   ASSERT_EQ(token.getToken(), "\\o");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "017371");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "_3977");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token.getToken(), "\"");

// //   str = "\"\\x2f6a9bcf_fg839\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
// //   ASSERT_EQ(token.getToken(), "\\x");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token.getToken(), "\"");

// //   str = "\"\\u2f6a9bcf_fg839\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
// //   ASSERT_EQ(token.getToken(), "\\u");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   ASSERT_EQ(token.getToken(), "\"");

// //   str = "\"\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"⮕\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);

// //   str = "\"鼻\"";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltString);
// //   ASSERT_EQ(token.getToken(), "鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scDoubleQuotation);
// // };

// // TEST_F(LexicalAnalyzerTest, RawString) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = "``";
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`1\\\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "`1\\\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "`1\\\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "`1.\\\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   str = "1`.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token.getToken(), "`");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "`1\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1\n1");

// //   str = "`1\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1\r\n1");

// //   str = "`1\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "`1.\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   str = "1`.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token.getToken(), "`");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "`\\r`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`\\n`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`\\t`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`\\\\`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`\\``";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltEscapeSequence);
// //   ASSERT_EQ(token.getToken(), "\\`");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`\\o017371_3977`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
// //   ASSERT_EQ(token.getToken(), "\\o");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltOctalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "017371");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "_3977");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token.getToken(), "`");

// //   str = "`\\x2f6a9bcf_fg839`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
// //   ASSERT_EQ(token.getToken(), "\\x");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token.getToken(), "`");

// //   str = "`\\u2f6a9bcf_fg839`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
// //   ASSERT_EQ(token.getToken(), "\\u");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::ltHexadecimalIntegralPart);
// //   ASSERT_EQ(token.getToken(), "2f6a9bcf");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "_fg839");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   ASSERT_EQ(token.getToken(), "`");

// //   str = "``";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`⮕`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);

// //   str = "`鼻`";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::ltRawString);
// //   ASSERT_EQ(token.getToken(), "鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scBackQuotation);
// // };

// // TEST_F(LexicalAnalyzerTest, CommentOutOneline) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str = "//comment oneline\n";
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scOnelineCommentOut);
// //   ASSERT_EQ(token.getToken(), "//");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "comment oneline");

// //   str = "//comment oneline\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scOnelineCommentOut);
// //   ASSERT_EQ(token.getToken(), "//");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "comment oneline");

// //   str = "//comment oneline";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scOnelineCommentOut);
// //   ASSERT_EQ(token.getToken(), "//");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "comment oneline");

// //   str = "// comment oneline";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scOnelineCommentOut);
// //   ASSERT_EQ(token.getToken(), "//");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "comment oneline");

// //   str = "// \n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scOnelineCommentOut);
// //   ASSERT_EQ(token.getToken(), "//");

// //   str = "/#comment oneline for doc\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scOnelineCommentOutDoc);
// //   ASSERT_EQ(token.getToken(), "/#");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "comment oneline for doc");

// //   str = "/#comment oneline for doc\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scOnelineCommentOutDoc);
// //   ASSERT_EQ(token.getToken(), "/#");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "comment oneline for doc");

// //   str = "/#comment oneline for doc";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scOnelineCommentOutDoc);
// //   ASSERT_EQ(token.getToken(), "/#");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "comment oneline for doc");

// //   str = "//comment oneline\na@i32 = 11;";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// TokenTypeEnum::scOnelineCommentOut);
// //   ASSERT_EQ(token.getToken(), "//");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "comment oneline");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);

// //   str = "/#comment oneline for doc\na@i32 = 11;";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scOnelineCommentOutDoc);
// //   ASSERT_EQ(token.getToken(), "/#");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "comment oneline for doc");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);

// //   str = "/# comment oneline for doc\na@i32 = 11;";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scOnelineCommentOutDoc);
// //   ASSERT_EQ(token.getToken(), "/#");
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "comment oneline for doc");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::reservedWord);

// //   str = "/# \n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scOnelineCommentOutDoc);
// //   ASSERT_EQ(token.getToken(), "/#");
// // };

// // TEST_F(LexicalAnalyzerTest, CommentOutBlock) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = "//<//>";
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<1\\\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "//<1\\\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "//<1\\\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "//<1.\\\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   str = "1//>.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);
// //   ASSERT_EQ(token.getToken(), "//>");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "//<1\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1\n1");

// //   str = "//<1\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1\r\n1");

// //   str = "//<1\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "//<1.\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   str = "1//>.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);
// //   ASSERT_EQ(token.getToken(), "//>");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "//<\\r//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<\\n//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<\\t//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<\\\\//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<\\//>//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "\\//>");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<⮕//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<鼻//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutClose);

// //   str = "//<   \t\n\r\n1\n1\n\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1\n1\n\n");

// //   str = "//<   \t\n\r\n1\n1\n\n//>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //   TokenTypeEnum::scBlockCommentOutOpen); token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coString);
// //   ASSERT_EQ(token.getToken(), "1\n1");
// // };

// // TEST_F(LexicalAnalyzerTest, CommentOutBlockDock) {
// //   LexicalAnalyzer l;
// //   Tokens *tokens;

// //   std::vector<char> buf;
// //   Token token;
// //   std::string str;
// //   str = "/#</#>";
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<1\\\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "/#<1\\\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "/#<1\\\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "/#<1.\\\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   str = "1/#>.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1.");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);
// //   ASSERT_EQ(token.getToken(), "/#>");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "/#<1\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1\n1");

// //   str = "/#<1\r\n1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1\r\n1");

// //   str = "/#<1\r\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   str = "1";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1\r\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");

// //   str = "/#<1.\r";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   str = "1/#>.";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1.\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getLocation().getLine(), 2ul);
// //   ASSERT_EQ(token.getToken(), "1");
// //   token = tokens->get(3);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);
// //   ASSERT_EQ(token.getToken(), "/#>");
// //   token = tokens->get(4);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::scDot);
// //   ASSERT_EQ(token.getToken(), ".");

// //   str = "/#<\\r/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "\\r");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<\\n/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "\\n");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<\\t/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "\\t");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<\\\\/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "\\\\");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<\\/#>/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "\\/#>");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#</#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<⮕/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "⮕");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<鼻/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "鼻");
// //   token = tokens->get(2);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocClose);

// //   str = "/#<   \t\n\r\n1\n1\n\n";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1\n1\n\n");

// //   str = "/#<   \t\n\r\n1\n1\n\n/#>";
// //   buf.clear();
// //   std::copy(str.begin(), str.end(), std::back_inserter(buf));
// //   l = LexicalAnalyzer();
// //   l.tokenizeNextBuffer(buf);
// //   tokens = l.getTokens();
// //   token = tokens->get(0);
// //   ASSERT_EQ(token.getTokenType(),
// //             TokenTypeEnum::scBlockCommentOutDocOpen);
// //   token = tokens->get(1);
// //   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::coStringDoc);
// //   ASSERT_EQ(token.getToken(), "1\n1");
// // };
