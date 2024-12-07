// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "cli/translate_encoding_to_utf32.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/string/utf16_string.hpp"
#include "char_set/string/utf32_string.hpp"
#include "char_set/string/utf8_string.hpp"
#include "io/stream/byte_array_output_stream.hpp"
#include "io/stream/utf16_input_stream.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

namespace gallop::Cli {
class TranslateEncodingToU32Test : public ::testing::Test {};
TEST(TranslateEncodingToU32Test, InvalidTextEncoding) {
  std::vector<char> buf{
      static_cast<char>(0xff),
      static_cast<char>(0xff),
      static_cast<char>(0xf0),
  };
  Utf32InputStream uis;
  uis = TranslateEncodingToU32::translate(
      EncodingCharsetEnum::InvalidTextEncoding, buf);
  ASSERT_EQ(uis.data().size(), (size_t)0);
};
TEST(TranslateEncodingToU32Test, FromUtf8) {
  std::vector<char> buf;
  Utf32InputStream uis;
  std::vector<int32_t> uisdata;
  std::vector<int32_t> expectUisData;
  std::string u8string;
  buf = {
      /*BOM start*/ static_cast<char>(0xef),
      static_cast<char>(0xbb),
      static_cast<char>(0xbf), /*BOM end*/
      static_cast<char>(0x61),
      static_cast<char>(0xe3),
      static_cast<char>(0x81),
      static_cast<char>(0x82),
      static_cast<char>(0x0a),
  };
  expectUisData = std::vector<int32_t>{
      static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x00003042),
      static_cast<int32_t>(0x0000000a),
  };
  uis = TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF8_BOM, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)3);
  ASSERT_EQ(uisdata, expectUisData);
  expectUisData = {
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
  u8string = " 0Aa~"
             "\xc2\xc2\x80 ÿĀ߿\xe0ࠀ鿿ꀀퟻ豈\xf0𐃺𠀀鼻𰻝𱁬\xc2\xc0"
             "\xe0\xbf\xc0\xf0\xbf\xbf\xc0あいうえお";
  buf = std::vector<char>(u8string.begin(), u8string.end());
  uis = TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF8, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)34);
  ASSERT_EQ(uisdata, expectUisData);
};
TEST(TranslateEncodingToU32Test, FromUtf16BE) {
  std::vector<char> buf;
  Utf32InputStream uis;
  std::vector<int32_t> uisdata;
  std::vector<int32_t> expectUisData;
  buf = {
      /*BOM start*/ static_cast<char>(0xfe),
      static_cast<char>(0xff),
      /*BOM end*/
      static_cast<char>(0x21),
      static_cast<char>(0x20),
  };
  expectUisData = std::vector<int32_t>{
      static_cast<int32_t>(0x00002120),
  };
  uis =
      TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF16BE_BOM, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)1);
  ASSERT_EQ(uisdata, expectUisData);
  ByteArrayOutputStream baos;
  baos.write(std::vector<int16_t>{
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
      static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)});
  expectUisData = std::vector<int32_t>{
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
  buf = baos.data();
  uis = TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF16BE, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)29);
  ASSERT_EQ(uisdata, expectUisData);
};

TEST(TranslateEncodingToU32Test, FromUtf16LE) {
  std::vector<char> buf;
  Utf32InputStream uis;
  std::vector<int32_t> uisdata;
  std::vector<int32_t> expectUisData;
  buf = {
      /*BOM start*/ static_cast<char>(0xff),
      static_cast<char>(0xfe),
      /*BOM end*/
      static_cast<char>(0x20),
      static_cast<char>(0x21),
  };
  expectUisData = std::vector<int32_t>{
      static_cast<int32_t>(0x00002120),
  };
  uis =
      TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF16LE_BOM, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)1);
  ASSERT_EQ(uisdata, expectUisData);
  ByteArrayOutputStream baos;
  baos.write(std::vector<int16_t>{
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
      static_cast<int16_t>(0x4830), static_cast<int16_t>(0x4a30)});
  expectUisData = std::vector<int32_t>{
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
  buf = baos.data();
  uis = TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF16LE, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)29);
  ASSERT_EQ(uisdata, expectUisData);
};
TEST(TranslateEncodingToU32Test, FromUtf32BE) {
  std::vector<char> buf;
  Utf32InputStream uis;
  std::vector<int32_t> uisdata;
  std::vector<int32_t> expectUisData;
  buf = {
      /*BOM start*/ static_cast<char>(0x00),
      static_cast<char>(0x00),
      static_cast<char>(0xfe),
      static_cast<char>(0xff),
      /*BOM end*/
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      static_cast<char>(0x21),
      static_cast<char>(0x20),
  };
  expectUisData = std::vector<int32_t>{
      static_cast<int32_t>(0x00002120),
  };
  uis =
      TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF32BE_BOM, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)1);
  ASSERT_EQ(uisdata, expectUisData);
  ByteArrayOutputStream baos;
  baos.write(std::vector<int32_t>{
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
      static_cast<int32_t>(0x0000304a)});
  expectUisData = std::vector<int32_t>{
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
  buf = baos.data();
  uis = TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF32BE, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)29);
  ASSERT_EQ(uisdata, expectUisData);
};
TEST(TranslateEncodingToU32Test, FromUtf32LE) {
  std::vector<char> buf;
  Utf32InputStream uis;
  std::vector<int32_t> uisdata;
  std::vector<int32_t> expectUisData;
  buf = {
      /*BOM start*/ static_cast<char>(0xff),
      static_cast<char>(0xfe),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      /*BOM end*/
      static_cast<char>(0x20),
      static_cast<char>(0x21),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
  };
  expectUisData = std::vector<int32_t>{
      static_cast<int32_t>(0x00002120),
  };
  uis =
      TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF32LE_BOM, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)1);
  ASSERT_EQ(uisdata, expectUisData);
  ByteArrayOutputStream baos;
  baos.write(std::vector<int32_t>{
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
      static_cast<int32_t>(0x4a300000)});
  expectUisData = std::vector<int32_t>{
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
  buf = baos.data();
  uis = TranslateEncodingToU32::translate(EncodingCharsetEnum::UTF32LE, buf);
  uisdata = uis.data();
  ASSERT_EQ(uisdata.size(), (size_t)29);
  ASSERT_EQ(uisdata, expectUisData);
};

} // namespace gallop::Cli
