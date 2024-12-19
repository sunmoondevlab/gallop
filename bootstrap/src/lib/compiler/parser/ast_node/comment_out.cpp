#include "compiler/parser/ast_node/comment_out.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeCommentOut::AstNodeCommentOut(const AstNodeTypeEnum nodeType_,
                                     const Location location_)
    : location(location_), blockBeginLocation(Location(0, 0)),
      blockEndLocation(Location(0, 0)), nodeType(nodeType_), parent(nullptr),
      prev(nullptr), next(nullptr), child(nullptr) {};
AstNodeCommentOut::AstNodeCommentOut(const AstNodeCommentOut &rhs)
    : location(rhs.location), blockBeginLocation(rhs.blockBeginLocation),
      blockEndLocation(rhs.blockEndLocation), nodeType(rhs.nodeType),
      parent(rhs.parent), prev(rhs.prev), next(rhs.next), child(rhs.child) {};

AstNodeCommentOut &AstNodeCommentOut::operator=(const AstNodeCommentOut &rhs) {
  location = rhs.location;
  blockBeginLocation = rhs.blockBeginLocation;
  blockEndLocation = rhs.blockEndLocation;
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  prev = rhs.prev;
  next = rhs.next;
  child = rhs.child;
  return *this;
};
Location AstNodeCommentOut::getLocation() const { return location; };
std::string AstNodeCommentOut::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeCommentOut::getAstNodeType() const { return nodeType; };

void AstNodeCommentOut::printNode(const size_t depth, const bool isVerbose_) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";
  indentDepth(depth);
  llvm::outs() << "}\n";
};
bool AstNodeCommentOut::hasParent() const { return parent != nullptr; };
bool AstNodeCommentOut::hasPrev() const { return prev != nullptr; };
bool AstNodeCommentOut::hasNext() const { return next != nullptr; };
bool AstNodeCommentOut::hasChild() const { return child != nullptr; };

AstNode *AstNodeCommentOut::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeCommentOut::moduleNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
    AstNodeTypeEnum nodeType = node->getAstNodeType();
    if ((uint32_t(nodeType) >> 24) == 2) {
      break;
    }
  }
  return node;
};
AstNode *AstNodeCommentOut::parentNode() { return parent; };
AstNode *AstNodeCommentOut::prevNode() { return next; };
AstNode *AstNodeCommentOut::nextNode() { return next; };
AstNode *AstNodeCommentOut::childNode() { return child; };

AstNode *AstNodeCommentOut::putParentNode(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeCommentOut::putPrevNode(AstNode *const node_) {
  prev = node_;
  return next;
};
AstNode *AstNodeCommentOut::putNextNode(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeCommentOut::putChildNode(AstNode *const node_) {
  child = node_;
  return child;
};

void AstNodeCommentOut::setCommentOutString(
    const std::string commentOutString_) {
  commentOutString = commentOutString_;
};

void AstNodeCommentOut::setBegenEndLocation(const Location beginLocation_,
                                            const Location endLocation_) {
  blockEndLocation = beginLocation_;
  blockBeginLocation = endLocation_;
};
