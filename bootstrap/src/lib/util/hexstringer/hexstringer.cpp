// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "util/hexstringer/hexstringer.hpp"

using namespace gallop::Util;

// std::string
std::string HexStringer::dumpChar(const char &binData_) {
  return dumpChar(uint8_t(binData_));
};
std::string HexStringer::dumpChar(const uint8_t &binData_) {
  return dumpChar(uint8_t(binData_), false);
};
std::string HexStringer::dumpChar(const uint8_t &binData_,
                                  const bool &isFixZero_) {
  if (binData_ == 0 && !isFixZero_) {
    return std::string("");
  }
  std::vector<char> hexCharArr(2);
  std::sprintf(&hexCharArr[0], "%02x", binData_);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string HexStringer::dumpChar(const int16_t &binData_) {
  return dumpChar(uint16_t(binData_));
};
std::string HexStringer::dumpChar(const int16_t &binData_,
                                  const bool &isFixZero_) {
  return dumpChar(uint16_t(binData_), isFixZero_, false);
};
std::string HexStringer::dumpChar(const int16_t &binData_,
                                  const bool &isFixZero_,
                                  const bool &isOmitSpace_) {
  return dumpChar(uint16_t(binData_), isFixZero_, isOmitSpace_);
};
std::string HexStringer::dumpChar(const uint16_t &binData_) {
  return dumpChar(binData_, false, false);
};
std::string HexStringer::dumpChar(const uint16_t &binData_,
                                  const bool &isFixZero_) {
  return dumpChar(binData_, isFixZero_, false);
};
std::string HexStringer::dumpChar(const uint16_t &binData_,
                                  const bool &isFixZero_,
                                  const bool &isOmitSpace_) {
  if (binData_ == 0 && !isFixZero_) {
    return std::string("");
  }
  uint8_t binData1 = binData_ >> ByteShift1;
  uint8_t binData2 = (uint8_t)(binData_ & MaskChar);
  std::vector<char> hexCharArr(isOmitSpace_ ? 4 : 5);
  std::sprintf(&hexCharArr[0], isOmitSpace_ ? "%02x%02x" : "%02x %02x",
               binData1, binData2);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string HexStringer::dumpChar(const int32_t &binData_) {
  return dumpChar(uint32_t(binData_));
};
std::string HexStringer::dumpChar(const int32_t &binData_,
                                  const bool &isFixZero_) {
  return dumpChar(uint32_t(binData_), isFixZero_, false);
};
std::string HexStringer::dumpChar(const int32_t &binData_,
                                  const bool &isFixZero_,
                                  const bool &isOmitSpace_) {
  return dumpChar(uint32_t(binData_), isFixZero_, isOmitSpace_);
};
std::string HexStringer::dumpChar(const uint32_t &binData_) {
  return dumpChar(binData_, false, false);
};
std::string HexStringer::dumpChar(const uint32_t &binData_,
                                  const bool &isFixZero_) {
  return dumpChar(binData_, isFixZero_, false);
};
std::string HexStringer::dumpChar(const uint32_t &binData_,
                                  const bool &isFixZero_,
                                  const bool &isOmitSpace_) {
  if (binData_ == 0 && !isFixZero_) {
    return std::string("");
  }
  uint8_t binData1 = binData_ >> ByteShift3;
  uint8_t binData2 = (uint8_t)((binData_ >> ByteShift2) & MaskChar);
  uint8_t binData3 = (uint8_t)((binData_ >> ByteShift1) & MaskChar);
  uint8_t binData4 = (uint8_t)(binData_ & MaskChar);
  std::vector<char> hexCharArr(isOmitSpace_ ? 8 : 11);
  std::sprintf(&hexCharArr[0],
               isOmitSpace_ ? "%02x%02x%02x%02x" : "%02x %02x %02x %02x",
               binData1, binData2, binData3, binData4);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string HexStringer::dumpChar(const int64_t &binData_) {
  return dumpChar(uint64_t(binData_));
};
std::string HexStringer::dumpChar(const uint64_t &binData_) {
  if (binData_ == 0) {
    return std::string("");
  }
  uint8_t binData1 = binData_ >> ByteShift7;
  uint8_t binData2 = (uint8_t)((binData_ >> ByteShift6) & MaskChar);
  uint8_t binData3 = (uint8_t)((binData_ >> ByteShift5) & MaskChar);
  uint8_t binData4 = (uint8_t)((binData_ >> ByteShift4) & MaskChar);
  uint8_t binData5 = (uint8_t)((binData_ >> ByteShift3) & MaskChar);
  uint8_t binData6 = (uint8_t)((binData_ >> ByteShift2) & MaskChar);
  uint8_t binData7 = (uint8_t)((binData_ >> ByteShift1) & MaskChar);
  uint8_t binData8 = (uint8_t)(binData_ & MaskChar);
  std::vector<char> hexCharArr(23);
  std::sprintf(&hexCharArr[0], "%02x %02x %02x %02x %02x %02x %02x %02x",
               binData1, binData2, binData3, binData4, binData5, binData6,
               binData7, binData8);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string HexStringer::dumpString(const std::string &str_) {
  return dumpString(std::vector(str_.begin(), str_.end()));
};
std::string HexStringer::dumpString(const std::vector<char> &str_) {
  if (str_.empty()) {
    return std::string("");
  }
  const char *strPtr = str_.data();
  size_t slen = str_.size();
  size_t buflen = slen * 3 - 1;
  std::vector<char> hexCharArr(buflen);
  char *hexChrArrPtr = hexCharArr.data();
  for (size_t i = 0; i < slen; i++) {
    uint8_t binData_ = *(strPtr + i);
    size_t bufpos = i * 3;
    std::string hex = dumpChar(binData_, true);
    std::copy(hex.begin(), hex.end(), hexCharArr.begin() + bufpos);
    bool lfFlag = ((i + 1) % 8) == 0;
    if (i < slen - 1 && !lfFlag) {
      *(hexChrArrPtr + (i + 1) * 3 - 1) = ' ';
    } else if (lfFlag) {
      *(hexChrArrPtr + (i + 1) * 3 - 1) = '\n';
    }
  }
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string HexStringer::codeGenVector(const std::string &str_) {
  return codeGenVector(std::vector<char>(str_.begin(), str_.end()));
};
std::string HexStringer::codeGenVector(const std::vector<char> &str_) {
  if (str_.empty()) {
    return std::string("std::vector<char>{}");
  }
  const size_t &buflenVecDef = 18;
  const size_t &buflenStaticCast = 25;
  const char *strPtr = str_.data();
  size_t slen = str_.size();
  size_t buflen = buflenVecDef + slen * buflenStaticCast;
  std::vector<char> hexCharArr(buflen);
  char *hexChrArrPtr = hexCharArr.data();
  const std::string vecValDcl = "std::vector<char>{";
  const std::string staticCast = "static_cast<char>(0x";
  std::copy(vecValDcl.begin(), vecValDcl.end(), hexCharArr.begin());
  const size_t &headerLen = 18;
  const size_t &sCastLen = 20;
  for (size_t i = 0; i < slen; i++) {
    uint8_t binData_ = *(strPtr + i);
    size_t bufpos = i * buflenStaticCast;
    std::copy(staticCast.begin(), staticCast.end(),
              hexCharArr.begin() + headerLen + bufpos);
    std::string hex = dumpChar(binData_, true);
    std::copy(hex.begin(), hex.end(),
              hexCharArr.begin() + headerLen + bufpos + sCastLen);
    *(hexChrArrPtr + headerLen + bufpos + sCastLen + 2) = ')';
    *(hexChrArrPtr + headerLen + bufpos + sCastLen + 3) = ',';
    if (i < slen - 1) {
      *(hexChrArrPtr + headerLen + bufpos + sCastLen + 4) = ' ';
    } else {
      *(hexChrArrPtr + headerLen + bufpos + sCastLen + 4) = '}';
    }
  }
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string HexStringer::codeGenVector(const std::u16string &str_) {
  return codeGenVector(std::vector<int16_t>(str_.begin(), str_.end()));
};
std::string HexStringer::codeGenVector(const std::vector<int16_t> &str_) {
  if (str_.empty()) {
    return std::string("std::vector<int16_t>{}");
  }
  const size_t &buflenVecDef = 21;
  const size_t &buflenStaticCast = 30;
  const int16_t *strPtr = str_.data();
  size_t slen = str_.size();
  size_t buflen = buflenVecDef + slen * buflenStaticCast;
  std::vector<char> hexCharArr(buflen);
  char *hexChrArrPtr = hexCharArr.data();
  const std::string vecValDcl = "std::vector<int16_t>{";
  const std::string staticCast = "static_cast<int16_t>(0x";
  std::copy(vecValDcl.begin(), vecValDcl.end(), hexCharArr.begin());
  const size_t &headerLen = 21;
  const size_t &sCastLen = 23;
  for (size_t i = 0; i < slen; i++) {
    uint16_t binData_ = *(strPtr + i);
    size_t bufpos = i * buflenStaticCast;
    std::copy(staticCast.begin(), staticCast.end(),
              hexCharArr.begin() + headerLen + bufpos);
    std::string hex = dumpChar(binData_, true, true);
    std::copy(hex.begin(), hex.end(),
              hexCharArr.begin() + headerLen + bufpos + sCastLen);
    *(hexChrArrPtr + headerLen + bufpos + sCastLen + 4) = ')';
    *(hexChrArrPtr + headerLen + bufpos + sCastLen + 5) = ',';
    if (i < slen - 1) {
      *(hexChrArrPtr + headerLen + bufpos + sCastLen + 6) = ' ';
    } else {
      *(hexChrArrPtr + headerLen + bufpos + sCastLen + 6) = '}';
    }
  }
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string HexStringer::codeGenVector(const std::u32string &str_) {
  return codeGenVector(std::vector<int32_t>(str_.begin(), str_.end()));
};
std::string HexStringer::codeGenVector(const std::vector<int32_t> &str_) {
  if (str_.empty()) {
    return std::string("std::vector<int32_t>{}");
  }
  const size_t &buflenVecDef = 21;
  const size_t &buflenStaticCast = 34;
  const int32_t *strPtr = str_.data();
  size_t slen = str_.size();
  size_t buflen = buflenVecDef + slen * buflenStaticCast;
  std::vector<char> hexCharArr(buflen);
  char *hexChrArrPtr = hexCharArr.data();
  const std::string vecValDcl = "std::vector<int32_t>{";
  const std::string staticCast = "static_cast<int32_t>(0x";
  std::copy(vecValDcl.begin(), vecValDcl.end(), hexCharArr.begin());
  const size_t &headerLen = 21;
  const size_t &sCastLen = 23;
  for (size_t i = 0; i < slen; i++) {
    uint32_t binData_ = *(strPtr + i);
    size_t bufpos = i * buflenStaticCast;
    std::copy(staticCast.begin(), staticCast.end(),
              hexCharArr.begin() + headerLen + bufpos);
    std::string hex = dumpChar(binData_, true, true);
    std::copy(hex.begin(), hex.end(),
              hexCharArr.begin() + headerLen + bufpos + sCastLen);
    *(hexChrArrPtr + headerLen + bufpos + sCastLen + 8) = ')';
    *(hexChrArrPtr + headerLen + bufpos + sCastLen + 9) = ',';
    if (i < slen - 1) {
      *(hexChrArrPtr + headerLen + bufpos + sCastLen + 10) = ' ';
    } else {
      *(hexChrArrPtr + headerLen + bufpos + sCastLen + 10) = '}';
    }
  }
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
