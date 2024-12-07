// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf8_output_stream.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;

class Utf8OutputStreamTest : public ::testing::Test {};
TEST_F(Utf8OutputStreamTest, String) {
  Utf8OutputStream uos;
  uos.writeBom();
  uos.writeBom();
  uos.write(static_cast<int32_t>(0x0000feff));
  uos.write(static_cast<int32_t>(0x00000020));
  uos.write(static_cast<int32_t>(0x00000030));
  uos.write(static_cast<int32_t>(0x00000041));
  uos.write(static_cast<int32_t>(0x00000061));
  uos.write(static_cast<int32_t>(0x0000007e));
  // 2byte
  uos.write(static_cast<int32_t>(0x00000080));
  uos.write(static_cast<int32_t>(0x000000a0));
  uos.write(static_cast<int32_t>(0x000000ff));
  uos.write(static_cast<int32_t>(0x00000100));
  uos.write(static_cast<int32_t>(0x000007ff));
  // 3byte
  uos.write(static_cast<int32_t>(0x00000800));
  uos.write(static_cast<int32_t>(0x00009fff));
  uos.write(static_cast<int32_t>(0x0000a000));
  uos.write(static_cast<int32_t>(0x0000d7fb));
  uos.write(static_cast<int32_t>(0x0000f900));
  // 4byte
  uos.write(static_cast<int32_t>(0x000100fa));
  uos.write(static_cast<int32_t>(0x00020000));
  uos.write(static_cast<int32_t>(0x0002fa1c));
  uos.write(static_cast<int32_t>(0x00030edd));
  uos.write(static_cast<int32_t>(0x0003106c));
  uos.writeBom();
  uos.writeString("あいうえお");
  ASSERT_EQ(uos.toU8String(), " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬�あいうえお");
  std::vector<char> expectUtf8{
      static_cast<char>(0xef), static_cast<char>(0xbb),
      static_cast<char>(0xbf), //
      static_cast<char>(0x20), //
      static_cast<char>(0x30), //
      static_cast<char>(0x41), //
      static_cast<char>(0x61), //
      static_cast<char>(0x7e), //
      static_cast<char>(0xc2),
      static_cast<char>(0x80), //
      static_cast<char>(0xc2),
      static_cast<char>(0xa0), //
      static_cast<char>(0xc3),
      static_cast<char>(0xbf), //
      static_cast<char>(0xc4),
      static_cast<char>(0x80), //
      static_cast<char>(0xdf),
      static_cast<char>(0xbf), //
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
  ASSERT_EQ(uos.data(), expectUtf8);
  uos.reset();
  expectUtf8 = {};
  ASSERT_EQ(uos.data(), expectUtf8);
  uos = Utf8OutputStream();
  ASSERT_EQ(uos.data(), expectUtf8);
};
