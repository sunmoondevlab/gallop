#if 0
#include "charset/translate/utf16.hpp"
#include <gtest/gtest.h>
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet::Translate;

class Utf16EncoderTest : public ::testing::Test {};
TEST(Utf16EncoderTest, EncodeTest) {
  std::string str;
  std::vector<int32_t> utf16EncRunes;
  std::vector<int32_t> expectRunesBuf;
  std::vector<char> utf16Enc;
  std::vector<char> expectBuf;
  // 1 bytes
  str = "09AZaz\t\r\n !/:@[`{~";

  // UTF-16BE without BOM
  Utf16Encoder utf16Buf(str, false, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
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
      static_cast<char>(0x00), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x39), static_cast<char>(0x00), static_cast<char>(0x41),
      static_cast<char>(0x00), static_cast<char>(0x5a), static_cast<char>(0x00),
      static_cast<char>(0x61), static_cast<char>(0x00), static_cast<char>(0x7a),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x0d), static_cast<char>(0x00), static_cast<char>(0x0a),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x21), static_cast<char>(0x00), static_cast<char>(0x2f),
      static_cast<char>(0x00), static_cast<char>(0x3a), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0x00), static_cast<char>(0x5b),
      static_cast<char>(0x00), static_cast<char>(0x60), static_cast<char>(0x00),
      static_cast<char>(0x7b), static_cast<char>(0x00), static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 18ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 36ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE without BOM
  utf16Buf = Utf16Encoder(str, true, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00003000), static_cast<int32_t>(0x00003900),
      static_cast<int32_t>(0x00004100), static_cast<int32_t>(0x00005a00),
      static_cast<int32_t>(0x00006100), static_cast<int32_t>(0x00007a00),
      static_cast<int32_t>(0x00000900), static_cast<int32_t>(0x00000d00),
      static_cast<int32_t>(0x00000a00), static_cast<int32_t>(0x00002000),
      static_cast<int32_t>(0x00002100), static_cast<int32_t>(0x00002f00),
      static_cast<int32_t>(0x00003a00), static_cast<int32_t>(0x00004000),
      static_cast<int32_t>(0x00005b00), static_cast<int32_t>(0x00006000),
      static_cast<int32_t>(0x00007b00), static_cast<int32_t>(0x00007e00),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x41), static_cast<char>(0x00),
      static_cast<char>(0x5a), static_cast<char>(0x00), static_cast<char>(0x61),
      static_cast<char>(0x00), static_cast<char>(0x7a), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x0d),
      static_cast<char>(0x00), static_cast<char>(0x0a), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x21),
      static_cast<char>(0x00), static_cast<char>(0x2f), static_cast<char>(0x00),
      static_cast<char>(0x3a), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x5b), static_cast<char>(0x00),
      static_cast<char>(0x60), static_cast<char>(0x00), static_cast<char>(0x7b),
      static_cast<char>(0x00), static_cast<char>(0x7e), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 18ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 36ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16BE with BOM
  utf16Buf = Utf16Encoder(str, false, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
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
      static_cast<char>(0xfe), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x41), static_cast<char>(0x00),
      static_cast<char>(0x5a), static_cast<char>(0x00), static_cast<char>(0x61),
      static_cast<char>(0x00), static_cast<char>(0x7a), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x0d),
      static_cast<char>(0x00), static_cast<char>(0x0a), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x21),
      static_cast<char>(0x00), static_cast<char>(0x2f), static_cast<char>(0x00),
      static_cast<char>(0x3a), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x5b), static_cast<char>(0x00),
      static_cast<char>(0x60), static_cast<char>(0x00), static_cast<char>(0x7b),
      static_cast<char>(0x00), static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 19ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 38ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE with BOM
  utf16Buf = Utf16Encoder(str, true, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000fffe), static_cast<int32_t>(0x00003000),
      static_cast<int32_t>(0x00003900), static_cast<int32_t>(0x00004100),
      static_cast<int32_t>(0x00005a00), static_cast<int32_t>(0x00006100),
      static_cast<int32_t>(0x00007a00), static_cast<int32_t>(0x00000900),
      static_cast<int32_t>(0x00000d00), static_cast<int32_t>(0x00000a00),
      static_cast<int32_t>(0x00002000), static_cast<int32_t>(0x00002100),
      static_cast<int32_t>(0x00002f00), static_cast<int32_t>(0x00003a00),
      static_cast<int32_t>(0x00004000), static_cast<int32_t>(0x00005b00),
      static_cast<int32_t>(0x00006000), static_cast<int32_t>(0x00007b00),
      static_cast<int32_t>(0x00007e00),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x30),
      static_cast<char>(0x00), static_cast<char>(0x39), static_cast<char>(0x00),
      static_cast<char>(0x41), static_cast<char>(0x00), static_cast<char>(0x5a),
      static_cast<char>(0x00), static_cast<char>(0x61), static_cast<char>(0x00),
      static_cast<char>(0x7a), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x0d), static_cast<char>(0x00),
      static_cast<char>(0x0a), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0x00), static_cast<char>(0x21), static_cast<char>(0x00),
      static_cast<char>(0x2f), static_cast<char>(0x00), static_cast<char>(0x3a),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x5b), static_cast<char>(0x00), static_cast<char>(0x60),
      static_cast<char>(0x00), static_cast<char>(0x7b), static_cast<char>(0x00),
      static_cast<char>(0x7e), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 19ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 38ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // 2 bytes
  str = "ÀÿĀǿȀ˿Ͽӿߺ";

  // UTF-16BE without BOM
  utf16Buf = Utf16Encoder(str, false, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000080), static_cast<int32_t>(0x000000c0),
      static_cast<int32_t>(0x000000ff), static_cast<int32_t>(0x00000100),
      static_cast<int32_t>(0x000001ff), static_cast<int32_t>(0x00000200),
      static_cast<int32_t>(0x000002ff), static_cast<int32_t>(0x000003ff),
      static_cast<int32_t>(0x000004ff), static_cast<int32_t>(0x000007fa),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0xc0), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0xff), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0xff), static_cast<char>(0x03),
      static_cast<char>(0xff), static_cast<char>(0x04), static_cast<char>(0xff),
      static_cast<char>(0x07), static_cast<char>(0xfa),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 10ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 20ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE without BOM
  utf16Buf = Utf16Encoder(str, true, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00008000), static_cast<int32_t>(0x0000c000),
      static_cast<int32_t>(0x0000ff00), static_cast<int32_t>(0x00000001),
      static_cast<int32_t>(0x0000ff01), static_cast<int32_t>(0x00000002),
      static_cast<int32_t>(0x0000ff02), static_cast<int32_t>(0x0000ff03),
      static_cast<int32_t>(0x0000ff04), static_cast<int32_t>(0x0000fa07),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x80), static_cast<char>(0x00), static_cast<char>(0xc0),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0xff),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xff), static_cast<char>(0x02), static_cast<char>(0xff),
      static_cast<char>(0x03), static_cast<char>(0xff), static_cast<char>(0x04),
      static_cast<char>(0xfa), static_cast<char>(0x07),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 10ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 20ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16BE with BOM
  utf16Buf = Utf16Encoder(str, false, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0x00000080),
      static_cast<int32_t>(0x000000c0), static_cast<int32_t>(0x000000ff),
      static_cast<int32_t>(0x00000100), static_cast<int32_t>(0x000001ff),
      static_cast<int32_t>(0x00000200), static_cast<int32_t>(0x000002ff),
      static_cast<int32_t>(0x000003ff), static_cast<int32_t>(0x000004ff),
      static_cast<int32_t>(0x000007fa),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xfe), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x80), static_cast<char>(0x00), static_cast<char>(0xc0),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0xff),
      static_cast<char>(0x02), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xff), static_cast<char>(0x03), static_cast<char>(0xff),
      static_cast<char>(0x04), static_cast<char>(0xff), static_cast<char>(0x07),
      static_cast<char>(0xfa),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 11ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 22ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE without BOM
  utf16Buf = Utf16Encoder(str, true, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000fffe), static_cast<int32_t>(0x00008000),
      static_cast<int32_t>(0x0000c000), static_cast<int32_t>(0x0000ff00),
      static_cast<int32_t>(0x00000001), static_cast<int32_t>(0x0000ff01),
      static_cast<int32_t>(0x00000002), static_cast<int32_t>(0x0000ff02),
      static_cast<int32_t>(0x0000ff03), static_cast<int32_t>(0x0000ff04),
      static_cast<int32_t>(0x0000fa07),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x80),
      static_cast<char>(0x00), static_cast<char>(0xc0), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0xff), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0xff),
      static_cast<char>(0x02), static_cast<char>(0xff), static_cast<char>(0x03),
      static_cast<char>(0xff), static_cast<char>(0x04), static_cast<char>(0xfa),
      static_cast<char>(0x07),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 11ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 22ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // 3 bytes
  str = "ࠀऀကჿ ⮕、䀀鿿ꀀퟻ豈﫿ﬀ￯";

  // UTF-16BE without BOM
  utf16Buf = Utf16Encoder(str, false, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
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
      static_cast<char>(0x08), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0xff), static_cast<char>(0x20),
      static_cast<char>(0x00), static_cast<char>(0x2b), static_cast<char>(0x95),
      static_cast<char>(0x30), static_cast<char>(0x01), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x9f), static_cast<char>(0xff),
      static_cast<char>(0xa0), static_cast<char>(0x00), static_cast<char>(0xd7),
      static_cast<char>(0xfb), static_cast<char>(0xe0), static_cast<char>(0x00),
      static_cast<char>(0xf8), static_cast<char>(0xff), static_cast<char>(0xf9),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0xff),
      static_cast<char>(0xfb), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0xef),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 17ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 34ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE without BOM
  utf16Buf = Utf16Encoder(str, true, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000008), static_cast<int32_t>(0x00000009),
      static_cast<int32_t>(0x00000010), static_cast<int32_t>(0x0000ff10),
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x0000952b),
      static_cast<int32_t>(0x00000130), static_cast<int32_t>(0x00000040),
      static_cast<int32_t>(0x0000ff9f), static_cast<int32_t>(0x000000a0),
      static_cast<int32_t>(0x0000fbd7), static_cast<int32_t>(0x000000e0),
      static_cast<int32_t>(0x0000fff8), static_cast<int32_t>(0x000000f9),
      static_cast<int32_t>(0x0000fffa), static_cast<int32_t>(0x000000fb),
      static_cast<int32_t>(0x0000efff),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0x08), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0xff), static_cast<char>(0x10), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x95), static_cast<char>(0x2b),
      static_cast<char>(0x01), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0xff), static_cast<char>(0x9f),
      static_cast<char>(0x00), static_cast<char>(0xa0), static_cast<char>(0xfb),
      static_cast<char>(0xd7), static_cast<char>(0x00), static_cast<char>(0xe0),
      static_cast<char>(0xff), static_cast<char>(0xf8), static_cast<char>(0x00),
      static_cast<char>(0xf9), static_cast<char>(0xff), static_cast<char>(0xfa),
      static_cast<char>(0x00), static_cast<char>(0xfb), static_cast<char>(0xef),
      static_cast<char>(0xff),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 17ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 34ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16BE with BOM
  utf16Buf = Utf16Encoder(str, false, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
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
      static_cast<char>(0xfe), static_cast<char>(0xff), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0xff), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x2b), static_cast<char>(0x95), static_cast<char>(0x30),
      static_cast<char>(0x01), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x9f), static_cast<char>(0xff), static_cast<char>(0xa0),
      static_cast<char>(0x00), static_cast<char>(0xd7), static_cast<char>(0xfb),
      static_cast<char>(0xe0), static_cast<char>(0x00), static_cast<char>(0xf8),
      static_cast<char>(0xff), static_cast<char>(0xf9), static_cast<char>(0x00),
      static_cast<char>(0xfa), static_cast<char>(0xff), static_cast<char>(0xfb),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xef),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 18ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 36ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE without BOM
  utf16Buf = Utf16Encoder(str, true, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000fffe), static_cast<int32_t>(0x00000008),
      static_cast<int32_t>(0x00000009), static_cast<int32_t>(0x00000010),
      static_cast<int32_t>(0x0000ff10), static_cast<int32_t>(0x00000020),
      static_cast<int32_t>(0x0000952b), static_cast<int32_t>(0x00000130),
      static_cast<int32_t>(0x00000040), static_cast<int32_t>(0x0000ff9f),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x0000fbd7),
      static_cast<int32_t>(0x000000e0), static_cast<int32_t>(0x0000fff8),
      static_cast<int32_t>(0x000000f9), static_cast<int32_t>(0x0000fffa),
      static_cast<int32_t>(0x000000fb), static_cast<int32_t>(0x0000efff),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x00),
      static_cast<char>(0x08), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0xff),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0x95), static_cast<char>(0x2b), static_cast<char>(0x01),
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0xff), static_cast<char>(0x9f), static_cast<char>(0x00),
      static_cast<char>(0xa0), static_cast<char>(0xfb), static_cast<char>(0xd7),
      static_cast<char>(0x00), static_cast<char>(0xe0), static_cast<char>(0xff),
      static_cast<char>(0xf8), static_cast<char>(0x00), static_cast<char>(0xf9),
      static_cast<char>(0xff), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0xfb), static_cast<char>(0xef), static_cast<char>(0xff),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 18ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 36ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // 4 bytes
  str = "𐀀𐃺𠀀鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf";

  // UTF-16BE without BOM
  utf16Buf = Utf16Encoder(str, false, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0xd800dc00), static_cast<int32_t>(0xd800dcfa),
      static_cast<int32_t>(0xd840dc00), static_cast<int32_t>(0xd87ede1c),
      static_cast<int32_t>(0xd883dedd), static_cast<int32_t>(0xd884dc6c),
      static_cast<int32_t>(0xdbc0dc00), static_cast<int32_t>(0xdbffdfff),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xd8), static_cast<char>(0x00), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0xd8), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0xfa), static_cast<char>(0xd8),
      static_cast<char>(0x40), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0xd8), static_cast<char>(0x7e), static_cast<char>(0xde),
      static_cast<char>(0x1c), static_cast<char>(0xd8), static_cast<char>(0x83),
      static_cast<char>(0xde), static_cast<char>(0xdd), static_cast<char>(0xd8),
      static_cast<char>(0x84), static_cast<char>(0xdc), static_cast<char>(0x6c),
      static_cast<char>(0xdb), static_cast<char>(0xc0), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0xdb), static_cast<char>(0xff),
      static_cast<char>(0xdf), static_cast<char>(0xff),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 8ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 32ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE without BOM
  utf16Buf = Utf16Encoder(str, true, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00dc00d8), static_cast<int32_t>(0xfadc00d8),
      static_cast<int32_t>(0x00dc40d8), static_cast<int32_t>(0x1cde7ed8),
      static_cast<int32_t>(0xddde83d8), static_cast<int32_t>(0x6cdc84d8),
      static_cast<int32_t>(0x00dcc0db), static_cast<int32_t>(0xffdfffdb),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x00), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0xd8), static_cast<char>(0xfa), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0xd8), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0x40), static_cast<char>(0xd8),
      static_cast<char>(0x1c), static_cast<char>(0xde), static_cast<char>(0x7e),
      static_cast<char>(0xd8), static_cast<char>(0xdd), static_cast<char>(0xde),
      static_cast<char>(0x83), static_cast<char>(0xd8), static_cast<char>(0x6c),
      static_cast<char>(0xdc), static_cast<char>(0x84), static_cast<char>(0xd8),
      static_cast<char>(0x00), static_cast<char>(0xdc), static_cast<char>(0xc0),
      static_cast<char>(0xdb), static_cast<char>(0xff), static_cast<char>(0xdf),
      static_cast<char>(0xff), static_cast<char>(0xdb),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 8ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 32ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16BE with BOM
  utf16Buf = Utf16Encoder(str, false, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000feff), static_cast<int32_t>(0xd800dc00),
      static_cast<int32_t>(0xd800dcfa), static_cast<int32_t>(0xd840dc00),
      static_cast<int32_t>(0xd87ede1c), static_cast<int32_t>(0xd883dedd),
      static_cast<int32_t>(0xd884dc6c), static_cast<int32_t>(0xdbc0dc00),
      static_cast<int32_t>(0xdbffdfff),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xfe), static_cast<char>(0xff), static_cast<char>(0xd8),
      static_cast<char>(0x00), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0xd8), static_cast<char>(0x00), static_cast<char>(0xdc),
      static_cast<char>(0xfa), static_cast<char>(0xd8), static_cast<char>(0x40),
      static_cast<char>(0xdc), static_cast<char>(0x00), static_cast<char>(0xd8),
      static_cast<char>(0x7e), static_cast<char>(0xde), static_cast<char>(0x1c),
      static_cast<char>(0xd8), static_cast<char>(0x83), static_cast<char>(0xde),
      static_cast<char>(0xdd), static_cast<char>(0xd8), static_cast<char>(0x84),
      static_cast<char>(0xdc), static_cast<char>(0x6c), static_cast<char>(0xdb),
      static_cast<char>(0xc0), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0xdb), static_cast<char>(0xff), static_cast<char>(0xdf),
      static_cast<char>(0xff),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 9ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 34ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE with BOM
  utf16Buf = Utf16Encoder(str, true, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000fffe), static_cast<int32_t>(0x00dc00d8),
      static_cast<int32_t>(0xfadc00d8), static_cast<int32_t>(0x00dc40d8),
      static_cast<int32_t>(0x1cde7ed8), static_cast<int32_t>(0xddde83d8),
      static_cast<int32_t>(0x6cdc84d8), static_cast<int32_t>(0x00dcc0db),
      static_cast<int32_t>(0xffdfffdb),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0x00), static_cast<char>(0xd8),
      static_cast<char>(0xfa), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0xd8), static_cast<char>(0x00), static_cast<char>(0xdc),
      static_cast<char>(0x40), static_cast<char>(0xd8), static_cast<char>(0x1c),
      static_cast<char>(0xde), static_cast<char>(0x7e), static_cast<char>(0xd8),
      static_cast<char>(0xdd), static_cast<char>(0xde), static_cast<char>(0x83),
      static_cast<char>(0xd8), static_cast<char>(0x6c), static_cast<char>(0xdc),
      static_cast<char>(0x84), static_cast<char>(0xd8), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0xc0), static_cast<char>(0xdb),
      static_cast<char>(0xff), static_cast<char>(0xdf), static_cast<char>(0xff),
      static_cast<char>(0xdb),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 9ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 34ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // mix
  str = "09ÀÿĀAZazࠀऀကჿ ⮕、𐀀𐃺𠀀\t\r\n "
        "鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf䀀鿿ꀀퟻ豈﫿"
        "ﬀ"
        "￯"
        "!"
        "ǿȀ˿Ͽӿߺ/"
        ":@[`{~";

  // UTF-16BE without BOM
  utf16Buf = Utf16Encoder(str, false, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00000030), static_cast<int32_t>(0x00000039),
      static_cast<int32_t>(0x00000080), static_cast<int32_t>(0x000000c0),
      static_cast<int32_t>(0x000000ff), static_cast<int32_t>(0x00000100),
      static_cast<int32_t>(0x00000041), static_cast<int32_t>(0x0000005a),
      static_cast<int32_t>(0x00000061), static_cast<int32_t>(0x0000007a),
      static_cast<int32_t>(0x00000800), static_cast<int32_t>(0x00000900),
      static_cast<int32_t>(0x00001000), static_cast<int32_t>(0x000010ff),
      static_cast<int32_t>(0x00002000), static_cast<int32_t>(0x00002b95),
      static_cast<int32_t>(0x00003001), static_cast<int32_t>(0xd800dc00),
      static_cast<int32_t>(0xd800dcfa), static_cast<int32_t>(0xd840dc00),
      static_cast<int32_t>(0x00000009), static_cast<int32_t>(0x0000000d),
      static_cast<int32_t>(0x0000000a), static_cast<int32_t>(0x00000020),
      static_cast<int32_t>(0xd87ede1c), static_cast<int32_t>(0xd883dedd),
      static_cast<int32_t>(0xd884dc6c), static_cast<int32_t>(0xdbc0dc00),
      static_cast<int32_t>(0xdbffdfff), static_cast<int32_t>(0x00004000),
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
      static_cast<char>(0x00), static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x39), static_cast<char>(0x00), static_cast<char>(0x80),
      static_cast<char>(0x00), static_cast<char>(0xc0), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x41), static_cast<char>(0x00),
      static_cast<char>(0x5a), static_cast<char>(0x00), static_cast<char>(0x61),
      static_cast<char>(0x00), static_cast<char>(0x7a), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0xff), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x2b), static_cast<char>(0x95), static_cast<char>(0x30),
      static_cast<char>(0x01), static_cast<char>(0xd8), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0x00), static_cast<char>(0xd8),
      static_cast<char>(0x00), static_cast<char>(0xdc), static_cast<char>(0xfa),
      static_cast<char>(0xd8), static_cast<char>(0x40), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x0d), static_cast<char>(0x00),
      static_cast<char>(0x0a), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0xd8), static_cast<char>(0x7e), static_cast<char>(0xde),
      static_cast<char>(0x1c), static_cast<char>(0xd8), static_cast<char>(0x83),
      static_cast<char>(0xde), static_cast<char>(0xdd), static_cast<char>(0xd8),
      static_cast<char>(0x84), static_cast<char>(0xdc), static_cast<char>(0x6c),
      static_cast<char>(0xdb), static_cast<char>(0xc0), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0xdb), static_cast<char>(0xff),
      static_cast<char>(0xdf), static_cast<char>(0xff), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x9f), static_cast<char>(0xff),
      static_cast<char>(0xa0), static_cast<char>(0x00), static_cast<char>(0xd7),
      static_cast<char>(0xfb), static_cast<char>(0xe0), static_cast<char>(0x00),
      static_cast<char>(0xf8), static_cast<char>(0xff), static_cast<char>(0xf9),
      static_cast<char>(0x00), static_cast<char>(0xfa), static_cast<char>(0xff),
      static_cast<char>(0xfb), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0xef), static_cast<char>(0x00), static_cast<char>(0x21),
      static_cast<char>(0x01), static_cast<char>(0xff), static_cast<char>(0x02),
      static_cast<char>(0x00), static_cast<char>(0x02), static_cast<char>(0xff),
      static_cast<char>(0x03), static_cast<char>(0xff), static_cast<char>(0x04),
      static_cast<char>(0xff), static_cast<char>(0x07), static_cast<char>(0xfa),
      static_cast<char>(0x00), static_cast<char>(0x2f), static_cast<char>(0x00),
      static_cast<char>(0x3a), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0x00), static_cast<char>(0x5b), static_cast<char>(0x00),
      static_cast<char>(0x60), static_cast<char>(0x00), static_cast<char>(0x7b),
      static_cast<char>(0x00), static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 53ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 122ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE without BOM
  utf16Buf = Utf16Encoder(str, true, false);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x00003000), static_cast<int32_t>(0x00003900),
      static_cast<int32_t>(0x00008000), static_cast<int32_t>(0x0000c000),
      static_cast<int32_t>(0x0000ff00), static_cast<int32_t>(0x00000001),
      static_cast<int32_t>(0x00004100), static_cast<int32_t>(0x00005a00),
      static_cast<int32_t>(0x00006100), static_cast<int32_t>(0x00007a00),
      static_cast<int32_t>(0x00000008), static_cast<int32_t>(0x00000009),
      static_cast<int32_t>(0x00000010), static_cast<int32_t>(0x0000ff10),
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0x0000952b),
      static_cast<int32_t>(0x00000130), static_cast<int32_t>(0x00dc00d8),
      static_cast<int32_t>(0xfadc00d8), static_cast<int32_t>(0x00dc40d8),
      static_cast<int32_t>(0x00000900), static_cast<int32_t>(0x00000d00),
      static_cast<int32_t>(0x00000a00), static_cast<int32_t>(0x00002000),
      static_cast<int32_t>(0x1cde7ed8), static_cast<int32_t>(0xddde83d8),
      static_cast<int32_t>(0x6cdc84d8), static_cast<int32_t>(0x00dcc0db),
      static_cast<int32_t>(0xffdfffdb), static_cast<int32_t>(0x00000040),
      static_cast<int32_t>(0x0000ff9f), static_cast<int32_t>(0x000000a0),
      static_cast<int32_t>(0x0000fbd7), static_cast<int32_t>(0x000000e0),
      static_cast<int32_t>(0x0000fff8), static_cast<int32_t>(0x000000f9),
      static_cast<int32_t>(0x0000fffa), static_cast<int32_t>(0x000000fb),
      static_cast<int32_t>(0x0000efff), static_cast<int32_t>(0x00002100),
      static_cast<int32_t>(0x0000ff01), static_cast<int32_t>(0x00000002),
      static_cast<int32_t>(0x0000ff02), static_cast<int32_t>(0x0000ff03),
      static_cast<int32_t>(0x0000ff04), static_cast<int32_t>(0x0000fa07),
      static_cast<int32_t>(0x00002f00), static_cast<int32_t>(0x00003a00),
      static_cast<int32_t>(0x00004000), static_cast<int32_t>(0x00005b00),
      static_cast<int32_t>(0x00006000), static_cast<int32_t>(0x00007b00),
      static_cast<int32_t>(0x00007e00),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0xc0), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x41), static_cast<char>(0x00), static_cast<char>(0x5a),
      static_cast<char>(0x00), static_cast<char>(0x61), static_cast<char>(0x00),
      static_cast<char>(0x7a), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x08), static_cast<char>(0x00), static_cast<char>(0x09),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0xff),
      static_cast<char>(0x10), static_cast<char>(0x00), static_cast<char>(0x20),
      static_cast<char>(0x95), static_cast<char>(0x2b), static_cast<char>(0x01),
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0xd8), static_cast<char>(0xfa),
      static_cast<char>(0xdc), static_cast<char>(0x00), static_cast<char>(0xd8),
      static_cast<char>(0x00), static_cast<char>(0xdc), static_cast<char>(0x40),
      static_cast<char>(0xd8), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x0d), static_cast<char>(0x00), static_cast<char>(0x0a),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x1c), static_cast<char>(0xde), static_cast<char>(0x7e),
      static_cast<char>(0xd8), static_cast<char>(0xdd), static_cast<char>(0xde),
      static_cast<char>(0x83), static_cast<char>(0xd8), static_cast<char>(0x6c),
      static_cast<char>(0xdc), static_cast<char>(0x84), static_cast<char>(0xd8),
      static_cast<char>(0x00), static_cast<char>(0xdc), static_cast<char>(0xc0),
      static_cast<char>(0xdb), static_cast<char>(0xff), static_cast<char>(0xdf),
      static_cast<char>(0xff), static_cast<char>(0xdb), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0xff), static_cast<char>(0x9f),
      static_cast<char>(0x00), static_cast<char>(0xa0), static_cast<char>(0xfb),
      static_cast<char>(0xd7), static_cast<char>(0x00), static_cast<char>(0xe0),
      static_cast<char>(0xff), static_cast<char>(0xf8), static_cast<char>(0x00),
      static_cast<char>(0xf9), static_cast<char>(0xff), static_cast<char>(0xfa),
      static_cast<char>(0x00), static_cast<char>(0xfb), static_cast<char>(0xef),
      static_cast<char>(0xff), static_cast<char>(0x21), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0xff), static_cast<char>(0x02),
      static_cast<char>(0xff), static_cast<char>(0x03), static_cast<char>(0xff),
      static_cast<char>(0x04), static_cast<char>(0xfa), static_cast<char>(0x07),
      static_cast<char>(0x2f), static_cast<char>(0x00), static_cast<char>(0x3a),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x5b), static_cast<char>(0x00), static_cast<char>(0x60),
      static_cast<char>(0x00), static_cast<char>(0x7b), static_cast<char>(0x00),
      static_cast<char>(0x7e), static_cast<char>(0x00),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 53ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 122ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16BE with BOM
  utf16Buf = Utf16Encoder(str, false, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
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
      static_cast<int32_t>(0xd800dc00), static_cast<int32_t>(0xd800dcfa),
      static_cast<int32_t>(0xd840dc00), static_cast<int32_t>(0x00000009),
      static_cast<int32_t>(0x0000000d), static_cast<int32_t>(0x0000000a),
      static_cast<int32_t>(0x00000020), static_cast<int32_t>(0xd87ede1c),
      static_cast<int32_t>(0xd883dedd), static_cast<int32_t>(0xd884dc6c),
      static_cast<int32_t>(0xdbc0dc00), static_cast<int32_t>(0xdbffdfff),
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
      static_cast<char>(0xfe), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x30), static_cast<char>(0x00), static_cast<char>(0x39),
      static_cast<char>(0x00), static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0xc0), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x41), static_cast<char>(0x00), static_cast<char>(0x5a),
      static_cast<char>(0x00), static_cast<char>(0x61), static_cast<char>(0x00),
      static_cast<char>(0x7a), static_cast<char>(0x08), static_cast<char>(0x00),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x10), static_cast<char>(0xff),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x2b),
      static_cast<char>(0x95), static_cast<char>(0x30), static_cast<char>(0x01),
      static_cast<char>(0xd8), static_cast<char>(0x00), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0xd8), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0xfa), static_cast<char>(0xd8),
      static_cast<char>(0x40), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x0d), static_cast<char>(0x00), static_cast<char>(0x0a),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0xd8),
      static_cast<char>(0x7e), static_cast<char>(0xde), static_cast<char>(0x1c),
      static_cast<char>(0xd8), static_cast<char>(0x83), static_cast<char>(0xde),
      static_cast<char>(0xdd), static_cast<char>(0xd8), static_cast<char>(0x84),
      static_cast<char>(0xdc), static_cast<char>(0x6c), static_cast<char>(0xdb),
      static_cast<char>(0xc0), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0xdb), static_cast<char>(0xff), static_cast<char>(0xdf),
      static_cast<char>(0xff), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x9f), static_cast<char>(0xff), static_cast<char>(0xa0),
      static_cast<char>(0x00), static_cast<char>(0xd7), static_cast<char>(0xfb),
      static_cast<char>(0xe0), static_cast<char>(0x00), static_cast<char>(0xf8),
      static_cast<char>(0xff), static_cast<char>(0xf9), static_cast<char>(0x00),
      static_cast<char>(0xfa), static_cast<char>(0xff), static_cast<char>(0xfb),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0xef),
      static_cast<char>(0x00), static_cast<char>(0x21), static_cast<char>(0x01),
      static_cast<char>(0xff), static_cast<char>(0x02), static_cast<char>(0x00),
      static_cast<char>(0x02), static_cast<char>(0xff), static_cast<char>(0x03),
      static_cast<char>(0xff), static_cast<char>(0x04), static_cast<char>(0xff),
      static_cast<char>(0x07), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0x2f), static_cast<char>(0x00), static_cast<char>(0x3a),
      static_cast<char>(0x00), static_cast<char>(0x40), static_cast<char>(0x00),
      static_cast<char>(0x5b), static_cast<char>(0x00), static_cast<char>(0x60),
      static_cast<char>(0x00), static_cast<char>(0x7b), static_cast<char>(0x00),
      static_cast<char>(0x7e),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 54ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 124ul);
  ASSERT_EQ(utf16Enc, expectBuf);

  // UTF-16LE with BOM
  utf16Buf = Utf16Encoder(str, true, true);
  utf16Enc = utf16Buf.getUtf16Buffer();
  utf16EncRunes = utf16Buf.getUtf16RunesBuffer();
  expectRunesBuf = std::vector<int32_t>{
      static_cast<int32_t>(0x0000fffe), static_cast<int32_t>(0x00003000),
      static_cast<int32_t>(0x00003900), static_cast<int32_t>(0x00008000),
      static_cast<int32_t>(0x0000c000), static_cast<int32_t>(0x0000ff00),
      static_cast<int32_t>(0x00000001), static_cast<int32_t>(0x00004100),
      static_cast<int32_t>(0x00005a00), static_cast<int32_t>(0x00006100),
      static_cast<int32_t>(0x00007a00), static_cast<int32_t>(0x00000008),
      static_cast<int32_t>(0x00000009), static_cast<int32_t>(0x00000010),
      static_cast<int32_t>(0x0000ff10), static_cast<int32_t>(0x00000020),
      static_cast<int32_t>(0x0000952b), static_cast<int32_t>(0x00000130),
      static_cast<int32_t>(0x00dc00d8), static_cast<int32_t>(0xfadc00d8),
      static_cast<int32_t>(0x00dc40d8), static_cast<int32_t>(0x00000900),
      static_cast<int32_t>(0x00000d00), static_cast<int32_t>(0x00000a00),
      static_cast<int32_t>(0x00002000), static_cast<int32_t>(0x1cde7ed8),
      static_cast<int32_t>(0xddde83d8), static_cast<int32_t>(0x6cdc84d8),
      static_cast<int32_t>(0x00dcc0db), static_cast<int32_t>(0xffdfffdb),
      static_cast<int32_t>(0x00000040), static_cast<int32_t>(0x0000ff9f),
      static_cast<int32_t>(0x000000a0), static_cast<int32_t>(0x0000fbd7),
      static_cast<int32_t>(0x000000e0), static_cast<int32_t>(0x0000fff8),
      static_cast<int32_t>(0x000000f9), static_cast<int32_t>(0x0000fffa),
      static_cast<int32_t>(0x000000fb), static_cast<int32_t>(0x0000efff),
      static_cast<int32_t>(0x00002100), static_cast<int32_t>(0x0000ff01),
      static_cast<int32_t>(0x00000002), static_cast<int32_t>(0x0000ff02),
      static_cast<int32_t>(0x0000ff03), static_cast<int32_t>(0x0000ff04),
      static_cast<int32_t>(0x0000fa07), static_cast<int32_t>(0x00002f00),
      static_cast<int32_t>(0x00003a00), static_cast<int32_t>(0x00004000),
      static_cast<int32_t>(0x00005b00), static_cast<int32_t>(0x00006000),
      static_cast<int32_t>(0x00007b00), static_cast<int32_t>(0x00007e00),
  };
  expectBuf = std::vector<char>{
      static_cast<char>(0xff), static_cast<char>(0xfe), static_cast<char>(0x30),
      static_cast<char>(0x00), static_cast<char>(0x39), static_cast<char>(0x00),
      static_cast<char>(0x80), static_cast<char>(0x00), static_cast<char>(0xc0),
      static_cast<char>(0x00), static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x01), static_cast<char>(0x41),
      static_cast<char>(0x00), static_cast<char>(0x5a), static_cast<char>(0x00),
      static_cast<char>(0x61), static_cast<char>(0x00), static_cast<char>(0x7a),
      static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0xff), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x95),
      static_cast<char>(0x2b), static_cast<char>(0x01), static_cast<char>(0x30),
      static_cast<char>(0x00), static_cast<char>(0xdc), static_cast<char>(0x00),
      static_cast<char>(0xd8), static_cast<char>(0xfa), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0xd8), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0x40), static_cast<char>(0xd8),
      static_cast<char>(0x09), static_cast<char>(0x00), static_cast<char>(0x0d),
      static_cast<char>(0x00), static_cast<char>(0x0a), static_cast<char>(0x00),
      static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x1c),
      static_cast<char>(0xde), static_cast<char>(0x7e), static_cast<char>(0xd8),
      static_cast<char>(0xdd), static_cast<char>(0xde), static_cast<char>(0x83),
      static_cast<char>(0xd8), static_cast<char>(0x6c), static_cast<char>(0xdc),
      static_cast<char>(0x84), static_cast<char>(0xd8), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0xc0), static_cast<char>(0xdb),
      static_cast<char>(0xff), static_cast<char>(0xdf), static_cast<char>(0xff),
      static_cast<char>(0xdb), static_cast<char>(0x00), static_cast<char>(0x40),
      static_cast<char>(0xff), static_cast<char>(0x9f), static_cast<char>(0x00),
      static_cast<char>(0xa0), static_cast<char>(0xfb), static_cast<char>(0xd7),
      static_cast<char>(0x00), static_cast<char>(0xe0), static_cast<char>(0xff),
      static_cast<char>(0xf8), static_cast<char>(0x00), static_cast<char>(0xf9),
      static_cast<char>(0xff), static_cast<char>(0xfa), static_cast<char>(0x00),
      static_cast<char>(0xfb), static_cast<char>(0xef), static_cast<char>(0xff),
      static_cast<char>(0x21), static_cast<char>(0x00), static_cast<char>(0xff),
      static_cast<char>(0x01), static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xff), static_cast<char>(0x02), static_cast<char>(0xff),
      static_cast<char>(0x03), static_cast<char>(0xff), static_cast<char>(0x04),
      static_cast<char>(0xfa), static_cast<char>(0x07), static_cast<char>(0x2f),
      static_cast<char>(0x00), static_cast<char>(0x3a), static_cast<char>(0x00),
      static_cast<char>(0x40), static_cast<char>(0x00), static_cast<char>(0x5b),
      static_cast<char>(0x00), static_cast<char>(0x60), static_cast<char>(0x00),
      static_cast<char>(0x7b), static_cast<char>(0x00), static_cast<char>(0x7e),
      static_cast<char>(0x00),
  };
  ASSERT_EQ(utf16Buf.getUtf16RunesBufferLen(), 54ul);
  ASSERT_EQ(utf16EncRunes, expectRunesBuf);
  ASSERT_EQ(utf16Buf.getUtf16BufferLen(), 124ul);
  ASSERT_EQ(utf16Enc, expectBuf);
};

#endif