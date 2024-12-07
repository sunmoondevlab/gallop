// Copyright © 2024- Sunmoon development laboratory. Allexer Rights Reserved.
#ifndef _LEXICAL_ANALYZER_TEST_CPP_SYMBOL_CHARACTERS_INC_
#define _LEXICAL_ANALYZER_TEST_CPP_SYMBOL_CHARACTERS_INC_

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

TEST_F(LexicalAnalyzerTest, SymbolCharacters) {
  SrcLines lines;
  std::u32string str = U"";
  std::vector<int32_t> buf = std::vector<int32_t>(str.begin(), str.end());
  LexicalAnalyzer lexer(lines, CompilerModeEnum::compilerFromStdin);

  // arithmetic
  TokensInputStream tis = lexer.getTokensInputStream();
  Token *token = tis.read();

  str = U"+ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPlus);
  ASSERT_EQ(token->getToken(), U"+");

  str = U"+% ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPlusWrapping);
  ASSERT_EQ(token->getToken(), U"+%");

  str = U"+| ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPlusSaturating);
  ASSERT_EQ(token->getToken(), U"+|");

  str = U"+= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPlusAssign);
  ASSERT_EQ(token->getToken(), U"+=");

  str = U"+%= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPlusWrappingAssign);
  ASSERT_EQ(token->getToken(), U"+%=");

  str = U"+|= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPlusSaturatingAssign);
  ASSERT_EQ(token->getToken(), U"+|=");

  str = U"++ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scIncrement);
  ASSERT_EQ(token->getToken(), U"++");

  str = U"- ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMinus);
  ASSERT_EQ(token->getToken(), U"-");

  str = U"-% ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMinusWrapping);
  ASSERT_EQ(token->getToken(), U"-%");

  str = U"-| ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMinusSaturating);
  ASSERT_EQ(token->getToken(), U"-|");

  str = U"-= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMinusAssign);
  ASSERT_EQ(token->getToken(), U"-=");

  str = U"-%= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMinusWrappingAssign);
  ASSERT_EQ(token->getToken(), U"-%=");

  str = U"-|= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMinusSaturatingAssign);
  ASSERT_EQ(token->getToken(), U"-|=");

  str = U"-- ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDecrement);
  ASSERT_EQ(token->getToken(), U"--");

  str = U"-> ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMemberAccessArrow);
  ASSERT_EQ(token->getToken(), U"->");

  str = U"* ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMultiple);
  ASSERT_EQ(token->getToken(), U"*");

  str = U"*% ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMultipleWrapping);
  ASSERT_EQ(token->getToken(), U"*%");

  str = U"*| ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMultipleSaturating);
  ASSERT_EQ(token->getToken(), U"*|");

  str = U"*= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMultipleAssign);
  ASSERT_EQ(token->getToken(), U"*=");

  str = U"*%= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMultipleWrappingAssign);
  ASSERT_EQ(token->getToken(), U"*%=");

  str = U"*|= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scMultipleSaturatingAssign);
  ASSERT_EQ(token->getToken(), U"*|=");

  str = U"** ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPower);
  ASSERT_EQ(token->getToken(), U"**");

  str = U"**% ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPowerWrapping);
  ASSERT_EQ(token->getToken(), U"**%");

  str = U"**| ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPowerSaturating);
  ASSERT_EQ(token->getToken(), U"**|");

  str = U"**= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPowerAssign);
  ASSERT_EQ(token->getToken(), U"**=");

  str = U"**%= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPowerWrappingAssign);
  ASSERT_EQ(token->getToken(), U"**%=");

  str = U"**|= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scPowerSaturatingAssign);
  ASSERT_EQ(token->getToken(), U"**|=");

  str = U"/ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDivide);
  ASSERT_EQ(token->getToken(), U"/");

  str = U"/= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDivideAssign);
  ASSERT_EQ(token->getToken(), U"/=");

  str = U"% ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scModulo);
  ASSERT_EQ(token->getToken(), U"%");

  str = U"%= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scModuloAssign);
  ASSERT_EQ(token->getToken(), U"%=");

  // bit , logical
  str = U"& ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitAnd);
  ASSERT_EQ(token->getToken(), U"&");

  str = U"&= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitAndAssign);
  ASSERT_EQ(token->getToken(), U"&=");

  str = U"&& ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalAnd);
  ASSERT_EQ(token->getToken(), U"&&");

  str = U"&&= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalAndAssign);
  ASSERT_EQ(token->getToken(), U"&&=");

  str = U"| ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitOr);
  ASSERT_EQ(token->getToken(), U"|");

  str = U"|= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitOrAssign);
  ASSERT_EQ(token->getToken(), U"|=");

  str = U"|| ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalOr);
  ASSERT_EQ(token->getToken(), U"||");

  str = U"||= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalOrAssign);
  ASSERT_EQ(token->getToken(), U"||=");

  str = U"^ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitExOr);
  ASSERT_EQ(token->getToken(), U"^");

  str = U"^= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitExOrAssign);
  ASSERT_EQ(token->getToken(), U"^=");

  str = U"^^ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalExOr);
  ASSERT_EQ(token->getToken(), U"^^");

  str = U"^^= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalExOrAssign);
  ASSERT_EQ(token->getToken(), U"^^=");

  str = U"~ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitNot);
  ASSERT_EQ(token->getToken(), U"~");

  str = U"~= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitNotAssign);
  ASSERT_EQ(token->getToken(), U"~=");

  str = U"! ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalNotUnary);
  ASSERT_EQ(token->getToken(), U"!");

  str = U"!= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalNotEqual);
  ASSERT_EQ(token->getToken(), U"!=");

  str = U"= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scAssignment);
  ASSERT_EQ(token->getToken(), U"=");

  str = U"== ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalEqual);
  ASSERT_EQ(token->getToken(), U"==");

  str = U"< ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLessThan);
  ASSERT_EQ(token->getToken(), U"<");

  str = U"<= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLessThanEqual);
  ASSERT_EQ(token->getToken(), U"<=");

  str = U"<< ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitShiftLeft);
  ASSERT_EQ(token->getToken(), U"<<");

  str = U"<<= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitShiftLeftAssign);
  ASSERT_EQ(token->getToken(), U"<<=");

  str = U"<<| ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBitShiftLeftSaturating);
  ASSERT_EQ(token->getToken(), U"<<|");

  str = U"<<|= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBitShiftLeftSaturatingAssign);
  ASSERT_EQ(token->getToken(), U"<<|=");

  str = U"> ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scGreaterThan);
  ASSERT_EQ(token->getToken(), U">");

  str = U">= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scGreaterThanEqual);
  ASSERT_EQ(token->getToken(), U">=");

  str = U">> ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scArithmeticBitShiftRight);
  ASSERT_EQ(token->getToken(), U">>");

  str = U">>= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scArithmeticBitShiftRightAssign);
  ASSERT_EQ(token->getToken(), U">>=");

  str = U">>> ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalBitShiftRight);
  ASSERT_EQ(token->getToken(), U">>>");

  str = U">>>= ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scLogicalBitShiftRightAssign);
  ASSERT_EQ(token->getToken(), U">>>=");

  // other
  str = U"$ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDollar);
  ASSERT_EQ(token->getToken(), U"$");

  str = U"# ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scNumberSign);
  ASSERT_EQ(token->getToken(), U"#");

  str = U"? ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scQuestion);
  ASSERT_EQ(token->getToken(), U"?");

  str = U"@ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scAtSign);
  ASSERT_EQ(token->getToken(), U"@");

  str = U": ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scColon);
  ASSERT_EQ(token->getToken(), U":");

  str = U":: ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scNameSpaceSeparater);
  ASSERT_EQ(token->getToken(), U"::");

  str = U"; ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSemiColon);
  ASSERT_EQ(token->getToken(), U";");

  str = U", ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scComma);
  ASSERT_EQ(token->getToken(), U",");

  str = U". ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDot);
  ASSERT_EQ(token->getToken(), U".");

  str = U".. ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDotDot);
  ASSERT_EQ(token->getToken(), U"..");

  str = U"... ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDotDotDot);
  ASSERT_EQ(token->getToken(), U"...");

  str = U"\\ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBackSlash);
  ASSERT_EQ(token->getToken(), U"\\");

  str = U"' '";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSingleQuotation);
  ASSERT_EQ(token->getToken(), U"'");

  str = U"\"\n ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scDoubleQuotation);
  ASSERT_EQ(token->getToken(), U"\"");

  str = U"` ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBackQuotation);
  ASSERT_EQ(token->getToken(), U"`");

  str = U"( ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scParenthesesOpen);
  ASSERT_EQ(token->getToken(), U"(");

  str = U") ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scParenthesesClose);
  ASSERT_EQ(token->getToken(), U")");

  str = U"{ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scCurlyBracketOpen);
  ASSERT_EQ(token->getToken(), U"{");

  str = U"} ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scCurlyBracketClose);
  ASSERT_EQ(token->getToken(), U"}");

  str = U"[ ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSquareBracketOpen);
  ASSERT_EQ(token->getToken(), U"[");

  str = U"] ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scSquareBracketClose);
  ASSERT_EQ(token->getToken(), U"]");

  str = U"// ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOut);
  ASSERT_EQ(token->getToken(), U"//");

  str = U"//< ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutOpen);
  ASSERT_EQ(token->getToken(), U"//<");

  str = U"//> ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutClose);
  ASSERT_EQ(token->getToken(), U"//>");

  str = U"/# ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scOnelineCommentOutDoc);
  ASSERT_EQ(token->getToken(), U"/#");

  str = U"/#< ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocOpen);
  ASSERT_EQ(token->getToken(), U"/#<");

  str = U"/#> ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(), TokenTypeEnum::scBlockCommentOutDocClose);
  ASSERT_EQ(token->getToken(), U"/#>");

  str = U"/#! ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scOnelineCommentOutDocTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!");

  str = U"/#!< ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  lines.resetBuffer();
  lines.appendBuffer(buf);
  lexer = LexicalAnalyzer(lines, CompilerModeEnum::compilerFromStdin);
  tis = lexer.getTokensInputStream();
  token = tis.read();
  ASSERT_EQ(token->getTokenType(),
            TokenTypeEnum::scBlockCommentOutDocOpenTopLevel);
  ASSERT_EQ(token->getToken(), U"/#!<");
};

#endif