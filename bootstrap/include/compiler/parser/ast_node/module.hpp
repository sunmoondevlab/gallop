#ifndef _COMPILER_PARSER_AST_NODE_MODULE_
#define _COMPILER_PARSER_AST_NODE_MODULE_
#include "compiler/common/location.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node_type.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeModule : public AstNode {
public:
  virtual ~AstNodeModule() {};
  virtual Location getLocation() const override = 0;
  virtual AstNodeTypeEnum getAstNodeType() const override = 0;
  virtual std::string getAstNodeTypeString() const override = 0;
  virtual void printNode(const size_t depth, const bool isVerbose) override = 0;
  virtual void generateLlvmIr(LLVM::IrGenContext *const context) override = 0;
  virtual bool hasParent() const override = 0;
  virtual bool hasPrev() const override = 0;
  virtual bool hasNext() const override = 0;
  virtual bool hasChild() const override = 0;
  virtual AstNode *rootNode() override = 0;
  virtual AstNode *moduleNode() override = 0;
  virtual AstNode *parentNode() override = 0;
  virtual AstNode *prevNode() override = 0;
  virtual AstNode *nextNode() override = 0;
  virtual AstNode *childNode() override = 0;
  virtual AstNode *putParentNode(AstNode *const node) override = 0;
  virtual AstNode *putPrevNode(AstNode *const node) override = 0;
  virtual AstNode *putNextNode(AstNode *const node) override = 0;
  virtual AstNode *putChildNode(AstNode *const node) override = 0;
  virtual AstNode *getLastModuleNode() = 0;
  virtual bool isDefinedPkgName() const = 0;
  virtual void replacePackageName(const std::string pkgName) = 0;
  virtual bool isDefinedModName() const = 0;
  virtual void replaceModuleName(const std::string modName) = 0;
  virtual std::string getFullModuleName() const = 0;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif