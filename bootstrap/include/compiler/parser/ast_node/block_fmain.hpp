#ifndef _COMPILER_AST_NODE_BLOCK_FMAIN_
#define _COMPILER_AST_NODE_BLOCK_FMAIN_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeBlockFmain : public AstNode {
public:
  AstNodeBlockFmain(const Location location_);
  AstNodeBlockFmain(const AstNodeBlockFmain &rhs);
  ~AstNodeBlockFmain() {};
  AstNodeBlockFmain &operator=(const AstNodeBlockFmain &rhs);
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
  void setBegenEndLocation(const Location location_, const bool endFlag_);

private:
  Location location;
  Location blockBeginLocation;
  Location blockEndLocation;
  AstNodeTypeEnum astNodeType;
  AstNode *parent;
  AstNode *child;
  AstNode *next;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif