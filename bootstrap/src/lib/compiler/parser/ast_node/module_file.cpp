#include "compiler/parser/ast_node/module_file.hpp"
#include "compiler/parser/ast_node/block_fmain.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeModuleFile::AstNodeModuleFile(const std::string filename_)
    : filename(filename_), nodeType(AstNodeTypeEnum::moduleFile),
      parent(nullptr), next(nullptr), child(nullptr), defaultPkgName("main"),
      packageName("main"), defaultModName("main"),
      moduleName(File::getBasename(filename_, true)) {};
AstNodeModuleFile::AstNodeModuleFile(const AstNodeModuleFile &rhs)
    : filename(rhs.filename), nodeType(rhs.nodeType), parent(rhs.parent),
      next(rhs.next), child(rhs.child), packageName(rhs.packageName),
      moduleName(rhs.moduleName) {};

AstNodeModuleFile &AstNodeModuleFile::operator=(const AstNodeModuleFile &rhs) {
  filename = rhs.filename;
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  next = rhs.next;
  child = rhs.child;
  packageName = rhs.packageName;
  moduleName = rhs.moduleName;
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
  indentDepth(depth_);
  llvm::outs() << getAstNodeTypeString() << "{\n";

  indentDepth(depth_ + 1);
  llvm::outs() << "filename: " << filename << ",\n";
  indentDepth(depth_ + 1);
  llvm::outs() << "package name: " << packageName << ",\n";
  indentDepth(depth_ + 1);
  llvm::outs() << "module name: " << moduleName << ",\n";
  if (child != nullptr) {
    child->printNode(depth_ + 1, isVerbose_);
  }
  indentDepth(depth_);
  llvm::outs() << "}";
  if (next != nullptr) {
    llvm::outs() << ",\n";
    next->printNode(depth_, isVerbose_);
  } else {
    llvm::outs() << "\n";
  }
};

bool AstNodeModuleFile::hasParent() const { return parent != nullptr; };
bool AstNodeModuleFile::hasPrev() const { return prev != nullptr; };
bool AstNodeModuleFile::hasNext() const { return next != nullptr; };
bool AstNodeModuleFile::hasChild() const { return child != nullptr; };

AstNode *AstNodeModuleFile::rootNode() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->parentNode();
  }
  return node;
};
AstNode *AstNodeModuleFile::moduleNode() { return this; };
AstNode *AstNodeModuleFile::parentNode() { return parent; };
AstNode *AstNodeModuleFile::prevNode() { return prev; };
AstNode *AstNodeModuleFile::nextNode() { return next; };
AstNode *AstNodeModuleFile::childNode() { return child; };

AstNode *AstNodeModuleFile::putParentNode(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeModuleFile::putPrevNode(AstNode *const node_) {
  prev = node_;
  return this;
};
AstNode *AstNodeModuleFile::putNextNode(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeModuleFile::putChildNode(AstNode *const node_) {
  child = node_;
  return child;
};
AstNode *AstNodeModuleFile::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};

bool AstNodeModuleFile::isDefinedPkgName() const {
  return defaultPkgName != packageName;
};
void AstNodeModuleFile::replacePackageName(const std::string pkgName_) {
  if (pkgName_ != "") {
    packageName = pkgName_;
  }
};
bool AstNodeModuleFile::isDefinedModName() const {
  return defaultModName != moduleName;
};
void AstNodeModuleFile::replaceModuleName(const std::string modName_) {
  if (modName_ != "") {
    moduleName = modName_;
  }
};
