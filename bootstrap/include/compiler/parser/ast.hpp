#ifndef _COMPILER_PARSER_AST_
#define _COMPILER_PARSER_AST_
#include "compiler/common/location.hpp"
#include "compiler/llvm/ir_gen_context.hpp"
#include "compiler/parser/ast_node_type.hpp"
#include <cstdint>
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
  virtual void printNode(const size_t depth, const bool isVerbose) = 0;
  virtual void generateLlvmIr(LLVM::IrGenContext *const context) = 0;
  virtual bool hasParent() const = 0;
  virtual bool hasPrev() const = 0;
  virtual bool hasNext() const = 0;
  virtual bool hasChild() const = 0;
  virtual AstNode *rootNode() = 0;
  virtual AstNode *moduleNode() = 0;
  virtual AstNode *parentNode() = 0;
  virtual AstNode *prevNode() = 0;
  virtual AstNode *nextNode() = 0;
  virtual AstNode *childNode() = 0;
  virtual AstNode *putParentNode(AstNode *const node) = 0;
  virtual AstNode *putPrevNode(AstNode *const node) = 0;
  virtual AstNode *putNextNode(AstNode *const node) = 0;
  virtual AstNode *putChildNode(AstNode *const node) = 0;
  static void indentDepth(const size_t depth);
  static void indentDepth(const size_t depth, const bool isPrintNodeType);
};

// Children classes of AstNode is Split into separate files

class Ast {
public:
  Ast(const AstNodeTypeEnum nodeType);
  ~Ast() {};
  Ast(const Ast &rhs);
  Ast &operator=(const Ast &rhs);
  AstNode *getRoot();
  void printAst(const bool isVerbose);

private:
  AstNode *root;
};

class AstNodeQueue {
public:
  AstNodeQueue(const size_t depth, AstNode *const node);
  AstNodeQueue(const size_t depth, AstNode *const node, const bool isVerbose);
  ~AstNodeQueue() {};
  AstNodeQueue(const AstNodeQueue &rhs);
  AstNodeQueue &operator=(const AstNodeQueue &rhs);
  void printNode();
  void generateLlvmIr(LLVM::IrGenContext *const context);
  static std::vector<AstNodeQueue> queueingAstNode(Ast *const ast);
  static std::vector<AstNodeQueue> queueingAstNode(Ast *const ast,
                                                   const bool isVerbose);

private:
  size_t depth;
  AstNode *node;
  bool isVerbose;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif