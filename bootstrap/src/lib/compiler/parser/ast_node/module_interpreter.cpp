#include "compiler/parser/ast_node/module_interpreter.hpp"
#include "compiler/parser/ast_node/block_fmain.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeModuleInterpreter::AstNodeModuleInterpreter()
    : astNodeType(AstNodeTypeEnum::moduleInterpreter), next(nullptr),
      child(nullptr), moduleName("moduleForInterpreter") {};
AstNodeModuleInterpreter::AstNodeModuleInterpreter(
    const AstNodeModuleInterpreter &rhs)
    : astNodeType(rhs.astNodeType), next(rhs.next), child(rhs.child) {};

AstNodeModuleInterpreter &
AstNodeModuleInterpreter::operator=(const AstNodeModuleInterpreter &rhs) {
  astNodeType = rhs.astNodeType;
  next = rhs.next;
  child = rhs.child;
  return *this;
};
Location AstNodeModuleInterpreter::getLocation() const {
  return Location(0, 0);
};
std::string AstNodeModuleInterpreter::getAstNodeTypeString() const {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeModuleInterpreter::getAstNodeType() const {
  return astNodeType;
};

void AstNodeModuleInterpreter::printAstNode(const size_t depth,
                                            const bool isVerbose_) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";

  indentDepth(depth + 1);
  llvm::outs() << "module name: " << moduleName << ",\n";

  indentDepth(depth);
  llvm::outs() << "}";
  if (next != nullptr) {
    llvm::outs() << ",\n";
    next->printAstNode(depth, isVerbose_);
  } else {
    llvm::outs() << "\n";
  }
};

bool AstNodeModuleInterpreter::hasParent() const { return false; };
bool AstNodeModuleInterpreter::hasNext() const { return next != nullptr; };
bool AstNodeModuleInterpreter::hasChild() const { return child != nullptr; };

AstNode *AstNodeModuleInterpreter::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeModuleInterpreter::moduleNode() { return this; };
AstNode *AstNodeModuleInterpreter::parentNode() { return nullptr; };
AstNode *AstNodeModuleInterpreter::nextNode() { return next; };
AstNode *AstNodeModuleInterpreter::childNode() { return child; };

AstNode *AstNodeModuleInterpreter::putParentNode(AstNode *const node_) {
  return this;
};
AstNode *AstNodeModuleInterpreter::putChildNode(AstNode *const node_) {
  child = node_;
  node_->putParentNode(this);
  return child;
};
AstNode *AstNodeModuleInterpreter::putNextNode(AstNode *const node_) {
  next = node_;
  (dynamic_cast<AstNodeModuleInterpreter *>(node_))->putPrevNode(this);
  return next;
};
AstNode *AstNodeModuleInterpreter::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};
bool AstNodeModuleInterpreter::hasPrev() const { return prev != nullptr; };
AstNode *AstNodeModuleInterpreter::prevNode() { return prev; };
AstNode *AstNodeModuleInterpreter::putPrevNode(AstNode *const node_) {
  prev = node_;
  return this;
};
