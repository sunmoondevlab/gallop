#ifndef _COMPILER_PARSER_AST_NODE_COMMENT_OUT_
#define _COMPILER_PARSER_AST_NODE_COMMENT_OUT_
#include "compiler/parser/ast.hpp"
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeCommentOut : public AstNode {
public:
  AstNodeCommentOut(const AstNodeTypeEnum nodeType, const Location location);
  AstNodeCommentOut(const AstNodeCommentOut &rhs);
  ~AstNodeCommentOut() {};
  AstNodeCommentOut &operator=(const AstNodeCommentOut &rhs);
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
  void setBody(const std::string body);
  void setBegenEndLocation(const Location beginLocation,
                           const Location endLocation);

private:
  Location location;
  Location blockBeginLocation;
  Location blockEndLocation;
  AstNodeTypeEnum nodeType;
  AstNode *parent;
  AstNode *prev;
  AstNode *next;
  AstNode *child;
  std::string body;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif