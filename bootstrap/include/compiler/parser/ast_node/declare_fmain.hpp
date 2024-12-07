// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_NODE_DECLARE_FMAIN_
#define _COMPILER_PARSER_AST_NODE_DECLARE_FMAIN_
#include "compiler/parser/ast.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeDeclareFmain : public AstNode {
public:
  AstNodeDeclareFmain(const Location location);
  AstNodeDeclareFmain(const Location location, const std::string entryPointId);
  AstNodeDeclareFmain(const AstNodeDeclareFmain &rhs);
  ~AstNodeDeclareFmain() {};
  AstNodeDeclareFmain &operator=(const AstNodeDeclareFmain &rhs);
  Location getLocation() const override;
  std::string getAstNodeTypeString() const override;
  AstNodeTypeEnum getAstNodeType() const override;
  void printNode(const size_t depth, const bool isVerbose) override;
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
  std::string getEntryPointId() const;

private:
  Location location;
  AstNodeTypeEnum nodeType;
  AstNode *parent;
  AstNode *prev;
  AstNode *next;
  AstNode *child;
  std::string entryPointId;

  bool settableChild(AstNode *const node) const override;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif