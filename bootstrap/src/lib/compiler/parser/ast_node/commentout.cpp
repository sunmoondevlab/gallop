#include "compiler/parser/ast_node/commentout.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeCommentOut::AstNodeCommentOut(const AstNodeTypeEnum nodeType_,
                                     const Location location_)
    : location(location_), blockBeginLocation(location_),
      blockEndLocation(Location(0, 0)), astNodeType(nodeType_), parent(nullptr),
      child(nullptr), next(nullptr) {};
AstNodeCommentOut::AstNodeCommentOut(const AstNodeCommentOut &rhs)
    : location(rhs.location), blockBeginLocation(rhs.blockBeginLocation),
      blockEndLocation(rhs.blockEndLocation), astNodeType(rhs.astNodeType),
      parent(rhs.parent), child(rhs.child), next(rhs.next) {};

AstNodeCommentOut &AstNodeCommentOut::operator=(const AstNodeCommentOut &rhs) {
  location = rhs.location;
  blockBeginLocation = rhs.blockBeginLocation;
  blockEndLocation = rhs.blockEndLocation;
  astNodeType = rhs.astNodeType;
  parent = rhs.parent;
  child = rhs.child;
  next = rhs.next;
  return *this;
};
Location AstNodeCommentOut::getLocation() { return location; };
std::string AstNodeCommentOut::getAstNodeTypeString() {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeCommentOut::getAstNodeType() { return astNodeType; };

void AstNodeCommentOut::printAstNode(const size_t depth, const bool isVerbose) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";
  indentDepth(depth);
  llvm::outs() << "}\n";
};
bool AstNodeCommentOut::hasParent() { return parent != nullptr; };
bool AstNodeCommentOut::hasNext() { return next != nullptr; };
bool AstNodeCommentOut::hasChild() { return child != nullptr; };

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
AstNode *AstNodeCommentOut::nextNode() { return next; };
AstNode *AstNodeCommentOut::childNode() { return child; };

AstNode *AstNodeCommentOut::putParentNode(AstNode *const node) {
  parent = node;
  return this;
};
AstNode *AstNodeCommentOut::putChildNode(AstNode *const node) {
  child = node;
  return child;
};
AstNode *AstNodeCommentOut::putNextNode(AstNode *const node) {
  next = node;
  return next;
};

void AstNodeCommentOut::setBegenEndLocation(const Location location_,
                                            const bool endFlag_) {
  if (endFlag_) {
    blockEndLocation = location_;
  } else {
    blockBeginLocation = location_;
  }
};
