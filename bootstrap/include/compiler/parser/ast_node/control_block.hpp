// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_NODE_CONTROL_BLOCK_
#define _COMPILER_PARSER_AST_NODE_CONTROL_BLOCK_

#include "compiler/parser/ast.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeControlBlock : public AstNode {
public:
  AstNodeControlBlock(const Location beginLocation,
                      AstNodeTypeEnum blockNodeType);
  AstNodeControlBlock(const AstNodeControlBlock &rhs);
  ~AstNodeControlBlock() {};
  AstNodeControlBlock &operator=(const AstNodeControlBlock &rhs);
  Location getLocation() const override;
  Location getBeginLocation() const;
  Location getEndLocation() const;
  std::string getAstNodeTypeString() const override;
  AstNodeTypeEnum getAstNodeType() const override;
  AstNodeTypeEnum getBlockNodeType() const;
  void printNode(const size_t &depth, const bool &isVerbose) override;
  llvm::Value *generateLlvmIr(LLVM::IrGenContext *const context) override;
  bool hasParent() const override;
  bool hasPrev() const override;
  bool hasNext() const override;
  bool hasChild() const override;
  AstNode *getModule() override;
  AstNode *getRoot() override;
  AstNode *getParent() override;
  AstNode *getPrev() override;
  AstNode *getNext() override;
  AstNode *getChild() override;
  AstNode *setParent(AstNode *const node) override;
  AstNode *setPrev(AstNode *const node) override;
  AstNode *setNext(AstNode *const node) override;
  AstNode *setChild(AstNode *const node) override;
  void setEndLocation(const Location endLocation);
  bool hasReturnVal();
  bool isInFmain();

private:
  Location beginLocation;
  Location endLocation;
  AstNodeTypeEnum nodeType;
  AstNodeTypeEnum blockNodeType;
  AstNode *parent;
  AstNode *prev;
  AstNode *next;
  AstNode *child;
  bool declaredReturnVal;

  bool settableChild(AstNode *const node) const override;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif