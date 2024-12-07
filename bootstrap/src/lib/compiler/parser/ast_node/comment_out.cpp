// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/ast_node/comment_out.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeCommentOut::AstNodeCommentOut(const AstNodeTypeEnum nodeType_,
                                     const Location location_,
                                     const std::string body_)
    : location(location_), beginLocation(Location(0, 0)),
      endLocation(Location(0, 0)), nodeType(nodeType_), parent(nullptr),
      prev(nullptr), next(nullptr), child(nullptr), body(body_) {};
AstNodeCommentOut::AstNodeCommentOut(const AstNodeTypeEnum nodeType_,
                                     const Location beginLocation_,
                                     const Location endLocation_,
                                     const std::string body_)
    : location(beginLocation_), beginLocation(beginLocation_),
      endLocation(endLocation_), nodeType(nodeType_), parent(nullptr),
      prev(nullptr), next(nullptr), child(nullptr), body(body_) {};
AstNodeCommentOut::AstNodeCommentOut(const AstNodeCommentOut &rhs)
    : location(rhs.location), beginLocation(rhs.beginLocation),
      endLocation(rhs.endLocation), nodeType(rhs.nodeType), parent(rhs.parent),
      prev(rhs.prev), next(rhs.next), child(rhs.child), body(rhs.body) {};

AstNodeCommentOut &AstNodeCommentOut::operator=(const AstNodeCommentOut &rhs) {
  location = rhs.location;
  beginLocation = rhs.beginLocation;
  endLocation = rhs.endLocation;
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  prev = rhs.prev;
  next = rhs.next;
  child = rhs.child;
  body = rhs.body;
  return *this;
};
Location AstNodeCommentOut::getLocation() const { return location; };
std::string AstNodeCommentOut::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeCommentOut::getAstNodeType() const { return nodeType; };

void AstNodeCommentOut::printNode(const size_t depth_, const bool isVerbose_) {
  indentDepth(depth_, true);
  llvm::outs() << getAstNodeTypeString() << "\n";
  if (isVerbose_) {
    if (nodeType == AstNodeTypeEnum::commentOutOneline ||
        nodeType == AstNodeTypeEnum::commentOutOnelineDoc) {
      indentDepth(depth_ + 1);
      llvm::outs() << "location: [" << location.getLine() << ","
                   << location.getColumn() << "]\n";
    } else {
      indentDepth(depth_ + 1);
      llvm::outs() << "beginLocation: [" << beginLocation.getLine() << ","
                   << beginLocation.getColumn() << "]\n";
      indentDepth(depth_ + 1);
      llvm::outs() << "endLocation: [" << endLocation.getLine() << ","
                   << endLocation.getColumn() << "]\n";
    }
  }
  if (body != "") {
    indentDepth(depth_ + 1);
    llvm::outs() << "body: " << body << "\n";
  }
};
llvm::Value *AstNodeCommentOut::generateLlvmIr(IrGenContext *const context_) {
  return nullptr;
};

bool AstNodeCommentOut::hasParent() const { return parent != nullptr; };
bool AstNodeCommentOut::hasPrev() const { return prev != nullptr; };
bool AstNodeCommentOut::hasNext() const { return next != nullptr; };
bool AstNodeCommentOut::hasChild() const { return child != nullptr; };

AstNode *AstNodeCommentOut::getRoot() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
  }
  return node;
};
AstNode *AstNodeCommentOut::getModule() {
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
AstNode *AstNodeCommentOut::getParent() { return parent; };
AstNode *AstNodeCommentOut::getPrev() { return next; };
AstNode *AstNodeCommentOut::getNext() { return next; };
AstNode *AstNodeCommentOut::getChild() { return child; };

AstNode *AstNodeCommentOut::setParent(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeCommentOut::setPrev(AstNode *const node_) {
  prev = node_;
  return next;
};
AstNode *AstNodeCommentOut::setNext(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeCommentOut::setChild(AstNode *const node_) {
  if (!settableChild(node_)) {
    return this;
  }
  child = node_;
  return child;
};

bool AstNodeCommentOut::settableChild(AstNode *const node_) const {
  return false;
};