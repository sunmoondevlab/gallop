// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/option/parser.hpp"

using namespace gallop::Compiler::Option;

Parser::Parser() : withCommentOutAll(false), withCommentOutForDoc(false) {};
Parser::Parser(const Parser &rhs)
    : withCommentOutAll(rhs.withCommentOutAll),
      withCommentOutForDoc(rhs.withCommentOutForDoc) {};
Parser &Parser::operator=(const Parser &rhs) {
  withCommentOutAll = rhs.withCommentOutAll;
  withCommentOutForDoc = rhs.withCommentOutForDoc;
  return *this;
};
bool Parser::isWithCommentOutAll() const { return withCommentOutAll; };
bool Parser::isWithCommentOutForDoc() const { return withCommentOutForDoc; };
void Parser::setWithCommentOutAll() { withCommentOutAll = true; };
void Parser::setWithCommentOutForDoc() { withCommentOutForDoc = true; };
