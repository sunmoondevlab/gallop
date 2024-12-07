#include "io/stream/utf32_output_stream.hpp"
#include <gtest/gtest.h>

namespace gallop::IO::Stream {

class Utf32OutputStreamTest : public ::testing::Test {};
TEST_F(Utf32OutputStreamTest, String) {
  Utf32OutputStream uos;
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
  std::vector<int32_t> expectUtf32{
      static_cast<int32_t>(0x0000feff), //
      static_cast<int32_t>(0x00000020), //
      static_cast<int32_t>(0x00000030), //
      static_cast<int32_t>(0x00000041), //
      static_cast<int32_t>(0x00000061), //
      static_cast<int32_t>(0x0000007e), //
      static_cast<int32_t>(0x00000080), //
      static_cast<int32_t>(0x000000a0), //
      static_cast<int32_t>(0x000000ff), //
      static_cast<int32_t>(0x00000100), //
      static_cast<int32_t>(0x000007ff), //
      static_cast<int32_t>(0x00000800), //
      static_cast<int32_t>(0x00009fff), //
      static_cast<int32_t>(0x0000a000), //
      static_cast<int32_t>(0x0000d7fb), //
      static_cast<int32_t>(0x0000f900), //
      static_cast<int32_t>(0x000100fa), //
      static_cast<int32_t>(0x00020000), //
      static_cast<int32_t>(0x0002fa1c), //
      static_cast<int32_t>(0x00030edd), //
      static_cast<int32_t>(0x0003106c), //
      static_cast<int32_t>(0x0000fffd), //
      static_cast<int32_t>(0x00003042), //
      static_cast<int32_t>(0x00003044), //
      static_cast<int32_t>(0x00003046), //
      static_cast<int32_t>(0x00003048), //
      static_cast<int32_t>(0x0000304a), //
  };
  ASSERT_EQ(uos.data(), expectUtf32);
  uos.reset();
  expectUtf32 = {};
  ASSERT_EQ(uos.data(), expectUtf32);
  uos = Utf32OutputStream();
  ASSERT_EQ(uos.data(), expectUtf32);
  uos = Utf32OutputStream(true);
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
  expectUtf32 = {
      static_cast<int32_t>(0xfffe0000), //
      static_cast<int32_t>(0x20000000), //
      static_cast<int32_t>(0x30000000), //
      static_cast<int32_t>(0x41000000), //
      static_cast<int32_t>(0x61000000), //
      static_cast<int32_t>(0x7e000000), //
      static_cast<int32_t>(0x80000000), //
      static_cast<int32_t>(0xa0000000), //
      static_cast<int32_t>(0xff000000), //
      static_cast<int32_t>(0x00010000), //
      static_cast<int32_t>(0xff070000), //
      static_cast<int32_t>(0x00080000), //
      static_cast<int32_t>(0xff9f0000), //
      static_cast<int32_t>(0x00a00000), //
      static_cast<int32_t>(0xfbd70000), //
      static_cast<int32_t>(0x00f90000), //
      static_cast<int32_t>(0xfa000100), //
      static_cast<int32_t>(0x00000200), //
      static_cast<int32_t>(0x1cfa0200), //
      static_cast<int32_t>(0xdd0e0300), //
      static_cast<int32_t>(0x6c100300), //
      static_cast<int32_t>(0xfdff0000), //
      static_cast<int32_t>(0x42300000), //
      static_cast<int32_t>(0x44300000), //
      static_cast<int32_t>(0x46300000), //
      static_cast<int32_t>(0x48300000), //
      static_cast<int32_t>(0x4a300000), //
  };
  uos = Utf32OutputStream(true, false);
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
  expectUtf32 = {
      static_cast<int32_t>(0x0000feff), //
      static_cast<int32_t>(0x00000020), //
      static_cast<int32_t>(0x00000030), //
      static_cast<int32_t>(0x00000041), //
      static_cast<int32_t>(0x00000061), //
      static_cast<int32_t>(0x0000007e), //
      static_cast<int32_t>(0x00000080), //
      static_cast<int32_t>(0x000000a0), //
      static_cast<int32_t>(0x000000ff), //
      static_cast<int32_t>(0x00000100), //
      static_cast<int32_t>(0x000007ff), //
      static_cast<int32_t>(0x00000800), //
      static_cast<int32_t>(0x00009fff), //
      static_cast<int32_t>(0x0000a000), //
      static_cast<int32_t>(0x0000d7fb), //
      static_cast<int32_t>(0x0000f900), //
      static_cast<int32_t>(0x000100fa), //
      static_cast<int32_t>(0x00020000), //
      static_cast<int32_t>(0x0002fa1c), //
      static_cast<int32_t>(0x00030edd), //
      static_cast<int32_t>(0x0003106c), //
      static_cast<int32_t>(0x0000fffd), //
      static_cast<int32_t>(0x00003042), //
      static_cast<int32_t>(0x00003044), //
      static_cast<int32_t>(0x00003046), //
      static_cast<int32_t>(0x00003048), //
      static_cast<int32_t>(0x0000304a), //
  };
  ASSERT_EQ(uos.data(), expectUtf32);
  uos.reset();
  expectUtf32 = {};
  ASSERT_EQ(uos.data(), expectUtf32);
  uos = Utf32OutputStream();
  ASSERT_EQ(uos.data(), expectUtf32);
  uos = Utf32OutputStream(true, true);
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
  expectUtf32 = {
      static_cast<int32_t>(0xfffe0000), //
      static_cast<int32_t>(0x20000000), //
      static_cast<int32_t>(0x30000000), //
      static_cast<int32_t>(0x41000000), //
      static_cast<int32_t>(0x61000000), //
      static_cast<int32_t>(0x7e000000), //
      static_cast<int32_t>(0x80000000), //
      static_cast<int32_t>(0xa0000000), //
      static_cast<int32_t>(0xff000000), //
      static_cast<int32_t>(0x00010000), //
      static_cast<int32_t>(0xff070000), //
      static_cast<int32_t>(0x00080000), //
      static_cast<int32_t>(0xff9f0000), //
      static_cast<int32_t>(0x00a00000), //
      static_cast<int32_t>(0xfbd70000), //
      static_cast<int32_t>(0x00f90000), //
      static_cast<int32_t>(0xfa000100), //
      static_cast<int32_t>(0x00000200), //
      static_cast<int32_t>(0x1cfa0200), //
      static_cast<int32_t>(0xdd0e0300), //
      static_cast<int32_t>(0x6c100300), //
      static_cast<int32_t>(0xfdff0000), //
      static_cast<int32_t>(0x42300000), //
      static_cast<int32_t>(0x44300000), //
      static_cast<int32_t>(0x46300000), //
      static_cast<int32_t>(0x48300000), //
      static_cast<int32_t>(0x4a300000), //
  };
};

} // namespace gallop::IO::Stream