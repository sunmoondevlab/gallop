#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler::Parser;

void AstNode::indentDepth(const size_t depth_) {
  for (size_t indent = 0; indent < depth_; indent++) {
    llvm::outs() << "  ";
  };
};

PritableAstNode::PritableAstNode(const size_t depth_, AstNode *const node_,
                                 const bool isVerbose_)
    : depth(depth_), node(node_), isVerbose(isVerbose_) {};

PritableAstNode::PritableAstNode(const PritableAstNode &rhs)
    : depth(rhs.depth), node(rhs.node), isVerbose(rhs.isVerbose) {};
PritableAstNode &PritableAstNode::operator=(const PritableAstNode &rhs) {
  depth = rhs.depth;
  node = rhs.node;
  isVerbose = rhs.isVerbose;
  return *this;
};

void PritableAstNode::printNode() { node->printNode(depth, isVerbose); };

Ast::Ast(const AstNodeTypeEnum nodeType_) {
  root = new AstNodeRoot(nodeType_);
};
Ast::Ast(const Ast &rhs) : root(rhs.root) {};
Ast &Ast::operator=(const Ast &rhs) {
  root = rhs.root;
  return *this;
};

AstNode *Ast::getRoot() { return root; }

void Ast::printAst(const bool isVerbose_) {
  std::vector<AstNode *> queue = queueingPrintableAstNode();
  root->printNode(0, isVerbose_);
};

std::vector<AstNode *> Ast::queueingPrintableAstNode() const {
  std::vector<AstNode *> queue;
  queue.push_back(root);
  bool hasParentNext = false;
  AstNode *currentNode = root;
  if (root->hasChild()) {
    currentNode = root->childNode();
    queue.push_back(currentNode);
  }
  return queue;
};
