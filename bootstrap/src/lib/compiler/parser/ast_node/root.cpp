// // Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
// #include "compiler/parser/ast_node/root.hpp"
// #include <llvm/Support/raw_ostream.h>
// #include <memory>

// using namespace gallop::Compiler;
// using namespace gallop::Compiler::Parser;
// using namespace gallop::Compiler::LLVM;

// AstNodeRoot::AstNodeRoot(const AstNodeTypeEnum nodeType_)
//     : nodeType(nodeType_), child(nullptr), moduleIdx(0),
//       entryPointMap(std::map<std::string, AstNode *>()) {};
// AstNodeRoot::AstNodeRoot(const AstNodeRoot &rhs)
//     : nodeType(rhs.nodeType), child(rhs.child), moduleIdx(rhs.moduleIdx),
//       entryPointMap(rhs.entryPointMap) {};
// AstNodeRoot &AstNodeRoot::operator=(const AstNodeRoot &rhs) {
//   nodeType = rhs.nodeType;
//   child = rhs.child;
//   moduleIdx = rhs.moduleIdx;
//   entryPointMap = rhs.entryPointMap;
//   return *this;
// };
// Location AstNodeRoot::getLocation() const { return Location(0, 0); };
// std::string AstNodeRoot::getAstNodeTypeString() const {
//   return AstNodeType::getString(nodeType);
// };
// AstNodeTypeEnum AstNodeRoot::getAstNodeType() const { return nodeType; };

// void AstNodeRoot::printNode(const size_t &depth_, const bool &isVerbose_) {
//   indentDepth(depth_, true);
//   llvm::outs() << "ast::" << getAstNodeTypeString() << "\n";
// };
// llvm::Value *AstNodeRoot::generateLlvmIr(IrGenContext *const context_) {
//   if (hasChild()) {
//     AstNode *child = getChild();
//     child->generateLlvmIr(context_);
//     while (child->hasNext()) {
//       child = child->getNext();
//       child->generateLlvmIr(context_);
//     }
//   }
//   return nullptr;
// };

// bool AstNodeRoot::hasParent() const { return false; };
// bool AstNodeRoot::hasPrev() const { return false; };
// bool AstNodeRoot::hasNext() const { return false; };
// bool AstNodeRoot::hasChild() const { return child != nullptr; };

// AstNode *AstNodeRoot::getRoot() { return this; };
// AstNode *AstNodeRoot::getModule() {
//   if (nodeType == AstNodeTypeEnum::rootFile) {
//     AstNode *moduleNode = child;
//     if (moduleNode == nullptr) {
//       return moduleNode;
//     }
//     for (size_t i = 0; i < moduleIdx && moduleNode->hasNext(); i++) {
//       moduleNode = moduleNode->getNext();
//     }
//     return moduleNode;
//   } else {
//     return child;
//   }
// };
// AstNode *AstNodeRoot::getParent() { return nullptr; };
// AstNode *AstNodeRoot::getPrev() { return nullptr; };
// AstNode *AstNodeRoot::getNext() { return nullptr; };
// AstNode *AstNodeRoot::getChild() { return child; };

// AstNode *AstNodeRoot::setParent(AstNode *const node_) { return this; };
// AstNode *AstNodeRoot::setPrev(AstNode *const node_) { return this; };
// AstNode *AstNodeRoot::setNext(AstNode *const node_) { return this; };
// AstNode *AstNodeRoot::setChild(AstNode *const node_) {
//   if (!settableChild(node_)) {
//     llvm::outs() << "can not set node type " + node_->getAstNodeTypeString()
//     +
//                         " on " + getAstNodeTypeString();
//     throw "";
//   }
//   if (child != nullptr && nodeType == AstNodeTypeEnum::rootFile) {
//     child->setNext(node_);
//   } else if (child == nullptr) {
//     child = node_;
//   } else {
//     llvm::outs() << "can not set multiple child on " +
//     getAstNodeTypeString(); throw "";
//   }
//   node_->setParent(this);
//   return child;
// };

// bool AstNodeRoot::settableChild(AstNode *const node_) const {
//   AstNodeTypeEnum childNodeType = node_->getAstNodeType();
//   return AstNodeType::isModule(childNodeType) &&
//          AstNodeType::matchSubtype(childNodeType, nodeType);
// };

// bool AstNodeRoot::isExistsEntryPointId(const std::string entryPointId_) const
// {
//   return entryPointMap.count(entryPointId_) > 0;
// };
// AstNode *AstNodeRoot::getTargetDeclareFmain(
//     const std::string targetEntryPointId_) const {
//   if (targetEntryPointId_ != "" &&
//       entryPointMap.count(targetEntryPointId_) > 0) {
//     return entryPointMap.at(targetEntryPointId_);
//   }
//   if (entryPointMap.count("") > 0) {
//     return entryPointMap.at("");
//   }
//   if (entryPointMap.size() > 0) {
//     auto entryPointHead = entryPointMap.begin();
//     return entryPointHead->second;
//   }
//   return nullptr;
// };
// void AstNodeRoot::setEntoryPoint(AstNode *const declareFmain_) {
//   AstNodeDeclareFmain *declareFmainPtr = (AstNodeDeclareFmain
//   *)(declareFmain_);
//   entryPointMap.emplace(declareFmainPtr->getEntryPointId(), declareFmain_);
// };
