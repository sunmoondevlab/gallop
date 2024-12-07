// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/ast_node/char_code_literal.hpp"
#include "compiler/parser/ast_node/module.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeCharCodeLiteral::AstNodeCharCodeLiteral(const Location beginLocation_,
                                               const Location endLocation_,
                                               const uint32_t value_,
                                               const std::string utf8Value_)
    : beginLocation(beginLocation_), endLocation(endLocation_),
      nodeType(AstNodeTypeEnum::charCodeLiteral), parent(nullptr),
      prev(nullptr), next(nullptr), child(nullptr), value(value_),
      utf8Value(utf8Value_) {};
AstNodeCharCodeLiteral::AstNodeCharCodeLiteral(
    const AstNodeCharCodeLiteral &rhs)
    : beginLocation(rhs.beginLocation), endLocation(rhs.endLocation),
      nodeType(rhs.nodeType), parent(rhs.parent), prev(rhs.prev),
      next(rhs.next), child(rhs.child), value(rhs.value),
      utf8Value(rhs.utf8Value) {};

AstNodeCharCodeLiteral &
AstNodeCharCodeLiteral::operator=(const AstNodeCharCodeLiteral &rhs) {
  beginLocation = rhs.beginLocation;
  endLocation = rhs.endLocation;
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  prev = rhs.prev;
  next = rhs.next;
  child = rhs.child;
  value = rhs.value;
  utf8Value = rhs.utf8Value;
  return *this;
};
Location AstNodeCharCodeLiteral::getLocation() const { return beginLocation; };
std::string AstNodeCharCodeLiteral::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeCharCodeLiteral::getAstNodeType() const {
  return nodeType;
};

void AstNodeCharCodeLiteral::printNode(const size_t depth_,
                                       const bool isVerbose_) {
  indentDepth(depth_, true);
  llvm::outs() << getAstNodeTypeString() << "\n";
  if (isVerbose_) {
    indentDepth(depth_ + 1);
    llvm::outs() << "beginLocation: [" << beginLocation.getLine() << ","
                 << beginLocation.getColumn() << "]\n";
    indentDepth(depth_ + 1);
    llvm::outs() << "endLocation: [" << endLocation.getLine() << ","
                 << endLocation.getColumn() << "]\n";
  }
  if (value != 0) {
    indentDepth(depth_ + 1);
    llvm::outs() << "value: '" << std::to_string(value) << "'\n";
    indentDepth(depth_ + 1);
    llvm::outs() << "utf8Value: \"" << utf8Value << "\"\n";
  }
};
llvm::Value *
AstNodeCharCodeLiteral::generateLlvmIr(IrGenContext *const context_) {
  llvm::IRBuilder<> *lBuilder = context_->getBuilder();
  llvm::Value *valueP = lBuilder->getInt32(value);
  return valueP;
};

bool AstNodeCharCodeLiteral::hasParent() const { return parent != nullptr; };
bool AstNodeCharCodeLiteral::hasPrev() const { return prev != nullptr; };
bool AstNodeCharCodeLiteral::hasNext() const { return next != nullptr; };
bool AstNodeCharCodeLiteral::hasChild() const { return child != nullptr; };

AstNode *AstNodeCharCodeLiteral::getRoot() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
  }
  return node;
};
AstNode *AstNodeCharCodeLiteral::getModule() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
    AstNodeTypeEnum nodeType = node->getAstNodeType();
    if (AstNodeType::isModule(nodeType)) {
      break;
    }
  }
  return node;
};
AstNode *AstNodeCharCodeLiteral::getParent() { return parent; };
AstNode *AstNodeCharCodeLiteral::getPrev() { return next; };
AstNode *AstNodeCharCodeLiteral::getNext() { return next; };
AstNode *AstNodeCharCodeLiteral::getChild() { return child; };

AstNode *AstNodeCharCodeLiteral::setParent(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeCharCodeLiteral::setPrev(AstNode *const node_) {
  prev = node_;
  return next;
};
AstNode *AstNodeCharCodeLiteral::setNext(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeCharCodeLiteral::setChild(AstNode *const node_) {
  if (!settableChild(node_)) {
    return this;
  }
  child = node_;
  return child;
};

bool AstNodeCharCodeLiteral::settableChild(AstNode *const node_) const {
  return false;
};