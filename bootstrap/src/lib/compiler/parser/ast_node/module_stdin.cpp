#include "compiler/parser/ast_node/module_stdin.hpp"
#include "compiler/parser/ast_node/block_fmain.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeModuleStdin::AstNodeModuleStdin()
    : astNodeType(AstNodeTypeEnum::moduleStdin), next(nullptr), child(nullptr),
      moduleName("moduleFromStdin") {};
AstNodeModuleStdin::AstNodeModuleStdin(const AstNodeModuleStdin &rhs)
    : astNodeType(rhs.astNodeType), next(rhs.next), child(rhs.child),
      moduleName(rhs.moduleName) {};

AstNodeModuleStdin &
AstNodeModuleStdin::operator=(const AstNodeModuleStdin &rhs) {
  astNodeType = rhs.astNodeType;
  next = rhs.next;
  child = rhs.child;
  moduleName = rhs.moduleName;
  return *this;
};
Location AstNodeModuleStdin::getLocation() { return Location(0, 0); };
std::string AstNodeModuleStdin::getAstNodeTypeString() {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeModuleStdin::getAstNodeType() { return astNodeType; };

void AstNodeModuleStdin::printAstNode(const size_t depth,
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

bool AstNodeModuleStdin::hasParent() { return false; };
bool AstNodeModuleStdin::hasNext() { return next != nullptr; };
bool AstNodeModuleStdin::hasChild() { return child != nullptr; };

AstNode *AstNodeModuleStdin::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeModuleStdin::moduleNode() { return this; };
AstNode *AstNodeModuleStdin::parentNode() { return nullptr; };
AstNode *AstNodeModuleStdin::nextNode() { return next; };
AstNode *AstNodeModuleStdin::childNode() { return child; };

AstNode *AstNodeModuleStdin::putParentNode(AstNode *const node) {
  return this;
};
AstNode *AstNodeModuleStdin::putChildNode(AstNode *const node) {
  child = node;
  node->putParentNode(this);
  return child;
};
AstNode *AstNodeModuleStdin::putNextNode(AstNode *const node) {
  next = node;
  (dynamic_cast<AstNodeModuleStdin *>(node))->putPrevNode(this);
  return next;
};
AstNode *AstNodeModuleStdin::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};
bool AstNodeModuleStdin::hasPrev() { return prev != nullptr; };
AstNode *AstNodeModuleStdin::prevNode() { return prev; };
AstNode *AstNodeModuleStdin::putPrevNode(AstNode *const node) {
  prev = node;
  return this;
};
