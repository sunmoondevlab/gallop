// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_PRE_PARSE_VALUE_
#define _COMPILER_MODEL_PRE_PARSE_VALUE_

#include <cstdint>

namespace gallop {
namespace Compiler {

enum class PreParseValueTypeEnum : uint32_t {
  none,
  escapeCharCode,
  number,
};

class PreParseValue {
public:
  PreParseValue();
  PreParseValue(const int32_t &charCode);
  ~PreParseValue() {};
  PreParseValue(const PreParseValue &rhs);
  PreParseValue &operator=(const PreParseValue &rhs);
  int32_t *escapeUtf32CharCode();

private:
  PreParseValueTypeEnum preParseValueType;
  typedef union UPreParseValue {
    int32_t ecU32c;
    UPreParseValue() {};
    UPreParseValue(const int32_t &escapeCharCode) : ecU32c(escapeCharCode) {};
  } UPreParseValue;
  UPreParseValue preParseValue;
};

} // namespace Compiler
} // namespace gallop
#endif