#ifndef _COMPILER_AST_NODE_MODULE_FILE_
#define _COMPILER_AST_NODE_MODULE_FILE_
#include "compiler/parser/ast.hpp"
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNodeModuleFile : public AstNode {
public:
  AstNodeModuleFile(const std::string filename);
  ~AstNodeModuleFile() {};
  AstNodeModuleFile(const AstNodeModuleFile &rhs);
  AstNodeModuleFile &operator=(const AstNodeModuleFile &rhs);
  Location getLocation() const override;
  std::string getAstNodeTypeString() const override;
  AstNodeTypeEnum getAstNodeType() const override;
  void printAstNode(const size_t depth, const bool isVerbose) override;
  bool hasParent() const override;
  bool hasNext() const override;
  bool hasChild() const override;
  AstNode *moduleNode() override;
  AstNode *rootNode() override;
  AstNode *parentNode() override;
  AstNode *nextNode() override;
  AstNode *childNode() override;
  AstNode *putParentNode(AstNode *const node) override;
  AstNode *putNextNode(AstNode *const node) override;
  AstNode *putChildNode(AstNode *const node) override;
  AstNode *getLastModuleNode();
  bool hasPrev() const;
  AstNode *prevNode();
  AstNode *putPrevNode(AstNode *const node);
  bool isDefinedPkgName() const;
  void replacePackageName(const std::string pkgName);
  bool isDefinedModName() const;
  void replaceModuleName(const std::string modName);

private:
  std::string filename;
  AstNodeTypeEnum astNodeType;
  AstNode *next;
  AstNode *child;
  AstNode *prev;
  const std::string defaultPkgName;
  std::string packageName;
  const std::string defaultModName;
  std::string moduleName;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif