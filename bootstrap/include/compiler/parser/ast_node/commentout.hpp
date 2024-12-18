#ifndef _COMPILER_AST_NODE_BLOCK_FMAIN_
#define _COMPILER_AST_NODE_BLOCK_FMAIN_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeCommentOut : public AstNode {
public:
  AstNodeCommentOut(const AstNodeTypeEnum nodeType_, const Location location_);
  AstNodeCommentOut(const AstNodeCommentOut &rhs);
  ~AstNodeCommentOut() {};
  AstNodeCommentOut &operator=(const AstNodeCommentOut &rhs);
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
  std::string commentOutString;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif