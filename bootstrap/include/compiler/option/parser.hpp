// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_OPTION_PARSER_
#define _COMPILER_OPTION_PARSER_

namespace gallop {
namespace Compiler {
namespace Option {

class Parser {
public:
  Parser();
  ~Parser() {};
  Parser(const Parser &rhs);
  Parser &operator=(const Parser &rhs);
  bool isWithCommentOutAll() const;
  bool isWithCommentOutForDoc() const;
  void setWithCommentOutAll();
  void setWithCommentOutForDoc();

private:
  bool withCommentOutAll;
  bool withCommentOutForDoc;
};

} // namespace Option
} // namespace Compiler
} // namespace gallop
#endif