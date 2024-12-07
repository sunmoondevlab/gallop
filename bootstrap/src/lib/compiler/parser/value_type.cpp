// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/parser/value_type.hpp"
#include "compiler/parser/package_name.hpp"

using namespace gallop::Compiler::Parser;

const std::map<ValueTypeEnum, std::string> ValueType::_map = {
    // unknown
    {ValueTypeEnum::unknown, "Unknown"},
    // number
    {ValueTypeEnum::typeNumberI4, "i4"},
    {ValueTypeEnum::typeNumberI8, "i8"},
    {ValueTypeEnum::typeNumberI16, "i16"},
    {ValueTypeEnum::typeNumberI32, "i32"},
    {ValueTypeEnum::typeNumberI64, "i64"},
    {ValueTypeEnum::typeNumberU4, "u4"},
    {ValueTypeEnum::typeNumberU8, "u8"},
    {ValueTypeEnum::typeNumberU16, "u16"},
    {ValueTypeEnum::typeNumberU32, "u32"},
    {ValueTypeEnum::typeNumberU64, "u64"},
    {ValueTypeEnum::typeNumberF16, "f16"},
    {ValueTypeEnum::typeNumberF32, "f32"},
    {ValueTypeEnum::typeNumberF64, "f64"},
    {ValueTypeEnum::typeNumberD16, "d16"},
    {ValueTypeEnum::typeNumberD32, "d32"},
    {ValueTypeEnum::typeNumberD64, "d64"},
    {ValueTypeEnum::typeNumberCharCode, "charCode"},
    // bool
    {ValueTypeEnum::typeBool, "bool"},
    // string
    {ValueTypeEnum::typeString, "string"},
    // list
    {ValueTypeEnum::typeList, "list"},
    // list
    {ValueTypeEnum::typeMap, "map"},
    // struct
    {ValueTypeEnum::typeStruct, "struct"},
    {ValueTypeEnum::typeStructUnion, "union"},
    // void
    {ValueTypeEnum::typeVoid, "void"},
};
std::string ValueType::getString(const enum ValueTypeEnum &valueType_) {
  if (_map.count(valueType_)) {
    return _map.at(valueType_);
  } else {
    return _map.at(ValueTypeEnum::unknown);
  }
};

const std::map<std::string, ValueTypeEnum> ValueType::_numberTypeMap{
    {"i4", ValueTypeEnum::typeNumberI4},
    {"i8", ValueTypeEnum::typeNumberI8},
    {"i16", ValueTypeEnum::typeNumberI16},
    {"i32", ValueTypeEnum::typeNumberI32},
    {"i64", ValueTypeEnum::typeNumberI64},
    {"u4", ValueTypeEnum::typeNumberU4},
    {"u8", ValueTypeEnum::typeNumberU8},
    {"u16", ValueTypeEnum::typeNumberU16},
    {"u32", ValueTypeEnum::typeNumberU32},
    {"u64", ValueTypeEnum::typeNumberU64},
    {"f16", ValueTypeEnum::typeNumberF16},
    {"f32", ValueTypeEnum::typeNumberF32},
    {"f64", ValueTypeEnum::typeNumberF64},
    {"d16", ValueTypeEnum::typeNumberD16},
    {"d32", ValueTypeEnum::typeNumberD32},
    {"d64", ValueTypeEnum::typeNumberD64},
};

ValueTypeEnum ValueType::getNumberType(const std::string &valueTypeStr_) {
  if (_numberTypeMap.count(valueTypeStr_) == 0) {
    return ValueTypeEnum::unknown;
  } else {
    return _numberTypeMap.at(valueTypeStr_);
  }
};

const std::map<std::string, ValueTypeEnum> ValueType::_typeMap{
    {"i4", ValueTypeEnum::typeNumberI4},
    {"i8", ValueTypeEnum::typeNumberI8},
    {"i16", ValueTypeEnum::typeNumberI16},
    {"i32", ValueTypeEnum::typeNumberI32},
    {"i64", ValueTypeEnum::typeNumberI64},
    {"u4", ValueTypeEnum::typeNumberU4},
    {"u8", ValueTypeEnum::typeNumberU8},
    {"u16", ValueTypeEnum::typeNumberU16},
    {"u32", ValueTypeEnum::typeNumberU32},
    {"u64", ValueTypeEnum::typeNumberU64},
    {"f16", ValueTypeEnum::typeNumberF16},
    {"f32", ValueTypeEnum::typeNumberF32},
    {"f64", ValueTypeEnum::typeNumberF64},
    {"d16", ValueTypeEnum::typeNumberD16},
    {"d32", ValueTypeEnum::typeNumberD32},
    {"d64", ValueTypeEnum::typeNumberD64},
    {"charCode", ValueTypeEnum::typeNumberCharCode},
    {"bool", ValueTypeEnum::typeBool},
    {"string", ValueTypeEnum::typeString},
    {"list", ValueTypeEnum::typeList},
    {"map", ValueTypeEnum::typeMap},
    {"struct", ValueTypeEnum::typeStruct},
    {"union", ValueTypeEnum::typeStructUnion},
    {"void", ValueTypeEnum::typeVoid},
};

ValueTypeEnum ValueType::getValueType(const std::string &valueTypeStr_) {
  if (_typeMap.count(valueTypeStr_) == 0) {
    return ValueTypeEnum::unknown;
  } else {
    return _typeMap.at(valueTypeStr_);
  }
};

bool ValueType::isInteger(const ValueTypeEnum &valueType_) {
  return isSignedInteger(valueType_) || isUnsignedInteger(valueType_);
};
bool ValueType::isSignedInteger(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeNumberI4 ||
         valueType_ == ValueTypeEnum::typeNumberI8 ||
         valueType_ == ValueTypeEnum::typeNumberI16 ||
         valueType_ == ValueTypeEnum::typeNumberI32 ||
         valueType_ == ValueTypeEnum::typeNumberI64;
};
bool ValueType::isUnsignedInteger(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeNumberU4 ||
         valueType_ == ValueTypeEnum::typeNumberU8 ||
         valueType_ == ValueTypeEnum::typeNumberU16 ||
         valueType_ == ValueTypeEnum::typeNumberU32 ||
         valueType_ == ValueTypeEnum::typeNumberU64;
};
bool ValueType::isFloat(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeNumberF16 ||
         valueType_ == ValueTypeEnum::typeNumberF32 ||
         valueType_ == ValueTypeEnum::typeNumberF64;
};
bool ValueType::isDecimal(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeNumberD16 ||
         valueType_ == ValueTypeEnum::typeNumberD32 ||
         valueType_ == ValueTypeEnum::typeNumberD64;
};
bool ValueType::isCharCode(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeNumberCharCode;
};
bool ValueType::isNumber(const ValueTypeEnum &valueType_) {
  return isInteger(valueType_) || isFloat(valueType_) ||
         isDecimal(valueType_) || isCharCode(valueType_);
};
bool ValueType::isString(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeString;
};
bool ValueType::isList(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeList;
};
bool ValueType::isMap(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeMap;
};
bool ValueType::isStruct(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeStruct;
};
bool ValueType::isUnion(const ValueTypeEnum &valueType_) {
  return valueType_ == ValueTypeEnum::typeStructUnion;
};
std::string
ValueType::getValueTypeWrapperObjectName(const ValueTypeEnum &valueType_) {
  if (isInteger(valueType_)) {
    return PackageName::gallopLangTypes + ".Integer";
  }
  if (isFloat(valueType_)) {
    return PackageName::gallopLangTypes + ".Float";
  }
  if (isDecimal(valueType_)) {
    return PackageName::gallopLangTypes + ".Decimal";
  }
  if (isCharCode(valueType_)) {
    return PackageName::gallopLangTypes + ".CharCode";
  }
  if (isString(valueType_)) {
    return PackageName::gallopLangTypes + ".String";
  }
  if (isList(valueType_)) {
    return PackageName::gallopLangTypes + ".List";
  }
  if (isMap(valueType_)) {
    return PackageName::gallopLangTypes + ".Map";
  }
  return "";
};
