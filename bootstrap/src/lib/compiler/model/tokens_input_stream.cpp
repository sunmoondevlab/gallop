// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/tokens_input_stream.hpp"

using namespace gallop::Compiler;

TokensInputStream::TokensInputStream(const Tokens &tokens_)
    : tokens(const_cast<Tokens &>(tokens_)), pos(0), mark(0) {};
TokensInputStream::TokensInputStream(const TokensInputStream &rhs)
    : tokens(rhs.tokens), pos(rhs.pos), mark(rhs.mark) {};

TokensInputStream &TokensInputStream::operator=(const TokensInputStream &rhs) {
  tokens = rhs.tokens;
  pos = rhs.pos;
  mark = rhs.mark;
  return *this;
};
std::vector<Token *> TokensInputStream::data() { return tokens.getTokens(); };
Token *TokensInputStream::current() {
  std::vector<Token *> tokensData = tokens.getTokens();
  Token **tokensDataPtr = tokensData.data();
  if (hasReadable()) {
    return *(tokensDataPtr + pos);
  }
  return nullptr;
};
Token *TokensInputStream::read() {
  std::vector<Token *> tokensData = tokens.getTokens();
  Token **tokensDataPtr = tokensData.data();
  if (hasReadable()) {
    Token *i32 = *(tokensDataPtr + pos);
    pos++;
    return i32;
  }
  return nullptr;
};
Token *TokensInputStream::undo() {
  std::vector<Token *> tokensData = tokens.getTokens();
  Token **tokensDataPtr = tokensData.data();
  if (pos == 0) {
    return nullptr;
  }
  pos--;
  return *(tokensDataPtr + pos);
};
Token *TokensInputStream::ahead() { return ahead(0ul); };
Token *TokensInputStream::ahead(const size_t &offset_) {
  std::vector<Token *> tokensData = tokens.getTokens();
  Token **tokensDataPtr = tokensData.data();
  if (readable() > (int64_t)(offset_ + 1)) {
    return *(tokensDataPtr + (pos + offset_ + 1));
  };
  return nullptr;
};
Token *TokensInputStream::tail() { return tail(0ul); };
Token *TokensInputStream::tail(const size_t &backOffset_) {
  std::vector<Token *> tokensData = tokens.getTokens();
  Token **tokensDataPtr = tokensData.data();
  size_t tokensDataSize = tokens.getTokenCount();
  if (tokensDataSize == 0) {
    return nullptr;
  }
  size_t pos = 0;
  if (tokensDataSize > backOffset_) {
    pos = tokensDataSize - backOffset_ - 1;
  }
  return *(tokensDataPtr + pos);
};
void TokensInputStream::skip() {
  std::vector<Token *> tokensData = tokens.getTokens();
  if (hasReadable()) {
    pos++;
  } else if (tokensData.size() > pos) {
    pos = tokensData.size();
  }
};
void TokensInputStream::skip(const size_t &skipSize_) {
  std::vector<Token *> tokensData = tokens.getTokens();
  size_t skipSize = skipSize_;
  size_t readableSize = readable();
  if (readableSize < skipSize) {
    skipSize = readableSize;
  }
  if (skipSize > 0) {
    pos += skipSize;
  } else if (tokensData.size() > pos) {
    pos = tokensData.size();
  }
};
void TokensInputStream::markCurrent() { mark = pos; };
void TokensInputStream::markAt(const size_t &markPos_) {
  size_t tokensDataSize = tokens.getTokenCount();
  if (markPos_ >= tokensDataSize) {
    mark = tokensDataSize - 1;
  } else {
    mark = markPos_;
  }
};
void TokensInputStream::resetMark() { mark = 0; };
void TokensInputStream::rewind() { pos = 0; };
void TokensInputStream::rewind(const size_t &rewindSize_) {
  if (pos >= rewindSize_) {
    pos -= rewindSize_;
  } else {
    pos = 0;
  }
};
void TokensInputStream::rewindToMark() { pos = mark; };
bool TokensInputStream::hasReadable() const {
  const size_t tokensDataSize = tokens.getTokenCount();
  return tokensDataSize > pos;
};
int64_t TokensInputStream::readable() const {
  const size_t tokensDataSize = tokens.getTokenCount();
  return tokensDataSize - (int64_t)(pos);
};
size_t TokensInputStream::size() const { return tokens.getTokenCount(); };
TokenTypeEnum TokensInputStream::tailTokenType() { return tailTokenType(0ul); };
TokenTypeEnum TokensInputStream::tailTokenType(const size_t &backOffset_) {
  Token *tailToken = tail(backOffset_);
  if (tailToken == nullptr) {
    return TokenTypeEnum::unknown;
  }
  return tailToken->getTokenType();
};
std::string TokensInputStream::toStringPrintTokens() {
  return toStringPrintTokens(false);
};
std::string TokensInputStream::toStringPrintTokens(const bool &isVerbose_) {
  std::vector<Token *> tokensData = tokens.getTokens();
  Token **tokensDataPtr = tokensData.data();
  size_t tokensDataSize = tokens.getTokenCount();
  if (tokensDataSize == 0) {
    return "[]\n";
  }
  std::string printString;
  const size_t &sqBrcBufSize = 4;
  const size_t &tokTypStrBufSize = 100;
  const size_t &tokSepBufSize = 10;
  const size_t &locBufSize = 40;
  const size_t &quoteDelimiterSize = 2;
  size_t printStringU8Size = sqBrcBufSize;
  // reserve buffer
  printStringU8Size += (tokTypStrBufSize + tokSepBufSize) * tokensDataSize;
  for (size_t i = 0; i < tokensDataSize; i++) {
    printStringU8Size +=
        ((*(tokensDataPtr + i))->getTokenLenU8() + quoteDelimiterSize);
  }
  if (isVerbose_) {
    printStringU8Size += locBufSize * tokensDataSize;
  }
  printString.reserve(printStringU8Size);
  // formatting
  printString.append("[\n");
  for (size_t i = 0; i < tokensDataSize; i++) {
    TokenTypeEnum tokenType = (*(tokensDataPtr + i))->getTokenType();
    printString.append("  ");
    printString.append((*(tokensDataPtr + i))->getTokenTypeString());
    if (!TokenType::isSymbolCharacterToken(tokenType)) {
      printString.append(": ");
      if (tokenType == TokenTypeEnum::coString ||
          tokenType == TokenTypeEnum::coSpace ||
          tokenType == TokenTypeEnum::ltString) {
        printString.append("\"");
      } else if (tokenType == TokenTypeEnum::ltSingleCharacter ||
                 (static_cast<uint32_t>(
                      TokenTypeEnum::ltEscapeSequenceNullChar) <=
                      uint32_t(tokenType) &&
                  uint32_t(tokenType) <
                      static_cast<uint32_t>(
                          TokenTypeEnum::ltStringLineBreak))) {
        printString.append("'");
      } else if (tokenType == TokenTypeEnum::ltRawString) {
        printString.append("`");
      }
      if (!TokenType::isLineBreak(tokenType)) {
        printString.append((*(tokensDataPtr + i))->getTokenU8());
      }
      if (tokenType == TokenTypeEnum::coString ||
          tokenType == TokenTypeEnum::coSpace ||
          tokenType == TokenTypeEnum::ltString) {
        printString.append("\"");
      } else if (tokenType == TokenTypeEnum::ltSingleCharacter ||
                 (static_cast<uint32_t>(
                      TokenTypeEnum::ltEscapeSequenceNullChar) <=
                      uint32_t(tokenType) &&
                  uint32_t(tokenType) <
                      static_cast<uint32_t>(
                          TokenTypeEnum::ltStringLineBreak))) {
        printString.append("'");
      } else if (tokenType == TokenTypeEnum::ltRawString) {
        printString.append("`");
      }
      printString.append(" ");
    }
    if (isVerbose_) {
      Location loc = (*(tokensDataPtr + i))->getLocation();
      printString.append(", location::[");
      printString.append(std::to_string(loc.getLine()));
      printString.append(",");
      printString.append(std::to_string(loc.getColumn()));
      printString.append("],\n");
    } else {
      printString.append(",\n");
    }
  }
  printString.append("]\n");
  printString.shrink_to_fit();
  return printString;
};
void TokensInputStream::printTokens() { return printTokens(false); };
void TokensInputStream::printTokens(const bool &isVerbose_) {
  std::cout << toStringPrintTokens(isVerbose_);
};
