// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/detector/detector.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/encoding_charset/encoding_charset.hpp"
#include "char_set/string/utf16_string.hpp"
#include "char_set/string/utf32_string.hpp"
#include "char_set/string/utf8_string.hpp"
#include "io/stream/utf16_input_stream.hpp"
#include "io/stream/utf32_input_stream.hpp"
#include "io/stream/utf8_input_stream.hpp"
#include "io/stream/byte_array_output_stream.hpp"

using namespace gallop::CharSet;
using namespace gallop::IO::Stream;

class DetectorTest : public ::testing::Test {};
TEST(DetectorTest, Invalid) {
  std::vector<char> buf{
      static_cast<char>(0xff),
      static_cast<char>(0xff),
      static_cast<char>(0xf0),
  };
  Detector d(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::InvalidTextEncoding);
};
TEST(DetectorTest, DetectUTFWithBOM) {
  // UTF-32BE
  std::vector<char> buf{
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
  Detector d(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF32BE_BOM);
  buf = {
      /*BOM start*/ static_cast<char>(0x00),
      static_cast<char>(0x00),
      static_cast<char>(0xfe),
      static_cast<char>(0xff),
      /*BOM end*/ static_cast<char>(0x20),
      static_cast<char>(0x21),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
  };
  d = Detector(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::InvalidTextEncoding);

  // UTF-32LE
  buf = {
      /*BOM end*/ static_cast<char>(0xff),
      static_cast<char>(0xfe),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      /*BOM end*/ static_cast<char>(0x20),
      static_cast<char>(0x21),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
  };
  d = Detector(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF32LE_BOM);
  buf = {
      /*BOM end*/ static_cast<char>(0xff),
      static_cast<char>(0xfe),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      /*BOM end*/
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      static_cast<char>(0x20),
      static_cast<char>(0x21),
  };
  d = Detector(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::InvalidTextEncoding);

  // UTF-8
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
  d = Detector(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF8_BOM);
  // UTF-16
  // UTF-16BE
  buf = {
      /*BOM end*/ static_cast<char>(0xff),
      static_cast<char>(0xfe),
      /*BOM end*/ static_cast<char>(0x20),
      static_cast<char>(0x21),
  };
  d = Detector(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF16LE_BOM);
  // UTF-16LE
  buf = {
      /*BOM start*/ static_cast<char>(0xfe),
      static_cast<char>(0xff),
      /*BOM end*/
      static_cast<char>(0x21),
      static_cast<char>(0x20),
  };
  d = Detector(buf);
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF16BE_BOM);
};

TEST(DetectorTest, DetectUtf8) {
  // ASCII
  std::string bufStr = "\t\r\n 0a~";
  Detector d = Detector(std::vector<char>(bufStr.begin(), bufStr.end()));
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::ASCII);

  // ASCII
  bufStr = "09AZaz\t\r\n !/:@[`{~";
  d = Detector(std::vector<char>(bufStr.begin(), bufStr.end()));
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::ASCII);

  bufStr = "ÀÿĀǿȀ˿Ͽӿߺ";
  d = Detector(std::vector<char>(bufStr.begin(), bufStr.end()));
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF8);

  bufStr = "ࠀऀကჿ ⮕、䀀鿿ꀀퟻ豈﫿ﬀ￯";
  d = Detector(std::vector<char>(bufStr.begin(), bufStr.end()));
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF8);

  bufStr = "𐀀𐃺𠀀鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf";
  d = Detector(std::vector<char>(bufStr.begin(), bufStr.end()));
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF8);

  bufStr =
      "09ÀÿĀAZazࠀऀကჿ ⮕、𐀀𐃺𠀀\t\r\n "
      "鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf䀀鿿ꀀퟻ豈﫿ﬀ"
      "￯"
      "!"
      "ǿȀ˿Ͽӿߺ/"
      ":@[`{~";
  d = Detector(std::vector<char>(bufStr.begin(), bufStr.end()));
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF8);

  bufStr =
      "\xef\xbb\xbf"
      "09ÀÿĀAZazࠀऀကჿ ⮕、𐀀𐃺𠀀\t\r\n "
      "鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf䀀鿿ꀀퟻ豈﫿ﬀ"
      "￯"
      "!"
      "ǿȀ˿Ͽӿߺ/"
      ":@[`{~";
  d = Detector(std::vector<char>(bufStr.begin(), bufStr.end()));
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF8_BOM);
};

TEST(DetectorTest, DetectUtf16) {
  ByteArrayOutputStream baos;
  baos.reserve(40);
  // UTF-16BE BOM(adulteration LE newline)
  baos.write(std::vector<int16_t>{
      static_cast<int16_t>(0xfeff), static_cast<int16_t>(0x0a00),
      static_cast<int16_t>(0xd883), static_cast<int16_t>(0xdedd),
      static_cast<int16_t>(0xd884), static_cast<int16_t>(0xdc6c),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0x3042), static_cast<int16_t>(0x3044),
      static_cast<int16_t>(0x3046), static_cast<int16_t>(0x3048),
      static_cast<int16_t>(0x304a)});
  Detector d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::InvalidTextEncoding);
  baos.reset();
  baos.reserve(40);
  // UTF-16BE BOM
  baos.write(std::vector<int16_t>{
      static_cast<int16_t>(0xfeff), static_cast<int16_t>(0x0041),
      static_cast<int16_t>(0x0061), static_cast<int16_t>(0x007e),
      static_cast<int16_t>(0x0080), static_cast<int16_t>(0x00a0),
      static_cast<int16_t>(0x00ff), static_cast<int16_t>(0x0100),
      static_cast<int16_t>(0x07ff), static_cast<int16_t>(0x0800),
      static_cast<int16_t>(0x9fff), static_cast<int16_t>(0xa000),
      static_cast<int16_t>(0xd7fb), static_cast<int16_t>(0xf900),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdcfa),
      static_cast<int16_t>(0xd840), static_cast<int16_t>(0xdc00),
      static_cast<int16_t>(0xd87e), static_cast<int16_t>(0xde1c),
      static_cast<int16_t>(0xd883), static_cast<int16_t>(0xdedd),
      static_cast<int16_t>(0xd884), static_cast<int16_t>(0xdc6c),
      static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
      static_cast<int16_t>(0x3042), static_cast<int16_t>(0x3044),
      static_cast<int16_t>(0x3046), static_cast<int16_t>(0x3048),
      static_cast<int16_t>(0x304a)});
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF16BE_BOM);
  baos.reset();
  baos.reserve(40);
  // UTF-16BE
  baos.write(std::vector<int16_t>{
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
      static_cast<int16_t>(0x3048), static_cast<int16_t>(0x304a)});
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF16BE);

  baos.reset();
  baos.reserve(40);
  // UTF-16LE BOM(adulteration BE newline)
  baos.write(
      std::vector<int16_t>{
          static_cast<int16_t>(0xfeff), static_cast<int16_t>(0x0a00),
          static_cast<int16_t>(0xd883), static_cast<int16_t>(0xdedd),
          static_cast<int16_t>(0xd884), static_cast<int16_t>(0xdc6c),
          static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
          static_cast<int16_t>(0x3042), static_cast<int16_t>(0x3044),
          static_cast<int16_t>(0x3046), static_cast<int16_t>(0x3048),
          static_cast<int16_t>(0x304a)},
      true);
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::InvalidTextEncoding);
  baos.reset();
  baos.reserve(40);
  // UTF-16LE BOM
  baos.write(
      std::vector<int16_t>{
          static_cast<int16_t>(0xfeff), static_cast<int16_t>(0x0041),
          static_cast<int16_t>(0x0061), static_cast<int16_t>(0x007e),
          static_cast<int16_t>(0x0080), static_cast<int16_t>(0x00a0),
          static_cast<int16_t>(0x00ff), static_cast<int16_t>(0x0100),
          static_cast<int16_t>(0x07ff), static_cast<int16_t>(0x0800),
          static_cast<int16_t>(0x9fff), static_cast<int16_t>(0xa000),
          static_cast<int16_t>(0xd7fb), static_cast<int16_t>(0xf900),
          static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
          static_cast<int16_t>(0xd800), static_cast<int16_t>(0xdcfa),
          static_cast<int16_t>(0xd840), static_cast<int16_t>(0xdc00),
          static_cast<int16_t>(0xd87e), static_cast<int16_t>(0xde1c),
          static_cast<int16_t>(0xd883), static_cast<int16_t>(0xdedd),
          static_cast<int16_t>(0xd884), static_cast<int16_t>(0xdc6c),
          static_cast<int16_t>(0xfffd), static_cast<int16_t>(0xfffd),
          static_cast<int16_t>(0x3042), static_cast<int16_t>(0x3044),
          static_cast<int16_t>(0x3046), static_cast<int16_t>(0x3048),
          static_cast<int16_t>(0x304a)},
      true);
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF16LE_BOM);
  baos.reset();
  baos.reserve(40);
  // UTF-16LE
  baos.write(
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
      true);
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF16LE);
};

TEST(DetectorTest, DetectUtf32) {
  ByteArrayOutputStream baos;
  baos.reserve(40);
  // UTF-32BE BOM(adulteration LE)
  baos.write(std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff),
      static_cast<int32_t>(0x00000020),
      static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000041),
      static_cast<int32_t>(0x00610000),
  });
  Detector d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::InvalidTextEncoding);
  baos.reset();
  baos.reserve(40);
  // UTF-32BE BOM
  baos.write(std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00000020),
      static_cast<int32_t>(0x00000030), static_cast<int32_t>(0x00000041),
      static_cast<int32_t>(0x00000061), static_cast<int32_t>(0x0000007e),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x00000800),
      static_cast<int32_t>(0x00009fff), static_cast<int32_t>(0x0000a000),
      static_cast<int32_t>(0x0000d7fb), static_cast<int32_t>(0x0000f900),
      static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
      static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
      static_cast<int32_t>(0x0000304a),
  });
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF32BE_BOM);
  baos.reset();
  baos.reserve(40);
  // UTF-32BE
  baos.write(std::vector<int32_t>{
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
  });
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF32BE);

  baos.reset();
  baos.reserve(40);
  // UTF-32LE BOM(adulteration BE)
  baos.write(
      std::vector<int32_t>{
          static_cast<int32_t>(0x0000feff),
          static_cast<int32_t>(0x00000020),
          static_cast<int32_t>(0x00000030),
          static_cast<int32_t>(0x00000041),
          static_cast<int32_t>(0x00610000),
      },
      true);
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::InvalidTextEncoding);
  baos.reset();
  baos.reserve(40);
  // UTF-32BE BOM
  baos.write(
      std::vector<int32_t>{
          static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00000020),
          static_cast<int32_t>(0x00000030), static_cast<int32_t>(0x00000041),
          static_cast<int32_t>(0x00000061), static_cast<int32_t>(0x0000007e),
          static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x00000080),
          static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000007ff),
          static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x00000800),
          static_cast<int32_t>(0x00009fff), static_cast<int32_t>(0x0000a000),
          static_cast<int32_t>(0x0000d7fb), static_cast<int32_t>(0x0000f900),
          static_cast<int32_t>(0x0000fffd), static_cast<int32_t>(0x000100fa),
          static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
          static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
          static_cast<int32_t>(0x00003042), static_cast<int32_t>(0x00003044),
          static_cast<int32_t>(0x00003046), static_cast<int32_t>(0x00003048),
          static_cast<int32_t>(0x0000304a),
      },
      true);
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF32LE_BOM);
  baos.reset();
  baos.reserve(40);
  // UTF-32BE
  baos.write(
      std::vector<int32_t>{
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
      },
      true);
  d = Detector(baos.data());
  ASSERT_EQ(d.encodingCharSet(), EncodingCharsetEnum::UTF32LE);
};
