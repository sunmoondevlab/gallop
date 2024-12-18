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
void Option::setWithCommentOutAll(const bool withCommentOutAll_) {
  withCommentOutAll = withCommentOutAll_;
};
void Option::setWithCommentOutForDoc(const bool withCommentOutForDoc_) {
  withCommentOutForDoc = withCommentOutForDoc_;
};
