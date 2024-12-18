#if 0
#include "compiler/lexer/lexical_analyzer.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;

class LexicalAnalyzerTest : public ::testing::Test {};

TEST_F(LexicalAnalyzerTest, ConstructorCheck) {
  std::vector<char> buf;
  Tokens *tokens;
  Token token;
  // interpreter default
  LexicalAnalyzer l;
  EXPECT_EQ(l.getLexAnlzFlag(), 0ul);
  EXPECT_EQ(l.isInterpreter(), true);
  EXPECT_EQ(l.getLineCnt(), 0ul);
  EXPECT_EQ(l.getLineString(1), "");

  // compiler from stdin
  std::string str = "";
  str = "";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf);
  EXPECT_EQ(l.getLexAnlzFlag(), 0ul);
  EXPECT_EQ(l.isInterpreter(), false);
  EXPECT_EQ(l.getLineCnt(), 0ul);
  EXPECT_EQ(l.getLineString(1), "");

  str = "a:i32=1;\nfmain{\n exit 0;\n}";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf);
  EXPECT_EQ(l.getLexAnlzFlag(), 0ul);
  EXPECT_EQ(l.isInterpreter(), false);
  EXPECT_EQ(l.getLineCnt(), 4ul);
  EXPECT_EQ(l.getLineString(1), "a:i32=1;\n");
  EXPECT_EQ(l.getLineString(4), "}");
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "a");
  EXPECT_EQ(token.getLocation().getFilename(), "");
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);

  str = "a:i32=1;\nfmain{\n exit 0;\n}\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf);
  EXPECT_EQ(l.getLexAnlzFlag(), 0ul);
  EXPECT_EQ(l.isInterpreter(), false);
  EXPECT_EQ(l.getLineCnt(), 4ul);
  EXPECT_EQ(l.getLineString(1), "a:i32=1;\n");
  EXPECT_EQ(l.getLineString(4), "}\n");
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "a");
  EXPECT_EQ(token.getLocation().getFilename(), "");
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);

  // compiler from file
  str = "a:i32=1;\nfmain{\n exit 0;\n}";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer(buf, "test.trot");
  EXPECT_EQ(l.getLexAnlzFlag(), 0ul);
  EXPECT_EQ(l.isInterpreter(), false);
  EXPECT_EQ(l.getLineCnt(), 4ul);
  EXPECT_EQ(l.getLineString(1), "a:i32=1;\n");
  EXPECT_EQ(l.getLineString(4), "}");
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "a");
  EXPECT_EQ(token.getLocation().getFilename(), "test.trot");
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);

  // interpreter
  str = "a:i32=1;\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  EXPECT_EQ(l.getLexAnlzFlag(), 0ul);
  EXPECT_EQ(l.isInterpreter(), true);
  EXPECT_EQ(l.getLineCnt(), 1ul);
  EXPECT_EQ(l.getLineString(1), "a:i32=1;\n");
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "a");
  EXPECT_EQ(token.getLocation().getFilename(), "");
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);
};

TEST_F(LexicalAnalyzerTest, IdentifierCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "_simple\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "_simple");
  EXPECT_EQ(token.getTokenLen(), 7ul);
};

TEST_F(LexicalAnalyzerTest, SymbolCharactersCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  // arithmetic
  std::vector<char> buf;
  Token token;
  std::string str = "+";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlus);
  EXPECT_EQ(token.getToken(), "+");

  str = "+%";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusPercent);
  EXPECT_EQ(token.getToken(), "+%");

  str = "+|";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusPipeline);
  EXPECT_EQ(token.getToken(), "+|");

  str = "+=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusEqual);
  EXPECT_EQ(token.getToken(), "+=");

  str = "+%=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPlusPercentEqual);
  EXPECT_EQ(token.getToken(), "+%=");

  str = "+|=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPlusPipelineEqual);
  EXPECT_EQ(token.getToken(), "+|=");

  str = "++";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlusPlus);
  EXPECT_EQ(token.getToken(), "++");

  str = "-";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(token.getToken(), "-");

  str = "-%";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinusPercent);
  EXPECT_EQ(token.getToken(), "-%");

  str = "-|";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinusPipeline);
  EXPECT_EQ(token.getToken(), "-|");

  str = "-=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinusEqual);
  EXPECT_EQ(token.getToken(), "-=");

  str = "-%=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterMinusPercentEqual);
  EXPECT_EQ(token.getToken(), "-%=");

  str = "-|=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterMinusPipelineEqual);
  EXPECT_EQ(token.getToken(), "-|=");

  str = "--";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinusMinus);
  EXPECT_EQ(token.getToken(), "--");

  str = "*";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAsterisk);
  EXPECT_EQ(token.getToken(), "*");

  str = "*%";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterAsteriskPercent);
  EXPECT_EQ(token.getToken(), "*%");

  str = "*|";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterAsteriskPipeline);
  EXPECT_EQ(token.getToken(), "*|");

  str = "*=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAsteriskEqual);
  EXPECT_EQ(token.getToken(), "*=");

  str = "*%=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterAsteriskPercentEqual);
  EXPECT_EQ(token.getToken(), "*%=");

  str = "*|=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterAsteriskPipelineEqual);
  EXPECT_EQ(token.getToken(), "*|=");

  str = "*%=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterAsteriskPercentEqual);
  EXPECT_EQ(token.getToken(), "*%=");

  str = "/";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlash);
  EXPECT_EQ(token.getToken(), "/");

  str = "/=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashEqual);
  EXPECT_EQ(token.getToken(), "/=");

  str = "%";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPercent);
  EXPECT_EQ(token.getToken(), "%");

  str = "%=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPercentEqual);
  EXPECT_EQ(token.getToken(), "%=");

  // bit , logical
  str = "&";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAmpersand);
  EXPECT_EQ(token.getToken(), "&");

  str = "&=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAmpersandEqual);
  EXPECT_EQ(token.getToken(), "&=");

  str = "&&";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterAmpersandAmpersand);
  EXPECT_EQ(token.getToken(), "&&");

  str = "&&=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterAmpersandAmpersandEqual);
  EXPECT_EQ(token.getToken(), "&&=");

  str = "|";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPipeline);
  EXPECT_EQ(token.getToken(), "|");

  str = "|=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPipelineEqual);
  EXPECT_EQ(token.getToken(), "|=");

  str = "||";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPipelinePipeline);
  EXPECT_EQ(token.getToken(), "||");

  str = "||=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPipelinePipelineEqual);
  EXPECT_EQ(token.getToken(), "||=");

  str = "^";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterCaret);
  EXPECT_EQ(token.getToken(), "^");

  str = "^=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterCaretEqual);
  EXPECT_EQ(token.getToken(), "^=");

  str = "~";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterTilde);
  EXPECT_EQ(token.getToken(), "~");

  str = "!";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterExclamation);
  EXPECT_EQ(token.getToken(), "!");

  str = "!=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterExclamationEqual);
  EXPECT_EQ(token.getToken(), "!=");

  str = "=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterEqual);
  EXPECT_EQ(token.getToken(), "=");

  str = "==";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterEqualEqual);
  EXPECT_EQ(token.getToken(), "==");

  str = "<";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterLess);
  EXPECT_EQ(token.getToken(), "<");

  str = "<=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterLessEqual);
  EXPECT_EQ(token.getToken(), "<=");

  str = "<<";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterLessLess);
  EXPECT_EQ(token.getToken(), "<<");

  str = "<<=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterLessLessEqual);
  EXPECT_EQ(token.getToken(), "<<=");

  str = "<<|";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterLessLessPipeline);
  EXPECT_EQ(token.getToken(), "<<|");

  str = "<<|=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterLessLessPipelineEqual);
  EXPECT_EQ(token.getToken(), "<<|=");

  str = ">";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterGreater);
  EXPECT_EQ(token.getToken(), ">");

  str = ">=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterGreaterEqual);
  EXPECT_EQ(token.getToken(), ">=");

  str = ">>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterGreaterGreater);
  EXPECT_EQ(token.getToken(), ">>");

  str = ">>=";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterGreaterGreaterEqual);
  EXPECT_EQ(token.getToken(), ">>=");

  // other
  str = "$";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoller);
  EXPECT_EQ(token.getToken(), "$");

  str = "#";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterNumbersign);
  EXPECT_EQ(token.getToken(), "#");

  str = "?";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterQuestion);
  EXPECT_EQ(token.getToken(), "?");

  str = "@";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterAtmark);
  EXPECT_EQ(token.getToken(), "@");

  str = ":";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterColon);
  EXPECT_EQ(token.getToken(), ":");

  str = "::";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterColonColon);
  EXPECT_EQ(token.getToken(), "::");

  str = ";";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSemicolon);
  EXPECT_EQ(token.getToken(), ";");

  str = ",";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterComma);
  EXPECT_EQ(token.getToken(), ",");

  str = ".";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");

  str = "..";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDotDot);
  EXPECT_EQ(token.getToken(), "..");

  str = "...";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDotDotDot);
  EXPECT_EQ(token.getToken(), "...");

  str = "\\";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackslash);
  EXPECT_EQ(token.getToken(), "\\");

  str = "'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  EXPECT_EQ(token.getToken(), "'");

  str = "\"\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  EXPECT_EQ(token.getToken(), "\"");

  str = "`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  EXPECT_EQ(token.getToken(), "`");

  str = "(";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterLeftparentheses);
  EXPECT_EQ(token.getToken(), "(");

  str = ")";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterRightparentheses);
  EXPECT_EQ(token.getToken(), ")");

  str = "{";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterLeftcurlybrackets);
  EXPECT_EQ(token.getToken(), "{");

  str = "}";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterRightcurlybrackets);
  EXPECT_EQ(token.getToken(), "}");

  str = "[";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterLeftsquarebrackets);
  EXPECT_EQ(token.getToken(), "[");

  str = "]";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterRightsquarebrackets);
  EXPECT_EQ(token.getToken(), "]");

  str = "//";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getToken(), "//");

  str = "//<";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  EXPECT_EQ(token.getToken(), "//<");

  str = "//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);
  EXPECT_EQ(token.getToken(), "//>");

  str = "/#";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersign);
  EXPECT_EQ(token.getToken(), "/#");

  str = "/#<";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  EXPECT_EQ(token.getToken(), "/#<");

  str = "/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);
  EXPECT_EQ(token.getToken(), "/#>");
};

TEST_F(LexicalAnalyzerTest, DecimalNumberCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "1234\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 1ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "1234");

  str = "-12345\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 2ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 2ul);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "12345");

  str = "0\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 1ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 1ul);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "0");

  str = "   \t -0\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 2ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 6ul);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  EXPECT_EQ(token.getLocation().getLine(), 1ul);
  EXPECT_EQ(token.getLocation().getColumn(), 7ul);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "0");

  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 1ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "1");

  str = "-1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 2ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "1");

  str = "-0.1\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 4ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(token.getToken(), "-");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "0");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "1");

  str = "10.001\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 3ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001");

  str = "10.\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 2ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");

  str = "10.e+1\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 5ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  EXPECT_EQ(token.getToken(), "e");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPositiveDecimalExponent);
  EXPECT_EQ(token.getToken(), "+");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  EXPECT_EQ(token.getToken(), "1");

  str = "10.0e-2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 6ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "0");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  EXPECT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimalExponent);
  EXPECT_EQ(token.getToken(), "-");
  token = tokens->get(5);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  EXPECT_EQ(token.getToken(), "2");

  str = "10.01e-2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 6ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "01");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  EXPECT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterNegativeDecimalExponent);
  EXPECT_EQ(token.getToken(), "-");
  token = tokens->get(5);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  EXPECT_EQ(token.getToken(), "2");

  str = "10.01e+2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 6ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "01");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  EXPECT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPositiveDecimalExponent);
  EXPECT_EQ(token.getToken(), "+");
  token = tokens->get(5);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  EXPECT_EQ(token.getToken(), "2");

  str = "10.001e+2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 6ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  EXPECT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterPositiveDecimalExponent);
  EXPECT_EQ(token.getToken(), "+");
  token = tokens->get(5);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentPart);
  EXPECT_EQ(token.getToken(), "2");

  str = "10.001e+\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 5ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  EXPECT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterPlus);
  EXPECT_EQ(token.getToken(), "+");

  str = "10.001e-\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 5ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberExponentOperator);
  EXPECT_EQ(token.getToken(), "e");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterMinus);
  EXPECT_EQ(token.getToken(), "-");

  str = "10.001e\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 4ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "e");

  str = "10.001ea\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 4ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "ea");

  str = "10.001a\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 4ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "a");

  str = "10a0_01a\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 2ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "10");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "a0_01a");

  str = "100_01";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 1ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "100_01");

  str = "100_01.001001_0101";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  EXPECT_EQ(tokens->getTokenCnt(), 3ul);
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "100_01");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberDecimalPart);
  EXPECT_EQ(token.getToken(), "001001_0101");
};

TEST_F(LexicalAnalyzerTest, BinaryNumberCheck) {
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
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryPrefix);
  EXPECT_EQ(token.getToken(), "0b");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryNumber);
  EXPECT_EQ(token.getToken(), "01001_0101");

  str = "0B01001_0101";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryPrefix);
  EXPECT_EQ(token.getToken(), "0B");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryNumber);
  EXPECT_EQ(token.getToken(), "01001_0101");

  str = "0b";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryPrefix);
  EXPECT_EQ(token.getToken(), "0b");

  str = "0b012\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryPrefix);
  EXPECT_EQ(token.getToken(), "0b");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryNumber);
  EXPECT_EQ(token.getToken(), "01");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "2");

  str = "0b2\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalBinaryPrefix);
  EXPECT_EQ(token.getToken(), "0b");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "2");
};

TEST_F(LexicalAnalyzerTest, OctalNumberCheck) {
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
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  EXPECT_EQ(token.getToken(), "0o");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  EXPECT_EQ(token.getToken(), "07422_263");

  str = "0O07422_263";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  EXPECT_EQ(token.getToken(), "0O");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  EXPECT_EQ(token.getToken(), "07422_263");

  str = "0o";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  EXPECT_EQ(token.getToken(), "0o");

  str = "0o738617\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  EXPECT_EQ(token.getToken(), "0o");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  EXPECT_EQ(token.getToken(), "73");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "8617");

  str = "0o8617\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalPrefix);
  EXPECT_EQ(token.getToken(), "0o");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalDecimalNumberIntegralPart);
  EXPECT_EQ(token.getToken(), "8617");
};

TEST_F(LexicalAnalyzerTest, HexadecimalNumberCheck) {
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
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalPrefix);
  EXPECT_EQ(token.getToken(), "0x");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "91f7a74_38e4f");

  str = "0X91F7A74_38E4F";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalPrefix);
  EXPECT_EQ(token.getToken(), "0X");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "91F7A74_38E4F");

  str = "0x";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalPrefix);
  EXPECT_EQ(token.getToken(), "0x");

  str = "0xfeG8437f\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalPrefix);
  EXPECT_EQ(token.getToken(), "0x");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "fe");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "G8437f");

  str = "0xG8437f\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalPrefix);
  EXPECT_EQ(token.getToken(), "0x");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);
  EXPECT_EQ(token.getToken(), "G8437f");
};

TEST_F(LexicalAnalyzerTest, RuneCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str;
  str = "''";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'1\\\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "'1\\\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "'1\\\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "'1.\\\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1.");
  str = "1'.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1.");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  EXPECT_EQ(token.getToken(), "'");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");

  str = "'1\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1\n1");

  str = "'1\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1\r\n1");

  str = "'1\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1\r\n");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1\r\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "'1.\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1.\r");
  EXPECT_EQ(l.isLexAnlzContinue(), true);
  str = "1'.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "1.\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  EXPECT_EQ(token.getToken(), "'");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  EXPECT_EQ(l.isLexAnlzContinue(), false);

  str = "'\\r'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'\\n'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'\\t'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\t");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'\\\\'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\\\");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'\\''";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\'");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'\\o017371_3977'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneOctalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\o");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  EXPECT_EQ(token.getToken(), "017371");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "_3977");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  EXPECT_EQ(token.getToken(), "'");

  str = "'\\x2f6a9bcf_fg839'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneHexadecimalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\x");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "2f6a9bcf");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "_fg839");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  EXPECT_EQ(token.getToken(), "'");

  str = "'\\u2f6a9bcf_fg839'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneUnicodePointEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\u");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "2f6a9bcf");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "_fg839");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  EXPECT_EQ(token.getToken(), "'");

  str = "''";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'⮕'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "⮕");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);

  str = "'鼻'";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalRune);
  EXPECT_EQ(token.getToken(), "鼻");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSinglequote);
};

TEST_F(LexicalAnalyzerTest, StringCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str;
  str = "\"\"";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"1\\\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "\"1\\\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "\"1\\\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "\"1.\\\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1.");
  str = "1\".";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1.");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  EXPECT_EQ(token.getToken(), "\"");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");

  str = "\"1\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1\n1");

  str = "\"1\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1\r\n1");

  str = "\"1\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1\r\n");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1\r\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "\"1.\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1.\r");
  EXPECT_EQ(l.isLexAnlzContinue(), true);
  str = "1\".";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "1.\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  EXPECT_EQ(token.getToken(), "\"");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  EXPECT_EQ(l.isLexAnlzContinue(), false);

  str = "\"\\r\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"\\n\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"\\t\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\t");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"\\\\\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\\\");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"\\\"\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\\"");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"\\o017371_3977\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneOctalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\o");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  EXPECT_EQ(token.getToken(), "017371");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "_3977");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  EXPECT_EQ(token.getToken(), "\"");

  str = "\"\\x2f6a9bcf_fg839\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneHexadecimalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\x");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "2f6a9bcf");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "_fg839");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  EXPECT_EQ(token.getToken(), "\"");

  str = "\"\\u2f6a9bcf_fg839\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneUnicodePointEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\u");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "2f6a9bcf");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "_fg839");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  EXPECT_EQ(token.getToken(), "\"");

  str = "\"\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"⮕\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "⮕");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);

  str = "\"鼻\"";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalString);
  EXPECT_EQ(token.getToken(), "鼻");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDoublequote);
};

TEST_F(LexicalAnalyzerTest, RegularExpressionPatternCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str;
  str = "``";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`1\\\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "`1\\\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "`1\\\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "`1.\\\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1.");
  str = "1`.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1.");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  EXPECT_EQ(token.getToken(), "`");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");

  str = "`1\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1\n1");

  str = "`1\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1\r\n1");

  str = "`1\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1\r\n");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1\r\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "`1.\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1.\r");
  EXPECT_EQ(l.isLexAnlzContinue(), true);
  str = "1`.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "1.\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  EXPECT_EQ(token.getToken(), "`");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  EXPECT_EQ(l.isLexAnlzContinue(), false);

  str = "`\\r`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`\\n`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`\\t`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\t");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`\\\\`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\\\");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`\\``";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\`");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`\\o017371_3977`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneOctalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\o");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalOctalNumber);
  EXPECT_EQ(token.getToken(), "017371");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "_3977");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  EXPECT_EQ(token.getToken(), "`");

  str = "`\\x2f6a9bcf_fg839`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneHexadecimalEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\x");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "2f6a9bcf");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "_fg839");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  EXPECT_EQ(token.getToken(), "`");

  str = "`\\u2f6a9bcf_fg839`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRuneUnicodePointEscapeSequence);
  EXPECT_EQ(token.getToken(), "\\u");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::literalHexadecimalNumber);
  EXPECT_EQ(token.getToken(), "2f6a9bcf");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "_fg839");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  EXPECT_EQ(token.getToken(), "`");

  str = "``";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`⮕`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "⮕");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);

  str = "`鼻`";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::literalRegularExpressionPattern);
  EXPECT_EQ(token.getToken(), "鼻");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterBackquote);
};

TEST_F(LexicalAnalyzerTest, CommentOutOnelineCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str = "//comment oneline\n";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getToken(), "//");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
  EXPECT_EQ(token.getToken(), "comment oneline");

  str = "//comment oneline\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getToken(), "//");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
  EXPECT_EQ(token.getToken(), "comment oneline");

  str = "//comment oneline";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getToken(), "//");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
  EXPECT_EQ(token.getToken(), "comment oneline");

  str = "// comment oneline";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getToken(), "//");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
  EXPECT_EQ(token.getToken(), "comment oneline");

  str = "// \n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(tokens->getTokenCnt(), 1ul);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getToken(), "//");

  str = "/#comment oneline for doc\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersign);
  EXPECT_EQ(token.getToken(), "/#");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
  EXPECT_EQ(token.getToken(), "comment oneline for doc");

  str = "/#comment oneline for doc\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersign);
  EXPECT_EQ(token.getToken(), "/#");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
  EXPECT_EQ(token.getToken(), "comment oneline for doc");

  str = "/#comment oneline for doc";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersign);
  EXPECT_EQ(token.getToken(), "/#");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
  EXPECT_EQ(token.getToken(), "comment oneline for doc");

  str = "//comment oneline\na@i32 = 11;";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlash);
  EXPECT_EQ(token.getToken(), "//");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOneline);
  EXPECT_EQ(token.getToken(), "comment oneline");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);

  str = "/#comment oneline for doc\na@i32 = 11;";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersign);
  EXPECT_EQ(token.getToken(), "/#");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
  EXPECT_EQ(token.getToken(), "comment oneline for doc");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);

  str = "/# comment oneline for doc\na@i32 = 11;";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersign);
  EXPECT_EQ(token.getToken(), "/#");
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutOnelineDoc);
  EXPECT_EQ(token.getToken(), "comment oneline for doc");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::identifier);

  str = "/# \n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(tokens->getTokenCnt(), 1ul);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersign);
  EXPECT_EQ(token.getToken(), "/#");
};

TEST_F(LexicalAnalyzerTest, CommentOutBlockCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str;
  str = "//<//>";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<1\\\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "//<1\\\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "//<1\\\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "//<1.\\\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1.");
  str = "1//>.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1.");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);
  EXPECT_EQ(token.getToken(), "//>");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");

  str = "//<1\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1\n1");

  str = "//<1\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1\r\n1");

  str = "//<1\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1\r\n");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1\r\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "//<1.\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1.\r");
  EXPECT_EQ(l.isLexAnlzContinue(), true);
  str = "1//>.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1.\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);
  EXPECT_EQ(token.getToken(), "//>");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  EXPECT_EQ(l.isLexAnlzContinue(), false);

  str = "//<\\r//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "\\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<\\n//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "\\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<\\t//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "\\t");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<\\\\//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "\\\\");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<\\//>//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "\\//>");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<⮕//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "⮕");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<鼻//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "鼻");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashSlashGreater);

  str = "//<   \t\n\r\n1\n1\n\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1\n1\n\n");

  str = "//<   \t\n\r\n1\n1\n\n//>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterSlashSlashLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlock);
  EXPECT_EQ(token.getToken(), "1\n1");
};

TEST_F(LexicalAnalyzerTest, CommentOutBlockDockCheck) {
  LexicalAnalyzer l;
  Tokens *tokens;

  std::vector<char> buf;
  Token token;
  std::string str;
  str = "/#</#>";
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<1\\\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "/#<1\\\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "/#<1\\\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "/#<1.\\\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1.");
  str = "1/#>.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1.");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);
  EXPECT_EQ(token.getToken(), "/#>");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");

  str = "/#<1\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1\n1");

  str = "/#<1\r\n1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1\r\n1");

  str = "/#<1\r\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1\r\n");
  str = "1";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1\r\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");

  str = "/#<1.\r";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1.\r");
  EXPECT_EQ(l.isLexAnlzContinue(), true);
  str = "1/#>.";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1.\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getLocation().getLine(), 2ul);
  EXPECT_EQ(token.getToken(), "1");
  token = tokens->get(3);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);
  EXPECT_EQ(token.getToken(), "/#>");
  token = tokens->get(4);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::symbolCharacterDot);
  EXPECT_EQ(token.getToken(), ".");
  EXPECT_EQ(l.isLexAnlzContinue(), false);

  str = "/#<\\r/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "\\r");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<\\n/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "\\n");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<\\t/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "\\t");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<\\\\/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "\\\\");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<\\/#>/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "\\/#>");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#</#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<⮕/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "⮕");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<鼻/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "鼻");
  token = tokens->get(2);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignGreater);

  str = "/#<   \t\n\r\n1\n1\n\n";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1\n1\n\n");

  str = "/#<   \t\n\r\n1\n1\n\n/#>";
  buf.clear();
  std::copy(str.begin(), str.end(), std::back_inserter(buf));
  l = LexicalAnalyzer();
  l.tokenizeNextBuffer(buf);
  tokens = l.getTokens();
  token = tokens->get(0);
  EXPECT_EQ(token.getTokenType(),
            TokenTypeEnum::symbolCharacterSlashNumbersignLess);
  token = tokens->get(1);
  EXPECT_EQ(token.getTokenType(), TokenTypeEnum::commentOutBlockDoc);
  EXPECT_EQ(token.getToken(), "1\n1");
};

#endif