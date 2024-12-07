// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/string/utf8_string.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

namespace gallop::CharSet::String {
class Utf8StringTest : public ::testing::Test {};
TEST(Utf8StringTest, StringTypes) {
  // null string
  ASSERT_EQ(Utf8::isNullString(""), true);
  ASSERT_EQ(Utf8::isNullString(std::vector<char>()), true);
  ASSERT_EQ(Utf8::isNullString("a"), false);
  ASSERT_EQ(Utf8::isNullString(std::vector<char>{static_cast<char>(0x7e)}),
            false);
  ASSERT_EQ(Utf8::isNullString(std::vector<char>{static_cast<char>(0xef),
                                                 static_cast<char>(0xbb),
                                                 static_cast<char>(0xbf)}),
            true);
  // UTF-8
  // BOM
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{static_cast<char>(0xef),
                                                  static_cast<char>(0xbb),
                                                  static_cast<char>(0xbf)}),
            true);
  // invalid
  // 4byte
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xf4),
                static_cast<char>(0x80),
                static_cast<char>(0x80),
            }),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xf0),
                static_cast<char>(0x8f),
                static_cast<char>(0x80),
                static_cast<char>(0x80),
            }),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xf4),
                static_cast<char>(0x90),
                static_cast<char>(0x80),
                static_cast<char>(0x80),
            }),
            false);
  // 3byte
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{static_cast<char>(0xef),
                                                  static_cast<char>(0xff)}),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xe0),
                static_cast<char>(0x9f),
                static_cast<char>(0x80),
            }),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xed),
                static_cast<char>(0xa0),
                static_cast<char>(0x80),
            }),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xed),
                static_cast<char>(0xbf),
                static_cast<char>(0xbf),
            }),
            false);
  // 2byte
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xc2),
            }),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xc2),
                static_cast<char>(0xc0),
            }),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0xc1),
            }),
            false);
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0x80),
            }),
            false);
  // valid
  ASSERT_EQ(Utf8::isValidString(std::vector<char>{
                static_cast<char>(0x01), static_cast<char>(0x7e),
                static_cast<char>(0xc2), static_cast<char>(0x80),
                static_cast<char>(0xdf), static_cast<char>(0xbf),
                static_cast<char>(0xe0), static_cast<char>(0xa0),
                static_cast<char>(0x80), static_cast<char>(0xef),
                static_cast<char>(0xbf), static_cast<char>(0xbf),
                static_cast<char>(0xf0), static_cast<char>(0x90),
                static_cast<char>(0x80), static_cast<char>(0x80),
                static_cast<char>(0xf4), static_cast<char>(0x8f),
                static_cast<char>(0xbf), static_cast<char>(0xbf),
            }),
            true);
  ASSERT_EQ(Utf8::isValidString(" 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
            true);
  // ascii
  ASSERT_EQ(Utf8::isAsciiString(std::vector<char>{
                static_cast<char>(0x01),
                static_cast<char>(0x01),
                static_cast<char>(0x7e),
            }),
            true);
  ASSERT_EQ(Utf8::isAsciiString(" 0Aa~"), true);
  ASSERT_EQ(Utf8::isAsciiString(std::vector<char>{
                static_cast<char>(0x01), static_cast<char>(0x7e),
                static_cast<char>(0xc2), static_cast<char>(0x80),
                static_cast<char>(0xdf), static_cast<char>(0xbf),
                static_cast<char>(0xe0), static_cast<char>(0xa0),
                static_cast<char>(0x80), static_cast<char>(0xef),
                static_cast<char>(0xbf), static_cast<char>(0xbf),
                static_cast<char>(0xf0), static_cast<char>(0x90),
                static_cast<char>(0x80), static_cast<char>(0x80),
                static_cast<char>(0xf4), static_cast<char>(0x8f),
                static_cast<char>(0xbf), static_cast<char>(0xbf),
            }),
            false);
  ASSERT_EQ(Utf8::isAsciiString(" 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
            false);
};
TEST(Utf8StringTest, ToU8Data) {
  std::vector<char> expectUtf8;
  // BOM
  expectUtf8 = {static_cast<char>(0xef), static_cast<char>(0xbb),
                static_cast<char>(0xbf)};
  ASSERT_EQ(Utf8::toU8Data("\xef\xbb\xbf", true), expectUtf8);
  // without BOM
  expectUtf8 = {};
  ASSERT_EQ(Utf8::toU8Data("\xef\xbb\xbf\xef\xbb\xbf", false), expectUtf8);

  // UTF-8
  expectUtf8 = {
      static_cast<char>(0x20), //
      static_cast<char>(0x30), //
      static_cast<char>(0x41), //
      static_cast<char>(0x61), //
      static_cast<char>(0x7e), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd),                          //
      static_cast<char>(0xc2), static_cast<char>(0x80), //
      static_cast<char>(0xc2), static_cast<char>(0xa0), //
      static_cast<char>(0xc3), static_cast<char>(0xbf), //
      static_cast<char>(0xc4), static_cast<char>(0x80), //
      static_cast<char>(0xdf), static_cast<char>(0xbf), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xe0), static_cast<char>(0xa0),
      static_cast<char>(0x80), //
      static_cast<char>(0xe9), static_cast<char>(0xbf),
      static_cast<char>(0xbf), //
      static_cast<char>(0xea), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xed), static_cast<char>(0x9f),
      static_cast<char>(0xbb), //
      static_cast<char>(0xef), static_cast<char>(0xa4),
      static_cast<char>(0x80), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xf0), static_cast<char>(0x90), static_cast<char>(0x83),
      static_cast<char>(0xba), //
      static_cast<char>(0xf0), static_cast<char>(0xa0), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xf0), static_cast<char>(0xaf), static_cast<char>(0xa8),
      static_cast<char>(0x9c), //
      static_cast<char>(0xf0), static_cast<char>(0xb0), static_cast<char>(0xbb),
      static_cast<char>(0x9d), //
      static_cast<char>(0xf0), static_cast<char>(0xb1), static_cast<char>(0x81),
      static_cast<char>(0xac), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xe3), static_cast<char>(0x81),
      static_cast<char>(0x82), //
      static_cast<char>(0xe3), static_cast<char>(0x81),
      static_cast<char>(0x84), //
      static_cast<char>(0xe3), static_cast<char>(0x81),
      static_cast<char>(0x86), //
      static_cast<char>(0xe3), static_cast<char>(0x81),
      static_cast<char>(0x88), //
      static_cast<char>(0xe3), static_cast<char>(0x81),
      static_cast<char>(0x8a), //
  };
  ASSERT_EQ(Utf8::toU8Data(" 0Aa~"
                           "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                           "\xe0\xbf\xc0\xf0\xbf\xbf\xc0あいうえお"),
            expectUtf8);
};
TEST(Utf8StringTest, ToU16Data) {
  // BE BOM
  ASSERT_EQ(Utf8::toU16Data("\xef\xbb\xbf", false, true),
            std::vector<int16_t>{static_cast<int16_t>(0xfeff)});
  // LE BOM
  ASSERT_EQ(Utf8::toU16Data("\xef\xbb\xbf", true, true),
            std::vector<int16_t>{static_cast<int16_t>(0xfffe)});
  // // without BOM
  // BE BOM
  ASSERT_EQ(Utf8::toU16Data("\xef\xbb\xbf\xef\xbb\xbf", false, false),
            std::vector<int16_t>());
  // LE BOM
  ASSERT_EQ(Utf8::toU16Data("\xef\xbb\xbf\xef\xbb\xbf", true, false),
            std::vector<int16_t>());
  // BE
  std::vector<int16_t> expectUtf16{
      static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
      static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
      static_cast<int16_t>(0x007e), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0x0080), static_cast<int16_t>(0x00a0),
      static_cast<int16_t>(0x00ff), static_cast<int16_t>(0x0100),
      static_cast<int16_t>(0x07ff), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0x0800), static_cast<int16_t>(0x9fff),
      static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
      static_cast<int16_t>(0xf900), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdcfa),
      static_cast<int16_t>(0xd840), static_cast<int16_t>(0xdc00),
      static_cast<int16_t>(0xd87e), static_cast<int16_t>(0xde1c),
      static_cast<int16_t>(0xd883), static_cast<int16_t>(0xdedd),
      static_cast<int16_t>(0xd884), static_cast<int16_t>(0xdc6c),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0x3042),
      static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
      static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(
      Utf8::toU16Data(" 0Aa~"
                      "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                      "\xe0\xbf\xc0\xf0\xbf\xbf\xc0\xef\xbb\xbfあいうえお"),
      expectUtf16);
  // LE
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x8000), static_cast<int16_t>(0xa000),
                 static_cast<int16_t>(0xff00), static_cast<int16_t>(0x0001),
                 static_cast<int16_t>(0xff07), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x00d8), static_cast<int16_t>(0xfadc),
                 static_cast<int16_t>(0x40d8), static_cast<int16_t>(0x00dc),
                 static_cast<int16_t>(0x7ed8), static_cast<int16_t>(0x1cde),
                 static_cast<int16_t>(0x83d8), static_cast<int16_t>(0xddde),
                 static_cast<int16_t>(0x84d8), static_cast<int16_t>(0x6cdc),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(
      Utf8::toU16Data(" 0Aa~"
                      "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                      "\xe0\xbf\xc0\xf0\xbf\xbf\xc0\xef\xbb\xbfあいうえお",
                      true),
      expectUtf16);
};
TEST(Utf8StringTest, ToU32Data) {
  // BE BOM
  ASSERT_EQ(Utf8::toU32Data("\xef\xbb\xbf", false, true),
            std::vector<int32_t>{static_cast<int32_t>(0x0000feff)});
  // LE BOM
  ASSERT_EQ(Utf8::toU32Data("\xef\xbb\xbf", true, true),
            std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)});
  // without BOM
  // BE BOM
  ASSERT_EQ(Utf8::toU32Data("\xef\xbb\xbf\xef\xbb\xbf", false, false),
            std::vector<int32_t>());
  // LE BOM
  ASSERT_EQ(Utf8::toU32Data("\xef\xbb\xbf\xef\xbb\xbf", true, false),
            std::vector<int32_t>());
  // BE
  std::vector<int32_t> expectUtf32{
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00000080), static_cast<int32_t>(0x000000a0),
      static_cast<int32_t>(0x000000ff), static_cast<int32_t>(0x00000100),
      static_cast<int32_t>(0x000007ff), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x000100fa), static_cast<int32_t>(0x00020000),
      static_cast<int32_t>(0x0002fa1c), static_cast<int32_t>(0x00030edd),
      static_cast<int32_t>(0x0003106c), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x00003042),
      static_cast<int32_t>(0x00003044), static_cast<int32_t>(0x00003046),
      static_cast<int32_t>(0x00003048), static_cast<int32_t>(0x0000304a)};
  ASSERT_EQ(Utf8::toU32Data(" 0Aa~"
                            "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                            "\xe0\xbf\xc0\xf0\xbf\xbf\xc0あいうえお"),
            expectUtf32);
  // LE
  expectUtf32 = {
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x80000000), static_cast<int32_t>(0xa0000000),
      static_cast<int32_t>(0xff000000), static_cast<int32_t>(0x00010000),
      static_cast<int32_t>(0xff070000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfa000100), static_cast<int32_t>(0x00000200),
      static_cast<int32_t>(0x1cfa0200), static_cast<int32_t>(0xdd0e0300),
      static_cast<int32_t>(0x6c100300), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0x42300000),
      static_cast<int32_t>(0x44300000), static_cast<int32_t>(0x46300000),
      static_cast<int32_t>(0x48300000), static_cast<int32_t>(0x4a300000)};
  ASSERT_EQ(Utf8::toU32Data(" 0Aa~"
                            "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                            "\xe0\xbf\xc0\xf0\xbf\xbf\xc0あいうえお",
                            true),
            expectUtf32);
};
TEST(Utf8StringTest, ToU8String) {
  // BOM
  ASSERT_EQ(Utf8::toU8String("\xef\xbb\xbf"), "");
  ASSERT_EQ(Utf8::toU8String(std::vector<char>{
                static_cast<char>(0xef), static_cast<char>(0xbb),
                static_cast<char>(0xbf), static_cast<char>(0xef),
                static_cast<char>(0xbb), static_cast<char>(0xbf)}),
            "");
  ASSERT_EQ(Utf8::toU8String(" 0Aa~"
                             "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                             "\xe0\xbf\xc0\xf0\xbf\xbf\xc0あいうえお"),
            " 0Aa~�\xc2\x80 ÿĀ߿�ࠀ鿿ꀀퟻ豈�𐃺𠀀鼻𰻝𱁬��"
            "����あいうえお");
};
TEST(Utf8StringTest, ToU16String) {
  // BOM
  ASSERT_EQ(Utf8::toU16String("\xef\xbb\xbf"), u"");
  ASSERT_EQ(Utf8::toU16String(std::vector<char>{
                static_cast<char>(0xef), static_cast<char>(0xbb),
                static_cast<char>(0xbf), static_cast<char>(0xef),
                static_cast<char>(0xbb), static_cast<char>(0xbf)}),
            u"");
  ASSERT_EQ(
      Utf8::toU16String(" 0Aa~"
                        "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                        "\xe0\xbf\xc0\xf0\xbf\xbf\xc0あいうえお"),
      u" 0Aa~�\x80 ÿĀ߿�ࠀ鿿ꀀퟻ豈�𐃺𠀀鼻𰻝𱁬��"
      u"����あいうえお");
};
TEST(Utf8StringTest, ToU32String) {
  // BOM
  ASSERT_EQ(Utf8::toU32String("\xef\xbb\xbf"), U"");
  ASSERT_EQ(Utf8::toU32String(std::vector<char>{
                static_cast<char>(0xef), static_cast<char>(0xbb),
                static_cast<char>(0xbf), static_cast<char>(0xef),
                static_cast<char>(0xbb), static_cast<char>(0xbf)}),
            U"");
  ASSERT_EQ(
      Utf8::toU32String(" 0Aa~"
                        "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
                        "\xe0\xbf\xc0\xf0\xbf\xbf\xc0あいうえお"),
      U" 0Aa~�\x80 ÿĀ߿�ࠀ鿿ꀀퟻ豈�𐃺𠀀鼻𰻝𱁬��"
      U"����あいうえお");
};

} // namespace gallop::CharSet::String
