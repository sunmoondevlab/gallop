// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/ast_node/declare_fmain.hpp"
#include "compiler/parser/ast_node/module.hpp"
#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler;
using namespace gallop::Compiler::Parser;
using namespace gallop::Compiler::LLVM;

AstNodeDeclareFmain::AstNodeDeclareFmain(const Location location_)
    : location(location_), nodeType(AstNodeTypeEnum::declareFmain),
      parent(nullptr), prev(nullptr), next(nullptr), child(nullptr),
      entryPointId("") {};
AstNodeDeclareFmain::AstNodeDeclareFmain(const Location location_,
                                         const std::string entryPointId_)
    : location(location_), nodeType(AstNodeTypeEnum::declareFmain),
      parent(nullptr), prev(nullptr), next(nullptr), child(nullptr),
      entryPointId(entryPointId_) {};
AstNodeDeclareFmain::AstNodeDeclareFmain(const AstNodeDeclareFmain &rhs)
    : location(rhs.location), nodeType(rhs.nodeType), parent(rhs.parent),
      prev(rhs.prev), next(rhs.next), child(rhs.child),
      entryPointId(rhs.entryPointId) {};

AstNodeDeclareFmain &
AstNodeDeclareFmain::operator=(const AstNodeDeclareFmain &rhs) {
  location = rhs.location;
  nodeType = rhs.nodeType;
  parent = rhs.parent;
  prev = rhs.prev;
  next = rhs.next;
  child = rhs.child;
  entryPointId = rhs.entryPointId;
  return *this;
};
Location AstNodeDeclareFmain::getLocation() const { return location; };
std::string AstNodeDeclareFmain::getAstNodeTypeString() const {
  return AstNodeType::getString(nodeType);
};
AstNodeTypeEnum AstNodeDeclareFmain::getAstNodeType() const {
  return nodeType;
};

void AstNodeDeclareFmain::printNode(const size_t depth_,
                                    const bool isVerbose_) {
  indentDepth(depth_, true);
  llvm::outs() << getAstNodeTypeString() << "\n";
  if (entryPointId != "") {
    indentDepth(depth_ + 1);
    llvm::outs() << "entryPointId: " << entryPointId << "\n";
  }
};
llvm::Value *AstNodeDeclareFmain::generateLlvmIr(IrGenContext *const context_) {
  context_->setExecutableBinary();
  llvm::LLVMContext *lContext = context_->getContext();
  llvm::Module *lModule = ((AstNodeModule *)(getModule()))->getLlvmModule();
  llvm::IRBuilder<> *lBuilder = context_->getBuilder();

  llvm::FunctionType *mainFuncType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*lContext), false);
  llvm::Function *mainFunc = llvm::Function::Create(
      mainFuncType, llvm::Function::ExternalLinkage, "main", *lModule);
  llvm::BasicBlock *entry =
      llvm::BasicBlock::Create(*lContext, "entrypoint", mainFunc);
  lBuilder->SetInsertPoint(entry);
  if (hasChild()) {
    AstNode *child = getChild();
    child->generateLlvmIr(context_);
    while (child->hasNext()) {
      child = child->getNext();
      child->generateLlvmIr(context_);
    }
  } else {
    lBuilder->CreateRet(lBuilder->getInt32(0));
  }
  return nullptr;
};

bool AstNodeDeclareFmain::hasParent() const { return parent != nullptr; };
bool AstNodeDeclareFmain::hasPrev() const { return prev != nullptr; };
bool AstNodeDeclareFmain::hasNext() const { return next != nullptr; };
bool AstNodeDeclareFmain::hasChild() const { return child != nullptr; };

AstNode *AstNodeDeclareFmain::getRoot() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
  }
  return node;
};
AstNode *AstNodeDeclareFmain::getModule() {
  AstNode *node = this;
  while (node->hasParent()) {
    node = node->getParent();
    AstNodeTypeEnum nodeType = node->getAstNodeType();
    if (AstNodeType::isModule(nodeType)) {
      break;
    }
  }
  return node;
};
AstNode *AstNodeDeclareFmain::getParent() { return parent; };
AstNode *AstNodeDeclareFmain::getPrev() { return prev; };
AstNode *AstNodeDeclareFmain::getNext() { return next; };
AstNode *AstNodeDeclareFmain::getChild() { return child; };

AstNode *AstNodeDeclareFmain::setParent(AstNode *const node_) {
  parent = node_;
  return this;
};
AstNode *AstNodeDeclareFmain::setPrev(AstNode *const node_) {
  prev = node_;
  return prev;
};
AstNode *AstNodeDeclareFmain::setNext(AstNode *const node_) {
  next = node_;
  return next;
};
AstNode *AstNodeDeclareFmain::setChild(AstNode *const node_) {
  if (!settableChild(node_)) {
    llvm::outs() << "can not set node type " + node_->getAstNodeTypeString() +
                        " on " + getAstNodeTypeString();
    throw "";
  }
  child = node_;
  return child;
};

std::string AstNodeDeclareFmain::getEntryPointId() const {
  return entryPointId;
};

bool AstNodeDeclareFmain::settableChild(AstNode *const node_) const {
  AstNodeTypeEnum childNodeType = node_->getAstNodeType();
  return childNodeType == AstNodeTypeEnum::controlBlock;
};