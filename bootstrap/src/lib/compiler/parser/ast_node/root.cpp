#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeRoot::AstNodeRoot(const AstNodeTypeEnum rootNodeType_)
    : astNodeType(rootNodeType_), child(nullptr) {};
AstNodeRoot::AstNodeRoot(const AstNodeRoot &rhs)
    : astNodeType(rhs.astNodeType), child(rhs.child) {};

AstNodeRoot &AstNodeRoot::operator=(const AstNodeRoot &rhs) {
  astNodeType = rhs.astNodeType;
  child = rhs.child;
  return *this;
};
Location AstNodeRoot::getLocation() { return Location(0, 0); };
std::string AstNodeRoot::getAstNodeTypeString() {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeRoot::getAstNodeType() { return astNodeType; };

void AstNodeRoot::printAstNode(const size_t depth, const bool isVerbose) {
  indentDepth(depth);
  llvm::outs() << "ast::" << getAstNodeTypeString() << "{\n";
  if (child != nullptr) {
    child->printAstNode(depth + 1, isVerbose);
  }
  indentDepth(depth);
  llvm::outs() << "}\n";
};

bool AstNodeRoot::hasParent() { return false; };
bool AstNodeRoot::hasNext() { return false; };
bool AstNodeRoot::hasChild() { return child != nullptr; };

AstNode *AstNodeRoot::rootNode() { return this; };
AstNode *AstNodeRoot::parentNode() { return nullptr; };
AstNode *AstNodeRoot::nextNode() { return nullptr; };
AstNode *AstNodeRoot::childNode() { return child; };

AstNode *AstNodeRoot::putParentNode(AstNode *const node) { return this; };
AstNode *AstNodeRoot::putChildNode(AstNode *const node) {
  if (child != nullptr && astNodeType == AstNodeTypeEnum::rootFile) {
    child->putNextNode(node);
  } else if (child == nullptr) {
    child = node;
  } else {
    throw "can not set multiple child on " +
        AstNodeType::getString(astNodeType);
  }
  node->putParentNode(this);
  return child;
};
AstNode *AstNodeRoot::putNextNode(AstNode *const node) { return this; };
