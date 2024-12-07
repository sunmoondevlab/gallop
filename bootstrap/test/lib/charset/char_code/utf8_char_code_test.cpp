#include "charset/char_code/utf8_char_code.hpp"
#include <gtest/gtest.h>

namespace gallop::CharSet::CharCode {
class Utf8CharCodeTest : public ::testing::Test {};
TEST(Utf8CharCodeTest, CharCodeTypes) {
  ASSERT_EQ(Utf8::isNullCharCode(static_cast<int8_t>(0)), true);
  // BOM
  ASSERT_EQ(Utf8::isBom(static_cast<int32_t>(0xefbbbf)), true);
  ASSERT_EQ(Utf8::isBom(static_cast<int32_t>(0xefbbbe)), false);
  // fetch Length
  // 4 byte
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xf4)), 4);
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xf0)), 4);
  // 3 byte
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xef)), 3);
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xe0)), 3);
  // 2 byte
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xdf)), 2);
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xc2)), 2);
  // 1 byte
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0x7f)), 1);
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0x00)), 1);
  // invalid
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xff)), 0);
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xf5)), 0);
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0xc1)), 0);
  ASSERT_EQ(Utf8::utf8FetchLength(static_cast<int8_t>(0x80)), 0);
  // Continuation Byte
  ASSERT_EQ(Utf8::isContinuationByte(static_cast<int8_t>(0xc0)), false);
  ASSERT_EQ(Utf8::isContinuationByte(static_cast<int8_t>(0xbf)), true);
  ASSERT_EQ(Utf8::isContinuationByte(static_cast<int8_t>(0x80)), true);
  ASSERT_EQ(Utf8::isContinuationByte(static_cast<int8_t>(0x7f)), false);
  // New line
  ASSERT_EQ(Utf8::isNewLine(static_cast<int8_t>(0x0a)), true);
  ASSERT_EQ(Utf8::isNewLine(static_cast<int8_t>(0x0d)), true);
  ASSERT_EQ(Utf8::isNewLine(static_cast<int8_t>(0x09)), false);
  // BE ASCII
  ASSERT_EQ(Utf8::isAscii(static_cast<int8_t>(0x00)), true);
  ASSERT_EQ(Utf8::isAscii(static_cast<int8_t>(0x01)), true);
  ASSERT_EQ(Utf8::isAscii(static_cast<int8_t>(0x7e)), true);
  ASSERT_EQ(Utf8::isAscii(static_cast<int8_t>(0x7f)), true);
  ASSERT_EQ(Utf8::isAscii(static_cast<int8_t>(0x80)), false);
  // 1byte UTF-8
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00000000)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00000001)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000007e)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000007f)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00000080)), false);
  // 2byte UTF-8
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000c280)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000c281)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000dfbe)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000dfbf)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000c180)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000c27f)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000dfc0)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x0000e0bf)), false);
  // 3byte UTF-8
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00e0a080)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00e0a081)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00efbfbe)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00efbfbf)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00dfa080)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00e08080)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00e09080)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00e09f80)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00e0a07f)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00f0bfbf)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00efc0bf)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0x00efbfc0)), false);
  // 4byte UTF-8
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf0908080)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf0908081)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf48fbfbe)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf38fbfbf)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf48fbfbf)), true);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xef908080)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf08f8080)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf0907f80)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf090807f)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf58fbfbe)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf490bfbe)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf48fc0be)), false);
  ASSERT_EQ(Utf8::isValidCharCode(static_cast<int32_t>(0xf48fbfc0)), false);
};
TEST(Utf8CharCodeTest, ToUtf32) {
  // BE BOM
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00efbbbf)),
            static_cast<int32_t>(0x0000feff));
  // LE BOM
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00efbbbf), true),
            static_cast<int32_t>(0xfffe0000));
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00000000)),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00000001)),
            static_cast<int32_t>(0x00000001));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000007e)),
            static_cast<int32_t>(0x0000007e));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000007f)),
            static_cast<int32_t>(0x0000007f));
  // 2byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000c280)),
            static_cast<int32_t>(0x00000080));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000c281)),
            static_cast<int32_t>(0x00000081));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000dfbe)),
            static_cast<int32_t>(0x000007fe));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000dfbf)),
            static_cast<int32_t>(0x000007ff));
  // 3byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00e0a080)),
            static_cast<int32_t>(0x00000800));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00e0a081)),
            static_cast<int32_t>(0x00000801));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00efbfbe)),
            static_cast<int32_t>(0x0000fffe));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00efbfbf)),
            static_cast<int32_t>(0x0000ffff));
  // surrogate pare
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00ed9fbf)),
            static_cast<int32_t>(0x0000d7ff));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00eda080)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00eda081)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00edbfbe)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00edbfbf)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00ee8080)),
            static_cast<int32_t>(0x0000e000));
  // 4byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf08f8080)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf0908080)),
            static_cast<int32_t>(0x00010000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf0908081)),
            static_cast<int32_t>(0x00010001));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf09fa7bf)),
            static_cast<int32_t>(0x0001f9ff));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf0afa89c)),
            static_cast<int32_t>(0x0002fa1c));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf48fbfbf)),
            static_cast<int32_t>(0x0010ffff));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf5bfbfbf)),
            static_cast<int32_t>(0x0000fffd));
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00000000), true),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00000001), true),
            static_cast<int32_t>(0x01000000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000007e), true),
            static_cast<int32_t>(0x7e000000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000007f), true),
            static_cast<int32_t>(0x7f000000));
  // 2byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000c280), true),
            static_cast<int32_t>(0x80000000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000c281), true),
            static_cast<int32_t>(0x81000000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000dfbe), true),
            static_cast<int32_t>(0xfe070000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x0000dfbf), true),
            static_cast<int32_t>(0xff070000));
  // 3byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00e0a080), true),
            static_cast<int32_t>(0x00080000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00e0a081), true),
            static_cast<int32_t>(0x01080000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00efbfbe), true),
            static_cast<int32_t>(0xfeff0000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00efbfbf), true),
            static_cast<int32_t>(0xffff0000));
  // surrogate pare
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00ed9fbf), true),
            static_cast<int32_t>(0xffd70000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00eda080), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00eda081), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00edbfbe), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00edbfbf), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0x00ee8080), true),
            static_cast<int32_t>(0x00e00000));
  // 4byte UTF-8
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf08f8080), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf0908080), true),
            static_cast<int32_t>(0x00000100));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf0908081), true),
            static_cast<int32_t>(0x01000100));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf09fa7bf), true),
            static_cast<int32_t>(0xfff90100));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf0afa89c), true),
            static_cast<int32_t>(0x1cfa0200));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf48fbfbf), true),
            static_cast<int32_t>(0xffff1000));
  ASSERT_EQ(Utf8::toUtf32(static_cast<int32_t>(0xf5bfbfbf), true),
            static_cast<int32_t>(0xfdff0000));
};
TEST(Utf8CharCodeTest, ToUTf16Chunk) {
  std::vector<int16_t> expectChunk;
  expectChunk = {static_cast<int16_t>(0x0000)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0)), expectChunk);
  // BE BOM
  expectChunk = {static_cast<int16_t>(0xfeff)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00efbbbf)), expectChunk);
  // LE BOM
  expectChunk = {static_cast<int16_t>(0xfffe)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00efbbbf), true),
            expectChunk);
  // BE
  // 1byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0009)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000009)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0020)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000020)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0030)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000030)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0041)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000041)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0061)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000061)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x007e)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000007e)), expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0080)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c280)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0081)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c281)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00a0)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c2a0)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00a1)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c2a1)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x00ff)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c3bf)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0100)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c480)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x07fa)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000dfba)), expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0800)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00e0a080)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x0801)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00e0a081)), expectChunk);
  expectChunk = {static_cast<int16_t>(0x1000)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00e18080)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd7fb)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00ed9fbb)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00eda080)), expectChunk);
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00edbfbf)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xf900)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00efa480)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00efbfbd)), expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc00)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf0908080)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc01)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf0908081)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd83e), static_cast<int16_t>(0xddff)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf09fa7bf)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xd87e), static_cast<int16_t>(0xde1c)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf0afa89c)), expectChunk);
  expectChunk = {static_cast<int16_t>(0xdbff), static_cast<int16_t>(0xdfff)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf48fbfbf)), expectChunk);
  // LE
  // 1byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0900)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000009), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x2000)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000020), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x3000)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000030), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x4100)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000041), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x6100)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00000061), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x7e00)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000007e), true),
            expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x8000)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c280), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x8100)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c281), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xa000)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c2a0), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xa100)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c2a1), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xff00)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c3bf), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0001)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000c480), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfa07)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x0000dfba), true),
            expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x0008)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00e0a080), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0108)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00e0a081), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x0010)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00e18080), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfbd7)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00ed9fbb), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00eda080), true),
            expectChunk);
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00edbfbf), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x00f9)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00efa480), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0x00efbfbd), true),
            expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00dc)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf0908080), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x01dc)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf0908081), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x3ed8), static_cast<int16_t>(0xffdd)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf09fa7bf), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0x7ed8), static_cast<int16_t>(0x1cde)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf0afa89c), true),
            expectChunk);
  expectChunk = {static_cast<int16_t>(0xffdb), static_cast<int16_t>(0xffdf)};
  ASSERT_EQ(Utf8::toUtf16Chunk(static_cast<int32_t>(0xf48fbfbf), true),
            expectChunk);
};

TEST(Utf8CharCodeTest, ToUtf8Chunk) {
  std::vector<char> expectChunk;
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0)), expectChunk);

  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbb),
                 static_cast<char>(0xbf)};
  // BE BOM
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00efbbbf)), expectChunk);
  // BE
  // 1byte UTF-8
  expectChunk = {static_cast<char>(0x09)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00000009)), expectChunk);
  expectChunk = {static_cast<char>(0x20)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00000020)), expectChunk);
  expectChunk = {static_cast<char>(0x30)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00000030)), expectChunk);
  expectChunk = {static_cast<char>(0x41)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00000041)), expectChunk);
  expectChunk = {static_cast<char>(0x61)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00000061)), expectChunk);
  expectChunk = {static_cast<char>(0x7e)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000007e)), expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x80)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000c280)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x81)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000c281)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa0)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000c2a0)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa1)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000c2a1)), expectChunk);
  expectChunk = {static_cast<char>(0xc3), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000c3bf)), expectChunk);
  expectChunk = {static_cast<char>(0xc4), static_cast<char>(0x80)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000c480)), expectChunk);
  expectChunk = {static_cast<char>(0xdf), static_cast<char>(0xba)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x0000dfba)), expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00e0a080)), expectChunk);
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x81)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00e0a081)), expectChunk);
  expectChunk = {static_cast<char>(0xe1), static_cast<char>(0x80),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00e18080)), expectChunk);
  expectChunk = {static_cast<char>(0xed), static_cast<char>(0x9f),
                 static_cast<char>(0xbb)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00ed9fbb)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00eda080)), expectChunk);
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00edbfbf)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xa4),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00efa480)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0x00efbfbd)), expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x80)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0xf0908080)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x81)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0xf0908081)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x9f),
                 static_cast<char>(0xa7), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0xf09fa7bf)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0xaf),
                 static_cast<char>(0xa8), static_cast<char>(0x9c)};
  ASSERT_EQ(Utf8::toUtf8Chunk(static_cast<int32_t>(0xf0afa89c)), expectChunk);
};
TEST(Utf8CharCodeTest, ToString) {
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0)), "");
  // BE BOM
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00efbbbf)), "");
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00000009)), "\t");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00000020)), " ");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00000030)), "0");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00000041)), "A");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00000061)), "a");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000007e)), "~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000c280)), "\xc2\x80");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000c281)), "\xc2\x81");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000c2a0)), "\xc2\xa0");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000c2a1)), "¡");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000c3bf)), "ÿ");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000c480)), "Ā");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x0000dfba)), "ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00e0a080)), "ࠀ");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00e0a081)), "ࠁ");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00e18080)), "က");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00ed9fbb)), "ퟻ");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00eda080)), "�");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00edbfbf)), "�");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00efa480)), "豈");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0x00efbfbd)), "�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0xf0908080)), "𐀀");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0xf0908081)), "𐀁");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0xf09fa7bf)), "🧿");
  ASSERT_EQ(Utf8::toString(static_cast<int32_t>(0xf0afa89c)), "鼻");
};

} // namespace gallop::CharSet::CharCode
