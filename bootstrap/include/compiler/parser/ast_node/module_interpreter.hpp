#ifndef _COMPILER_PARSER_AST_NODE_MODULE_INTERPRETER_
#define _COMPILER_PARSER_AST_NODE_MODULE_INTERPRETER_
#include "compiler/parser/ast_node/module.hpp"
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeModuleInterpreter : public AstNodeModule {
public:
  AstNodeModuleInterpreter();
  ~AstNodeModuleInterpreter() {};
  AstNodeModuleInterpreter(const AstNodeModuleInterpreter &rhs);
  AstNodeModuleInterpreter &operator=(const AstNodeModuleInterpreter &rhs);
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
  AstNode *getLastModuleNode() override;
  bool isDefinedPkgName() const override;
  void replacePackageName(const std::string pkgName) override;
  bool isDefinedModName() const override;
  void replaceModuleName(const std::string modName) override;
  std::string getFullModuleName() const override;

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