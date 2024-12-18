#include "compiler/parser/ast.hpp"
#include "compiler/parser/ast_node/root.hpp"
#include <llvm/Support/raw_ostream.h>

using namespace gallop::Compiler::Parser;

void AstNode::indentDepth(const size_t depth_) {
  for (size_t indent = 0; indent < depth_; indent++) {
    llvm::outs() << "  ";
  };
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
  root->printAstNode(0, isVerbose_);
};
