#include "compiler/lexer/lexical_analyzer.hpp"

using namespace gallop::Compiler;
using namespace gallop::Compiler::Lexer;

// interpreter
LexicalAnalyzer::LexicalAnalyzer()
    : buffer(std::string("")), bufferLen(0), location(Location(0, 0)),
      interpreterFlag(true), laContFlags(0), filename(""), lineCnt(0),
      lines({}), tokens(new Tokens()) {
  bufferPtr = buffer.c_str();
};

// compiler from stdin
LexicalAnalyzer::LexicalAnalyzer(const std::vector<char> &buffer_)
    : buffer(std::string(buffer_.begin(), buffer_.end())),
      bufferLen(buffer_.size()), location(Location(1, 1)),
      interpreterFlag(false), laContFlags(0), filename(""), lineCnt(0),
      lines({}), tokens(new Tokens()) {
  bufferPtr = buffer.c_str();
  splitLinesFromBuffer();
  tokenize();
};

// compiler from file
LexicalAnalyzer::LexicalAnalyzer(const std::vector<char> &buffer_,
                                 const std::string &filename_)
    : buffer(std::string(buffer_.begin(), buffer_.end())),
      bufferLen(buffer_.size()), location(Location(filename_, 1, 1)),
      interpreterFlag(false), laContFlags(0), filename(filename_), lineCnt(0),
      lines({}), tokens(new Tokens()) {
  bufferPtr = buffer.c_str();
  splitLinesFromBuffer();
  tokenize();
};

// copier
LexicalAnalyzer::LexicalAnalyzer(const LexicalAnalyzer &rhs)
    : buffer(rhs.buffer), bufferLen(rhs.bufferLen), location(rhs.location),
      interpreterFlag(rhs.interpreterFlag), laContFlags(rhs.laContFlags),
      filename(rhs.filename), lineCnt(rhs.lineCnt), lines(rhs.lines) {
  bufferPtr = buffer.c_str();
  tokens = new Tokens();
  *tokens = *rhs.tokens;
};

// setter
LexicalAnalyzer &LexicalAnalyzer::operator=(const LexicalAnalyzer &rhs) {
  buffer = rhs.buffer;
  bufferLen = rhs.bufferLen;
  bufferPtr = buffer.c_str();
  location = rhs.location;
  interpreterFlag = rhs.interpreterFlag;
  laContFlags = rhs.laContFlags;
  filename = rhs.filename;
  lineCnt = rhs.lineCnt;
  lines = rhs.lines;
  tokens = new Tokens();
  *tokens = *rhs.tokens;
  return *this;
};

void LexicalAnalyzer::tokenizeNextBuffer(const std::vector<char> &buffer_) {
  if (!interpreterFlag) {
    return;
  }
  buffer = std::string(buffer_.begin(), buffer_.end());
  bufferLen = buffer_.size();
  bufferPtr = buffer.c_str();
  if (location.getLine() == 0) {
    location.addLine(1);
    location.rewindColumn();
  }
  splitLinesFromBuffer();
  tokenize();
};

void LexicalAnalyzer::splitLinesFromBuffer() {
  lineCnt = 0;
  if (bufferLen == 0) {
    return;
  };
  lineCnt++;
  size_t lineBeginPos = 0;
  for (size_t i = 0; i < bufferLen; i++) {
    if (*(bufferPtr + i) == '\n') {
      lines.push_back(
          std::string(buffer.begin() + lineBeginPos, buffer.begin() + i + 1));
      lineCnt++;
      lineBeginPos = i + 1;
    }
  }
  if (lineBeginPos < bufferLen) {
    lines.push_back(std::string(buffer.begin() + lineBeginPos, buffer.end()));
  }
  if (*(bufferPtr + bufferLen - 1) == '\n') {
    lineCnt--;
  }
};

uint64_t LexicalAnalyzer::getLexAnlzFlag() const { return laContFlags; };
bool LexicalAnalyzer::isInterpreter() const { return interpreterFlag; };
bool LexicalAnalyzer::isFromFile() const { return filename != ""; };
size_t LexicalAnalyzer::getLineCnt() const { return lineCnt; };
std::string LexicalAnalyzer::getLineString(const size_t line_) const {
  if (line_ == 0) {
    return "";
  }
  if (line_ <= lines.size()) {
    return lines.at(line_ - 1);
  }
  return "";
};
Tokens *LexicalAnalyzer::getTokens() { return tokens; };
bool LexicalAnalyzer::isLexAnlzContinue() const {
  return (laContFlags &
          (LaContFlags::LaContFlagsInLiteralRune |
           LaContFlags::LaContFlagsInLiteralString |
           LaContFlags::LaContFlagsInLiteralRegularExpressionPattern |
           LaContFlags::LaContFlagsInCommentOutBlock |
           LaContFlags::LaContFlagsInCommentOutBlockDoc)) > 0;
};

void LexicalAnalyzer::tokenize() {
  for (size_t pos = 0; pos < bufferLen;) {
    size_t tokenLen = 0;
    if ((laContFlags & LaContFlags::LaContFlagsInCommentOutOneline) > 0) {
      tokenLen = toNextToken(pos);
      location = computeLocation(pos, tokenLen, location);
      pos += tokenLen;
      nextToken = new Token(location);
      tokenLen = scanningOnelineComment(pos);
      location = computeLocation(pos, tokenLen, location);
      if (tokenLen > 0) {
        pos += tokenLen;
        if (pos >= bufferLen) {
          break;
        }
      }
    } else if ((laContFlags & LaContFlags::LaContFlagsInCommentOutBlock) > 0 ||
               (laContFlags & LaContFlags::LaContFlagsInCommentOutBlockDoc) >
                   0) {
      tokenLen = toNextToken(pos);
      location = computeLocation(pos, tokenLen, location);
      pos += tokenLen;
      nextToken = new Token(location);
      tokenLen = scanningBlockComment(pos);
      if (tokenLen > 0) {
        pos += tokenLen;
        if (pos >= bufferLen) {
          break;
        }
      }
    } else if ((laContFlags & LaContFlags::LaContFlagsInLiteralRune) > 0 ||
               (laContFlags & LaContFlags::LaContFlagsInLiteralString) > 0 ||
               (laContFlags &
                LaContFlags::LaContFlagsInLiteralRegularExpressionPattern) >
                   0) {
      nextToken = new Token(location);
      tokenLen = scanningRunes(pos);
      location = computeLocation(pos, tokenLen, location);
      if (tokenLen > 0) {
        pos += tokenLen;
        if (pos >= bufferLen) {
          break;
        }
      }
    }
    tokenLen = toNextToken(pos);
    location = computeLocation(pos, tokenLen, location);
    if (tokenLen > 0) {
      pos += tokenLen;
      if (pos >= bufferLen) {
        break;
      }
    }
    nextToken = new Token(location);
    tokenLen = scanningToken(pos);
    location = computeLocation(pos, tokenLen, location);
    if (tokenLen > 0) {
      pos += tokenLen;
    }
  }
};

size_t LexicalAnalyzer::toNextToken(const size_t pos_) {
  size_t tokenLen = 0;
  for (size_t pos = pos_ + tokenLen;
       *(bufferPtr + pos) != '\0' &&
       (*(bufferPtr + pos) == '\t' || *(bufferPtr + pos) == '\f' ||
        *(bufferPtr + pos) == '\v' || *(bufferPtr + pos) == '\r' ||
        *(bufferPtr + pos) == '\n' || *(bufferPtr + pos) == ' ');
       pos++, tokenLen++)
    ;
  return tokenLen;
};

Location LexicalAnalyzer::computeLocation(const size_t pos_,
                                          const size_t tokenLen_,
                                          const Location location_) {
  std::string filenameN = location_.getFilename();
  size_t lineN = location_.getLine();
  size_t columnN = location_.getColumn();
  for (size_t pos = pos_;
       *(bufferPtr + pos) != '\0' && pos < pos_ + tokenLen_;) {
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

void LexicalAnalyzer::pushToken(const size_t pos_, const size_t tokenLen_,
                                const TokenTypeEnum tokenType_) {
  std::string token =
      std::string(buffer.begin() + pos_, buffer.begin() + pos_ + tokenLen_);
  TokenTypeEnum tokenType = tokenType_;
  nextToken->setTokenVal(tokenType, token);
  tokens->push(nextToken);
};

size_t LexicalAnalyzer::scanningToken(const size_t pos_) {
  size_t tokenLen = 0;
  char chr0 = *(bufferPtr + pos_);
  if (chr0 == '0') {
    tokenLen += scanningNonDecimalNumber(pos_);
    if (tokenLen > 0) {
      return tokenLen;
    }
  }
  if (('0' <= chr0 && chr0 <= '9')) {
    tokenLen += scanningDecimalNumber(pos_);
  } else if (('A' <= chr0 && chr0 <= 'Z') || ('a' <= chr0 && chr0 <= 'z') ||
             chr0 == '_') {
    tokenLen += scanningIdentifier(pos_);
  } else {
    tokenLen += scanningSymbolCharacters(pos_);
  }
  return tokenLen;
};

size_t LexicalAnalyzer::scanningIdentifier(const size_t pos_) {
  size_t tokenLen = 0;
  char chr0;
  for (chr0 = *(bufferPtr + pos_ + tokenLen);
       ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'Z') ||
       ('a' <= chr0 && chr0 <= 'z') || chr0 == '_';
       tokenLen++, chr0 = *(bufferPtr + pos_ + tokenLen))
    ;
  if (tokenLen == 1 && chr0 == '_') {
    pushToken(pos_, tokenLen, TokenTypeEnum::symbolCharacterUnderline);
  } else {
    pushToken(pos_, tokenLen, TokenTypeEnum::identifier);
  }
  // identifier
  return tokenLen;
};

size_t LexicalAnalyzer::scanningSymbolCharacters(const size_t pos_) {
  size_t tokenLen = 0;
  char chr0, chr1, chr2, chr3;
  TokenTypeEnum tokenType = TokenTypeEnum::unknown;
  TokenTypeEnum prevTokenType = tokens->getLastTokenType();
  chr0 = *(bufferPtr + pos_);
  switch (chr0) {
    // arithmetic
  case '+':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '%':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterPlusPercentEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterPlusPercent;
        tokenLen = 2;
        break;
      }
      break;
    case '|':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterPlusPipelineEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterPlusPipeline;
        tokenLen = 2;
        break;
      }
      break;
    case '+':
      tokenType = TokenTypeEnum::symbolCharacterPlusPlus;
      tokenLen = 2;
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterPlusEqual;
      tokenLen = 2;
      break;
    default:
      if ('0' <= chr1 && chr1 <= '9') {
        if (prevTokenType ==
            // exponent sign
            TokenTypeEnum::literalDecimalNumberExponentOperator) {
          tokenType = TokenTypeEnum::symbolCharacterPositiveDecimalExponent;
        } else {
          tokenType = TokenTypeEnum::symbolCharacterPlus;
        }
      } else {
        tokenType = TokenTypeEnum::symbolCharacterPlus;
      }
      tokenLen = 1;
      break;
    }
    break;
  case '-':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '%':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterMinusPercentEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterMinusPercent;
        tokenLen = 2;
        break;
      }
      break;
    case '|':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterMinusPipelineEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterMinusPipeline;
        tokenLen = 2;
        break;
      }
      break;
    case '-':
      tokenType = TokenTypeEnum::symbolCharacterMinusMinus;
      tokenLen = 2;
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterMinusEqual;
      tokenLen = 2;
      break;
    default:
      if ('0' <= chr1 && chr1 <= '9') {
        if (prevTokenType ==
            TokenTypeEnum::literalDecimalNumberExponentOperator) {
          // exponent sign
          tokenType = TokenTypeEnum::symbolCharacterNegativeDecimalExponent;
        } else {
          tokenType = TokenTypeEnum::symbolCharacterMinus;
        }
      } else {
        tokenType = TokenTypeEnum::symbolCharacterMinus;
      }
      tokenLen = 1;
      break;
    }
    break;
  case '*':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '%':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterAsteriskPercentEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterAsteriskPercent;
        tokenLen = 2;
        break;
      }
      break;
    case '|':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterAsteriskPipelineEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterAsteriskPipeline;
        tokenLen = 2;
        break;
      }
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterAsteriskEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterAsterisk;
      tokenLen = 1;
      break;
    }
    break;
  case '/':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '/':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '<':
        tokenType = TokenTypeEnum::symbolCharacterSlashSlashLess;
        tokenLen = 3;
        if ((laContFlags & LaContFlags::LaContFlagsInCommentOutBlock) == 0) {
          laContFlags |= LaContFlags::LaContFlagsInCommentOutBlock;
        }
        break;
      case '>':
        tokenType = TokenTypeEnum::symbolCharacterSlashSlashGreater;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterSlashSlash;
        if ((laContFlags & LaContFlags::LaContFlagsInCommentOutOneline) == 0) {
          laContFlags |= LaContFlags::LaContFlagsInCommentOutOneline;
        }
        tokenLen = 2;
        break;
      }
      break;
    case '#':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '<':
        tokenType = TokenTypeEnum::symbolCharacterSlashNumbersignLess;
        tokenLen = 3;
        if ((laContFlags & LaContFlags::LaContFlagsInCommentOutBlockDoc) == 0) {
          laContFlags |= LaContFlags::LaContFlagsInCommentOutBlockDoc;
        }
        break;
      case '>':
        tokenType = TokenTypeEnum::symbolCharacterSlashNumbersignGreater;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterSlashNumbersign;
        tokenLen = 2;
        if ((laContFlags & LaContFlags::LaContFlagsInCommentOutOneline) == 0) {
          laContFlags |= LaContFlags::LaContFlagsInCommentOutOneline;
        }
        break;
      }
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterSlashEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterSlash;
      tokenLen = 1;
      break;
    }
    break;
  case '%':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterPercentEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterPercent;
      tokenLen = 1;
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
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterAmpersandAmpersandEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterAmpersandAmpersand;
        tokenLen = 2;
        break;
      }
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterAmpersandEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterAmpersand;
      tokenLen = 1;
      break;
    }
    break;
  case '|':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '|':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterPipelinePipelineEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterPipelinePipeline;
        tokenLen = 2;
        break;
      }
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterPipelineEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterPipeline;
      tokenLen = 1;
      break;
    }
    break;
  case '^':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterCaretEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterCaret;
      tokenLen = 1;
      break;
    }
    break;
  case '~':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::symbolCharacterTilde;
      tokenLen = 1;
      break;
    }
    break;
  case '!':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterExclamationEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterExclamation;
      tokenLen = 1;
      break;
    }
    break;
  case '=':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterEqualEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterEqual;
      tokenLen = 1;
      break;
    }
    break;
  case '<':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '<':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '|':
        chr3 = *(bufferPtr + pos_ + 3);
        switch (chr3) {
        case '=':
          tokenType = TokenTypeEnum::symbolCharacterLessLessPipelineEqual;
          tokenLen = 4;
          break;
        default:
          tokenType = TokenTypeEnum::symbolCharacterLessLessPipeline;
          tokenLen = 3;
          break;
        }
        break;
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterLessLessEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterLessLess;
        tokenLen = 2;
        break;
      }
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterLessEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterLess;
      tokenLen = 1;
      break;
    }
    break;
  case '>':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case '>':
      chr2 = *(bufferPtr + pos_ + 2);
      switch (chr2) {
      case '=':
        tokenType = TokenTypeEnum::symbolCharacterGreaterGreaterEqual;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterGreaterGreater;
        tokenLen = 2;
        break;
      }
      break;
    case '=':
      tokenType = TokenTypeEnum::symbolCharacterGreaterEqual;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterGreater;
      tokenLen = 1;
      break;
    }
    break;
  case '$':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::symbolCharacterDoller;
      tokenLen = 1;
      break;
    }
    break;
  case '#':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::symbolCharacterNumbersign;
      tokenLen = 1;
      break;
    }
    break;
  case '?':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::symbolCharacterQuestion;
      tokenLen = 1;
      break;
    }
    break;
  case '@':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::symbolCharacterAtmark;
      tokenLen = 1;
      break;
    }
    break;
  case ':':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    case ':':
      tokenType = TokenTypeEnum::symbolCharacterColonColon;
      tokenLen = 2;
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterColon;
      tokenLen = 1;
      break;
    }
    break;
  case ';':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::symbolCharacterSemicolon;
      tokenLen = 1;
      break;
    }
    break;
  case ',':
    chr1 = *(bufferPtr + pos_ + 1);
    switch (chr1) {
    default:
      tokenType = TokenTypeEnum::symbolCharacterComma;
      tokenLen = 1;
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
        tokenType = TokenTypeEnum::symbolCharacterDotDotDot;
        tokenLen = 3;
        break;
      default:
        tokenType = TokenTypeEnum::symbolCharacterDotDot;
        tokenLen = 2;
        break;
      }
      break;
    default:
      tokenType = TokenTypeEnum::symbolCharacterDot;
      tokenLen = 1;
      if (prevTokenType == TokenTypeEnum::literalDecimalNumberIntegralPart) {
        if (chr1 == 'e' || chr1 == 'E') {
          chr2 = *(bufferPtr + pos_ + 2);
          if (chr2 == '+' || chr2 == '-' || ('0' <= chr2 && chr2 <= '9')) {
            pushToken(pos_, tokenLen, tokenType);
            nextToken = new Token(location);
            // passing exponent charcter [e|E]
            pushToken(pos_ + tokenLen, 1,
                      TokenTypeEnum::literalDecimalNumberExponentOperator);
            nextToken = new Token(location);
            tokenType = TokenTypeEnum::unknown;
            tokenLen++;
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
      tokenType = TokenTypeEnum::symbolCharacterBackslash;
      tokenLen = 1;
      break;
    }
    break;
  case '\'':
    tokenType = TokenTypeEnum::symbolCharacterSinglequote;
    tokenLen++;
    if ((laContFlags & LaContFlags::LaContFlagsInLiteralRune) > 0) {
      laContFlags &= ~LaContFlags::LaContFlagsInLiteralRune;
    } else {
      laContFlags |= LaContFlags::LaContFlagsInLiteralRune;
    }
    break;
  case '"':
    tokenType = TokenTypeEnum::symbolCharacterDoublequote;
    tokenLen++;
    if ((laContFlags & LaContFlags::LaContFlagsInLiteralString) > 0) {
      laContFlags &= ~LaContFlags::LaContFlagsInLiteralString;
    } else {
      laContFlags |= LaContFlags::LaContFlagsInLiteralString;
    }
    break;
  case '`':
    tokenType = TokenTypeEnum::symbolCharacterBackquote;
    tokenLen++;
    if ((laContFlags &
         LaContFlags::LaContFlagsInLiteralRegularExpressionPattern) > 0) {
      laContFlags &= ~LaContFlags::LaContFlagsInLiteralRegularExpressionPattern;
    } else {
      laContFlags |= LaContFlags::LaContFlagsInLiteralRegularExpressionPattern;
    }
    break;
  case '(':
    tokenType = TokenTypeEnum::symbolCharacterLeftparentheses;
    tokenLen++;
    break;
  case ')':
    tokenType = TokenTypeEnum::symbolCharacterRightparentheses;
    tokenLen++;
    break;
  case '{':
    tokenType = TokenTypeEnum::symbolCharacterLeftcurlybrackets;
    tokenLen++;
    break;
  case '}':
    tokenType = TokenTypeEnum::symbolCharacterRightcurlybrackets;
    tokenLen++;
    break;
  case '[':
    tokenType = TokenTypeEnum::symbolCharacterLeftsquarebrackets;
    tokenLen++;
    break;
  case ']':
    tokenType = TokenTypeEnum::symbolCharacterRightsquarebrackets;
    tokenLen++;
    break;
  default:
    break;
  }
  if (tokenType != TokenTypeEnum::unknown) {
    pushToken(pos_, tokenLen, tokenType);
  }
  return tokenLen;
};

size_t LexicalAnalyzer::scanningNonDecimalNumber(const size_t pos_) {
  size_t tokenLen = 0, numberTokenLen = 0;
  char chr1;
  chr1 = *(bufferPtr + pos_ + 1);
  TokenTypeEnum tokenType = TokenTypeEnum::unknown;
  // binary number
  if (chr1 == 'b' || chr1 == 'B') {
    tokenType = TokenTypeEnum::literalBinaryPrefix;
    tokenLen = 2;
    pushToken(pos_, tokenLen, tokenType);
    nextToken = new Token(location);
    numberTokenLen = scanningBinaryNumber(pos_ + tokenLen);
    if (numberTokenLen > 0) {
      tokenLen += numberTokenLen;
    }
  }
  // ocatal number
  else if (chr1 == 'o' || chr1 == 'O') {
    tokenType = TokenTypeEnum::literalOctalPrefix;
    tokenLen = 2;
    pushToken(pos_, tokenLen, tokenType);
    nextToken = new Token(location);
    numberTokenLen = scanningOctalNumber(pos_ + tokenLen);
    if (numberTokenLen > 0) {
      tokenLen += numberTokenLen;
    }
  }
  // hexadecimal number
  else if (chr1 == 'x' || chr1 == 'X') {
    tokenType = TokenTypeEnum::literalHexadecimalPrefix;
    tokenLen = 2;
    pushToken(pos_, tokenLen, tokenType);
    nextToken = new Token(location);
    numberTokenLen = scanningHexadecimalNumber(pos_ + tokenLen);
    if (numberTokenLen > 0) {
      tokenLen += numberTokenLen;
    }
  }
  return tokenLen;
};

size_t LexicalAnalyzer::scanningDecimalNumber(const size_t pos_) {
  size_t tokenLen = 0;
  size_t pos = pos_;
  TokenTypeEnum prevTokenType = tokens->getLastTokenType();
  char chr0, chr1;
  chr0 = *(bufferPtr + pos_);
  if (prevTokenType == TokenTypeEnum::literalDecimalNumberExponentOperator ||
      prevTokenType == TokenTypeEnum::symbolCharacterNegativeDecimalExponent ||
      prevTokenType == TokenTypeEnum::symbolCharacterPositiveDecimalExponent) {
    // passing exponent part number
    for (pos = pos_ + tokenLen, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9');
         tokenLen++, pos++, chr0 = *(bufferPtr + pos))
      ;
  } else {
    // passing integral part number
    // passing decimal part number
    for (pos = pos_ + tokenLen, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9') || chr0 == '_';
         tokenLen++, pos++, chr0 = *(bufferPtr + pos))
      ;
  }
  if (prevTokenType == TokenTypeEnum::symbolCharacterDot) {
    pushToken(pos_, tokenLen, TokenTypeEnum::literalDecimalNumberDecimalPart);
    nextToken = new Token(location);
  } else if (prevTokenType ==
                 TokenTypeEnum::literalDecimalNumberExponentOperator ||
             prevTokenType ==
                 TokenTypeEnum::symbolCharacterNegativeDecimalExponent ||
             prevTokenType ==
                 TokenTypeEnum::symbolCharacterPositiveDecimalExponent) {
    pushToken(pos_, tokenLen, TokenTypeEnum::literalDecimalNumberExponentPart);
    nextToken = new Token(location);
  } else {
    pushToken(pos_, tokenLen, TokenTypeEnum::literalDecimalNumberIntegralPart);
    nextToken = new Token(location);
  }
  if (tokenLen > 0 && (chr0 == 'e' || chr0 == 'E')) {
    if (prevTokenType == TokenTypeEnum::literalDecimalNumberExponentOperator ||
        prevTokenType ==
            TokenTypeEnum::symbolCharacterNegativeDecimalExponent ||
        prevTokenType ==
            TokenTypeEnum::symbolCharacterPositiveDecimalExponent) {
      return tokenLen;
    } else {
      chr1 = *(bufferPtr + pos_ + tokenLen + 1);
      if (chr1 == '+' || chr1 == '-' || ('0' <= chr1 && chr1 <= '9')) {
        // passing exponent charcter [e|E]
        pushToken(pos_ + tokenLen, 1,
                  TokenTypeEnum::literalDecimalNumberExponentOperator);
        nextToken = new Token(location);
        tokenLen++;
      }
    }
  }
  return tokenLen;
};

size_t LexicalAnalyzer::scanningBinaryNumber(const size_t pos_) {
  size_t tokenLen = 0;
  size_t pos = pos_;
  char chr0;
  chr0 = *(bufferPtr + pos_ + tokenLen);
  // not binary number?
  if (!(chr0 == '0' || chr0 == '1')) {
    return tokenLen;
  }
  // passing binary number
  for (pos = pos_ + tokenLen, chr0 = *(bufferPtr + pos);
       chr0 == '0' || chr0 == '1' || chr0 == '_';
       tokenLen++, pos++, chr0 = *(bufferPtr + pos))
    ;
  // binary number
  pushToken(pos_, tokenLen, TokenTypeEnum::literalBinaryNumber);
  return tokenLen;
};

size_t LexicalAnalyzer::scanningOctalNumber(const size_t pos_) {
  size_t tokenLen = 0;
  size_t pos = pos_;
  char chr0;
  chr0 = *(bufferPtr + pos_ + tokenLen);
  // not octal number?
  if (!('0' <= chr0 && chr0 <= '7')) {
    return tokenLen;
  }
  TokenTypeEnum prevTokenType = tokens->getLastTokenType();
  if (prevTokenType == TokenTypeEnum::literalOctalPrefix) {
    // passing octal number
    for (pos = pos_ + tokenLen, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '7') || chr0 == '_';
         tokenLen++, pos++, chr0 = *(bufferPtr + pos))
      ;
  } else {
    // passing octal number
    for (pos = pos_ + tokenLen, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '7');
         tokenLen++, pos++, chr0 = *(bufferPtr + pos))
      ;
  }
  // octal number
  pushToken(pos_, tokenLen, TokenTypeEnum::literalOctalNumber);
  return tokenLen;
};

size_t LexicalAnalyzer::scanningHexadecimalNumber(const size_t pos_) {
  size_t tokenLen = 0;
  size_t pos = pos_;
  char chr0;
  chr0 = *(bufferPtr + pos_ + tokenLen);
  // not hexadecimal number?
  if (!(('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'F') ||
        ('a' <= chr0 && chr0 <= 'f'))) {
    return tokenLen;
  }
  TokenTypeEnum prevTokenType = tokens->getLastTokenType();
  if (prevTokenType == TokenTypeEnum::literalHexadecimalPrefix) {
    // passing hexadecimal number
    for (pos = pos_ + tokenLen, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'F') ||
         ('a' <= chr0 && chr0 <= 'f') || chr0 == '_';
         tokenLen++, pos++, chr0 = *(bufferPtr + pos))
      ;
  } else {
    // passing hexadecimal number
    for (pos = pos_ + tokenLen, chr0 = *(bufferPtr + pos);
         ('0' <= chr0 && chr0 <= '9') || ('A' <= chr0 && chr0 <= 'F') ||
         ('a' <= chr0 && chr0 <= 'f');
         tokenLen++, pos++, chr0 = *(bufferPtr + pos))
      ;
  }
  // hexadecimal number
  pushToken(pos_, tokenLen, TokenTypeEnum::literalHexadecimalNumber);
  return tokenLen;
};

size_t LexicalAnalyzer::scanningRunes(const size_t pos_) {
  size_t tokenLen = 0, nextTokenLen = 0, nextTokenPos = pos_;
  char chr0, chr1;
  chr0 = *(bufferPtr + pos_ + tokenLen);
  char tokenDelimiter = '\'';
  if ((laContFlags & LaContFlags::LaContFlagsInLiteralString) > 0) {
    tokenDelimiter = '"';
  } else if ((laContFlags &
              LaContFlags::LaContFlagsInLiteralRegularExpressionPattern) > 0) {
    tokenDelimiter = '`';
  }
  for (size_t pos = pos_; pos < bufferLen;) {
    chr0 = *(bufferPtr + pos);
    // 1 byte (U+0000 - U+007f)
    if ((chr0 & 0x80) == 0) {
      if (chr0 == '\0' || chr0 == tokenDelimiter) {
        break;
      }
      if (chr0 == '\\') {
        chr1 = *(bufferPtr + pos + 1);
        if (chr1 == '\r' || chr1 == '\n') {
          if (nextTokenLen > 0) {
            if ((laContFlags & LaContFlags::LaContFlagsInLiteralString) > 0) {
              pushToken(nextTokenPos, nextTokenLen,
                        TokenTypeEnum::literalString);
            } else if ((laContFlags &
                        LaContFlags::
                            LaContFlagsInLiteralRegularExpressionPattern) > 0) {
              pushToken(nextTokenPos, nextTokenLen,
                        TokenTypeEnum::literalRegularExpressionPattern);
            } else {
              pushToken(nextTokenPos, nextTokenLen, TokenTypeEnum::literalRune);
            }
          }
          pos++;
          tokenLen++;
          size_t nlTokenLen = toNextToken(pos);
          location = computeLocation(pos, tokenLen, location);
          pos += nlTokenLen;
          tokenLen += nlTokenLen;
          nextToken = new Token(location);
          nextTokenPos = pos;
          nextTokenLen = 0;
          continue;
        } else if (chr1 == 'o') {
          pos += 2;
          nextTokenLen += 2;
          tokenLen += 2;
          pushToken(nextTokenPos, nextTokenLen,
                    TokenTypeEnum::literalRuneOctalEscapeSequence);
          nextToken = new Token(location);
          size_t nTokenLen = scanningOctalNumber(pos);
          location = computeLocation(pos, nTokenLen, location);
          pos += nTokenLen;
          tokenLen += nTokenLen;
          if (nTokenLen > 0) {
            nextToken = new Token(location);
          }
          nextTokenPos = pos;
          nextTokenLen = 0;
          continue;
        } else if (chr1 == 'x') {
          pos += 2;
          nextTokenLen += 2;
          tokenLen += 2;
          pushToken(nextTokenPos, nextTokenLen,
                    TokenTypeEnum::literalRuneHexadecimalEscapeSequence);
          nextToken = new Token(location);
          size_t nTokenLen = scanningHexadecimalNumber(pos);
          location = computeLocation(pos, nTokenLen, location);
          pos += nTokenLen;
          tokenLen += nTokenLen;
          if (nTokenLen > 0) {
            nextToken = new Token(location);
          }
          nextTokenPos = pos;
          nextTokenLen = 0;
          continue;
        } else if (chr1 == 'u') {
          pos += 2;
          nextTokenLen += 2;
          tokenLen += 2;
          pushToken(nextTokenPos, nextTokenLen,
                    TokenTypeEnum::literalRuneUnicodePointEscapeSequence);
          nextToken = new Token(location);
          size_t nTokenLen = scanningHexadecimalNumber(pos);
          location = computeLocation(pos, nTokenLen, location);
          pos += nTokenLen;
          tokenLen += nTokenLen;
          if (nTokenLen > 0) {
            nextToken = new Token(location);
          }
          nextTokenPos = pos;
          nextTokenLen = 0;
          continue;
        } else {
          pos += 2;
          nextTokenLen += 2;
          tokenLen += 2;
          pushToken(nextTokenPos, nextTokenLen,
                    TokenTypeEnum::literalEscapeSequence);
          location = computeLocation(nextTokenPos, nextTokenLen, location);
          nextToken = new Token(location);
          nextTokenPos = pos;
          nextTokenLen = 0;
          continue;
        }
      }
      pos++;
      tokenLen++;
      nextTokenLen++;
    }
    // 2 byte (U+0080 - U+07ff)
    else if ((chr0 & 0xe0) == 0xc0) {
      tokenLen += 2;
      nextTokenLen += 2;
      pos += 2;
    }
    // 3 byte (U+0800 - U+ffff)
    else if ((chr0 & 0xf0) == 0xe0) {
      tokenLen += 3;
      nextTokenLen += 3;
      pos += 3;
    }
    // 4 byte (U+010000 - U+01ffff)
    else if ((chr0 & 0xf8) == 0xf0) {
      tokenLen += 4;
      nextTokenLen += 4;
      pos += 4;
    }
  }
  if (nextTokenLen > 0) {
    if ((laContFlags & LaContFlags::LaContFlagsInLiteralString) > 0) {
      pushToken(nextTokenPos, nextTokenLen, TokenTypeEnum::literalString);
    } else if ((laContFlags &
                LaContFlags::LaContFlagsInLiteralRegularExpressionPattern) >
               0) {
      pushToken(nextTokenPos, nextTokenLen,
                TokenTypeEnum::literalRegularExpressionPattern);
    } else {
      pushToken(nextTokenPos, nextTokenLen, TokenTypeEnum::literalRune);
    }
    nextToken = new Token(location);
  }
  return tokenLen;
};

size_t LexicalAnalyzer::scanningOnelineComment(const size_t pos_) {
  size_t tokenLen = 0, actualTokenLen = 0;
  char chr0;
  TokenTypeEnum prevTokenType = tokens->getLastTokenType();
  for (chr0 = *(bufferPtr + pos_ + tokenLen);
       chr0 != '\0' && chr0 != '\r' && chr0 != '\n';
       tokenLen++, chr0 = *(bufferPtr + pos_ + tokenLen))
    ;
  actualTokenLen = tokenLen;
  size_t tailPos = 0;
  for (tailPos = 0, chr0 = *(bufferPtr + pos_ + tokenLen - tailPos - 1);
       tailPos < tokenLen && (chr0 == ' ' || chr0 == '\t'); tailPos++,
      chr0 = *(bufferPtr + pos_ + tokenLen - tailPos - 1), actualTokenLen--)
    ;
  if (actualTokenLen > 0) {
    if (prevTokenType == TokenTypeEnum::symbolCharacterSlashSlash) {
      pushToken(pos_, actualTokenLen, TokenTypeEnum::commentOutOneline);
    } else {
      pushToken(pos_, actualTokenLen, TokenTypeEnum::commentOutOnelineDoc);
    }
  }
  laContFlags &= ~LaContFlags::LaContFlagsInCommentOutOneline;
  nextToken = new Token(location);
  return tokenLen;
};

size_t LexicalAnalyzer::scanningBlockComment(const size_t pos_) {
  size_t tokenLen = 0, nextTokenLen = 0, nextTokenPos = pos_,
         actualTokenLen = 0;
  char chr0, chr1, chr2;
  chr0 = *(bufferPtr + pos_ + tokenLen);
  bool commentBlockFlag =
      (laContFlags & LaContFlags::LaContFlagsInCommentOutBlock) > 0;
  bool commentBlockDocFlag =
      (laContFlags & LaContFlags::LaContFlagsInCommentOutBlockDoc) > 0;
  for (size_t pos = pos_; pos < bufferLen;) {
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
            if (commentBlockFlag) {
              pushToken(nextTokenPos, nextTokenLen,
                        TokenTypeEnum::commentOutBlock);
            } else if (commentBlockDocFlag) {
              pushToken(nextTokenPos, nextTokenLen,
                        TokenTypeEnum::commentOutBlockDoc);
            }
          }
          pos++;
          tokenLen++;
          nextTokenLen++;
          size_t nlTokenLen = toNextToken(pos);
          pos += nlTokenLen;
          tokenLen += nlTokenLen;
          nextTokenLen += nlTokenLen;
          location = computeLocation(nextTokenPos, nextTokenLen, location);
          nextToken = new Token(location);
          nextTokenPos = pos;
          nextTokenLen = 0;
          continue;
        } else {
          pos += 2;
          tokenLen += 2;
          nextTokenLen += 2;
          continue;
        }
      } else if (chr0 == '/') {
        chr1 = *(bufferPtr + pos + 1);
        if (commentBlockFlag && chr1 == '/') {
          chr2 = *(bufferPtr + pos + 2);
          if (chr2 == '>') {
            laContFlags &= ~LaContFlags::LaContFlagsInCommentOutBlock;
            break;
          }
        } else if (commentBlockDocFlag && chr1 == '#') {
          chr2 = *(bufferPtr + pos + 2);
          if (chr2 == '>') {
            laContFlags &= ~LaContFlags::LaContFlagsInCommentOutBlockDoc;
            break;
          }
        }
      }
      pos++;
      tokenLen++;
      nextTokenLen++;
    }
    // 2 byte (U+0080 - U+07ff)
    else if ((chr0 & 0xe0) == 0xc0) {
      tokenLen += 2;
      nextTokenLen += 2;
      pos += 2;
    }
    // 3 byte (U+0800 - U+ffff)
    else if ((chr0 & 0xf0) == 0xe0) {
      tokenLen += 3;
      nextTokenLen += 3;
      pos += 3;
    }
    // 4 byte (U+010000 - U+01ffff)
    else if ((chr0 & 0xf8) == 0xf0) {
      tokenLen += 4;
      nextTokenLen += 4;
      pos += 4;
    }
  }
  actualTokenLen = nextTokenLen;
  if ((laContFlags & LaContFlags::LaContFlagsInCommentOutBlock) == 0 &&
      (laContFlags & LaContFlags::LaContFlagsInCommentOutBlockDoc) == 0) {
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
    if (commentBlockFlag) {
      pushToken(nextTokenPos, actualTokenLen, TokenTypeEnum::commentOutBlock);
    } else if (commentBlockDocFlag) {
      pushToken(nextTokenPos, actualTokenLen,
                TokenTypeEnum::commentOutBlockDoc);
    }
  }
  location = computeLocation(nextTokenPos, nextTokenLen, location);
  nextToken = new Token(location);
  return tokenLen;
};
