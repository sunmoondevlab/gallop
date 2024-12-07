// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _MATH_BIG_UINT_
#define _MATH_BIG_UINT_

#include <cmath>
#include <cstdint>
#include <vector>

namespace gallop {
namespace Math {

class BigUint {
public:
  BigUint(const uint64_t &val);
  BigUint(const std::u32string &valStr, const uint8_t &radix);
  BigUint(const std::u32string &valStr, const uint8_t &radix,
          const int32_t &numberFormatDelimiter);
  BigUint(const std::u32string &valStr, const uint8_t &radix,
          const int32_t &numberFormatDelimiter, const bool &isLowerPrefer);
  BigUint(const std::vector<int32_t> &valData, const uint8_t &radix);
  BigUint(const std::vector<int32_t> &valData, const uint8_t &radix,
          const int32_t &numberFormatDelimiter);
  BigUint(const std::vector<int32_t> &valData, const uint8_t &radix,
          const int32_t &numberFormatDelimiter, const bool &isLowerPrefer);
  ~BigUint() {};
  BigUint(const BigUint &rhs);
  BigUint &operator=(const BigUint &rhs);
  BigUint operator+(const BigUint &rhs);
  BigUint &operator+=(const BigUint &rhs);
  BigUint operator-(const BigUint &rhs);
  BigUint &operator-=(const BigUint &rhs);
  BigUint operator*(const BigUint &rhs);
  BigUint &operator*=(const BigUint &rhs);
  BigUint operator/(const BigUint &rhs);
  BigUint &operator/=(const BigUint &rhs);
  BigUint operator%(const BigUint &rhs);
  BigUint &operator%=(const BigUint &rhs);
  BigUint operator<<(const uint32_t &bits);
  BigUint &operator<<=(const uint32_t &bits);
  BigUint operator>>(const uint32_t &bits);
  BigUint &operator>>=(const uint32_t &bits);
  BigUint operator|(const BigUint &rhs);
  BigUint &operator|=(const BigUint &rhs);
  BigUint operator&(const BigUint &rhs);
  BigUint &operator&=(const BigUint &rhs);
  BigUint operator^(const BigUint &rhs);
  BigUint &operator^=(const BigUint &rhs);
  BigUint operator~();
  BigUint &operator++();
  BigUint &operator--();
  bool operator<(const BigUint &rhs);
  bool operator<=(const BigUint &rhs);
  bool operator>(const BigUint &rhs);
  bool operator>=(const BigUint &rhs);
  bool operator==(const BigUint &rhs);
  bool operator!=(const BigUint &rhs);
  std::vector<uint32_t> getChunks() const;
  uint32_t getBitLength() const;
  uint32_t getOctalDigitLength() const;
  uint32_t getDecimalDigitLength() const;
  uint32_t getHexadecimalDigitLength() const;
  uint32_t getDigitLengthByRadix(const uint8_t &radix) const;
  static const uint32_t MaxBitLength = 8388607;
  std::string toBinaryString() const;
  std::string toBinaryString(const uint32_t &rightAlignLength) const;
  std::string toBinaryString(const uint32_t &rightAlignLength,
                             const uint8_t &formatChunkLength) const;
  std::string toBinaryString(const uint32_t &rightAlignLength,
                             const uint8_t &formatChunkLength,
                             const uint8_t &numberFormatDelimiter) const;
  std::string toBinaryString(const uint32_t &rightAlignLength,
                             const uint8_t &formatChunkLength,
                             const uint8_t &numberFormatDelimiter,
                             const bool &hasPrefix) const;
  std::string toBinaryString(const uint32_t &rightAlignLength,
                             const uint8_t &formatChunkLength,
                             const uint8_t &numberFormatDelimiter,
                             const bool &hasPrefix,
                             const bool &hasPaddingZero) const;
  std::string toOctalString() const;
  std::string toOctalString(const uint32_t &rightAlignLength) const;
  std::string toOctalString(const uint32_t &rightAlignLength,
                            const uint8_t &formatChunkLength) const;
  std::string toOctalString(const uint32_t &rightAlignLength,
                            const uint8_t &formatChunkLength,
                            const uint8_t &numberFormatDelimiter) const;
  std::string toOctalString(const uint32_t &rightAlignLength,
                            const uint8_t &formatChunkLength,
                            const uint8_t &numberFormatDelimiter,
                            const bool &hasPrefix) const;
  std::string toOctalString(const uint32_t &rightAlignLength,
                            const uint8_t &formatChunkLength,
                            const uint8_t &numberFormatDelimiter,
                            const bool &hasPrefix,
                            const bool &hasPaddingZero) const;
  std::string toDecimalString() const;
  std::string toDecimalString(const uint8_t &rightAlignLength) const;
  std::string toDecimalString(const uint32_t &rightAlignLength,
                              const uint8_t &formatChunkLength) const;
  std::string toDecimalString(const uint32_t &rightAlignLength,
                              const uint8_t &formatChunkLength,
                              const uint8_t &numberFormatDelimiter) const;
  std::string toDecimalString(const uint32_t &rightAlignLength,
                              const uint8_t &formatChunkLength,
                              const uint8_t &numberFormatDelimiter,
                              const bool &hasPaddingZero) const;
  std::string toHexadecimalString() const;
  std::string toHexadecimalString(const uint32_t &rightAlignLength) const;
  std::string toHexadecimalString(const uint32_t &rightAlignLength,
                                  const uint8_t &formatChunkLength) const;
  std::string toHexadecimalString(const uint32_t &rightAlignLength,
                                  const uint8_t &formatChunkLength,
                                  const uint8_t &numberFormatDelimiter) const;
  std::string toHexadecimalString(const uint32_t &rightAlignLength,
                                  const uint8_t &formatChunkLength,
                                  const uint8_t &numberFormatDelimiter,
                                  const bool &hasPrefix) const;
  std::string toHexadecimalString(const uint32_t &rightAlignLength,
                                  const uint8_t &formatChunkLength,
                                  const uint8_t &numberFormatDelimiter,
                                  const bool &hasPrefix,
                                  const bool &hasPaddingZero) const;
  std::string toStringByRadix(const uint8_t &radix) const;
  std::string toStringByRadix(const uint8_t &radix,
                              const uint32_t &rightAlignLength) const;
  std::string toStringByRadix(const uint8_t &radix,
                              const uint32_t &rightAlignLength,
                              const uint8_t &formatChunkLength) const;
  std::string toStringByRadix(const uint8_t &radix,
                              const uint32_t &rightAlignLength,
                              const uint8_t &formatChunkLength,
                              const uint8_t &numberFormatDelimiter) const;
  std::string toStringByRadix(const uint8_t &radix,
                              const uint32_t &rightAlignLength,
                              const uint8_t &formatChunkLength,
                              const uint8_t &numberFormatDelimiter,
                              const bool &hasPaddingZero) const;

private:
  std::vector<uint32_t> chunks;
  uint32_t bitLength;
  BigUint();
  bool hasPrefixInValData(const std::vector<int32_t> &valData,
                          const uint8_t radix) const;
  uint32_t decideBitLength(const uint8_t &val) const;
  uint32_t decideBitLength(const uint64_t &val) const;
  uint32_t decideBitLength(const std::vector<uint32_t> &valChunks) const;
  uint32_t decideDigitLength(const uint64_t &bitLength, const uint8_t &radix,
                             const std::vector<uint32_t> &valChunks) const;
  std::vector<uint32_t> decideChunks(const uint64_t &val) const;
  std::vector<uint32_t> addCC(const std::vector<uint32_t> &lChunks,
                              const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> subCC(const std::vector<uint32_t> &lChunks,
                              const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> mulCC(const std::vector<uint32_t> &lChunks,
                              const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> mulUU(const uint32_t &lVal, const uint32_t &rVal) const;
  std::vector<uint32_t> mulCU(const std::vector<uint32_t> &lChunks,
                              const uint32_t &rVal) const;
  std::vector<uint32_t> mulCCSimple(const std::vector<uint32_t> &lChunks,
                                    const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> divCC(const std::vector<uint32_t> &lChunks,
                              const std::vector<uint32_t> &rChunks,
                              std::vector<uint32_t> &modulo) const;
  std::vector<uint32_t> divUU(const uint64_t &lVal, const uint64_t &rVal,
                              std::vector<uint32_t> &modulo) const;
  std::vector<uint32_t> divCU(const std::vector<uint32_t> &lChunks,
                              const uint32_t &rVal,
                              std::vector<uint32_t> &modulo) const;
  std::vector<uint32_t> divCCSimple(const std::vector<uint32_t> &lChunks,
                                    const std::vector<uint32_t> &rChunks,
                                    std::vector<uint32_t> &modulo) const;
  std::vector<uint32_t> shiftBitLeft(const std::vector<uint32_t> &lChunks,
                                     const uint32_t &shiftBits) const;
  std::vector<uint32_t> shiftBitRight(const std::vector<uint32_t> &lChunks,
                                      const uint32_t &shiftBits) const;
  std::vector<uint32_t> andCC(const std::vector<uint32_t> &lChunks,
                              const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> orCC(const std::vector<uint32_t> &lChunks,
                             const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> xorCC(const std::vector<uint32_t> &lChunks,
                              const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> cmplC(const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t>
  normalizeChunk(const std::vector<uint32_t> &rChunks) const;
  std::vector<uint32_t> digitWeightByRadix(const uint32_t &digitPosition,
                                           const uint8_t &radix) const;
  bool isPower2(const std::vector<uint32_t> &valChunks) const;
  bool isPower2(const uint32_t &val) const;
  bool isRadixPower2(const uint8_t &radix) const;
  bool isCarryUp(const uint32_t &lVal, const uint32_t &rVal,
                 const uint32_t &cuVal) const;
  int8_t compare(const std::vector<uint32_t> &lChunks,
                 const std::vector<uint32_t> &rChunks) const;
  void
  validateNumberFormatDelimiter(const int32_t &numberFormatDelimiter) const;
  static constexpr uint8_t MinRadix = 2;
  static constexpr uint8_t MaxRadix = 62;
  static constexpr uint8_t MinFormatLength = 2;
  static constexpr uint32_t U64Bit = 64;
  static constexpr uint32_t U32Bit = 32;
  static constexpr uint32_t U8Bit = 8;
  static constexpr uint32_t U64BitMaxPos = 63;
  static constexpr uint32_t U32BitMaxPos = 31;
  static constexpr uint32_t U8BitMaxPos = 7;
  static constexpr uint32_t U32ShiftBit = 5;
  static constexpr uint32_t U32BitMask = 0xffffffff;
  static constexpr uint64_t U64High32BitMask = 0xffffffff00000000;
  static constexpr uint32_t U4MaxOneDigit = 3;
  static constexpr uint32_t U2ShiftBit = 2;
  static constexpr uint32_t U4ShiftBit = 4;
  static constexpr uint32_t U32High4BitMask = 0xf0000000;
  static constexpr uint32_t U32High4RightShiftBit = 28;
  static constexpr uint64_t U32CarryDownBit = 0x100000000;
  static constexpr uint8_t HexStrPrefixLen = 0x02;
  static constexpr uint8_t MinHexAlpha = 0x0a;
  static constexpr uint8_t MaxHexadecimalCharLenPerChunk = 8;
  static constexpr std::string PrefixBinaryString = "0b";
  static constexpr std::string PrefixBinaryStringUpper = "0B";
  static constexpr std::string PrefixOctalString = "0o";
  static constexpr std::string PrefixOctalStringUpper = "0O";
  static constexpr std::string PrefixHexadecimalString = "0x";
  static constexpr std::string PrefixHexadecimalStringUpper = "0X";
};

} // namespace Math
} // namespace gallop
#endif