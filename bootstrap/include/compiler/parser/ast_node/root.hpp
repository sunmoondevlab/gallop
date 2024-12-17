#ifndef _COMPILER_AST_NODE_ROOT_
#define _COMPILER_AST_NODE_ROOT_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeRoot : public AstNode {
public:
  AstNodeRoot(const AstNodeTypeEnum rootNodeType_);
  ~AstNodeRoot() {};
  AstNodeRoot(const AstNodeRoot &rhs);
  AstNodeRoot &operator=(const AstNodeRoot &rhs);
  Location getLocation() override;
  std::string getAstNodeTypeString() override;
  AstNodeTypeEnum getAstNodeType() override;
  void printAstNode(const size_t depth, const bool isVerbose) override;
  bool hasParent() override;
  bool hasNext() override;
  bool hasChild() override;
  AstNode *moduleNode() override;
  AstNode *rootNode() override;
  AstNode *parentNode() override;
  AstNode *nextNode() override;
  AstNode *childNode() override;
  AstNode *putParentNode(AstNode *const node) override;
  AstNode *putNextNode(AstNode *const node) override;
  AstNode *putChildNode(AstNode *const node) override;

private:
  AstNodeTypeEnum astNodeType;
  AstNode *child;
  size_t moduleIdx;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif