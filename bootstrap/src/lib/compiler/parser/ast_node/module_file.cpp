#include "compiler/parser/ast_node/module_file.hpp"
#include "compiler/parser/ast_node/block_fmain.hpp"
#include "file/file.hpp"
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;

AstNodeModuleFile::AstNodeModuleFile(const std::string filename_)
    : filename(filename_), astNodeType(AstNodeTypeEnum::moduleFile),
      next(nullptr), child(nullptr), defaultPkgName("main"),
      packageName("main"), defaultModName("main"),
      moduleName(File::getBasename(filename_, true)) {};
AstNodeModuleFile::AstNodeModuleFile(const AstNodeModuleFile &rhs)
    : filename(rhs.filename), astNodeType(rhs.astNodeType), next(rhs.next),
      child(rhs.child), packageName(rhs.packageName),
      moduleName(rhs.moduleName) {};

AstNodeModuleFile &AstNodeModuleFile::operator=(const AstNodeModuleFile &rhs) {
  filename = rhs.filename;
  astNodeType = rhs.astNodeType;
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
  return AstNodeType::getString(astNodeType);
};
AstNodeTypeEnum AstNodeModuleFile::getAstNodeType() const {
  return astNodeType;
};

void AstNodeModuleFile::printAstNode(const size_t depth,
                                     const bool isVerbose_) {
  indentDepth(depth);
  llvm::outs() << getAstNodeTypeString() << "{\n";

  indentDepth(depth + 1);
  llvm::outs() << "filename: " << filename << ",\n";
  indentDepth(depth + 1);
  llvm::outs() << "package name: " << packageName << ",\n";
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

bool AstNodeModuleFile::hasParent() const { return false; };
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
AstNode *AstNodeModuleFile::parentNode() { return nullptr; };
AstNode *AstNodeModuleFile::nextNode() { return next; };
AstNode *AstNodeModuleFile::childNode() { return child; };

AstNode *AstNodeModuleFile::putParentNode(AstNode *const node_) {
  return this;
};
AstNode *AstNodeModuleFile::putChildNode(AstNode *const node_) {
  child = node_;
  node_->putParentNode(this);
  return child;
};
AstNode *AstNodeModuleFile::putNextNode(AstNode *const node_) {
  next = node_;
  (dynamic_cast<AstNodeModuleFile *>(node_))->putPrevNode(this);
  return next;
};
AstNode *AstNodeModuleFile::getLastModuleNode() {
  AstNode *node = this;
  while (node->hasNext()) {
    node = node->parentNode();
  }
  return node;
};
bool AstNodeModuleFile::hasPrev() const { return prev != nullptr; };
AstNode *AstNodeModuleFile::prevNode() { return prev; };
AstNode *AstNodeModuleFile::putPrevNode(AstNode *const node_) {
  prev = node_;
  return this;
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
