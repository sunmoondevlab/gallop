#include "charset/char_code/utf16_char_code.hpp"
#include <gtest/gtest.h>

namespace gallop::CharSet::CharCode {
class Utf16CharCodeTest : public ::testing::Test {};
TEST(Utf16CharCodeTest, CharCodeTypes) {
  ASSERT_EQ(Utf16::isNullCharCode(static_cast<int16_t>(0)), true);
  // BE BOM
  ASSERT_EQ(Utf16::isBom(static_cast<int16_t>(0xfeff)), true);
  ASSERT_EQ(Utf16::isBom(static_cast<int16_t>(0xfefe)), false);
  // LE BOM
  ASSERT_EQ(Utf16::isBom(static_cast<int16_t>(0xfffe), true), true);
  ASSERT_EQ(Utf16::isBom(static_cast<int16_t>(0xfefe), true), false);
  // BE High surrogate
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xd7ff)), false);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xd800)), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xd801)), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xdbfe)), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xdbff)), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xdc00)), false);
  // LE High surrogate
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xffd7), true), false);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0x00d8), true), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0x01d8), true), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xfedb), true), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0xffdb), true), true);
  ASSERT_EQ(Utf16::isHighSurrogate(static_cast<int16_t>(0x00dc), true), false);
  // BE Low surrogate
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xdbff)), false);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xdc00)), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xdc01)), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xdffe)), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xdfff)), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xe000)), false);
  // LE Low surrogate
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xffdb), true), false);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0x00dc), true), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0x01dc), true), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xfedf), true), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0xffdf), true), true);
  ASSERT_EQ(Utf16::isLowSurrogate(static_cast<int16_t>(0x00e0), true), false);
  // BE New line
  ASSERT_EQ(Utf16::isNewLine(static_cast<int16_t>(0x000a)), true);
  ASSERT_EQ(Utf16::isNewLine(static_cast<int16_t>(0x000d)), true);
  ASSERT_EQ(Utf16::isNewLine(static_cast<int16_t>(0x0009)), false);
  // LE New line
  ASSERT_EQ(Utf16::isNewLine(static_cast<int16_t>(0x0a00), true), true);
  ASSERT_EQ(Utf16::isNewLine(static_cast<int16_t>(0x0d00), true), true);
  ASSERT_EQ(Utf16::isNewLine(static_cast<int16_t>(0x0900), true), false);
  // BE ASCII
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x0000)), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x0001)), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x007e)), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x007f)), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x0080)), false);
  // LE ASCII
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x0000), true), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x0100), true), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x7e00), true), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x7f00), true), true);
  ASSERT_EQ(Utf16::isAscii(static_cast<int16_t>(0x8000), true), false);
  // BE Surrogate pair
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xd7ffdc00)), false);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xd800dbff)), false);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xd800dc00)), true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xd801dc01)), true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xdbfedffe)), true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xdbffdfff)), true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xdc00dfff)), false);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xdbffe000)), false);
  // LE Surrogate pair
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xffd700dc), true),
            false);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0x00d8ffdb), true),
            false);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0x00d800dc), true),
            true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0x01d801dc), true),
            true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xfedbfedf), true),
            true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xffdbffdf), true),
            true);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0x00dcffdf), true),
            false);
  ASSERT_EQ(Utf16::isSurrogatePair(static_cast<int32_t>(0xffdb00e0), true),
            false);
};
TEST(Utf16CharCodeTest, SwapEndianness) {
  // BE BOM
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xfeff)),
            static_cast<int16_t>(0xfffe));
  // LE BOM
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xfffe)),
            static_cast<int16_t>(0xfeff));
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0000)),
            static_cast<int16_t>(0x0000));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0001)),
            static_cast<int16_t>(0x0100));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x007e)),
            static_cast<int16_t>(0x7e00));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x007f)),
            static_cast<int16_t>(0x7f00));
  // 2byte UTF-8
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0080)),
            static_cast<int16_t>(0x8000));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0081)),
            static_cast<int16_t>(0x8100));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x07fe)),
            static_cast<int16_t>(0xfe07));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x07ff)),
            static_cast<int16_t>(0xff07));
  // 3byte UTF-8
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0800)),
            static_cast<int16_t>(0x0008));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0801)),
            static_cast<int16_t>(0x0108));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xfffe)),
            static_cast<int16_t>(0xfeff));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xffff)),
            static_cast<int16_t>(0xffff));
  // surrogate pare
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xd7ff)),
            static_cast<int16_t>(0xffd7));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xd800)),
            static_cast<int16_t>(0x00d8));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xd801)),
            static_cast<int16_t>(0x01d8));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xdffe)),
            static_cast<int16_t>(0xfedf));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xdfff)),
            static_cast<int16_t>(0xffdf));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xe000)),
            static_cast<int16_t>(0x00e0));
  // 4byte UTF-8
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0xd800dc00)),
      static_cast<int32_t>(0x00d800dc));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0xd800dc01)),
      static_cast<int32_t>(0x00d801dc));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0xd83eddff)),
      static_cast<int32_t>(0x3ed8ffdd));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0xd87ede1c)),
      static_cast<int32_t>(0x7ed81cde));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0xdbffdfff)),
      static_cast<int32_t>(0xffdbffdf));
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0000)),
            static_cast<int16_t>(0x0000));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0100)),
            static_cast<int16_t>(0x0001));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x7e00)),
            static_cast<int16_t>(0x007e));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x7f00)),
            static_cast<int16_t>(0x007f));
  // 2byte UTF-8
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x8000)),
            static_cast<int16_t>(0x0080));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x8100)),
            static_cast<int16_t>(0x0081));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xfe07)),
            static_cast<int16_t>(0x07fe));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xff07)),
            static_cast<int16_t>(0x07ff));
  // 3byte UTF-8
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0008)),
            static_cast<int16_t>(0x0800));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x0108)),
            static_cast<int16_t>(0x0801));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xfeff)),
            static_cast<int16_t>(0xfffe));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xffff)),
            static_cast<int16_t>(0xffff));
  // surrogate pare
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xffd7)),
            static_cast<int16_t>(0xd7ff));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x00d8)),
            static_cast<int16_t>(0xd800));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x01d8)),
            static_cast<int16_t>(0xd801));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xfedf)),
            static_cast<int16_t>(0xdffe));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0xffdf)),
            static_cast<int16_t>(0xdfff));
  ASSERT_EQ(Utf16::swapEndianness(static_cast<int16_t>(0x00e0)),
            static_cast<int16_t>(0xe000));
  // 4byte UTF-8
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0x00d800dc)),
      static_cast<int32_t>(0xd800dc00));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0x00d801dc)),
      static_cast<int32_t>(0xd800dc01));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0x3ed8ffdd)),
      static_cast<int32_t>(0xd83eddff));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0x7ed81cde)),
      static_cast<int32_t>(0xd87ede1c));
  ASSERT_EQ(
      Utf16::swapEndiannessSurrogatePair(static_cast<int32_t>(0xffdbffdf)),
      static_cast<int32_t>(0xdbffdfff));
};
TEST(Utf16CharCodeTest, ToUtf32) {
  // BE BOM
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfeff)),
            static_cast<int32_t>(0x0000feff));
  // LE BOM
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfffe), true),
            static_cast<int32_t>(0xfffe0000));
  // BE BOM to LE BOM
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfeff), false, true),
            static_cast<int32_t>(0xfffe0000));
  // LE BOM to BE BOM
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfffe), true, true),
            static_cast<int32_t>(0x0000feff));
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0000)),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0001)),
            static_cast<int32_t>(0x00000001));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x007e)),
            static_cast<int32_t>(0x0000007e));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x007f)),
            static_cast<int32_t>(0x0000007f));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000007f)),
            static_cast<int32_t>(0x0000007f));
  // 2byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0080)),
            static_cast<int32_t>(0x00000080));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0081)),
            static_cast<int32_t>(0x00000081));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x07fe)),
            static_cast<int32_t>(0x000007fe));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x07ff)),
            static_cast<int32_t>(0x000007ff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x000007ff)),
            static_cast<int32_t>(0x000007ff));
  // 3byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0800)),
            static_cast<int32_t>(0x00000800));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0801)),
            static_cast<int32_t>(0x00000801));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfffe)),
            static_cast<int32_t>(0x0000fffe));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffff)),
            static_cast<int32_t>(0x0000ffff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000ffff)),
            static_cast<int32_t>(0x0000ffff));
  // surrogate pare
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xd7ff)),
            static_cast<int32_t>(0x0000d7ff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xd800)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xd801)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xdffe)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xdfff)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xe000)),
            static_cast<int32_t>(0x0000e000));
  // 4byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd7ffdc00)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd800dbff)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd800dc00)),
            static_cast<int32_t>(0x00010000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd800dc01)),
            static_cast<int32_t>(0x00010001));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd83eddff)),
            static_cast<int32_t>(0x0001f9ff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd87ede1c)),
            static_cast<int32_t>(0x0002fa1c));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdbffdfff)),
            static_cast<int32_t>(0x0010ffff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdc00dfff)),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdbffe000)),
            static_cast<int32_t>(0x0000fffd));
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0000), true),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0100), true),
            static_cast<int32_t>(0x01000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x7e00), true),
            static_cast<int32_t>(0x7e000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x7f00), true),
            static_cast<int32_t>(0x7f000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00007f00), true),
            static_cast<int32_t>(0x7f000000));
  // 2byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x8000), true),
            static_cast<int32_t>(0x80000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x8100), true),
            static_cast<int32_t>(0x81000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfe07), true),
            static_cast<int32_t>(0xfe070000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xff07), true),
            static_cast<int32_t>(0xff070000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000ff07), true),
            static_cast<int32_t>(0xff070000));
  // 3byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0008), true),
            static_cast<int32_t>(0x00080000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0108), true),
            static_cast<int32_t>(0x01080000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfeff), true),
            static_cast<int32_t>(0xfeff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffff), true),
            static_cast<int32_t>(0xffff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000ffff), true),
            static_cast<int32_t>(0xffff0000));
  // surrogate pare
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffd7), true),
            static_cast<int32_t>(0xffd70000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x00d8), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x01d8), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfedf), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffdf), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x00e0), true),
            static_cast<int32_t>(0x00e00000));
  // 4byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xffd700dc), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00d8ffdb), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00d800dc), true),
            static_cast<int32_t>(0x00000100));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00d801dc), true),
            static_cast<int32_t>(0x01000100));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x3ed8ffdd), true),
            static_cast<int32_t>(0xfff90100));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x7ed81cde), true),
            static_cast<int32_t>(0x1cfa0200));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xffdbffdf), true),
            static_cast<int32_t>(0xffff1000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00dcffdf), true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdbffe000), true),
            static_cast<int32_t>(0xfdff0000));
  // BE to LE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0000), false, true),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0001), false, true),
            static_cast<int32_t>(0x01000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x007e), false, true),
            static_cast<int32_t>(0x7e000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x007f), false, true),
            static_cast<int32_t>(0x7f000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000007f), false, true),
            static_cast<int32_t>(0x7f000000));
  // 2byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0080), false, true),
            static_cast<int32_t>(0x80000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0081), false, true),
            static_cast<int32_t>(0x81000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x07fe), false, true),
            static_cast<int32_t>(0xfe070000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x07ff), false, true),
            static_cast<int32_t>(0xff070000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x000007ff), false, true),
            static_cast<int32_t>(0xff070000));
  // 3byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0800), false, true),
            static_cast<int32_t>(0x00080000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0801), false, true),
            static_cast<int32_t>(0x01080000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfffe), false, true),
            static_cast<int32_t>(0xfeff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffff), false, true),
            static_cast<int32_t>(0xffff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000ffff), false, true),
            static_cast<int32_t>(0xffff0000));
  // surrogate pare
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xd7ff), false, true),
            static_cast<int32_t>(0xffd70000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xd800), false, true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xd801), false, true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xdffe), false, true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xdfff), false, true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xe000), false, true),
            static_cast<int32_t>(0x00e00000));
  // 4byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd7ffdc00), false, true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd800dbff), false, true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd800dc00), false, true),
            static_cast<int32_t>(0x00000100));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd800dc01), false, true),
            static_cast<int32_t>(0x01000100));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd83eddff), false, true),
            static_cast<int32_t>(0xfff90100));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xd87ede1c), false, true),
            static_cast<int32_t>(0x1cfa0200));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdbffdfff), false, true),
            static_cast<int32_t>(0xffff1000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdc00dfff), false, true),
            static_cast<int32_t>(0xfdff0000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdbffe000), false, true),
            static_cast<int32_t>(0xfdff0000));
  // LE to BE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0000), true, true),
            static_cast<int32_t>(0x00000000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0100), true, true),
            static_cast<int32_t>(0x00000001));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x7e00), true, true),
            static_cast<int32_t>(0x0000007e));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x7f00), true, true),
            static_cast<int32_t>(0x0000007f));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00007f00), true, true),
            static_cast<int32_t>(0x0000007f));
  // 2byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x8000), true, true),
            static_cast<int32_t>(0x00000080));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x8100), true, true),
            static_cast<int32_t>(0x00000081));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfe07), true, true),
            static_cast<int32_t>(0x000007fe));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xff07), true, true),
            static_cast<int32_t>(0x000007ff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000ff07), true, true),
            static_cast<int32_t>(0x000007ff));
  // 3byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0008), true, true),
            static_cast<int32_t>(0x00000800));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x0108), true, true),
            static_cast<int32_t>(0x00000801));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfeff), true, true),
            static_cast<int32_t>(0x0000fffe));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffff), true, true),
            static_cast<int32_t>(0x0000ffff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x0000ffff), true, true),
            static_cast<int32_t>(0x0000ffff));
  // surrogate pare
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffd7), true, true),
            static_cast<int32_t>(0x0000d7ff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x00d8), true, true),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x01d8), true, true),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xfedf), true, true),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0xffdf), true, true),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int16_t>(0x00e0), true, true),
            static_cast<int32_t>(0x0000e000));
  // 4byte UTF-8
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xffd700dc), true, true),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00d8ffdb), true, true),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00d800dc), true, true),
            static_cast<int32_t>(0x00010000));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00d801dc), true, true),
            static_cast<int32_t>(0x00010001));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x3ed8ffdd), true, true),
            static_cast<int32_t>(0x0001f9ff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x7ed81cde), true, true),
            static_cast<int32_t>(0x0002fa1c));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xffdbffdf), true, true),
            static_cast<int32_t>(0x0010ffff));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0x00dcffdf), true, true),
            static_cast<int32_t>(0x0000fffd));
  ASSERT_EQ(Utf16::toUtf32(static_cast<int32_t>(0xdbffe000), true, true),
            static_cast<int32_t>(0x0000fffd));
};
TEST(Utf16CharCodeTest, ToUtf8Chunk) {
  std::vector<char> expectChunk;
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0)), expectChunk);

  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbb),
                 static_cast<char>(0xbf)};
  // BE BOM
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xfeff)), expectChunk);
  // LE BOM
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xfffe), true),
            expectChunk);
  // BE
  // 1byte UTF-8
  expectChunk = {static_cast<char>(0x09)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0009)), expectChunk);
  expectChunk = {static_cast<char>(0x20)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0020)), expectChunk);
  expectChunk = {static_cast<char>(0x30)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0030)), expectChunk);
  expectChunk = {static_cast<char>(0x41)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0041)), expectChunk);
  expectChunk = {static_cast<char>(0x61)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0061)), expectChunk);
  expectChunk = {static_cast<char>(0x7e)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x007e)), expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0080)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x81)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0081)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa0)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x00a0)), expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa1)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x00a1)), expectChunk);
  expectChunk = {static_cast<char>(0xc3), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x00ff)), expectChunk);
  expectChunk = {static_cast<char>(0xc4), static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0100)), expectChunk);
  expectChunk = {static_cast<char>(0xdf), static_cast<char>(0xba)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x07fa)), expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0800)), expectChunk);
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x81)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0801)), expectChunk);
  expectChunk = {static_cast<char>(0xe1), static_cast<char>(0x80),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x1000)), expectChunk);
  expectChunk = {static_cast<char>(0xed), static_cast<char>(0x9f),
                 static_cast<char>(0xbb)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xd7fb)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xd800)), expectChunk);
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xdfff)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xa4),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xf900)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xfffd)), expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xd7ffdc00)), expectChunk);
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xd800dbff)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xd800dc00)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x81)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xd800dc01)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x9f),
                 static_cast<char>(0xa7), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xd83eddff)), expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0xaf),
                 static_cast<char>(0xa8), static_cast<char>(0x9c)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xd87ede1c)), expectChunk);
  expectChunk = {static_cast<char>(0xf4), static_cast<char>(0x8f),
                 static_cast<char>(0xbf), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xdbffdfff)), expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xdc00dfff)), expectChunk);
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xdbffe000)), expectChunk);
  // LE
  // 1byte UTF-8
  expectChunk = {static_cast<char>(0x09)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0900), true),
            expectChunk);
  expectChunk = {static_cast<char>(0x20)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x2000), true),
            expectChunk);
  expectChunk = {static_cast<char>(0x30)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x3000), true),
            expectChunk);
  expectChunk = {static_cast<char>(0x41)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x4100), true),
            expectChunk);
  expectChunk = {static_cast<char>(0x61)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x6100), true),
            expectChunk);
  expectChunk = {static_cast<char>(0x7e)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x7e00), true),
            expectChunk);
  // 2 byte UTF-8
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x8000), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0x81)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x8100), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa0)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xa000), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xc2), static_cast<char>(0xa1)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xa100), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xc3), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xff00), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xc4), static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0001), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xdf), static_cast<char>(0xba)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xfa07), true),
            expectChunk);
  // 3 byte UTF-8
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0008), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xe0), static_cast<char>(0xa0),
                 static_cast<char>(0x81)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0108), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xe1), static_cast<char>(0x80),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x0010), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xed), static_cast<char>(0x9f),
                 static_cast<char>(0xbb)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xfbd7), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x00d8), true),
            expectChunk);
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xffdf), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xa4),
                 static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0x00f9), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int16_t>(0xfdff), true),
            expectChunk);
  // 4 byte UTF-8
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xffd700dc), true),
            expectChunk);
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0x00d8ffdb), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x80)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0x00d800dc), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x90),
                 static_cast<char>(0x80), static_cast<char>(0x81)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0x00d801dc), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0x9f),
                 static_cast<char>(0xa7), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0x3ed8ffdd), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xf0), static_cast<char>(0xaf),
                 static_cast<char>(0xa8), static_cast<char>(0x9c)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0x7ed81cde), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xf4), static_cast<char>(0x8f),
                 static_cast<char>(0xbf), static_cast<char>(0xbf)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xffdbffdf), true),
            expectChunk);
  expectChunk = {static_cast<char>(0xef), static_cast<char>(0xbf),
                 static_cast<char>(0xbd)};
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0x00dcffdf), true),
            expectChunk);
  ASSERT_EQ(Utf16::toUtf8Chunk(static_cast<int32_t>(0xffdb00e0), true),
            expectChunk);
};
TEST(Utf16CharCodeTest, ToString) {
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0)), "");
  // BE BOM
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xfeff)), "");
  // LE BOM
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xfffe), true), "");
  // BE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0009)), "\t");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0020)), " ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0030)), "0");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0041)), "A");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0061)), "a");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x007e)), "~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0080)), "\xc2\x80");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0081)), "\xc2\x81");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x00a0)), "\xc2\xa0");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x00a1)), "¡");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x00ff)), "ÿ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0100)), "Ā");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x07fa)), "ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0800)), "ࠀ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0801)), "ࠁ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x1000)), "က");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xd7fb)), "ퟻ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xd800)), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xdfff)), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xf900)), "豈");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xfffd)), "�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xd7ffdc00)), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xd800dbff)), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xd800dc00)), "𐀀");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xd800dc01)), "𐀁");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xd83eddff)), "🧿");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xd87ede1c)), "鼻");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xdc00dfff)), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xdbffe000)), "�");
  // LE
  // 1byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0900), true), "\t");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x2000), true), " ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x3000), true), "0");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x4100), true), "A");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x6100), true), "a");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x7e00), true), "~");
  // 2 byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x8000), true), "\xc2\x80");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x8100), true), "\xc2\x81");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xa000), true), "\xc2\xa0");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xa100), true), "¡");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xff00), true), "ÿ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0001), true), "Ā");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xfa07), true), "ߺ");
  // 3 byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0008), true), "ࠀ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0108), true), "ࠁ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x0010), true), "က");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xfbd7), true), "ퟻ");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x00d8), true), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xffdf), true), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0x00f9), true), "豈");
  ASSERT_EQ(Utf16::toString(static_cast<int16_t>(0xfdff), true), "�");
  // 4 byte UTF-8
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xffd700dc), true), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0x00d8ffdb), true), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0x00d800dc), true), "𐀀");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0x00d801dc), true), "𐀁");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0x3ed8ffdd), true), "🧿");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0x7ed81cde), true), "鼻");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0x00dcffdf), true), "�");
  ASSERT_EQ(Utf16::toString(static_cast<int32_t>(0xffdb00e0), true), "�");
};

} // namespace gallop::CharSet::CharCode
