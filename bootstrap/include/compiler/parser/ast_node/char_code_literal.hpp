// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_NODE_CHAR_CODE_LITERAL_
#define _COMPILER_PARSER_AST_NODE_CHAR_CODE_LITERAL_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeCharCodeLiteral : public AstNode {
public:
  AstNodeCharCodeLiteral(const Location beginLocation,
                         const Location endLocation, const uint32_t value,
                         const std::string utf8Value);
  AstNodeCharCodeLiteral(const AstNodeCharCodeLiteral &rhs);
  ~AstNodeCharCodeLiteral() {};
  AstNodeCharCodeLiteral &operator=(const AstNodeCharCodeLiteral &rhs);
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

private:
  Location beginLocation;
  Location endLocation;
  AstNodeTypeEnum nodeType;
  AstNode *parent;
  AstNode *prev;
  AstNode *next;
  AstNode *child;
  uint32_t value;
  std::string utf8Value;

  bool settableChild(AstNode *const node) const override;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif