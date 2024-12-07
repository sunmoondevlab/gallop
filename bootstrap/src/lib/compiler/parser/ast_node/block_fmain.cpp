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
Location AstNodeBlockFmain::getLocation() { return location; };
std::string AstNodeBlockFmain::getAstNodeTypeString() {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeBlockFmain::getAstNodeType() { return astNodeType; };

void AstNodeBlockFmain::printAstNode(const size_t depth, const bool isVerbose) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";
  indentDepth(depth);
  llvm::outs() << "}\n";
};
bool AstNodeBlockFmain::hasParent() { return parent != nullptr; };
bool AstNodeBlockFmain::hasNext() { return next != nullptr; };
bool AstNodeBlockFmain::hasChild() { return child != nullptr; };

AstNode *AstNodeBlockFmain::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};

AstNode *AstNodeBlockFmain::parentNode() { return parent; };
AstNode *AstNodeBlockFmain::nextNode() { return next; };
AstNode *AstNodeBlockFmain::childNode() { return child; };

AstNode *AstNodeBlockFmain::putParentNode(AstNode *const node) {
  parent = node;
  return this;
};
AstNode *AstNodeBlockFmain::putChildNode(AstNode *const node) {
  child = node;
  return child;
};
AstNode *AstNodeBlockFmain::putNextNode(AstNode *const node) {
  next = node;
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
