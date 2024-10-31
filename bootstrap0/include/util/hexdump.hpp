#ifndef _UTIL_HEXDUMP_
#define _UTIL_HEXDUMP_
#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace Util {
namespace HexStringer {
std::string dumpChar(const int8_t chr);
std::string dumpChar(const u_int8_t chr);
std::string dumpChar(const u_int8_t chr,bool fixZero);
std::string dumpChar(const int16_t chr);
std::string dumpChar(const u_int16_t chr);
std::string dumpChar(const int32_t chr);
std::string dumpChar(const u_int32_t chr);
std::string dumpChar(const int64_t chr);
std::string dumpChar(const u_int64_t chr);
std::string dumpString(const std::string str);
std::string dumpString(const std::vector<char> str);
} // namespace HexStringer
} // namespace Util
} // namespace gallop
#endif