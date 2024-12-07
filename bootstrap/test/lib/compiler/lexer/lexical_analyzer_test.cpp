#include "compiler/lexer/lexical_analyzer.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;

class LexicalAnalyzerTest : public ::testing::Test {};

TEST_F(LexicalAnalyzerTest, Constructor) {
  std::vector<char> buf;
  Tokens *tokens;
  Token token;
  // interpreter default
  LexicalAnalyzer l;
  ASSERT_EQ(l.isInterpreter(), true);
  ASSERT_EQ(l.getLineCount(), 0ul);
  ASSERT_EQ(l.getLineString(1), "");

  // compiler from stdin
  std::string str = "";
  str = "";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf);
  ASSERT_EQ(l.isInterpreter(), false);
  ASSERT_EQ(l.getLineCount(), 0ul);
  ASSERT_EQ(l.getLineString(1), "");

  str = "a:i32=1;\nfmain{\n exit 0;\n}";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf);
  ASSERT_EQ(l.isInterpreter(), false);
  ASSERT_EQ(l.getLineCount(), 4ul);
  ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
  ASSERT_EQ(l.getLineString(4), "}");
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "a");
  ASSERT_EQ(token.getLocation().getFilename(), "");
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);

  str = "a:i32=1;\nfmain{\n exit 0;\n}\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf);
  ASSERT_EQ(l.isInterpreter(), false);
  ASSERT_EQ(l.getLineCount(), 4ul);
  ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
  ASSERT_EQ(l.getLineString(4), "}\n");
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "a");
  ASSERT_EQ(token.getLocation().getFilename(), "");
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);

  // compiler from file
  str = "a:i32=1;\nfmain{\n exit 0;\n}";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf, "test.trot");
  ASSERT_EQ(l.isInterpreter(), false);
  ASSERT_EQ(l.getLineCount(), 4ul);
  ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
  ASSERT_EQ(l.getLineString(4), "}");
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "a");
  ASSERT_EQ(token.getLocation().getFilename(), "test.trot");
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);

  // interpreter
  str = "a:i32=1;\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  ASSERT_EQ(l.isInterpreter(), true);
  ASSERT_EQ(l.getLineCount(), 1ul);
  ASSERT_EQ(l.getLineString(1), "a:i32=1;\n");
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "a");
  ASSERT_EQ(token.getLocation().getFilename(), "");
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);
};

TEST_F(LexicalAnalyzerTest, Identifier) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "$_simple\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "_simple");
  ASSERT_EQ(token.getTokenLen(), 7ul);

  str = "$16bin\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "16bin");
  ASSERT_EQ(token.getTokenLen(), 5ul);

  str = "-0e.0simple\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0e");
  ASSERT_EQ(token.getTokenLen(), 2ul);
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "0simple");
  ASSERT_EQ(token.getTokenLen(), 7ul);

  str = "0.0simple\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "0simple");
  ASSERT_EQ(token.getTokenLen(), 7ul);
};

// TEST_F(LexicalAnalyzerTest, SymbolCharacters) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   // arithmetic
//   std::vector<char> buf;
//   Token token;
//   std::string str = "+";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlus);
//   ASSERT_EQ(token.getToken(), "+");

//   str = "+%";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusPercent);
//   ASSERT_EQ(token.getToken(), "+%");

//   str = "+|";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterPlusPipeline); ASSERT_EQ(token.getToken(),
//   "+|");

//   str = "+=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusEqual);
//   ASSERT_EQ(token.getToken(), "+=");

//   str = "+%=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterPlusPercentEqual);
//   ASSERT_EQ(token.getToken(), "+%=");

//   str = "+|=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterPlusPipelineEqual);
//   ASSERT_EQ(token.getToken(), "+|=");

//   str = "++";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusPlus);
//   ASSERT_EQ(token.getToken(), "++");

//   str = "-";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
//   ASSERT_EQ(token.getToken(), "-");

//   str = "-%";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterMinusPercent); ASSERT_EQ(token.getToken(),
//   "-%");

//   str = "-|";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterMinusPipeline); ASSERT_EQ(token.getToken(),
//   "-|");

//   str = "-=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinusEqual);
//   ASSERT_EQ(token.getToken(), "-=");

//   str = "-%=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterMinusPercentEqual);
//   ASSERT_EQ(token.getToken(), "-%=");

//   str = "-|=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterMinusPipelineEqual);
//   ASSERT_EQ(token.getToken(), "-|=");

//   str = "--";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinusMinus);
//   ASSERT_EQ(token.getToken(), "--");

//   str = "*";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAsterisk);
//   ASSERT_EQ(token.getToken(), "*");

//   str = "*%";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterAsteriskPercent);
//   ASSERT_EQ(token.getToken(), "*%");

//   str = "*|";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterAsteriskPipeline);
//   ASSERT_EQ(token.getToken(), "*|");

//   str = "*=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterAsteriskEqual); ASSERT_EQ(token.getToken(),
//   "*=");

//   str = "*%=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterAsteriskPercentEqual);
//   ASSERT_EQ(token.getToken(), "*%=");

//   str = "*|=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterAsteriskPipelineEqual);
//   ASSERT_EQ(token.getToken(), "*|=");

//   str = "*%=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterAsteriskPercentEqual);
//   ASSERT_EQ(token.getToken(), "*%=");

//   str = "/";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlash);
//   ASSERT_EQ(token.getToken(), "/");

//   str = "/=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashEqual);
//   ASSERT_EQ(token.getToken(), "/=");

//   str = "%";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPercent);
//   ASSERT_EQ(token.getToken(), "%");

//   str = "%=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterPercentEqual); ASSERT_EQ(token.getToken(),
//   "%=");

//   // bit , logical
//   str = "&";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAmpersand);
//   ASSERT_EQ(token.getToken(), "&");

//   str = "&=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterAmpersandEqual); ASSERT_EQ(token.getToken(),
//   "&=");

//   str = "&&";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterAmpersandAmpersand);
//   ASSERT_EQ(token.getToken(), "&&");

//   str = "&&=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterAmpersandAmpersandEqual);
//   ASSERT_EQ(token.getToken(), "&&=");

//   str = "|";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPipeline);
//   ASSERT_EQ(token.getToken(), "|");

//   str = "|=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterPipelineEqual); ASSERT_EQ(token.getToken(),
//   "|=");

//   str = "||";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterPipelinePipeline);
//   ASSERT_EQ(token.getToken(), "||");

//   str = "||=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterPipelinePipelineEqual);
//   ASSERT_EQ(token.getToken(), "||=");

//   str = "^";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterCaret);
//   ASSERT_EQ(token.getToken(), "^");

//   str = "^=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterCaretEqual);
//   ASSERT_EQ(token.getToken(), "^=");

//   str = "~";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterTilde);
//   ASSERT_EQ(token.getToken(), "~");

//   str = "!";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterExclamation);
//   ASSERT_EQ(token.getToken(), "!");

//   str = "!=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterExclamationEqual);
//   ASSERT_EQ(token.getToken(), "!=");

//   str = "=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterEqual);
//   ASSERT_EQ(token.getToken(), "=");

//   str = "==";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterEqualEqual);
//   ASSERT_EQ(token.getToken(), "==");

//   str = "<";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterLess);
//   ASSERT_EQ(token.getToken(), "<");

//   str = "<=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterLessEqual);
//   ASSERT_EQ(token.getToken(), "<=");

//   str = "<<";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterLessLess);
//   ASSERT_EQ(token.getToken(), "<<");

//   str = "<<=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterLessLessEqual); ASSERT_EQ(token.getToken(),
//   "<<=");

//   str = "<<|";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterLessLessPipeline);
//   ASSERT_EQ(token.getToken(), "<<|");

//   str = "<<|=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterLessLessPipelineEqual);
//   ASSERT_EQ(token.getToken(), "<<|=");

//   str = ">";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterGreater);
//   ASSERT_EQ(token.getToken(), ">");

//   str = ">=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterGreaterEqual); ASSERT_EQ(token.getToken(),
//   ">=");

//   str = ">>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterGreaterGreater); ASSERT_EQ(token.getToken(),
//   ">>");

//   str = ">>=";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterGreaterGreaterEqual);
//   ASSERT_EQ(token.getToken(), ">>=");

//   // other
//   str = "$";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoller);
//   ASSERT_EQ(token.getToken(), "$");

//   str = "#";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterNumbersign);
//   ASSERT_EQ(token.getToken(), "#");

//   str = "?";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterQuestion);
//   ASSERT_EQ(token.getToken(), "?");

//   str = "@";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAtmark);
//   ASSERT_EQ(token.getToken(), "@");

//   str = ":";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterColon);
//   ASSERT_EQ(token.getToken(), ":");

//   str = "::";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterColonColon);
//   ASSERT_EQ(token.getToken(), "::");

//   str = ";";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSemicolon);
//   ASSERT_EQ(token.getToken(), ";");

//   str = ",";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterComma);
//   ASSERT_EQ(token.getToken(), ",");

//   str = ".";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "..";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDotDot);
//   ASSERT_EQ(token.getToken(), "..");

//   str = "...";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDotDotDot);
//   ASSERT_EQ(token.getToken(), "...");

//   str = "\\";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackslash);
//   ASSERT_EQ(token.getToken(), "\\");

//   str = "'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   ASSERT_EQ(token.getToken(), "'");

//   str = "\"\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   ASSERT_EQ(token.getToken(), "\"");

//   str = "`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   ASSERT_EQ(token.getToken(), "`");

//   str = "(";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterLeftparentheses);
//   ASSERT_EQ(token.getToken(), "(");

//   str = ")";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterRightparentheses);
//   ASSERT_EQ(token.getToken(), ")");

//   str = "{";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterLeftcurlybrackets);
//   ASSERT_EQ(token.getToken(), "{");

//   str = "}";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterRightcurlybrackets);
//   ASSERT_EQ(token.getToken(), "}");

//   str = "[";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterLeftsquarebrackets);
//   ASSERT_EQ(token.getToken(), "[");

//   str = "]";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterRightsquarebrackets);
//   ASSERT_EQ(token.getToken(), "]");

//   str = "//";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getToken(), "//");

//   str = "//<";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); ASSERT_EQ(token.getToken(),
//   "//<");

//   str = "//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);
//   ASSERT_EQ(token.getToken(), "//>");

//   str = "/#";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersign);
//   ASSERT_EQ(token.getToken(), "/#");

//   str = "/#<";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   ASSERT_EQ(token.getToken(), "/#<");

//   str = "/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);
//   ASSERT_EQ(token.getToken(), "/#>");
// };

TEST_F(LexicalAnalyzerTest, DecimalNumber) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "1234\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "1234");

  str = "-12345\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimal);
  ASSERT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 2ul);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "12345");

  str = "0\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 1ul);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "0");

  str = "   \t -0\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 6ul);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimal);
  ASSERT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  ASSERT_EQ(token.getLocation().getLine(), 1ul);
  ASSERT_EQ(token.getLocation().getColumn(), 7ul);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "0");

  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "1");

  str = "-1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimal);
  ASSERT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "1");

  str = "-0.1\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimal);
  ASSERT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "0");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  ASSERT_EQ(token.getToken(), "1");

  str = "10.001\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  ASSERT_EQ(token.getToken(), "001");

  str = "10.\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 2ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");

  str = "10.e+1\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 5ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  ASSERT_EQ(token.getToken(), "e");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPositiveDecimalExponent);
  ASSERT_EQ(token.getToken(), "+");
  token = tokens->get(4);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  ASSERT_EQ(token.getToken(), "1");

  str = "10.0e-2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  ASSERT_EQ(token.getToken(), "0");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  ASSERT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimalExponent);
  ASSERT_EQ(token.getToken(), "-");
  token = tokens->get(5);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  ASSERT_EQ(token.getToken(), "2");

  str = "10.01e-2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  ASSERT_EQ(token.getToken(), "01");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  ASSERT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimalExponent);
  ASSERT_EQ(token.getToken(), "-");
  token = tokens->get(5);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  ASSERT_EQ(token.getToken(), "2");

  str = "10.01e+2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  ASSERT_EQ(token.getToken(), "01");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  ASSERT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPositiveDecimalExponent);
  ASSERT_EQ(token.getToken(), "+");
  token = tokens->get(5);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  ASSERT_EQ(token.getToken(), "2");

  str = "10.001e+2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 6ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  ASSERT_EQ(token.getToken(), "001");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  ASSERT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPositiveDecimalExponent);
  ASSERT_EQ(token.getToken(), "+");
  token = tokens->get(5);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  ASSERT_EQ(token.getToken(), "2");

  str = "10.001e+\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "001e");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlus);
  ASSERT_EQ(token.getToken(), "+");

  str = "10.001e-\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 4ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "001e");
  token = tokens->get(3);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  ASSERT_EQ(token.getToken(), "-");

  str = "10.001e\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "001e");

  str = "10.001ea\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "001ea");

  str = "10.001a\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  ASSERT_EQ(token.getToken(), "001a");

  str = "10a0_01a\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "10a0_01a");

  str = "100_01";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "100_01");

  str = "100_01.001001_0101";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  ASSERT_EQ(tokens->getParsableTokenCount(), 3ul);
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "100_01");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  ASSERT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  ASSERT_EQ(token.getToken(), "001001_0101");
};

TEST_F(LexicalAnalyzerTest, BinaryNumber) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "0b01001_0101\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryPrefix);
  ASSERT_EQ(token.getToken(), "0b");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryNumber);
  ASSERT_EQ(token.getToken(), "01001_0101");

  str = "0B01001_0101";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryPrefix);
  ASSERT_EQ(token.getToken(), "0B");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryNumber);
  ASSERT_EQ(token.getToken(), "01001_0101");

  str = "0b";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0b");

  str = "0b2a\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0b2a");

  str = "0b012\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0b012");
};

TEST_F(LexicalAnalyzerTest, OctalNumber) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "0o07422_263\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  ASSERT_EQ(token.getToken(), "0o");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  ASSERT_EQ(token.getToken(), "07422_263");

  str = "0O07422_263";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  ASSERT_EQ(token.getToken(), "0O");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  ASSERT_EQ(token.getToken(), "07422_263");

  str = "0o";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0o");

  str = "0o738617\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  ASSERT_EQ(token.getToken(), "0o");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  ASSERT_EQ(token.getToken(), "73");
  token = tokens->get(2);
  ASSERT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  ASSERT_EQ(token.getToken(), "8617");

  str = "0o8617\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0o8617");

  str = "0o78617\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0o78617");
};

TEST_F(LexicalAnalyzerTest, HexadecimalNumber) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "0x91f7a74_38e4f\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalPrefix);
  ASSERT_EQ(token.getToken(), "0x");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  ASSERT_EQ(token.getToken(), "91f7a74_38e4f");

  str = "0X91F7A74_38E4F";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalPrefix);
  ASSERT_EQ(token.getToken(), "0X");
  token = tokens->get(1);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  ASSERT_EQ(token.getToken(), "91F7A74_38E4F");

  str = "0x";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0x");

  str = "0xfeG8437f\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0xfeG8437f");

  str = "0xG8437f\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);
  ASSERT_EQ(token.getToken(), "0xG8437f");
};

// TEST_F(LexicalAnalyzerTest, CharCode) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str;
//   str = "''";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'1\\\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "'1\\\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "'1\\\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "'1.\\\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1.");
//   str = "1'.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1.");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   ASSERT_EQ(token.getToken(), "'");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "'1\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1\n1");

//   str = "'1\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1\r\n1");

//   str = "'1\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "'1.\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   str = "1'.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   ASSERT_EQ(token.getToken(), "'");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "'\\r'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'\\n'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'\\t'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\t");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'\\\\'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\\\");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'\\''";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\'");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'\\o017371_3977'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeOctalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\o");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
//   ASSERT_EQ(token.getToken(), "017371");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "_3977");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   ASSERT_EQ(token.getToken(), "'");

//   str = "'\\x2f6a9bcf_fg839'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeHexadecimalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\x");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
//   ASSERT_EQ(token.getToken(), "2f6a9bcf");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "_fg839");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   ASSERT_EQ(token.getToken(), "'");

//   str = "'\\u2f6a9bcf_fg839'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeUnicodePointEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\u");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
//   ASSERT_EQ(token.getToken(), "2f6a9bcf");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "_fg839");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   ASSERT_EQ(token.getToken(), "'");

//   str = "''";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'⮕'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "⮕");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

//   str = "'鼻'";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalCharCode);
//   ASSERT_EQ(token.getToken(), "鼻");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
// };

// TEST_F(LexicalAnalyzerTest, String) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str;
//   str = "\"\"";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"1\\\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "\"1\\\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "\"1\\\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "\"1.\\\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1.");
//   str = "1\".";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1.");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   ASSERT_EQ(token.getToken(), "\"");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "\"1\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1\n1");

//   str = "\"1\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1\r\n1");

//   str = "\"1\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "\"1.\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   str = "1\".";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   ASSERT_EQ(token.getToken(), "\"");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "\"\\r\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"\\n\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"\\t\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\t");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"\\\\\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\\\");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"\\\"\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\\"");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"\\o017371_3977\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeOctalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\o");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
//   ASSERT_EQ(token.getToken(), "017371");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "_3977");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   ASSERT_EQ(token.getToken(), "\"");

//   str = "\"\\x2f6a9bcf_fg839\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeHexadecimalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\x");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
//   ASSERT_EQ(token.getToken(), "2f6a9bcf");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "_fg839");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   ASSERT_EQ(token.getToken(), "\"");

//   str = "\"\\u2f6a9bcf_fg839\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeUnicodePointEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\u");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
//   ASSERT_EQ(token.getToken(), "2f6a9bcf");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "_fg839");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   ASSERT_EQ(token.getToken(), "\"");

//   str = "\"\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"⮕\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "⮕");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

//   str = "\"鼻\"";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
//   ASSERT_EQ(token.getToken(), "鼻");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
// };

// TEST_F(LexicalAnalyzerTest, RawString) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str;
//   str = "``";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`1\\\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "`1\\\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "`1\\\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "`1.\\\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1.");
//   str = "1`.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1.");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   ASSERT_EQ(token.getToken(), "`");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "`1\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1\n1");

//   str = "`1\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1\r\n1");

//   str = "`1\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "`1.\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   str = "1`.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   ASSERT_EQ(token.getToken(), "`");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "`\\r`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`\\n`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`\\t`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\t");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`\\\\`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\\\");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`\\``";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\`");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`\\o017371_3977`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeOctalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\o");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
//   ASSERT_EQ(token.getToken(), "017371");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "_3977");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   ASSERT_EQ(token.getToken(), "`");

//   str = "`\\x2f6a9bcf_fg839`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeHexadecimalEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\x");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
//   ASSERT_EQ(token.getToken(), "2f6a9bcf");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "_fg839");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   ASSERT_EQ(token.getToken(), "`");

//   str = "`\\u2f6a9bcf_fg839`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::literalCharCodeUnicodePointEscapeSequence);
//   ASSERT_EQ(token.getToken(), "\\u");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
//   ASSERT_EQ(token.getToken(), "2f6a9bcf");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "_fg839");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   ASSERT_EQ(token.getToken(), "`");

//   str = "``";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`⮕`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "⮕");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

//   str = "`鼻`";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::literalRawString);
//   ASSERT_EQ(token.getToken(), "鼻");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
// };

// TEST_F(LexicalAnalyzerTest, CommentOutOneline) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str = "//comment oneline\n";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getToken(), "//");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
//   ASSERT_EQ(token.getToken(), "comment oneline");

//   str = "//comment oneline\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getToken(), "//");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
//   ASSERT_EQ(token.getToken(), "comment oneline");

//   str = "//comment oneline";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getToken(), "//");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
//   ASSERT_EQ(token.getToken(), "comment oneline");

//   str = "// comment oneline";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getToken(), "//");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
//   ASSERT_EQ(token.getToken(), "comment oneline");

//   str = "// \n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getToken(), "//");

//   str = "/#comment oneline for doc\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersign);
//   ASSERT_EQ(token.getToken(), "/#");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
//   ASSERT_EQ(token.getToken(), "comment oneline for doc");

//   str = "/#comment oneline for doc\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersign);
//   ASSERT_EQ(token.getToken(), "/#");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
//   ASSERT_EQ(token.getToken(), "comment oneline for doc");

//   str = "/#comment oneline for doc";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersign);
//   ASSERT_EQ(token.getToken(), "/#");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
//   ASSERT_EQ(token.getToken(), "comment oneline for doc");

//   str = "//comment oneline\na@i32 = 11;";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
//   ASSERT_EQ(token.getToken(), "//");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
//   ASSERT_EQ(token.getToken(), "comment oneline");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);

//   str = "/#comment oneline for doc\na@i32 = 11;";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersign);
//   ASSERT_EQ(token.getToken(), "/#");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
//   ASSERT_EQ(token.getToken(), "comment oneline for doc");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);

//   str = "/# comment oneline for doc\na@i32 = 11;";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersign);
//   ASSERT_EQ(token.getToken(), "/#");
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
//   ASSERT_EQ(token.getToken(), "comment oneline for doc");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::keyword);

//   str = "/# \n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(tokens->getParsableTokenCount(), 1ul);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersign);
//   ASSERT_EQ(token.getToken(), "/#");
// };

// TEST_F(LexicalAnalyzerTest, CommentOutBlock) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str;
//   str = "//<//>";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<1\\\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "//<1\\\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "//<1\\\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "//<1.\\\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1.");
//   str = "1//>.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1.");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);
//   ASSERT_EQ(token.getToken(), "//>");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "//<1\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1\n1");

//   str = "//<1\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1\r\n1");

//   str = "//<1\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "//<1.\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   str = "1//>.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);
//   ASSERT_EQ(token.getToken(), "//>");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "//<\\r//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "\\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<\\n//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "\\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<\\t//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "\\t");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<\\\\//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "\\\\");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<\\//>//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "\\//>");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<⮕//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "⮕");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<鼻//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "鼻");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashSlashGreater);

//   str = "//<   \t\n\r\n1\n1\n\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1\n1\n\n");

//   str = "//<   \t\n\r\n1\n1\n\n//>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//   TokenTypeEnum::symbolCharacterSlashSlashLess); token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
//   ASSERT_EQ(token.getToken(), "1\n1");
// };

// TEST_F(LexicalAnalyzerTest, CommentOutBlockDock) {
//   LexicalAnalyzer l;
//   Tokens *tokens;

//   std::vector<char> buf;
//   Token token;
//   std::string str;
//   str = "/#</#>";
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<1\\\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "/#<1\\\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "/#<1\\\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "/#<1.\\\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1.");
//   str = "1/#>.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1.");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);
//   ASSERT_EQ(token.getToken(), "/#>");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "/#<1\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1\n1");

//   str = "/#<1\r\n1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1\r\n1");

//   str = "/#<1\r\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   str = "1";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1\r\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");

//   str = "/#<1.\r";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   str = "1/#>.";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1.\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getLocation().getLine(), 2ul);
//   ASSERT_EQ(token.getToken(), "1");
//   token = tokens->get(3);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);
//   ASSERT_EQ(token.getToken(), "/#>");
//   token = tokens->get(4);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
//   ASSERT_EQ(token.getToken(), ".");

//   str = "/#<\\r/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "\\r");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<\\n/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "\\n");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<\\t/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "\\t");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<\\\\/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "\\\\");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<\\/#>/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "\\/#>");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#</#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<⮕/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "⮕");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<鼻/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "鼻");
//   token = tokens->get(2);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

//   str = "/#<   \t\n\r\n1\n1\n\n";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1\n1\n\n");

//   str = "/#<   \t\n\r\n1\n1\n\n/#>";
//   buf.clear();
//   std::copy(str.begin(), str.end(), std::back_inserter(buf));
//   l = LexicalAnalyzer();
//   l.tokenizeNextBuffer(buf);
//   tokens = l.getTokens();
//   token = tokens->get(0);
//   ASSERT_EQ(token.getTokenType(),
//             TokenTypeEnum::symbolCharacterSlashNumbersignLess);
//   token = tokens->get(1);
//   ASSERT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
//   ASSERT_EQ(token.getToken(), "1\n1");
// };
