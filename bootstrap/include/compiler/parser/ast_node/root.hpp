// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_NODE_ROOT_
#define _COMPILER_PARSER_AST_NODE_ROOT_
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/declare_fmain.hpp"
#include <map>
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
  bool isExistsEntryPointId(const std::string entryPointId) const;
  AstNode *getTargetDeclareFmain(const std::string targetEntryPointId) const;
  void setEntoryPoint(AstNode *const declareFmain);

private:
  AstNodeTypeEnum nodeType;
  AstNode *child;
  size_t moduleIdx;
  std::map<std::string, AstNode *> entryPointMap;

  bool settableChild(AstNode *const node) const override;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif