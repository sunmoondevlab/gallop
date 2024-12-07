// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_OPTION_
#define _COMPILER_PARSER_OPTION_
namespace gallop {
namespace Compiler {
namespace Parser {

class Option {
public:
  Option();
  ~Option() {};
  Option(const Option &rhs);
  Option &operator=(const Option &rhs);
  bool isWithCommentOutAll() const;
  bool isWithCommentOutForDoc() const;
  void setWithCommentOutAll();
  void setWithCommentOutForDoc();

private:
  bool withCommentOutAll;
  bool withCommentOutForDoc;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif