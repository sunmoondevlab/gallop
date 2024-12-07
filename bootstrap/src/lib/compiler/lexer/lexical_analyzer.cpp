#if 0
// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/lexer/lexical_analyzer.hpp"

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;

// interpreter
LexicalAnalyzer::LexicalAnalyzer()
    : buffer(std::string("")), bufferSize(0), location(Location(0, 0)),
      isInterpreterFlag(true), isAnalyzeContinue(false),
      continueTokenType(TokenTypeEnum::unknown), filename(""), lineCount(0),
      lines({}), tokens(new Tokens()) {
  bufferPtr = buffer.c_str();
};

// compiler from stdin
LexicalAnalyzer::LexicalAnalyzer(const std::vector<char> &buffer_)
    : buffer(std::string(buffer_.begin(), buffer_.end())),
      bufferSize(buffer_.size()), location(Location(1, 1)),
      isInterpreterFlag(false), isAnalyzeContinue(false),
      continueTokenType(TokenTypeEnum::unknown), filename(""), lineCount(0),
      lines({}), tokens(new Tokens()) {
  bufferPtr = buffer.c_str();
  splitLinesFromBuffer();
  tokenize();
};

// compiler from file
LexicalAnalyzer::LexicalAnalyzer(const std::vector<char> &buffer_,
                                 const std::string &filename_)
    : buffer(std::string(buffer_.begin(), buffer_.end())),
      bufferSize(buffer_.size()), location(Location(filename_, 1, 1)),
      isInterpreterFlag(false), isAnalyzeContinue(false),
      continueTokenType(TokenTypeEnum::unknown), filename(filename_),
      lineCount(0), lines({}), tokens(new Tokens()) {
  bufferPtr = buffer.c_str();
  splitLinesFromBuffer();
  tokenize();
};

// copier
LexicalAnalyzer::LexicalAnalyzer(const LexicalAnalyzer &rhs)
    : buffer(rhs.buffer), bufferSize(rhs.bufferSize), location(rhs.location),
      isInterpreterFlag(rhs.isInterpreterFlag),
      isAnalyzeContinue(rhs.isAnalyzeContinue),
      continueTokenType(rhs.continueTokenType), filename(rhs.filename),
      lineCount(rhs.lineCount), lines(rhs.lines) {
  bufferPtr = buffer.c_str();
  tokens = new Tokens();
  *tokens = *rhs.tokens;
};

// setter
LexicalAnalyzer &LexicalAnalyzer::operator=(const LexicalAnalyzer &rhs) {
  buffer = rhs.buffer;
  bufferSize = rhs.bufferSize;
  bufferPtr = buffer.c_str();
  location = rhs.location;
  isInterpreterFlag = rhs.isInterpreterFlag;
  isAnalyzeContinue = rhs.isAnalyzeContinue;
  continueTokenType = rhs.continueTokenType;
  filename = rhs.filename;
  lineCount = rhs.lineCount;
  lines = rhs.lines;
  tokens = new Tokens();
  *tokens = *rhs.tokens;
  return *this;
};

void LexicalAnalyzer::tokenizeNextBuffer(const std::vector<char> &buffer_) {
  if (!isInterpreterFlag) {
    return;
  }
  buffer = std::string(buffer_.begin(), buffer_.end());
  bufferSize = buffer_.size();
  bufferPtr = buffer.c_str();
  if (location.getLine() == 0) {
    location.addLine(1);
    location.rewindColumn();
  }
  splitLinesFromBuffer();
  tokenize();
};

void LexicalAnalyzer::splitLinesFromBuffer() {
  lineCount = 0;
  if (bufferSize == 0) {
    return;
  };
  lineCount++;
  size_t lineBeginPos = 0;
  for (size_t i = 0; i < bufferSize; i++) {
    if (*(bufferPtr + i) == '\n') {
      lines.push_back(
          std::string(buffer.begin() + lineBeginPos, buffer.begin() + i + 1));
      lineCount++;
      lineBeginPos = i + 1;
    }
  }
  if (lineBeginPos < bufferSize) {
    lines.push_back(std::string(buffer.begin() + lineBeginPos, buffer.end()));
  }
  if (*(bufferPtr + bufferSize - 1) == '\n') {
    lineCount--;
  }
};

bool LexicalAnalyzer::isInterpreter() const { return isInterpreterFlag; };
bool LexicalAnalyzer::isFromFile() const { return filename != ""; };
size_t LexicalAnalyzer::getLineCount() const { return lineCount; };
std::string LexicalAnalyzer::getLineString(const size_t &line_) const {
  if (line_ == 0) {
    return "";
  }
  if (line_ <= lines.size()) {
    return lines.at(line_ - 1);
  }
  return "";
};
Tokens *LexicalAnalyzer::getTokens() { return tokens; };

void LexicalAnalyzer::tokenize() {
  for (size_t pos = 0; pos < bufferSize;) {
    if (isAnalyzeContinue) {
      if (continueTokenType == TokenTypeEnum::scOnelineCommentOut ||
          continueTokenType == TokenTypeEnum::scOnelineCommentOutDoc) {
        pos += toNextToken(pos);
        if (pos >= bufferSize) {
          break;
        }
        pos += scanningOnelineComment(pos);
      } else if (continueTokenType == TokenTypeEnum::scBlockCommentOutOpen ||
                 continueTokenType == TokenTypeEnum::scBlockCommentOutDocOpen) {
        pos += toNextToken(pos);
        if (pos >= bufferSize) {
          break;
        }
        pos += scanningBlockComment(pos);
      } else if (continueTokenType == TokenTypeEnum::scSingleQuotation ||
                 continueTokenType == TokenTypeEnum::scDoubleQuotation ||
                 continueTokenType == TokenTypeEnum::scBackQuotation) {
        pos += scanningCharactersLiteral(pos);
      }
    } else {
      pos += toNextToken(pos);
      if (pos >= bufferSize) {
        break;
      }
      pos += scanningToken(pos);
    }
    if (pos >= bufferSize) {
      break;
    }
  }
};
size_t LexicalAnalyzer::toNextToken(const size_t &pos_) {
  size_t tokenSize = 0;
  for (size_t pos = pos_ + tokenSize;
       *(bufferPtr + pos) != '\0' &&
       (*(bufferPtr + pos) == '\t' || *(bufferPtr + pos) == '\f' ||
        *(bufferPtr + pos) == '\v' || *(bufferPtr + pos) == '\r' ||
        *(bufferPtr + pos) == '\n' || *(bufferPtr + pos) == ' ');
       pos++, tokenSize++)
    ;
  location = computeLocation(pos_, tokenSize, location);
  nextToken = new Token(location);
  return tokenSize;
};

Location LexicalAnalyzer::computeLocation(const size_t &pos_,
                                          const size_t &tokenSize_,
                                          const Location location_) {
  std::string filenameN = location_.getFilename();
  size_t lineN = location_.getLine();
  size_t columnN = location_.getColumn();
  for (size_t pos = pos_;
       *(bufferPtr + pos) != '\0' && pos < pos_ + tokenSize_;) {
    if (*(bufferPtr + pos) == '\r') {
      if (*(bufferPtr + pos + 1) == '\n') {
        pos += 2;
      } else {
        pos++;
      }
      lineN++;
      columnN = 1;
      continue;
    } else if (*(bufferPtr + pos) == '\n') {
      pos++;
      lineN++;
      columnN = 1;
      continue;
    } else {
      pos++;
      columnN++;
    }
  }
  return Location(filenameN, lineN, columnN);
};

void LexicalAnalyzer::pushToken(const size_t &pos_, const size_t tokenSize_,
                                const TokenTypeEnum tokenType_) {
  std::string token =
      std::string(buffer.begin() + pos_, buffer.begin() + pos_ + tokenSize_);
  TokenTypeEnum tokenType = tokenType_;
  nextToken->setTokenVal(tokenType, token);
  tokens->push(nextToken, isAnalyzeContinue);
};

size_t LexicalAnalyzer::scanningToken(const size_t &pos_) {
  size_t tokenSize = 0;
  char chr0 = *(bufferPtr + pos_);
  TokenTypeEnum prevTokenType = tokens->tailTokenType();
  if (prevTokenType != TokenTypeEnum::scDoller && chr0 == '0') {
    tokenSize += scanningNonDecimal(pos_);
    if (tokenSize > 0) {
      return tokenSize;
    }
  }
  if (prevTokenType != TokenTypeEnum::scDoller &&
      ('0' <= chr0 && chr0 <= '9')) {
    tokenSize += scanningDecimalNumber(pos_);
  } else if (prevTokenType == TokenTypeEnum::scDoller &&
             (('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'Z') ||
              ('a' <= chr0 && chr0 <= 'z') || chr0 == '_')) {
    tokenSize += scanningIdentifier(pos_);
  } else if (prevTokenType != TokenTypeEnum::scDoller &&
             (('A' <= chr0 && chr0 <= 'Z') || ('a' <= chr0 && chr0 <= 'z') ||
              chr0 == '_')) {
    tokenSize += scanningIdentifier(pos_);
  } else {
    tokenSize += scanningSymbol(pos_);
  }
  return tokenSize;
};

size_t LexicalAnalyzer::scanningIdentifier(const size_t &pos_) {
  size_t tokenSize = 0;
  char chr0;
  for (chr0 = *(bufferPtr + pos_ + tokenSize);
       ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'Z') ||
       ('a' <= chr0 && chr0 <= 'z') || chr0 == '_';
       tokenSize++, chr0 = *(bufferPtr + pos_ + tokenSize))
    ;

  TokenTypeEnum prevTokenType = tokens->tailTokenType();
  if (prevTokenType == TokenTypeEnum::scDot ||
      prevTokenType == TokenTypeEnum::scDoller ||
      prevTokenType == TokenTypeEnum::ltDecimalIntegralPart ||
      prevTokenType == TokenTypeEnum::ltDecimalFractionalPart) {
    pushToken(pos_, tokenSize, TokenTypeEnum::identifier);
  } else {
    pushToken(pos_, tokenSize, TokenTypeEnum::reservedWord);
  }
  location = computeLocation(pos_, tokenSize, location);
  nextToken = new Token(location);
  // identifier
  return tokenSize;
};

size_t LexicalAnalyzer::scanningSymbol(const size_t &pos_) {
  size_t tokenSize = 0;
  char chr0, chr1, chr2, chr3;
  TokenTypeEnum tokenType = TokenTypeEnum::unknown;
  TokenTypeEnum prevTokenType = tokens->tailTokenType();
  chr0 = *(bufferPtr + pos_);
  switch (chr0) {
    // arithmetic
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Plus):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scPlusWrappingAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scPlusWrapping;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scPlusSaturatingAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scPlusSaturating;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Plus):
      tokenType = TokenTypeEnum::scIncrement;
      tokenSize = 2;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scPlusAssign;
      tokenSize = 2;
      break;
    default:
      if ('0' <= chr1 && chr1 <= '9') {
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
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Minus):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMinusWrappingAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scMinusWrapping;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMinusSaturatingAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scMinusSaturating;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Minus):
      tokenType = TokenTypeEnum::scDecrement;
      tokenSize = 2;
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scMinusAssign;
      tokenSize = 2;
      break;
    default:
      if ('0' <= chr1 && chr1 <= '9') {
        if (prevTokenType == TokenTypeEnum::ltDecimalExponentOperator) {
          // exponent sign
          tokenType = TokenTypeEnum::scNegativeDecimalExponent;
        } else {
          tokenType = TokenTypeEnum::scNegativeDecimal;
        }
      } else {
        tokenType = TokenTypeEnum::scMinus;
      }
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Asterisk):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMultipleWrappingAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scMultipleWrapping;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scMultipleSaturatingAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scMultipleSaturating;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scMultipleAssign;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scMultiple;
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Slash):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Slash):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
        tokenType = TokenTypeEnum::scBlockCommentOutOpen;
        tokenSize = 3;
        isAnalyzeContinue = true;
        continueTokenType = tokenType;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
        tokenType = TokenTypeEnum::scBlockCommentOutClose;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scOnelineCommentOut;
        tokenSize = 2;
        isAnalyzeContinue = true;
        continueTokenType = tokenType;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::NumberSign):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
        tokenType = TokenTypeEnum::scBlockCommentOutDocOpen;
        tokenSize = 3;
        isAnalyzeContinue = true;
        continueTokenType = tokenType;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
        tokenType = TokenTypeEnum::scBlockCommentOutDocClose;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scOnelineCommentOutDoc;
        tokenSize = 2;
        isAnalyzeContinue = true;
        continueTokenType = tokenType;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scDivideAssign;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scDivide;
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Percent):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scModuloAssign;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scModulo;
      tokenSize = 1;
      break;
    }
    break;
  // bit , logical
  case '&':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '&':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scLogicalAndAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scLogicalAnd;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scBitAndAssign;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scBitAnd;
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scLogicalOrAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scLogicalOr;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scBitOrAssign;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scBitOr;
      tokenSize = 1;
      break;
    }
    break;
  case '^':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scBitExOrAssign;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scBitExOr;
      tokenSize = 1;
      break;
    }
    break;
  case '~':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scBitNot;
      tokenSize = 1;
      break;
    }
    break;
  case '!':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scLogicalNotEqual;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scLogicalNotUnary;
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scLogicalEqual;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scAssignment;
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::LessThan):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::VerticalBar):
        chr3 = *(bufferPtr + pos_ + 3);
        switch (chr3) {
        case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
          tokenType = TokenTypeEnum::scBitShiftLeftSaturatingAssign;
          tokenSize = 4;
          break;
        default:
          tokenType = TokenTypeEnum::scBitShiftLeftSaturating;
          tokenSize = 3;
          break;
        }
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scBitShiftLeftAssign;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scBitShiftLeft;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scLessThanEqual;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scLessThan;
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
        tokenType = TokenTypeEnum::scArithmeticBitShiftRightAssign;
        tokenSize = 3;
        break;
      case static_cast<uint32_t>(CharCode::UtfAsciiTable::GreaterThan):
        tokenType = TokenTypeEnum::scLogicalBitShiftRight;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scArithmeticBitShiftRight;
        tokenSize = 2;
        break;
      }
      break;
    case static_cast<uint32_t>(CharCode::UtfAsciiTable::Equal):
      tokenType = TokenTypeEnum::scGreaterThanEqual;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scGreaterThan;
      tokenSize = 1;
      break;
    }
    break;
  case '$':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scDoller;
      tokenSize = 1;
      break;
    }
    break;
  case static_cast<uint32_t>(CharCode::UtfAsciiTable::NumberSign):
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scNumberSign;
      tokenSize = 1;
      break;
    }
    break;
  case '?':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scQuestion;
      tokenSize = 1;
      break;
    }
    break;
  case '@':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scAtSign;
      tokenSize = 1;
      break;
    }
    break;
  case ':':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case ':':
      tokenType = TokenTypeEnum::scNameSpaceSeparater;
      tokenSize = 2;
      break;
    default:
      tokenType = TokenTypeEnum::scColon;
      tokenSize = 1;
      break;
    }
    break;
  case ';':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scSemiColon;
      tokenSize = 1;
      break;
    }
    break;
  case ',':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scComma;
      tokenSize = 1;
      break;
    }
    break;
  case '.':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '.':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '.':
        tokenType = TokenTypeEnum::scDotDotDot;
        tokenSize = 3;
        break;
      default:
        tokenType = TokenTypeEnum::scDotDot;
        tokenSize = 2;
        break;
      }
      break;
    default:
      tokenType = TokenTypeEnum::scDot;
      tokenSize = 1;
      if (prevTokenType == TokenTypeEnum::ltDecimalIntegralPart) {
        if (chr1 == 'e' || chr1 == 'E') {
          chr2 = *(bufferPtr + pos_ + 2);
          if (chr2 == '+' || chr2 == '-' || ('0' <= chr2 && chr2 <= '9')) {
            pushToken(pos_, tokenSize, tokenType);
            nextToken = new Token(location);
            // passing exponent charcter [e|E]
            pushToken(pos_ + tokenSize, 1,
                      TokenTypeEnum::ltDecimalExponentOperator);
            nextToken = new Token(location);
            tokenType = TokenTypeEnum::unknown;
            tokenSize++;
          }
        }
      }
      break;
    }
    break;
  case '\\':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::scBackSlash;
      tokenSize = 1;
      break;
    }
    break;
  case '\'':
    tokenType = TokenTypeEnum::scSingleQuotation;
    tokenSize++;
    if (continueTokenType != TokenTypeEnum::unknown) {
      isAnalyzeContinue = false;
      continueTokenType = TokenTypeEnum::unknown;
    } else {
      isAnalyzeContinue = true;
      continueTokenType = tokenType;
    }
    break;
  case '"':
    tokenType = TokenTypeEnum::scDoubleQuotation;
    tokenSize++;
    if (continueTokenType != TokenTypeEnum::unknown) {
      isAnalyzeContinue = false;
      continueTokenType = TokenTypeEnum::unknown;
    } else {
      isAnalyzeContinue = true;
      continueTokenType = tokenType;
    }
    break;
  case '`':
    tokenType = TokenTypeEnum::scBackQuotation;
    tokenSize++;
    if (continueTokenType != TokenTypeEnum::unknown) {
      isAnalyzeContinue = false;
      continueTokenType = TokenTypeEnum::unknown;
    } else {
      isAnalyzeContinue = true;
      continueTokenType = tokenType;
    }
    break;
  case '(':
    tokenType = TokenTypeEnum::scParenthesesOpen;
    tokenSize++;
    break;
  case ')':
    tokenType = TokenTypeEnum::scParenthesesClose;
    tokenSize++;
    break;
  case '{':
    tokenType = TokenTypeEnum::scCurlyBracketOpen;
    tokenSize++;
    break;
  case '}':
    tokenType = TokenTypeEnum::scCurlyBracketClose;
    tokenSize++;
    break;
  case '[':
    tokenType = TokenTypeEnum::scSquareBracketOpen;
    tokenSize++;
    break;
  case ']':
    tokenType = TokenTypeEnum::scSquareBracketClose;
    tokenSize++;
    break;
  default:
    break;
  }
  if (tokenType != TokenTypeEnum::unknown) {
    pushToken(pos_, tokenSize, tokenType);
    location = computeLocation(pos_, tokenSize, location);
    nextToken = new Token(location);
  }
  return tokenSize;
};

size_t LexicalAnalyzer::scanningNonDecimal(const size_t &pos_) {
  size_t tokenSize = 0, numberTokenLen = 0;
  char chr1, chr2;
  chr1 = *(bufferPtr + pos_ + 1);
  TokenTypeEnum tokenType = TokenTypeEnum::unknown;
  // binary number
  if (chr1 == 'b' || chr1 == 'B') {
    chr2 = *(bufferPtr + pos_ + 2);
    if ((chr2 == '0' || chr2 == '1')) {
      tokenType = TokenTypeEnum::ltBinaryPrefix;
      tokenSize = 2;
      pushToken(pos_, tokenSize, tokenType);
      location = computeLocation(pos_, tokenSize, location);
      nextToken = new Token(location);
      numberTokenLen = scanningBinaryNumber(pos_ + tokenSize);
      if (numberTokenLen > 0) {
        tokenSize += numberTokenLen;
      }
    } else {
      tokenType = TokenTypeEnum::reservedWord;
      tokenSize = 2;
      for (size_t pos = pos_ + 2;
           ('0' <= chr2 && chr2 <= '9') || ('A' <= chr2 && chr2 <= 'Z') ||
           ('a' <= chr2 && chr2 <= 'z') || chr2 == '_';
           tokenSize++, pos++, chr2 = *(bufferPtr + pos))
        ;
      pushToken(pos_, tokenSize, tokenType);
      location = computeLocation(pos_, tokenSize, location);
      nextToken = new Token(location);
    }
  }
  // ocatal number
  else if (chr1 == 'o' || chr1 == 'O') {
    chr2 = *(bufferPtr + pos_ + 2);
    if (('0' <= chr2 && chr2 <= '7')) {
      tokenType = TokenTypeEnum::ltOctalPrefix;
      tokenSize = 2;
      pushToken(pos_, tokenSize, tokenType);
      location = computeLocation(pos_, tokenSize, location);
      nextToken = new Token(location);
      numberTokenLen = scanningOctalNumber(pos_ + tokenSize);
      if (numberTokenLen > 0) {
        tokenSize += numberTokenLen;
      }
    } else {
      tokenType = TokenTypeEnum::reservedWord;
      tokenSize = 2;
      for (size_t pos = pos_ + 2;
           ('0' <= chr2 && chr2 <= '9') || ('A' <= chr2 && chr2 <= 'Z') ||
           ('a' <= chr2 && chr2 <= 'z') || chr2 == '_';
           tokenSize++, pos++, chr2 = *(bufferPtr + pos))
        ;
      pushToken(pos_, tokenSize, tokenType);
      location = computeLocation(pos_, tokenSize, location);
      nextToken = new Token(location);
    }
  }
  // hexadecimal number
  else if (chr1 == 'x' || chr1 == 'X') {
    chr2 = *(bufferPtr + pos_ + 2);
    if ((('0' <= chr2 && chr2 <= '9') || ('A' <= chr2 && chr2 <= 'F') ||
         ('a' <= chr2 && chr2 <= 'f'))) {
      tokenType = TokenTypeEnum::ltHexadecimalPrefix;
      tokenSize = 2;
      pushToken(pos_, tokenSize, tokenType);
      location = computeLocation(pos_, tokenSize, location);
      nextToken = new Token(location);
      numberTokenLen = scanningHexadecimalNumber(pos_ + tokenSize);
      if (numberTokenLen > 0) {
        tokenSize += numberTokenLen;
      }
    } else {
      tokenType = TokenTypeEnum::reservedWord;
      tokenSize = 2;
      for (size_t pos = pos_ + 2;
           ('0' <= chr2 && chr2 <= '9') || ('A' <= chr2 && chr2 <= 'Z') ||
           ('a' <= chr2 && chr2 <= 'z') || chr2 == '_';
           tokenSize++, pos++, chr2 = *(bufferPtr + pos))
        ;
      pushToken(pos_, tokenSize, tokenType);
      location = computeLocation(pos_, tokenSize, location);
      nextToken = new Token(location);
    }
  }
  return tokenSize;
};

size_t LexicalAnalyzer::scanningDecimalNumber(const size_t &pos_) {
  size_t tokenSize = 0;
  size_t pos = pos_;
  TokenTypeEnum prevTokenType = tokens->tailTokenType();
  char chr0, chr1;
  chr0 = *(bufferPtr + pos_);
  bool isNonDecimal = false;
  bool isExponent = false;
  if (prevTokenType == TokenTypeEnum::ltDecimalExponentOperator ||
      prevTokenType == TokenTypeEnum::scNegativeDecimalExponent ||
      prevTokenType == TokenTypeEnum::scPositiveDecimalExponent) {
    // passing exponent part number
    for (pos = pos_ + tokenSize, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9');
         tokenSize++, pos++, chr0 = *(bufferPtr + pos))
      ;
    // non decimal
    if (('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'Z') ||
        ('a' <= chr0 && chr0 <= 'z') || chr0 == '_') {
      isNonDecimal = true;
      for (; ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'Z') ||
             ('a' <= chr0 && chr0 <= 'z') || chr0 == '_';
           tokenSize++, pos++, chr0 = *(bufferPtr + pos))
        ;
    }
  } else {
    // passing integral part number
    // passing fractional part number
    for (pos = pos_ + tokenSize, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9') || chr0 == '_';
         tokenSize++, pos++, chr0 = *(bufferPtr + pos))
      ;
    // non decimal
    if (('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'Z') ||
        ('a' <= chr0 && chr0 <= 'z') || chr0 == '_') {
      if ((chr0 != 'e' && chr0 != 'E')) {
        isNonDecimal = true;
      } else {
        // passing exponent charcter [e|E]
        chr1 = *(bufferPtr + pos + 1);
        if ((('0' <= chr1 && chr1 <= '9') || chr1 == '+' || chr1 == '-')) {
          isExponent = true;
          if (chr1 == '+' || chr1 == '-') {
            char chr2 = *(bufferPtr + pos + 2);
            if (!('0' <= chr2 && chr2 <= '9')) {
              isExponent = false;
              isNonDecimal = true;
            }
          }
          if (prevTokenType == TokenTypeEnum::ltDecimalExponentOperator ||
              prevTokenType == TokenTypeEnum::scNegativeDecimalExponent ||
              prevTokenType == TokenTypeEnum::scPositiveDecimalExponent) {
            isExponent = false;
            isNonDecimal = true;
          }
        } else {
          isNonDecimal = true;
        }
      }
      if (isNonDecimal) {
        for (; ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'Z') ||
               ('a' <= chr0 && chr0 <= 'z') || chr0 == '_';
             tokenSize++, pos++, chr0 = *(bufferPtr + pos))
          ;
      }
    }
  }
  if (!isNonDecimal && prevTokenType == TokenTypeEnum::scDot) {
    pushToken(pos_, tokenSize, TokenTypeEnum::ltDecimalFractionalPart);
    location = computeLocation(pos_, tokenSize, location);
    nextToken = new Token(location);
  } else if (!isNonDecimal &&
             (prevTokenType == TokenTypeEnum::ltDecimalExponentOperator ||
              prevTokenType == TokenTypeEnum::scNegativeDecimalExponent ||
              prevTokenType == TokenTypeEnum::scPositiveDecimalExponent)) {
    pushToken(pos_, tokenSize, TokenTypeEnum::ltExponentPart);
    location = computeLocation(pos_, tokenSize, location);
    nextToken = new Token(location);
  } else if (!isNonDecimal) {
    pushToken(pos_, tokenSize, TokenTypeEnum::ltDecimalIntegralPart);
    location = computeLocation(pos_, tokenSize, location);
    nextToken = new Token(location);
  } else if (isNonDecimal) {
    if (prevTokenType == TokenTypeEnum::scDot) {
      pushToken(pos_, tokenSize, TokenTypeEnum::identifier);
    } else {
      pushToken(pos_, tokenSize, TokenTypeEnum::reservedWord);
    }
    location = computeLocation(pos_, tokenSize, location);
    nextToken = new Token(location);
  }
  if (isExponent) {
    // passing exponent charcter [e|E]
    pushToken(pos_ + tokenSize, 1, TokenTypeEnum::ltDecimalExponentOperator);
    location = computeLocation(pos_, tokenSize, location);
    nextToken = new Token(location);
    tokenSize++;
  }
  return tokenSize;
};

size_t LexicalAnalyzer::scanningBinaryNumber(const size_t &pos_) {
  size_t tokenSize = 0;
  size_t pos = pos_;
  char chr0;
  chr0 = *(bufferPtr + pos_ + tokenSize);
  // not binary number?
  if (!(chr0 == '0' || chr0 == '1')) {
    return tokenSize;
  }
  // passing binary number
  for (pos = pos_ + tokenSize, chr0 = *(bufferPtr + pos);
       chr0 == '0' || chr0 == '1' || chr0 == '_';
       tokenSize++, pos++, chr0 = *(bufferPtr + pos))
    ;
  // binary number
  pushToken(pos_, tokenSize, TokenTypeEnum::ltBinaryIntegralPart);
  location = computeLocation(pos_, tokenSize, location);
  nextToken = new Token(location);
  return tokenSize;
};

size_t LexicalAnalyzer::scanningOctalNumber(const size_t &pos_) {
  size_t tokenSize = 0;
  size_t pos = pos_;
  char chr0;
  chr0 = *(bufferPtr + pos_ + tokenSize);
  // not octal number?
  if (!('0' <= chr0 && chr0 <= '7')) {
    return tokenSize;
  }
  TokenTypeEnum prevTokenType = tokens->tailTokenType();
  if (prevTokenType == TokenTypeEnum::ltOctalPrefix) {
    // passing octal number
    for (pos = pos_ + tokenSize, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '7') || chr0 == '_';
         tokenSize++, pos++, chr0 = *(bufferPtr + pos))
      ;
  } else {
    // passing octal number
    for (pos = pos_ + tokenSize, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '7');
         tokenSize++, pos++, chr0 = *(bufferPtr + pos))
      ;
  }
  // octal number
  pushToken(pos_, tokenSize, TokenTypeEnum::ltOctalIntegralPart);
  location = computeLocation(pos_, tokenSize, location);
  nextToken = new Token(location);
  return tokenSize;
};

size_t LexicalAnalyzer::scanningHexadecimalNumber(const size_t &pos_) {
  size_t tokenSize = 0;
  size_t pos = pos_;
  char chr0;
  chr0 = *(bufferPtr + pos_ + tokenSize);
  // not hexadecimal number?
  if (!(('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'F') ||
        ('a' <= chr0 && chr0 <= 'f'))) {
    return tokenSize;
  }
  TokenTypeEnum prevTokenType = tokens->tailTokenType();
  if (prevTokenType == TokenTypeEnum::ltHexadecimalPrefix) {
    // passing hexadecimal number
    for (pos = pos_ + tokenSize, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'F') ||
         ('a' <= chr0 && chr0 <= 'f') || chr0 == '_';
         tokenSize++, pos++, chr0 = *(bufferPtr + pos))
      ;
  } else {
    // passing hexadecimal number
    for (pos = pos_ + tokenSize, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'F') ||
         ('a' <= chr0 && chr0 <= 'f');
         tokenSize++, pos++, chr0 = *(bufferPtr + pos))
      ;
  }
  // hexadecimal number
  pushToken(pos_, tokenSize, TokenTypeEnum::ltHexadecimalIntegralPart);
  location = computeLocation(pos_, tokenSize, location);
  nextToken = new Token(location);
  return tokenSize;
};

size_t LexicalAnalyzer::scanningCharactersLiteral(const size_t &pos_) {
  size_t tokenSize = 0, nextTokenLen = 0, nextTokenPos = pos_;
  char chr0, chr1;
  chr0 = *(bufferPtr + pos_ + tokenSize);
  char tokenDelimiter = '\'';
  TokenTypeEnum charCodesTokenType = TokenTypeEnum::ltSingleCharacter;
  if (continueTokenType == TokenTypeEnum::scDoubleQuotation) {
    tokenDelimiter = '"';
    charCodesTokenType = TokenTypeEnum::ltString;
  } else if (continueTokenType == TokenTypeEnum::scBackQuotation) {
    tokenDelimiter = '`';
    charCodesTokenType = TokenTypeEnum::ltRawString;
  }
  for (size_t pos = pos_; pos < bufferSize;) {
    chr0 = *(bufferPtr + pos);
    // 1 byte (U+0000 - U+007f)
    if ((chr0 & 0x80) == 0) {
      if (chr0 == '\0' || chr0 == tokenDelimiter) {
        isAnalyzeContinue = false;
        break;
      }
      if (chr0 != '\\') {
        pos++;
        tokenSize++;
        nextTokenLen++;
        continue;
      }
      if (nextTokenLen > 0) {
        pushToken(nextTokenPos, nextTokenLen, charCodesTokenType);
        location = computeLocation(nextTokenPos, nextTokenLen, location);
        nextToken = new Token(location);
        nextTokenPos = pos;
        nextTokenLen = 0;
      }
      chr1 = *(bufferPtr + pos + 1);
      if (chr1 == '\r' || chr1 == '\n') {
        pos++;
        tokenSize++;
        nextTokenPos++;
        nextTokenLen += toNextToken(pos);
        pos += nextTokenLen;
        tokenSize += nextTokenLen;
        nextToken = new Token(location);
        nextTokenPos = pos;
        nextTokenLen = 0;
        continue;
      } else if (chr1 == 'o') {
        pos += 2;
        nextTokenLen = 2;
        tokenSize += 2;
        pushToken(nextTokenPos, nextTokenLen,
                  TokenTypeEnum::ltEscapeSequenceUtf8CodeOctal);
        location = computeLocation(pos, nextTokenLen, location);
        nextToken = new Token(location);
        size_t nTokenLen = scanningOctalNumber(pos);
        nextToken = new Token(location);
        pos += nTokenLen;
        tokenSize += nTokenLen;
        nextTokenPos = pos;
        nextTokenLen = 0;
        continue;
      } else if (chr1 == 'x') {
        pos += 2;
        nextTokenLen = 2;
        tokenSize += 2;
        pushToken(nextTokenPos, nextTokenLen,
                  TokenTypeEnum::ltEscapeSequenceUtf8CodeHexadecimal);
        location = computeLocation(pos, nextTokenLen, location);
        nextToken = new Token(location);
        size_t nTokenLen = scanningHexadecimalNumber(pos);
        nextToken = new Token(location);
        pos += nTokenLen;
        tokenSize += nTokenLen;
        nextTokenPos = pos;
        nextTokenLen = 0;
        continue;
      } else if (chr1 == 'u') {
        pos += 2;
        nextTokenLen = 2;
        tokenSize += 2;
        pushToken(nextTokenPos, nextTokenLen,
                  TokenTypeEnum::ltEscapeSequenceUtf16CodeHexadecimal);
        location = computeLocation(pos, nextTokenLen, location);
        nextToken = new Token(location);
        size_t nTokenLen = scanningHexadecimalNumber(pos);
        nextToken = new Token(location);
        pos += nTokenLen;
        tokenSize += nTokenLen;
        nextTokenPos = pos;
        nextTokenLen = 0;
        continue;
      } else {
        pos += 2;
        nextTokenLen = 2;
        tokenSize += 2;
        pushToken(nextTokenPos, nextTokenLen, TokenTypeEnum::ltEscapeSequence);
        location = computeLocation(nextTokenPos, nextTokenLen, location);
        nextToken = new Token(location);
        nextTokenPos = pos;
        nextTokenLen = 0;
        continue;
      }
    }
    // 2 byte (U+0080 - U+07ff)
    else if ((chr0 & 0xe0) == 0xc0) {
      tokenSize += 2;
      nextTokenLen += 2;
      pos += 2;
    }
    // 3 byte (U+0800 - U+ffff)
    else if ((chr0 & 0xf0) == 0xe0) {
      tokenSize += 3;
      nextTokenLen += 3;
      pos += 3;
    }
    // 4 byte (U+010000 - U+01ffff)
    else if ((chr0 & 0xf8) == 0xf0) {
      tokenSize += 4;
      nextTokenLen += 4;
      pos += 4;
    }
  }
  if (nextTokenLen > 0) {
    pushToken(nextTokenPos, nextTokenLen, charCodesTokenType);
    location = computeLocation(nextTokenPos, nextTokenLen, location);
    nextToken = new Token(location);
  }
  return tokenSize;
};

size_t LexicalAnalyzer::scanningOnelineComment(const size_t &pos_) {
  size_t tokenSize = 0, actualTokenLen = 0;
  char chr0;
  TokenTypeEnum coTokenType = TokenTypeEnum::coString;
  if (continueTokenType == TokenTypeEnum::scOnelineCommentOutDoc) {
    coTokenType = TokenTypeEnum::coStringDoc;
  }
  for (chr0 = *(bufferPtr + pos_ + tokenSize);
       chr0 != '\0' && chr0 != '\r' && chr0 != '\n';
       tokenSize++, chr0 = *(bufferPtr + pos_ + tokenSize))
    ;
  actualTokenLen = tokenSize;
  size_t tailPos = 0;
  for (tailPos = 0, chr0 = *(bufferPtr + pos_ + tokenSize - tailPos - 1);
       tailPos < tokenSize && (chr0 == ' ' || chr0 == '\t'); tailPos++,
      chr0 = *(bufferPtr + pos_ + tokenSize - tailPos - 1), actualTokenLen--)
    ;
  if (actualTokenLen > 0) {
    pushToken(pos_, actualTokenLen, coTokenType);
  }
  isAnalyzeContinue = false;
  continueTokenType = TokenTypeEnum::unknown;
  location = computeLocation(pos_, tokenSize, location);
  nextToken = new Token(location);
  return tokenSize;
};

size_t LexicalAnalyzer::scanningBlockComment(const size_t &pos_) {
  size_t tokenSize = 0, nextTokenLen = 0, nextTokenPos = pos_,
         actualTokenLen = 0;
  char chr0, chr1, chr2;
  chr0 = *(bufferPtr + pos_ + tokenSize);
  TokenTypeEnum coTokenType = TokenTypeEnum::coString;
  if (continueTokenType == TokenTypeEnum::scBlockCommentOutDocOpen) {
    coTokenType = TokenTypeEnum::coStringDoc;
  }

  bool commentBlockFlag = coTokenType == TokenTypeEnum::coString;
  for (size_t pos = pos_; pos < bufferSize;) {
    chr0 = *(bufferPtr + pos);
    // 1 byte (U+0000 - U+007f)
    if ((chr0 & 0x80) == 0) {
      if (chr0 == '\0') {
        break;
      }
      if (chr0 == '\\') {
        chr1 = *(bufferPtr + pos + 1);
        if (chr1 == '\r' || chr1 == '\n') {
          if (nextTokenLen > 0) {
            pushToken(nextTokenPos, nextTokenLen, coTokenType);
          }
          pos++;
          tokenSize++;
          nextTokenLen++;
          size_t nlTokenLen = toNextToken(pos);
          pos += nlTokenLen;
          tokenSize += nlTokenLen;
          nextTokenLen += nlTokenLen;
          location = computeLocation(nextTokenPos, nextTokenLen, location);
          nextToken = new Token(location);
          nextTokenPos = pos;
          nextTokenLen = 0;
          continue;
        } else {
          pos += 2;
          tokenSize += 2;
          nextTokenLen += 2;
          continue;
        }
      } else if (chr0 == '/') {
        chr1 = *(bufferPtr + pos + 1);
        if (commentBlockFlag && chr1 == '/') {
          chr2 = *(bufferPtr + pos + 2);
          if (chr2 == '>') {
            isAnalyzeContinue = false;
            continueTokenType = TokenTypeEnum::unknown;
            break;
          }
        } else if (!commentBlockFlag && chr1 == '#') {
          chr2 = *(bufferPtr + pos + 2);
          if (chr2 == '>') {
            isAnalyzeContinue = false;
            continueTokenType = TokenTypeEnum::unknown;
            break;
          }
        }
      }
      pos++;
      tokenSize++;
      nextTokenLen++;
    }
    // 2 byte (U+0080 - U+07ff)
    else if ((chr0 & 0xe0) == 0xc0) {
      tokenSize += 2;
      nextTokenLen += 2;
      pos += 2;
    }
    // 3 byte (U+0800 - U+ffff)
    else if ((chr0 & 0xf0) == 0xe0) {
      tokenSize += 3;
      nextTokenLen += 3;
      pos += 3;
    }
    // 4 byte (U+010000 - U+01ffff)
    else if ((chr0 & 0xf8) == 0xf0) {
      tokenSize += 4;
      nextTokenLen += 4;
      pos += 4;
    }
  }
  actualTokenLen = nextTokenLen;
  if (!isAnalyzeContinue) {
    size_t tailPos = 0;
    for (tailPos = 0,
        chr0 = *(bufferPtr + nextTokenPos + nextTokenLen - tailPos - 1);
         tailPos < nextTokenLen &&
         (chr0 == '\t' || chr0 == '\f' || chr0 == '\v' || chr0 == '\r' ||
          chr0 == '\n' || chr0 == ' ');
         tailPos++,
        chr0 = *(bufferPtr + nextTokenPos + nextTokenLen - tailPos - 1),
        actualTokenLen--)
      ;
  }
  if (actualTokenLen > 0) {
    pushToken(nextTokenPos, actualTokenLen, coTokenType);
  }
  location = computeLocation(nextTokenPos, nextTokenLen, location);
  nextToken = new Token(location);
  return tokenSize;
};
#endif