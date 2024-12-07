// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_VALUE_TYPE_
#define _COMPILER_MODEL_VALUE_TYPE_

#include "compiler/model/const_for_type_enum.hpp"

#include <cstdint>
#include <map>
#include <string>

namespace gallop {
namespace Compiler {

enum class ValueTypeCategoryEnum : uint8_t {
  typeNumber = 1,
  typeBool,
  typeString,
  typeList,
  typeMap,
  typeStruct,
  typeVoid,
};
enum class ValueTypeEnum : uint32_t {
  // unknown
  unknown = 0,
  // number
  typeNumberI4 = (static_cast<uint8_t>(ValueTypeCategoryEnum::typeNumber)
                  << ConstForTypeEnum::BitShift) +
                 1,
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
  typeBool = (static_cast<uint8_t>(ValueTypeCategoryEnum::typeBool)
              << ConstForTypeEnum::BitShift) +
             1,
  // string
  typeString = (static_cast<uint8_t>(ValueTypeCategoryEnum::typeString)
                << ConstForTypeEnum::BitShift) +
               1,
  // list
  typeList = (static_cast<uint8_t>(ValueTypeCategoryEnum::typeList)
              << ConstForTypeEnum::BitShift) +
             1,
  // list
  typeMap = (static_cast<uint8_t>(ValueTypeCategoryEnum::typeMap)
             << ConstForTypeEnum::BitShift) +
            1,
  // struct
  typeStruct = (static_cast<uint8_t>(ValueTypeCategoryEnum::typeStruct)
                << ConstForTypeEnum::BitShift) +
               1,
  typeStructUnion,
  // void
  typeVoid = (static_cast<uint8_t>(ValueTypeCategoryEnum::typeVoid)
              << ConstForTypeEnum::BitShift) +
             1,
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

} // namespace Compiler
} // namespace gallop
#endif