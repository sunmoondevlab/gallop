#include "compiler/parser/ast_node/comment_out.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

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
      llvm::outs() << "beginLocation: [" << blockBeginLocation.getLine() << ","
                   << blockBeginLocation.getColumn() << "]\n";
      indentDepth(depth_ + 1);
      llvm::outs() << "endLocation: [" << blockEndLocation.getLine() << ","
                   << blockEndLocation.getColumn() << "]\n";
    }
  }
  if (body != "") {
    indentDepth(depth_ + 1);
    llvm::outs() << "body: " << body << "\n";
  }
};
void AstNodeCommentOut::generateLlvmIr(
    IrGenContext *const context_) { /*nop */ };

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

void AstNodeCommentOut::setBody(const std::string body_) { body = body_; };

void AstNodeCommentOut::setBegenEndLocation(const Location beginLocation_,
                                            const Location endLocation_) {
  blockBeginLocation = beginLocation_;
  blockEndLocation = endLocation_;
};
