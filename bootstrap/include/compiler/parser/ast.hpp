// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_AST_
#define _COMPILER_PARSER_AST_

#include "compiler/llvm/ir_gen_context.hpp"
#include "compiler/model/location.hpp"
#include "compiler/parser/ast_node_type.hpp"
#include <cstdint>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class AstNode {
public:
  virtual ~AstNode() {};
  virtual Location getLocation() const = 0;
  virtual AstNodeTypeEnum getAstNodeType() const = 0;
  virtual std::string getAstNodeTypeString() const = 0;
  virtual void printNode(const size_t &depth, const bool &isVerbose) = 0;
  virtual llvm::Value *generateLlvmIr(LLVM::IrGenContext *const context) = 0;
  virtual bool hasParent() const = 0;
  virtual bool hasPrev() const = 0;
  virtual bool hasNext() const = 0;
  virtual bool hasChild() const = 0;
  virtual AstNode *getRoot() = 0;
  virtual AstNode *getModule() = 0;
  virtual AstNode *getParent() = 0;
  virtual AstNode *getPrev() = 0;
  virtual AstNode *getNext() = 0;
  virtual AstNode *getChild() = 0;
  virtual AstNode *setParent(AstNode *const node) = 0;
  virtual AstNode *setPrev(AstNode *const node) = 0;
  virtual AstNode *setNext(AstNode *const node) = 0;
  virtual AstNode *setChild(AstNode *const node) = 0;
  static void indentDepth(const size_t &depth);
  static void indentDepth(const size_t &depth, const bool &isPrintNodeType);

private:
  virtual bool settableChild(AstNode *const node) const = 0;
};

// Children classes of AstNode is Split into separate files

class Ast {
public:
  Ast(const AstNodeTypeEnum nodeType);
  ~Ast() {};
  Ast(const Ast &rhs);
  Ast &operator=(const Ast &rhs);
  AstNode *getRoot();
  void printAst(const bool &isVerbose);

private:
  AstNode *root;
};

class AstNodeQueue {
public:
  AstNodeQueue(const size_t &depth, AstNode *const node);
  AstNodeQueue(const size_t &depth, AstNode *const node, const bool &isVerbose);
  ~AstNodeQueue() {};
  AstNodeQueue(const AstNodeQueue &rhs);
  AstNodeQueue &operator=(const AstNodeQueue &rhs);
  void printNode();
  void generateLlvmIr(LLVM::IrGenContext *const context);
  static std::vector<AstNodeQueue> queueingAstNode(Ast *const ast,
                                                   const bool &isVerbose);
  static std::vector<AstNodeQueue>
  queueingAstNode(Ast *const ast, LLVM::IrGenContext *const context);

private:
  size_t depth;
  AstNode *node;
  bool isVerbose;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif