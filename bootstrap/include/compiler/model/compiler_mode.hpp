// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_COMPILER_MODE_
#define _COMPILER_MODEL_COMPILER_MODE_

#include <cstdint>

namespace gallop {
namespace Compiler {

enum class CompilerModeEnum : uint8_t {
  interpreter = 1,
  compilerFromStdin,
  compilerFromFile,
};

} // namespace Compiler
} // namespace gallop
#endif