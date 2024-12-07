#include "compiler/parser/ast_node/module_stdin.hpp"
#include "compiler/parser/ast_node/block_fmain.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeModuleStdin::AstNodeModuleStdin()
    : nodeType(AstNodeTypeEnum::moduleStdin), parent(nullptr), child(nullptr),
      defaultModName("moduleFromStdin"), moduleName("moduleFromStdin") {};
AstNodeModuleStdin::AstNodeModuleStdin(const AstNodeModuleStdin &rhs)
    : nodeType(rhs.nodeType), parent(rhs.parent), child(rhs.child),
      moduleName(rhs.moduleName) {};

AstNodeModuleStdin &
AstNodeModuleStdin::operator=(const AstNodeModuleStdin &rhs) {
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  child = rhs.child;
  moduleName = rhs.moduleName;
  return *this;
};
Location AstNodeModuleStdin::getLocation() const { return Location(0, 0); };
std::string AstNodeModuleStdin::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeModuleStdin::getAstNodeType() const { return nodeType; };

void AstNodeModuleStdin::printNode(const size_t depth_, const bool isVerbose_) {
  indentDepth(depth_, true);
  llvm::outs() << getAstNodeTypeString() << "\n";

  indentDepth(depth_ + 1);
  llvm::outs() << "module name: " << moduleName << "\n";
};
void AstNodeModuleStdin::generateLlvmIr(IrGenContext *const context_) {
  llvm::LLVMContext *lContext = context_->getContext();
  llvm::Module *module = new llvm::Module(getFullModuleName(), *lContext);
  context_->pushModule(module);
};

bool AstNodeModuleStdin::hasParent() const { return parent != nullptr; };
bool AstNodeModuleStdin::hasPrev() const { return false; };
bool AstNodeModuleStdin::hasNext() const { return false; };
bool AstNodeModuleStdin::hasChild() const { return child != nullptr; };

AstNode *AstNodeModuleStdin::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeModuleStdin::moduleNode() { return this; };
AstNode *AstNodeModuleStdin::parentNode() { return parent; };
AstNode *AstNodeModuleStdin::prevNode() { return nullptr; };
AstNode *AstNodeModuleStdin::nextNode() { return nullptr; };
AstNode *AstNodeModuleStdin::childNode() { return child; };

AstNode *AstNodeModuleStdin::putParentNode(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeModuleStdin::putPrevNode(AstNode *const node_) { return this; };
AstNode *AstNodeModuleStdin::putNextNode(AstNode *const node_) { return this; };
AstNode *AstNodeModuleStdin::putChildNode(AstNode *const node_) {
  child = node_;
  return child;
};
AstNode *AstNodeModuleStdin::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};

bool AstNodeModuleStdin::isDefinedPkgName() const { return true; };
void AstNodeModuleStdin::replacePackageName(const std::string pkgName_) {
  /* nop*/
};
bool AstNodeModuleStdin::isDefinedModName() const {
  return defaultModName != moduleName;
};
void AstNodeModuleStdin::replaceModuleName(const std::string modName_) {
  if (modName_ != "") {
    moduleName = modName_;
  }
};

std::string AstNodeModuleStdin::getFullModuleName() const {
  return moduleName;
};