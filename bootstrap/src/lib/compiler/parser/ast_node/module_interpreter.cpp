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
    : astNodeType(rhs.astNodeType), next(rhs.next), child(rhs.child),
      moduleName(rhs.moduleName) {};

AstNodeModuleInterpreter &
AstNodeModuleInterpreter::operator=(const AstNodeModuleInterpreter &rhs) {
  astNodeType = rhs.astNodeType;
  next = rhs.next;
  child = rhs.child;
  moduleName = rhs.moduleName;
  return *this;
};
Location AstNodeModuleInterpreter::getLocation() { return Location(0, 0); };
std::string AstNodeModuleInterpreter::getAstNodeTypeString() {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeModuleInterpreter::getAstNodeType() {
  return astNodeType;
};

void AstNodeModuleInterpreter::printAstNode(const size_t depth,
                                            const bool isVerbose) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";

  indentDepth(depth + 1);
  llvm::outs() << "module name: " << moduleName << ",\n";

  indentDepth(depth);
  llvm::outs() << "}";
  if (next != nullptr) {
    llvm::outs() << ",\n";
    next->printAstNode(depth, isVerbose);
  } else {
    llvm::outs() << "\n";
  }
};

bool AstNodeModuleInterpreter::hasParent() { return false; };
bool AstNodeModuleInterpreter::hasNext() { return next != nullptr; };
bool AstNodeModuleInterpreter::hasChild() { return child != nullptr; };

AstNode *AstNodeModuleInterpreter::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeModuleInterpreter::parentNode() { return nullptr; };
AstNode *AstNodeModuleInterpreter::nextNode() { return next; };
AstNode *AstNodeModuleInterpreter::childNode() { return child; };

AstNode *AstNodeModuleInterpreter::putParentNode(AstNode *const node) {
  return this;
};
AstNode *AstNodeModuleInterpreter::putChildNode(AstNode *const node) {
  child = node;
  node->putParentNode(this);
  return child;
};
AstNode *AstNodeModuleInterpreter::putNextNode(AstNode *const node) {
  next = node;
  (dynamic_cast<AstNodeModuleInterpreter *>(node))->putPrevNode(this);
  return next;
};
AstNode *AstNodeModuleInterpreter::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};
bool AstNodeModuleInterpreter::hasPrev() { return prev != nullptr; };
AstNode *AstNodeModuleInterpreter::prevNode() { return prev; };
AstNode *AstNodeModuleInterpreter::putPrevNode(AstNode *const node) {
  prev = node;
  return this;
};
