#include "compiler/parser/printable_ast.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler::Parser;

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
