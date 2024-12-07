#include "charset/string/utf16_string.hpp"
#include <gtest/gtest.h>

namespace gallop::CharSet::String {
class Utf16StringTest : public ::testing::Test {};
TEST(Utf16StringTest, StringTypes) {
  // null string
  // BE
  ASSERT_EQ(Utf16::isNullString(std::vector<int16_t>()), true);
  ASSERT_EQ(
      Utf16::isNullString(std::vector<int16_t>{static_cast<int16_t>(0xfeff)}),
      true);
  ASSERT_EQ(
      Utf16::isNullString(std::vector<int16_t>{static_cast<int16_t>(0x007e)}),
      false);
  // LE
  ASSERT_EQ(Utf16::isNullString(std::vector<int16_t>(), true), true);
  ASSERT_EQ(Utf16::isNullString(
                std::vector<int16_t>{static_cast<int16_t>(0xfffe)}, true),
            true);
  ASSERT_EQ(Utf16::isNullString(
                std::vector<int16_t>{static_cast<int16_t>(0x7e00)}, true),
            false);
  // UTF-16
  // BE BOM
  ASSERT_EQ(
      Utf16::isValidString(std::vector<int16_t>{static_cast<int16_t>(0xfeff)}),
      true);
  // invalid
  // 4byte
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0xdc00),
                static_cast<int16_t>(0xdc00),
            }),
            false);
  // 3byte
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0xd800),
            }),
            false);
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0xdbff),
            }),
            false);
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0xdc00),
            }),
            false);
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0xdfff),
            }),
            false);
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0xd800),
                static_cast<int16_t>(0xd800),
            }),
            false);
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0xd800),
                static_cast<int16_t>(0xe000),
            }),
            false);
  // newline LE
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0x000a),
                static_cast<int16_t>(0x0a00),
            }),
            false);
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0x000d),
                static_cast<int16_t>(0x0d00),
            }),
            false);
  // may be LE
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
                static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
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
                static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)}),
            false);
  // valid
  ASSERT_EQ(Utf16::isValidString(std::vector<int16_t>{
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
                static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)}),
            true);
  // LE BOM
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{static_cast<int16_t>(0xfffe)}, true),
            true);
  // invalid
  // 4byte
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00dc),
                },
                true),
            false);
  // 3byte
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x00d8),
                },
                true),
            false);
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0xffdb),
                },
                true),
            false);
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x00dc),
                },
                true),
            false);
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0xffdf),
                },
                true),
            false);
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0x00d8),
                },
                true),
            false);
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0x00e0),
                },
                true),
            false);
  // newline BE
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x000a),
                },
                true),
            false);
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0d00),
                    static_cast<int16_t>(0x000d),
                },
                true),
            false);
  // may be BE
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
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
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                true),
            false);
  // valid
  ASSERT_EQ(Utf16::isValidString(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
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
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                true),
            true);
};
TEST(Utf16StringTest, ToUtf8Data) {
  std::vector<char> expectUtf8;
  expectUtf8 = {static_cast<char>(0xef), static_cast<char>(0xbb),
                static_cast<char>(0xbf)};
  // BE BOM
  ASSERT_EQ(
      Utf16::toUtf8Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff)},
                        false, true),
      expectUtf8);
  // LE BOM
  ASSERT_EQ(Utf16::toUtf8Data(
                std::vector<int16_t>{static_cast<int16_t>(0xfffe)}, true, true),
            expectUtf8);
  // // without bom
  expectUtf8 = {};
  // BE BOM
  ASSERT_EQ(
      Utf16::toUtf8Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff),
                                             static_cast<int16_t>(0xfeff)},
                        false, false),
      expectUtf8);
  // LE BOM
  ASSERT_EQ(
      Utf16::toUtf8Data(std::vector<int16_t>{static_cast<int16_t>(0xfffe),
                                             static_cast<int16_t>(0xfffe)},
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
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
  ASSERT_EQ(Utf16::toUtf8Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                false),
            expectUtf8);
  expectUtf8 = {
      static_cast<char>(0xe2), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xe3), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xe4), static_cast<char>(0x84),
      static_cast<char>(0x80), //
      static_cast<char>(0xe6), static_cast<char>(0x84),
      static_cast<char>(0x80), //
      static_cast<char>(0xe7), static_cast<char>(0xb8),
      static_cast<char>(0x80), //
      static_cast<char>(0xe8), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xea), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xef), static_cast<char>(0xbc),
      static_cast<char>(0x80), //
      static_cast<char>(0x01), //
      static_cast<char>(0xef), static_cast<char>(0xbc),
      static_cast<char>(0x87), //
      static_cast<char>(0x08), //
      static_cast<char>(0x0a), //
      static_cast<char>(0x0d), //
      static_cast<char>(0xef), static_cast<char>(0xbe),
      static_cast<char>(0x9f),                          //
      static_cast<char>(0xc2), static_cast<char>(0xa0), //
      static_cast<char>(0xef), static_cast<char>(0xaf),
      static_cast<char>(0x97),                          //
      static_cast<char>(0xc3), static_cast<char>(0xb9), //
      static_cast<char>(0xc3), static_cast<char>(0x9c), //
      static_cast<char>(0xc3), static_cast<char>(0x98), //
      static_cast<char>(0xc3), static_cast<char>(0x98), //
      static_cast<char>(0xef), static_cast<char>(0xab),
      static_cast<char>(0x9c), //
      static_cast<char>(0xe4), static_cast<char>(0x83),
      static_cast<char>(0x98),                          //
      static_cast<char>(0xc3), static_cast<char>(0x9c), //
      static_cast<char>(0xe7), static_cast<char>(0xbb),
      static_cast<char>(0x98), //
      static_cast<char>(0xe1), static_cast<char>(0xb3),
      static_cast<char>(0x9e), //
      static_cast<char>(0xe8), static_cast<char>(0x8f),
      static_cast<char>(0x98), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xe8), static_cast<char>(0x93),
      static_cast<char>(0x98), //
      static_cast<char>(0xe6), static_cast<char>(0xb3),
      static_cast<char>(0x9c), //
      static_cast<char>(0xe4), static_cast<char>(0x88),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0x90),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0x98),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0xa0),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0xa8),
      static_cast<char>(0xb0), //
  };
  ASSERT_EQ(Utf16::toUtf8Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                false),
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
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
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
  ASSERT_EQ(Utf16::toUtf8Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                true),
            expectUtf8);
  expectUtf8 = {
      static_cast<char>(0xe2), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xe3), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xe4), static_cast<char>(0x84),
      static_cast<char>(0x80), //
      static_cast<char>(0xe6), static_cast<char>(0x84),
      static_cast<char>(0x80), //
      static_cast<char>(0xe7), static_cast<char>(0xb8),
      static_cast<char>(0x80), //
      static_cast<char>(0xe8), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xea), static_cast<char>(0x80),
      static_cast<char>(0x80), //
      static_cast<char>(0xef), static_cast<char>(0xbc),
      static_cast<char>(0x80), //
      static_cast<char>(0x01), //
      static_cast<char>(0xef), static_cast<char>(0xbc),
      static_cast<char>(0x87), //
      static_cast<char>(0x08), //
      static_cast<char>(0x0a), //
      static_cast<char>(0x0d), //
      static_cast<char>(0xef), static_cast<char>(0xbe),
      static_cast<char>(0x9f),                          //
      static_cast<char>(0xc2), static_cast<char>(0xa0), //
      static_cast<char>(0xef), static_cast<char>(0xaf),
      static_cast<char>(0x97),                          //
      static_cast<char>(0xc3), static_cast<char>(0xb9), //
      static_cast<char>(0xc3), static_cast<char>(0x9c), //
      static_cast<char>(0xc3), static_cast<char>(0x98), //
      static_cast<char>(0xc3), static_cast<char>(0x98), //
      static_cast<char>(0xef), static_cast<char>(0xab),
      static_cast<char>(0x9c), //
      static_cast<char>(0xe4), static_cast<char>(0x83),
      static_cast<char>(0x98),                          //
      static_cast<char>(0xc3), static_cast<char>(0x9c), //
      static_cast<char>(0xe7), static_cast<char>(0xbb),
      static_cast<char>(0x98), //
      static_cast<char>(0xe1), static_cast<char>(0xb3),
      static_cast<char>(0x9e), //
      static_cast<char>(0xe8), static_cast<char>(0x8f),
      static_cast<char>(0x98), //
      static_cast<char>(0xef), static_cast<char>(0xbf),
      static_cast<char>(0xbd), //
      static_cast<char>(0xe8), static_cast<char>(0x93),
      static_cast<char>(0x98), //
      static_cast<char>(0xe6), static_cast<char>(0xb3),
      static_cast<char>(0x9c), //
      static_cast<char>(0xe4), static_cast<char>(0x88),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0x90),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0x98),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0xa0),
      static_cast<char>(0xb0), //
      static_cast<char>(0xe4), static_cast<char>(0xa8),
      static_cast<char>(0xb0), //
  };
  ASSERT_EQ(Utf16::toUtf8Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                true),
            expectUtf8);
};
TEST(Utf16StringTest, ToUtf16Data) {
  // BE BOM
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff)},
                         false, true),
      std::vector<int16_t>{static_cast<int16_t>(0xfeff)});
  // LE BOM
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{static_cast<int16_t>(0xfffe)}, true, true),
            std::vector<int16_t>{static_cast<int16_t>(0xfffe)});
  // BE BOM to LE BOM
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff)},
                         false, true, true),
      std::vector<int16_t>{static_cast<int16_t>(0xfffe)});
  // LE BOM to BE BOM
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xfffe)},
                         true, true, true),
      std::vector<int16_t>{static_cast<int16_t>(0xfeff)});
  // // without bom
  // BE BOM
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff),
                                              static_cast<int16_t>(0xfeff)},
                         false, false),
      std::vector<int16_t>());
  // LE BOM
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xfffe),
                                              static_cast<int16_t>(0xfffe)},
                         true, false),
      std::vector<int16_t>());
  // BE BOM to LE
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff),
                                              static_cast<int16_t>(0xfeff)},
                         false, false, true),
      std::vector<int16_t>());
  // LE BOM to BE
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xfffe),
                                              static_cast<int16_t>(0xfffe)},
                         true, false, true),
      std::vector<int16_t>());

  // BE surrrogate
  std::vector<int16_t> expectUtf16{static_cast<int16_t>(0xfffd),
                                   static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800)},
                         false),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800),
                                              static_cast<int16_t>(0xd800)},
                         false),
      expectUtf16);
  // BE
  expectUtf16 = {static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                 static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                 static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                 static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                 static_cast<int16_t>(0x0800), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0x9fff),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                 static_cast<int16_t>(0xf900), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xd800),
                 static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                 static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                 static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                 static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                 static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                 static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                false),
            expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                 static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                 static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                 static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                 static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                 static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0x84d8),
                 static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                false),
            expectUtf16);
  // LE surrrogate
  expectUtf16 = {static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8)},
                         true),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8),
                                              static_cast<int16_t>(0x00d8)},
                         true),
      expectUtf16);
  // LE
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                 static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0x00d8),
                 static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                 static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                 static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                 static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                true),
            expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                 static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                 static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                 static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                 static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                 static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                 static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                 static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                 static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                 static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xd884),
                 static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                 static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                 static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                true),
            expectUtf16);
  // BE surrrogate to LE
  expectUtf16 = {static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800)},
                         false, false, true),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800),
                                              static_cast<int16_t>(0xd800)},
                         false, false, true),
      expectUtf16);
  // BE to LE
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                 static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0xfdff),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0x00d8),
                 static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                 static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                 static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                 static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                false, false, true),
            expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                 static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                 static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                 static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                 static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                 static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                 static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                 static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                 static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                 static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                 static_cast<int16_t>(0xfdff), static_cast<int16_t>(0xd884),
                 static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                 static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                 static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                false, false, true),
            expectUtf16);
  // LE surrrogate to BE
  expectUtf16 = {static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8)},
                         true, false, true),
      expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd)};
  ASSERT_EQ(
      Utf16::toUtf16Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8),
                                              static_cast<int16_t>(0x00d8)},
                         true, false, true),
      expectUtf16);
  // LE to BE
  expectUtf16 = {static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                 static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                 static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                 static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                 static_cast<int16_t>(0x0800), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0x9fff),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                 static_cast<int16_t>(0xf900), static_cast<int16_t>(0xfffd),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xd800),
                 static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                 static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                 static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                 static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                 static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                 static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                 static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                true, false, true),
            expectUtf16);
  expectUtf16 = {static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                 static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                 static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                 static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                 static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                 static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                 static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                 static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                 static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                 static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                 static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                 static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                 static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                 static_cast<int16_t>(0xfffd), static_cast<int16_t>(0x84d8),
                 static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                 static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                 static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)};
  ASSERT_EQ(Utf16::toUtf16Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                true, false, true),
            expectUtf16);
};
TEST(Utf16StringTest, ToUtf32Data) {
  // BE BOM
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff)},
                         false, true),
      std::vector<int32_t>{static_cast<int32_t>(0x0000feff)});
  // LE BOM
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{static_cast<int16_t>(0xfffe)}, true, true),
            std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)});
  // BE BOM to LE BOM
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff)},
                         false, true, true),
      std::vector<int32_t>{static_cast<int32_t>(0xfffe0000)});
  // LE BOM to BE BOM
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xfffe)},
                         true, true, true),
      std::vector<int32_t>{static_cast<int32_t>(0x0000feff)});
  // // without bom
  // BE BOM
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff),
                                              static_cast<int16_t>(0xfeff)},
                         false, false),
      std::vector<int32_t>());
  // LE BOM
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xfffe),
                                              static_cast<int16_t>(0xfffe)},
                         true, false),
      std::vector<int32_t>());

  // BE BOM to LE
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xfeff),
                                              static_cast<int16_t>(0xfeff)},
                         false, false, true),
      std::vector<int32_t>());
  // LE BOM to LE
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xfffe),
                                              static_cast<int16_t>(0xfffe)},
                         true, false, true),
      std::vector<int32_t>());

  // BE surrrogate
  std::vector<int32_t> expectUtf32{static_cast<int32_t>(0x0000fffd),
                                   static_cast<int32_t>(0x0000fffd)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800)},
                         false),
      expectUtf32);
  expectUtf32 = {static_cast<int32_t>(0x0000fffd),
                 static_cast<int32_t>(0x0000fffd),
                 static_cast<int32_t>(0x0000fffd)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800),
                                              static_cast<int16_t>(0xd800)},
                         false),
      expectUtf32);
  // BE
  expectUtf32 = {
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
      static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
      static_cast<int32_t>(0x0000304a)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                false),
            expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x00002000), static_cast<int32_t>(0x00003000),
      static_cast<int32_t>(0x00004100), static_cast<int32_t>(0x00006100),
      static_cast<int32_t>(0x00007e00), static_cast<int32_t>(0x00008000),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000ff00),
      static_cast<int32_t>(0x00000001), static_cast<int32_t>(0x0000ff07),
      static_cast<int32_t>(0x00000008), static_cast<int32_t>(0x0000000a),
      static_cast<int32_t>(0x0000000d), static_cast<int32_t>(0x0000ff9f),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x0000fbd7),
      static_cast<int32_t>(0x000000f9), static_cast<int32_t>(0x000000dc),
      static_cast<int32_t>(0x000000d8), static_cast<int32_t>(0x000000d8),
      static_cast<int32_t>(0x0000fadc), static_cast<int32_t>(0x000040d8),
      static_cast<int32_t>(0x000000dc), static_cast<int32_t>(0x00007ed8),
      static_cast<int32_t>(0x00001cde), static_cast<int32_t>(0x000083d8),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000084d8),
      static_cast<int32_t>(0x00006cdc), static_cast<int32_t>(0x00004230),
      static_cast<int32_t>(0x00004430), static_cast<int32_t>(0x00004630),
      static_cast<int32_t>(0x00004830), static_cast<int32_t>(0x00004a30)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                false),
            expectUtf32);
  // LE surrrogate
  expectUtf32 = {static_cast<int32_t>(0xfdff0000),
                 static_cast<int32_t>(0xfdff0000)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8)},
                         true),
      expectUtf32);
  expectUtf32 = {static_cast<int32_t>(0xfdff0000),
                 static_cast<int32_t>(0xfdff0000),
                 static_cast<int32_t>(0xfdff0000)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8),
                                              static_cast<int16_t>(0x00d8)},
                         true),
      expectUtf32);
  // LE
  expectUtf32 = {
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
      static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfa000100),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
      static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
      static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
      static_cast<int32_t>(0x4a300000)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                true),
            expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x00200000), static_cast<int32_t>(0x00300000),
      static_cast<int32_t>(0x00410000), static_cast<int32_t>(0x00610000),
      static_cast<int32_t>(0x007e0000), static_cast<int32_t>(0x00800000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0x00ff0000),
      static_cast<int32_t>(0x01000000), static_cast<int32_t>(0x07ff0000),
      static_cast<int32_t>(0x08000000), static_cast<int32_t>(0x0a000000),
      static_cast<int32_t>(0x0d000000), static_cast<int32_t>(0x9fff0000),
      static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xd7fb0000),
      static_cast<int32_t>(0xf9000000), static_cast<int32_t>(0xdc000000),
      static_cast<int32_t>(0xd8000000), static_cast<int32_t>(0xd8000000),
      static_cast<int32_t>(0xdcfa0000), static_cast<int32_t>(0xd8400000),
      static_cast<int32_t>(0xdc000000), static_cast<int32_t>(0xd87e0000),
      static_cast<int32_t>(0xde1c0000), static_cast<int32_t>(0xd8830000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xd8840000),
      static_cast<int32_t>(0xdc6c0000), static_cast<int32_t>(0x30420000),
      static_cast<int32_t>(0x30440000), static_cast<int32_t>(0x30460000),
      static_cast<int32_t>(0x30480000), static_cast<int32_t>(0x304a0000)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                true),
            expectUtf32);
  // BE surrrogate to LE
  expectUtf32 = {static_cast<int32_t>(0xfdff0000),
                 static_cast<int32_t>(0xfdff0000)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800)},
                         false, false, true),
      expectUtf32);
  expectUtf32 = {static_cast<int32_t>(0xfdff0000),
                 static_cast<int32_t>(0xfdff0000),
                 static_cast<int32_t>(0xfdff0000)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0xdc00),
                                              static_cast<int16_t>(0xd800),
                                              static_cast<int16_t>(0xd800)},
                         false, false, true),
      expectUtf32);
  // BE to LE
  expectUtf32 = {
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7e000000), static_cast<int32_t>(0x80000000),
      static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xff000000),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff070000),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfdff0000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xfa000100),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
      static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0x42300000), static_cast<int32_t>(0x44300000),
      static_cast<int32_t>(0x46300000), static_cast<int32_t>(0x48300000),
      static_cast<int32_t>(0x4a300000)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                false, false, true),
            expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x00200000), static_cast<int32_t>(0x00300000),
      static_cast<int32_t>(0x00410000), static_cast<int32_t>(0x00610000),
      static_cast<int32_t>(0x007e0000), static_cast<int32_t>(0x00800000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0x00ff0000),
      static_cast<int32_t>(0x01000000), static_cast<int32_t>(0x07ff0000),
      static_cast<int32_t>(0x08000000), static_cast<int32_t>(0x0a000000),
      static_cast<int32_t>(0x0d000000), static_cast<int32_t>(0x9fff0000),
      static_cast<int32_t>(0xa0000000), static_cast<int32_t>(0xd7fb0000),
      static_cast<int32_t>(0xf9000000), static_cast<int32_t>(0xdc000000),
      static_cast<int32_t>(0xd8000000), static_cast<int32_t>(0xd8000000),
      static_cast<int32_t>(0xdcfa0000), static_cast<int32_t>(0xd8400000),
      static_cast<int32_t>(0xdc000000), static_cast<int32_t>(0xd87e0000),
      static_cast<int32_t>(0xde1c0000), static_cast<int32_t>(0xd8830000),
      static_cast<int32_t>(0xfdff0000), static_cast<int32_t>(0xd8840000),
      static_cast<int32_t>(0xdc6c0000), static_cast<int32_t>(0x30420000),
      static_cast<int32_t>(0x30440000), static_cast<int32_t>(0x30460000),
      static_cast<int32_t>(0x30480000), static_cast<int32_t>(0x304a0000)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                false, false, true),
            expectUtf32);
  // LE surrrogate to BE
  expectUtf32 = {static_cast<int32_t>(0x0000fffd),
                 static_cast<int32_t>(0x0000fffd)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8)},
                         true, false, true),
      expectUtf32);
  expectUtf32 = {static_cast<int32_t>(0x0000fffd),
                 static_cast<int32_t>(0x0000fffd),
                 static_cast<int32_t>(0x0000fffd)};
  ASSERT_EQ(
      Utf16::toUtf32Data(std::vector<int16_t>{static_cast<int16_t>(0x00dc),
                                              static_cast<int16_t>(0x00d8),
                                              static_cast<int16_t>(0x00d8)},
                         true, false, true),
      expectUtf32);
  // LE to BE
  expectUtf32 = {
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007e), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000fffd),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
      static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
      static_cast<int32_t>(0x0000304a)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                true, false, true),
            expectUtf32);
  expectUtf32 = {
      static_cast<int32_t>(0x00002000), static_cast<int32_t>(0x00003000),
      static_cast<int32_t>(0x00004100), static_cast<int32_t>(0x00006100),
      static_cast<int32_t>(0x00007e00), static_cast<int32_t>(0x00008000),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000ff00),
      static_cast<int32_t>(0x00000001), static_cast<int32_t>(0x0000ff07),
      static_cast<int32_t>(0x00000008), static_cast<int32_t>(0x0000000a),
      static_cast<int32_t>(0x0000000d), static_cast<int32_t>(0x0000ff9f),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x0000fbd7),
      static_cast<int32_t>(0x000000f9), static_cast<int32_t>(0x000000dc),
      static_cast<int32_t>(0x000000d8), static_cast<int32_t>(0x000000d8),
      static_cast<int32_t>(0x0000fadc), static_cast<int32_t>(0x000040d8),
      static_cast<int32_t>(0x000000dc), static_cast<int32_t>(0x00007ed8),
      static_cast<int32_t>(0x00001cde), static_cast<int32_t>(0x000083d8),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000084d8),
      static_cast<int32_t>(0x00006cdc), static_cast<int32_t>(0x00004230),
      static_cast<int32_t>(0x00004430), static_cast<int32_t>(0x00004630),
      static_cast<int32_t>(0x00004830), static_cast<int32_t>(0x00004a30)};
  ASSERT_EQ(Utf16::toUtf32Data(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                    static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                    static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                    static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                    static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                    static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                    static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                    static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                    static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                    static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                    static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                    static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                    static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                    static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                    static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
                true, false, true),
            expectUtf32);
};
TEST(Utf16StringTest, ToUtf8String) {
  // BE BOM
  ASSERT_EQ(
      Utf16::toUtf8String(std::vector<int16_t>{static_cast<int16_t>(0xfeff)}),
      "");
  // LE BOM
  ASSERT_EQ(Utf16::toUtf8String(
                std::vector<int16_t>{static_cast<int16_t>(0xfffe)}, true),
            "");
  ASSERT_EQ(Utf16::toUtf8String(std::vector<int16_t>{
                static_cast<int16_t>(0xfeff),
                static_cast<int16_t>(0xfeff),
            }),
            "");
  // BE
  ASSERT_EQ(Utf16::toUtf8String(std::vector<int16_t>{
                static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
                static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
                static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
                static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
                static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
                static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
                static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
                static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
                static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
                static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
                static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
                static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
                static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
                static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
                static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
                static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
                static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)}),
            " 0Aa~\xc2\x80 ÿĀ߿ࠀ��鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬あいうえお");
  ASSERT_EQ(
      Utf16::toUtf8String(std::vector<int16_t>{
          static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
          static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
          static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
          static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
          static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
          static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
          static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
          static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
          static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
          static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
          static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
          static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
          static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
          static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
          static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
          static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
          static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)}),
      " 　䄀愀縀耀ꀀ＀\x01＇\b\n\r\xef\xbe\x9f\xc2\xa0"
      "ﯗùÜØØ﫜䃘Ü\xe7\xbb\x98\xe1\xb3\x9e菘\xef\xbf\xbd蓘泜䈰䐰"
      "䘰"
      "䠰"
      "䨰");
  // LE
  ASSERT_EQ(Utf16::toUtf8String(
                std::vector<int16_t>{
                    static_cast<int16_t>(0x2000), static_cast<int16_t>(0x3000),
                    static_cast<int16_t>(0x4100), static_cast<int16_t>(0x6100),
                    static_cast<int16_t>(0x7e00), static_cast<int16_t>(0x8000),
                    static_cast<int16_t>(0xa000), static_cast<int16_t>(0xff00),
                    static_cast<int16_t>(0x0001), static_cast<int16_t>(0xff07),
                    static_cast<int16_t>(0x0008), static_cast<int16_t>(0x000a),
                    static_cast<int16_t>(0x000d), static_cast<int16_t>(0xff9f),
                    static_cast<int16_t>(0x00a0), static_cast<int16_t>(0xfbd7),
                    static_cast<int16_t>(0x00f9), static_cast<int16_t>(0x00dc),
                    static_cast<int16_t>(0x00d8), static_cast<int16_t>(0x00d8),
                    static_cast<int16_t>(0xfadc), static_cast<int16_t>(0x40d8),
                    static_cast<int16_t>(0x00dc), static_cast<int16_t>(0x7ed8),
                    static_cast<int16_t>(0x1cde), static_cast<int16_t>(0x83d8),
                    static_cast<int16_t>(0xddde), static_cast<int16_t>(0x84d8),
                    static_cast<int16_t>(0x6cdc), static_cast<int16_t>(0x4230),
                    static_cast<int16_t>(0x4430), static_cast<int16_t>(0x4630),
                    static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)},
                true),
            " 0Aa~\xc2\x80 ÿĀ߿ࠀ��鿿ꀀퟻ豈��𐃺𠀀鼻𰻝𱁬あいうえお");
  ASSERT_EQ(
      Utf16::toUtf8String(
          std::vector<int16_t>{
              static_cast<int16_t>(0x0020), static_cast<int16_t>(0x0030),
              static_cast<int16_t>(0x0041), static_cast<int16_t>(0x0061),
              static_cast<int16_t>(0x007e), static_cast<int16_t>(0x0080),
              static_cast<int16_t>(0x00a0), static_cast<int16_t>(0x00ff),
              static_cast<int16_t>(0x0100), static_cast<int16_t>(0x07ff),
              static_cast<int16_t>(0x0800), static_cast<int16_t>(0x0a00),
              static_cast<int16_t>(0x0d00), static_cast<int16_t>(0x9fff),
              static_cast<int16_t>(0xa000), static_cast<int16_t>(0xd7fb),
              static_cast<int16_t>(0xf900), static_cast<int16_t>(0xdc00),
              static_cast<int16_t>(0xd800), static_cast<int16_t>(0xd800),
              static_cast<int16_t>(0xdcfa), static_cast<int16_t>(0xd840),
              static_cast<int16_t>(0xdc00), static_cast<int16_t>(0xd87e),
              static_cast<int16_t>(0xde1c), static_cast<int16_t>(0xd883),
              static_cast<int16_t>(0xdedd), static_cast<int16_t>(0xd884),
              static_cast<int16_t>(0xdc6c), static_cast<int16_t>(0x3042),
              static_cast<int16_t>(0x3044), static_cast<int16_t>(0x3046),
              static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)},
          true),
      " 　䄀愀縀耀ꀀ＀\x01＇\b\n\r\xef\xbe\x9f\xc2\xa0"
      "ﯗùÜØØ﫜䃘Ü\xe7\xbb\x98\xe1\xb3\x9e菘\xef\xbf\xbd蓘泜䈰䐰"
      "䘰"
      "䠰"
      "䨰");
};

} // namespace gallop::CharSet::String
