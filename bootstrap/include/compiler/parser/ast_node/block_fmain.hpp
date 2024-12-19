#ifndef _COMPILER_AST_NODE_BLOCK_FMAIN_
#define _COMPILER_AST_NODE_BLOCK_FMAIN_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeBlockFmain : public AstNode {
public:
  AstNodeBlockFmain(const Location location);
  AstNodeBlockFmain(const AstNodeBlockFmain &rhs);
  ~AstNodeBlockFmain() {};
  AstNodeBlockFmain &operator=(const AstNodeBlockFmain &rhs);
  Location getLocation() const override;
  std::string getAstNodeTypeString() const override;
  AstNodeTypeEnum getAstNodeType() const override;
  void printAstNode(const size_t depth, const bool isVerbose) override;
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
  void setBegenEndLocation(const Location location, const bool endFlag);

private:
  Location location;
  Location blockBeginLocation;
  Location blockEndLocation;
  AstNodeTypeEnum astNodeType;
  AstNode *parent;
  AstNode *prev;
  AstNode *next;
  AstNode *child;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif