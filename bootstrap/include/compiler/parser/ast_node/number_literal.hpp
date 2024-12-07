// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_NODE_NUMBER_LITERAL_
#define _COMPILER_PARSER_AST_NODE_NUMBER_LITERAL_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeNumberLiteral : public AstNode {
public:
  AstNodeNumberLiteral(const Location location,
                       const AstNodeTypeEnum numberNodeType,
                       const std::string integralValue,
                       const std::string decimalValue,
                       const std::string exponentValue);
  AstNodeNumberLiteral(const AstNodeNumberLiteral &rhs);
  ~AstNodeNumberLiteral() {};
  AstNodeNumberLiteral &operator=(const AstNodeNumberLiteral &rhs);
  Location getLocation() const override;
  std::string getAstNodeTypeNumber() const override;
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

private:
  Location location;
  AstNodeTypeEnum nodeType;
  AstNode *parent;
  AstNode *prev;
  AstNode *next;
  AstNode *child;
  std::string value;
  size_t length;

  bool settableChild(AstNode *const node) const override;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif