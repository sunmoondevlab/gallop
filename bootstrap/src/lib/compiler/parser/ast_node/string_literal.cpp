// // Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
// #include "compiler/parser/ast_node/string_literal.hpp"
// #include "compiler/parser/ast_node/module.hpp"
// #include <llvm/Support/raw_ostream.h>

// using namespace gallop::Compiler;
// using namespace gallop::Compiler::Parser;
// using namespace gallop::Compiler::LLVM;

// AstNodeStringLiteral::AstNodeStringLiteral(const Location beginLocation_,
//                                            const Location endLocation_,
//                                            const std::string value_)
//     : beginLocation(beginLocation_), endLocation(endLocation_),
//       nodeType(AstNodeTypeEnum::stringLiteral), parent(nullptr),
//       prev(nullptr), next(nullptr), child(nullptr), value(value_),
//       length(value_.size()) {};
// AstNodeStringLiteral::AstNodeStringLiteral(const AstNodeStringLiteral &rhs)
//     : beginLocation(rhs.beginLocation), endLocation(rhs.endLocation),
//       nodeType(rhs.nodeType), parent(rhs.parent), prev(rhs.prev),
//       next(rhs.next), child(rhs.child), value(rhs.value), length(rhs.length)
//       {};

// AstNodeStringLiteral &
// AstNodeStringLiteral::operator=(const AstNodeStringLiteral &rhs) {
//   beginLocation = rhs.beginLocation;
//   endLocation = rhs.endLocation;
//   nodeType = rhs.nodeType;
//   parent = rhs.parent;
//   prev = rhs.prev;
//   next = rhs.next;
//   child = rhs.child;
//   value = rhs.value;
//   length = rhs.length;
//   return *this;
// };
// Location AstNodeStringLiteral::getLocation() const { return beginLocation; };
// std::string AstNodeStringLiteral::getAstNodeTypeString() const {
//   return AstNodeType::getString(nodeType);
// };
// AstNodeTypeEnum AstNodeStringLiteral::getAstNodeType() const {
//   return nodeType;
// };

// void AstNodeStringLiteral::printNode(const size_t &depth_,
//                                      const bool &isVerbose_) {
//   indentDepth(depth_, true);
//   llvm::outs() << getAstNodeTypeString() << "\n";
//   if (isVerbose_) {
//     indentDepth(depth_ + 1);
//     llvm::outs() << "beginLocation: [" << beginLocation.getLine() << ","
//                  << beginLocation.getColumn() << "]\n";
//     indentDepth(depth_ + 1);
//     llvm::outs() << "endLocation: [" << endLocation.getLine() << ","
//                  << endLocation.getColumn() << "]\n";
//   }
//   if (value != "") {
//     indentDepth(depth_ + 1);
//     llvm::outs() << "value: \"" << value.c_str() << "\"\n";
//     indentDepth(depth_ + 1);
//     llvm::outs() << "length: " << std::to_string(length) << "\n";
//   }
// };
// llvm::Value *
// AstNodeStringLiteral::generateLlvmIr(IrGenContext *const context_) {
//   llvm::IRBuilder<> *lBuilder = context_->getBuilder();
//   llvm::Value *valueP = lBuilder->CreateGlobalStringPtr(value);
//   return valueP;
// };

// bool AstNodeStringLiteral::hasParent() const { return parent != nullptr; };
// bool AstNodeStringLiteral::hasPrev() const { return prev != nullptr; };
// bool AstNodeStringLiteral::hasNext() const { return next != nullptr; };
// bool AstNodeStringLiteral::hasChild() const { return child != nullptr; };

// AstNode *AstNodeStringLiteral::getRoot() {
//   AstNode *node = this;
//   while (node->hasParent()) {
//     node = node->getParent();
//   }
//   return node;
// };
// AstNode *AstNodeStringLiteral::getModule() {
//   AstNode *node = this;
//   while (node->hasParent()) {
//     node = node->getParent();
//     AstNodeTypeEnum nodeType = node->getAstNodeType();
//     if (AstNodeType::isModule(nodeType)) {
//       break;
//     }
//   }
//   return node;
// };
// AstNode *AstNodeStringLiteral::getParent() { return parent; };
// AstNode *AstNodeStringLiteral::getPrev() { return next; };
// AstNode *AstNodeStringLiteral::getNext() { return next; };
// AstNode *AstNodeStringLiteral::getChild() { return child; };

// AstNode *AstNodeStringLiteral::setParent(AstNode *const node_) {
//   parent = node_;
//   return this;
// };
// AstNode *AstNodeStringLiteral::setPrev(AstNode *const node_) {
//   prev = node_;
//   return next;
// };
// AstNode *AstNodeStringLiteral::setNext(AstNode *const node_) {
//   next = node_;
//   return next;
// };
// AstNode *AstNodeStringLiteral::setChild(AstNode *const node_) {
//   if (!settableChild(node_)) {
//     return this;
//   }
//   child = node_;
//   return child;
// };

// bool AstNodeStringLiteral::settableChild(AstNode *const node_) const {
//   return false;
// };