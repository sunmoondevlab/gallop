// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/ast_node/module_stdin.hpp"
#include "compiler/parser/ast_node/declare_fmain.hpp"
#include "io/file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;
using namespace gallop::IO;

AstNodeModuleStdin::AstNodeModuleStdin()
    : nodeType(AstNodeTypeEnum::moduleStdin), parent(nullptr), child(nullptr),
      defaultModuleName("moduleFromStdin"), moduleName("moduleFromStdin"),
      llvmModule(nullptr) {};
AstNodeModuleStdin::AstNodeModuleStdin(const AstNodeModuleStdin &rhs)
    : nodeType(rhs.nodeType), parent(rhs.parent), child(rhs.child),
      moduleName(rhs.moduleName), llvmModule(rhs.llvmModule) {};

AstNodeModuleStdin &
AstNodeModuleStdin::operator=(const AstNodeModuleStdin &rhs) {
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  child = rhs.child;
  moduleName = rhs.moduleName;
  llvmModule = rhs.llvmModule;
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
llvm::Value *AstNodeModuleStdin::generateLlvmIr(IrGenContext *const context_) {
  llvm::LLVMContext *lContext = context_->getContext();
  llvmModule = new llvm::Module(getFullModuleName(), *lContext);
  context_->pushModule(llvmModule);
  if (hasChild()) {
    AstNode *child = getChild();
    child->generateLlvmIr(context_);
    while (child->hasNext()) {
      child = child->getNext();
      child->generateLlvmIr(context_);
    }
  }
  return nullptr;
};

bool AstNodeModuleStdin::hasParent() const { return parent != nullptr; };
bool AstNodeModuleStdin::hasPrev() const { return false; };
bool AstNodeModuleStdin::hasNext() const { return false; };
bool AstNodeModuleStdin::hasChild() const { return child != nullptr; };

AstNode *AstNodeModuleStdin::getRoot() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
  }
  return node;
};
AstNode *AstNodeModuleStdin::getModule() { return this; };
AstNode *AstNodeModuleStdin::getParent() { return parent; };
AstNode *AstNodeModuleStdin::getPrev() { return nullptr; };
AstNode *AstNodeModuleStdin::getNext() { return nullptr; };
AstNode *AstNodeModuleStdin::getChild() { return child; };

AstNode *AstNodeModuleStdin::setParent(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeModuleStdin::setPrev(AstNode *const node_) { return this; };
AstNode *AstNodeModuleStdin::setNext(AstNode *const node_) { return this; };
AstNode *AstNodeModuleStdin::setChild(AstNode *const node_) {
  if (!settableChild(node_)) {
    llvm::outs() << "can not set node type " + node_->getAstNodeTypeString() +
                        " on " + getAstNodeTypeString();
    throw "";
  }
  child = node_;
  return child;
};
AstNode *AstNodeModuleStdin::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->getParent();
  }
  return node;
};

bool AstNodeModuleStdin::isDefinedPackageName() const { return true; };
void AstNodeModuleStdin::replacePackageName(const std::string pkgName_) {
  /* nop*/
};
bool AstNodeModuleStdin::isDefinedModuleName() const {
  return defaultModuleName != moduleName;
};
void AstNodeModuleStdin::replaceModuleName(const std::string modName_) {
  if (modName_ != "") {
    moduleName = modName_;
  }
};

std::string AstNodeModuleStdin::getFullModuleName() const {
  return moduleName;
};

llvm::Module *AstNodeModuleStdin::getLlvmModule() { return llvmModule; };

bool AstNodeModuleStdin::settableChild(AstNode *const node_) const {
  return AstNodeType::isTopLevelChildOfModule(node_->getAstNodeType());
};
