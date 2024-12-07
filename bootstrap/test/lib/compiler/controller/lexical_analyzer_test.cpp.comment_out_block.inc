// Copyright © 2024- Sunmoon development laboratory. Allexer Rights Reserved.
#ifndef _LEXICAL_ANALYZER_TEST_CPP_COMMENT_OUT_BLOCK_INC_
#define _LEXICAL_ANALYZER_TEST_CPP_COMMENT_OUT_BLOCK_INC_

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

TEST_F(LexicalAnalyzerTest, CommentOutBlock) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"//<";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");

  str = U"//<\t\f\v \n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");

  str = U"//<\t\f\v \n//<\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"//<");

  str = U"//<\t\f\v comment\t\f\v oneline\n//<\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"comment");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U"\t\f\v ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"oneline");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"//<");

  str = U"//<搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");

  str = U"//< @since 0.0.2 搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"@since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");

  str = U"//< @since 0.0.2 搭載\n//>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"@since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutClose);
  ASSERT_EQ(token->getToken(), U"//>");

  str = U"//< @since 0.0.2 搭載\n\\//>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"@since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"\\");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutClose);
  ASSERT_EQ(token->getToken(), U"//>");
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(block) open\"//<\", location::[1,1],\n"
            "  string of comment out: \"@since\" , location::[1,5],\n"
            "  space of comment out: \" \" , location::[1,11],\n"
            "  string of comment out: \"0.0.2\" , location::[1,12],\n"
            "  space of comment out: \" \" , location::[1,17],\n"
            "  string of comment out: \"搭載\" , location::[1,18],\n"
            "  line break(\\r,\\n) of comment out:  , location::[1,20],\n"
            "  string of comment out: \"\\\" , location::[2,1],\n"
            "  comment out(block) close\"//>\", location::[2,2],\n"
            "]\n");

  str = U"//< @since 0.0.2 搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::interpreter);
  lexer.tokenizeNextBuffer(buf);
  str = U"\\//>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lexer.tokenizeNextBuffer(buf);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"@since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"\\");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutClose);
  ASSERT_EQ(token->getToken(), U"//>");
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(block) open\"//<\", location::[1,1],\n"
            "  string of comment out: \"@since\" , location::[1,5],\n"
            "  space of comment out: \" \" , location::[1,11],\n"
            "  string of comment out: \"0.0.2\" , location::[1,12],\n"
            "  space of comment out: \" \" , location::[1,17],\n"
            "  string of comment out: \"搭載\" , location::[1,18],\n"
            "  line break(\\r,\\n) of comment out:  , location::[1,20],\n"
            "  string of comment out: \"\\\" , location::[2,1],\n"
            "  comment out(block) close\"//>\", location::[2,2],\n"
            "]\n");
};

TEST_F(LexicalAnalyzerTest, CommentOutBlockDoc) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"/#<";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");

  str = U"/#<\t\f\v \n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");

  str = U"/#<\t\f\v \n/#<\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"/#<");

  str = U"/#<\t\f\v comment\t\f\v oneline\n/#<\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"comment");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U"\t\f\v ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"oneline");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"/#<");

  str = U"/#<搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");

  str = U"/#< @since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"開始");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");

  str = U"/#<@since 0.0.2 搭載\n    @author Example, Auth \n/#>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"author");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Example,");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Auth");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocClose);
  ASSERT_EQ(token->getToken(), U"/#>");
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(block for document) open\"/#<\", location::[1,1],\n"
            "  doc tag open in commentout(@), location::[1,4],\n"
            "  tag for documentation comment: since , location::[1,5],\n"
            "  string of comment out: \"0.0.2\" , location::[1,11],\n"
            "  space of comment out: \" \" , location::[1,16],\n"
            "  string of comment out: \"搭載\" , location::[1,17],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[1,19],\n"
            "  doc tag open in commentout(@), location::[2,5],\n"
            "  tag for documentation comment: author , location::[2,6],\n"
            "  string of comment out: \"Example,\" , location::[2,13],\n"
            "  space of comment out: \" \" , location::[2,21],\n"
            "  string of comment out: \"Auth\" , location::[2,22],\n"
            "  space of comment out: \" \" , location::[2,26],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[2,27],\n"
            "  comment out(block for document) close\"/#>\", location::[3,1],\n"
            "]\n");

  str = U"/#<@since 0.0.2 搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::interpreter);
  lexer.tokenizeNextBuffer(buf);
  str = U"    @author Example, Auth \n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lexer.tokenizeNextBuffer(buf);
  str = U"/#>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lexer.tokenizeNextBuffer(buf);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"author");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Example,");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Auth");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocClose);
  ASSERT_EQ(token->getToken(), U"/#>");
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(block for document) open\"/#<\", location::[1,1],\n"
            "  doc tag open in commentout(@), location::[1,4],\n"
            "  tag for documentation comment: since , location::[1,5],\n"
            "  string of comment out: \"0.0.2\" , location::[1,11],\n"
            "  space of comment out: \" \" , location::[1,16],\n"
            "  string of comment out: \"搭載\" , location::[1,17],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[1,19],\n"
            "  doc tag open in commentout(@), location::[2,5],\n"
            "  tag for documentation comment: author , location::[2,6],\n"
            "  string of comment out: \"Example,\" , location::[2,13],\n"
            "  space of comment out: \" \" , location::[2,21],\n"
            "  string of comment out: \"Auth\" , location::[2,22],\n"
            "  space of comment out: \" \" , location::[2,26],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[2,27],\n"
            "  comment out(block for document) close\"/#>\", location::[3,1],\n"
            "]\n");

  str = U"/#< @since 0.0.2 搭載\n\\/#>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"\\");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocClose);
  ASSERT_EQ(token->getToken(), U"/#>");
};

TEST_F(LexicalAnalyzerTest, CommentOutBlockDocTopLevel) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"/#!<";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");

  str = U"/#!<\t\f\v \n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");

  str = U"/#!<\t\f\v \n/#!<\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"/#!<");

  str = U"/#!<\t\f\v comment\t\f\v oneline\n/#!<\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"comment");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U"\t\f\v ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"oneline");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"/#!<");

  str = U"/#!<搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");

  str = U"/#!< @since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"開始");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");

  str = U"/#!<@since 0.0.2 搭載\n    @author Example, Auth \n/#>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"author");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Example,");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Auth");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocClose);
  ASSERT_EQ(token->getToken(), U"/#>");
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(block for document top level) open\"/#!<\", "
            "location::[1,1],\n"
            "  doc tag open in commentout(@), location::[1,5],\n"
            "  tag for documentation comment: since , location::[1,6],\n"
            "  string of comment out: \"0.0.2\" , location::[1,12],\n"
            "  space of comment out: \" \" , location::[1,17],\n"
            "  string of comment out: \"搭載\" , location::[1,18],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[1,20],\n"
            "  doc tag open in commentout(@), location::[2,5],\n"
            "  tag for documentation comment: author , location::[2,6],\n"
            "  string of comment out: \"Example,\" , location::[2,13],\n"
            "  space of comment out: \" \" , location::[2,21],\n"
            "  string of comment out: \"Auth\" , location::[2,22],\n"
            "  space of comment out: \" \" , location::[2,26],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[2,27],\n"
            "  comment out(block for document) close\"/#>\", location::[3,1],\n"
            "]\n");

  str = U"/#!<@since 0.0.2 搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::interpreter);
  lexer.tokenizeNextBuffer(buf);
  str = U"    @author Example, Auth \n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lexer.tokenizeNextBuffer(buf);
  str = U"/#>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lexer.tokenizeNextBuffer(buf);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"author");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Example,");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"Auth");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocClose);
  ASSERT_EQ(token->getToken(), U"/#>");
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(block for document top level) open\"/#!<\", "
            "location::[1,1],\n"
            "  doc tag open in commentout(@), location::[1,5],\n"
            "  tag for documentation comment: since , location::[1,6],\n"
            "  string of comment out: \"0.0.2\" , location::[1,12],\n"
            "  space of comment out: \" \" , location::[1,17],\n"
            "  string of comment out: \"搭載\" , location::[1,18],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[1,20],\n"
            "  doc tag open in commentout(@), location::[2,5],\n"
            "  tag for documentation comment: author , location::[2,6],\n"
            "  string of comment out: \"Example,\" , location::[2,13],\n"
            "  space of comment out: \" \" , location::[2,21],\n"
            "  string of comment out: \"Auth\" , location::[2,22],\n"
            "  space of comment out: \" \" , location::[2,26],\n"
            "  line break(\\r,\\n) of documentation comment out:  , "
            "location::[2,27],\n"
            "  comment out(block for document) close\"/#>\", location::[3,1],\n"
            "]\n");

  str = U"/#!< @since 0.0.2 搭載\n\\/#>\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDocTagOpen);
  ASSERT_EQ(token->getToken(), U"@");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocTag);
  ASSERT_EQ(token->getToken(), U"since");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"0.0.2");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coDocLineBreak);
  ASSERT_EQ(token->getToken(), U"\n");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"\\");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocClose);
  ASSERT_EQ(token->getToken(), U"/#>");
};

#endif