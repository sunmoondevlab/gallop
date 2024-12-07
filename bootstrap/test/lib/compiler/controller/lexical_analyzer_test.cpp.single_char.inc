// Copyright © 2024- Sunmoon development laboratory. Allexer Rights Reserved.
#ifndef _LEXICAL_ANALYZER_TEST_CPP_SINGLE_CHAR_INC_
#define _LEXICAL_ANALYZER_TEST_CPP_SINGLE_CHAR_INC_

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

TEST_F(LexicalAnalyzerTest, SingleCharacter) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"''";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set empty character in single "
                 "character literal. at :1:2\n"
                 "''\n"
                 " ^\n",
                 err->what());
    delete err;
  }

  str = U"' 1'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set multiple characters in single "
                 "character literal. at :1:2\n"
                 "' 1'\n"
                 " ^^\n",
                 err->what());
    delete err;
  }
  str = U"' ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. single character literal is not closed. at :1:2\n"
        "' \n"
        " ^\n",
        err->what());
    delete err;
  }
  str = U"'\r'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set raw line break character(\\r,\\n) "
                 "in single character literal. at :1:2\n"
                 "'\n"
                 " ^\n",
                 err->what());
    delete err;
  }

  str = U"'\n'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set raw line break character(\\r,\\n) "
                 "in single character literal. at :1:2\n"
                 "'\n"
                 " ^\n",
                 err->what());
    delete err;
  }

  str = U"' '\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(escapeCharCode, nullptr);
  }

  str = U"'\\''\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceSingleQuotation);
  ASSERT_EQ(token->getToken(), U"\\'");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::SingleQuotation));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\'\n'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. single character literal is not closed. at :1:2\n"
        "'\\'\n"
        " ^^^\n",
        err->what());
    delete err;
  }

  str = U"'\\a'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceBellAlert);
  ASSERT_EQ(token->getToken(), U"\\a");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::BellAlert));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\b'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceBackspace);
  ASSERT_EQ(token->getToken(), U"\\b");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::Backspace));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\t'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceHorizontalTab);
  ASSERT_EQ(token->getToken(), U"\\t");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::HorizontalTab));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\n'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceLineFeed);
  ASSERT_EQ(token->getToken(), U"\\n");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::LineFeed));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\v'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceVerticalTab);
  ASSERT_EQ(token->getToken(), U"\\v");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::VerticalTab));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\f'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceFormFeed);
  ASSERT_EQ(token->getToken(), U"\\f");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::FormFeed));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\r'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceCarriageReturn);
  ASSERT_EQ(token->getToken(), U"\\r");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::CarriageReturn));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\e'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceAnsiEscape);
  ASSERT_EQ(token->getToken(), U"\\e");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::Escape));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\\\'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceBackSlash);
  ASSERT_EQ(token->getToken(), U"\\\\");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::BackSlash));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\0'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltEscapeSequenceNullChar);
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode,
              static_cast<int32_t>(CharCode::UtfAsciiTable::NullChar));
  }
  ASSERT_EQ(token->getToken(), U"\\0");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\'a'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set multiple characters in single "
                 "character literal. at :1:2\n"
                 "'\\'a'\n"
                 " ^^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\o'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "'\\o'\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\o8'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "'\\o8'\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\o{1'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "'\\o{1'\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"'\\o{36044100177}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid UTF-8 octal character code. at :1:5\n"
                 "'\\o{36044100177}'\n"
                 "    ^^^^^^^^^^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\o{36044100200}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10000));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  ASSERT_EQ(
      tis.toStringPrintTokens(true),

      "[\n"
      "  single character literal separator('), location::[1,1],\n"
      "  escape sequence UTF-8 octal code(\\o): '\\o' , location::[1,2],\n"
      "  UTF code open'{': '{' , location::[1,4],\n"
      "  UTF-8 octal code(\\o): '36044100200' , location::[1,5],\n"
      "  UTF code close'}': '}' , location::[1,16],\n"
      "  single character literal separator('), location::[1,17],\n"
      "]\n");

  str = U"'\\o{0000000}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000007}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000010}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000011}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000012}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000013}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000014}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000015}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o{0000033}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o36044100177'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set multiple characters in single "
                 "character literal. at :1:2\n"
                 "'\\o36044100177'\n"
                 " ^^^^^^^^^^^^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\o36044100200'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o73737675'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o157677'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o176'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o0'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o7'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o10'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o11'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o12'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o13'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o14'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o15'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o33'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\o00000157677'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"\\o");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeOctal);
  ASSERT_EQ(token->getToken(), U"00000157677");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7ff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xG'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "'\\xG'\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\x{1'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "'\\x{1'\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"'\\x{F48FBFC0}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. invalid UTF-8 hexadecimal character code. at :1:5\n"
        "'\\x{F48FBFC0}'\n"
        "    ^^^^^^^^\n",
        err->what());
    delete err;
  }

  str = U"'\\x{F48FBFBF}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x10ffff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{0000000}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{0000007}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{0000008}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{0000009}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{000000A}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{000000B}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{000000C}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{000000D}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x{000001B}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xf48fbfc0'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set multiple characters in single "
                 "character literal. at :1:2\n"
                 "'\\xf48fbfc0'\n"
                 " ^^^^^^^^^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\xf48fbfbf'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xefbfbf'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xdfbf'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x7f'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x0'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x7'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x8'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"8");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x9'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"9");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xa'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"a");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xb'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"b");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xc'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"c");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\xd'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"d");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x1b'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"1b");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\x0000dfbf'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\x");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf8CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"0000dfbf");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7ff));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\ug'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "'\\ug'\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\u{1'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "'\\u{1'\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"'\\u{DBFFE000}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. invalid UTF-16 hexadecimal character code. at :1:5\n"
        "'\\u{DBFFE000}'\n"
        "    ^^^^^^^^\n",
        err->what());
    delete err;
  }

  str = U"'\\u{DBFFDFFF}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{0000000}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{0000007}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x7));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{0000008}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{0000009}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{000000A}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{000000B}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{000000C}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{000000D}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u{000001B}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\udbffe000'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set multiple characters in single "
                 "character literal. at :1:2\n"
                 "'\\udbffe000'\n"
                 " ^^^^^^^^^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\udbffdfff'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\uffff'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u7ff'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u7f'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u0'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u7'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u8'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"8");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u9'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"9");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\ua'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"a");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\ub'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"b");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\uc'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"c");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\ud'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"d");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u1b'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"1b");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\u0000fffd'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\u");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf16CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"0000fffd");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xfffd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. invalid escape sequence. at :1:2\n"
                 "'\\U'\n"
                 " ^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\U{1'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. UTF character code literal is not closed. at :1:5\n"
        "'\\U{1'\n"
        "    ^\n",
        err->what());
    delete err;
  }

  str = U"'\\U{110000}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ(
        "Tokenize Error. invalid UTF-32 hexadecimal character code. at :1:5\n"
        "'\\U{110000}'\n"
        "    ^^^^^^\n",
        err->what());
    delete err;
  }

  str = U"'\\U{10FFFF}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{000000}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x0));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{000007}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{000008}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{000009}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{00000A}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{00000B}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xb));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{00000C}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{00000D}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U{00001B}'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeClose);
  ASSERT_EQ(token->getToken(), U"}");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U1100ff'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  try {
    lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  } catch (TokenizeError *err) {
    // check exception
    ASSERT_STREQ("Tokenize Error. unable set multiple characters in single "
                 "character literal. at :1:2\n"
                 "'\\U1100ff'\n"
                 " ^^^^^^^^\n",
                 err->what());
    delete err;
  }

  str = U"'\\U10ffff'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\Uffff'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U7ff'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U7f'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U0'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U7'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U8'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeBackspace);
  ASSERT_EQ(token->getToken(), U"8");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x8));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U9'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeHorizontalTab);
  ASSERT_EQ(token->getToken(), U"9");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x9));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\Ua'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeLineFeed);
  ASSERT_EQ(token->getToken(), U"a");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xa));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\Ub'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeVerticalTab);
  ASSERT_EQ(token->getToken(), U"b");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xB));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\Uc'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeFormFeed);
  ASSERT_EQ(token->getToken(), U"c");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xc));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\Ud'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeCarriageReturn);
  ASSERT_EQ(token->getToken(), U"d");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U1b'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtfCodeAnsiEscape);
  ASSERT_EQ(token->getToken(), U"1b");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0x1b));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'\\U00fffd'";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"\\U");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltUtf32CodeHexadecimal);
  ASSERT_EQ(token->getToken(), U"00fffd");
  {
    int32_t *escapeCharCode = token->preParseEscapeUtf32CharCode();
    ASSERT_EQ(*escapeCharCode, static_cast<int32_t>(0xfffd));
  }
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"''\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
  ASSERT_EQ(token->getToken(), U"");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'⮕'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
  ASSERT_EQ(token->getToken(), U"⮕");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"'鼻'\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::ltSingleCharacter);
  ASSERT_EQ(token->getToken(), U"鼻");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");
};

#endif