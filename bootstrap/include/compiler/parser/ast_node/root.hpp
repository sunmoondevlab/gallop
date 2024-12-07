#ifndef _COMPILER_PARSER_AST_NODE_ROOT_
#define _COMPILER_PARSER_AST_NODE_ROOT_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeRoot : public AstNode {
public:
  AstNodeRoot(const AstNodeTypeEnum nodeType);
  ~AstNodeRoot() {};
  AstNodeRoot(const AstNodeRoot &rhs);
  AstNodeRoot &operator=(const AstNodeRoot &rhs);
  Location getLocation() const override;
  std::string getAstNodeTypeString() const override;
  AstNodeTypeEnum getAstNodeType() const override;
  void printNode(const size_t depth, const bool isVerbose) override;
  void generateLlvmIr(LLVM::IrGenContext *const context) override;
  bool hasParent() const override;
  bool hasPrev() const override;
  bool hasNext() const override;
  bool hasChild() const override;
  AstNode *moduleNode() override;
  AstNode *rootNode() override;
  AstNode *parentNode() override;
  AstNode *prevNode() override;
  AstNode *nextNode() override;
  AstNode *childNode() override;
  AstNode *putParentNode(AstNode *const node) override;
  AstNode *putPrevNode(AstNode *const node) override;
  AstNode *putNextNode(AstNode *const node) override;
  AstNode *putChildNode(AstNode *const node) override;

private:
  AstNodeTypeEnum nodeType;
  AstNode *child;
  size_t moduleIdx;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif