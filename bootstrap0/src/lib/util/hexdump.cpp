#include "gallop.hpp"

namespace gallop {
namespace Util {
namespace HexStringer {
// std::string
std::string dumpChar(const int8_t chr) { return dumpChar((u_int8_t)chr); };
std::string dumpChar(const u_int8_t chr) {
  return dumpChar((u_int8_t)chr, false);
}
std::string dumpChar(const u_int8_t chr, bool fixZero) {
  if (chr == 0 && !fixZero) {
    return std::string("");
  }
  std::vector<char> hexCharArr(2);
  std::sprintf(&hexCharArr[0], "%02x", chr);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string dumpChar(const int16_t chr) { return dumpChar((u_int16_t)chr); };
std::string dumpChar(const u_int16_t chr) {
  if (chr == 0) {
    return std::string("");
  }
  u_int8_t chr1 = chr >> 8;
  u_int8_t chr2 = (u_int8_t)(chr & 0xff);
  std::vector<char> hexCharArr(5);
  std::sprintf(&hexCharArr[0], "%02x %02x", chr1, chr2);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string dumpChar(const int32_t chr) { return dumpChar((u_int32_t)chr); };
std::string dumpChar(const u_int32_t chr) {
  if (chr == 0) {
    return std::string("");
  }
  u_int8_t chr1 = chr >> 24;
  u_int8_t chr2 = (u_int8_t)((chr >> 16) & 0xff);
  u_int8_t chr3 = (u_int8_t)((chr >> 8) & 0xff);
  u_int8_t chr4 = (u_int8_t)(chr & 0xff);
  std::vector<char> hexCharArr(11);
  std::sprintf(&hexCharArr[0], "%02x %02x %02x %02x", chr1, chr2, chr3, chr4);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string dumpChar(const int64_t chr) { return dumpChar((u_int64_t)chr); };
std::string dumpChar(const u_int64_t chr) {
  if (chr == 0) {
    return std::string("");
  }
  u_int8_t chr1 = chr >> 56;
  u_int8_t chr2 = (u_int8_t)((chr >> 48) & 0xff);
  u_int8_t chr3 = (u_int8_t)((chr >> 40) & 0xff);
  u_int8_t chr4 = (u_int8_t)((chr >> 32) & 0xff);
  u_int8_t chr5 = (u_int8_t)((chr >> 24) & 0xff);
  u_int8_t chr6 = (u_int8_t)((chr >> 16) & 0xff);
  u_int8_t chr7 = (u_int8_t)((chr >> 8) & 0xff);
  u_int8_t chr8 = (u_int8_t)(chr & 0xff);
  std::vector<char> hexCharArr(23);
  std::sprintf(&hexCharArr[0], "%02x %02x %02x %02x %02x %02x %02x %02x", chr1,
               chr2, chr3, chr4, chr5, chr6, chr7, chr8);
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
std::string dumpString(const std::string str) {
  return dumpString(std::vector(str.begin(), str.end()));
};
std::string dumpString(const std::vector<char> str) {
  if (str.empty()) {
    return std::string("");
  }
  size_t slen = str.size();
  size_t buflen = slen * 3 - 1;
  std::vector<char> hexCharArr(buflen);
  for (size_t i = 0; i < slen; i++) {
    size_t bufpos = i * 3;
    std::string hex = dumpChar((u_int8_t)str.at(i), true);
    std::copy(hex.begin(), hex.end(), hexCharArr.begin() + bufpos);
    bool isLF = ((i + 1) % 8) == 0;
    if (i < slen - 1 && !isLF) {
      *(&hexCharArr[0] + (i + 1) * 3 - 1) = ' ';
    } else if (isLF) {
      *(&hexCharArr[0] + (i + 1) * 3 - 1) = '\n';
    }
  }
  std::string hexString(hexCharArr.begin(), hexCharArr.end());
  return hexString;
};
} // namespace HexStringer
} // namespace Util
} // namespace gallop
