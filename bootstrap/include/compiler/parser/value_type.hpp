// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_PARSER_VALUE_TYPE_
#define _COMPILER_PARSER_VALUE_TYPE_

#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {
namespace Parser {

namespace ValueTypeCategoryEnum {
static const uint8_t typeNumber = 1;
static const uint8_t typeBool = 2;
static const uint8_t typeString = 3;
static const uint8_t typeList = 4;
static const uint8_t typeMap = 5;
static const uint8_t typeStruct = 6;
static const uint8_t typeVoid = 7;

} // namespace ValueTypeCategoryEnum
enum class ValueTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  // number
  typeNumberI4 = (ValueTypeCategoryEnum::typeNumber << 24) + 1,
  typeNumberI8,
  typeNumberI16,
  typeNumberI32,
  typeNumberI64,
  typeNumberU4,
  typeNumberU8,
  typeNumberU16,
  typeNumberU32,
  typeNumberU64,
  typeNumberF16,
  typeNumberF32,
  typeNumberF64,
  typeNumberD16,
  typeNumberD32,
  typeNumberD64,
  typeNumberCharCode,
  // bool
  typeBool = (ValueTypeCategoryEnum::typeBool << 24) + 1,
  // string
  typeString = (ValueTypeCategoryEnum::typeString << 24) + 1,
  // list
  typeList = (ValueTypeCategoryEnum::typeList << 24) + 1,
  // list
  typeMap = (ValueTypeCategoryEnum::typeMap << 24) + 1,
  // struct
  typeStruct = (ValueTypeCategoryEnum::typeStruct << 24) + 1,
  typeStructUnion,
  // void
  typeVoid = (ValueTypeCategoryEnum::typeVoid << 24) + 1,
};

class ValueType final {
public:
  ValueType() = delete;
  ~ValueType() = delete;
  static std::string getString(const enum ValueTypeEnum &valueType);
  static ValueTypeEnum getNumberType(const std::string &valueTypeStr);
  static ValueTypeEnum getValueType(const std::string &valueTypeStr);
  static bool isInteger(const ValueTypeEnum &valueType);
  static bool isSignedInteger(const ValueTypeEnum &valueType);
  static bool isUnsignedInteger(const ValueTypeEnum &valueType);
  static bool isFloat(const ValueTypeEnum &valueType);
  static bool isDecimal(const ValueTypeEnum &valueType);
  static bool isCharCode(const ValueTypeEnum &valueType);
  static bool isNumber(const ValueTypeEnum &valueType);
  static bool isString(const ValueTypeEnum &valueType);
  static bool isList(const ValueTypeEnum &valueType);
  static bool isMap(const ValueTypeEnum &valueType);
  static bool isStruct(const ValueTypeEnum &valueType);
  static bool isUnion(const ValueTypeEnum &valueType);
  static std::string
  getValueTypeWrapperObjectName(const ValueTypeEnum &valueType);

private:
  static const std::map<ValueTypeEnum, std::string> _map;
  static const std::map<std::string, ValueTypeEnum> _numberTypeMap;
  static const std::map<std::string, ValueTypeEnum> _typeMap;
};

} // namespace Parser
} // namespace Compiler
} // namespace gallop
#endif