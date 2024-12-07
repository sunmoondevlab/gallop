// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/option.hpp"
using namespace gallop::Compiler::Parser;

Option::Option() : withCommentOutAll(false), withCommentOutForDoc(false) {};
Option::Option(const Option &rhs)
    : withCommentOutAll(rhs.withCommentOutAll),
      withCommentOutForDoc(rhs.withCommentOutForDoc) {};
Option &Option::operator=(const Option &rhs) {
  withCommentOutAll = rhs.withCommentOutAll;
  withCommentOutForDoc = rhs.withCommentOutForDoc;
  return *this;
};
bool Option::isWithCommentOutAll() const { return withCommentOutAll; };
bool Option::isWithCommentOutForDoc() const { return withCommentOutForDoc; };
void Option::setWithCommentOutAll() { withCommentOutAll = true; };
void Option::setWithCommentOutForDoc() { withCommentOutForDoc = true; };
