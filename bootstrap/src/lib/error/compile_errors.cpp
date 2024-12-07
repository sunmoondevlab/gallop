// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "error/compile_errors.hpp"

using namespace gallop::Error;

TokenizeError::TokenizeError(const Token &token_,
                             const std::string &srcLineStr_)
    : token(const_cast<Token &>(token_)),
      srcLineStr(const_cast<std::string &>(srcLineStr_)) {
  initializeMessage();
};

void TokenizeError::initializeMessage() {
  Location location = token.getLocation();
  message += "Tokenize Error. " + token.getTokenTypeString() + ". at " +
             location.getString() + "\n";
  message += srcLineStr + "\n";
  size_t columnTokenBeginPos = location.getColumn();
  for (size_t pos = 1; pos < columnTokenBeginPos; pos++) {
    message.push_back(' ');
  }
  size_t tokenLen = token.getTokenLen();
  for (size_t pos = 0; pos < tokenLen; pos++) {
    // TODO When self-hosting, using character witdh.
    message.push_back(('^'));
  }
  message.push_back('\n');
};
