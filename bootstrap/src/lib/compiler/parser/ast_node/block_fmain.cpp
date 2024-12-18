#include "compiler/parser/ast_node/block_fmain.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeBlockFmain::AstNodeBlockFmain(const Location location_)
    : location(location_), blockBeginLocation(Location(0, 0)),
      blockEndLocation(Location(0, 0)),
      astNodeType(AstNodeTypeEnum::blockFmain), parent(nullptr), child(nullptr),
      next(nullptr) {};
AstNodeBlockFmain::AstNodeBlockFmain(const AstNodeBlockFmain &rhs)
    : location(rhs.location), blockBeginLocation(rhs.blockBeginLocation),
      blockEndLocation(rhs.blockEndLocation), astNodeType(rhs.astNodeType),
      parent(rhs.parent), child(rhs.child), next(rhs.next) {};

AstNodeBlockFmain &AstNodeBlockFmain::operator=(const AstNodeBlockFmain &rhs) {
  location = rhs.location;
  blockBeginLocation = rhs.blockBeginLocation;
  blockEndLocation = rhs.blockEndLocation;
  astNodeType = rhs.astNodeType;
  parent = rhs.parent;
  child = rhs.child;
  next = rhs.next;
  return *this;
};
Location AstNodeBlockFmain::getLocation() const { return location; };
std::string AstNodeBlockFmain::getAstNodeTypeString() const {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeBlockFmain::getAstNodeType() const {
  return astNodeType;
};

void AstNodeBlockFmain::printAstNode(const size_t depth,
                                     const bool isVerbose_) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";
  indentDepth(depth);
  llvm::outs() << "}\n";
};
bool AstNodeBlockFmain::hasParent() const { return parent != nullptr; };
bool AstNodeBlockFmain::hasNext() const { return next != nullptr; };
bool AstNodeBlockFmain::hasChild() const { return child != nullptr; };

AstNode *AstNodeBlockFmain::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeBlockFmain::moduleNode() {
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
AstNode *AstNodeBlockFmain::parentNode() { return parent; };
AstNode *AstNodeBlockFmain::nextNode() { return next; };
AstNode *AstNodeBlockFmain::childNode() { return child; };

AstNode *AstNodeBlockFmain::putParentNode(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeBlockFmain::putChildNode(AstNode *const node_) {
  child = node_;
  return child;
};
AstNode *AstNodeBlockFmain::putNextNode(AstNode *const node_) {
  next = node_;
  return next;
};

void AstNodeBlockFmain::setBegenEndLocation(const Location location_,
                                            const bool endFlag_) {
  if (endFlag_) {
    blockEndLocation = location_;
  } else {
    blockBeginLocation = location_;
  }
};
