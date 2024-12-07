#include "compiler/parser/ast_node/block_fmain.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeBlockFmain::AstNodeBlockFmain(const Location location_)
    : location(location_), blockBeginLocation(Location(0, 0)),
      blockEndLocation(Location(0, 0)), nodeType(AstNodeTypeEnum::blockFmain),
      parent(nullptr), prev(nullptr), next(nullptr), child(nullptr) {};
AstNodeBlockFmain::AstNodeBlockFmain(const AstNodeBlockFmain &rhs)
    : location(rhs.location), blockBeginLocation(rhs.blockBeginLocation),
      blockEndLocation(rhs.blockEndLocation), nodeType(rhs.nodeType),
      parent(rhs.parent), prev(rhs.prev), next(rhs.next), child(rhs.child) {};

AstNodeBlockFmain &AstNodeBlockFmain::operator=(const AstNodeBlockFmain &rhs) {
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
Location AstNodeBlockFmain::getLocation() const { return location; };
std::string AstNodeBlockFmain::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeBlockFmain::getAstNodeType() const { return nodeType; };

void AstNodeBlockFmain::printNode(const size_t depth, const bool isVerbose_) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";
  indentDepth(depth);
  llvm::outs() << "}\n";
};
void AstNodeBlockFmain::generateLlvmIr(IrGenContext *const context_) {};

bool AstNodeBlockFmain::hasParent() const { return parent != nullptr; };
bool AstNodeBlockFmain::hasPrev() const { return prev != nullptr; };
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
AstNode *AstNodeBlockFmain::prevNode() { return prev; };
AstNode *AstNodeBlockFmain::nextNode() { return next; };
AstNode *AstNodeBlockFmain::childNode() { return child; };

AstNode *AstNodeBlockFmain::putParentNode(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeBlockFmain::putPrevNode(AstNode *const node_) {
  prev = node_;
  return prev;
};
AstNode *AstNodeBlockFmain::putNextNode(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeBlockFmain::putChildNode(AstNode *const node_) {
  child = node_;
  return child;
};

void AstNodeBlockFmain::setBegenEndLocation(const Location location_,
                                            const bool endFlag_) {
  if (endFlag_) {
    blockEndLocation = location_;
  } else {
    blockBeginLocation = location_;
  }
};
