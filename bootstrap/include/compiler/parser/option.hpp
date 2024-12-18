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
  bool isWithCommentOutAll();
  bool isWithCommentOutForDoc();
  void setWithCommentOutAll(const bool withCommentOutAll_);
  void setWithCommentOutForDoc(const bool withCommentOutForDoc_);

private:
  bool withCommentOutAll;
  bool withCommentOutForDoc;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif