// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/controller/lexical_analyzer.hpp"

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"
#include "char_set/string/utf32_string.hpp"
#include "error/compile_errors.hpp"

using namespace gallop::Compiler;
using namespace gallop::Error;
using namespace gallop::Compiler::Controller;
using namespace gallop::CharSet;
using namespace gallop::IO::Stream;

LexicalAnalyzer::LexicalAnalyzer(const SrcLines &lines_,
                                 const enum CompilerModeEnum &mode_)
    : lines(const_cast<SrcLines &>(lines_)),
      mode(const_cast<CompilerModeEnum &>(mode_)),
      uis(lines.createUtf32InputStream()), tokens(Tokens()),
      tis(TokensInputStream(tokens)),
      location(Location(lines.getFilename(), 0, 0, 0)),
      tokenBeginLocation(location) {
  if (!isInterpreter()) {
    tokenize();
  }
};

// copier
LexicalAnalyzer::LexicalAnalyzer(const LexicalAnalyzer &rhs)
    : lines(rhs.lines), mode(rhs.mode), uis(rhs.uis), tokens(rhs.tokens),
      tis(rhs.tis), location(rhs.tokenBeginLocation),
      tokenBeginLocation(rhs.tokenBeginLocation) {};

// setters
LexicalAnalyzer &LexicalAnalyzer::operator=(const LexicalAnalyzer &rhs) {
  lines = rhs.lines;
  mode = rhs.mode;
  uis = rhs.uis;
  tokens = rhs.tokens;
  tis = rhs.tis;
  location = rhs.location;
  tokenBeginLocation = rhs.tokenBeginLocation;
  return *this;
};

void LexicalAnalyzer::tokenizeNextBuffer(const std::vector<int32_t> &buffer_) {
  if (!isInterpreter()) {
    return;
  }
  lines.appendBuffer(const_cast<std::vector<int32_t> &>(buffer_));
  uis = lines.createUtf32InputStream();
  tokenize();
};

bool LexicalAnalyzer::isInterpreter() const {
  return mode == CompilerModeEnum::interpreter;
};
bool LexicalAnalyzer::isFromFile() const {
  return mode == CompilerModeEnum::compilerFromFile;
};
std::string LexicalAnalyzer::getFilename() const {
  return lines.getFilename();
};
size_t LexicalAnalyzer::getLineCount() const { return lines.getLinesCount(); };
std::string LexicalAnalyzer::getLineString(const size_t &line_) const {
  return lines.getLineString(line_);
};
TokensInputStream LexicalAnalyzer::getTokensInputStream() { return tis; };

void LexicalAnalyzer::tokenize() {
  if (!uis.hasReadable()) {
    return;
  }
  TokenTypeEnum tailTokenType = tis.tailTokenType();
  if (tailTokenType == TokenTypeEnum::coLineBreak) {
    scanningBlockComment(TokenTypeEnum::scBlockCommentOutOpen);
  } else if (tailTokenType == TokenTypeEnum::coDocLineBreak) {
    scanningBlockComment(TokenTypeEnum::scBlockCommentOutDocOpen);
  } else if (tailTokenType == TokenTypeEnum::ltStringLineBreak) {
    scanningStringLiteral();
  } else if (tailTokenType == TokenTypeEnum::ltRawStringLineBreak) {
    scanningRawStringLiteral();
  }
  int32_t charCode = uis.current();
  while (uis.hasReadable()) {
    toNextToken();
    charCode = uis.current();
    if (CharCode::Utf32::isIdentifierChar(charCode)) {
      scanningIdentifier();
    } else if (CharCode::Utf32::isSymbolChar(charCode)) {
      scanningSymbol();
    } else {
      uis.skip();
    }
  }
  //   for (size_t pos = 0; pos < bufferSize;) {
  //     if (isAnalyzeContinue) {
  //       if (continueTokenType == TokenTypeEnum::scOnelineCommentOut ||
  //           continueTokenType == TokenTypeEnum::scOnelineCommentOutDoc)
  //           {
  //         pos += toNextToken(pos);
  //         if (pos >= bufferSize) {
  //           break;
  //         }
  //         pos += scanningOnelineComment(pos);
  //       } else if (continueTokenType ==
  //                      TokenTypeEnum::scBlockCommentOutOpen ||
  //                  continueTokenType ==
  //                      TokenTypeEnum::scBlockCommentOutDocOpen) {
  //         pos += toNextToken(pos);
  //         if (pos >= bufferSize) {
  //           break;
  //         }
  //         pos += scanningBlockComment(pos);
  //       } else if (continueTokenType ==
  //                      TokenTypeEnum::scSingleQuotation ||
  //                  continueTokenType ==
  //                      TokenTypeEnum::scDoubleQuotation ||
  //                  continueTokenType ==
  //                  TokenTypeEnum::scBackQuotation) {
  //         pos += scanningCharactersLiteral(pos);
  //       }
  //     } else {
  //       pos += toNextToken(pos);
  //       if (pos >= bufferSize) {
  //         break;
  //       }
  //       pos += scanningToken(pos);
  //     }
  //     if (pos >= bufferSize) {
  //       break;
  //     }
  //   }
};
void LexicalAnalyzer::toNextToken() {
  while (uis.hasReadable()) {
    int32_t charCode = uis.current();
    if (CharCode::Utf32::isSpaceChar(charCode)) {
      scanningSpaces();
    } else if (CharCode::Utf32::isLineBreak(charCode)) {
      scanningLineBreaks();
    } else {
      break;
    }
  }
  tokenBeginLocation = location;
};

void LexicalAnalyzer::scanningSpaces() {
  while (uis.hasReadable()) {
    int32_t charCode = uis.read();
    if (!CharCode::Utf32::isSpaceChar(charCode)) {
      uis.undo();
      break;
    }
  };
  size_t currentBufferPos = uis.currentPos();
  if (tokenBeginLocation.getBufferPos() == currentBufferPos) {
    return;
  } else {
    size_t spacesSize = currentBufferPos - tokenBeginLocation.getBufferPos();
    location = Location(location.getFilename(), currentBufferPos,
                        location.getLine(), location.getColumn() + spacesSize);
  }
};
void LexicalAnalyzer::scanningLineBreaks() {
  while (uis.hasReadable()) {
    int32_t charCode = uis.read();
    if (CharCode::Utf32::isCarriageReturn(charCode)) {
      int32_t charCode1 = uis.current();
      if (CharCode::Utf32::isLineFeed(charCode1)) {
        uis.skip();
      }
      size_t currentBufferPos = uis.currentPos();
      location = Location(location.getFilename(), currentBufferPos,
                          location.getLine() + 1, 1ul);
    } else if (CharCode::Utf32::isLineFeed(charCode)) {
      size_t currentBufferPos = uis.currentPos();
      location = Location(location.getFilename(), currentBufferPos,
                          location.getLine() + 1, 1ul);
    } else {
      uis.undo();
      break;
    }
  };
};
void LexicalAnalyzer::scanningIdentifier() {
  uis.skip();
  while (uis.hasReadable()) {
    int32_t charCode = uis.read();
    if (!CharCode::Utf32::isIdentifierChar(charCode, true)) {
      uis.undo();
      break;
    }
  }
  TokenTypeEnum prevTokenType = tis.tailTokenType();
  if (prevTokenType == TokenTypeEnum::scDot ||
      prevTokenType == TokenTypeEnum::scDollar) {
    pushToken(TokenTypeEnum::identifier,
              uis.currentPos() - tokenBeginLocation.getBufferPos());
  } else {
    pushToken(TokenTypeEnum::reservedWord,
              uis.currentPos() - tokenBeginLocation.getBufferPos());
  }
};
void LexicalAnalyzer::scanningSymbol() {
  TokenTypeEnum tokenType = TokenTypeEnum::unknown;
  TokenTypeEnum prevTokenType = tis.tailTokenType();
  size_t symbolSize = 0;
  switch (uis.current()) {
    // arithmetic
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Plus):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scPlusWrappingAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scPlusWrapping;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scPlusSaturatingAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scPlusSaturating;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Plus):
      tokenType = TokenTypeEnum::scIncrement;
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scPlusAssign;
      symbolSize++;
      break;
    default:
      if (CharCode::Utf32::isNumberChar(uis.ahead(1))) {
        if (prevTokenType ==
            // exponent sign
            TokenTypeEnum::ltDecimalExponentOperator) {
          tokenType = TokenTypeEnum::scPositiveDecimalExponent;
        } else {
          tokenType = TokenTypeEnum::scPlus;
        }
      } else {
        tokenType = TokenTypeEnum::scPlus;
      }
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Minus):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMinusWrappingAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scMinusWrapping;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMinusSaturatingAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scMinusSaturating;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Minus):
      tokenType = TokenTypeEnum::scDecrement;
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scMinusAssign;
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
      tokenType = TokenTypeEnum::scMemberAccessArrow;
      symbolSize++;
      break;
    default:
      if (CharCode::Utf32::isNumberChar(uis.ahead(1))) {
        if (prevTokenType == TokenTypeEnum::ltDecimalExponentOperator) {
          // exponent sign
          tokenType = TokenTypeEnum::scNegativeDecimalExponent;
        } else {
          tokenType = TokenTypeEnum::scNegativeDecimal;
        }
      } else {
        tokenType = TokenTypeEnum::scMinus;
      }
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Asterisk):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Asterisk):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
        switch (uis.ahead(2)) {
        case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
          tokenType = TokenTypeEnum::scPowerWrappingAssign;
          symbolSize++;
          break;
        default:
          tokenType = TokenTypeEnum::scPowerWrapping;
          break;
        }
        symbolSize++;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
        switch (uis.ahead(2)) {
        case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
          tokenType = TokenTypeEnum::scPowerSaturatingAssign;
          symbolSize++;
          break;
        default:
          tokenType = TokenTypeEnum::scPowerSaturating;
          break;
        }
        symbolSize++;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scPowerAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scPower;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMultipleWrappingAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scMultipleWrapping;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMultipleSaturatingAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scMultipleSaturating;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scMultipleAssign;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scMultiple;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Slash):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Slash):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
        tokenType = TokenTypeEnum::scBlockCommentOutOpen;
        symbolSize++;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
        tokenType = TokenTypeEnum::scBlockCommentOutClose;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scOnelineCommentOut;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::NumberSign):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
        tokenType = TokenTypeEnum::scBlockCommentOutDocOpen;
        symbolSize++;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
        tokenType = TokenTypeEnum::scBlockCommentOutDocClose;
        symbolSize++;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Exclamation):
        switch (uis.ahead(2)) {
        case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
          tokenType = TokenTypeEnum::scBlockCommentOutDocOpenTopLevel;
          symbolSize++;
          break;
        default:
          tokenType = TokenTypeEnum::scOnelineCommentOutDocTopLevel;
          break;
        }
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scOnelineCommentOutDoc;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scDivideAssign;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scDivide;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scModuloAssign;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scModulo;
      break;
    }
    symbolSize++;
    break;
  // bit , logical
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Ampersand):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Ampersand):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scLogicalAndAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scLogicalAnd;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scBitAndAssign;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scBitAnd;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scLogicalOrAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scLogicalOr;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scBitOrAssign;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scBitOr;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Caret):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Caret):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scLogicalExOrAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scLogicalExOr;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scBitExOrAssign;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scBitExOr;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Tilde):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scBitNotAssign;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scBitNot;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Exclamation):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scLogicalNotEqual;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scLogicalNotUnary;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scLogicalEqual;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scAssignment;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
        switch (uis.ahead(2)) {
        case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
          tokenType = TokenTypeEnum::scBitShiftLeftSaturatingAssign;
          symbolSize++;
          break;
        default:
          tokenType = TokenTypeEnum::scBitShiftLeftSaturating;
          break;
        }
        symbolSize++;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scBitShiftLeftAssign;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scBitShiftLeft;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scLessThanEqual;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scLessThan;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scArithmeticBitShiftRightAssign;
        symbolSize++;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
        switch (uis.ahead(2)) {
        case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
          tokenType = TokenTypeEnum::scLogicalBitShiftRightAssign;
          symbolSize++;
          break;
        default:
          tokenType = TokenTypeEnum::scLogicalBitShiftRight;
          break;
        }
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scArithmeticBitShiftRight;
        break;
      }
      symbolSize++;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scGreaterThanEqual;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scGreaterThan;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Dollar):
    if (CharCode::Utf32::isIdentifierChar(uis.ahead(0))) {
      tokenType = TokenTypeEnum::scIdentifierPrefix;
    } else {
      tokenType = TokenTypeEnum::scDollar;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::NumberSign):
    tokenType = TokenTypeEnum::scNumberSign;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Question):
    tokenType = TokenTypeEnum::scQuestion;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::AtSign):
    tokenType = TokenTypeEnum::scAtSign;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Colon):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Colon):
      tokenType = TokenTypeEnum::scNameSpaceSeparater;
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scColon;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::SemiColon):
    tokenType = TokenTypeEnum::scSemiColon;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Comma):
    tokenType = TokenTypeEnum::scComma;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Dot):
    switch (uis.ahead(0)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Dot):
      switch (uis.ahead(1)) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Dot):
        tokenType = TokenTypeEnum::scDotDotDot;
        symbolSize++;
        break;
      default:
        tokenType = TokenTypeEnum::scDotDot;
        break;
      }
      symbolSize++;
      break;
    default:
      tokenType = TokenTypeEnum::scDot;
      break;
    }
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::BackSlash):
    tokenType = TokenTypeEnum::scBackSlash;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::SingleQuotation):
    tokenType = TokenTypeEnum::scSingleQuotation;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::DoubleQuotation):
    tokenType = TokenTypeEnum::scDoubleQuotation;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::BackQuotation):
    tokenType = TokenTypeEnum::scBackQuotation;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::ParenthesesOpen):
    tokenType = TokenTypeEnum::scParenthesesOpen;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::ParenthesesClose):
    tokenType = TokenTypeEnum::scParenthesesClose;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::CurlyBracketOpen):
    tokenType = TokenTypeEnum::scCurlyBracketOpen;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::CurlyBracketClose):
    tokenType = TokenTypeEnum::scCurlyBracketClose;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::SquareBracketOpen):
    tokenType = TokenTypeEnum::scSquareBracketOpen;
    symbolSize++;
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::SquareBracketClose):
    tokenType = TokenTypeEnum::scSquareBracketClose;
    symbolSize++;
    break;
  default:
    break;
  }
  if (symbolSize == 0) {
    return;
  }
  uis.skip(symbolSize);
  pushToken(tokenType, symbolSize);
  if (TokenType::isCommentOutOnelineOpen(tokenType)) {
    scanningOnelineComment(tokenType);
  } else if (TokenType::isCommentOutBlockOpen(tokenType)) {
    scanningBlockComment(tokenType);
  } else if (tokenType == TokenTypeEnum::scSingleQuotation) {
    scanningSingleCharacterLiteral();
  } else if (tokenType == TokenTypeEnum::scDoubleQuotation) {
    scanningStringLiteral();
  } else if (tokenType == TokenTypeEnum::scBackQuotation) {
    scanningRawStringLiteral();
  }
};
void LexicalAnalyzer::scanningOnelineComment(
    const enum TokenTypeEnum &tokenType_) {
  scanningSpaces();
  if (!uis.hasReadable() || CharCode::Utf32::isLineBreak(uis.current())) {
    return;
  }
  tokenBeginLocation = location;
  bool isForDoc = TokenType::isCommentOutOpenForDoc(tokenType_) ||
                  TokenType::isCommentOutOpenForDocTopLevel(tokenType_);
  bool isDocTagToken = true;
  bool isSkipSpace = true;
  if (!isForDoc) {
    isDocTagToken = false;
    isSkipSpace = false;
  }
  while (uis.hasReadable()) {
    int32_t charCode = uis.current();
    if (CharCode::Utf32::isLineBreak(charCode)) {
      return;
    }
    if (CharCode::Utf32::isSpaceChar(charCode)) {
      scanningSpaces();
      if (!isSkipSpace) {
        pushToken(TokenTypeEnum::coSpace);
      } else {
        tokenBeginLocation = location;
        isSkipSpace = false;
      }
    } else {
      int32_t cosCharCode = charCode;
      while (uis.hasReadable()) {
        cosCharCode = uis.current();
        if (CharCode::Utf32::isSpaceChar(cosCharCode) ||
            CharCode::Utf32::isLineBreak(cosCharCode)) {
          break;
        } else {
          if (isForDoc && isDocTagToken) {
            if (uint32_t(cosCharCode) ==
                    static_cast<uint32_t>(CharCode::UtfAsciiTable::AtSign) &&
                CharCode::Utf32::isAlphabetChar(uis.ahead())) {
              uis.skip();
              pushToken(TokenTypeEnum::scDocTagOpen, 1);
              while (uis.hasReadable() &&
                     CharCode::Utf32::isAlphabetNumberChar(uis.current())) {
                uis.skip();
              }
              break;
            } else {
              if (tis.tailTokenType() != TokenTypeEnum::scDocTagOpen) {
                isDocTagToken = false;
              }
              uis.skip();
            }
          } else {
            uis.skip();
          }
        }
      }
      size_t coStringSize =
          uis.currentPos() - tokenBeginLocation.getBufferPos();
      if (coStringSize > 0) {
        if (isDocTagToken) {
          pushToken(TokenTypeEnum::coDocTag, coStringSize);
          isDocTagToken = false;
          isSkipSpace = true;
        } else {
          pushToken(TokenTypeEnum::coString, coStringSize);
          isSkipSpace = false;
        }
      }
    }
  }
};
void LexicalAnalyzer::scanningBlockComment(
    const enum TokenTypeEnum &tokenType_) {
  toNextToken();
  if (!uis.hasReadable()) {
    return;
  }
  tokenBeginLocation = location;
  bool isForDoc = TokenType::isCommentOutOpenForDoc(tokenType_) ||
                  TokenType::isCommentOutOpenForDocTopLevel(tokenType_);
  bool isDocTagToken = true;
  bool isSkipSpace = true;
  bool isCloseBlockComment = false;
  if (!isForDoc) {
    isDocTagToken = false;
    isSkipSpace = false;
  }
  while (uis.hasReadable()) {
    int32_t charCode = uis.current();
    if (CharCode::Utf32::isLineBreak(charCode)) {
      scanningLineBreaks();
      if (isForDoc) {
        pushToken(TokenTypeEnum::coDocLineBreak);
      } else {
        pushToken(TokenTypeEnum::coLineBreak);
      }
      if (isForDoc) {
        isDocTagToken = true;
        isSkipSpace = true;
      }
      toNextToken();
      if (!uis.hasReadable()) {
        return;
      }
      tokenBeginLocation = location;
    } else if (CharCode::Utf32::isSpaceChar(charCode)) {
      scanningSpaces();
      if (!isSkipSpace) {
        pushToken(TokenTypeEnum::coSpace);
      } else {
        tokenBeginLocation = location;
        isSkipSpace = false;
      }
    } else {
      int32_t cosCharCode = charCode;
      while (uis.hasReadable()) {
        cosCharCode = uis.current();
        if (CharCode::Utf32::isSpaceChar(cosCharCode) ||
            CharCode::Utf32::isLineBreak(cosCharCode)) {
          break;
        } else {
          if ((!isForDoc &&
               uint32_t(cosCharCode) ==
                   static_cast<uint32_t>(CharCode::UtfAsciiTable::Slash) &&
               uint32_t(uis.ahead()) ==
                   static_cast<uint32_t>(CharCode::UtfAsciiTable::Slash) &&
               uint32_t(uis.ahead(1)) ==
                   static_cast<uint32_t>(
                       CharCode::UtfAsciiTable::GreaterThan)) ||
              (isForDoc &&
               uint32_t(cosCharCode) ==
                   static_cast<uint32_t>(CharCode::UtfAsciiTable::Slash) &&
               uint32_t(uis.ahead()) ==
                   static_cast<uint32_t>(CharCode::UtfAsciiTable::NumberSign) &&
               uint32_t(uis.ahead(1)) ==
                   static_cast<uint32_t>(
                       CharCode::UtfAsciiTable::GreaterThan))) {
            isCloseBlockComment = true;
            break;
          }
          if (isForDoc && isDocTagToken) {
            if (uint32_t(cosCharCode) ==
                    static_cast<uint32_t>(CharCode::UtfAsciiTable::AtSign) &&
                CharCode::Utf32::isAlphabetChar(uis.ahead())) {
              uis.skip();
              pushToken(TokenTypeEnum::scDocTagOpen, 1);
              while (uis.hasReadable() &&
                     CharCode::Utf32::isAlphabetNumberChar(uis.current())) {
                uis.skip();
              }
              break;
            } else {
              if (tis.tailTokenType() != TokenTypeEnum::scDocTagOpen) {
                isDocTagToken = false;
              }
              uis.skip();
            }
          } else {
            uis.skip();
          }
        }
      }
      size_t coStringSize =
          uis.currentPos() - tokenBeginLocation.getBufferPos();
      if (coStringSize > 0) {
        if (isDocTagToken) {
          pushToken(TokenTypeEnum::coDocTag, coStringSize);
          isDocTagToken = false;
          isSkipSpace = true;
        } else {
          pushToken(TokenTypeEnum::coString, coStringSize);
          isSkipSpace = false;
        }
      }
      if (isCloseBlockComment) {
        scanningSymbol();
        return;
      }
    }
  }
};
void LexicalAnalyzer::scanningSingleCharacterLiteral() {
  int32_t charCode = uis.current();
  if (uint32_t(charCode) ==
      static_cast<uint32_t>(CharCode::UtfAsciiTable::SingleQuotation)) {
    Token *errTokenPtr =
        createToken(TokenTypeEnum::unableEmptyCharInLtSingleChar, 1);
    Token errToken = *(errTokenPtr);
    delete errTokenPtr;
    throw new TokenizeError(errToken, lines.getLineString(location.getLine()));
  }
  if (uint32_t(charCode) ==
      static_cast<uint32_t>(CharCode::UtfAsciiTable::BackSlash)) {
    scanningEscapeSequence(TokenTypeEnum::scSingleQuotation);
  } else if (uint32_t(uis.ahead()) !=
             static_cast<uint32_t>(CharCode::UtfAsciiTable::SingleQuotation)) {
    while (uis.hasReadable()) {
      if (uint32_t(uis.current()) !=
              static_cast<uint32_t>(CharCode::UtfAsciiTable::SingleQuotation) &&
          !CharCode::Utf32::isLineBreak(uis.current())) {
        uis.skip();
      } else {
        break;
      }
    }
    TokenTypeEnum errTokenType =
        TokenTypeEnum::unableMultipleCharInLtSingleChar;
    if (!uis.hasReadable() || CharCode::Utf32::isLineBreak(uis.current())) {
      errTokenType = TokenTypeEnum::notClosedLtSingleChar;
      uis.skip();
    }
    Token *errTokenPtr = createToken(
        errTokenType, uis.currentPos() - tokenBeginLocation.getBufferPos());
    Token errToken = *(errTokenPtr);
    delete errTokenPtr;
    throw new TokenizeError(errToken, lines.getLineString(location.getLine()));
  } else {
    if (CharCode::Utf32::isLineBreak(uis.current())) {
      uis.skip();
      Token *errTokenPtr =
          createToken(TokenTypeEnum::unableLineBreakCharInLtSingleChar,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    }
    uis.skip();
    pushToken(TokenTypeEnum::ltSingleCharacter, 1);
    uis.skip();
    pushToken(TokenTypeEnum::scSingleQuotation, 1);
  }
};
void LexicalAnalyzer::scanningStringLiteral() {
  int32_t charCode = uis.current();
  if (uint32_t(charCode) ==
      static_cast<uint32_t>(CharCode::UtfAsciiTable::DoubleQuotation)) {
    pushToken(TokenTypeEnum::scDoubleQuotation, 1);
    return;
  }
  while (uis.hasReadable()) {
    charCode = uis.current();
    if (uint32_t(charCode) ==
        static_cast<uint32_t>(CharCode::UtfAsciiTable::BackSlash)) {
      scanningEscapeSequence(TokenTypeEnum::scDoubleQuotation);
      continue;
    }
    while (uis.hasReadable()) {
      if (uint32_t(uis.current()) !=
              static_cast<uint32_t>(CharCode::UtfAsciiTable::DoubleQuotation) &&
          !CharCode::Utf32::isLineBreak(uis.current())) {
        uis.skip();
      } else {
        break;
      }
    }
    size_t ltStringSize = uis.currentPos() - tokenBeginLocation.getBufferPos();
    if (ltStringSize > 0) {
      pushToken(TokenTypeEnum::ltString, ltStringSize);
    }
    if (uint32_t(uis.current()) ==
        static_cast<uint32_t>(CharCode::UtfAsciiTable::DoubleQuotation)) {
      uis.skip();
      pushToken(TokenTypeEnum::scDoubleQuotation, 1);
      return;
    } else if (CharCode::Utf32::isLineBreak(uis.current())) {
      scanningLineBreaks();
      pushToken(TokenTypeEnum::ltStringLineBreak);
    }
  }
};
void LexicalAnalyzer::scanningRawStringLiteral() {
  int32_t charCode = uis.current();
  if (uint32_t(charCode) ==
      static_cast<uint32_t>(CharCode::UtfAsciiTable::BackQuotation)) {
    pushToken(TokenTypeEnum::scBackQuotation, 1);
    return;
  }
  while (uis.hasReadable()) {
    charCode = uis.current();
    if (uint32_t(charCode) ==
        static_cast<uint32_t>(CharCode::UtfAsciiTable::BackSlash)) {
      scanningEscapeSequence(TokenTypeEnum::scBackQuotation);
      if (tokenBeginLocation.getBufferPos() != uis.currentPos()) {
        continue;
      }
    }
    while (uis.hasReadable()) {
      if (uint32_t(uis.current()) !=
              static_cast<uint32_t>(CharCode::UtfAsciiTable::BackQuotation) &&
          !CharCode::Utf32::isLineBreak(uis.current())) {
        uis.skip();
      } else {
        break;
      }
    }
    size_t ltRawStringSize =
        uis.currentPos() - tokenBeginLocation.getBufferPos();
    if (ltRawStringSize > 0) {
      pushToken(TokenTypeEnum::ltRawString, ltRawStringSize);
    }
    if (uint32_t(uis.current()) ==
        static_cast<uint32_t>(CharCode::UtfAsciiTable::BackQuotation)) {
      uis.skip();
      pushToken(TokenTypeEnum::scBackQuotation, 1);
      return;
    } else if (CharCode::Utf32::isLineBreak(uis.current())) {
      scanningLineBreaks();
      pushToken(TokenTypeEnum::ltRawStringLineBreak);
    }
  }
};
void LexicalAnalyzer::scanningEscapeSequence(
    const enum TokenTypeEnum &tokenType_) {
  Location tokenBeginLocForSingleCharErr = tokenBeginLocation;
  uis.skip();
  int32_t escapeCharCode = uis.read();
  if (tokenType_ == TokenTypeEnum::scBackQuotation) {
    if (uint32_t(escapeCharCode) ==
        static_cast<uint32_t>(CharCode::UtfAsciiTable::BackQuotation)) {
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceBackQuotation, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::BackQuotation));
    } else {
      uis.rewind(2);
    }
    return;
  }
  if (tokenType_ == TokenTypeEnum::scDoubleQuotation &&
      uint32_t(escapeCharCode) ==
          static_cast<uint32_t>(CharCode::UtfAsciiTable::DoubleQuotation)) {
    pushTokenEscapeCharCode(
        TokenTypeEnum::ltEscapeSequenceDoubleQuotation, 2,
        static_cast<int32_t>(CharCode::UtfAsciiTable::DoubleQuotation));
    return;
  }
  bool isSingleCharacter = tokenType_ == TokenTypeEnum::scSingleQuotation;
  if (tokenType_ == TokenTypeEnum::scSingleQuotation &&
      uint32_t(escapeCharCode) ==
          static_cast<uint32_t>(CharCode::UtfAsciiTable::SingleQuotation)) {
    pushTokenEscapeCharCode(
        TokenTypeEnum::ltEscapeSequenceSingleQuotation, 2,
        static_cast<int32_t>(CharCode::UtfAsciiTable::SingleQuotation));
  } else {
    switch (uint32_t(escapeCharCode)) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerA):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceBellAlert, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::BellAlert));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerB):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceBackspace, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::Backspace));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerT):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceHorizontalTab, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::HorizontalTab));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerN):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceLineFeed, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::LineFeed));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerV):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceVerticalTab, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::VerticalTab));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerR):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceCarriageReturn, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::CarriageReturn));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerF):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceFormFeed, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::FormFeed));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerE):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceAnsiEscape, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::Escape));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::BackSlash):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceBackSlash, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::BackSlash));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Number0):
      pushTokenEscapeCharCode(
          TokenTypeEnum::ltEscapeSequenceNullChar, 2,
          static_cast<int32_t>(CharCode::UtfAsciiTable::NullChar));
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerO):
      if (CharCode::Utf32::isOctalDigitChar(uis.current())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal, 2);
        scanningEscapeSequenceUtf8CodeOctal(false, isSingleCharacter);
      } else if (uint32_t(uis.current()) ==
                     static_cast<uint32_t>(
                         CharCode::UtfAsciiTable::CurlyBracketOpen) &&
                 CharCode::Utf32::isOctalDigitChar(uis.ahead())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal, 2);
        uis.skip();
        pushToken(TokenTypeEnum::ltUtfCodeOpen, 1);
        scanningEscapeSequenceUtf8CodeOctal(true, isSingleCharacter);
      } else {
        Token *errTokenPtr =
            createToken(TokenTypeEnum::invalidEscapeSequence, 2);
        Token errToken = *(errTokenPtr);
        delete errTokenPtr;
        throw new TokenizeError(errToken,
                                lines.getLineString(location.getLine()));
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerX):
      if (CharCode::Utf32::isHexadecimalDigitChar(uis.current())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal, 2);
        scanningEscapeSequenceUtf8CodeHexadecimal(false, isSingleCharacter);
      } else if (uint32_t(uis.current()) ==
                     static_cast<uint32_t>(
                         CharCode::UtfAsciiTable::CurlyBracketOpen) &&
                 CharCode::Utf32::isHexadecimalDigitChar(uis.ahead())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal, 2);
        uis.skip();
        pushToken(TokenTypeEnum::ltUtfCodeOpen, 1);
        scanningEscapeSequenceUtf8CodeHexadecimal(true, isSingleCharacter);
      } else {
        Token *errTokenPtr =
            createToken(TokenTypeEnum::invalidEscapeSequence, 2);
        Token errToken = *(errTokenPtr);
        delete errTokenPtr;
        throw new TokenizeError(errToken,
                                lines.getLineString(location.getLine()));
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LowerU):
      if (CharCode::Utf32::isHexadecimalDigitChar(uis.current())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal, 2);
        scanningEscapeSequenceUtf16CodeHexadecimal(false, isSingleCharacter);
      } else if (uint32_t(uis.current()) ==
                     static_cast<uint32_t>(
                         CharCode::UtfAsciiTable::CurlyBracketOpen) &&
                 CharCode::Utf32::isHexadecimalDigitChar(uis.ahead())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal, 2);
        uis.skip();
        pushToken(TokenTypeEnum::ltUtfCodeOpen, 1);
        scanningEscapeSequenceUtf16CodeHexadecimal(true, isSingleCharacter);
      } else {
        Token *errTokenPtr =
            createToken(TokenTypeEnum::invalidEscapeSequence, 2);
        Token errToken = *(errTokenPtr);
        delete errTokenPtr;
        throw new TokenizeError(errToken,
                                lines.getLineString(location.getLine()));
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::UpperU):
      if (CharCode::Utf32::isHexadecimalDigitChar(uis.current())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal, 2);
        scanningEscapeSequenceUtf32CodeHexadecimal(false, isSingleCharacter);
      } else if (uint32_t(uis.current()) ==
                     static_cast<uint32_t>(
                         CharCode::UtfAsciiTable::CurlyBracketOpen) &&
                 CharCode::Utf32::isHexadecimalDigitChar(uis.ahead())) {
        pushToken(TokenTypeEnum::ltEscapeSequenceUtf32CodeHexadecimal, 2);
        uis.skip();
        pushToken(TokenTypeEnum::ltUtfCodeOpen, 1);
        scanningEscapeSequenceUtf32CodeHexadecimal(true, isSingleCharacter);
      } else {
        Token *errTokenPtr =
            createToken(TokenTypeEnum::invalidEscapeSequence, 2);
        Token errToken = *(errTokenPtr);
        delete errTokenPtr;
        throw new TokenizeError(errToken,
                                lines.getLineString(location.getLine()));
      }
      break;
    default:
      Token *errTokenPtr = createToken(TokenTypeEnum::invalidEscapeSequence, 2);
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    }
  }
  if (tokenType_ == TokenTypeEnum::scSingleQuotation) {
    if (uint32_t(uis.current()) !=
        static_cast<int32_t>(CharCode::UtfAsciiTable::SingleQuotation)) {
      tokenBeginLocation = tokenBeginLocForSingleCharErr;
      while (uis.hasReadable()) {
        if (uint32_t(uis.current()) !=
                static_cast<uint32_t>(
                    CharCode::UtfAsciiTable::SingleQuotation) &&
            !CharCode::Utf32::isLineBreak(uis.current())) {
          uis.skip();
        } else {
          break;
        }
      }
      TokenTypeEnum errTokenType =
          TokenTypeEnum::unableMultipleCharInLtSingleChar;
      if (!uis.hasReadable() || CharCode::Utf32::isLineBreak(uis.current())) {
        errTokenType = TokenTypeEnum::notClosedLtSingleChar;
        uis.skip();
      }
      Token *errTokenPtr = createToken(
          errTokenType, uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else {
      uis.skip();
      pushToken(TokenTypeEnum::scSingleQuotation, 1);
    }
  }
};
void LexicalAnalyzer::scanningEscapeSequenceUtf8CodeOctal(
    const bool &isInBrackets_, const bool &isSingleCharacter_) {
  uint32_t utf8CharCode = 0;
  size_t maxDigitLen = 11;
  size_t digitPos = 0;
  size_t paddingCount = 0;
  size_t parsedBitCount = 0;
  const size_t maxPaddingCount = 3;
  const size_t shiftBitCount = 3;
  bool isEnablePadding = !isInBrackets_ && !isSingleCharacter_;
  bool isNullPadding = false;
  while (uis.hasReadable() && digitPos < maxDigitLen) {
    uint32_t octalCharDigit = uis.current();
    if (CharCode::Utf32::isOctalDigitChar(octalCharDigit)) {
      uint32_t octalDigit =
          CharCode::Utf32::toDecimalFromOctalChar(octalCharDigit);
      if (utf8CharCode == 0) {
        if (digitPos == 0 && octalDigit > 3) {
          maxDigitLen--;
        }
        utf8CharCode = octalDigit;
        if (octalDigit == 0 && isEnablePadding) {
          paddingCount++;
          parsedBitCount += shiftBitCount;
          if (isEnablePadding && paddingCount == maxPaddingCount) {
            uis.skip();
            digitPos++;
            isNullPadding = true;
            break;
          }
        } else {
          switch (octalDigit) {
          case 1:
            parsedBitCount++;
            if (isEnablePadding && paddingCount > 0) {
              parsedBitCount++;
            }
            break;
          case 2:
          case 3:
            parsedBitCount += 2;
            break;
          case 4:
          case 5:
          case 6:
          case 7:
            parsedBitCount += 3;
            if (isEnablePadding && paddingCount > 0) {
              parsedBitCount--;
            }
            break;
          }
        }
      } else {
        utf8CharCode <<= shiftBitCount;
        utf8CharCode |= octalDigit;
        parsedBitCount += shiftBitCount;
      }
      uis.skip();
      digitPos++;
    } else {
      break;
    }
  }
  if (isInBrackets_) {
    if (uint32_t(uis.current()) !=
        static_cast<uint32_t>(CharCode::UtfAsciiTable::CurlyBracketClose)) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::notClosedLtUtfCharCode,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else if (!CharCode::Utf8::isValidCharCode(utf8CharCode)) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::invalidUtf8CharCodeOctal,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else {
      pushTokenEscapeUtfCharCode(
          TokenTypeEnum::ltUtf8CodeOctal,
          uis.currentPos() - tokenBeginLocation.getBufferPos(),
          CharCode::Utf8::toU32(int32_t(utf8CharCode)), true);
    }
  } else {
    const ssize_t oneByteBitCount = 8;
    if (isEnablePadding && !isNullPadding) {
      ssize_t surplusBitCount = (ssize_t)parsedBitCount;
      if (parsedBitCount > oneByteBitCount) {
        while (surplusBitCount >= oneByteBitCount) {
          surplusBitCount -= oneByteBitCount;
        }
        while (surplusBitCount > 0) {
          uis.undo();
          utf8CharCode >>= shiftBitCount;
          parsedBitCount -= shiftBitCount;
          surplusBitCount -= shiftBitCount;
        }
      }
    }
    size_t nextMinBitCount = 24;
    const size_t maxAsciiBitCount = 7;
    while (!CharCode::Utf8::isValidCharCode(utf8CharCode)) {
      if (nextMinBitCount >= maxAsciiBitCount) {
        while (parsedBitCount > nextMinBitCount) {
          uis.undo();
          utf8CharCode >>= shiftBitCount;
          parsedBitCount -= shiftBitCount;
        }
        if (nextMinBitCount > oneByteBitCount) {
          nextMinBitCount -= oneByteBitCount;
        } else {
          nextMinBitCount--;
        }
      }
    }
    pushTokenEscapeUtfCharCode(
        TokenTypeEnum::ltUtf8CodeOctal,
        uis.currentPos() - tokenBeginLocation.getBufferPos(),
        CharCode::Utf8::toU32(int32_t(utf8CharCode)), false);
  }
};
void LexicalAnalyzer::scanningEscapeSequenceUtf8CodeHexadecimal(
    const bool &isInBrackets_, const bool &isSingleCharacter_) {
  uint32_t utf8CharCode = 0;
  size_t maxDigitLen = 8;
  size_t digitPos = 0;
  size_t paddingCount = 0;
  size_t parsedBitCount = 0;
  const size_t maxPaddingCount = 2;
  const size_t shiftBitCount = 4;
  bool isEnablePadding = !isInBrackets_ && !isSingleCharacter_;
  while (uis.hasReadable() && digitPos < maxDigitLen) {
    uint32_t hexadecimalCharDigit = uis.current();
    if (CharCode::Utf32::isHexadecimalDigitChar(hexadecimalCharDigit)) {
      uint32_t hexadecimalDigit =
          CharCode::Utf32::toDecimalFromHexadecimalChar(hexadecimalCharDigit);
      if (utf8CharCode == 0) {
        utf8CharCode = hexadecimalDigit;
        parsedBitCount += shiftBitCount;
        if (hexadecimalDigit == 0 && isEnablePadding) {
          paddingCount++;
          if (isEnablePadding && paddingCount == maxPaddingCount) {
            uis.skip();
            digitPos++;
            break;
          }
        }
      } else {
        utf8CharCode <<= shiftBitCount;
        utf8CharCode |= hexadecimalDigit;
        parsedBitCount += shiftBitCount;
      }
      uis.skip();
      digitPos++;
    } else {
      break;
    }
  }
  if (isInBrackets_) {
    if (uint32_t(uis.current()) !=
        static_cast<uint32_t>(CharCode::UtfAsciiTable::CurlyBracketClose)) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::notClosedLtUtfCharCode,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else if (!CharCode::Utf8::isValidCharCode(utf8CharCode)) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::invalidUtf8CharCodeHexadecimal,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else {
      pushTokenEscapeUtfCharCode(
          TokenTypeEnum::ltUtf8CodeHexadecimal,
          uis.currentPos() - tokenBeginLocation.getBufferPos(),
          CharCode::Utf8::toU32(int32_t(utf8CharCode)), true);
    }
  } else {
    const ssize_t oneByteBitCount = 8;
    size_t nextMinBitCount = 24;
    const size_t oneHexdecBitCount = 4;
    while (!CharCode::Utf8::isValidCharCode(utf8CharCode)) {
      if (nextMinBitCount >= oneHexdecBitCount) {
        while (parsedBitCount > nextMinBitCount) {
          uis.undo();
          utf8CharCode >>= shiftBitCount;
          parsedBitCount -= shiftBitCount;
        }
        if (nextMinBitCount > oneByteBitCount) {
          nextMinBitCount -= oneByteBitCount;
        } else {
          nextMinBitCount -= oneHexdecBitCount;
        }
      }
    }
    pushTokenEscapeUtfCharCode(
        TokenTypeEnum::ltUtf8CodeHexadecimal,
        uis.currentPos() - tokenBeginLocation.getBufferPos(),
        CharCode::Utf8::toU32(int32_t(utf8CharCode)), false);
  }
};
void LexicalAnalyzer::scanningEscapeSequenceUtf16CodeHexadecimal(
    const bool &isInBrackets_, const bool &isSingleCharacter_) {
  uint32_t utf16CharCode = 0;
  size_t maxDigitLen = 8;
  size_t digitPos = 0;
  size_t paddingCount = 0;
  size_t parsedBitCount = 0;
  const size_t maxPaddingCount = 4;
  const size_t shiftBitCount = 4;
  bool isEnablePadding = !isInBrackets_ && !isSingleCharacter_;
  while (uis.hasReadable() && digitPos < maxDigitLen) {
    uint32_t hexadecimalCharDigit = uis.current();
    if (CharCode::Utf32::isHexadecimalDigitChar(hexadecimalCharDigit)) {
      uint32_t hexadecimalDigit =
          CharCode::Utf32::toDecimalFromHexadecimalChar(hexadecimalCharDigit);
      if (utf16CharCode == 0) {
        utf16CharCode = hexadecimalDigit;
        parsedBitCount += shiftBitCount;
        if (hexadecimalDigit == 0 && isEnablePadding) {
          paddingCount++;
          if (isEnablePadding && paddingCount == maxPaddingCount) {
            uis.skip();
            digitPos++;
            break;
          }
        }
      } else {
        utf16CharCode <<= shiftBitCount;
        utf16CharCode |= hexadecimalDigit;
        parsedBitCount += shiftBitCount;
      }
      uis.skip();
      digitPos++;
    } else {
      break;
    }
  }
  if (isInBrackets_) {
    if (uint32_t(uis.current()) !=
        static_cast<uint32_t>(CharCode::UtfAsciiTable::CurlyBracketClose)) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::notClosedLtUtfCharCode,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else if (!CharCode::Utf16::isValidCharCode(int32_t(utf16CharCode), false,
                                                 false)) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::invalidUtf16CharCodeHexadecimal,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else {
      pushTokenEscapeUtfCharCode(
          TokenTypeEnum::ltUtf16CodeHexadecimal,
          uis.currentPos() - tokenBeginLocation.getBufferPos(),
          CharCode::Utf16::toU32(int32_t(utf16CharCode)), true);
    }
  } else {
    const ssize_t oneByteBitCount = 8;
    size_t nextMinBitCount = 24;
    if (isEnablePadding) {
      nextMinBitCount = 16;
    }
    const size_t oneHexdecBitCount = 4;
    while (!CharCode::Utf16::isValidCharCode(int32_t(utf16CharCode), false,
                                             false)) {
      if (nextMinBitCount >= oneHexdecBitCount) {
        while (parsedBitCount > nextMinBitCount) {
          uis.undo();
          utf16CharCode >>= shiftBitCount;
          parsedBitCount -= shiftBitCount;
        }
        if (nextMinBitCount > oneByteBitCount) {
          nextMinBitCount -= oneByteBitCount;
        } else {
          nextMinBitCount -= oneHexdecBitCount;
        }
      }
    }
    pushTokenEscapeUtfCharCode(
        TokenTypeEnum::ltUtf16CodeHexadecimal,
        uis.currentPos() - tokenBeginLocation.getBufferPos(),
        CharCode::Utf16::toU32(int32_t(utf16CharCode)), false);
  }
};
void LexicalAnalyzer::scanningEscapeSequenceUtf32CodeHexadecimal(
    const bool &isInBrackets_, const bool &isSingleCharacter_) {
  uint32_t utf32CharCode = 0;
  size_t maxDigitLen = 6;
  size_t digitPos = 0;
  size_t parsedBitCount = 0;
  const size_t shiftBitCount = 4;
  while (uis.hasReadable() && digitPos < maxDigitLen) {
    uint32_t hexadecimalCharDigit = uis.current();
    if (CharCode::Utf32::isHexadecimalDigitChar(hexadecimalCharDigit)) {
      uint32_t hexadecimalDigit =
          CharCode::Utf32::toDecimalFromHexadecimalChar(hexadecimalCharDigit);
      if (utf32CharCode == 0) {
        utf32CharCode = hexadecimalDigit;
        parsedBitCount += shiftBitCount;
      } else {
        utf32CharCode <<= shiftBitCount;
        utf32CharCode |= hexadecimalDigit;
        parsedBitCount += shiftBitCount;
      }
      uis.skip();
      digitPos++;
    } else {
      break;
    }
  }
  if (isInBrackets_) {
    if (uint32_t(uis.current()) !=
        static_cast<uint32_t>(CharCode::UtfAsciiTable::CurlyBracketClose)) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::notClosedLtUtfCharCode,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else if (!CharCode::Utf32::isValidCharCode(int32_t(utf32CharCode))) {
      Token *errTokenPtr =
          createToken(TokenTypeEnum::invalidUtf32CharCodeHexadecimal,
                      uis.currentPos() - tokenBeginLocation.getBufferPos());
      Token errToken = *(errTokenPtr);
      delete errTokenPtr;
      throw new TokenizeError(errToken,
                              lines.getLineString(location.getLine()));
    } else {
      pushTokenEscapeUtfCharCode(TokenTypeEnum::ltUtf32CodeHexadecimal,
                                 uis.currentPos() -
                                     tokenBeginLocation.getBufferPos(),
                                 int32_t(utf32CharCode), true);
    }
  } else {
    const ssize_t oneByteBitCount = 8;
    size_t nextMinBitCount = 24;
    const size_t oneHexdecBitCount = 4;
    while (!CharCode::Utf32::isValidCharCode(int32_t(utf32CharCode))) {
      if (nextMinBitCount >= oneHexdecBitCount) {
        while (parsedBitCount > nextMinBitCount) {
          uis.undo();
          utf32CharCode >>= shiftBitCount;
          parsedBitCount -= shiftBitCount;
        }
        if (nextMinBitCount > oneByteBitCount) {
          nextMinBitCount -= oneByteBitCount;
        } else {
          nextMinBitCount -= oneHexdecBitCount;
        }
      }
    }
    pushTokenEscapeUtfCharCode(TokenTypeEnum::ltUtf32CodeHexadecimal,
                               uis.currentPos() -
                                   tokenBeginLocation.getBufferPos(),
                               int32_t(utf32CharCode), false);
  }
};

void LexicalAnalyzer::pushToken(const enum TokenTypeEnum &tokenType_,
                                const size_t &tokenSize_) {
  location = Location(tokenBeginLocation.getFilename(),
                      tokenBeginLocation.getBufferPos() + tokenSize_,
                      tokenBeginLocation.getLine(),
                      tokenBeginLocation.getColumn() + tokenSize_);
  return pushToken(tokenType_);
};
void LexicalAnalyzer::pushToken(const enum TokenTypeEnum &tokenType_) {
  Token *token = createToken(tokenType_);
  tokens.push(token);
  tokenBeginLocation = location;
};
Token *LexicalAnalyzer::createToken(const enum TokenTypeEnum &tokenType_,
                                    const size_t &tokenSize_) {
  location = Location(tokenBeginLocation.getFilename(),
                      tokenBeginLocation.getBufferPos() + tokenSize_,
                      tokenBeginLocation.getLine(),
                      tokenBeginLocation.getColumn() + tokenSize_);
  return createToken(tokenType_);
};
Token *LexicalAnalyzer::createToken(const enum TokenTypeEnum &tokenType_) {
  size_t tokenBeginPos = tokenBeginLocation.getBufferPos();
  size_t tokenEndPos = location.getBufferPos();
  std::vector<int32_t> &uisData = uis.dataRef();
  std::u32string tokenStr(uisData.begin() + tokenBeginPos,
                          uisData.begin() + tokenEndPos);
  return new Token(tokenBeginLocation, tokenType_, tokenStr);
};
void LexicalAnalyzer::pushTokenEscapeCharCode(
    const enum TokenTypeEnum &tokenType_, const size_t &tokenSize_,
    const int32_t &escapeCharCode_) {
  location =
      Location(location.getFilename(), location.getBufferPos() + tokenSize_,
               location.getLine(), location.getColumn() + tokenSize_);
  size_t tokenBeginPos = tokenBeginLocation.getBufferPos();
  size_t tokenEndPos = location.getBufferPos();
  std::vector<int32_t> &uisData = uis.dataRef();
  std::u32string tokenStr(uisData.begin() + tokenBeginPos,
                          uisData.begin() + tokenEndPos);
  Token *token =
      new Token(tokenBeginLocation, tokenType_, tokenStr, escapeCharCode_);
  tokens.push(token);
  tokenBeginLocation = location;
};

void LexicalAnalyzer::pushTokenEscapeUtfCharCode(
    const enum TokenTypeEnum &defaultTokenType_, const size_t &tokenSize_,
    const int32_t &escapeUtf32CharCode_, const bool &isInBrackets_) {
  switch (uint32_t(escapeUtf32CharCode_)) {
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::NullChar):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeNullChar, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::BellAlert):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeBellAlert, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Backspace):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeBackspace, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::HorizontalTab):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeHorizontalTab, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::LineFeed):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeLineFeed, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalTab):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeVerticalTab, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::FormFeed):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeFormFeed, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::CarriageReturn):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeCarriageReturn, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Escape):
    pushTokenEscapeCharCode(TokenTypeEnum::ltUtfCodeAnsiEscape, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  default:
    pushTokenEscapeCharCode(defaultTokenType_, tokenSize_,
                            escapeUtf32CharCode_);
    break;
  }
  if (isInBrackets_) {
    uis.skip();
    pushToken(TokenTypeEnum::ltUtfCodeClose, 1);
  }
};

// size_t LexicalAnalyzer::scanningToken(const size_t &pos_) {
//   size_t tokenSize = 0;
//   char charCode0 = *(bufferPtr + pos_);
//   TokenTypeEnum prevTokenType = tis.tailTokenType();
//   if (prevTokenType != TokenTypeEnum::scDollar && charCode0 == '0') {
//     tokenSize += scanningNonDecimal(pos_);
//     if (tokenSize > 0) {
//       return tokenSize;
//     }
//   }
//   if (prevTokenType != TokenTypeEnum::scDollar &&
//       ('0' <= charCode0 && charCode0 <= '9')) {
//     tokenSize += scanningDecimalNumber(pos_);
//   } else if (prevTokenType == TokenTypeEnum::scDollar &&
//              (('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0
//              && charCode0 <= 'Z') ||
//               ('a' <= charCode0 && charCode0 <= 'z') || charCode0 == '_'))
//               {
//     tokenSize += scanningIdentifier(pos_);
//   } else if (prevTokenType != TokenTypeEnum::scDollar &&
//              (('A' <= charCode0 && charCode0 <= 'Z') || ('a' <= charCode0
//              && charCode0 <= 'z') ||
//               charCode0 == '_')) {
//     tokenSize += scanningIdentifier(pos_);
//   } else {
//     tokenSize += scanningSymbol(pos_);
//   }
//   return tokenSize;
// };

// size_t LexicalAnalyzer::scanningIdentifier(const size_t &pos_) {
//   size_t tokenSize = 0;
//   char charCode0;
//   for (charCode0 = *(bufferPtr + pos_ + tokenSize);
//        ('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0 &&
//        charCode0 <= 'Z') ||
//        ('a' <= charCode0 && charCode0 <= 'z') || charCode0 == '_';
//        tokenSize++, charCode0 = *(bufferPtr + pos_ + tokenSize))
//     ;

//   TokenTypeEnum prevTokenType = tis.tailTokenType();
//   if (prevTokenType == TokenTypeEnum::scDot ||
//       prevTokenType == TokenTypeEnum::scDollar ||
//       prevTokenType == TokenTypeEnum::ltDecimalIntegralPart ||
//       prevTokenType == TokenTypeEnum::ltDecimalFractionalPart) {
//     pushToken(pos_, tokenSize, TokenTypeEnum::identifier);
//   } else {
//     pushToken(pos_, tokenSize, TokenTypeEnum::reservedWord);
//   }
//   location = computeLocation(pos_, tokenSize, location);
//   nextToken = new Token(location);
//   // identifier
//   return tokenSize;
// };

// size_t LexicalAnalyzer::scanningNonDecimal(const size_t &pos_) {
//   size_t tokenSize = 0, numberTokenLen = 0;
//   char charCode1, charCode2;
//   charCode1 = *(bufferPtr + pos_ + 1);
//   TokenTypeEnum tokenType = TokenTypeEnum::unknown;
//   // binary number
//   if (charCode1 == 'b' || charCode1 == 'B') {
//     charCode2 = *(bufferPtr + pos_ + 2);
//     if ((charCode2 == '0' || charCode2 == '1')) {
//       tokenType = TokenTypeEnum::ltBinaryPrefix;
//       tokenSize = 2;
//       pushToken(pos_, tokenSize, tokenType);
//       location = computeLocation(pos_, tokenSize, location);
//       nextToken = new Token(location);
//       numberTokenLen = scanningBinaryNumber(pos_ + tokenSize);
//       if (numberTokenLen > 0) {
//         tokenSize += numberTokenLen;
//       }
//     } else {
//       tokenType = TokenTypeEnum::reservedWord;
//       tokenSize = 2;
//       for (size_t pos = pos_ + 2;
//            ('0' <= charCode2 && charCode2 <= '9') || ('A' <= charCode2 &&
//            charCode2 <= 'Z') ||
//            ('a' <= charCode2 && charCode2 <= 'z') || charCode2 == '_';
//            tokenSize++, pos++, charCode2 = *(bufferPtr + pos))
//         ;
//       pushToken(pos_, tokenSize, tokenType);
//       location = computeLocation(pos_, tokenSize, location);
//       nextToken = new Token(location);
//     }
//   }
//   // ocatal number
//   else if (charCode1 == 'o' || charCode1 == 'O') {
//     charCode2 = *(bufferPtr + pos_ + 2);
//     if (('0' <= charCode2 && charCode2 <= '7')) {
//       tokenType = TokenTypeEnum::ltOctalPrefix;
//       tokenSize = 2;
//       pushToken(pos_, tokenSize, tokenType);
//       location = computeLocation(pos_, tokenSize, location);
//       nextToken = new Token(location);
//       numberTokenLen = scanningOctalNumber(pos_ + tokenSize);
//       if (numberTokenLen > 0) {
//         tokenSize += numberTokenLen;
//       }
//     } else {
//       tokenType = TokenTypeEnum::reservedWord;
//       tokenSize = 2;
//       for (size_t pos = pos_ + 2;
//            ('0' <= charCode2 && charCode2 <= '9') || ('A' <= charCode2 &&
//            charCode2 <= 'Z') ||
//            ('a' <= charCode2 && charCode2 <= 'z') || charCode2 == '_';
//            tokenSize++, pos++, charCode2 = *(bufferPtr + pos))
//         ;
//       pushToken(pos_, tokenSize, tokenType);
//       location = computeLocation(pos_, tokenSize, location);
//       nextToken = new Token(location);
//     }
//   }
//   // hexadecimal number
//   else if (charCode1 == 'x' || charCode1 == 'X') {
//     charCode2 = *(bufferPtr + pos_ + 2);
//     if ((('0' <= charCode2 && charCode2 <= '9') || ('A' <= charCode2 &&
//     charCode2 <= 'F') ||
//          ('a' <= charCode2 && charCode2 <= 'f'))) {
//       tokenType = TokenTypeEnum::ltHexadecimalPrefix;
//       tokenSize = 2;
//       pushToken(pos_, tokenSize, tokenType);
//       location = computeLocation(pos_, tokenSize, location);
//       nextToken = new Token(location);
//       numberTokenLen = scanningHexadecimalNumber(pos_ + tokenSize);
//       if (numberTokenLen > 0) {
//         tokenSize += numberTokenLen;
//       }
//     } else {
//       tokenType = TokenTypeEnum::reservedWord;
//       tokenSize = 2;
//       for (size_t pos = pos_ + 2;
//            ('0' <= charCode2 && charCode2 <= '9') || ('A' <= charCode2 &&
//            charCode2 <= 'Z') ||
//            ('a' <= charCode2 && charCode2 <= 'z') || charCode2 == '_';
//            tokenSize++, pos++, charCode2 = *(bufferPtr + pos))
//         ;
//       pushToken(pos_, tokenSize, tokenType);
//       location = computeLocation(pos_, tokenSize, location);
//       nextToken = new Token(location);
//     }
//   }
//   return tokenSize;
// };

// size_t LexicalAnalyzer::scanningDecimalNumber(const size_t &pos_) {
//   size_t tokenSize = 0;
//   size_t pos = pos_;
//   TokenTypeEnum prevTokenType = tis.tailTokenType();
//   char charCode0, charCode1;
//   charCode0 = *(bufferPtr + pos_);
//   bool isNonDecimal = false;
//   bool isExponent = false;
//   if (prevTokenType == TokenTypeEnum::ltDecimalExponentOperator ||
//       prevTokenType == TokenTypeEnum::scNegativeDecimalExponent
//       || prevTokenType ==
//       TokenTypeEnum::scPositiveDecimalExponent) {
//     // passing exponent part number
//     for (pos = pos_ + tokenSize, charCode0 = *(bufferPtr + pos);
//          ('0' <= charCode0 && charCode0 <= '9');
//          tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//       ;
//     // non decimal
//     if (('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0 &&
//     charCode0 <= 'Z') ||
//         ('a' <= charCode0 && charCode0 <= 'z') || charCode0 == '_') {
//       isNonDecimal = true;
//       for (; ('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0 &&
//       charCode0 <= 'Z') ||
//              ('a' <= charCode0 && charCode0 <= 'z') || charCode0 == '_';
//            tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//         ;
//     }
//   } else {
//     // passing integral part number
//     // passing fractional part number
//     for (pos = pos_ + tokenSize, charCode0 = *(bufferPtr + pos);
//          ('0' <= charCode0 && charCode0 <= '9') || charCode0 == '_';
//          tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//       ;
//     // non decimal
//     if (('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0 &&
//     charCode0 <= 'Z') ||
//         ('a' <= charCode0 && charCode0 <= 'z') || charCode0 == '_') {
//       if ((charCode0 != 'e' && charCode0 != 'E')) {
//         isNonDecimal = true;
//       } else {
//         // passing exponent charcter [e|E]
//         charCode1 = *(bufferPtr + pos + 1);
//         if ((('0' <= charCode1 && charCode1 <= '9') || charCode1 == '+' ||
//         charCode1 == '-')) {
//           isExponent = true;
//           if (charCode1 == '+' || charCode1 == '-') {
//             char charCode2 = *(bufferPtr + pos + 2);
//             if (!('0' <= charCode2 && charCode2 <= '9')) {
//               isExponent = false;
//               isNonDecimal = true;
//             }
//           }
//           if (prevTokenType ==
//                   TokenTypeEnum::ltDecimalExponentOperator ||
//               prevTokenType ==
//                   TokenTypeEnum::scNegativeDecimalExponent ||
//               prevTokenType ==
//                   TokenTypeEnum::scPositiveDecimalExponent) {
//             isExponent = false;
//             isNonDecimal = true;
//           }
//         } else {
//           isNonDecimal = true;
//         }
//       }
//       if (isNonDecimal) {
//         for (; ('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0
//         && charCode0 <= 'Z')
//         ||
//                ('a' <= charCode0 && charCode0 <= 'z') || charCode0 == '_';
//              tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//           ;
//       }
//     }
//   }
//   if (!isNonDecimal && prevTokenType == TokenTypeEnum::scDot) {
//     pushToken(pos_, tokenSize,
//     TokenTypeEnum::ltDecimalFractionalPart); location =
//     computeLocation(pos_, tokenSize, location); nextToken = new
//     Token(location);
//   } else if (!isNonDecimal &&
//              (prevTokenType ==
//                   TokenTypeEnum::ltDecimalExponentOperator ||
//               prevTokenType ==
//                   TokenTypeEnum::scNegativeDecimalExponent ||
//               prevTokenType ==
//                   TokenTypeEnum::scPositiveDecimalExponent)) {
//     pushToken(pos_, tokenSize,
//     TokenTypeEnum::ltExponentPart); location =
//     computeLocation(pos_, tokenSize, location); nextToken = new
//     Token(location);
//   } else if (!isNonDecimal) {
//     pushToken(pos_, tokenSize,
//     TokenTypeEnum::ltDecimalIntegralPart); location =
//     computeLocation(pos_, tokenSize, location); nextToken = new
//     Token(location);
//   } else if (isNonDecimal) {
//     if (prevTokenType == TokenTypeEnum::scDot) {
//       pushToken(pos_, tokenSize, TokenTypeEnum::identifier);
//     } else {
//       pushToken(pos_, tokenSize, TokenTypeEnum::reservedWord);
//     }
//     location = computeLocation(pos_, tokenSize, location);
//     nextToken = new Token(location);
//   }
//   if (isExponent) {
//     // passing exponent charcter [e|E]
//     pushToken(pos_ + tokenSize, 1,
//               TokenTypeEnum::ltDecimalExponentOperator);
//     location = computeLocation(pos_, tokenSize, location);
//     nextToken = new Token(location);
//     tokenSize++;
//   }
//   return tokenSize;
// };

// size_t LexicalAnalyzer::scanningBinaryNumber(const size_t &pos_) {
//   size_t tokenSize = 0;
//   size_t pos = pos_;
//   char charCode0;
//   charCode0 = *(bufferPtr + pos_ + tokenSize);
//   // not binary number?
//   if (!(charCode0 == '0' || charCode0 == '1')) {
//     return tokenSize;
//   }
//   // passing binary number
//   for (pos = pos_ + tokenSize, charCode0 = *(bufferPtr + pos);
//        charCode0 == '0' || charCode0 == '1' || charCode0 == '_';
//        tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//     ;
//   // binary number
//   pushToken(pos_, tokenSize, TokenTypeEnum::ltBinaryIntegralPart);
//   location = computeLocation(pos_, tokenSize, location);
//   nextToken = new Token(location);
//   return tokenSize;
// };

// size_t LexicalAnalyzer::scanningOctalNumber(const size_t &pos_) {
//   size_t tokenSize = 0;
//   size_t pos = pos_;
//   char charCode0;
//   charCode0 = *(bufferPtr + pos_ + tokenSize);
//   // not octal number?
//   if (!('0' <= charCode0 && charCode0 <= '7')) {
//     return tokenSize;
//   }
//   TokenTypeEnum prevTokenType = tis.tailTokenType();
//   if (prevTokenType == TokenTypeEnum::ltOctalPrefix) {
//     // passing octal number
//     for (pos = pos_ + tokenSize, charCode0 = *(bufferPtr + pos);
//          ('0' <= charCode0 && charCode0 <= '7') || charCode0 == '_';
//          tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//       ;
//   } else {
//     // passing octal number
//     for (pos = pos_ + tokenSize, charCode0 = *(bufferPtr + pos);
//          ('0' <= charCode0 && charCode0 <= '7');
//          tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//       ;
//   }
//   // octal number
//   pushToken(pos_, tokenSize, TokenTypeEnum::ltOctalIntegralPart);
//   location = computeLocation(pos_, tokenSize, location);
//   nextToken = new Token(location);
//   return tokenSize;
// };

// size_t LexicalAnalyzer::scanningHexadecimalNumber(const size_t &pos_) {
//   size_t tokenSize = 0;
//   size_t pos = pos_;
//   char charCode0;
//   charCode0 = *(bufferPtr + pos_ + tokenSize);
//   // not hexadecimal number?
//   if (!(('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0 &&
//   charCode0 <= 'F') ||
//         ('a' <= charCode0 && charCode0 <= 'f'))) {
//     return tokenSize;
//   }
//   TokenTypeEnum prevTokenType = tis.tailTokenType();
//   if (prevTokenType == TokenTypeEnum::ltHexadecimalPrefix) {
//     // passing hexadecimal number
//     for (pos = pos_ + tokenSize, charCode0 = *(bufferPtr + pos);
//          ('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0 &&
//          charCode0 <= 'F') ||
//          ('a' <= charCode0 && charCode0 <= 'f') || charCode0 == '_';
//          tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//       ;
//   } else {
//     // passing hexadecimal number
//     for (pos = pos_ + tokenSize, charCode0 = *(bufferPtr + pos);
//          ('0' <= charCode0 && charCode0 <= '9') || ('A' <= charCode0 &&
//          charCode0 <= 'F') ||
//          ('a' <= charCode0 && charCode0 <= 'f');
//          tokenSize++, pos++, charCode0 = *(bufferPtr + pos))
//       ;
//   }
//   // hexadecimal number
//   pushToken(pos_, tokenSize, TokenTypeEnum::ltHexadecimalIntegralPart);
//   location = computeLocation(pos_, tokenSize, location);
//   nextToken = new Token(location);
//   return tokenSize;
// };

// size_t LexicalAnalyzer::scanningCharactersLiteral(const size_t &pos_) {
//   size_t tokenSize = 0, nextTokenLen = 0, nextTokenPos = pos_;
//   char charCode0, charCode1;
//   charCode0 = *(bufferPtr + pos_ + tokenSize);
//   char tokenDelimiter = '\'';
//   TokenTypeEnum charCodesTokenType = TokenTypeEnum::ltSingleCharacter;
//   if (continueTokenType == TokenTypeEnum::scDoubleQuotation) {
//     tokenDelimiter = '"';
//     charCodesTokenType = TokenTypeEnum::ltString;
//   } else if (continueTokenType == TokenTypeEnum::scBackQuotation) {
//     tokenDelimiter = '`';
//     charCodesTokenType = TokenTypeEnum::ltRawString;
//   }
//   for (size_t pos = pos_; pos < bufferSize;) {
//     charCode0 = *(bufferPtr + pos);
//     // 1 byte (U+0000 - U+007f)
//     if ((charCode0 & 0x80) == 0) {
//       if (charCode0 == '\0' || charCode0 == tokenDelimiter) {
//         isAnalyzeContinue = false;
//         break;
//       }
//       if (charCode0 != '\\') {
//         pos++;
//         tokenSize++;
//         nextTokenLen++;
//         continue;
//       }
//       if (nextTokenLen > 0) {
//         pushToken(nextTokenPos, nextTokenLen, charCodesTokenType);
//         location = computeLocation(nextTokenPos, nextTokenLen, location);
//         nextToken = new Token(location);
//         nextTokenPos = pos;
//         nextTokenLen = 0;
//       }
//       charCode1 = *(bufferPtr + pos + 1);
//       if (charCode1 == '\r' || charCode1 == '\n') {
//         pos++;
//         tokenSize++;
//         nextTokenPos++;
//         nextTokenLen += toNextToken(pos);
//         pos += nextTokenLen;
//         tokenSize += nextTokenLen;
//         nextToken = new Token(location);
//         nextTokenPos = pos;
//         nextTokenLen = 0;
//         continue;
//       } else if (charCode1 == 'o') {
//         pos += 2;
//         nextTokenLen = 2;
//         tokenSize += 2;
//         pushToken(nextTokenPos, nextTokenLen,
//                   TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
//         location = computeLocation(pos, nextTokenLen, location);
//         nextToken = new Token(location);
//         size_t nTokenLen = scanningOctalNumber(pos);
//         nextToken = new Token(location);
//         pos += nTokenLen;
//         tokenSize += nTokenLen;
//         nextTokenPos = pos;
//         nextTokenLen = 0;
//         continue;
//       } else if (charCode1 == 'x') {
//         pos += 2;
//         nextTokenLen = 2;
//         tokenSize += 2;
//         pushToken(nextTokenPos, nextTokenLen,
//                   TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
//         location = computeLocation(pos, nextTokenLen, location);
//         nextToken = new Token(location);
//         size_t nTokenLen = scanningHexadecimalNumber(pos);
//         nextToken = new Token(location);
//         pos += nTokenLen;
//         tokenSize += nTokenLen;
//         nextTokenPos = pos;
//         nextTokenLen = 0;
//         continue;
//       } else if (charCode1 == 'u') {
//         pos += 2;
//         nextTokenLen = 2;
//         tokenSize += 2;
//         pushToken(nextTokenPos, nextTokenLen,
//                   TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
//         location = computeLocation(pos, nextTokenLen, location);
//         nextToken = new Token(location);
//         size_t nTokenLen = scanningHexadecimalNumber(pos);
//         nextToken = new Token(location);
//         pos += nTokenLen;
//         tokenSize += nTokenLen;
//         nextTokenPos = pos;
//         nextTokenLen = 0;
//         continue;
//       } else {
//         pos += 2;
//         nextTokenLen = 2;
//         tokenSize += 2;
//         pushToken(nextTokenPos, nextTokenLen,
//                   TokenTypeEnum::ltEscapeSequence);
//         location = computeLocation(nextTokenPos, nextTokenLen, location);
//         nextToken = new Token(location);
//         nextTokenPos = pos;
//         nextTokenLen = 0;
//         continue;
//       }
//     }
//     // 2 byte (U+0080 - U+07ff)
//     else if ((charCode0 & 0xe0) == 0xc0) {
//       tokenSize += 2;
//       nextTokenLen += 2;
//       pos += 2;
//     }
//     // 3 byte (U+0800 - U+ffff)
//     else if ((charCode0 & 0xf0) == 0xe0) {
//       tokenSize += 3;
//       nextTokenLen += 3;
//       pos += 3;
//     }
//     // 4 byte (U+010000 - U+01ffff)
//     else if ((charCode0 & 0xf8) == 0xf0) {
//       tokenSize += 4;
//       nextTokenLen += 4;
//       pos += 4;
//     }
//   }
//   if (nextTokenLen > 0) {
//     pushToken(nextTokenPos, nextTokenLen, charCodesTokenType);
//     location = computeLocation(nextTokenPos, nextTokenLen, location);
//     nextToken = new Token(location);
//   }
//   return tokenSize;
// };
