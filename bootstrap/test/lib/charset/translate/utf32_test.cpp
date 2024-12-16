#if 0
#include "charset/translate/utf32.hpp"
#include <gtest/gtest.h>
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet::Translate;

class Utf32EncoderTest : public ::testing::Test {};
TEST(Utf32EncoderTest, EncodeTest) {
  std::string str;
  std::vector<int32_t> utf32EncRunes;
  std::vector<int32_t> expectRunesBuf;
  std::vector<char> utf32Enc;
  std::vector<char> expectBuf;
  // 1 bytes
  str = "09AZaz\t\r\n !/:@[`{~";

  // UTF-32BE without BOM
  Utf32Encoder utf32Buf(str, false, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000030), static_cast<int32_t>(0x00000039),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x0000005a),
      static_cast<int32_t>(0x00000061), static_cast<int32_t>(0x0000007a),
      static_cast<int32_t>(0x00000009), static_cast<int32_t>(0x0000000d),
      static_cast<int32_t>(0x0000000a), static_cast<int32_t>(0x00000020),
      static_cast<int32_t>(0x00000021), static_cast<int32_t>(0x0000002f),
      static_cast<int32_t>(0x0000003a), static_cast<int32_t>(0x00000040),
      static_cast<int32_t>(0x0000005b), static_cast<int32_t>(0x00000060),
      static_cast<int32_t>(0x0000007b), static_cast<int32_t>(0x0000007e),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x39), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x41),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x5a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x61), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x0d), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x0a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x21), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x2f),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x3a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x5b),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x60), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 18ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 72ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE without BOM
  utf32Buf = Utf32Encoder(str, true, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x30000000), static_cast<int32_t>(0x39000000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x5a000000),
      static_cast<int32_t>(0x61000000), static_cast<int32_t>(0x7a000000),
      static_cast<int32_t>(0x09000000), static_cast<int32_t>(0x0d000000),
      static_cast<int32_t>(0x0a000000), static_cast<int32_t>(0x20000000),
      static_cast<int32_t>(0x21000000), static_cast<int32_t>(0x2f000000),
      static_cast<int32_t>(0x3a000000), static_cast<int32_t>(0x40000000),
      static_cast<int32_t>(0x5b000000), static_cast<int32_t>(0x60000000),
      static_cast<int32_t>(0x7b000000), static_cast<int32_t>(0x7e000000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x39), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x41),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x5a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x61), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x0d), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x0a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x21), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x2f),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x3a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x5b),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x60), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7e),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 18ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 72ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32BE with BOM
  utf32Buf = Utf32Encoder(str, false, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000039), static_cast<int32_t>(0x00000041),
      static_cast<int32_t>(0x0000005a), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007a), static_cast<int32_t>(0x00000009),
      static_cast<int32_t>(0x0000000d), static_cast<int32_t>(0x0000000a),
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x00000021),
      static_cast<int32_t>(0x0000002f), static_cast<int32_t>(0x0000003a),
      static_cast<int32_t>(0x00000040), static_cast<int32_t>(0x0000005b),
      static_cast<int32_t>(0x00000060), static_cast<int32_t>(0x0000007b),
      static_cast<int32_t>(0x0000007e),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfe),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x41), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x5a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x61),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x0d),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x0a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x21),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x2f), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x3a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x5b), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x60), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7b),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 19ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 76ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE with BOM
  utf32Buf = Utf32Encoder(str, true, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0xfffe0000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x39000000), static_cast<int32_t>(0x41000000),
      static_cast<int32_t>(0x5a000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7a000000), static_cast<int32_t>(0x09000000),
      static_cast<int32_t>(0x0d000000), static_cast<int32_t>(0x0a000000),
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x21000000),
      static_cast<int32_t>(0x2f000000), static_cast<int32_t>(0x3a000000),
      static_cast<int32_t>(0x40000000), static_cast<int32_t>(0x5b000000),
      static_cast<int32_t>(0x60000000), static_cast<int32_t>(0x7b000000),
      static_cast<int32_t>(0x7e000000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x41), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x5a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x61),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x0d),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x0a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x21),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x2f), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x3a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x5b), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x60), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7b),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7e), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 19ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 76ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // 2 bytes
  str = "ÀÿĀǿȀ˿Ͽӿߺ";

  // UTF-32BE without BOM
  utf32Buf = Utf32Encoder(str, false, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000080), static_cast<int32_t>(0x000000c0),
      static_cast<int32_t>(0x000000ff), static_cast<int32_t>(0x00000100),
      static_cast<int32_t>(0x000001ff), static_cast<int32_t>(0x00000200),
      static_cast<int32_t>(0x000002ff), static_cast<int32_t>(0x000003ff),
      static_cast<int32_t>(0x000004ff), static_cast<int32_t>(0x000007fa),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x80), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xc0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x03), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x04), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x07),
      static_cast<char>(0xfa),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 10ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 40ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE without BOM
  utf32Buf = Utf32Encoder(str, true, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x80000000), static_cast<int32_t>(0xc0000000),
      static_cast<int32_t>(0xff000000), static_cast<int32_t>(0x00010000),
      static_cast<int32_t>(0xff010000), static_cast<int32_t>(0x00020000),
      static_cast<int32_t>(0xff020000), static_cast<int32_t>(0xff030000),
      static_cast<int32_t>(0xff040000), static_cast<int32_t>(0xfa070000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x80), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xc0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x03),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x04), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfa), static_cast<char>(0x07), static_cast<char>(0x00),
      static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 10ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 40ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32BE with BOM
  utf32Buf = Utf32Encoder(str, false, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000c0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000001ff),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x000002ff),
      static_cast<int32_t>(0x000003ff), static_cast<int32_t>(0x000004ff),
      static_cast<int32_t>(0x000007fa),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfe),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xc0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x03), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x04),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x07), static_cast<char>(0xfa),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 11ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 44ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE with BOM
  utf32Buf = Utf32Encoder(str, true, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0xfffe0000), static_cast<int32_t>(0x80000000),
      static_cast<int32_t>(0xc0000000), static_cast<int32_t>(0xff000000),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0xff010000),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0xff020000),
      static_cast<int32_t>(0xff030000), static_cast<int32_t>(0xff040000),
      static_cast<int32_t>(0xfa070000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xc0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x03), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x04), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0x07),
      static_cast<char>(0x00), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 11ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 44ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // 3 bytes
  str = "ࠀऀကჿ ⮕、䀀鿿ꀀퟻ豈﫿ﬀ￯";

  // UTF-32BE without BOM
  utf32Buf = Utf32Encoder(str, false, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00000900),
      static_cast<int32_t>(0x00001000), static_cast<int32_t>(0x000010ff),
      static_cast<int32_t>(0x00002000), static_cast<int32_t>(0x00002b95),
      static_cast<int32_t>(0x00003001), static_cast<int32_t>(0x00004000),
      static_cast<int32_t>(0x00009fff), static_cast<int32_t>(0x0000a000),
      static_cast<int32_t>(0x0000d7fb), static_cast<int32_t>(0x0000e000),
      static_cast<int32_t>(0x0000f8ff), static_cast<int32_t>(0x0000f900),
      static_cast<int32_t>(0x0000faff), static_cast<int32_t>(0x0000fb00),
      static_cast<int32_t>(0x0000ffef),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x2b), static_cast<char>(0x95),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x30),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x9f), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xa0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xd7), static_cast<char>(0xfb), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xe0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xf8),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xf9), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfb),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0xef),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 17ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 68ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE without BOM
  utf32Buf = Utf32Encoder(str, true, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0x00090000),
      static_cast<int32_t>(0x00100000), static_cast<int32_t>(0xff100000),
      static_cast<int32_t>(0x00200000), static_cast<int32_t>(0x952b0000),
      static_cast<int32_t>(0x01300000), static_cast<int32_t>(0x00400000),
      static_cast<int32_t>(0xff9f0000), static_cast<int32_t>(0x00a00000),
      static_cast<int32_t>(0xfbd70000), static_cast<int32_t>(0x00e00000),
      static_cast<int32_t>(0xfff80000), static_cast<int32_t>(0x00f90000),
      static_cast<int32_t>(0xfffa0000), static_cast<int32_t>(0x00fb0000),
      static_cast<int32_t>(0xefff0000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x08), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x95),
      static_cast<char>(0x2b), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x9f), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xa0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xfb), static_cast<char>(0xd7),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xe0), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0xf8), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xf9),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0xfa), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xfb), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xef), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 17ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 68ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32BE with BOM
  utf32Buf = Utf32Encoder(str, false, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00000800),
      static_cast<int32_t>(0x00000900), static_cast<int32_t>(0x00001000),
      static_cast<int32_t>(0x000010ff), static_cast<int32_t>(0x00002000),
      static_cast<int32_t>(0x00002b95), static_cast<int32_t>(0x00003001),
      static_cast<int32_t>(0x00004000), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000e000), static_cast<int32_t>(0x0000f8ff),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000faff),
      static_cast<int32_t>(0x0000fb00), static_cast<int32_t>(0x0000ffef),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfe),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x08), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x2b),
      static_cast<char>(0x95), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x30), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x9f),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xa0), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xd7), static_cast<char>(0xfb),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xe0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xf8), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xf9), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfa),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfb), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xef),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 18ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 72ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE with BOM
  utf32Buf = Utf32Encoder(str, true, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0xfffe0000), static_cast<int32_t>(0x00080000),
      static_cast<int32_t>(0x00090000), static_cast<int32_t>(0x00100000),
      static_cast<int32_t>(0xff100000), static_cast<int32_t>(0x00200000),
      static_cast<int32_t>(0x952b0000), static_cast<int32_t>(0x01300000),
      static_cast<int32_t>(0x00400000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00e00000), static_cast<int32_t>(0xfff80000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfffa0000),
      static_cast<int32_t>(0x00fb0000), static_cast<int32_t>(0xefff0000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x95), static_cast<char>(0x2b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x30),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x9f), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xa0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfb),
      static_cast<char>(0xd7), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xe0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xf8),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xf9), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfb),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xef),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 18ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 72ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // 4 bytes
  str = "𐀀𐃺𠀀鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf";

  // UTF-32BE without BOM
  utf32Buf = Utf32Encoder(str, false, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x00100000), static_cast<int32_t>(0x0010ffff),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0xfa),
      static_cast<char>(0x1c), static_cast<char>(0x00), static_cast<char>(0x03),
      static_cast<char>(0x0e), static_cast<char>(0xdd), static_cast<char>(0x00),
      static_cast<char>(0x03), static_cast<char>(0x10), static_cast<char>(0x6c),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0xff), static_cast<char>(0xff),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 8ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 32ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE without BOM
  utf32Buf = Utf32Encoder(str, true, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0xfa000100),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x1cfa0200),
      static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0x00001000), static_cast<int32_t>(0xffff1000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x1c), static_cast<char>(0xfa), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0xdd), static_cast<char>(0x0e),
      static_cast<char>(0x03), static_cast<char>(0x00), static_cast<char>(0x6c),
      static_cast<char>(0x10), static_cast<char>(0x03), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xff),
      static_cast<char>(0x10), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 8ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 32ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32BE with BOM
  utf32Buf = Utf32Encoder(str, false, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00010000),
      static_cast<int32_t>(0x000100fa), static_cast<int32_t>(0x00020000),
      static_cast<int32_t>(0x0002fa1c), static_cast<int32_t>(0x00030edd),
      static_cast<int32_t>(0x0003106c), static_cast<int32_t>(0x00100000),
      static_cast<int32_t>(0x0010ffff),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfe),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0xfa),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xfa), static_cast<char>(0x1c), static_cast<char>(0x00),
      static_cast<char>(0x03), static_cast<char>(0x0e), static_cast<char>(0xdd),
      static_cast<char>(0x00), static_cast<char>(0x03), static_cast<char>(0x10),
      static_cast<char>(0x6c), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0xff), static_cast<char>(0xff),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 9ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 36ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE with BOM
  utf32Buf = Utf32Encoder(str, true, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0xfffe0000), static_cast<int32_t>(0x00000100),
      static_cast<int32_t>(0xfa000100), static_cast<int32_t>(0x00000200),
      static_cast<int32_t>(0x1cfa0200), static_cast<int32_t>(0xdd0e0300),
      static_cast<int32_t>(0x6c100300), static_cast<int32_t>(0x00001000),
      static_cast<int32_t>(0xffff1000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0xfa),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0x1c), static_cast<char>(0xfa),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0xdd),
      static_cast<char>(0x0e), static_cast<char>(0x03), static_cast<char>(0x00),
      static_cast<char>(0x6c), static_cast<char>(0x10), static_cast<char>(0x03),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0xff), static_cast<char>(0x10), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 9ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 36ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // mix
  str =
      "09ÀÿĀAZazࠀऀကჿ ⮕、𐀀𐃺𠀀\t\r\n "
      "鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf䀀鿿ꀀퟻ豈﫿ﬀ"
      "￯"
      "!"
      "ǿȀ˿Ͽӿߺ/"
      ":@[`{~";

  // UTF-32BE without BOM
  utf32Buf = Utf32Encoder(str, false, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000030), static_cast<int32_t>(0x00000039),
      static_cast<int32_t>(0x00000080), static_cast<int32_t>(0x000000c0),
      static_cast<int32_t>(0x000000ff), static_cast<int32_t>(0x00000100),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x0000005a),
      static_cast<int32_t>(0x00000061), static_cast<int32_t>(0x0000007a),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00000900),
      static_cast<int32_t>(0x00001000), static_cast<int32_t>(0x000010ff),
      static_cast<int32_t>(0x00002000), static_cast<int32_t>(0x00002b95),
      static_cast<int32_t>(0x00003001), static_cast<int32_t>(0x00010000),
      static_cast<int32_t>(0x000100fa), static_cast<int32_t>(0x00020000),
      static_cast<int32_t>(0x00000009), static_cast<int32_t>(0x0000000d),
      static_cast<int32_t>(0x0000000a), static_cast<int32_t>(0x00000020),
      static_cast<int32_t>(0x0002fa1c), static_cast<int32_t>(0x00030edd),
      static_cast<int32_t>(0x0003106c), static_cast<int32_t>(0x00100000),
      static_cast<int32_t>(0x0010ffff), static_cast<int32_t>(0x00004000),
      static_cast<int32_t>(0x00009fff), static_cast<int32_t>(0x0000a000),
      static_cast<int32_t>(0x0000d7fb), static_cast<int32_t>(0x0000e000),
      static_cast<int32_t>(0x0000f8ff), static_cast<int32_t>(0x0000f900),
      static_cast<int32_t>(0x0000faff), static_cast<int32_t>(0x0000fb00),
      static_cast<int32_t>(0x0000ffef), static_cast<int32_t>(0x00000021),
      static_cast<int32_t>(0x000001ff), static_cast<int32_t>(0x00000200),
      static_cast<int32_t>(0x000002ff), static_cast<int32_t>(0x000003ff),
      static_cast<int32_t>(0x000004ff), static_cast<int32_t>(0x000007fa),
      static_cast<int32_t>(0x0000002f), static_cast<int32_t>(0x0000003a),
      static_cast<int32_t>(0x00000040), static_cast<int32_t>(0x0000005b),
      static_cast<int32_t>(0x00000060), static_cast<int32_t>(0x0000007b),
      static_cast<int32_t>(0x0000007e),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x39), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x80),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xc0), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x41), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x5a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x61),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x08), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x2b),
      static_cast<char>(0x95), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x30), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0xfa), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x0d), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x0a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0xfa),
      static_cast<char>(0x1c), static_cast<char>(0x00), static_cast<char>(0x03),
      static_cast<char>(0x0e), static_cast<char>(0xdd), static_cast<char>(0x00),
      static_cast<char>(0x03), static_cast<char>(0x10), static_cast<char>(0x6c),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0xff), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x9f),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xa0), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xd7), static_cast<char>(0xfb),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xe0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xf8), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xf9), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfa),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfb), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xef),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x21), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x03), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x04), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x07),
      static_cast<char>(0xfa), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x2f), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x3a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x5b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x60),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7b), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 53ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 212ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE without BOM
  utf32Buf = Utf32Encoder(str, true, false);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x30000000), static_cast<int32_t>(0x39000000),
      static_cast<int32_t>(0x80000000), static_cast<int32_t>(0xc0000000),
      static_cast<int32_t>(0xff000000), static_cast<int32_t>(0x00010000),
      static_cast<int32_t>(0x41000000), static_cast<int32_t>(0x5a000000),
      static_cast<int32_t>(0x61000000), static_cast<int32_t>(0x7a000000),
      static_cast<int32_t>(0x00080000), static_cast<int32_t>(0x00090000),
      static_cast<int32_t>(0x00100000), static_cast<int32_t>(0xff100000),
      static_cast<int32_t>(0x00200000), static_cast<int32_t>(0x952b0000),
      static_cast<int32_t>(0x01300000), static_cast<int32_t>(0x00000100),
      static_cast<int32_t>(0xfa000100), static_cast<int32_t>(0x00000200),
      static_cast<int32_t>(0x09000000), static_cast<int32_t>(0x0d000000),
      static_cast<int32_t>(0x0a000000), static_cast<int32_t>(0x20000000),
      static_cast<int32_t>(0x1cfa0200), static_cast<int32_t>(0xdd0e0300),
      static_cast<int32_t>(0x6c100300), static_cast<int32_t>(0x00001000),
      static_cast<int32_t>(0xffff1000), static_cast<int32_t>(0x00400000),
      static_cast<int32_t>(0xff9f0000), static_cast<int32_t>(0x00a00000),
      static_cast<int32_t>(0xfbd70000), static_cast<int32_t>(0x00e00000),
      static_cast<int32_t>(0xfff80000), static_cast<int32_t>(0x00f90000),
      static_cast<int32_t>(0xfffa0000), static_cast<int32_t>(0x00fb0000),
      static_cast<int32_t>(0xefff0000), static_cast<int32_t>(0x21000000),
      static_cast<int32_t>(0xff010000), static_cast<int32_t>(0x00020000),
      static_cast<int32_t>(0xff020000), static_cast<int32_t>(0xff030000),
      static_cast<int32_t>(0xff040000), static_cast<int32_t>(0xfa070000),
      static_cast<int32_t>(0x2f000000), static_cast<int32_t>(0x3a000000),
      static_cast<int32_t>(0x40000000), static_cast<int32_t>(0x5b000000),
      static_cast<int32_t>(0x60000000), static_cast<int32_t>(0x7b000000),
      static_cast<int32_t>(0x7e000000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x39), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x80),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xc0), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x41), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x5a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x61),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x95), static_cast<char>(0x2b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x30),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0xfa), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x0d), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x0a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x1c), static_cast<char>(0xfa), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0xdd), static_cast<char>(0x0e),
      static_cast<char>(0x03), static_cast<char>(0x00), static_cast<char>(0x6c),
      static_cast<char>(0x10), static_cast<char>(0x03), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xff),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x9f), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xa0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfb),
      static_cast<char>(0xd7), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xe0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xf8),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xf9), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfb),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xef),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x21), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x03),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x04), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfa), static_cast<char>(0x07), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x2f), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x3a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x5b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x60),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x7b), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7e), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 53ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 212ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32BE with BOM
  utf32Buf = Utf32Encoder(str, false, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00000030),
      static_cast<int32_t>(0x00000039), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000c0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x00000041),
      static_cast<int32_t>(0x0000005a), static_cast<int32_t>(0x00000061),
      static_cast<int32_t>(0x0000007a), static_cast<int32_t>(0x00000800),
      static_cast<int32_t>(0x00000900), static_cast<int32_t>(0x00001000),
      static_cast<int32_t>(0x000010ff), static_cast<int32_t>(0x00002000),
      static_cast<int32_t>(0x00002b95), static_cast<int32_t>(0x00003001),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0x000100fa),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0x00000009),
      static_cast<int32_t>(0x0000000d), static_cast<int32_t>(0x0000000a),
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x0002fa1c),
      static_cast<int32_t>(0x00030edd), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x00100000), static_cast<int32_t>(0x0010ffff),
      static_cast<int32_t>(0x00004000), static_cast<int32_t>(0x00009fff),
      static_cast<int32_t>(0x0000a000), static_cast<int32_t>(0x0000d7fb),
      static_cast<int32_t>(0x0000e000), static_cast<int32_t>(0x0000f8ff),
      static_cast<int32_t>(0x0000f900), static_cast<int32_t>(0x0000faff),
      static_cast<int32_t>(0x0000fb00), static_cast<int32_t>(0x0000ffef),
      static_cast<int32_t>(0x00000021), static_cast<int32_t>(0x000001ff),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x000002ff),
      static_cast<int32_t>(0x000003ff), static_cast<int32_t>(0x000004ff),
      static_cast<int32_t>(0x000007fa), static_cast<int32_t>(0x0000002f),
      static_cast<int32_t>(0x0000003a), static_cast<int32_t>(0x00000040),
      static_cast<int32_t>(0x0000005b), static_cast<int32_t>(0x00000060),
      static_cast<int32_t>(0x0000007b), static_cast<int32_t>(0x0000007e),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xfe),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x80), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xc0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x41), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x5a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x61), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x08), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x2b), static_cast<char>(0x95), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x30), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x0d), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x0a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xfa), static_cast<char>(0x1c), static_cast<char>(0x00),
      static_cast<char>(0x03), static_cast<char>(0x0e), static_cast<char>(0xdd),
      static_cast<char>(0x00), static_cast<char>(0x03), static_cast<char>(0x10),
      static_cast<char>(0x6c), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0xff), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x9f), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xa0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xd7),
      static_cast<char>(0xfb), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xe0), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xf8), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xf9),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfa), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xfb), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0xef), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x21), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x03), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x04),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x07), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x2f),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x3a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x5b),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x60), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 54ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 216ul);
  ASSERT_EQ(utf32Enc, expectBuf);

  // UTF-32LE without BOM
  utf32Buf = Utf32Encoder(str, true, true);
  utf32Enc = utf32Buf.getUtf32Buffer();
  utf32EncRunes = utf32Buf.getUtf32RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0xfffe0000), static_cast<int32_t>(0x30000000),
      static_cast<int32_t>(0x39000000), static_cast<int32_t>(0x80000000),
      static_cast<int32_t>(0xc0000000), static_cast<int32_t>(0xff000000),
      static_cast<int32_t>(0x00010000), static_cast<int32_t>(0x41000000),
      static_cast<int32_t>(0x5a000000), static_cast<int32_t>(0x61000000),
      static_cast<int32_t>(0x7a000000), static_cast<int32_t>(0x00080000),
      static_cast<int32_t>(0x00090000), static_cast<int32_t>(0x00100000),
      static_cast<int32_t>(0xff100000), static_cast<int32_t>(0x00200000),
      static_cast<int32_t>(0x952b0000), static_cast<int32_t>(0x01300000),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0xfa000100),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x09000000),
      static_cast<int32_t>(0x0d000000), static_cast<int32_t>(0x0a000000),
      static_cast<int32_t>(0x20000000), static_cast<int32_t>(0x1cfa0200),
      static_cast<int32_t>(0xdd0e0300), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0x00001000), static_cast<int32_t>(0xffff1000),
      static_cast<int32_t>(0x00400000), static_cast<int32_t>(0xff9f0000),
      static_cast<int32_t>(0x00a00000), static_cast<int32_t>(0xfbd70000),
      static_cast<int32_t>(0x00e00000), static_cast<int32_t>(0xfff80000),
      static_cast<int32_t>(0x00f90000), static_cast<int32_t>(0xfffa0000),
      static_cast<int32_t>(0x00fb0000), static_cast<int32_t>(0xefff0000),
      static_cast<int32_t>(0x21000000), static_cast<int32_t>(0xff010000),
      static_cast<int32_t>(0x00020000), static_cast<int32_t>(0xff020000),
      static_cast<int32_t>(0xff030000), static_cast<int32_t>(0xff040000),
      static_cast<int32_t>(0xfa070000), static_cast<int32_t>(0x2f000000),
      static_cast<int32_t>(0x3a000000), static_cast<int32_t>(0x40000000),
      static_cast<int32_t>(0x5b000000), static_cast<int32_t>(0x60000000),
      static_cast<int32_t>(0x7b000000), static_cast<int32_t>(0x7e000000),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x80), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xc0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x41), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x5a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x61), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7a), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x08), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x95), static_cast<char>(0x2b),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x0d), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x0a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x1c), static_cast<char>(0xfa),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0xdd),
      static_cast<char>(0x0e), static_cast<char>(0x03), static_cast<char>(0x00),
      static_cast<char>(0x6c), static_cast<char>(0x10), static_cast<char>(0x03),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0xff), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x9f),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xa0), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfb), static_cast<char>(0xd7), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xe0),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0xf8), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xf9), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xfa),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfb), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xef), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x21), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x03), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x04), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0x07),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x2f),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x3a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x5b),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x60), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7b), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x7e),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf32Buf.getUtf32RunesBufferLen(), 54ul);
  ASSERT_EQ(utf32EncRunes, expectRunesBuf);
  ASSERT_EQ(utf32Buf.getUtf32BufferLen(), 216ul);
  ASSERT_EQ(utf32Enc, expectBuf);
};

#endif