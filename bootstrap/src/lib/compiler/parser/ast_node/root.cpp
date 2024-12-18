#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeRoot::AstNodeRoot(const AstNodeTypeEnum nodeType_)
    : astNodeType(nodeType_), child(nullptr), moduleIdx(0) {};
AstNodeRoot::AstNodeRoot(const AstNodeRoot &rhs)
    : astNodeType(rhs.astNodeType), child(rhs.child),
      moduleIdx(rhs.moduleIdx) {};
AstNodeRoot &AstNodeRoot::operator=(const AstNodeRoot &rhs) {
  astNodeType = rhs.astNodeType;
  child = rhs.child;
  moduleIdx = rhs.moduleIdx;
  return *this;
};
Location AstNodeRoot::getLocation() const { return Location(0, 0); };
std::string AstNodeRoot::getAstNodeTypeString() const {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeRoot::getAstNodeType() const { return astNodeType; };

void AstNodeRoot::printAstNode(const size_t depth_, const bool isVerbose_) {
  indentDepth(depth_);
  llvm::outs() << "ast::" << getAstNodeTypeString() << "{\n";
  if (child != nullptr) {
    child->printAstNode(depth_ + 1, isVerbose_);
  }
  indentDepth(depth_);
  llvm::outs() << "}\n";
};

bool AstNodeRoot::hasParent() const { return false; };
bool AstNodeRoot::hasNext() const { return false; };
bool AstNodeRoot::hasChild() const { return child != nullptr; };

AstNode *AstNodeRoot::rootNode() { return this; };
AstNode *AstNodeRoot::moduleNode() {
  if (astNodeType == AstNodeTypeEnum::rootFile) {
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
AstNode *AstNodeRoot::nextNode() { return nullptr; };
AstNode *AstNodeRoot::childNode() { return child; };

AstNode *AstNodeRoot::putParentNode(AstNode *const node_) { return this; };
AstNode *AstNodeRoot::putChildNode(AstNode *const node_) {
  if (child != nullptr && astNodeType == AstNodeTypeEnum::rootFile) {
    child->putNextNode(node_);
  } else if (child == nullptr) {
    child = node_;
  } else {
    throw "can not set multiple child on " +
        AstNodeType::getString(astNodeType);
  }
  node_->putParentNode(this);
  return child;
};
AstNode *AstNodeRoot::putNextNode(AstNode *const node_) { return this; };
