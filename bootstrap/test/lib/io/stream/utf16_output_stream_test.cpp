#include "io/stream/utf16_output_stream.hpp"
#include <gtest/gtest.h>

namespace gallop::IO::Stream {

class Utf16OutputStreamTest : public ::testing::Test {};
TEST_F(Utf16OutputStreamTest, String) {
  Utf16OutputStream uos;
  // BE to BE
  uos.write(static_cast<int32_t>(0x0000feff));
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
  uos.write(static_cast<int32_t>(0x0000feff));
  uos.writeString("あいうえお");
  ASSERT_EQ(uos.toString(), " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬�あいうえお");
  std::vector<int16_t> expectUtf16{
      static_cast<int16_t>(0xfeff), //
      static_cast<int16_t>(0x0020), //
      static_cast<int16_t>(0x0030), //
      static_cast<int16_t>(0x0041), //
      static_cast<int16_t>(0x0061), //
      static_cast<int16_t>(0x007e), //
      static_cast<int16_t>(0x0080), //
      static_cast<int16_t>(0x00a0), //
      static_cast<int16_t>(0x00ff), //
      static_cast<int16_t>(0x0100), //
      static_cast<int16_t>(0x07ff), //
      static_cast<int16_t>(0x0800), //
      static_cast<int16_t>(0x9fff), //
      static_cast<int16_t>(0xa000), //
      static_cast<int16_t>(0xd7fb), //
      static_cast<int16_t>(0xf900), //
      static_cast<int16_t>(0xd800),
      static_cast<int16_t>(0xdcfa), //
      static_cast<int16_t>(0xd840),
      static_cast<int16_t>(0xdc00), //
      static_cast<int16_t>(0xd87e),
      static_cast<int16_t>(0xde1c), //
      static_cast<int16_t>(0xd883),
      static_cast<int16_t>(0xdedd), //
      static_cast<int16_t>(0xd884),
      static_cast<int16_t>(0xdc6c), //
      static_cast<int16_t>(0xfffd), //
      static_cast<int16_t>(0x3042), //
      static_cast<int16_t>(0x3044), //
      static_cast<int16_t>(0x3046), //
      static_cast<int16_t>(0x3048), //
      static_cast<int16_t>(0x304a), //
  };
  ASSERT_EQ(uos.data(), expectUtf16);
  uos.reset();
  expectUtf16 = {};
  ASSERT_EQ(uos.data(), expectUtf16);
  uos = Utf16OutputStream();
  ASSERT_EQ(uos.data(), expectUtf16);
  uos = Utf16OutputStream(true);
  // BE to LE
  uos.write(static_cast<int32_t>(0x0000feff));
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
  uos.write(static_cast<int32_t>(0x0000feff));
  uos.writeString("あいうえお");
  ASSERT_EQ(uos.toString(), " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬�あいうえお");
  expectUtf16 = {
      static_cast<int16_t>(0xfffe), //
      static_cast<int16_t>(0x2000), //
      static_cast<int16_t>(0x3000), //
      static_cast<int16_t>(0x4100), //
      static_cast<int16_t>(0x6100), //
      static_cast<int16_t>(0x7e00), //
      static_cast<int16_t>(0x8000), //
      static_cast<int16_t>(0xa000), //
      static_cast<int16_t>(0xff00), //
      static_cast<int16_t>(0x0001), //
      static_cast<int16_t>(0xff07), //
      static_cast<int16_t>(0x0008), //
      static_cast<int16_t>(0xff9f), //
      static_cast<int16_t>(0x00a0), //
      static_cast<int16_t>(0xfbd7), //
      static_cast<int16_t>(0x00f9), //
      static_cast<int16_t>(0x00d8),
      static_cast<int16_t>(0xfadc), //
      static_cast<int16_t>(0x40d8),
      static_cast<int16_t>(0x00dc), //
      static_cast<int16_t>(0x7ed8),
      static_cast<int16_t>(0x1cde), //
      static_cast<int16_t>(0x83d8),
      static_cast<int16_t>(0xddde), //
      static_cast<int16_t>(0x84d8),
      static_cast<int16_t>(0x6cdc), //
      static_cast<int16_t>(0xfdff), //
      static_cast<int16_t>(0x4230), //
      static_cast<int16_t>(0x4430), //
      static_cast<int16_t>(0x4630), //
      static_cast<int16_t>(0x4830), //
      static_cast<int16_t>(0x4a30), //
  };
  uos = Utf16OutputStream(true, false);
  // LE to BE
  uos.write(static_cast<int32_t>(0xfffe0000));
  uos.write(static_cast<int32_t>(0xfffe0000));
  uos.write(static_cast<int32_t>(0x20000000));
  uos.write(static_cast<int32_t>(0x30000000));
  uos.write(static_cast<int32_t>(0x41000000));
  uos.write(static_cast<int32_t>(0x61000000));
  uos.write(static_cast<int32_t>(0x7e000000));
  // 2byte
  uos.write(static_cast<int32_t>(0x80000000));
  uos.write(static_cast<int32_t>(0xa0000000));
  uos.write(static_cast<int32_t>(0xff000000));
  uos.write(static_cast<int32_t>(0x00010000));
  uos.write(static_cast<int32_t>(0xff070000));
  // 3byte
  uos.write(static_cast<int32_t>(0x00080000));
  uos.write(static_cast<int32_t>(0xff9f0000));
  uos.write(static_cast<int32_t>(0x00a00000));
  uos.write(static_cast<int32_t>(0xfbd70000));
  uos.write(static_cast<int32_t>(0x00f90000));
  // 4byte
  uos.write(static_cast<int32_t>(0xfa000100));
  uos.write(static_cast<int32_t>(0x00000200));
  uos.write(static_cast<int32_t>(0x1cfa0200));
  uos.write(static_cast<int32_t>(0xdd0e0300));
  uos.write(static_cast<int32_t>(0x6c100300));
  uos.write(static_cast<int32_t>(0xfffe0000));
  uos.writeString("あいうえお");
  ASSERT_EQ(uos.toString(), " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬�あいうえお");
  expectUtf16 = {
      static_cast<int16_t>(0xfeff), //
      static_cast<int16_t>(0x0020), //
      static_cast<int16_t>(0x0030), //
      static_cast<int16_t>(0x0041), //
      static_cast<int16_t>(0x0061), //
      static_cast<int16_t>(0x007e), //
      static_cast<int16_t>(0x0080), //
      static_cast<int16_t>(0x00a0), //
      static_cast<int16_t>(0x00ff), //
      static_cast<int16_t>(0x0100), //
      static_cast<int16_t>(0x07ff), //
      static_cast<int16_t>(0x0800), //
      static_cast<int16_t>(0x9fff), //
      static_cast<int16_t>(0xa000), //
      static_cast<int16_t>(0xd7fb), //
      static_cast<int16_t>(0xf900), //
      static_cast<int16_t>(0xd800),
      static_cast<int16_t>(0xdcfa), //
      static_cast<int16_t>(0xd840),
      static_cast<int16_t>(0xdc00), //
      static_cast<int16_t>(0xd87e),
      static_cast<int16_t>(0xde1c), //
      static_cast<int16_t>(0xd883),
      static_cast<int16_t>(0xdedd), //
      static_cast<int16_t>(0xd884),
      static_cast<int16_t>(0xdc6c), //
      static_cast<int16_t>(0xfffd), //
      static_cast<int16_t>(0x3042), //
      static_cast<int16_t>(0x3044), //
      static_cast<int16_t>(0x3046), //
      static_cast<int16_t>(0x3048), //
      static_cast<int16_t>(0x304a), //
  };
  ASSERT_EQ(uos.data(), expectUtf16);
  uos.reset();
  expectUtf16 = {};
  ASSERT_EQ(uos.data(), expectUtf16);
  uos = Utf16OutputStream();
  ASSERT_EQ(uos.data(), expectUtf16);
  uos = Utf16OutputStream(true, true);
  // BE to LE
  uos.write(static_cast<int32_t>(0xfffe0000));
  uos.write(static_cast<int32_t>(0xfffe0000));
  uos.write(static_cast<int32_t>(0x20000000));
  uos.write(static_cast<int32_t>(0x30000000));
  uos.write(static_cast<int32_t>(0x41000000));
  uos.write(static_cast<int32_t>(0x61000000));
  uos.write(static_cast<int32_t>(0x7e000000));
  // 2byte
  uos.write(static_cast<int32_t>(0x80000000));
  uos.write(static_cast<int32_t>(0xa0000000));
  uos.write(static_cast<int32_t>(0xff000000));
  uos.write(static_cast<int32_t>(0x00010000));
  uos.write(static_cast<int32_t>(0xff070000));
  // 3byte
  uos.write(static_cast<int32_t>(0x00080000));
  uos.write(static_cast<int32_t>(0xff9f0000));
  uos.write(static_cast<int32_t>(0x00a00000));
  uos.write(static_cast<int32_t>(0xfbd70000));
  uos.write(static_cast<int32_t>(0x00f90000));
  // 4byte
  uos.write(static_cast<int32_t>(0xfa000100));
  uos.write(static_cast<int32_t>(0x00000200));
  uos.write(static_cast<int32_t>(0x1cfa0200));
  uos.write(static_cast<int32_t>(0xdd0e0300));
  uos.write(static_cast<int32_t>(0x6c100300));
  uos.write(static_cast<int32_t>(0xfffe0000));
  uos.writeString("あいうえお");
  ASSERT_EQ(uos.toString(), " 0Aa~\xc2\x80 ÿĀ߿ࠀ鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬�あいうえお");
  expectUtf16 = {
      static_cast<int16_t>(0xfffe), //
      static_cast<int16_t>(0x2000), //
      static_cast<int16_t>(0x3000), //
      static_cast<int16_t>(0x4100), //
      static_cast<int16_t>(0x6100), //
      static_cast<int16_t>(0x7e00), //
      static_cast<int16_t>(0x8000), //
      static_cast<int16_t>(0xa000), //
      static_cast<int16_t>(0xff00), //
      static_cast<int16_t>(0x0001), //
      static_cast<int16_t>(0xff07), //
      static_cast<int16_t>(0x0008), //
      static_cast<int16_t>(0xff9f), //
      static_cast<int16_t>(0x00a0), //
      static_cast<int16_t>(0xfbd7), //
      static_cast<int16_t>(0x00f9), //
      static_cast<int16_t>(0x00d8),
      static_cast<int16_t>(0xfadc), //
      static_cast<int16_t>(0x40d8),
      static_cast<int16_t>(0x00dc), //
      static_cast<int16_t>(0x7ed8),
      static_cast<int16_t>(0x1cde), //
      static_cast<int16_t>(0x83d8),
      static_cast<int16_t>(0xddde), //
      static_cast<int16_t>(0x84d8),
      static_cast<int16_t>(0x6cdc), //
      static_cast<int16_t>(0xfdff), //
      static_cast<int16_t>(0x4230), //
      static_cast<int16_t>(0x4430), //
      static_cast<int16_t>(0x4630), //
      static_cast<int16_t>(0x4830), //
      static_cast<int16_t>(0x4a30), //
  };
};

} // namespace gallop::IO::Stream