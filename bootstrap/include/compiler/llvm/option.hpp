// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
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
  std::string getSrcRootDir() const;
  std::string getDstRootDir() const;
  void setEntryPointId(const std::string entryPointId);
  void setSrcRootDir(const std::string srcRootDir);
  void setDstRootDir(const std::string dstRootDir);

private:
  std::string entryPointId;
  std::string srcRootDir;
  std::string dstRootDir;
};

} // namespace LLVM
} // namespace Compiler
} // namespace gallop
#endif