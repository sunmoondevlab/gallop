// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/ast_node/module_file.hpp"
#include "compiler/parser/ast_node/declare_fmain.hpp"
#include "io/file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;
using namespace gallop::IO;

AstNodeModuleFile::AstNodeModuleFile(const std::string filename_)
    : filename(filename_), nodeType(AstNodeTypeEnum::moduleFile),
      parent(nullptr), next(nullptr), child(nullptr),
      defaultPackageName("main"), packageName("main"),
      defaultModuleName(File::filenameOrStem(filename_, true)),
      moduleName(File::filenameOrStem(filename_, true)), llvmModule(nullptr) {};
AstNodeModuleFile::AstNodeModuleFile(const AstNodeModuleFile &rhs)
    : filename(rhs.filename), nodeType(rhs.nodeType), parent(rhs.parent),
      next(rhs.next), child(rhs.child), packageName(rhs.packageName),
      moduleName(rhs.moduleName), llvmModule(rhs.llvmModule) {};

AstNodeModuleFile &AstNodeModuleFile::operator=(const AstNodeModuleFile &rhs) {
  filename = rhs.filename;
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  next = rhs.next;
  child = rhs.child;
  packageName = rhs.packageName;
  moduleName = rhs.moduleName;
  llvmModule = rhs.llvmModule;
  return *this;
};
Location AstNodeModuleFile::getLocation() const {
  return Location(filename, 0, 0);
};
std::string AstNodeModuleFile::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeModuleFile::getAstNodeType() const { return nodeType; };

void AstNodeModuleFile::printNode(const size_t depth_, const bool isVerbose_) {
  indentDepth(depth_, true);
  llvm::outs() << getAstNodeTypeString() << "\n";

  indentDepth(depth_ + 1);
  llvm::outs() << "filename: " << filename << "\n";
  indentDepth(depth_ + 1);
  llvm::outs() << "package name: " << packageName << "\n";
  indentDepth(depth_ + 1);
  llvm::outs() << "module name: " << moduleName << "\n";
};
llvm::Value *AstNodeModuleFile::generateLlvmIr(IrGenContext *const context_) {
  llvm::LLVMContext *lContext = context_->getContext();
  llvmModule = new llvm::Module(getFullModuleName(), *lContext);
  context_->pushModule(llvmModule);
  llvmModule->setSourceFileName(filename);
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

bool AstNodeModuleFile::hasParent() const { return parent != nullptr; };
bool AstNodeModuleFile::hasPrev() const { return prev != nullptr; };
bool AstNodeModuleFile::hasNext() const { return next != nullptr; };
bool AstNodeModuleFile::hasChild() const { return child != nullptr; };

AstNode *AstNodeModuleFile::getRoot() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
  }
  return node;
};
AstNode *AstNodeModuleFile::getModule() { return this; };
AstNode *AstNodeModuleFile::getParent() { return parent; };
AstNode *AstNodeModuleFile::getPrev() { return prev; };
AstNode *AstNodeModuleFile::getNext() { return next; };
AstNode *AstNodeModuleFile::getChild() { return child; };

AstNode *AstNodeModuleFile::setParent(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeModuleFile::setPrev(AstNode *const node_) {
  prev = node_;
  return this;
};
AstNode *AstNodeModuleFile::setNext(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeModuleFile::setChild(AstNode *const node_) {
  if (!settableChild(node_)) {
    llvm::outs() << "can not set node type " + node_->getAstNodeTypeString() +
                        " on " + getAstNodeTypeString();
    throw "";
  }
  child = node_;
  return child;
};
AstNode *AstNodeModuleFile::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->getParent();
  }
  return node;
};

bool AstNodeModuleFile::isDefinedPackageName() const {
  return defaultPackageName != packageName;
};
void AstNodeModuleFile::replacePackageName(const std::string pkgName_) {
  if (pkgName_ != "") {
    packageName = pkgName_;
  }
};
bool AstNodeModuleFile::isDefinedModuleName() const {
  return defaultModuleName != moduleName;
};
void AstNodeModuleFile::replaceModuleName(const std::string modName_) {
  if (modName_ != "") {
    moduleName = modName_;
  }
};

std::string AstNodeModuleFile::getFullModuleName() const {
  return packageName + "." + moduleName;
};

llvm::Module *AstNodeModuleFile::getLlvmModule() { return llvmModule; };

bool AstNodeModuleFile::settableChild(AstNode *const node_) const {
  return AstNodeType::isTopLevelChildOfModule(node_->getAstNodeType());
};
