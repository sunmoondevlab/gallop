// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "math/big_uint.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"
#include "char_set/string/utf32_string.hpp"
#include "char_set/string/utf8_string.hpp"
#include "error/common_errors.hpp"

#include <algorithm>
#include <cmath>

using namespace gallop::Math;
using namespace gallop::Error;
using namespace gallop::CharSet;

BigUint::BigUint() : chunks(std::vector<uint32_t>()), bitLength(0) {};
BigUint::BigUint(const uint64_t &val_) : chunks(std::vector<uint32_t>()) {
  bitLength = decideBitLength(val_);
  chunks = decideChunks(val_);
};
BigUint::BigUint(const std::u32string &valStr_, const uint8_t &radix_)
    : BigUint(String::Utf32::toU32Data(valStr_), radix_, false) {};
BigUint::BigUint(const std::u32string &valStr_, const uint8_t &radix_,
                 const int32_t &numberFormatDelimiter_)
    : BigUint(String::Utf32::toU32Data(valStr_), radix_, numberFormatDelimiter_,
              false) {};
BigUint::BigUint(const std::u32string &valStr_, const uint8_t &radix_,
                 const int32_t &numberFormatDelimiter_,
                 const bool &isLowerPrefer_)
    : BigUint(String::Utf32::toU32Data(valStr_), radix_, numberFormatDelimiter_,
              isLowerPrefer_) {};
BigUint::BigUint(const std::vector<int32_t> &valData_, const uint8_t &radix_)
    : BigUint(valData_, radix_, false) {};
BigUint::BigUint(const std::vector<int32_t> &valData_, const uint8_t &radix_,
                 const int32_t &numberFormatDelimiter_)
    : BigUint(valData_, radix_, numberFormatDelimiter_, false) {};
BigUint::BigUint(const std::vector<int32_t> &valData_, const uint8_t &radix_,
                 const int32_t &numberFormatDelimiter_,
                 const bool &isLowerPrefer_) {
  if (radix_ < MinRadix || MaxRadix < radix_) {
    throw new InvalidArgumentError(
        "invalid radix. radix is only between 2 and 62 are allowed. radix = " +
        std::to_string(radix_) + ".\n");
  }
  uint32_t skipPrefixPos = 0;
  if (hasPrefixInValData(valData_, radix_)) {
    skipPrefixPos = 2;
  }
  uint32_t valDataLength = valData_.size();
  if (valDataLength == skipPrefixPos) {
    std::string messageTail;
    if (skipPrefixPos > 0) {
      messageTail = " with prefix. prefix = " +
                    CharSet::String::Utf32::toU8String(std::vector<int32_t>(
                        valData_.begin(), valData_.begin() + 2));
    } else {
      messageTail = ".";
    }
    throw new InvalidArgumentError(
        "invalid number string. empty numeric string is not allowed" +
        messageTail + "\n");
  }
  validateNumberFormatDelimiter(numberFormatDelimiter_);
  uint32_t paddingPos = 0;
  uint32_t digitLength = valData_.size();
  int32_t *valDataPtr = const_cast<int32_t *>(valData_.data());
  uint32_t prevChr = valData_.at(skipPrefixPos);
  for (paddingPos = skipPrefixPos; paddingPos < valDataLength; paddingPos++) {
    uint32_t currChr = uint32_t(*(valDataPtr + paddingPos));
    if (currChr == static_cast<uint32_t>(CharCode::UtfAsciiTable::Number0)) {
      prevChr = currChr;
      continue;
    }
    if (currChr == numberFormatDelimiter_) {
      if (paddingPos == 0) {
        throw new InvalidArgumentError(
            "invalid number string. cannot start with number format "
            "delimiter('" +
            CharSet::CharCode::Utf32::toU8String(numberFormatDelimiter_) +
            "'). number string = \"" +
            CharSet::String::Utf32::toU8String(valData_) + "\".\n");
      }
      if (currChr == prevChr) {
        throw new InvalidArgumentError(
            "invalid number string. cannot consecutive number format "
            "delimiter('" +
            CharSet::CharCode::Utf32::toU8String(numberFormatDelimiter_) +
            "'). number string = \"" +
            CharSet::String::Utf32::toU8String(valData_) + "\".\n");
      }
      prevChr = currChr;
      continue;
    }
    if (prevChr == numberFormatDelimiter_ &&
        currChr == numberFormatDelimiter_) {
    }
  }
  if (paddingPos == digitLength) {
    *this = BigUint(0);
    return;
  }
  std::vector<int32_t> valData =
      std::vector<int32_t>(valData_.begin() + paddingPos, valData_.end());
  digitLength = valData.size();
  valDataPtr = const_cast<int32_t *>(valData_.data());

  for (int64_t pos = digitLength - 1; pos > 0; pos--) {
    // int32_t digit = CharCode::Utf32::toDecimalFromDigitCharByRadix(
    //     *(valDataPtr + pos), radix_, isLowerPrefer_);
  }
  uint32_t chunkLength = chunks.size();
  const uint32_t *chunkDataPtr = chunks.data();
  bitLength = decideBitLength(uint64_t(*(chunkDataPtr + chunkLength - 1)));
};
BigUint::BigUint(const BigUint &rhs)
    : chunks(rhs.chunks), bitLength(rhs.bitLength) {};
BigUint &BigUint::operator=(const BigUint &rhs) {
  chunks = rhs.chunks;
  bitLength = rhs.bitLength;
  return *this;
};
BigUint BigUint::operator+(const BigUint &rhs) {
  BigUint r;
  r.chunks = addCC(chunks, rhs.getChunks());
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator+=(const BigUint &rhs) {
  *this = *this + rhs;
  return *this;
};
BigUint BigUint::operator-(const BigUint &rhs) {
  if (*this < rhs) {
    throw new InvalidArgumentError(
        "invalid sub operand. allow only first operand greater than or equal "
        "second. first = " +
        this->toHexadecimalString() +
        ". second = " + rhs.toHexadecimalString() + ".\n");
  }
  BigUint r;
  r.chunks = subCC(chunks, rhs.getChunks());
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator-=(const BigUint &rhs) {
  *this = *this - rhs;
  return *this;
};
BigUint BigUint::operator*(const BigUint &rhs) {
  if ((*this == BigUint(0)) || (const_cast<BigUint &>(rhs) == BigUint(0))) {
    return BigUint(0);
  }
  BigUint r;
  if (isPower2(rhs.getChunks())) {
    uint32_t rbl = decideBitLength(rhs.getChunks());
    r.chunks = shiftBitLeft(chunks, rbl - 1);
  } else if (*this >= rhs) {
    r.chunks = mulCC(chunks, rhs.getChunks());
  } else {
    r.chunks = mulCC(rhs.getChunks(), getChunks());
  }
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator*=(const BigUint &rhs) {
  *this = *this * rhs;
  return *this;
};
BigUint BigUint::operator/(const BigUint &rhs) {
  if (const_cast<BigUint &>(rhs) == BigUint(0)) {
    throw new InvalidArgumentError(
        "invalid div operand. allow only second operand greater than zero.\n");
  }
  BigUint r;
  if (isPower2(rhs.getChunks())) {
    uint32_t rbl = decideBitLength(rhs.getChunks());
    r.chunks = shiftBitRight(chunks, rbl - 1);
  } else {
    [[maybe_unused]] std::vector<uint32_t> modulo;
    r.chunks = divCC(chunks, rhs.getChunks(), modulo);
  }
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator/=(const BigUint &rhs) {
  *this = *this / rhs;
  return *this;
};
BigUint BigUint::operator%(const BigUint &rhs) {
  if (const_cast<BigUint &>(rhs) == BigUint(0)) {
    throw new InvalidArgumentError(
        "invalid mod operand. allow only second operand greater than zero.\n");
  }
  BigUint r;
  if (isPower2(rhs.getChunks())) {
    std::vector<uint32_t> maskChunks =
        subCC(rhs.getChunks(), std::vector<uint32_t>{1});
    r.chunks = andCC(chunks, maskChunks);
  } else {
    divCC(chunks, rhs.getChunks(), r.chunks);
  }
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator%=(const BigUint &rhs) {
  *this = *this % rhs;
  return *this;
};
BigUint BigUint::operator<<(const uint32_t &bits_) {
  BigUint r;
  r.chunks = shiftBitLeft(chunks, bits_);
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator<<=(const uint32_t &bits_) {
  *this = *this << bits_;
  return *this;
};
BigUint BigUint::operator>>(const uint32_t &bits_) {
  BigUint r;
  r.chunks = shiftBitRight(chunks, bits_);
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator>>=(const uint32_t &bits_) {
  *this = *this >> bits_;
  return *this;
};
bool BigUint::operator<(const BigUint &rhs) {
  return compare(chunks, (const_cast<BigUint &>(rhs)).chunks) < 0;
};
bool BigUint::operator<=(const BigUint &rhs) {
  return compare(chunks, (const_cast<BigUint &>(rhs)).chunks) <= 0;
};
bool BigUint::operator>(const BigUint &rhs) {
  return compare(chunks, (const_cast<BigUint &>(rhs)).chunks) > 0;
};
bool BigUint::operator>=(const BigUint &rhs) {
  return compare(chunks, (const_cast<BigUint &>(rhs)).chunks) >= 0;
};
bool BigUint::operator==(const BigUint &rhs) {
  return compare(chunks, (const_cast<BigUint &>(rhs)).chunks) == 0;
};
bool BigUint::operator!=(const BigUint &rhs) {
  return compare(chunks, (const_cast<BigUint &>(rhs)).chunks) != 0;
};
BigUint BigUint::operator&(const BigUint &rhs) {
  BigUint r;
  r.chunks = andCC(chunks, rhs.getChunks());
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator&=(const BigUint &rhs) {
  *this = *this & rhs;
  return *this;
};
BigUint BigUint::operator|(const BigUint &rhs) {
  BigUint r;
  r.chunks = orCC(chunks, rhs.getChunks());
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator|=(const BigUint &rhs) {
  *this = *this | rhs;
  return *this;
};
BigUint BigUint::operator^(const BigUint &rhs) {
  BigUint r;
  r.chunks = xorCC(chunks, rhs.getChunks());
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator^=(const BigUint &rhs) {
  *this = *this ^ rhs;
  return *this;
};
BigUint BigUint::operator~() {
  BigUint r;
  r.chunks = cmplC(chunks);
  r.bitLength = decideBitLength(r.chunks);
  return r;
};
BigUint &BigUint::operator++() {
  chunks = addCC(chunks, std::vector<uint32_t>{1});
  bitLength = decideBitLength(chunks);
  return *this;
};
BigUint &BigUint::operator--() {
  chunks = subCC(chunks, std::vector<uint32_t>{1});
  bitLength = decideBitLength(chunks);
  return *this;
};

std::vector<uint32_t> BigUint::getChunks() const { return chunks; };
uint32_t BigUint::getBitLength() const { return bitLength; };
uint32_t BigUint::getOctalDigitLength() const {
  return getDigitLengthByRadix(8);
};
uint32_t BigUint::getDecimalDigitLength() const {
  return getDigitLengthByRadix(10);
};
uint32_t BigUint::getHexadecimalDigitLength() const {
  return getDigitLengthByRadix(16);
};
uint32_t BigUint::getDigitLengthByRadix(const uint8_t &radix_) const {
  if (radix_ < MinRadix || MaxRadix < radix_) {
    throw new InvalidArgumentError(
        "invalid radix. radix is only between 2 and 62 are allowed. radix = " +
        std::to_string(radix_) + ".\n");
  }
  if (radix_ == 2) {
    return bitLength;
  }
  uint32_t digitLength =
      uint32_t(std::log10l(double(2)) / std::log10l(double(radix_)) *
               double(bitLength)) +
      1;
  if (digitLength == 1) {
    return digitLength;
  }
  std::vector<uint32_t> digitWeightChunks =
      digitWeightByRadix(digitLength, radix_);
  if (compare(chunks, digitWeightChunks) < 0) {
    digitLength--;
  };
  return digitLength;
};
std::string BigUint::toBinaryString() const {
  return toBinaryString(
      0, 0, static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), true,
      false);
};
std::string BigUint::toBinaryString(const uint32_t &rightAlignLength_) const {
  return toBinaryString(
      rightAlignLength_, 0,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), true, false);
};
std::string BigUint::toBinaryString(const uint32_t &rightAlignLength_,
                                    const uint8_t &formatChunkLength_) const {
  return toBinaryString(
      rightAlignLength_, formatChunkLength_,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), true, false);
};
std::string
BigUint::toBinaryString(const uint32_t &rightAlignLength_,
                        const uint8_t &formatChunkLength_,
                        const uint8_t &numberFormatDelimiter_) const {
  return toBinaryString(rightAlignLength_, formatChunkLength_,
                        numberFormatDelimiter_, true, false);
};
std::string BigUint::toBinaryString(const uint32_t &rightAlignLength_,
                                    const uint8_t &formatChunkLength_,
                                    const uint8_t &numberFormatDelimiter_,
                                    const bool &hasPrefix_) const {
  return toBinaryString(rightAlignLength_, formatChunkLength_,
                        numberFormatDelimiter_, hasPrefix_, false);
};
std::string BigUint::toBinaryString(const uint32_t &rightAlignLength_,
                                    const uint8_t &formatChunkLength_,
                                    const uint8_t &numberFormatDelimiter_,
                                    const bool &hasPrefix_,
                                    const bool &hasPaddingZero_) const {
  bool hasPrefix =
      hasPrefix_ && (numberFormatDelimiter_ ==
                     static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline));
  bool hasPaddingZero = hasPaddingZero_ || (hasPrefix && rightAlignLength_ > 0);
  std::string digitString;
  if (hasPrefix) {
    digitString = PrefixBinaryString;
  }
  digitString.append(toStringByRadix(2, rightAlignLength_, formatChunkLength_,
                                     numberFormatDelimiter_, hasPaddingZero));
  return digitString;
};
std::string BigUint::toOctalString() const {
  return toOctalString(0, 0,
                       static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline),
                       true, false);
};
std::string BigUint::toOctalString(const uint32_t &rightAlignLength_) const {
  return toOctalString(rightAlignLength_, 0,
                       static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline),
                       true, false);
};
std::string BigUint::toOctalString(const uint32_t &rightAlignLength_,
                                   const uint8_t &formatChunkLength_) const {
  return toOctalString(rightAlignLength_, formatChunkLength_,
                       static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline),
                       true, false);
};
std::string
BigUint::toOctalString(const uint32_t &rightAlignLength_,
                       const uint8_t &formatChunkLength_,
                       const uint8_t &numberFormatDelimiter_) const {
  return toOctalString(rightAlignLength_, formatChunkLength_,
                       numberFormatDelimiter_, true, false);
};
std::string BigUint::toOctalString(const uint32_t &rightAlignLength_,
                                   const uint8_t &formatChunkLength_,
                                   const uint8_t &numberFormatDelimiter_,
                                   const bool &hasPrefix_) const {
  return toOctalString(rightAlignLength_, formatChunkLength_,
                       numberFormatDelimiter_, hasPrefix_, false);
};
std::string BigUint::toOctalString(const uint32_t &rightAlignLength_,
                                   const uint8_t &formatChunkLength_,
                                   const uint8_t &numberFormatDelimiter_,
                                   const bool &hasPrefix_,
                                   const bool &hasPaddingZero_) const {
  bool hasPrefix =
      hasPrefix_ && (numberFormatDelimiter_ ==
                     static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline));
  bool hasPaddingZero = hasPaddingZero_ || (hasPrefix && rightAlignLength_ > 0);
  std::string digitString;
  if (hasPrefix) {
    digitString = PrefixOctalString;
  }
  digitString.append(toStringByRadix(8, rightAlignLength_, formatChunkLength_,
                                     numberFormatDelimiter_, hasPaddingZero));
  return digitString;
};
std::string BigUint::toDecimalString() const {
  return toDecimalString(
      0, 0, static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), false);
};
std::string BigUint::toDecimalString(const uint8_t &rightAlignLength_) const {
  return toDecimalString(
      rightAlignLength_, 0,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), false);
};
std::string BigUint::toDecimalString(const uint32_t &rightAlignLength_,
                                     const uint8_t &formatChunkLength_) const {
  return toDecimalString(
      rightAlignLength_, formatChunkLength_,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), false);
};
std::string
BigUint::toDecimalString(const uint32_t &rightAlignLength_,
                         const uint8_t &formatChunkLength_,
                         const uint8_t &numberFormatDelimiter_) const {
  return toDecimalString(rightAlignLength_, formatChunkLength_,
                         numberFormatDelimiter_, false);
};
std::string BigUint::toDecimalString(const uint32_t &rightAlignLength_,
                                     const uint8_t &formatChunkLength_,
                                     const uint8_t &numberFormatDelimiter_,
                                     const bool &hasPaddingZero_) const {
  return toStringByRadix(10, rightAlignLength_, formatChunkLength_,
                         numberFormatDelimiter_, hasPaddingZero_);
};
std::string BigUint::toHexadecimalString() const {
  return toHexadecimalString(
      0, 0, static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), true,
      false);
};
std::string
BigUint::toHexadecimalString(const uint32_t &rightAlignLength_) const {
  return toHexadecimalString(
      rightAlignLength_, 0,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), true, false);
};
std::string
BigUint::toHexadecimalString(const uint32_t &rightAlignLength_,
                             const uint8_t &formatChunkLength_) const {
  return toHexadecimalString(
      rightAlignLength_, formatChunkLength_,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), true, false);
};
std::string
BigUint::toHexadecimalString(const uint32_t &rightAlignLength_,
                             const uint8_t &formatChunkLength_,
                             const uint8_t &numberFormatDelimiter_) const {
  return toHexadecimalString(rightAlignLength_, formatChunkLength_,
                             numberFormatDelimiter_, true, false);
};
std::string BigUint::toHexadecimalString(const uint32_t &rightAlignLength_,
                                         const uint8_t &formatChunkLength_,
                                         const uint8_t &numberFormatDelimiter_,
                                         const bool &hasPrefix_) const {
  return toHexadecimalString(rightAlignLength_, formatChunkLength_,
                             numberFormatDelimiter_, hasPrefix_, false);
};
std::string BigUint::toHexadecimalString(const uint32_t &rightAlignLength_,
                                         const uint8_t &formatChunkLength_,
                                         const uint8_t &numberFormatDelimiter_,
                                         const bool &hasPrefix_,
                                         const bool &hasPaddingZero_) const {
  bool hasPrefix =
      hasPrefix_ && (numberFormatDelimiter_ ==
                     static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline));
  bool hasPaddingZero = hasPaddingZero_ || (hasPrefix && rightAlignLength_ > 0);
  std::string digitString;
  if (hasPrefix) {
    digitString = PrefixHexadecimalString;
  }
  digitString.append(toStringByRadix(16, rightAlignLength_, formatChunkLength_,
                                     numberFormatDelimiter_, hasPaddingZero));
  return digitString;
};
std::string BigUint::toStringByRadix(const uint8_t &radix_) const {
  return toStringByRadix(
      radix_, 0, 0, static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline),
      false);
};
std::string BigUint::toStringByRadix(const uint8_t &radix_,
                                     const uint32_t &rightAlignLength_) const {
  return toStringByRadix(
      radix_, rightAlignLength_, 0,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), false);
};
std::string BigUint::toStringByRadix(const uint8_t &radix_,
                                     const uint32_t &rightAlignLength_,
                                     const uint8_t &formatChunkLength_) const {
  return toStringByRadix(
      radix_, rightAlignLength_, formatChunkLength_,
      static_cast<uint8_t>(CharCode::UtfAsciiTable::Underline), false);
};
std::string
BigUint::toStringByRadix(const uint8_t &radix_,
                         const uint32_t &rightAlignLength_,
                         const uint8_t &formatChunkLength_,
                         const uint8_t &numberFormatDelimiter_) const {
  return toStringByRadix(radix_, rightAlignLength_, formatChunkLength_,
                         numberFormatDelimiter_, false);
};
std::string BigUint::toStringByRadix(const uint8_t &radix_,
                                     const uint32_t &rightAlignLength_,
                                     const uint8_t &formatChunkLength_,
                                     const uint8_t &numberFormatDelimiter_,
                                     const bool &hasPaddingZero_) const {
  if (radix_ < MinRadix || MaxRadix < radix_) {
    throw new InvalidArgumentError(
        "invalid radix. radix is only between 2 and 62 are allowed. radix = " +
        std::to_string(radix_) + ".\n");
  }
  if (0 < rightAlignLength_ && rightAlignLength_ < MinFormatLength) {
    throw new InvalidArgumentError(
        "invalid right alignment length. right alignment length is only zero "
        "or "
        "greater than equals 2 allowed. right alignment length = " +
        std::to_string(rightAlignLength_) + ".\n");
  }
  if (0 < formatChunkLength_ && formatChunkLength_ < MinFormatLength) {
    throw new InvalidArgumentError(
        "invalid format chunk length. format chunk length is only zero or "
        "greater than equals 2 allowed. format chunk length = " +
        std::to_string(formatChunkLength_) + ".\n");
  }
  this->validateNumberFormatDelimiter(numberFormatDelimiter_);
  uint32_t digitLen = getDigitLengthByRadix(radix_);
  std::vector<uint8_t> digitStrVec;
  uint32_t bufferLen = digitLen;
  uint32_t paddingLen = 0;
  uint32_t delimitersLen = 0;
  if (rightAlignLength_ > digitLen) {
    paddingLen = rightAlignLength_ - digitLen;
    bufferLen += paddingLen;
  }
  if (formatChunkLength_ > 0) {
    uint32_t actualDigitLen = digitLen;
    if (hasPaddingZero_ && paddingLen > 0) {
      actualDigitLen += paddingLen;
    }
    if (actualDigitLen > formatChunkLength_) {
      delimitersLen = (actualDigitLen - 1) / formatChunkLength_;
      bufferLen += delimitersLen;
    }
  }
  uint32_t writedDigitPos = 0;
  digitStrVec.reserve(bufferLen);
  if (compare(chunks, std::vector<uint32_t>{0}) == 0) {
    digitStrVec.push_back(
        static_cast<uint8_t>(CharCode::UtfAsciiTable::Number0));
    writedDigitPos++;
  } else {
    std::vector<uint32_t> tmpChunks = chunks;
    if (isRadixPower2(radix_)) {
      std::vector<uint32_t> maskChunk{uint32_t(radix_ - 1)};
      uint32_t shiftBit = decideBitLength(uint8_t(radix_ - 1));
      while (compare(tmpChunks, std::vector<uint32_t>{0}) > 0) {
        if (writedDigitPos > 0 && formatChunkLength_ > 0 &&
            (writedDigitPos % formatChunkLength_) == 0) {
          digitStrVec.push_back(numberFormatDelimiter_);
        }
        std::vector<uint32_t> digitChunk = andCC(tmpChunks, maskChunk);
        tmpChunks = shiftBitRight(tmpChunks, shiftBit);
        digitStrVec.push_back(CharCode::Utf32::toDigitCharFromDecimalByRadix(
            digitChunk.at(0), radix_, true));
        writedDigitPos++;
      }
    } else {
      while (compare(tmpChunks, std::vector<uint32_t>{0}) > 0) {
        if (writedDigitPos > 0 && formatChunkLength_ > 0 &&
            (writedDigitPos % formatChunkLength_) == 0) {
          digitStrVec.push_back(numberFormatDelimiter_);
        }
        std::vector<uint32_t> digitChunk;
        tmpChunks = divCU(tmpChunks, static_cast<uint32_t>(radix_), digitChunk);
        digitStrVec.push_back(CharCode::Utf32::toDigitCharFromDecimalByRadix(
            digitChunk.at(0), radix_, true));
        writedDigitPos++;
      }
    }
  }
  if (paddingLen > 0) {
    for (uint32_t pi = 0; pi < paddingLen; pi++) {
      if (hasPaddingZero_) {
        if (formatChunkLength_ > 0 &&
            (writedDigitPos % formatChunkLength_) == 0) {
          digitStrVec.push_back(numberFormatDelimiter_);
        }
        digitStrVec.push_back(
            static_cast<uint8_t>(CharCode::UtfAsciiTable::Number0));
        writedDigitPos++;
      } else {
        digitStrVec.push_back(
            static_cast<uint8_t>(CharCode::UtfAsciiTable::Space));
      }
    }
  }
  std::reverse(digitStrVec.begin(), digitStrVec.end());
  return std::string(digitStrVec.begin(), digitStrVec.end());
};

bool BigUint::hasPrefixInValData(const std::vector<int32_t> &valData_,
                                 const uint8_t radix_) const {
  if (valData_.size() < 2) {
    return false;
  }
  if (radix_ != 2 && radix_ != 8 && radix_ != 16) {
    return false;
  }
  uint8_t prefixRadix = 0;
  std::string specificPrefix;
  switch (radix_) {
  case 2:
    specificPrefix = "0b or 0B";
    break;
  case 8:
    specificPrefix = "0o or 0O";
    break;
  case 16:
    specificPrefix = "0x or 0X";
    break;
  }
  std::vector<int32_t> prefix(valData_.begin(), valData_.begin() + 2);
  if (prefix == CharSet::String::Utf8::toU32Data(PrefixBinaryString) ||
      prefix == CharSet::String::Utf8::toU32Data(PrefixBinaryStringUpper)) {
    prefixRadix = 2;
  } else if (prefix == CharSet::String::Utf8::toU32Data(PrefixOctalString) ||
             prefix ==
                 CharSet::String::Utf8::toU32Data(PrefixOctalStringUpper)) {
    prefixRadix = 8;
  } else if (prefix ==
                 CharSet::String::Utf8::toU32Data(PrefixHexadecimalString) ||
             prefix == CharSet::String::Utf8::toU32Data(
                           PrefixHexadecimalStringUpper)) {
    prefixRadix = 16;
  } else {
    return false;
  }
  if (prefixRadix != radix_) {
    throw new InvalidArgumentError(
        "invalid prefix in number string. only prefixes allowed for the "
        "specified radix " +
        std::to_string(radix_) + " are " + specificPrefix +
        ". prefix = " + CharSet::String::Utf32::toU8String(prefix) + ".\n");
  }
  return true;
};

uint32_t BigUint::decideBitLength(const uint8_t &val_) const {
  uint32_t rpos = 0;
  for (; rpos < U8Bit; rpos++) {
    if ((val_ & ((uint8_t)((uint8_t)1 << (U8BitMaxPos - rpos)))) > 0) {
      break;
    }
  }
  if (rpos >= U8Bit) {
    rpos--;
  }
  return U8Bit - rpos;
};
uint32_t BigUint::decideBitLength(const uint64_t &val_) const {
  uint32_t rpos = 0;
  for (; rpos < U64Bit; rpos++) {
    if ((val_ & ((uint64_t)((uint64_t)1 << (U64BitMaxPos - rpos)))) > 0) {
      break;
    }
  }
  if (rpos >= U64Bit) {
    rpos--;
  }
  return U64Bit - rpos;
};
uint32_t
BigUint::decideBitLength(const std::vector<uint32_t> &valChunks_) const {
  uint32_t cl = valChunks_.size();
  uint32_t bos = (cl - 1) << U32ShiftBit;
  uint32_t rpos = 0;
  uint32_t val = valChunks_.at((cl - 1));
  for (; rpos < U32Bit; rpos++) {
    if ((val & ((uint32_t)((uint32_t)1 << (U32BitMaxPos - rpos)))) > 0) {
      break;
    }
  }
  if (rpos >= U32Bit) {
    rpos--;
  }
  return U32Bit - rpos + bos;
};
std::vector<uint32_t> BigUint::decideChunks(const uint64_t &val_) const {
  uint64_t val = val_;
  std::vector<uint32_t> tChunks = std::vector<uint32_t>();
  uint32_t chunkLength = (bitLength >> 5);
  if (chunkLength == 0 || (bitLength % U32Bit) > 0) {
    chunkLength++;
  }
  for (uint32_t chunkPos = 0; chunkPos < chunkLength; chunkPos++) {
    tChunks.push_back(uint32_t(val & U32BitMask));
    val >>= U32Bit;
  }
  return tChunks;
};
std::vector<uint32_t>
BigUint::addCC(const std::vector<uint32_t> &lChunks_,
               const std::vector<uint32_t> &rChunks_) const {
  uint32_t lcl = lChunks_.size();
  uint32_t rcl = rChunks_.size();
  uint32_t loChPos;
  uint32_t endChPos;
  std::vector<uint32_t> *lc;
  std::vector<uint32_t> *rc;
  if (lcl >= rcl) {
    loChPos = rcl;
    endChPos = lcl;
    lc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
  } else {
    loChPos = lcl;
    endChPos = rcl;
    lc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
  }
  bool isCarryUpF = false;
  std::vector<uint32_t> rsltChunks;
  for (uint32_t cp = 0; cp < loChPos; cp++) {
    uint32_t lu = lc->at(cp);
    uint32_t ru = rc->at(cp);
    uint32_t cuu = isCarryUpF ? 1 : 0;
    isCarryUpF = isCarryUp(lu, ru, cuu);
    rsltChunks.push_back(lu + ru + cuu);
  }
  for (uint32_t cp = loChPos; cp < endChPos; cp++) {
    uint32_t cuu = isCarryUpF ? 1 : 0;
    uint32_t lu = lc->at(cp);
    isCarryUpF = isCarryUp(lu, 0, cuu);
    rsltChunks.push_back(lu + cuu);
  }
  if (isCarryUpF) {
    rsltChunks.push_back(1);
  }
  return rsltChunks;
};
std::vector<uint32_t>
BigUint::subCC(const std::vector<uint32_t> &lChunks_,
               const std::vector<uint32_t> &rChunks_) const {
  uint32_t lcl = lChunks_.size();
  uint32_t rcl = rChunks_.size();
  uint32_t loChPos;
  uint32_t endChPos;
  std::vector<uint32_t> *lc;
  std::vector<uint32_t> *rc;
  if (lcl >= rcl) {
    loChPos = rcl;
    endChPos = lcl;
    lc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
  } else {
    loChPos = lcl;
    endChPos = rcl;
    lc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
  }
  bool isCarryDownF = false;
  std::vector<uint32_t> rsltChunks;
  for (uint32_t cp = 0; cp < loChPos; cp++) {
    uint32_t lu = lc->at(cp);
    uint32_t ru = rc->at(cp);
    uint32_t cdu = isCarryDownF ? U32BitMask : 0;
    ru = ~ru + 1;
    isCarryDownF = !isCarryUp(lu, ru, 0);
    rsltChunks.push_back(lu + ru + cdu);
  }
  for (uint32_t cp = loChPos; cp < endChPos; cp++) {
    uint32_t cdu = isCarryDownF ? U32BitMask : 0;
    uint32_t lu = lc->at(cp);
    isCarryDownF = !isCarryUp(lu, 0, cdu);
    rsltChunks.push_back(lu + cdu);
  }
  return normalizeChunk(rsltChunks);
};
std::vector<uint32_t>
BigUint::mulCC(const std::vector<uint32_t> &lChunks_,
               const std::vector<uint32_t> &rChunks_) const {
  uint32_t lcl = lChunks_.size();
  uint32_t rcl = rChunks_.size();
  if (lcl == 1 && rcl == 1) {
    return mulUU(lChunks_.at(0), rChunks_.at(0));
  }
  if (rcl == 1) {
    return mulCU(lChunks_, rChunks_.at(0));
  }
  // TODO When self-hosting, too big uint(chunk size > 10) multiple using
  // karatsuba.
  return mulCCSimple(lChunks_, rChunks_);
};
std::vector<uint32_t> BigUint::mulUU(const uint32_t &lVal_,
                                     const uint32_t &rVal_) const {
  std::vector<uint32_t> rsltChunks = std::vector<uint32_t>();
  if (lVal_ == 0 || rVal_ == 0) {
    rsltChunks.push_back(0);
    return rsltChunks;
  }
  uint64_t mrVal = uint64_t(lVal_) * rVal_;
  rsltChunks.push_back(uint32_t(mrVal & U32BitMask));
  mrVal >>= U32Bit;
  if (mrVal > 0) {
    rsltChunks.push_back(uint32_t(mrVal & U32BitMask));
  }
  return rsltChunks;
};
std::vector<uint32_t> BigUint::mulCU(const std::vector<uint32_t> &lChunks_,
                                     const uint32_t &rVal_) const {
  std::vector<uint32_t> rsltChunks = std::vector<uint32_t>();
  if (rVal_ == 0) {
    rsltChunks.push_back(0);
    return rsltChunks;
  }
  uint32_t lcl = lChunks_.size();
  uint32_t carryUpVal = 0;
  for (uint32_t cp = 0; cp < lcl; cp++) {
    uint32_t lcu = lChunks_.at(cp);
    std::vector<uint32_t> muur =
        addCC(mulUU(lcu, rVal_), std::vector<uint32_t>{carryUpVal});
    rsltChunks.push_back(muur.at(0));
    if (muur.size() > 1) {
      carryUpVal = muur.at(1);
    } else {
      carryUpVal = 0;
    }
  }
  if (carryUpVal > 0) {
    rsltChunks.push_back(uint32_t(carryUpVal));
  }
  return rsltChunks;
};
std::vector<uint32_t>
BigUint::mulCCSimple(const std::vector<uint32_t> &lChunks_,
                     const std::vector<uint32_t> &rChunks_) const {
  std::vector<uint32_t> rsltChunks = std::vector<uint32_t>();
  uint32_t rcl = rChunks_.size();
  std::vector<uint32_t> carryUpChunks = std::vector<uint32_t>{0};
  for (uint32_t rcp = 0; rcp < rcl; rcp++) {
    uint32_t rcu = rChunks_.at(rcp);
    std::vector<uint32_t> muur = addCC(mulCU(lChunks_, rcu), carryUpChunks);
    rsltChunks.push_back(muur.at(0));
    if (muur.size() > 1) {
      carryUpChunks.clear();
      std::copy(muur.begin() + 1, muur.end(),
                std::back_inserter(carryUpChunks));
    } else {
      carryUpChunks = std::vector<uint32_t>{0};
    }
  }
  if (carryUpChunks.size() > 1 || carryUpChunks.at(0) > 0) {
    std::copy(carryUpChunks.begin(), carryUpChunks.end(),
              std::back_inserter(rsltChunks));
  }
  return rsltChunks;
};
std::vector<uint32_t> BigUint::divCC(const std::vector<uint32_t> &lChunks_,
                                     const std::vector<uint32_t> &rChunks_,
                                     std::vector<uint32_t> &modulo_) const {
  if (rChunks_.size() == 1 && rChunks_.at(0) == 1) {
    modulo_ = std::vector<uint32_t>{0};
    return lChunks_;
  }
  if (compare(const_cast<std::vector<uint32_t> &>(lChunks_),
              const_cast<std::vector<uint32_t> &>(rChunks_)) < 0) {
    modulo_ = lChunks_;
    return std::vector<uint32_t>{0};
  }
  uint32_t lcl = lChunks_.size();
  uint32_t rcl = rChunks_.size();
  if (lcl <= 2 && rcl <= 2) {
    uint64_t lVal = lChunks_.at(0);
    uint64_t rVal = rChunks_.at(0);
    if (lcl > 1) {
      lVal |= (uint64_t(lChunks_.at(1)) << U32Bit);
    }
    if (rcl > 1) {
      rVal |= (uint64_t(rChunks_.at(1)) << U32Bit);
    }
    return divUU(lVal, rVal, modulo_);
  }
  if (rcl == 1) {
    return divCU(lChunks_, rChunks_.at(0), modulo_);
  }
  return divCCSimple(lChunks_, rChunks_, modulo_);
};
std::vector<uint32_t> BigUint::divUU(const uint64_t &lVal_,
                                     const uint64_t &rVal_,
                                     std::vector<uint32_t> &modulo_) const {
  modulo_ = normalizeChunk(decideChunks((lVal_ % rVal_)));
  return normalizeChunk(decideChunks((lVal_ / rVal_)));
};
std::vector<uint32_t> BigUint::divCU(const std::vector<uint32_t> &lChunks_,
                                     const uint32_t &rVal_,
                                     std::vector<uint32_t> &modulo_) const {
  uint32_t lcl = lChunks_.size();
  std::vector<uint32_t> rsltChunks = std::vector<uint32_t>();
  uint64_t tmpModulo = 0;
  for (uint32_t lcp = 0; lcp < lcl; lcp++) {
    uint64_t diviendPartVal =
        (tmpModulo << U32Bit) + uint64_t(lChunks_.at(lcl - lcp - 1));
    if (diviendPartVal < uint64_t(rVal_)) {
      tmpModulo = diviendPartVal;
      if (rsltChunks.size() > 0) {
        rsltChunks.push_back(0);
      }
      continue;
    }
    uint32_t quotVal = diviendPartVal / uint64_t(rVal_);
    tmpModulo = diviendPartVal % uint64_t(rVal_);
    rsltChunks.push_back(quotVal);
  }
  std::reverse(rsltChunks.begin(), rsltChunks.end());
  modulo_ = normalizeChunk(decideChunks(tmpModulo));
  if (rsltChunks.size() == 0) {
    rsltChunks.push_back(0);
  }
  return normalizeChunk(rsltChunks);
};
std::vector<uint32_t>
BigUint::divCCSimple(const std::vector<uint32_t> &lChunks_,
                     const std::vector<uint32_t> &rChunks_,
                     std::vector<uint32_t> &modulo_) const {
  uint32_t lbl = decideBitLength(lChunks_);
  uint32_t rbl = decideBitLength(rChunks_);

  uint32_t sbl = lbl - rbl;
  std::vector<uint32_t> rsltChunks = std::vector<uint32_t>();
  if (sbl == 0) {
    rsltChunks = std::vector<uint32_t>{1};
    modulo_ = subCC(lChunks_, rChunks_);
    return rsltChunks;
  }
  rsltChunks.push_back(0);
  modulo_ = lChunks_;
  while (sbl > 0) {
    std::vector<uint32_t> tmpMulChunks = shiftBitLeft(rChunks_, sbl);
    if (compare(modulo_, tmpMulChunks) > 0) {
      rsltChunks =
          orCC(rsltChunks, shiftBitLeft(std::vector<uint32_t>{1}, sbl));
      modulo_ = subCC(lChunks_, mulCC(rsltChunks, rChunks_));
    }
    sbl--;
  }
  return rsltChunks;
};
std::vector<uint32_t>
BigUint::shiftBitLeft(const std::vector<uint32_t> &lChunks_,
                      const uint32_t &shiftBits_) const {
  uint32_t mecl = lChunks_.size();
  if (shiftBits_ == 0) {
    return lChunks_;
  }
  uint32_t shcl = shiftBits_ / U32Bit;
  uint32_t shbl = shiftBits_ % U32Bit;
  std::vector<uint32_t> shiftChunks = std::vector<uint32_t>();
  for (uint32_t cp = 0; cp < shcl; cp++) {
    shiftChunks.push_back(0);
  }
  if (shbl == 0) {
    std::copy(lChunks_.begin(), lChunks_.end(),
              std::back_inserter(shiftChunks));
    return shiftChunks;
  }
  uint64_t carryUpVal = 0;
  for (uint32_t cp = 0; cp < mecl; cp++) {
    uint64_t shiftedVal = (uint64_t(lChunks_.at(cp)) << shbl) | carryUpVal;
    shiftChunks.push_back((shiftedVal & U32BitMask));
    carryUpVal = (shiftedVal & U64High32BitMask) >> U32Bit;
  }
  if (carryUpVal > 0) {
    shiftChunks.push_back(carryUpVal);
  }
  return shiftChunks;
};
std::vector<uint32_t>
BigUint::shiftBitRight(const std::vector<uint32_t> &lChunks_,
                       const uint32_t &shiftBits_) const {
  uint32_t lcl = lChunks_.size();
  uint32_t debl =
      decideBitLength(const_cast<std::vector<uint32_t> &>(lChunks_));
  if (shiftBits_ == 0) {
    return lChunks_;
  }
  if (shiftBits_ >= debl) {
    return std::vector<uint32_t>{0};
  }
  uint32_t shcl = shiftBits_ / U32Bit;
  uint32_t shbl = shiftBits_ % U32Bit;
  std::vector<uint32_t> shiftChunks = std::vector<uint32_t>();
  if (shbl == 0) {
    std::copy(lChunks_.begin() + shcl, lChunks_.end(),
              std::back_inserter(shiftChunks));
    return shiftChunks;
  }
  uint32_t carryDownVal = 0;
  for (uint32_t cp = 0; cp < (lcl - shcl); cp++) {
    uint32_t lVal = lChunks_.at(lcl - 1 - cp);
    uint32_t shiftedVal = (lVal >> shbl) | carryDownVal;
    shiftChunks.push_back(shiftedVal);
    carryDownVal = (lVal & ((static_cast<uint32_t>(1) << shbl) - 1))
                   << (U32Bit - shbl);
  }
  std::reverse(shiftChunks.begin(), shiftChunks.end());
  return normalizeChunk(shiftChunks);
};
std::vector<uint32_t>
BigUint::andCC(const std::vector<uint32_t> &lChunks_,
               const std::vector<uint32_t> &rChunks_) const {
  uint32_t lcl = lChunks_.size();
  uint32_t rcl = rChunks_.size();
  uint32_t loChPos;
  std::vector<uint32_t> *lc;
  std::vector<uint32_t> *rc;
  if (lcl >= rcl) {
    loChPos = rcl;
    lc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
  } else {
    loChPos = lcl;
    lc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
  }
  std::vector<uint32_t> rsltChunks;
  for (uint32_t cp = 0; cp < loChPos; cp++) {
    uint32_t lu = lc->at(cp);
    uint32_t ru = rc->at(cp);
    rsltChunks.push_back(lu & ru);
  }
  return normalizeChunk(rsltChunks);
};
std::vector<uint32_t>
BigUint::orCC(const std::vector<uint32_t> &lChunks_,
              const std::vector<uint32_t> &rChunks_) const {
  uint32_t lcl = lChunks_.size();
  uint32_t rcl = rChunks_.size();
  uint32_t loChPos;
  std::vector<uint32_t> *lc;
  std::vector<uint32_t> *rc;
  if (lcl >= rcl) {
    loChPos = rcl;
    lc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
  } else {
    loChPos = lcl;
    lc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
  }
  std::vector<uint32_t> rsltChunks;
  for (uint32_t cp = 0; cp < loChPos; cp++) {
    uint32_t lu = lc->at(cp);
    uint32_t ru = rc->at(cp);
    rsltChunks.push_back(lu | ru);
  }
  std::copy(lc->begin() + loChPos, lc->end(), std::back_inserter(rsltChunks));
  return rsltChunks;
};
std::vector<uint32_t>
BigUint::xorCC(const std::vector<uint32_t> &lChunks_,
               const std::vector<uint32_t> &rChunks_) const {
  uint32_t lcl = lChunks_.size();
  uint32_t rcl = rChunks_.size();
  uint32_t loChPos;
  std::vector<uint32_t> *lc;
  std::vector<uint32_t> *rc;
  if (lcl >= rcl) {
    loChPos = rcl;
    lc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
  } else {
    loChPos = lcl;
    lc = &(const_cast<std::vector<uint32_t> &>(rChunks_));
    rc = &(const_cast<std::vector<uint32_t> &>(lChunks_));
  }
  std::vector<uint32_t> rsltChunks;
  for (uint32_t cp = 0; cp < loChPos; cp++) {
    uint32_t lu = lc->at(cp);
    uint32_t ru = rc->at(cp);
    rsltChunks.push_back(lu ^ ru);
  }
  std::copy(lc->begin() + loChPos, lc->end(), std::back_inserter(rsltChunks));
  return rsltChunks;
};
std::vector<uint32_t>
BigUint::cmplC(const std::vector<uint32_t> &rChunks_) const {
  uint32_t rcl = rChunks_.size();
  std::vector<uint32_t> rsltChunks;
  for (uint32_t cp = 0; cp < rcl; cp++) {
    rsltChunks.push_back(~(rChunks_.at(cp)));
  }
  return normalizeChunk(rsltChunks);
};
std::vector<uint32_t>
BigUint::normalizeChunk(const std::vector<uint32_t> &rChunks_) const {
  std::vector<uint32_t> normChunks;
  uint32_t chunkLength = rChunks_.size();
  int64_t copyCp = chunkLength - 1;
  for (; copyCp > 0; copyCp--) {
    if (rChunks_.at(copyCp) > 0) {
      break;
    }
  }
  for (uint32_t cp = 0; cp <= copyCp; cp++) {
    normChunks.push_back(rChunks_.at(cp));
  }
  return normChunks;
};
std::vector<uint32_t>
BigUint::digitWeightByRadix(const uint32_t &digitPosition_,
                            const uint8_t &radix_) const {
  if (digitPosition_ <= 1) {
    return std::vector<uint32_t>{1};
  }
  if (isRadixPower2(radix_)) {
    uint32_t shiftBitUnit = uint32_t(std::log2(radix_));
    return shiftBitLeft(std::vector<uint32_t>{1},
                        (digitPosition_ - 1) * shiftBitUnit);
  } else {
    if (digitPosition_ == 2) {
      return std::vector<uint32_t>{radix_};
    }
    uint32_t tmpRadixPowerVal = digitPosition_ - 1;
    std::vector<bool> extraMultipleStack;
    while (tmpRadixPowerVal > 1) {
      extraMultipleStack.push_back((tmpRadixPowerVal & 1) == 1);
      tmpRadixPowerVal >>= 1;
    }
    std::reverse(extraMultipleStack.begin(), extraMultipleStack.end());
    uint32_t stackLen = extraMultipleStack.size();
    std::vector<uint32_t> digitWeightChunks{radix_};
    for (uint32_t sp = 0; sp < stackLen; sp++) {
      digitWeightChunks = mulCC(digitWeightChunks, digitWeightChunks);
      if (extraMultipleStack.at(sp)) {
        digitWeightChunks = mulCU(digitWeightChunks, radix_);
      }
    }
    return digitWeightChunks;
  }
};
bool BigUint::isPower2(const std::vector<uint32_t> &valChunks_) const {
  uint32_t chunkLength = valChunks_.size();
  if (chunkLength == 1) {
    uint32_t val = valChunks_.at(0);
    return (val > 1) && (val & (val - 1)) == 0;
  }
  uint32_t pow2ChunkLength = chunkLength - 1;
  for (uint32_t cp = 0; cp < pow2ChunkLength; cp++) {
    if (valChunks_.at(cp) > 0) {
      return false;
    }
  }
  return valChunks_.at(pow2ChunkLength) == 1 ||
         isPower2(valChunks_.at(pow2ChunkLength));
};
bool BigUint::isPower2(const uint32_t &val_) const {
  return (val_ > 1) && (val_ & (val_ - 1)) == 0;
}
bool BigUint::isRadixPower2(const uint8_t &radix_) const {
  return (radix_ > 1) && (radix_ & (radix_ - 1)) == 0;
};
bool BigUint::isCarryUp(const uint32_t &lVal_, const uint32_t &rVal_,
                        const uint32_t &cuVal_) const {
  return ((uint64_t(lVal_) + uint64_t(rVal_) + uint64_t(cuVal_)) &
          U64High32BitMask) > 0;
};
int8_t BigUint::compare(const std::vector<uint32_t> &lChunks_,
                        const std::vector<uint32_t> &rChunks_) const {
  if (lChunks_.size() < rChunks_.size()) {
    return -1;
  } else if (lChunks_.size() > rChunks_.size()) {
    return 1;
  }
  uint32_t chunkLength = lChunks_.size();
  for (uint32_t cp = 0; cp < chunkLength; cp++) {
    uint32_t lu = lChunks_.at(chunkLength - cp - 1);
    uint32_t ru = rChunks_.at(chunkLength - cp - 1);
    if (lu < ru) {
      return -1;
    } else if (lu > ru) {
      return 1;
    }
  }
  return 0;
};
void BigUint::validateNumberFormatDelimiter(
    const int32_t &numberFormatDelimiter_) const {
  if (CharCode::Utf32::isAlphabetNumberChar(numberFormatDelimiter_)) {
    throw new InvalidArgumentError(
        "invalid number format delimiter. alphanumeric characters cannot "
        "be used as the number format delimiter."
        " number format delimiter = '" +
        CharCode::Utf8::toU8String(numberFormatDelimiter_) + "'.\n");
  }
  if (numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Plus) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Minus) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Asterisk) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Slash) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Percent) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Equal) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Ampersand) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(
              CharSet::CharCode::UtfAsciiTable::VerticalBar) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Caret) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::Tilde) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(
              CharSet::CharCode::UtfAsciiTable::Exclamation) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(CharSet::CharCode::UtfAsciiTable::LessThan) ||
      numberFormatDelimiter_ ==
          static_cast<uint32_t>(
              CharSet::CharCode::UtfAsciiTable::GreaterThan)) {
    throw new InvalidArgumentError(
        "invalid number format delimiter. operator symbol characters cannot "
        "be used as the number format delimiter."
        " number format delimiter = '" +
        CharCode::Utf8::toU8String(numberFormatDelimiter_) + "'.\n");
  }
};
