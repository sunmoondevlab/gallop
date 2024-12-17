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
  AstNode *getLastModuleNode();
  bool hasPrev();
  AstNode *prevNode();
  AstNode *putPrevNode(AstNode *const node);

private:
  AstNodeTypeEnum astNodeType;
  AstNode *next;
  AstNode *child;
  AstNode *prev;
  const std::string moduleName;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif