#ifndef _COMPILER_PARSER_PRINTABLE_AST_
#define _COMPILER_PARSER_PRINTABLE_AST_
#include "compiler/parser/ast.hpp"
#include <cstdint>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Parser {

class PritableAstNode {
public:
  PritableAstNode(const size_t depth, AstNode *const node,
                  const bool isVerbose);
  ~PritableAstNode() {};
  PritableAstNode(const PritableAstNode &rhs);
  PritableAstNode &operator=(const PritableAstNode &rhs);
  void printNode();

private:
  size_t depth;
  AstNode *node;
  bool isVerbose;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop

#endif