#ifndef _COMPILER_LLVM_OPTION_
#define _COMPILER_LLVM_OPTION_
#include <string>
namespace gallop {
namespace Compiler {
namespace LLVM {

class Option {
public:
  Option();
  ~Option() {};
  Option(const Option &rhs);
  Option &operator=(const Option &rhs);
  std::string getEntryPointId() const;
  void setEntryPointId(const std::string entryPointId);

private:
  std::string entryPointId;
};

} // namespace LLVM
} // namespace Compiler
} // namespace gallop
#endif