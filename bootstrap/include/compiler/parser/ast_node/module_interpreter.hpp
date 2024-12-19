#ifndef _COMPILER_AST_NODE_MODULE_INTERPRETER_
#define _COMPILER_AST_NODE_MODULE_INTERPRETER_
#include "compiler/parser/ast.hpp"
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeModuleInterpreter : public AstNode {
public:
  AstNodeModuleInterpreter();
  ~AstNodeModuleInterpreter() {};
  AstNodeModuleInterpreter(const AstNodeModuleInterpreter &rhs);
  AstNodeModuleInterpreter &operator=(const AstNodeModuleInterpreter &rhs);
  Location getLocation() const override;
  std::string getAstNodeTypeString() const override;
  AstNodeTypeEnum getAstNodeType() const override;
  void printNode(const size_t depth, const bool isVerbose) override;
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
  AstNode *getLastModuleNode();

private:
  AstNodeTypeEnum nodeType;
  AstNode *parent;
  AstNode *child;
  const std::string moduleName;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif