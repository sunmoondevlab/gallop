// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_NODE_MODULE_
#define _COMPILER_PARSER_AST_NODE_MODULE_
#include "compiler/model/location.hpp"
#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node_type.hpp"
#include <llvm/IR/Module.h>

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
  virtual llvm::Value *
  generateLlvmIr(LLVM::IrGenContext *const context) override = 0;
  virtual bool hasParent() const override = 0;
  virtual bool hasPrev() const override = 0;
  virtual bool hasNext() const override = 0;
  virtual bool hasChild() const override = 0;
  virtual AstNode *getRoot() override = 0;
  virtual AstNode *getModule() override = 0;
  virtual AstNode *getParent() override = 0;
  virtual AstNode *getPrev() override = 0;
  virtual AstNode *getNext() override = 0;
  virtual AstNode *getChild() override = 0;
  virtual AstNode *setParent(AstNode *const node) override = 0;
  virtual AstNode *setPrev(AstNode *const node) override = 0;
  virtual AstNode *setNext(AstNode *const node) override = 0;
  virtual AstNode *setChild(AstNode *const node) override = 0;
  virtual AstNode *getLastModuleNode() = 0;
  virtual bool isDefinedPackageName() const = 0;
  virtual void replacePackageName(const std::string pkgName) = 0;
  virtual bool isDefinedModuleName() const = 0;
  virtual void replaceModuleName(const std::string modName) = 0;
  virtual std::string getFullModuleName() const = 0;
  virtual llvm::Module *getLlvmModule() = 0;

private:
  virtual bool settableChild(AstNode *const node) const override = 0;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif