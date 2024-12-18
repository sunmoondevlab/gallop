#include "compiler/parser/ast_node/module_stdin.hpp"
#include "compiler/parser/ast_node/block_fmain.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeModuleStdin::AstNodeModuleStdin()
    : astNodeType(AstNodeTypeEnum::moduleStdin), next(nullptr), child(nullptr),
      defaultModName("moduleFromStdin"), moduleName("moduleFromStdin") {};
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
Location AstNodeModuleStdin::getLocation() const { return Location(0, 0); };
std::string AstNodeModuleStdin::getAstNodeTypeString() const {
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeModuleStdin::getAstNodeType() const {
  return astNodeType;
};

void AstNodeModuleStdin::printAstNode(const size_t depth,
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

bool AstNodeModuleStdin::hasParent() const { return false; };
bool AstNodeModuleStdin::hasNext() const { return next != nullptr; };
bool AstNodeModuleStdin::hasChild() const { return child != nullptr; };

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

AstNode *AstNodeModuleStdin::putParentNode(AstNode *const node_) {
  return this;
};
AstNode *AstNodeModuleStdin::putChildNode(AstNode *const node_) {
  child = node_;
  node_->putParentNode(this);
  return child;
};
AstNode *AstNodeModuleStdin::putNextNode(AstNode *const node_) {
  next = node_;
  (dynamic_cast<AstNodeModuleStdin *>(node_))->putPrevNode(this);
  return next;
};
AstNode *AstNodeModuleStdin::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};
bool AstNodeModuleStdin::hasPrev() const { return prev != nullptr; };
AstNode *AstNodeModuleStdin::prevNode() { return prev; };
AstNode *AstNodeModuleStdin::putPrevNode(AstNode *const node_) {
  prev = node_;
  return this;
};

bool AstNodeModuleStdin::isDefinedModName() const {
  return defaultModName != moduleName;
};
void AstNodeModuleStdin::replaceModuleName(const std::string modName_) {
  if (modName_ != "") {
    moduleName = modName_;
  }
};
