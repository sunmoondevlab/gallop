#ifndef _UTIL_HEXSTRINGER_HEXSTRINGER_
#define _UTIL_HEXSTRINGER_HEXSTRINGER_
#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace Util {
namespace HexStringer {
std::string dumpChar(const int8_t &chr);
std::string dumpChar(const u_int8_t &chr);
std::string dumpChar(const u_int8_t &chr, const bool fixZeroFlag);

std::string dumpChar(const int16_t &chr);
std::string dumpChar(const uint16_t &chr);

std::string dumpChar(const int32_t &chr);
std::string dumpChar(const uint32_t &chr);

std::string dumpChar(const int64_t &chr);
std::string dumpChar(const uint64_t &chr);

std::string dumpString(const std::string &str);
std::string dumpString(const std::vector<char> &str);

std::string codeGenVector(const std::string &str);
std::string codeGenVector(const std::vector<char> &str);
} // namespace HexStringer
} // namespace Util
} // namespace gallop
#endif