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
  void setWithCommentOutAll(const bool withCommentOutAll);
  void setWithCommentOutForDoc(const bool withCommentOutForDoc);

private:
  bool withCommentOutAll;
  bool withCommentOutForDoc;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif