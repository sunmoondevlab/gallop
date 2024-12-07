// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/string/utf32_string.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

namespace gallop::CharSet::String {
class Utf32StringTest : public ::testing::Test {};
TEST(Utf32StringTest, StringTypes) {
  // null string
  ASSERT_EQ(Utf32::isNullString(U""), true);
  ASSERT_EQ(Utf32::isNullString(U"a"), false);
  // BE
  ASSERT_EQ(Utf32::isNullString(std::vector<int32_t>()), true);
  ASSERT_EQ(Utf32::isNullString(
                std::vector<int32_t>{static_cast<int32_t>(0x0000feff)}),
            true);
  ASSERT_EQ(Utf32::isNullString(
                std::vector<int32_t>{static_cast<int32_t>(0x0000007e)}),
            false);
  // LE
  ASSERT_EQ(Utf32::isNullString(std::vector<int32_t>(), true), true);
  ASSERT_EQ(Utf32::isNullString(
                std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)}, true),
            true);
  ASSERT_EQ(Utf32::isNullString(
                std::vector<int32_t>{static_cast<int32_t>(0x7e000000)}, true),
            false);
  // UTF-32
  // BE BOM
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{static_cast<int32_t>(0x0000feff)}),
            true);
  // invalid
  // 4byte
  ASSERT_EQ(Utf32::isValidString(std::vector<int32_t>{
                static_cast<int32_t>(0x00110000),
            }),
            false);
  // 3byte
  ASSERT_EQ(Utf32::isValidString(std::vector<int32_t>{
                static_cast<int32_t>(0x0000d800),
            }),
            false);
  ASSERT_EQ(Utf32::isValidString(std::vector<int32_t>{
                static_cast<int32_t>(0x0000dbff),
            }),
            false);
  ASSERT_EQ(Utf32::isValidString(std::vector<int32_t>{
                static_cast<int32_t>(0x0000dc00),
            }),
            false);
  ASSERT_EQ(Utf32::isValidString(std::vector<int32_t>{
                static_cast<int32_t>(0x0000dfff),
            }),
            false);
  ASSERT_EQ(
      Utf32::isValidString(std::vector<int32_t>{
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
          static_cast<int32_t>(0x6c100300), static_cast<int32_t>(0x42300000),
          static_cast<int32_t>(0x44300000), static_cast<int32_t>(0x46300000),
          static_cast<int32_t>(0x48300000), static_cast<int32_t>(0x4a300000)}),
      false);
  // valid
  ASSERT_EQ(
      Utf32::isValidString(std::vector<int32_t>{
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
          static_cast<int32_t>(0x0003106c), static_cast<int32_t>(0x00003042),
          static_cast<int32_t>(0x00003044), static_cast<int32_t>(0x00003046),
          static_cast<int32_t>(0x00003048), static_cast<int32_t>(0x0000304a),
      }),
      true);
  ASSERT_EQ(
      Utf32::isValidString(U" 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
      true);
  // LE BOM
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)}, true),
            true);
  // invalid
  // 4byte
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0x00001100),
                },
                true),
            false);
  // 3byte
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0x00d80000),
                },
                true),
            false);
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0xffdb0000),
                },
                true),
            false);
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0x00dc0000),
                },
                true),
            false);
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0xffdf0000),
                },
                true),
            false);
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0x00000020),
                    static_cast<int32_t>(0x00000030),
                    static_cast<int32_t>(0x00000041),
                    static_cast<int32_t>(0x00000061),
                    static_cast<int32_t>(0x0000007e),
                    static_cast<int32_t>(0x0000fffd),
                    static_cast<int32_t>(0x00000080),
                    static_cast<int32_t>(0x000000a0),
                    static_cast<int32_t>(0x000000ff),
                    static_cast<int32_t>(0x00000100),
                    static_cast<int32_t>(0x000007ff),
                    static_cast<int32_t>(0x0000fffd),
                    static_cast<int32_t>(0x00000800),
                    static_cast<int32_t>(0x00009fff),
                    static_cast<int32_t>(0x0000a000),
                    static_cast<int32_t>(0x0000d7fb),
                    static_cast<int32_t>(0x0000f900),
                    static_cast<int32_t>(0x0000fffd),
                    static_cast<int32_t>(0x000100fa),
                    static_cast<int32_t>(0x00020000),
                    static_cast<int32_t>(0x0002fa1c),
                    static_cast<int32_t>(0x00030edd),
                    static_cast<int32_t>(0x0003106c),
                    static_cast<int32_t>(0x00003042),
                    static_cast<int32_t>(0x00003044),
                    static_cast<int32_t>(0x00003046),
                    static_cast<int32_t>(0x00003048),
                    static_cast<int32_t>(0x0000304a),
                },
                true),
            false);
  // valid
  ASSERT_EQ(Utf32::isValidString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0x20000000),
                    static_cast<int32_t>(0x30000000),
                    static_cast<int32_t>(0x41000000),
                    static_cast<int32_t>(0x61000000),
                    static_cast<int32_t>(0x7e000000),
                    static_cast<int32_t>(0xfdff0000),
                    static_cast<int32_t>(0x80000000),
                    static_cast<int32_t>(0xa0000000),
                    static_cast<int32_t>(0xff000000),
                    static_cast<int32_t>(0x00010000),
                    static_cast<int32_t>(0xff070000),
                    static_cast<int32_t>(0xfdff0000),
                    static_cast<int32_t>(0x00080000),
                    static_cast<int32_t>(0xff9f0000),
                    static_cast<int32_t>(0x00a00000),
                    static_cast<int32_t>(0xfbd70000),
                    static_cast<int32_t>(0x00f90000),
                    static_cast<int32_t>(0xfdff0000),
                    static_cast<int32_t>(0xfa000100),
                    static_cast<int32_t>(0x00000200),
                    static_cast<int32_t>(0x1cfa0200),
                    static_cast<int32_t>(0xdd0e0300),
                    static_cast<int32_t>(0x6c100300),
                    static_cast<int32_t>(0x42300000),
                    static_cast<int32_t>(0x44300000),
                    static_cast<int32_t>(0x46300000),
                    static_cast<int32_t>(0x48300000),
                    static_cast<int32_t>(0x4a300000),
                },
                true),
            true);
  // ascii
  ASSERT_EQ(Utf32::isAsciiString(std::vector<int32_t>{
                static_cast<int32_t>(0x00000001),
                static_cast<int32_t>(0x00000001),
                static_cast<int32_t>(0x0000007e),
            }),
            true);
  ASSERT_EQ(Utf32::isAsciiString(U" 0Aa~"), true);
  ASSERT_EQ(Utf32::isAsciiString(std::vector<int32_t>{
                static_cast<int32_t>(0x00000001),
                static_cast<int32_t>(0x0000007e),
                static_cast<int32_t>(0x00000080),
            }),
            false);
  ASSERT_EQ(Utf32::isAsciiString(
                std::vector<int32_t>{
                    static_cast<int32_t>(0x01000000),
                    static_cast<int32_t>(0x7e000000),
                    static_cast<int32_t>(0x80000000),
                },
                true),
            false);
  ASSERT_EQ(
      Utf32::isAsciiString(U" 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
      false);
};
TEST(Utf32StringTest, ToU8Data) {
  std::vector<char> expectUtf8;
  expectUtf8 = {static_cast<char>(0xef), static_cast<char>(0xbb),
                static_cast<char>(0xbf)};
  // BE BOM
  ASSERT_EQ(Utf32::toU8Data(U"", true), expectUtf8);
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff)},
                      false, true),
      expectUtf8);
  // LE BOM
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)},
                      true, true),
      expectUtf8);
  // // without bom
  expectUtf8 = {};
  // BE BOM
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff),
                                           static_cast<int32_t>(0x0000feff)},
                      false, false),
      expectUtf8);
  // LE BOM
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000),
                                           static_cast<int32_t>(0xfffe0000)},
                      true, false),
      expectUtf8);

  // BE
  expectUtf8 = {
      static_cast<char>(0x20),                          //
      static_cast<char>(0x30),                          //
      static_cast<char>(0x41),                          //
      static_cast<char>(0x61),                          //
      static_cast<char>(0x7e),                          //
      static_cast<char>(0xc2), static_cast<char>(0x80), //
      static_cast<char>(0xc2), static_cast<char>(0xa0), //
      static_cast<char>(0xc3), static_cast<char>(0xbf), //
      static_cast<char>(0xc4), static_cast<char>(0x80), //
      static_cast<char>(0xdf), static_cast<char>(0xbf), //
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xf0), static_cast<char>(0x90),
      static_cast<char>(0x83), static_cast<char>(0xba), //
      static_cast<char>(0xf0), static_cast<char>(0xa0),
      static_cast<char>(0x80), static_cast<char>(0x80), //
      static_cast<char>(0xf0), static_cast<char>(0xaf),
      static_cast<char>(0xa8), static_cast<char>(0x9c), //
      static_cast<char>(0xf0), static_cast<char>(0xb0),
      static_cast<char>(0xbb), static_cast<char>(0x9d), //
      static_cast<char>(0xf0), static_cast<char>(0xb1),
      static_cast<char>(0x81), static_cast<char>(0xac), //
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
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{
          static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
          static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
          static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
          static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
          static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
          static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
          static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000dc00),
          static_cast<int32_t>(0x0000dfff), static_cast<int32_t>(0x000100fa),
          static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
          static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
          static_cast<int32_t>(0x00110000), static_cast<int32_t>(0x0000feff),
          static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
          static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
          static_cast<int32_t>(0x0000304a)}),
      expectUtf8);
  expectUtf8 = {
      static_cast<char>(0x20),                          //
      static_cast<char>(0x30),                          //
      static_cast<char>(0x41),                          //
      static_cast<char>(0x61),                          //
      static_cast<char>(0x7e),                          //
      static_cast<char>(0xc2), static_cast<char>(0x80), //
      static_cast<char>(0xc2), static_cast<char>(0xa0), //
      static_cast<char>(0xc3), static_cast<char>(0xbf), //
      static_cast<char>(0xc4), static_cast<char>(0x80), //
      static_cast<char>(0xdf), static_cast<char>(0xbf), //
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
      static_cast<char>(0xf0), static_cast<char>(0x90),
      static_cast<char>(0x83), static_cast<char>(0xba), //
      static_cast<char>(0xf0), static_cast<char>(0xa0),
      static_cast<char>(0x80), static_cast<char>(0x80), //
      static_cast<char>(0xf0), static_cast<char>(0xaf),
      static_cast<char>(0xa8), static_cast<char>(0x9c), //
      static_cast<char>(0xf0), static_cast<char>(0xb0),
      static_cast<char>(0xbb), static_cast<char>(0x9d), //
      static_cast<char>(0xf0), static_cast<char>(0xb1),
      static_cast<char>(0x81), static_cast<char>(0xac), //
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
  ASSERT_EQ(Utf32::toU8Data(U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
            expectUtf8);
  expectUtf8 = {
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xf0), static_cast<char>(0x90), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xf2), static_cast<char>(0x80), static_cast<char>(0x80),
      static_cast<char>(0x80), //
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xc8),
      static_cast<char>(0x80), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xe1), static_cast<char>(0x84),
      static_cast<char>(0x80), //
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
  };
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{
          static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
          static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
          static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
          static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
          static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
          static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
          static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
          static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0x00dc0000),
          static_cast<int32_t>(0xffdf0000), static_cast<int32_t>(0xfa000100),
          static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
          static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
          static_cast<int32_t>(0x00001100), static_cast<int32_t>(0xfffe0000),
          static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
          static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
          static_cast<int32_t>(0x4a300000)}),
      expectUtf8);
  // LE
  expectUtf8 = {
      static_cast<char>(0x20),                          //
      static_cast<char>(0x30),                          //
      static_cast<char>(0x41),                          //
      static_cast<char>(0x61),                          //
      static_cast<char>(0x7e),                          //
      static_cast<char>(0xc2), static_cast<char>(0x80), //
      static_cast<char>(0xc2), static_cast<char>(0xa0), //
      static_cast<char>(0xc3), static_cast<char>(0xbf), //
      static_cast<char>(0xc4), static_cast<char>(0x80), //
      static_cast<char>(0xdf), static_cast<char>(0xbf), //
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xf0), static_cast<char>(0x90),
      static_cast<char>(0x83), static_cast<char>(0xba), //
      static_cast<char>(0xf0), static_cast<char>(0xa0),
      static_cast<char>(0x80), static_cast<char>(0x80), //
      static_cast<char>(0xf0), static_cast<char>(0xaf),
      static_cast<char>(0xa8), static_cast<char>(0x9c), //
      static_cast<char>(0xf0), static_cast<char>(0xb0),
      static_cast<char>(0xbb), static_cast<char>(0x9d), //
      static_cast<char>(0xf0), static_cast<char>(0xb1),
      static_cast<char>(0x81), static_cast<char>(0xac), //
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
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                           static_cast<int32_t>(0x30000000),
                                           static_cast<int32_t>(0x41000000),
                                           static_cast<int32_t>(0x61000000),
                                           static_cast<int32_t>(0x7e000000),
                                           static_cast<int32_t>(0x80000000),
                                           static_cast<int32_t>(0xa0000000),
                                           static_cast<int32_t>(0xff000000),
                                           static_cast<int32_t>(0x00010000),
                                           static_cast<int32_t>(0xff070000),
                                           static_cast<int32_t>(0x00080000),
                                           static_cast<int32_t>(0xff9f0000),
                                           static_cast<int32_t>(0x00a00000),
                                           static_cast<int32_t>(0xfbd70000),
                                           static_cast<int32_t>(0x00f90000),
                                           static_cast<int32_t>(0x00dc0000),
                                           static_cast<int32_t>(0xffdf0000),
                                           static_cast<int32_t>(0xfa000100),
                                           static_cast<int32_t>(0x00000200),
                                           static_cast<int32_t>(0x1cfa0200),
                                           static_cast<int32_t>(0xdd0e0300),
                                           static_cast<int32_t>(0x6c100300),
                                           static_cast<int32_t>(0x00001100),
                                           static_cast<int32_t>(0xfffe0000),
                                           static_cast<int32_t>(0x42300000),
                                           static_cast<int32_t>(0x44300000),
                                           static_cast<int32_t>(0x46300000),
                                           static_cast<int32_t>(0x48300000),
                                           static_cast<int32_t>(0x4a300000)},
                      true),
      expectUtf8);
  expectUtf8 = {
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xf0), static_cast<char>(0x90), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xf2), static_cast<char>(0x80), static_cast<char>(0x80),
      static_cast<char>(0x80), //
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xc8),
      static_cast<char>(0x80), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xe1), static_cast<char>(0x84),
      static_cast<char>(0x80), //
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
  };
  ASSERT_EQ(
      Utf32::toU8Data(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                           static_cast<int32_t>(0x00000030),
                                           static_cast<int32_t>(0x00000041),
                                           static_cast<int32_t>(0x00000061),
                                           static_cast<int32_t>(0x0000007e),
                                           static_cast<int32_t>(0x00000080),
                                           static_cast<int32_t>(0x000000a0),
                                           static_cast<int32_t>(0x000000ff),
                                           static_cast<int32_t>(0x00000100),
                                           static_cast<int32_t>(0x000007ff),
                                           static_cast<int32_t>(0x00000800),
                                           static_cast<int32_t>(0x00009fff),
                                           static_cast<int32_t>(0x0000a000),
                                           static_cast<int32_t>(0x0000d7fb),
                                           static_cast<int32_t>(0x0000f900),
                                           static_cast<int32_t>(0x0000dc00),
                                           static_cast<int32_t>(0x0000dfff),
                                           static_cast<int32_t>(0x000100fa),
                                           static_cast<int32_t>(0x00020000),
                                           static_cast<int32_t>(0x0002fa1c),
                                           static_cast<int32_t>(0x00030edd),
                                           static_cast<int32_t>(0x0003106c),
                                           static_cast<int32_t>(0x00110000),
                                           static_cast<int32_t>(0x0000feff),
                                           static_cast<int32_t>(0x00003042),
                                           static_cast<int32_t>(0x00003044),
                                           static_cast<int32_t>(0x00003046),
                                           static_cast<int32_t>(0x00003048),
                                           static_cast<int32_t>(0x0000304a)},
                      true),
      expectUtf8);
};
TEST(Utf32StringTest, ToU16Data) {
  // BE BOM
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff)},
                       false, true),
      std::vector<int16_t>{static_cast<int16_t>(0xfeff)});
  ASSERT_EQ(Utf32::toU16Data(U"", false, true),
            std::vector<int16_t>{static_cast<int16_t>(0xfeff)});
  // LE BOM
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)},
                       true, true),
      std::vector<int16_t>{static_cast<int16_t>(0xfffe)});
  // BE BOM to LE BOM
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff)},
                       false, true, true),
      std::vector<int16_t>{static_cast<int16_t>(0xfffe)});
  ASSERT_EQ(Utf32::toU16Data(U"", true, true),
            std::vector<int16_t>{static_cast<int16_t>(0xfffe)});
  // LE BOM to BE BOM
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)},
                       true, false, true),
      std::vector<int16_t>{static_cast<int16_t>(0xfeff)});
  // // without bom
  // BE BOM
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x0000feff)},
                       false, false),
      std::vector<int16_t>());
  // LE BOM
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0xfffe0000)},
                       true, false),
      std::vector<int16_t>());
  // BE BOM to LE
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x0000feff)},
                       false, true, false),
      std::vector<int16_t>());
  // LE BOM to BE
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0xfffe0000)},
                       true, false, false),
      std::vector<int16_t>());

  // BE
  std::vector<int16_t> expectUtf16{
      static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
      static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
      static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
      static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
      static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
      static_cast<int16_t>(0x0800), static_cast<int16_t>(0x9fff),
      static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
      static_cast<int16_t>(0xf900), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xd800),
      static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
      static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
      static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
      static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
      static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0x3042),
      static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
      static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{
          static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
          static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
          static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
          static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
          static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
          static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
          static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000dc00),
          static_cast<int32_t>(0x0000dfff), static_cast<int32_t>(0x000100fa),
          static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
          static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
          static_cast<int32_t>(0x00110000), static_cast<int32_t>(0x0000feff),
          static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
          static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
          static_cast<int32_t>(0x0000304a)}),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                 static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                 static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                 static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                 static_cast<int16_t>(0x0800), static_cast<int16_t>(0x9fff),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                 static_cast<int16_t>(0xf900), static_cast<int16_t>(0xd800),
                 static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                 static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                 static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                 static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                 static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                 static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(Utf32::toU16Data(U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
            expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc00),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xd9c0),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0x0200), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0x1100), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{
          static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
          static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
          static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
          static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
          static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
          static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
          static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
          static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0x00dc0000),
          static_cast<int32_t>(0xffdf0000), static_cast<int32_t>(0xfa000100),
          static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
          static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
          static_cast<int32_t>(0x00001100), static_cast<int32_t>(0xfffe0000),
          static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
          static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
          static_cast<int32_t>(0x4a300000)}),
      expectUtf16);
  // LE
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                 static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0x00d8),
                 static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                 static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                 static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                 static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                            static_cast<int32_t>(0x30000000),
                                            static_cast<int32_t>(0x41000000),
                                            static_cast<int32_t>(0x61000000),
                                            static_cast<int32_t>(0x7e000000),
                                            static_cast<int32_t>(0x80000000),
                                            static_cast<int32_t>(0xa0000000),
                                            static_cast<int32_t>(0xff000000),
                                            static_cast<int32_t>(0x00010000),
                                            static_cast<int32_t>(0xff070000),
                                            static_cast<int32_t>(0x00080000),
                                            static_cast<int32_t>(0xff9f0000),
                                            static_cast<int32_t>(0x00a00000),
                                            static_cast<int32_t>(0xfbd70000),
                                            static_cast<int32_t>(0x00f90000),
                                            static_cast<int32_t>(0x00dc0000),
                                            static_cast<int32_t>(0xffdf0000),
                                            static_cast<int32_t>(0xfa000100),
                                            static_cast<int32_t>(0x00000200),
                                            static_cast<int32_t>(0x1cfa0200),
                                            static_cast<int32_t>(0xdd0e0300),
                                            static_cast<int32_t>(0x6c100300),
                                            static_cast<int32_t>(0x00001100),
                                            static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0x42300000),
                                            static_cast<int32_t>(0x44300000),
                                            static_cast<int32_t>(0x46300000),
                                            static_cast<int32_t>(0x48300000),
                                            static_cast<int32_t>(0x4a300000)},
                       true),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00dc),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xc0d9),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x0002), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x0011), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                            static_cast<int32_t>(0x00000030),
                                            static_cast<int32_t>(0x00000041),
                                            static_cast<int32_t>(0x00000061),
                                            static_cast<int32_t>(0x0000007e),
                                            static_cast<int32_t>(0x00000080),
                                            static_cast<int32_t>(0x000000a0),
                                            static_cast<int32_t>(0x000000ff),
                                            static_cast<int32_t>(0x00000100),
                                            static_cast<int32_t>(0x000007ff),
                                            static_cast<int32_t>(0x00000800),
                                            static_cast<int32_t>(0x00009fff),
                                            static_cast<int32_t>(0x0000a000),
                                            static_cast<int32_t>(0x0000d7fb),
                                            static_cast<int32_t>(0x0000f900),
                                            static_cast<int32_t>(0x0000dc00),
                                            static_cast<int32_t>(0x0000dfff),
                                            static_cast<int32_t>(0x000100fa),
                                            static_cast<int32_t>(0x00020000),
                                            static_cast<int32_t>(0x0002fa1c),
                                            static_cast<int32_t>(0x00030edd),
                                            static_cast<int32_t>(0x0003106c),
                                            static_cast<int32_t>(0x00110000),
                                            static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x00003042),
                                            static_cast<int32_t>(0x00003044),
                                            static_cast<int32_t>(0x00003046),
                                            static_cast<int32_t>(0x00003048),
                                            static_cast<int32_t>(0x0000304a)},
                       true),
      expectUtf16);
  // BE to LE
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                 static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0x00d8),
                 static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                 static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                 static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                 static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                            static_cast<int32_t>(0x00000030),
                                            static_cast<int32_t>(0x00000041),
                                            static_cast<int32_t>(0x00000061),
                                            static_cast<int32_t>(0x0000007e),
                                            static_cast<int32_t>(0x00000080),
                                            static_cast<int32_t>(0x000000a0),
                                            static_cast<int32_t>(0x000000ff),
                                            static_cast<int32_t>(0x00000100),
                                            static_cast<int32_t>(0x000007ff),
                                            static_cast<int32_t>(0x00000800),
                                            static_cast<int32_t>(0x00009fff),
                                            static_cast<int32_t>(0x0000a000),
                                            static_cast<int32_t>(0x0000d7fb),
                                            static_cast<int32_t>(0x0000f900),
                                            static_cast<int32_t>(0x0000dc00),
                                            static_cast<int32_t>(0x0000dfff),
                                            static_cast<int32_t>(0x000100fa),
                                            static_cast<int32_t>(0x00020000),
                                            static_cast<int32_t>(0x0002fa1c),
                                            static_cast<int32_t>(0x00030edd),
                                            static_cast<int32_t>(0x0003106c),
                                            static_cast<int32_t>(0x00110000),
                                            static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x00003042),
                                            static_cast<int32_t>(0x00003044),
                                            static_cast<int32_t>(0x00003046),
                                            static_cast<int32_t>(0x00003048),
                                            static_cast<int32_t>(0x0000304a)},
                       false, true, false),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                 static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00d8),
                 static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                 static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                 static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                 static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(Utf32::toU16Data(U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお", true,
                             false),
            expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00dc),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xc0d9),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x0002), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0x0011), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                            static_cast<int32_t>(0x30000000),
                                            static_cast<int32_t>(0x41000000),
                                            static_cast<int32_t>(0x61000000),
                                            static_cast<int32_t>(0x7e000000),
                                            static_cast<int32_t>(0x80000000),
                                            static_cast<int32_t>(0xa0000000),
                                            static_cast<int32_t>(0xff000000),
                                            static_cast<int32_t>(0x00010000),
                                            static_cast<int32_t>(0xff070000),
                                            static_cast<int32_t>(0x00080000),
                                            static_cast<int32_t>(0xff9f0000),
                                            static_cast<int32_t>(0x00a00000),
                                            static_cast<int32_t>(0xfbd70000),
                                            static_cast<int32_t>(0x00f90000),
                                            static_cast<int32_t>(0x00dc0000),
                                            static_cast<int32_t>(0xffdf0000),
                                            static_cast<int32_t>(0xfa000100),
                                            static_cast<int32_t>(0x00000200),
                                            static_cast<int32_t>(0x1cfa0200),
                                            static_cast<int32_t>(0xdd0e0300),
                                            static_cast<int32_t>(0x6c100300),
                                            static_cast<int32_t>(0x00001100),
                                            static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0x42300000),
                                            static_cast<int32_t>(0x44300000),
                                            static_cast<int32_t>(0x46300000),
                                            static_cast<int32_t>(0x48300000),
                                            static_cast<int32_t>(0x4a300000)},
                       false, true, false),
      expectUtf16);
  // LE to BE
  expectUtf16 = {static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                 static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                 static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                 static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                 static_cast<int16_t>(0x0800), static_cast<int16_t>(0x9fff),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                 static_cast<int16_t>(0xf900), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xd800),
                 static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                 static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                 static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                 static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0x3042),
                 static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                 static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                            static_cast<int32_t>(0x30000000),
                                            static_cast<int32_t>(0x41000000),
                                            static_cast<int32_t>(0x61000000),
                                            static_cast<int32_t>(0x7e000000),
                                            static_cast<int32_t>(0x80000000),
                                            static_cast<int32_t>(0xa0000000),
                                            static_cast<int32_t>(0xff000000),
                                            static_cast<int32_t>(0x00010000),
                                            static_cast<int32_t>(0xff070000),
                                            static_cast<int32_t>(0x00080000),
                                            static_cast<int32_t>(0xff9f0000),
                                            static_cast<int32_t>(0x00a00000),
                                            static_cast<int32_t>(0xfbd70000),
                                            static_cast<int32_t>(0x00f90000),
                                            static_cast<int32_t>(0x00dc0000),
                                            static_cast<int32_t>(0xffdf0000),
                                            static_cast<int32_t>(0xfa000100),
                                            static_cast<int32_t>(0x00000200),
                                            static_cast<int32_t>(0x1cfa0200),
                                            static_cast<int32_t>(0xdd0e0300),
                                            static_cast<int32_t>(0x6c100300),
                                            static_cast<int32_t>(0x00001100),
                                            static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0x42300000),
                                            static_cast<int32_t>(0x44300000),
                                            static_cast<int32_t>(0x46300000),
                                            static_cast<int32_t>(0x48300000),
                                            static_cast<int32_t>(0x4a300000)},
                       true, false, false),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdc00),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xd9c0),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0x0200), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0x1100), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(
      Utf32::toU16Data(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                            static_cast<int32_t>(0x00000030),
                                            static_cast<int32_t>(0x00000041),
                                            static_cast<int32_t>(0x00000061),
                                            static_cast<int32_t>(0x0000007e),
                                            static_cast<int32_t>(0x00000080),
                                            static_cast<int32_t>(0x000000a0),
                                            static_cast<int32_t>(0x000000ff),
                                            static_cast<int32_t>(0x00000100),
                                            static_cast<int32_t>(0x000007ff),
                                            static_cast<int32_t>(0x00000800),
                                            static_cast<int32_t>(0x00009fff),
                                            static_cast<int32_t>(0x0000a000),
                                            static_cast<int32_t>(0x0000d7fb),
                                            static_cast<int32_t>(0x0000f900),
                                            static_cast<int32_t>(0x0000dc00),
                                            static_cast<int32_t>(0x0000dfff),
                                            static_cast<int32_t>(0x000100fa),
                                            static_cast<int32_t>(0x00020000),
                                            static_cast<int32_t>(0x0002fa1c),
                                            static_cast<int32_t>(0x00030edd),
                                            static_cast<int32_t>(0x0003106c),
                                            static_cast<int32_t>(0x00110000),
                                            static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x00003042),
                                            static_cast<int32_t>(0x00003044),
                                            static_cast<int32_t>(0x00003046),
                                            static_cast<int32_t>(0x00003048),
                                            static_cast<int32_t>(0x0000304a)},
                       true, false, false),
      expectUtf16);
};
TEST(Utf32StringTest, ToU32Data) {
  // BE BOM
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff)},
                       false, true),
      std::vector<int32_t>{static_cast<int32_t>(0x0000feff)});
  ASSERT_EQ(Utf32::toU32Data(U"", true),
            std::vector<int32_t>{static_cast<int32_t>(0x0000feff)});
  // LE BOM
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)},
                       true, true),
      std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)});
  // BE BOM to LE BOM
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff)},
                       false, true, true),
      std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)});
  ASSERT_EQ(Utf32::toU32Data(U"", true, true),
            std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)});
  // LE BOM to BE BOM
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)},
                       true, false, true),
      std::vector<int32_t>{static_cast<int32_t>(0x0000feff)});
  // // without bom
  // BE BOM
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x0000feff)},
                       false, false),
      std::vector<int32_t>());
  // LE BOM
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0xfffe0000)},
                       true, false),
      std::vector<int32_t>());

  // BE BOM to LE
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x0000feff)},
                       false, true, false),
      std::vector<int32_t>());
  // LE BOM to LE
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0xfffe0000)},
                       true, false, false),
      std::vector<int32_t>());

  // BE
  std::vector<int32_t> expectUtf32{
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
      static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
      static_cast<int32_t>(0x0000304a)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{
          static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
          static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
          static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
          static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
          static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
          static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
          static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000dc00),
          static_cast<int32_t>(0x0000dfff), static_cast<int32_t>(0x000100fa),
          static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
          static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
          static_cast<int32_t>(0x00110000), static_cast<int32_t>(0x0000feff),
          static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
          static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
          static_cast<int32_t>(0x0000304a)}),
      expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
      static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
      static_cast<int32_t>(0x0000304a)};
  ASSERT_EQ(Utf32::toU32Data(U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
            expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00001100), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{
          static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
          static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
          static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
          static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
          static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
          static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
          static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
          static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0x00dc0000),
          static_cast<int32_t>(0xffdf0000), static_cast<int32_t>(0xfa000100),
          static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
          static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
          static_cast<int32_t>(0x00001100), static_cast<int32_t>(0xfffe0000),
          static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
          static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
          static_cast<int32_t>(0x4a300000)}),
      expectUtf32);
  // LE
  expectUtf32 = {
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
      static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfa000100),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
      static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
      static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
      static_cast<int32_t>(0x4a300000)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                            static_cast<int32_t>(0x30000000),
                                            static_cast<int32_t>(0x41000000),
                                            static_cast<int32_t>(0x61000000),
                                            static_cast<int32_t>(0x7e000000),
                                            static_cast<int32_t>(0x80000000),
                                            static_cast<int32_t>(0xa0000000),
                                            static_cast<int32_t>(0xff000000),
                                            static_cast<int32_t>(0x00010000),
                                            static_cast<int32_t>(0xff070000),
                                            static_cast<int32_t>(0x00080000),
                                            static_cast<int32_t>(0xff9f0000),
                                            static_cast<int32_t>(0x00a00000),
                                            static_cast<int32_t>(0xfbd70000),
                                            static_cast<int32_t>(0x00f90000),
                                            static_cast<int32_t>(0x00dc0000),
                                            static_cast<int32_t>(0xffdf0000),
                                            static_cast<int32_t>(0xfa000100),
                                            static_cast<int32_t>(0x00000200),
                                            static_cast<int32_t>(0x1cfa0200),
                                            static_cast<int32_t>(0xdd0e0300),
                                            static_cast<int32_t>(0x6c100300),
                                            static_cast<int32_t>(0x00001100),
                                            static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0x42300000),
                                            static_cast<int32_t>(0x44300000),
                                            static_cast<int32_t>(0x46300000),
                                            static_cast<int32_t>(0x48300000),
                                            static_cast<int32_t>(0x4a300000)},
                       true),
      expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00110000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                            static_cast<int32_t>(0x00000030),
                                            static_cast<int32_t>(0x00000041),
                                            static_cast<int32_t>(0x00000061),
                                            static_cast<int32_t>(0x0000007e),
                                            static_cast<int32_t>(0x00000080),
                                            static_cast<int32_t>(0x000000a0),
                                            static_cast<int32_t>(0x000000ff),
                                            static_cast<int32_t>(0x00000100),
                                            static_cast<int32_t>(0x000007ff),
                                            static_cast<int32_t>(0x00000800),
                                            static_cast<int32_t>(0x00009fff),
                                            static_cast<int32_t>(0x0000a000),
                                            static_cast<int32_t>(0x0000d7fb),
                                            static_cast<int32_t>(0x0000f900),
                                            static_cast<int32_t>(0x0000dc00),
                                            static_cast<int32_t>(0x0000dfff),
                                            static_cast<int32_t>(0x000100fa),
                                            static_cast<int32_t>(0x00020000),
                                            static_cast<int32_t>(0x0002fa1c),
                                            static_cast<int32_t>(0x00030edd),
                                            static_cast<int32_t>(0x0003106c),
                                            static_cast<int32_t>(0x00110000),
                                            static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x00003042),
                                            static_cast<int32_t>(0x00003044),
                                            static_cast<int32_t>(0x00003046),
                                            static_cast<int32_t>(0x00003048),
                                            static_cast<int32_t>(0x0000304a)},
                       true),
      expectUtf32);
  // BE to LE
  expectUtf32 = {
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
      static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfa000100),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
      static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
      static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
      static_cast<int32_t>(0x4a300000)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                            static_cast<int32_t>(0x00000030),
                                            static_cast<int32_t>(0x00000041),
                                            static_cast<int32_t>(0x00000061),
                                            static_cast<int32_t>(0x0000007e),
                                            static_cast<int32_t>(0x00000080),
                                            static_cast<int32_t>(0x000000a0),
                                            static_cast<int32_t>(0x000000ff),
                                            static_cast<int32_t>(0x00000100),
                                            static_cast<int32_t>(0x000007ff),
                                            static_cast<int32_t>(0x00000800),
                                            static_cast<int32_t>(0x00009fff),
                                            static_cast<int32_t>(0x0000a000),
                                            static_cast<int32_t>(0x0000d7fb),
                                            static_cast<int32_t>(0x0000f900),
                                            static_cast<int32_t>(0x0000dc00),
                                            static_cast<int32_t>(0x0000dfff),
                                            static_cast<int32_t>(0x000100fa),
                                            static_cast<int32_t>(0x00020000),
                                            static_cast<int32_t>(0x0002fa1c),
                                            static_cast<int32_t>(0x00030edd),
                                            static_cast<int32_t>(0x0003106c),
                                            static_cast<int32_t>(0x00110000),
                                            static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x00003042),
                                            static_cast<int32_t>(0x00003044),
                                            static_cast<int32_t>(0x00003046),
                                            static_cast<int32_t>(0x00003048),
                                            static_cast<int32_t>(0x0000304a)},
                       false, true, false),
      expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
      static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfa000100),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
      static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
      static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
      static_cast<int32_t>(0x4a300000)};
  ASSERT_EQ(Utf32::toU32Data(U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお", true,
                             false),
            expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0x00110000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                            static_cast<int32_t>(0x30000000),
                                            static_cast<int32_t>(0x41000000),
                                            static_cast<int32_t>(0x61000000),
                                            static_cast<int32_t>(0x7e000000),
                                            static_cast<int32_t>(0x80000000),
                                            static_cast<int32_t>(0xa0000000),
                                            static_cast<int32_t>(0xff000000),
                                            static_cast<int32_t>(0x00010000),
                                            static_cast<int32_t>(0xff070000),
                                            static_cast<int32_t>(0x00080000),
                                            static_cast<int32_t>(0xff9f0000),
                                            static_cast<int32_t>(0x00a00000),
                                            static_cast<int32_t>(0xfbd70000),
                                            static_cast<int32_t>(0x00f90000),
                                            static_cast<int32_t>(0x00dc0000),
                                            static_cast<int32_t>(0xffdf0000),
                                            static_cast<int32_t>(0xfa000100),
                                            static_cast<int32_t>(0x00000200),
                                            static_cast<int32_t>(0x1cfa0200),
                                            static_cast<int32_t>(0xdd0e0300),
                                            static_cast<int32_t>(0x6c100300),
                                            static_cast<int32_t>(0x00001100),
                                            static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0x42300000),
                                            static_cast<int32_t>(0x44300000),
                                            static_cast<int32_t>(0x46300000),
                                            static_cast<int32_t>(0x48300000),
                                            static_cast<int32_t>(0x4a300000)},
                       false, true, false),
      expectUtf32);
  // LE to BE
  expectUtf32 = {
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
      static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
      static_cast<int32_t>(0x0000304a)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                            static_cast<int32_t>(0x30000000),
                                            static_cast<int32_t>(0x41000000),
                                            static_cast<int32_t>(0x61000000),
                                            static_cast<int32_t>(0x7e000000),
                                            static_cast<int32_t>(0x80000000),
                                            static_cast<int32_t>(0xa0000000),
                                            static_cast<int32_t>(0xff000000),
                                            static_cast<int32_t>(0x00010000),
                                            static_cast<int32_t>(0xff070000),
                                            static_cast<int32_t>(0x00080000),
                                            static_cast<int32_t>(0xff9f0000),
                                            static_cast<int32_t>(0x00a00000),
                                            static_cast<int32_t>(0xfbd70000),
                                            static_cast<int32_t>(0x00f90000),
                                            static_cast<int32_t>(0x00dc0000),
                                            static_cast<int32_t>(0xffdf0000),
                                            static_cast<int32_t>(0xfa000100),
                                            static_cast<int32_t>(0x00000200),
                                            static_cast<int32_t>(0x1cfa0200),
                                            static_cast<int32_t>(0xdd0e0300),
                                            static_cast<int32_t>(0x6c100300),
                                            static_cast<int32_t>(0x00001100),
                                            static_cast<int32_t>(0xfffe0000),
                                            static_cast<int32_t>(0x42300000),
                                            static_cast<int32_t>(0x44300000),
                                            static_cast<int32_t>(0x46300000),
                                            static_cast<int32_t>(0x48300000),
                                            static_cast<int32_t>(0x4a300000)},
                       true, false, false),
      expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x00001100), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd)};
  ASSERT_EQ(
      Utf32::toU32Data(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                            static_cast<int32_t>(0x00000030),
                                            static_cast<int32_t>(0x00000041),
                                            static_cast<int32_t>(0x00000061),
                                            static_cast<int32_t>(0x0000007e),
                                            static_cast<int32_t>(0x00000080),
                                            static_cast<int32_t>(0x000000a0),
                                            static_cast<int32_t>(0x000000ff),
                                            static_cast<int32_t>(0x00000100),
                                            static_cast<int32_t>(0x000007ff),
                                            static_cast<int32_t>(0x00000800),
                                            static_cast<int32_t>(0x00009fff),
                                            static_cast<int32_t>(0x0000a000),
                                            static_cast<int32_t>(0x0000d7fb),
                                            static_cast<int32_t>(0x0000f900),
                                            static_cast<int32_t>(0x0000dc00),
                                            static_cast<int32_t>(0x0000dfff),
                                            static_cast<int32_t>(0x000100fa),
                                            static_cast<int32_t>(0x00020000),
                                            static_cast<int32_t>(0x0002fa1c),
                                            static_cast<int32_t>(0x00030edd),
                                            static_cast<int32_t>(0x0003106c),
                                            static_cast<int32_t>(0x00110000),
                                            static_cast<int32_t>(0x0000feff),
                                            static_cast<int32_t>(0x00003042),
                                            static_cast<int32_t>(0x00003044),
                                            static_cast<int32_t>(0x00003046),
                                            static_cast<int32_t>(0x00003048),
                                            static_cast<int32_t>(0x0000304a)},
                       true, false, false),
      expectUtf32);
};
TEST(Utf32StringTest, ToU8String) {
  // BE BOM
  ASSERT_EQ(
      Utf32::toU8String(std::vector<int32_t>{static_cast<int32_t>(0x0000feff)}),
      "");
  // LE BOM
  ASSERT_EQ(Utf32::toU8String(
                std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)}, true),
            "");
  ASSERT_EQ(Utf32::toU8String(std::vector<int32_t>{
                static_cast<int32_t>(0x0000feff),
                static_cast<int32_t>(0x0000feff),
            }),
            "");
  // BE
  ASSERT_EQ(
      Utf32::toU8String(std::vector<int32_t>{
          static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
          static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
          static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
          static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
          static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
          static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
          static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000dc00),
          static_cast<int32_t>(0x0000dfff), static_cast<int32_t>(0x000100fa),
          static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
          static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
          static_cast<int32_t>(0x00110000), static_cast<int32_t>(0x0000feff),
          static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
          static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
          static_cast<int32_t>(0x0000304a)}),
      " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬��あいうえお");
  ASSERT_EQ(
      Utf32::toU8String(std::vector<int32_t>{
          static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
          static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
          static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
          static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
          static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
          static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
          static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
          static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0x00dc0000),
          static_cast<int32_t>(0xffdf0000), static_cast<int32_t>(0xfa000100),
          static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
          static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
          static_cast<int32_t>(0x00001100), static_cast<int32_t>(0xfffe0000),
          static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
          static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
          static_cast<int32_t>(0x4a300000)}),
      "��������𐀀�򀀀�������Ȁ���ᄀ"
      "������");
  // LE
  ASSERT_EQ(
      Utf32::toU8String(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                             static_cast<int32_t>(0x30000000),
                                             static_cast<int32_t>(0x41000000),
                                             static_cast<int32_t>(0x61000000),
                                             static_cast<int32_t>(0x7e000000),
                                             static_cast<int32_t>(0x80000000),
                                             static_cast<int32_t>(0xa0000000),
                                             static_cast<int32_t>(0xff000000),
                                             static_cast<int32_t>(0x00010000),
                                             static_cast<int32_t>(0xff070000),
                                             static_cast<int32_t>(0x00080000),
                                             static_cast<int32_t>(0xff9f0000),
                                             static_cast<int32_t>(0x00a00000),
                                             static_cast<int32_t>(0xfbd70000),
                                             static_cast<int32_t>(0x00f90000),
                                             static_cast<int32_t>(0x00dc0000),
                                             static_cast<int32_t>(0xffdf0000),
                                             static_cast<int32_t>(0xfa000100),
                                             static_cast<int32_t>(0x00000200),
                                             static_cast<int32_t>(0x1cfa0200),
                                             static_cast<int32_t>(0xdd0e0300),
                                             static_cast<int32_t>(0x6c100300),
                                             static_cast<int32_t>(0x00001100),
                                             static_cast<int32_t>(0xfffe0000),
                                             static_cast<int32_t>(0x42300000),
                                             static_cast<int32_t>(0x44300000),
                                             static_cast<int32_t>(0x46300000),
                                             static_cast<int32_t>(0x48300000),
                                             static_cast<int32_t>(0x4a300000)},
                        true),
      " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬��あいうえお");
  ASSERT_EQ(
      Utf32::toU8String(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                             static_cast<int32_t>(0x00000030),
                                             static_cast<int32_t>(0x00000041),
                                             static_cast<int32_t>(0x00000061),
                                             static_cast<int32_t>(0x0000007e),
                                             static_cast<int32_t>(0x00000080),
                                             static_cast<int32_t>(0x000000a0),
                                             static_cast<int32_t>(0x000000ff),
                                             static_cast<int32_t>(0x00000100),
                                             static_cast<int32_t>(0x000007ff),
                                             static_cast<int32_t>(0x00000800),
                                             static_cast<int32_t>(0x00009fff),
                                             static_cast<int32_t>(0x0000a000),
                                             static_cast<int32_t>(0x0000d7fb),
                                             static_cast<int32_t>(0x0000f900),
                                             static_cast<int32_t>(0x0000dc00),
                                             static_cast<int32_t>(0x0000dfff),
                                             static_cast<int32_t>(0x000100fa),
                                             static_cast<int32_t>(0x00020000),
                                             static_cast<int32_t>(0x0002fa1c),
                                             static_cast<int32_t>(0x00030edd),
                                             static_cast<int32_t>(0x0003106c),
                                             static_cast<int32_t>(0x00110000),
                                             static_cast<int32_t>(0x0000feff),
                                             static_cast<int32_t>(0x00003042),
                                             static_cast<int32_t>(0x00003044),
                                             static_cast<int32_t>(0x00003046),
                                             static_cast<int32_t>(0x00003048),
                                             static_cast<int32_t>(0x0000304a)},
                        true),
      "��������𐀀�򀀀�������Ȁ���ᄀ"
      "������");
};
TEST(Utf32StringTest, ToU16String) {
  // BE BOM
  ASSERT_EQ(Utf32::toU16String(
                std::vector<int32_t>{static_cast<int32_t>(0x0000feff)}),
            u"");
  // LE BOM
  ASSERT_EQ(Utf32::toU16String(
                std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)}, true),
            u"");
  ASSERT_EQ(Utf32::toU16String(std::vector<int32_t>{
                static_cast<int32_t>(0x0000feff),
                static_cast<int32_t>(0x0000feff),
            }),
            u"");
  // BE
  ASSERT_EQ(
      Utf32::toU16String(std::vector<int32_t>{
          static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
          static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
          static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
          static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
          static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
          static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
          static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000dc00),
          static_cast<int32_t>(0x0000dfff), static_cast<int32_t>(0x000100fa),
          static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
          static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
          static_cast<int32_t>(0x00110000), static_cast<int32_t>(0x0000feff),
          static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
          static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
          static_cast<int32_t>(0x0000304a)}),
      u" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬��あいうえお");
  ASSERT_EQ(
      Utf32::toU16String(std::vector<int32_t>{
          static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
          static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
          static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
          static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
          static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
          static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
          static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
          static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0x00dc0000),
          static_cast<int32_t>(0xffdf0000), static_cast<int32_t>(0xfa000100),
          static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
          static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
          static_cast<int32_t>(0x00001100), static_cast<int32_t>(0xfffe0000),
          static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
          static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
          static_cast<int32_t>(0x4a300000)}),
      u"��������𐀀�򀀀�������Ȁ���ᄀ"
      u"������");
  // LE
  ASSERT_EQ(
      Utf32::toU16String(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                              static_cast<int32_t>(0x30000000),
                                              static_cast<int32_t>(0x41000000),
                                              static_cast<int32_t>(0x61000000),
                                              static_cast<int32_t>(0x7e000000),
                                              static_cast<int32_t>(0x80000000),
                                              static_cast<int32_t>(0xa0000000),
                                              static_cast<int32_t>(0xff000000),
                                              static_cast<int32_t>(0x00010000),
                                              static_cast<int32_t>(0xff070000),
                                              static_cast<int32_t>(0x00080000),
                                              static_cast<int32_t>(0xff9f0000),
                                              static_cast<int32_t>(0x00a00000),
                                              static_cast<int32_t>(0xfbd70000),
                                              static_cast<int32_t>(0x00f90000),
                                              static_cast<int32_t>(0x00dc0000),
                                              static_cast<int32_t>(0xffdf0000),
                                              static_cast<int32_t>(0xfa000100),
                                              static_cast<int32_t>(0x00000200),
                                              static_cast<int32_t>(0x1cfa0200),
                                              static_cast<int32_t>(0xdd0e0300),
                                              static_cast<int32_t>(0x6c100300),
                                              static_cast<int32_t>(0x00001100),
                                              static_cast<int32_t>(0xfffe0000),
                                              static_cast<int32_t>(0x42300000),
                                              static_cast<int32_t>(0x44300000),
                                              static_cast<int32_t>(0x46300000),
                                              static_cast<int32_t>(0x48300000),
                                              static_cast<int32_t>(0x4a300000)},
                         true),
      u" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬��あいうえお");
  ASSERT_EQ(
      Utf32::toU16String(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                              static_cast<int32_t>(0x00000030),
                                              static_cast<int32_t>(0x00000041),
                                              static_cast<int32_t>(0x00000061),
                                              static_cast<int32_t>(0x0000007e),
                                              static_cast<int32_t>(0x00000080),
                                              static_cast<int32_t>(0x000000a0),
                                              static_cast<int32_t>(0x000000ff),
                                              static_cast<int32_t>(0x00000100),
                                              static_cast<int32_t>(0x000007ff),
                                              static_cast<int32_t>(0x00000800),
                                              static_cast<int32_t>(0x00009fff),
                                              static_cast<int32_t>(0x0000a000),
                                              static_cast<int32_t>(0x0000d7fb),
                                              static_cast<int32_t>(0x0000f900),
                                              static_cast<int32_t>(0x0000dc00),
                                              static_cast<int32_t>(0x0000dfff),
                                              static_cast<int32_t>(0x000100fa),
                                              static_cast<int32_t>(0x00020000),
                                              static_cast<int32_t>(0x0002fa1c),
                                              static_cast<int32_t>(0x00030edd),
                                              static_cast<int32_t>(0x0003106c),
                                              static_cast<int32_t>(0x00110000),
                                              static_cast<int32_t>(0x0000feff),
                                              static_cast<int32_t>(0x00003042),
                                              static_cast<int32_t>(0x00003044),
                                              static_cast<int32_t>(0x00003046),
                                              static_cast<int32_t>(0x00003048),
                                              static_cast<int32_t>(0x0000304a)},
                         true),
      u"��������𐀀�򀀀�������Ȁ���ᄀ"
      u"������");
  ASSERT_EQ(Utf32::toU16String(U" 0Aa~"
                               U"\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
            u" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお");
};
TEST(Utf32StringTest, ToU32String) {
  // BE BOM
  ASSERT_EQ(Utf32::toU32String(
                std::vector<int32_t>{static_cast<int32_t>(0x0000feff)}),
            U"");
  // LE BOM
  ASSERT_EQ(Utf32::toU32String(
                std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)}, true),
            U"");
  ASSERT_EQ(Utf32::toU32String(std::vector<int32_t>{
                static_cast<int32_t>(0x0000feff),
                static_cast<int32_t>(0x0000feff),
            }),
            U"");
  // BE
  ASSERT_EQ(
      Utf32::toU32String(std::vector<int32_t>{
          static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
          static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
          static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
          static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
          static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00009fff),
          static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
          static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000dc00),
          static_cast<int32_t>(0x0000dfff), static_cast<int32_t>(0x000100fa),
          static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
          static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
          static_cast<int32_t>(0x00110000), static_cast<int32_t>(0x0000feff),
          static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
          static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
          static_cast<int32_t>(0x0000304a)}),
      U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬��あいうえお");
  ASSERT_EQ(
      Utf32::toU32String(std::vector<int32_t>{
          static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
          static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
          static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
          static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
          static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
          static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xff9f0000),
          static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
          static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0x00dc0000),
          static_cast<int32_t>(0xffdf0000), static_cast<int32_t>(0xfa000100),
          static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
          static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
          static_cast<int32_t>(0x00001100), static_cast<int32_t>(0xfffe0000),
          static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
          static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
          static_cast<int32_t>(0x4a300000)}),
      U"��������𐀀�򀀀�������Ȁ���ᄀ"
      U"������");
  // LE
  ASSERT_EQ(
      Utf32::toU32String(std::vector<int32_t>{static_cast<int32_t>(0x20000000),
                                              static_cast<int32_t>(0x30000000),
                                              static_cast<int32_t>(0x41000000),
                                              static_cast<int32_t>(0x61000000),
                                              static_cast<int32_t>(0x7e000000),
                                              static_cast<int32_t>(0x80000000),
                                              static_cast<int32_t>(0xa0000000),
                                              static_cast<int32_t>(0xff000000),
                                              static_cast<int32_t>(0x00010000),
                                              static_cast<int32_t>(0xff070000),
                                              static_cast<int32_t>(0x00080000),
                                              static_cast<int32_t>(0xff9f0000),
                                              static_cast<int32_t>(0x00a00000),
                                              static_cast<int32_t>(0xfbd70000),
                                              static_cast<int32_t>(0x00f90000),
                                              static_cast<int32_t>(0x00dc0000),
                                              static_cast<int32_t>(0xffdf0000),
                                              static_cast<int32_t>(0xfa000100),
                                              static_cast<int32_t>(0x00000200),
                                              static_cast<int32_t>(0x1cfa0200),
                                              static_cast<int32_t>(0xdd0e0300),
                                              static_cast<int32_t>(0x6c100300),
                                              static_cast<int32_t>(0x00001100),
                                              static_cast<int32_t>(0xfffe0000),
                                              static_cast<int32_t>(0x42300000),
                                              static_cast<int32_t>(0x44300000),
                                              static_cast<int32_t>(0x46300000),
                                              static_cast<int32_t>(0x48300000),
                                              static_cast<int32_t>(0x4a300000)},
                         true),
      U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬��あいうえお");
  ASSERT_EQ(
      Utf32::toU32String(std::vector<int32_t>{static_cast<int32_t>(0x00000020),
                                              static_cast<int32_t>(0x00000030),
                                              static_cast<int32_t>(0x00000041),
                                              static_cast<int32_t>(0x00000061),
                                              static_cast<int32_t>(0x0000007e),
                                              static_cast<int32_t>(0x00000080),
                                              static_cast<int32_t>(0x000000a0),
                                              static_cast<int32_t>(0x000000ff),
                                              static_cast<int32_t>(0x00000100),
                                              static_cast<int32_t>(0x000007ff),
                                              static_cast<int32_t>(0x00000800),
                                              static_cast<int32_t>(0x00009fff),
                                              static_cast<int32_t>(0x0000a000),
                                              static_cast<int32_t>(0x0000d7fb),
                                              static_cast<int32_t>(0x0000f900),
                                              static_cast<int32_t>(0x0000dc00),
                                              static_cast<int32_t>(0x0000dfff),
                                              static_cast<int32_t>(0x000100fa),
                                              static_cast<int32_t>(0x00020000),
                                              static_cast<int32_t>(0x0002fa1c),
                                              static_cast<int32_t>(0x00030edd),
                                              static_cast<int32_t>(0x0003106c),
                                              static_cast<int32_t>(0x00110000),
                                              static_cast<int32_t>(0x0000feff),
                                              static_cast<int32_t>(0x00003042),
                                              static_cast<int32_t>(0x00003044),
                                              static_cast<int32_t>(0x00003046),
                                              static_cast<int32_t>(0x00003048),
                                              static_cast<int32_t>(0x0000304a)},
                         true),
      U"��������𐀀�򀀀�������Ȁ���ᄀ"
      U"������");
  ASSERT_EQ(Utf32::toU32String(U" 0Aa~"
                               U"\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお"),
            U" 0Aa~\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬あいうえお");
};

} // namespace gallop::CharSet::String
