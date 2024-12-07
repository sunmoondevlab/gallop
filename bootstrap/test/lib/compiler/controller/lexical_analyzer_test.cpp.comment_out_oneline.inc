// Copyright © 2024- Sunmoon development laboratory. Allexer Rights Reserved.
#ifndef _LEXICAL_ANALYZER_TEST_CPP_COMMENT_OUT_ONELINE_INC_
#define _LEXICAL_ANALYZER_TEST_CPP_COMMENT_OUT_ONELINE_INC_

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

TEST_F(LexicalAnalyzerTest, CommentOutOneline) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"//";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");

  str = U"//\t\f\v \n//\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");

  str = U"//\t\f\v comment\t\f\v oneline\n//\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");

  str = U"//搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");

  str = U"// @since 0.0.2 搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");
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
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(oneline) open\"//\", location::[1,1],\n"
            "  string of comment out: \"@since\" , location::[1,4],\n"
            "  space of comment out: \" \" , location::[1,10],\n"
            "  string of comment out: \"0.0.2\" , location::[1,11],\n"
            "  space of comment out: \" \" , location::[1,16],\n"
            "  string of comment out: \"搭載\" , location::[1,17],\n"
            "]\n");
};
TEST_F(LexicalAnalyzerTest, CommentOutOnelineDoc) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"/#";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");

  str = U"/#\t\f\v \n/#\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");

  str = U"/#\t\f\v comment\t\f\v oneline\n/#\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");

  str = U"/#搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");

  str = U"/# @since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");
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
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(oneline for document) open\"/#\", location::[1,1],\n"
            "  doc tag open in commentout(@), location::[1,4],\n"
            "  tag for documentation comment: since , location::[1,5],\n"
            "  string of comment out: \"0.0.2\" , location::[1,11],\n"
            "  space of comment out: \" \" , location::[1,16],\n"
            "  string of comment out: \"搭載\" , location::[1,17],\n"
            "  space of comment out: \" \" , location::[1,19],\n"
            "  string of comment out: \"開始\" , location::[1,20],\n"
            "]\n");

  str = U"/# \\@since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"\\@since");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"開始");

  str = U"/# @\\since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"@\\since");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"開始");
};
TEST_F(LexicalAnalyzerTest, CommentOutOnelineDocTopLevel) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"/#!";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");

  str = U"/#!\t\f\v \n/#!\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");

  str = U"/#!\t\f\v comment\t\f\v oneline\n/#!\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
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
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");

  str = U"/#!搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");

  str = U"/#! @since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
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
  ASSERT_EQ(tis.toStringPrintTokens(true),

            "[\n"
            "  comment out(oneline for document top level) open\"/#!\", "
            "location::[1,1],\n"
            "  doc tag open in commentout(@), location::[1,5],\n"
            "  tag for documentation comment: since , location::[1,6],\n"
            "  string of comment out: \"0.0.2\" , location::[1,12],\n"
            "  space of comment out: \" \" , location::[1,17],\n"
            "  string of comment out: \"搭載\" , location::[1,18],\n"
            "  space of comment out: \" \" , location::[1,20],\n"
            "  string of comment out: \"開始\" , location::[1,21],\n"
            "]\n");

  str = U"/#!搭載\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"搭載");

  str = U"/#! @since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
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

  str = U"/#! \\@since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"\\@since");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"開始");

  str = U"/#! @\\since 0.0.2 搭載 開始\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"@\\since");
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
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coSpace);
  ASSERT_EQ(token->getToken(), U" ");
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::coString);
  ASSERT_EQ(token->getToken(), U"開始");
};

#endif