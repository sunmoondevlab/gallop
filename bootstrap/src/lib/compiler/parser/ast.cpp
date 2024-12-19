#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler::Parser;

void AstNode::indentDepth(const size_t depth_) { indentDepth(depth_, false); };
void AstNode::indentDepth(const size_t depth_, const bool isPrintNodeType_) {
  if (depth_ > 1) {
    for (size_t indent = 0; indent < depth_ - 1; indent++) {
      llvm::outs() << "    ";
    };
  }
  if (depth_ > 0) {
    if (isPrintNodeType_) {
      llvm::outs() << " => ";
    } else {
      llvm::outs() << "|-> ";
    }
  }
};

PrintableAstNode::PrintableAstNode(const size_t depth_, AstNode *const node_,
                                   const bool isVerbose_)
    : depth(depth_), node(node_), isVerbose(isVerbose_) {};

PrintableAstNode::PrintableAstNode(const PrintableAstNode &rhs)
    : depth(rhs.depth), node(rhs.node), isVerbose(rhs.isVerbose) {};
PrintableAstNode &PrintableAstNode::operator=(const PrintableAstNode &rhs) {
  depth = rhs.depth;
  node = rhs.node;
  isVerbose = rhs.isVerbose;
  return *this;
};

void PrintableAstNode::printNode() { node->printNode(depth, isVerbose); };

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
  std::vector<PrintableAstNode> queue = queueingPrintableAstNode(isVerbose_);
  for (PrintableAstNode node : queue) {
    node.printNode();
  }
};

std::vector<PrintableAstNode>
Ast::queueingPrintableAstNode(const bool isVerbose_) const {
  std::vector<PrintableAstNode> queue;
  queue.push_back(PrintableAstNode(0, root, isVerbose_));
  bool hasParentNext = false;
  AstNode *currentNode = root;
  size_t depth = 0;
  if (root->hasChild()) {
    depth++;
    currentNode = root->childNode();
    queue.push_back(PrintableAstNode(depth, currentNode, isVerbose_));
    while (currentNode != root) {
      if (currentNode->hasChild()) {
        depth++;
        currentNode = currentNode->childNode();
        queue.push_back(PrintableAstNode(depth, currentNode, isVerbose_));
        continue;
      }
      if (currentNode->hasNext()) {
        currentNode = currentNode->nextNode();
        queue.push_back(PrintableAstNode(depth, currentNode, isVerbose_));
        continue;
      }
      break;
    }
  }
  return queue;
};
