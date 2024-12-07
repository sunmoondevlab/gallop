// Copyright © 2024- Sunmoon development laboratory. Allexer Rights Reserved.
#ifndef _LEXICAL_ANALYZER_TEST_CPP_STRING_INC_
#define _LEXICAL_ANALYZER_TEST_CPP_STRING_INC_

#include "compiler/controller/lexical_analyzer.hpp"

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

class LexicalAnalyzerTest;

TEST_F(LexicalAnalyzerTest, String) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"\"\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\" 1\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U" 1");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\" 1\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U" 1");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltStringLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");

  str = U"\"\r\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltStringLineBreak);
  ASSERT_EQ(token->getToken(), U"\r");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\n\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltStringLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\" \"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(escapeCharCode, nullptr);
  }

  str = U"\"\\\"\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\\\"");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::DoubleQuotation));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\\"\r\n\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\\\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltStringLineBreak);
  ASSERT_EQ(token->getToken(), U"\r\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"36044\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::interpreter);
  lexer.tokenizeNextBuffer(buf);
  str = U"100200\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lexer.tokenizeNextBuffer(buf);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"36044");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltStringLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"100200");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  string literal separotor(\"), location::[1,1],\n"
            "  string literal: \"36044\" , location::[1,2],\n"
            "  line break(\\r,\\n) of string literal:  , location::[1,7],\n"
            "  string literal: \"100200\" , location::[2,1],\n"
            "  string literal separotor(\"), location::[2,7],\n"
            "]\n");

  str = U"\"\\a\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceBellAlert);
  ASSERT_EQ(token->getToken(), U"\\a");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::BellAlert));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\b\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceBackspace);
  ASSERT_EQ(token->getToken(), U"\\b");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\t\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceHorizontalTab);
  ASSERT_EQ(token->getToken(), U"\\t");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\n\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceLineFeed);
  ASSERT_EQ(token->getToken(), U"\\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\v\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceVerticalTab);
  ASSERT_EQ(token->getToken(), U"\\v");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\f\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceFormFeed);
  ASSERT_EQ(token->getToken(), U"\\f");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\r\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceCarriageReturn);
  ASSERT_EQ(token->getToken(), U"\\r");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\e\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceAnsiEscape);
  ASSERT_EQ(token->getToken(), U"\\e");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\\\\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceBackSlash);
  ASSERT_EQ(token->getToken(), U"\\\\");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\0\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceNullChar);
  ASSERT_EQ(token->getToken(), U"\\0");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\\"aaaa\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\\\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"aaaa");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\\r\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "\"\\\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"\"\\o\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "\"\\o\"\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"\"\\o8\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "\"\\o8\"\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"\"\\o{1\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "\"\\o{1\"\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"\"\\o{36044100177}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid UTF-8 octal character code. at :1:5\n"
                 "\"\\o{36044100177}\"\n"
                 "    ^^^^^^^^^^^\n",
                 err->what());
    delete err;
  }

  str = U"\"\\o{36044100200}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"36044100200");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  ASSERT_EQ(
      tis.toStringPrintTokens(true),

      "[\n"
      "  string literal separotor(\"), location::[1,1],\n"
      "  escape sequence UTF-8 octal code(\\o): '\\o' , location::[1,2],\n"
      "  UTF code open'{': '{' , location::[1,4],\n"
      "  UTF-8 octal code(\\o): '36044100200' , location::[1,5],\n"
      "  UTF code close'}': '}' , location::[1,16],\n"
      "  string literal separotor(\"), location::[1,17],\n"
      "]\n");

  str = U"\"\\o{0000000}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0000000");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000007}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"0000007");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000010}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"0000010");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000011}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"0000011");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000012}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"0000012");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000013}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"0000013");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000014}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"0000014");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000015}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"0000015");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o{0000033}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"0000033");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o36044100177\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"36");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1e));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"044100177");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o036044100177\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"036");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1e));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"044100177");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o0036044100177\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"003");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x3));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"6044100177");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o00157677\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"00157");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x6f));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"677");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o00457677\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"004");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x4));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"57677");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o0000457677\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"000");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"0457677");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o36044100200\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"36044100200");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10000));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o73737675\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"73737675");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xfffd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o157677\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"157677");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7ff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o176\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"176");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7e));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o0\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o7\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"7");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o10\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"10");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o11\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"11");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o12\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"12");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o13\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"13");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o14\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"14");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o15\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"15");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\o33\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"33");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xG\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "\"\\xG\"\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"\"\\x{1\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "\"\\x{1\"\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"\"\\x{F48FBFC0}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. invalid UTF-8 hexadecimal character code. at :1:5\n"
        "\"\\x{F48FBFC0}\"\n"
        "    ^^^^^^^^\n",
        err->what());
    delete err;
  }

  str = U"\"\\x{F48FBFBF}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"F48FBFBF");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{0000000}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0000000");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{0000007}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"0000007");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{0000008}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"0000008");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{0000009}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"0000009");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{000000A}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"000000A");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{000000B}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"000000B");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{000000C}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"000000C");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{000000D}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"000000D");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x{000001B}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"000001B");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xf48fbfc0\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"f");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xf));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"48fbfc0");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xf48fbfbf\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"f48fbfbf");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10ffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x0f48fbfbf\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"0f");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xf));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"48fbfbf");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x00f48fbfbf\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"00");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"f48fbfbf");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xefbfbf\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"efbfbf");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xdfbf\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"dfbf");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7ff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x7f\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"7f");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7f));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x0\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x7\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"7");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x8\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"8");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x9\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"9");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xa\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"a");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xb\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"b");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xc\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"c");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\xd\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"d");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\x1b\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"1b");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\ug\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "\"\\ug\"\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"\"\\u{1\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "\"\\u{1\"\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"\"\\u{DBFFE000}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. invalid UTF-16 hexadecimal character code. at :1:5\n"
        "\"\\u{DBFFE000}\"\n"
        "    ^^^^^^^^\n",
        err->what());
    delete err;
  }

  str = U"\"\\u{DBFFDFFF}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"DBFFDFFF");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10ffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{0000000}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0000000");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{0000007}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"0000007");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{0000008}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"0000008");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{0000009}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"0000009");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{000000A}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"000000A");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{000000B}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"000000B");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{000000C}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"000000C");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{000000D}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"000000D");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u{000001B}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"000001B");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\udbffe000\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"db");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xdb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"ffe000");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\udbffdfff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"dbffdfff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10ffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  str = U"\"\\u0dbffdfff\"";

  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"0dbf");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xdbf));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"fdfff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u00dbffdfff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"00db");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xdb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"ffdfff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u000dbffdfff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"000d");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"bffdfff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u0000dbffdfff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0000");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"dbffdfff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\uffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"ffff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u7ff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"7ff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7ff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u7f\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"7f");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7f));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u0\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u7\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"7");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u8\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"8");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u9\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"9");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\ua\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"a");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\ub\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"b");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\uc\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"c");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\ud\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"d");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\u1b\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"1b");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "\"\\U\"\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"\"\\U{1\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "\"\\U{1\"\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"\"\\U{110000}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. invalid UTF-32 hexadecimal character code. at :1:5\n"
        "\"\\U{110000}\"\n"
        "    ^^^^^^\n",
        err->what());
    delete err;
  }

  str = U"\"\\U{10FFFF}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"10FFFF");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10ffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{000000}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"000000");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{000007}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"000007");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{000008}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"000008");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{000009}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"000009");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{00000A}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"00000A");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{00000B}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"00000B");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{00000C}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"00000C");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{00000D}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"00000D");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U{00001B}\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeOpen);
  ASSERT_EQ(token->getToken(), U"{");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"00001B");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U1100ff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"1100");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1100));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"ff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U10ffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"10ffff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10ffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U011ffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"011fff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x11fff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"f");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U0011ffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"0011ff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x11ff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"ff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U00011ffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"00011f");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x11f));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"fff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U000011ffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"000011");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x11));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"ffff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U0000011ffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"000001");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"1ffff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U00000011ffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"000000");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"11ffff");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\Uffff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"ffff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U7ff\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"7ff");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7ff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U7f\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"7f");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7f));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U0\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeNullChar);
  ASSERT_EQ(token->getToken(), U"0");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U7\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBellAlert);
  ASSERT_EQ(token->getToken(), U"7");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U8\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"8");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U9\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"9");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\Ua\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"a");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\Ub\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"b");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\Uc\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"c");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\Ud\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"d");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\\U1b\"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"1b");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"⮕\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"⮕");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"\"鼻\"\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltString);
  ASSERT_EQ(token->getToken(), U"鼻");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");
};

#endif