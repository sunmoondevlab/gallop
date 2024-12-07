#include "compiler/parser/ast_node/module_interpreter.hpp"
#include "compiler/parser/ast_node/block_fmain.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeModuleInterpreter::AstNodeModuleInterpreter()
    : nodeType(AstNodeTypeEnum::moduleInterpreter), parent(nullptr),
      child(nullptr), moduleName("moduleForInterpreter") {};
AstNodeModuleInterpreter::AstNodeModuleInterpreter(
    const AstNodeModuleInterpreter &rhs)
    : nodeType(rhs.nodeType), parent(rhs.parent), child(rhs.child) {};

AstNodeModuleInterpreter &
AstNodeModuleInterpreter::operator=(const AstNodeModuleInterpreter &rhs) {
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  child = rhs.child;
  return *this;
};
Location AstNodeModuleInterpreter::getLocation() const {
  return Location(0, 0);
};
std::string AstNodeModuleInterpreter::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeModuleInterpreter::getAstNodeType() const {
  return nodeType;
};

void AstNodeModuleInterpreter::printNode(const size_t depth_,
                                         const bool isVerbose_) {
  indentDepth(depth_, true);
  llvm::outs() << getAstNodeTypeString() << "\n";

  indentDepth(depth_ + 1);
  llvm::outs() << "module name: " << moduleName << ",\n";
};
void AstNodeModuleInterpreter::generateLlvmIr(IrGenContext *const context_) {
  llvm::LLVMContext *lContext = context_->getContext();
  llvm::Module *module = new llvm::Module(getFullModuleName(), *lContext);
  context_->pushModule(module);
};

bool AstNodeModuleInterpreter::hasParent() const { return parent != nullptr; };
bool AstNodeModuleInterpreter::hasPrev() const { return false; };
bool AstNodeModuleInterpreter::hasNext() const { return false; };
bool AstNodeModuleInterpreter::hasChild() const { return child != nullptr; };

AstNode *AstNodeModuleInterpreter::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeModuleInterpreter::moduleNode() { return this; };
AstNode *AstNodeModuleInterpreter::parentNode() { return parent; };
AstNode *AstNodeModuleInterpreter::prevNode() { return nullptr; };
AstNode *AstNodeModuleInterpreter::nextNode() { return nullptr; };
AstNode *AstNodeModuleInterpreter::childNode() { return child; };

AstNode *AstNodeModuleInterpreter::putParentNode(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeModuleInterpreter::putPrevNode(AstNode *const node_) {
  return this;
};
AstNode *AstNodeModuleInterpreter::putNextNode(AstNode *const node_) {
  return this;
};
AstNode *AstNodeModuleInterpreter::putChildNode(AstNode *const node_) {
  child = node_;
  return child;
};
AstNode *AstNodeModuleInterpreter::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};
bool AstNodeModuleInterpreter::isDefinedPkgName() const { return true; };
void AstNodeModuleInterpreter::replacePackageName(const std::string pkgName_) {
  /* nop*/
};
bool AstNodeModuleInterpreter::isDefinedModName() const { return true; };
void AstNodeModuleInterpreter::replaceModuleName(const std::string modName_) {
  /* nop */
};

std::string AstNodeModuleInterpreter::getFullModuleName() const {
  return moduleName;
};