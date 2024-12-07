// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/ast_node/module_interpreter.hpp"
#include "compiler/parser/ast_node/declare_fmain.hpp"
#include "io/file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;
using namespace gallop::IO;

AstNodeModuleInterpreter::AstNodeModuleInterpreter()
    : nodeType(AstNodeTypeEnum::moduleInterpreter), parent(nullptr),
      child(nullptr), moduleName("moduleForInterpreter"),
      llvmModule(nullptr) {};
AstNodeModuleInterpreter::AstNodeModuleInterpreter(
    const AstNodeModuleInterpreter &rhs)
    : nodeType(rhs.nodeType), parent(rhs.parent), child(rhs.child),
      llvmModule(rhs.llvmModule) {};

AstNodeModuleInterpreter &
AstNodeModuleInterpreter::operator=(const AstNodeModuleInterpreter &rhs) {
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  child = rhs.child;
  llvmModule = rhs.llvmModule;
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
llvm::Value *
AstNodeModuleInterpreter::generateLlvmIr(IrGenContext *const context_) {
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

bool AstNodeModuleInterpreter::hasParent() const { return parent != nullptr; };
bool AstNodeModuleInterpreter::hasPrev() const { return false; };
bool AstNodeModuleInterpreter::hasNext() const { return false; };
bool AstNodeModuleInterpreter::hasChild() const { return child != nullptr; };

AstNode *AstNodeModuleInterpreter::getRoot() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
  }
  return node;
};
AstNode *AstNodeModuleInterpreter::getModule() { return this; };
AstNode *AstNodeModuleInterpreter::getParent() { return parent; };
AstNode *AstNodeModuleInterpreter::getPrev() { return nullptr; };
AstNode *AstNodeModuleInterpreter::getNext() { return nullptr; };
AstNode *AstNodeModuleInterpreter::getChild() { return child; };

AstNode *AstNodeModuleInterpreter::setParent(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeModuleInterpreter::setPrev(AstNode *const node_) {
  return this;
};
AstNode *AstNodeModuleInterpreter::setNext(AstNode *const node_) {
  return this;
};
AstNode *AstNodeModuleInterpreter::setChild(AstNode *const node_) {
  if (!settableChild(node_)) {
    llvm::outs() << "can not set node type " + node_->getAstNodeTypeString() +
                        " on " + getAstNodeTypeString();
    throw "";
  }
  child = node_;
  return child;
};
AstNode *AstNodeModuleInterpreter::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->getParent();
  }
  return node;
};
bool AstNodeModuleInterpreter::isDefinedPackageName() const { return true; };
void AstNodeModuleInterpreter::replacePackageName(const std::string pkgName_) {
  /* nop*/
};
bool AstNodeModuleInterpreter::isDefinedModuleName() const { return true; };
void AstNodeModuleInterpreter::replaceModuleName(const std::string modName_) {
  /* nop */
};

std::string AstNodeModuleInterpreter::getFullModuleName() const {
  return moduleName;
};

llvm::Module *AstNodeModuleInterpreter::getLlvmModule() { return llvmModule; };

bool AstNodeModuleInterpreter::settableChild(AstNode *const node_) const {
  return AstNodeType::isTopLevelChildOfModule(node_->getAstNodeType()) &&
         node_->getAstNodeType() != AstNodeTypeEnum::declareFmain;
};
