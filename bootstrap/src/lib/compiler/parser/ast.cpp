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
  std::vector<AstNodeQueue> queue =
      AstNodeQueue::queueingAstNode(this, isVerbose_);
  for (AstNodeQueue node : queue) {
    node.printNode();
  }
};

AstNodeQueue::AstNodeQueue(const size_t depth_, AstNode *const node_)
    : depth(depth_), node(node_), isVerbose(false) {};
AstNodeQueue::AstNodeQueue(const size_t depth_, AstNode *const node_,
                           const bool isVerbose_)
    : depth(depth_), node(node_), isVerbose(isVerbose_) {};
AstNodeQueue::AstNodeQueue(const AstNodeQueue &rhs)
    : depth(rhs.depth), node(rhs.node), isVerbose(rhs.isVerbose) {};
AstNodeQueue &AstNodeQueue::operator=(const AstNodeQueue &rhs) {
  depth = rhs.depth;
  node = rhs.node;
  isVerbose = rhs.isVerbose;
  return *this;
};

void AstNodeQueue::printNode() { node->printNode(depth, isVerbose); };
void AstNodeQueue::generateLlvmIr(LLVM::IrGenContext *const context_) {
  node->generateLlvmIr(context_);
};


std::vector<AstNodeQueue> AstNodeQueue::queueingAstNode(Ast *const ast_) {
  return queueingAstNode(ast_);
}
std::vector<AstNodeQueue> AstNodeQueue::queueingAstNode(Ast *const ast_,
                                                        const bool isVerbose_) {
  std::vector<AstNodeQueue> queue;
  AstNode *root = ast_->getRoot();
  queue.push_back(AstNodeQueue(0, root, isVerbose_));
  bool hasParentNext = false;
  AstNode *currentNode = root;
  size_t depth = 0;
  if (root->hasChild()) {
    depth++;
    currentNode = root->childNode();
    queue.push_back(AstNodeQueue(depth, currentNode, isVerbose_));
    while (currentNode != root) {
      if (currentNode->hasChild()) {
        depth++;
        currentNode = currentNode->childNode();
        queue.push_back(AstNodeQueue(depth, currentNode, isVerbose_));
        continue;
      }
      if (currentNode->hasNext()) {
        currentNode = currentNode->nextNode();
        queue.push_back(AstNodeQueue(depth, currentNode, isVerbose_));
        continue;
      }
      break;
    }
  }
  return queue;
};