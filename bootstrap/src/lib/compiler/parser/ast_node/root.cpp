#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeRoot::AstNodeRoot(const AstNodeTypeEnum nodeType_)
    : nodeType(nodeType_), child(nullptr), moduleIdx(0) {};
AstNodeRoot::AstNodeRoot(const AstNodeRoot &rhs)
    : nodeType(rhs.nodeType), child(rhs.child), moduleIdx(rhs.moduleIdx) {};
AstNodeRoot &AstNodeRoot::operator=(const AstNodeRoot &rhs) {
  nodeType = rhs.nodeType;
  child = rhs.child;
  moduleIdx = rhs.moduleIdx;
  return *this;
};
Location AstNodeRoot::getLocation() const { return Location(0, 0); };
std::string AstNodeRoot::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeRoot::getAstNodeType() const { return nodeType; };

void AstNodeRoot::printNode(const size_t depth_, const bool isVerbose_) {
  indentDepth(depth_, true);
  llvm::outs() << "ast::" << getAstNodeTypeString() << "\n";
};
void AstNodeRoot::generateLlvmIr(IrGenContext *const context_) { /*nop */ };

bool AstNodeRoot::hasParent() const { return false; };
bool AstNodeRoot::hasPrev() const { return false; };
bool AstNodeRoot::hasNext() const { return false; };
bool AstNodeRoot::hasChild() const { return child != nullptr; };

AstNode *AstNodeRoot::rootNode() { return this; };
AstNode *AstNodeRoot::moduleNode() {
  if (nodeType == AstNodeTypeEnum::rootFile) {
    AstNode *moduleNode = child;
    if (moduleNode == nullptr) {
      return moduleNode;
    }
    for (size_t i = 0; i < moduleIdx && moduleNode->hasNext(); i++) {
      moduleNode = moduleNode->nextNode();
    }
    return moduleNode;
  } else {
    return child;
  }
};
AstNode *AstNodeRoot::parentNode() { return nullptr; };
AstNode *AstNodeRoot::prevNode() { return nullptr; };
AstNode *AstNodeRoot::nextNode() { return nullptr; };
AstNode *AstNodeRoot::childNode() { return child; };

AstNode *AstNodeRoot::putParentNode(AstNode *const node_) { return this; };
AstNode *AstNodeRoot::putPrevNode(AstNode *const node_) { return this; };
AstNode *AstNodeRoot::putNextNode(AstNode *const node_) { return this; };
AstNode *AstNodeRoot::putChildNode(AstNode *const node_) {
  if (child != nullptr && nodeType == AstNodeTypeEnum::rootFile) {
    child->putNextNode(node_);
  } else if (child == nullptr) {
    child = node_;
  } else {
    throw "can not set multiple child on " + AstNodeType::getString(nodeType);
  }
  node_->putParentNode(this);
  return child;
};
