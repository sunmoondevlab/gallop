// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/token.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"
#include "char_set/string/utf32_string.hpp"
#include "io/stream/utf32_input_stream.hpp"

using namespace gallop::Compiler;
using namespace gallop::CharSet;
using namespace gallop::IO::Stream;

Token::Token()
    : location(Location(0, 0, 0)), tokenType(TokenTypeEnum::unknown),
      token(U""), tokenSize(0), preParseValue(PreParseValue()) {};
Token::Token(const Location &location_, const TokenTypeEnum &tokenType_,
             const std::u32string &token_)
    : location(location_), tokenType(tokenType_), token(token_),
      tokenSize(token_.size()), preParseValue(PreParseValue()) {};
Token::Token(const Location &location_, const TokenTypeEnum &tokenType_,
             const std::u32string &token_, const int32_t &escapeCharCode_)
    : location(location_), tokenType(tokenType_), token(token_),
      tokenSize(token_.size()),
      preParseValue(PreParseValue(escapeCharCode_)) {};
Token::Token(const Token &rhs)
    : location(rhs.location), tokenType(rhs.tokenType), token(rhs.token),
      tokenSize(rhs.tokenSize), preParseValue(rhs.preParseValue) {};
Token &Token::operator=(const Token &rhs) {
  location = rhs.location;
  tokenType = rhs.tokenType;
  token = rhs.token;
  tokenSize = rhs.tokenSize;
  preParseValue = rhs.preParseValue;
  return *this;
};

Location Token::getLocation() const { return location; };
TokenTypeEnum Token::getTokenType() const { return tokenType; };
std::string Token::getTokenTypeString() const {
  return TokenType::getString(tokenType);
};
std::u32string Token::getToken() const { return token; };
size_t Token::getTokenLen() const { return tokenSize; };
std::string Token::getTokenU8() const {
  return String::Utf32::toU8String(token);
};
size_t Token::getTokenLenU8() const { return getTokenU8().size(); };

size_t Token::countLineBreakInToken(size_t &column_) {
  Utf32InputStream uis(token);
  size_t newLineCount = 0;
  while (uis.hasReadable()) {
    int32_t charCode = uis.read();
    if (CharCode::Utf32::isCarriageReturn(charCode)) {
      if (CharCode::Utf32::isLineFeed(uis.current())) {
        uis.skip();
      }
      newLineCount++;
      column_ = 0;
    } else if (CharCode::Utf32::isLineFeed(charCode)) {
      newLineCount++;
      column_ = 0;
    }
    column_++;
  }
  return newLineCount;
};
int32_t *Token::preParseEscapeUtf32CharCode() {
  return preParseValue.escapeUtf32CharCode();
};
