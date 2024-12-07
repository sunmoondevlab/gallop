// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/ast_node/control_block.hpp"
#include "compiler/parser/ast_node/declare_fmain.hpp"
#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeControlBlock::AstNodeControlBlock(const Location beginLocation_,

                                         AstNodeTypeEnum blockNodeType_)
    : beginLocation(beginLocation_), endLocation(beginLocation_),
      nodeType(AstNodeTypeEnum::controlBlock), blockNodeType(blockNodeType_),
      parent(nullptr), prev(nullptr), next(nullptr), child(nullptr),
      declaredReturnVal(false) {};
AstNodeControlBlock::AstNodeControlBlock(const AstNodeControlBlock &rhs)
    : beginLocation(rhs.beginLocation), endLocation(rhs.endLocation),
      nodeType(rhs.nodeType), blockNodeType(rhs.blockNodeType),
      parent(rhs.parent), prev(rhs.prev), next(rhs.next), child(rhs.child),
      declaredReturnVal(rhs.declaredReturnVal) {};

AstNodeControlBlock &
AstNodeControlBlock::operator=(const AstNodeControlBlock &rhs) {
  beginLocation = rhs.beginLocation;
  endLocation = rhs.endLocation;
  nodeType = rhs.nodeType;
  blockNodeType = rhs.blockNodeType;
  parent = rhs.parent;
  prev = rhs.prev;
  next = rhs.next;
  child = rhs.child;
  declaredReturnVal = rhs.declaredReturnVal;
  return *this;
};
Location AstNodeControlBlock::getLocation() const { return beginLocation; };
Location AstNodeControlBlock::getBeginLocation() const {
  return beginLocation;
};
Location AstNodeControlBlock::getEndLocation() const { return endLocation; };
std::string AstNodeControlBlock::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeControlBlock::getAstNodeType() const {
  return nodeType;
};
AstNodeTypeEnum AstNodeControlBlock::getBlockNodeType() const {
  return blockNodeType;
};

void AstNodeControlBlock::printNode(const size_t depth_,
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
};
llvm::Value *AstNodeControlBlock::generateLlvmIr(IrGenContext *const context_) {
  llvm::IRBuilder<> *lBuilder = context_->getBuilder();
  if (hasChild()) {
    AstNode *child = getChild();
    child->generateLlvmIr(context_);
    while (child->hasNext()) {
      child = child->getNext();
      child->generateLlvmIr(context_);
    }
  }
  if (parent->getAstNodeType() == AstNodeTypeEnum::declareFmain &&
      !hasReturnVal()) {
    lBuilder->CreateRet(lBuilder->getInt32(0));
  }
  return nullptr;
};

bool AstNodeControlBlock::hasParent() const { return parent != nullptr; };
bool AstNodeControlBlock::hasPrev() const { return prev != nullptr; };
bool AstNodeControlBlock::hasNext() const { return next != nullptr; };
bool AstNodeControlBlock::hasChild() const { return child != nullptr; };

AstNode *AstNodeControlBlock::getRoot() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
  }
  return node;
};
AstNode *AstNodeControlBlock::getModule() {
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
AstNode *AstNodeControlBlock::getParent() { return parent; };
AstNode *AstNodeControlBlock::getPrev() { return prev; };
AstNode *AstNodeControlBlock::getNext() { return next; };
AstNode *AstNodeControlBlock::getChild() { return child; };

AstNode *AstNodeControlBlock::setParent(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeControlBlock::setPrev(AstNode *const node_) {
  prev = node_;
  return prev;
};
AstNode *AstNodeControlBlock::setNext(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeControlBlock::setChild(AstNode *const node_) {
  if (!settableChild(node_)) {
    llvm::outs() << "can not set node type " + node_->getAstNodeTypeString() +
                        " on " + getAstNodeTypeString();
    throw "";
  }
  child = node_;
  return child;
};

void AstNodeControlBlock::setEndLocation(const Location endLocation_) {
  endLocation = endLocation_;
};

bool AstNodeControlBlock::hasReturnVal() {
  bool hasReturnVal = hasReturnVal;

  AstNode *node = this;
  if (node->hasChild()) {
    node = node->getChild();
    while (node != this) {
      while (node->hasChild()) {
        node = node->getChild();
        if (node->getAstNodeType() == AstNodeTypeEnum::controlBlock) {
          hasReturnVal =
              hasReturnVal || ((AstNodeControlBlock *)node)->hasReturnVal();
        }
      }
      if (node->hasNext()) {
        node = node->getNext();
        if (node->getAstNodeType() == AstNodeTypeEnum::controlBlock) {
          hasReturnVal =
              hasReturnVal || ((AstNodeControlBlock *)node)->hasReturnVal();
        }
        continue;
      }
      while (node != this && !node->hasNext()) {
        node = node->getParent();
      }
      if (node->hasNext()) {
        node = node->getNext();
      }
    }
  }
  return hasReturnVal;
};

bool AstNodeControlBlock::isInFmain() {
  AstNode *node = this;
  AstNodeTypeEnum nodeType = node->getAstNodeType();
  while (node->hasParent()) {
    node = node->getParent();
    nodeType = node->getAstNodeType();
    if (nodeType == AstNodeTypeEnum::declareFmain ||
        nodeType == AstNodeTypeEnum::declareFn) {
      break;
    }
  }
  if (nodeType == AstNodeTypeEnum::declareFmain) {
    return true;
  } else {
    return false;
  }
};

bool AstNodeControlBlock::settableChild(AstNode *const node_) const {
  AstNodeTypeEnum childNodeType = node_->getAstNodeType();
  return AstNodeType::isLeafType(childNodeType) ||
         childNodeType == AstNodeTypeEnum::controlBlock;
};