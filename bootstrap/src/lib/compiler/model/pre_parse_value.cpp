// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/pre_parse_value.hpp"

using namespace gallop::Compiler;

PreParseValue::PreParseValue()
    : preParseValueType(PreParseValueTypeEnum::none), preParseValue(0) {};
PreParseValue::PreParseValue(const int32_t &escapeCharCode_)
    : preParseValueType(PreParseValueTypeEnum::escapeCharCode),
      preParseValue(PreParseValue::UPreParseValue(escapeCharCode_)) {};
PreParseValue::PreParseValue(const PreParseValue &rhs)
    : preParseValueType(rhs.preParseValueType),
      preParseValue(rhs.preParseValue) {};
PreParseValue &PreParseValue::operator=(const PreParseValue &rhs) {
  preParseValueType = rhs.preParseValueType;
  preParseValue = rhs.preParseValue;
  return *this;
};
int32_t *PreParseValue::escapeUtf32CharCode() {
  if (preParseValueType != PreParseValueTypeEnum::escapeCharCode) {
    return nullptr;
  }
  return new int(preParseValue.ecU32c);
};
