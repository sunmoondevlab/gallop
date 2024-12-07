// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/char_code/utf32_char_code.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"
#include "error/common_errors.hpp"

using namespace gallop::Error;
using namespace gallop::CharSet::CharCode;

class Utf32CharCodeTest : public ::testing::Test {};
TEST(Utf32CharCodeTest, CharCodeTypes) {
  ASSERT_EQ(Utf32::isNullCharCode(static_cast<int32_t>(0)), true);
  // BE BOM
  ASSERT_EQ(Utf32::isBom(static_cast<int32_t>(0x0000feff)), true);
  ASSERT_EQ(Utf32::isBom(static_cast<int32_t>(0x0001feff)), false);
  // LE BOM
  ASSERT_EQ(Utf32::isBom(static_cast<int32_t>(0xfffe0000), true), true);
  ASSERT_EQ(Utf32::isBom(static_cast<int32_t>(0xfffe0100), true), false);
  // BE BOM
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000feff)), true);
  // LE BOM
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xfffe0000), true),
            true);
  // BE New line
  ASSERT_EQ(Utf32::isLineBreak(static_cast<int32_t>(0x0000000a)), true);
  ASSERT_EQ(Utf32::isLineBreak(static_cast<int32_t>(0x0000000d)), true);
  ASSERT_EQ(Utf32::isLineBreak(static_cast<int32_t>(0x00000009)), false);
  ASSERT_EQ(Utf32::isLineFeed(static_cast<int32_t>(0x0000000a)), true);
  ASSERT_EQ(Utf32::isLineFeed(static_cast<int32_t>(0x0000000d)), false);
  ASSERT_EQ(Utf32::isCarriageReturn(static_cast<int32_t>(0x0000000d)), true);
  ASSERT_EQ(Utf32::isCarriageReturn(static_cast<int32_t>(0x0000000a)), false);
  // LE New line
  ASSERT_EQ(Utf32::isLineBreak(static_cast<int32_t>(0x0a000000), true), true);
  ASSERT_EQ(Utf32::isLineBreak(static_cast<int32_t>(0x0d000000), true), true);
  ASSERT_EQ(Utf32::isLineBreak(static_cast<int32_t>(0x09000000), true), false);
  ASSERT_EQ(Utf32::isLineFeed(static_cast<int32_t>(0x0a000000), true), true);
  ASSERT_EQ(Utf32::isLineFeed(static_cast<int32_t>(0x0d000000), true), false);
  ASSERT_EQ(Utf32::isCarriageReturn(static_cast<int32_t>(0x0d000000), true),
            true);
  ASSERT_EQ(Utf32::isCarriageReturn(static_cast<int32_t>(0x0a000000), true),
            false);
  // BE ASCII
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x00000000)), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x00000001)), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x0000007e)), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x0000007f)), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x00000080)), false);
  // LE ASCII
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x00000000), true), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x01000000), true), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x7e000000), true), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x7f000000), true), true);
  ASSERT_EQ(Utf32::isAscii(static_cast<int32_t>(0x80000000), true), false);
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000000)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000001)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000007e)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000007f)), true);
  // 2byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000080)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000081)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x000007fe)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x000007ff)), true);
  // 3byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000800)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000801)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000fffe)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000ffff)), true);
  // surrogate pare
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000d7ff)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000d800)), false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000d801)), false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000dffe)), false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000dfff)), false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0000e000)), true);
  // 4byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00010000)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00010001)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0010fffe)), true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x0010ffff)), true);
  // out bounds
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00110000)), false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00110001)), false);
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x01000000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x7e000000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x7f000000), true),
            true);
  // 2byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x80000000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x81000000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xfe070000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xff070000), true),
            true);
  // 3byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00080000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x01080000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xfeff0000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xffff0000), true),
            true);
  // surrogate pare
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xffd70000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00d80000), true),
            false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x01d80000), true),
            false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xfedf0000), true),
            false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xffdf0000), true),
            false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00e00000), true),
            true);
  // 4byte UTF-8
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00000100), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x01000100), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xfeff1000), true),
            true);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0xffff1000), true),
            true);
  // out bounds
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x00001100), true),
            false);
  ASSERT_EQ(Utf32::isValidCharCode(static_cast<int32_t>(0x01001100), true),
            false);
};
TEST(Utf32CharCodeTest, SwapEndianness) {
  ASSERT_EQ(Utf32::getBom(false), static_cast<int32_t>(0x0000feff));
  ASSERT_EQ(Utf32::getBom(true), static_cast<int32_t>(0xfffe0000));
  ASSERT_EQ(Utf32::getReplacementChar(false), static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf32::getReplacementChar(true), static_cast<int32_t>(0xfdff0000));
  // BE BOM
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000feff)),
            static_cast<int32_t>(0xfffe0000));
  // LE BOM
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xfffe0000)),
            static_cast<int32_t>(0x0000feff));
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000000)),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000001)),
            static_cast<int32_t>(0x01000000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000007e)),
            static_cast<int32_t>(0x7e000000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000007f)),
            static_cast<int32_t>(0x7f000000));
  // 2byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000080)),
            static_cast<int32_t>(0x80000000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000081)),
            static_cast<int32_t>(0x81000000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x000007fe)),
            static_cast<int32_t>(0xfe070000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x000007ff)),
            static_cast<int32_t>(0xff070000));
  // 3byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000800)),
            static_cast<int32_t>(0x00080000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000801)),
            static_cast<int32_t>(0x01080000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000fffe)),
            static_cast<int32_t>(0xfeff0000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000ffff)),
            static_cast<int32_t>(0xffff0000));
  // surrogate pare
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000d7ff)),
            static_cast<int32_t>(0xffd70000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000d800)),
            static_cast<int32_t>(0x00d80000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000d801)),
            static_cast<int32_t>(0x01d80000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000dffe)),
            static_cast<int32_t>(0xfedf0000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000dfff)),
            static_cast<int32_t>(0xffdf0000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0000e000)),
            static_cast<int32_t>(0x00e00000));
  // 4byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00010000)),
            static_cast<int32_t>(0x00000100));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00010001)),
            static_cast<int32_t>(0x01000100));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0010fffe)),
            static_cast<int32_t>(0xfeff1000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x0010ffff)),
            static_cast<int32_t>(0xffff1000));
  // out bounds
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00110000)),
            static_cast<int32_t>(0x00001100));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00110001)),
            static_cast<int32_t>(0x01001100));
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000000)),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x01000000)),
            static_cast<int32_t>(0x00000001));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x7e000000)),
            static_cast<int32_t>(0x0000007e));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x7f000000)),
            static_cast<int32_t>(0x0000007f));
  // 2byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x80000000)),
            static_cast<int32_t>(0x00000080));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x81000000)),
            static_cast<int32_t>(0x00000081));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xfe070000)),
            static_cast<int32_t>(0x000007fe));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xff070000)),
            static_cast<int32_t>(0x000007ff));
  // 3byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00080000)),
            static_cast<int32_t>(0x00000800));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x01080000)),
            static_cast<int32_t>(0x00000801));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xfeff0000)),
            static_cast<int32_t>(0x0000fffe));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xffff0000)),
            static_cast<int32_t>(0x0000ffff));
  // surrogate pare
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xffd70000)),
            static_cast<int32_t>(0x0000d7ff));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00d80000)),
            static_cast<int32_t>(0x0000d800));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x01d80000)),
            static_cast<int32_t>(0x0000d801));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xfedf0000)),
            static_cast<int32_t>(0x0000dffe));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xffdf0000)),
            static_cast<int32_t>(0x0000dfff));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00e00000)),
            static_cast<int32_t>(0x0000e000));
  // 4byte UTF-8
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00000100)),
            static_cast<int32_t>(0x00010000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x01000100)),
            static_cast<int32_t>(0x00010001));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xfeff1000)),
            static_cast<int32_t>(0x0010fffe));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0xffff1000)),
            static_cast<int32_t>(0x0010ffff));
  // out bounds
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x00001100)),
            static_cast<int32_t>(0x00110000));
  ASSERT_EQ(Utf32::swapEndianness(static_cast<int32_t>(0x01001100)),
            static_cast<int32_t>(0x00110001));
};
TEST(Utf32CharCodeTest, ToU8) {
  std::vector<char> expectChunk;
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0)), expectChunk);

  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbb),
                 static_cast<char>(0xbf)};
  // BE BOM
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0000feff)), expectChunk);
  // LE BOM
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xfffe0000), true), expectChunk);
  // BE
  // 1byte UTF-8
  expectChunk = {static_cast<char>(0x09)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000009)), expectChunk);
  expectChunk = {static_cast<char>(0x20)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000020)), expectChunk);
  expectChunk = {static_cast<char>(0x30)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000030)), expectChunk);
  expectChunk = {static_cast<char>(0x41)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000041)), expectChunk);
  expectChunk = {static_cast<char>(0x61)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000061)), expectChunk);
  expectChunk = {static_cast<char>(0x7e)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0000007e)), expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000080)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x81)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000081)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa0)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x000000a0)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa1)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x000000a1)), expectChunk);
  expectChunk = {static_cast<char>(0xc3), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x000000ff)), expectChunk);
  expectChunk = {static_cast<char>(0xc4), static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000100)), expectChunk);
  expectChunk = {static_cast<char>(0xdf), static_cast<char>(0xba)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x000007fa)), expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000800)), expectChunk);
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x81)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000801)), expectChunk);
  expectChunk = {static_cast<char>(0xe1), static_cast<char>(0x80),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00001000)), expectChunk);
  expectChunk = {static_cast<char>(0xed), static_cast<char>(0x9f),
                 static_cast<char>(0xbb)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0000d7fb)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0000d800)), expectChunk);
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0000dfff)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xa4),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0000f900)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0000fffd)), expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00010000)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x81)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00010001)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x9f),
                 static_cast<char>(0xa7), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0001f9ff)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0xaf),
                 static_cast<char>(0xa8), static_cast<char>(0x9c)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x0002fa1c)), expectChunk);
  // LE
  // 1byte UTF-8
  expectChunk = {static_cast<char>(0x09)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x09000000), true), expectChunk);
  expectChunk = {static_cast<char>(0x20)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x20000000), true), expectChunk);
  expectChunk = {static_cast<char>(0x30)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x30000000), true), expectChunk);
  expectChunk = {static_cast<char>(0x41)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x41000000), true), expectChunk);
  expectChunk = {static_cast<char>(0x61)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x61000000), true), expectChunk);
  expectChunk = {static_cast<char>(0x7e)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x7e000000), true), expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x80000000), true), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x81)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x81000000), true), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa0)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xa0000000), true), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa1)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xa1000000), true), expectChunk);
  expectChunk = {static_cast<char>(0xc3), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xff000000), true), expectChunk);
  expectChunk = {static_cast<char>(0xc4), static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00010000), true), expectChunk);
  expectChunk = {static_cast<char>(0xdf), static_cast<char>(0xba)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xfa070000), true), expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00080000), true), expectChunk);
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x81)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x01080000), true), expectChunk);
  expectChunk = {static_cast<char>(0xe1), static_cast<char>(0x80),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00100000), true), expectChunk);
  expectChunk = {static_cast<char>(0xed), static_cast<char>(0x9f),
                 static_cast<char>(0xbb)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xfbd70000), true), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00d80000), true), expectChunk);
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xffdf0000), true), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xa4),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00f90000), true), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xfdff0000), true), expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x80)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x00000100), true), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x81)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x01000100), true), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x9f),
                 static_cast<char>(0xa7), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0xfff90100), true), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0xaf),
                 static_cast<char>(0xa8), static_cast<char>(0x9c)};
  ASSERT_EQ(Utf32::toU8(static_cast<int32_t>(0x1cfa0200), true), expectChunk);
};
TEST(Utf32CharCodeTest, ToU16) {
  std::vector<int16_t> expectChunk;
  expectChunk = {static_cast<int16_t>(0x0000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0)), expectChunk);
  // BE BOM
  expectChunk = {static_cast<int16_t>(0xfeff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000feff)), expectChunk);
  // LE BOM
  expectChunk = {static_cast<int16_t>(0xfffe)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfffe0000), true), expectChunk);
  // BE BOM to LE BOM
  expectChunk = {static_cast<int16_t>(0xfffe)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000feff), false, true),
            expectChunk);
  // LE BOM to BE BOM
  expectChunk = {static_cast<int16_t>(0xfeff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfffe0000), true, false),
            expectChunk);
  // BE
  // 1byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0009)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000009)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0020)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000020)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0030)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000030)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0041)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000041)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0061)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000061)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x007e)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000007e)), expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0080)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000080)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0081)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000081)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00a0)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000000a0)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00a1)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000000a1)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00ff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000000ff)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000100)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x07fa)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000007fa)), expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0800)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000800)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0801)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000801)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x1000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00001000)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd7fb)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000d7fb)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000d800)), expectChunk);
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000dfff)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xf900)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000f900)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000fffd)), expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc00)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00010000)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc01)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00010001)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd83e), static_cast<int16_t>(0xddff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0001f9ff)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd87e), static_cast<int16_t>(0xde1c)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0002fa1c)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xdbff), static_cast<int16_t>(0xdfff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0010ffff)), expectChunk);
  // LE
  // 1byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0900)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x09000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x2000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x20000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x3000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x30000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x4100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x41000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x6100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x61000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x7e00)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x7e000000), true), expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x8000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x80000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x8100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x81000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xa000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xa0000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xa100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xa1000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xff00)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xff000000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0001)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00010000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfa07)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfa070000), true), expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0008)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00080000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0108)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x01080000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0010)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00100000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfbd7)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfbd70000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00d80000), true), expectChunk);
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xffdf0000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00f9)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00f90000), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfdff0000), true), expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00dc)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000100), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x01dc)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x01000100), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x3ed8), static_cast<int16_t>(0xffdd)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfff90100), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0x7ed8), static_cast<int16_t>(0x1cde)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x1cfa0200), true), expectChunk);
  expectChunk = {static_cast<int16_t>(0xffdb), static_cast<int16_t>(0xffdf)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xffff1000), true), expectChunk);
  // BE to LE
  // 1byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0900)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000009), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x2000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000020), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x3000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000030), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x4100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000041), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x6100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000061), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x7e00)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000007e), false, true),
            expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x8000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000080), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x8100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000081), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xa000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000000a0), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xa100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000000a1), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xff00)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000000ff), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0001)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000100), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfa07)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x000007fa), false, true),
            expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0008)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000800), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0108)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000801), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0010)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00001000), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfbd7)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000d7fb), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000d800), false, true),
            expectChunk);
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000dfff), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x00f9)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000f900), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0000fffd), false, true),
            expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00dc)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00010000), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x01dc)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00010001), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x3ed8), static_cast<int16_t>(0xffdd)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0001f9ff), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x7ed8), static_cast<int16_t>(0x1cde)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0002fa1c), false, true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xffdb), static_cast<int16_t>(0xffdf)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x0010ffff), false, true),
            expectChunk);
  // LE to BE
  // 1byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0009)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x09000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0020)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x20000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0030)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x30000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0041)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x41000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0061)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x61000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x007e)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x7e000000), true, false),
            expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0080)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x80000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0081)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x81000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x00a0)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xa0000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x00a1)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xa1000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x00ff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xff000000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0100)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00010000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x07fa)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfa070000), true, false),
            expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0800)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00080000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0801)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x01080000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x1000)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00100000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xd7fb)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfbd70000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00d80000), true, false),
            expectChunk);
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xffdf0000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xf900)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00f90000), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfdff0000), true, false),
            expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc00)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x00000100), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc01)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x01000100), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xd83e), static_cast<int16_t>(0xddff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xfff90100), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xd87e), static_cast<int16_t>(0xde1c)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0x1cfa0200), true, false),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xdbff), static_cast<int16_t>(0xdfff)};
  ASSERT_EQ(Utf32::toU16(static_cast<int32_t>(0xffff1000), true, false),
            expectChunk);
};
TEST(Utf32CharCodeTest, ToU8String) {
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0)), "");
  // BE BOM
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0000feff)), "");
  // LE BOM
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xfffe0000), true), "");
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000009)), "\t");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000020)), " ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000030)), "0");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000041)), "A");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000061)), "a");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0000007e)), "~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000080)), "\xc2\x80");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000081)), "\xc2\x81");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x000000a0)), "\xc2\xa0");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x000000a1)), "¡");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x000000ff)), "ÿ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000100)), "Ā");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x000007fa)), "ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000800)), "ࠀ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000801)), "ࠁ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00001000)), "က");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0000d7fb)), "ퟻ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0000d800)), "�");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0000dfff)), "�");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0000f900)), "豈");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0000fffd)), "�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00010000)), "𐀀");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00010001)), "𐀁");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0001f9ff)), "🧿");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x0002fa1c)), "鼻");
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x09000000), true), "\t");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x20000000), true), " ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x30000000), true), "0");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x41000000), true), "A");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x61000000), true), "a");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x7e000000), true), "~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x80000000), true),
            "\xc2\x80");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x81000000), true),
            "\xc2\x81");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xa0000000), true),
            "\xc2\xa0");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xa1000000), true), "¡");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xff000000), true), "ÿ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00010000), true), "Ā");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xfa070000), true), "ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00080000), true), "ࠀ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x01080000), true), "ࠁ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00100000), true), "က");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xfbd70000), true), "ퟻ");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00d80000), true), "�");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xffdf0000), true), "�");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00f90000), true), "豈");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xfdff0000), true), "�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x00000100), true), "𐀀");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x01000100), true), "𐀁");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0xfff90100), true), "🧿");
  ASSERT_EQ(Utf32::toU8String(static_cast<int32_t>(0x1cfa0200), true), "鼻");
};
TEST(Utf32CharCodeTest, ToU16String) {
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0)), u"");
  // BE BOM
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0000feff)), u"");
  // LE BOM
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xfffe0000), true), u"");
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000009)), u"\t");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000020)), u" ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000030)), u"0");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000041)), u"A");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000061)), u"a");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0000007e)), u"~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000080)), u"\x80");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000081)), u"\x81");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x000000a0)), u"\xa0");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x000000a1)), u"¡");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x000000ff)), u"ÿ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000100)), u"Ā");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x000007fa)), u"ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000800)), u"ࠀ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000801)), u"ࠁ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00001000)), u"က");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0000d7fb)), u"ퟻ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0000d800)), u"�");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0000dfff)), u"�");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0000f900)), u"豈");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0000fffd)), u"�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00010000)), u"𐀀");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00010001)), u"𐀁");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0001f9ff)), u"🧿");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x0002fa1c)), u"鼻");
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x09000000), true), u"\t");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x20000000), true), u" ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x30000000), true), u"0");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x41000000), true), u"A");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x61000000), true), u"a");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x7e000000), true), u"~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x80000000), true),
            u"\x80");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x81000000), true),
            u"\x81");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xa0000000), true),
            u"\xa0");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xa1000000), true), u"¡");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xff000000), true), u"ÿ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00010000), true), u"Ā");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xfa070000), true), u"ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00080000), true), u"ࠀ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x01080000), true), u"ࠁ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00100000), true), u"က");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xfbd70000), true), u"ퟻ");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00d80000), true), u"�");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xffdf0000), true), u"�");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00f90000), true), u"豈");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xfdff0000), true), u"�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x00000100), true), u"𐀀");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x01000100), true), u"𐀁");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0xfff90100), true), u"🧿");
  ASSERT_EQ(Utf32::toU16String(static_cast<int32_t>(0x1cfa0200), true), u"鼻");
};
TEST(Utf32CharCodeTest, ToU32String) {
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0)), U"");
  // BE BOM
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0000feff)), U"");
  // LE BOM
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xfffe0000), true), U"");
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000009)), U"\t");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000020)), U" ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000030)), U"0");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000041)), U"A");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000061)), U"a");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0000007e)), U"~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000080)), U"\x80");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000081)), U"\x81");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x000000a0)), U"\xa0");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x000000a1)), U"¡");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x000000ff)), U"ÿ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000100)), U"Ā");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x000007fa)), U"ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000800)), U"ࠀ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000801)), U"ࠁ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00001000)), U"က");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0000d7fb)), U"ퟻ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0000d800)), U"�");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0000dfff)), U"�");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0000f900)), U"豈");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0000fffd)), U"�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00010000)), U"𐀀");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00010001)), U"𐀁");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0001f9ff)), U"🧿");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x0002fa1c)), U"鼻");
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x09000000), true), U"\t");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x20000000), true), U" ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x30000000), true), U"0");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x41000000), true), U"A");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x61000000), true), U"a");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x7e000000), true), U"~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x80000000), true),
            U"\x80");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x81000000), true),
            U"\x81");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xa0000000), true),
            U"\xa0");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xa1000000), true), U"¡");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xff000000), true), U"ÿ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00010000), true), U"Ā");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xfa070000), true), U"ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00080000), true), U"ࠀ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x01080000), true), U"ࠁ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00100000), true), U"က");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xfbd70000), true), U"ퟻ");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00d80000), true), U"�");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xffdf0000), true), U"�");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00f90000), true), U"豈");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xfdff0000), true), U"�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x00000100), true), U"𐀀");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x01000100), true), U"𐀁");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0xfff90100), true), U"🧿");
  ASSERT_EQ(Utf32::toU32String(static_cast<int32_t>(0x1cfa0200), true), U"鼻");
};

// TODO : if will self hosting? following testing , and implements other code
// static bool isSpaceChar(const int32_t &charCode);
// static bool isNumberChar(const int32_t &charCode);
// static bool isUpperAlphaChar(const int32_t &charCode);
// static bool isLowerAlphaChar(const int32_t &charCode);
// static bool isAlphabetChar(const int32_t &charCode);
// static bool isAlphabetNumberChar(const int32_t &charCode);
// static bool isSymbolChar(const int32_t &charCode);
// static bool isIdentifierChar(const int32_t &charCode);
// static bool isIdentifierChar(const int32_t &charCode, const bool
// static bool equalsCharIgnoreCase(const int32_t &charCode,
//                                  const int32_t &expectCharCode);

TEST(Utf32CharCodeTest, IsDigitChar) {
  ASSERT_EQ(Utf32::isBinaryDigitChar(static_cast<int32_t>(U'0')), true);
  ASSERT_EQ(Utf32::isBinaryDigitChar(static_cast<int32_t>(U'1')), true);
  ASSERT_EQ(Utf32::isBinaryDigitChar(static_cast<int32_t>(U'2')), false);
  ASSERT_EQ(Utf32::isBinaryDigitChar(static_cast<int32_t>(U'_')), false);
  ASSERT_EQ(Utf32::isBinaryDigitChar(static_cast<int32_t>(U'_'), true), true);

  ASSERT_EQ(Utf32::isOctalDigitChar(static_cast<int32_t>(U'0')), true);
  ASSERT_EQ(Utf32::isOctalDigitChar(static_cast<int32_t>(U'7')), true);
  ASSERT_EQ(Utf32::isOctalDigitChar(static_cast<int32_t>(U'8')), false);
  ASSERT_EQ(Utf32::isOctalDigitChar(static_cast<int32_t>(U'_')), false);
  ASSERT_EQ(Utf32::isOctalDigitChar(static_cast<int32_t>(U'_'), true), true);

  ASSERT_EQ(Utf32::isDecimalDigitChar(static_cast<int32_t>(U'0')), true);
  ASSERT_EQ(Utf32::isDecimalDigitChar(static_cast<int32_t>(U'9')), true);
  ASSERT_EQ(Utf32::isDecimalDigitChar(static_cast<int32_t>(U'a')), false);
  ASSERT_EQ(Utf32::isDecimalDigitChar(static_cast<int32_t>(U'_')), false);
  ASSERT_EQ(Utf32::isDecimalDigitChar(static_cast<int32_t>(U'_'), true), true);

  ASSERT_EQ(Utf32::isHexadecimalDigitChar(static_cast<int32_t>(U'0')), true);
  ASSERT_EQ(Utf32::isHexadecimalDigitChar(static_cast<int32_t>(U'F')), true);
  ASSERT_EQ(Utf32::isHexadecimalDigitChar(static_cast<int32_t>(U'f')), true);
  ASSERT_EQ(Utf32::isHexadecimalDigitChar(static_cast<int32_t>(U'G')), false);
  ASSERT_EQ(Utf32::isHexadecimalDigitChar(static_cast<int32_t>(U'g')), false);
  ASSERT_EQ(Utf32::isHexadecimalDigitChar(static_cast<int32_t>(U'_')), false);
  ASSERT_EQ(Utf32::isHexadecimalDigitChar(static_cast<int32_t>(U'_'), true),
            true);

  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'0'), 11), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'A'), 11), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'a'), 11), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'B'), 11), false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'b'), 11), false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 11), false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 11, true),
            true);

  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'0'), 36), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'A'), 36), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'a'), 36), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'Z'), 36), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'z'), 36), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'!'), 36), false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 36), false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 36, true),
            true);

  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'0'), 37), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'A'), 37), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'Z'), 37), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'a'), 37), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'b'), 37), false);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'a'), 37, true, false),
      true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'z'), 37, true, false),
      true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'A'), 37, true, false),
      true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'B'), 37, true, false),
      false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 37), false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 37, true),
            true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 37, true, false),
      false);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 37, true, true),
      true);

  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'0'), 62), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'A'), 62), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'Z'), 62), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'a'), 62), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'z'), 62), true);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'!'), 62), false);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'a'), 62, true, false),
      true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'z'), 62, true, false),
      true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'A'), 62, true, false),
      true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'Z'), 62, true, false),
      true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'!'), 62, true, false),
      false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 62), false);
  ASSERT_EQ(Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 62, true),
            true);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 62, true, false),
      false);
  ASSERT_EQ(
      Utf32::isDigitCharByRadix(static_cast<int32_t>(U'_'), 62, true, true),
      true);

  try {
    Utf32::isDigitCharByRadix(static_cast<int32_t>(U'0'), 1);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 1.\n",
                 err->what());
    delete err;
  }

  try {
    Utf32::isDigitCharByRadix(static_cast<int32_t>(U'0'), 63);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 63.\n",
                 err->what());
    delete err;
  }
};

TEST(Utf32CharCodeTest, ToDecimalFromDigitChar) {
  ASSERT_EQ(Utf32::toDecimalFromBinaryChar(static_cast<int32_t>(U'0')),
            static_cast<int32_t>(0));
  ASSERT_EQ(Utf32::toDecimalFromBinaryChar(static_cast<int32_t>(U'1')),
            static_cast<int32_t>(1));
  try {
    Utf32::toDecimalFromBinaryChar(static_cast<int32_t>(U'2'));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 2. digit char = 2.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDecimalFromOctalChar(static_cast<int32_t>(U'0')),
            static_cast<int32_t>(0));
  ASSERT_EQ(Utf32::toDecimalFromOctalChar(static_cast<int32_t>(U'7')),
            static_cast<int32_t>(7));
  try {
    Utf32::toDecimalFromOctalChar(static_cast<int32_t>(U'8'));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 8. digit char = 8.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDecimalFromDecimalChar(static_cast<int32_t>(U'0')),
            static_cast<int32_t>(0));
  ASSERT_EQ(Utf32::toDecimalFromDecimalChar(static_cast<int32_t>(U'9')),
            static_cast<int32_t>(9));
  try {
    Utf32::toDecimalFromDecimalChar(static_cast<int32_t>(U'A'));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 10. digit char = A.\n",
                 err->what());
    delete err;
  }
  try {
    Utf32::toDecimalFromDecimalChar(static_cast<int32_t>(U'a'));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 10. digit char = a.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'0')),
            static_cast<int32_t>(0));
  ASSERT_EQ(Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'9')),
            static_cast<int32_t>(9));
  ASSERT_EQ(Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'A')),
            static_cast<int32_t>(10));
  ASSERT_EQ(Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'a')),
            static_cast<int32_t>(10));
  ASSERT_EQ(Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'F')),
            static_cast<int32_t>(15));
  ASSERT_EQ(Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'f')),
            static_cast<int32_t>(15));
  try {
    Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'G'));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 16. digit char = G.\n",
                 err->what());
    delete err;
  }
  try {
    Utf32::toDecimalFromHexadecimalChar(static_cast<int32_t>(U'g'));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 16. digit char = g.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'0'), 11),
      static_cast<int32_t>(0));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'9'), 11),
      static_cast<int32_t>(9));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'A'), 11),
      static_cast<int32_t>(10));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'a'), 11),
      static_cast<int32_t>(10));
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'B'), 11);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 11. digit char = B.\n",
                 err->what());
    delete err;
  }
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'b'), 11);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 11. digit char = b.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'0'), 36),
      static_cast<int32_t>(0));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'9'), 36),
      static_cast<int32_t>(9));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'A'), 36),
      static_cast<int32_t>(10));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'a'), 36),
      static_cast<int32_t>(10));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'Z'), 36),
      static_cast<int32_t>(35));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'z'), 36),
      static_cast<int32_t>(35));
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'_'), 36);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 36. digit char = _.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'0'), 37),
      static_cast<int32_t>(0));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'9'), 37),
      static_cast<int32_t>(9));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'A'), 37),
      static_cast<int32_t>(10));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'Z'), 37),
      static_cast<int32_t>(35));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'a'), 37),
      static_cast<int32_t>(36));
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'b'), 37);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 37. digit char = b.\n",
                 err->what());
    delete err;
  }
  ASSERT_EQ(Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'a'), 37,
                                                 true),
            static_cast<int32_t>(10));
  ASSERT_EQ(Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'z'), 37,
                                                 true),
            static_cast<int32_t>(35));
  ASSERT_EQ(Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'A'), 37,
                                                 true),
            static_cast<int32_t>(36));
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'B'), 37, true);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ(
        "invalid digit char in radix(lower prefer) = 37. digit char = B.\n",
        err->what());
    delete err;
  }
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'_'), 37);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 37. digit char = _.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'0'), 62),
      static_cast<int32_t>(0));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'9'), 62),
      static_cast<int32_t>(9));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'A'), 62),
      static_cast<int32_t>(10));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'Z'), 62),
      static_cast<int32_t>(35));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'a'), 62),
      static_cast<int32_t>(36));
  ASSERT_EQ(
      Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'z'), 62),
      static_cast<int32_t>(61));
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'_'), 62);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit char in radix = 62. digit char = _.\n",
                 err->what());
    delete err;
  }
  ASSERT_EQ(Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'a'), 62,
                                                 true),
            static_cast<int32_t>(10));
  ASSERT_EQ(Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'z'), 62,
                                                 true),
            static_cast<int32_t>(35));
  ASSERT_EQ(Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'A'), 62,
                                                 true),
            static_cast<int32_t>(36));
  ASSERT_EQ(Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'Z'), 62,
                                                 true),
            static_cast<int32_t>(61));
  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'_'), 62, true);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ(
        "invalid digit char in radix(lower prefer) = 62. digit char = _.\n",
        err->what());
    delete err;
  }

  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'0'), 1);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 1.\n",
                 err->what());
    delete err;
  }

  try {
    Utf32::toDecimalFromDigitCharByRadix(static_cast<int32_t>(U'0'), 63);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 63.\n",
                 err->what());
    delete err;
  }
};

TEST(Utf32CharCodeTest, ToDigitCharFromDecimal) {
  ASSERT_EQ(Utf32::toBinaryCharFromDecimal(static_cast<int32_t>(0)),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toBinaryCharFromDecimal(static_cast<int32_t>(1)),
            static_cast<int32_t>(U'1'));
  try {
    Utf32::toBinaryCharFromDecimal(static_cast<int32_t>(2));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 2. digit is only less than radix. "
                 "digit = 2.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toOctalCharFromDecimal(static_cast<int32_t>(0)),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toOctalCharFromDecimal(static_cast<int32_t>(7)),
            static_cast<int32_t>(U'7'));
  try {
    Utf32::toOctalCharFromDecimal(static_cast<int32_t>(8));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 8. digit is only less than radix. "
                 "digit = 8.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDecimalCharFromDecimal(static_cast<int32_t>(0)),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toDecimalCharFromDecimal(static_cast<int32_t>(9)),
            static_cast<int32_t>(U'9'));
  try {
    Utf32::toDecimalCharFromDecimal(static_cast<int32_t>(10));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 10. digit is only less than radix. "
                 "digit = 10.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(0)),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(9)),
            static_cast<int32_t>(U'9'));
  ASSERT_EQ(Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(10)),
            static_cast<int32_t>(U'a'));
  ASSERT_EQ(Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(15)),
            static_cast<int32_t>(U'f'));
  ASSERT_EQ(
      Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(10), false),
      static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(15), false),
      static_cast<int32_t>(U'F'));
  ASSERT_EQ(Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(10), true),
            static_cast<int32_t>(U'a'));
  ASSERT_EQ(Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(15), true),
            static_cast<int32_t>(U'f'));
  try {
    Utf32::toHexadecimalCharFromDecimal(static_cast<int32_t>(16));
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 16. digit is only less than radix. "
                 "digit = 16.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 11),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 11, false),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 11, true),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 11),
            static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 11, false),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 11, true),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 11),
            static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 11, false),
      static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 11, true),
      static_cast<int32_t>(U'a'));
  try {
    Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(11), 11);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 11. digit is only less than radix. "
                 "digit = 11.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 36),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 36, false),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 36, true),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 36),
            static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 36, false),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 36, true),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 36),
            static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 36, false),
      static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 36, true),
      static_cast<int32_t>(U'a'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 36),
            static_cast<int32_t>(U'Z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 36, false),
      static_cast<int32_t>(U'Z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 36, true),
      static_cast<int32_t>(U'z'));
  try {
    Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(36), 36);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 36. digit is only less than radix. "
                 "digit = 36.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 37),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 37, false),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 37, true),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 37),
            static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 37, false),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 37, true),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 37),
            static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 37, false),
      static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 37, true),
      static_cast<int32_t>(U'a'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 37),
            static_cast<int32_t>(U'Z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 37, false),
      static_cast<int32_t>(U'Z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 37, true),
      static_cast<int32_t>(U'z'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(36), 37),
            static_cast<int32_t>(U'a'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(36), 37, false),
      static_cast<int32_t>(U'a'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(36), 37, true),
      static_cast<int32_t>(U'A'));
  try {
    Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(37), 37);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 37. digit is only less than radix. "
                 "digit = 37.\n",
                 err->what());
    delete err;
  }

  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 62),
            static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 62, false),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(0), 62, true),
      static_cast<int32_t>(U'0'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 62),
            static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 62, false),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(9), 62, true),
      static_cast<int32_t>(U'9'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 62),
            static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 62, false),
      static_cast<int32_t>(U'A'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(10), 62, true),
      static_cast<int32_t>(U'a'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 62),
            static_cast<int32_t>(U'Z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 62, false),
      static_cast<int32_t>(U'Z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(35), 62, true),
      static_cast<int32_t>(U'z'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(36), 62),
            static_cast<int32_t>(U'a'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(36), 62, false),
      static_cast<int32_t>(U'a'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(36), 62, true),
      static_cast<int32_t>(U'A'));
  ASSERT_EQ(Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(61), 62),
            static_cast<int32_t>(U'z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(61), 62, false),
      static_cast<int32_t>(U'z'));
  ASSERT_EQ(
      Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(61), 62, true),
      static_cast<int32_t>(U'Z'));
  try {
    Utf32::toDigitCharFromDecimalByRadix(static_cast<int32_t>(62), 62);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid digit in radix = 62. digit is only less than radix. "
                 "digit = 62.\n",
                 err->what());
    delete err;
  }
};