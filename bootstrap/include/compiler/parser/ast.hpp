#ifndef _COMPILER_PARSER_AST_
#define _COMPILER_PARSER_AST_
#include "compiler/common/location.hpp"
#include "compiler/parser/ast_node_type.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNode {
public:
  virtual ~AstNode() {};
  virtual Location getLocation() = 0;
  virtual AstNodeTypeEnum getAstNodeType() = 0;
  virtual std::string getAstNodeTypeString() = 0;
  virtual void printAstNode(const size_t depth, const bool isVerbose) = 0;
  virtual bool hasParent() = 0;
  virtual bool hasNext() = 0;
  virtual bool hasChild() = 0;
  virtual AstNode *rootNode() = 0;
  virtual AstNode *parentNode() = 0;
  virtual AstNode *nextNode() = 0;
  virtual AstNode *childNode() = 0;
  virtual AstNode *putParentNode(AstNode *const node) = 0;
  virtual AstNode *putNextNode(AstNode *const node) = 0;
  virtual AstNode *putChildNode(AstNode *const node) = 0;
  static void indentDepth(const size_t depth);
};

// Children classes of AstNode is Split into separate files

class Ast {
public:
  Ast(const AstNodeTypeEnum rootNodeType_);
  ~Ast() {};
  Ast(const Ast &rhs);
  Ast &operator=(const Ast &rhs);
  AstNode *getRoot();
  void printAst(const bool isVerbose);

private:
  AstNode *root;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif