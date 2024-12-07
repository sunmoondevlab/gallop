#include "io/stream/utf8_output_stream.hpp"
#include <gtest/gtest.h>

namespace gallop::IO::Stream {

class Utf8OutputStreamTest : public ::testing::Test {};
TEST_F(Utf8OutputStreamTest, String) {
  Utf8OutputStream baos;
  baos.write(static_cast<int32_t>(0x0000feff));
  baos.write(static_cast<int32_t>(0x0000feff));
  baos.write(static_cast<int32_t>(0x00000020));
  baos.write(static_cast<int32_t>(0x00000030));
  baos.write(static_cast<int32_t>(0x00000041));
  baos.write(static_cast<int32_t>(0x00000061));
  baos.write(static_cast<int32_t>(0x0000007e));
  // 2byte
  baos.write(static_cast<int32_t>(0x00000080));
  baos.write(static_cast<int32_t>(0x000000a0));
  baos.write(static_cast<int32_t>(0x000000ff));
  baos.write(static_cast<int32_t>(0x00000100));
  baos.write(static_cast<int32_t>(0x000007ff));
  // 3byte
  baos.write(static_cast<int32_t>(0x00000800));
  baos.write(static_cast<int32_t>(0x00009fff));
  baos.write(static_cast<int32_t>(0x0000a000));
  baos.write(static_cast<int32_t>(0x0000d7fb));
  baos.write(static_cast<int32_t>(0x0000f900));
  // 4byte
  baos.write(static_cast<int32_t>(0x000100fa));
  baos.write(static_cast<int32_t>(0x00020000));
  baos.write(static_cast<int32_t>(0x0002fa1c));
  baos.write(static_cast<int32_t>(0x00030edd));
  baos.write(static_cast<int32_t>(0x0003106c));
  baos.write(static_cast<int32_t>(0x0000feff));
  baos.writeString("あいうえお");
  ASSERT_EQ(baos.toString(), " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬�あいうえお");
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
  ASSERT_EQ(baos.data(), expectUtf8);
  baos.reset();
  expectUtf8 = {};
  ASSERT_EQ(baos.data(), expectUtf8);
  baos = Utf8OutputStream();
  ASSERT_EQ(baos.data(), expectUtf8);
};

} // namespace gallop::IO::Stream