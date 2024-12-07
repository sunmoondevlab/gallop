// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_OPTION_LLVM_
#define _COMPILER_OPTION_LLVM_

#include "io/file/file.hpp"

#include <string>

namespace gallop {
namespace Compiler {
namespace Option {

class LLVM {
public:
  LLVM();
  ~LLVM() {};
  LLVM(const LLVM &rhs);
  LLVM &operator=(const LLVM &rhs);
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

} // namespace Option
} // namespace Compiler
} // namespace gallop
#endif