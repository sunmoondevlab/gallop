// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/byte_array_input_stream.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;

class ByteArrayInputStreamTest : public ::testing::Test {};
TEST_F(ByteArrayInputStreamTest, String) {
  std::string str = "";
  ByteArrayInputStream bais(str);

  ASSERT_EQ(bais.hasReadable(), false);
  ASSERT_EQ(bais.readable(), 0);

  str = "1234567890";

  bais = ByteArrayInputStream(str);
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 10);
  ASSERT_EQ(bais.read(), '1');
  ASSERT_EQ(bais.read(), '2');
  ASSERT_EQ(bais.current(), '3');
  ASSERT_EQ(bais.readable(), 8);
  ASSERT_EQ(bais.undo(), '2');
  ASSERT_EQ(bais.readable(), 9);
  ASSERT_EQ(bais.ahead(), '3');
  ASSERT_EQ(bais.ahead(1), '4');
  ASSERT_EQ(bais.ahead(7), '0');
  ASSERT_EQ(bais.readable(), 9);
  ASSERT_EQ(bais.ahead(8), '\0');
  std::vector<char> expectChunk{'2', '3', '4'};
  ASSERT_EQ(bais.readChunk(3), expectChunk);
  ASSERT_EQ(bais.readable(), 9);
  ASSERT_EQ(bais.readChunk(3, true), expectChunk);
  ASSERT_EQ(bais.readable(), 6);
  expectChunk = {'5', '6', '7', '8', '9', '0'};
  ASSERT_EQ(bais.readChunk(7, true), expectChunk);
  ASSERT_EQ(bais.hasReadable(), false);
  ASSERT_EQ(bais.readable(), 0);
  ASSERT_EQ(bais.read(), '\0');
  bais.rewind();
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 10);
  bais.rewind(3);
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 10);
  bais.skip();
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 9);
  bais.skip(3);
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 6);
  bais.markCurrent();
  bais.skip(3);
  bais.rewindToMark();
  ASSERT_EQ(bais.read(), '5');
  bais.markAt(4);
  bais.rewindToMark();
  ASSERT_EQ(bais.currentPos(), 4ul);
  ASSERT_EQ(bais.read(), '5');
  ASSERT_EQ(bais.currentPos(), 5ul);
  ASSERT_EQ(bais.current(), '6');
  bais.resetMark();
  bais.rewindToMark();
  ASSERT_EQ(bais.read(), '1');
  bais.markAt(11);
  bais.rewindToMark();
  ASSERT_EQ(bais.read(), '0');
};

TEST_F(ByteArrayInputStreamTest, Vector) {
  std::vector<char> buf;
  ByteArrayInputStream bais(buf);

  ASSERT_EQ(bais.hasReadable(), false);
  ASSERT_EQ(bais.readable(), 0);

  std::string str = "\xef"
                    "\xbb"
                    "\xbf"
                    "1234567890";
  bais = ByteArrayInputStream(std::vector<char>(str.begin(), str.end()));
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 13);
  ASSERT_EQ(bais.read(), static_cast<char>(0xef));
  ASSERT_EQ(bais.read(), static_cast<char>(0xbb));
  ASSERT_EQ(bais.read(), static_cast<char>(0xbf));
  ASSERT_EQ(bais.read(), '1');
  ASSERT_EQ(bais.read(), '2');
  ASSERT_EQ(bais.readable(), 8);
  ASSERT_EQ(bais.undo(), '2');
  ASSERT_EQ(bais.readable(), 9);
  ASSERT_EQ(bais.ahead(), '3');
  ASSERT_EQ(bais.ahead(1), '4');
  ASSERT_EQ(bais.ahead(7), '0');
  ASSERT_EQ(bais.readable(), 9);
  ASSERT_EQ(bais.ahead(8), '\0');
  std::vector<char> expectChunk{'2', '3', '4'};
  ASSERT_EQ(bais.readChunk(3), expectChunk);
  ASSERT_EQ(bais.readable(), 9);
  ASSERT_EQ(bais.readChunk(3, true), expectChunk);
  ASSERT_EQ(bais.readable(), 6);
  expectChunk = {'5', '6', '7', '8', '9', '0'};
  ASSERT_EQ(bais.readChunk(7, true), expectChunk);
  ASSERT_EQ(bais.hasReadable(), false);
  ASSERT_EQ(bais.readable(), 0);
  ASSERT_EQ(bais.read(), '\0');
  bais.rewind();
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 13);
  bais.rewind(3);
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 13);
  expectChunk = {
      static_cast<char>(0xef),
      static_cast<char>(0xbb),
      static_cast<char>(0xbf),
  };
  ASSERT_EQ(bais.readChunk(3, true), expectChunk);
  bais.skip();
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 9);
  bais.skip(3);
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 6);
  bais.markCurrent();
  bais.skip(3);
  bais.rewindToMark();
  ASSERT_EQ(bais.read(), '5');
  bais.markAt(4);
  bais.rewindToMark();
  ASSERT_EQ(bais.read(), '2');
  bais.resetMark();
  bais.rewindToMark();
  ASSERT_EQ(bais.read(), static_cast<char>(0xef));
  bais.markAt(15);
  bais.rewindToMark();
  ASSERT_EQ(bais.read(), '0');
};

TEST_F(ByteArrayInputStreamTest, Utf8String) {
  std::vector<char> buf = {
      /*BOM start*/ static_cast<char>(0xef), static_cast<char>(0xbb),
      static_cast<char>(0xbf), /*BOM end*/
  };
  ByteArrayInputStream bais(buf);
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 3);
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0x00efbbbf));
  std::string str = "\xef"
                    "\xbb"
                    "\xbf"
                    "0Aa\t\nÀÿĀǿ䀀鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬";
  bais = ByteArrayInputStream(std::vector<char>(str.begin(), str.end()));
  ASSERT_EQ(bais.hasReadable(), true);
  ASSERT_EQ(bais.readable(), 53);
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0x00efbbbf));
  ASSERT_EQ(bais.read(), static_cast<char>(0x30));
  ASSERT_EQ(bais.read(), static_cast<char>(0x41));
  ASSERT_EQ(bais.read(), static_cast<char>(0x61));
  ASSERT_EQ(bais.read(), static_cast<char>(0x09));
  ASSERT_EQ(bais.read(), static_cast<char>(0x0a));
  ASSERT_EQ(bais.readByte2(), static_cast<int16_t>(0xc280));
  ASSERT_EQ(bais.readByte2(), static_cast<int16_t>(0xc380));
  ASSERT_EQ(bais.readByte2(), static_cast<int16_t>(0xc3bf));
  ASSERT_EQ(bais.readByte2(), static_cast<int16_t>(0xc480));
  ASSERT_EQ(bais.readByte2(), static_cast<int16_t>(0xc7bf));
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0xe48080));
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0xe9bfbf));
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0xea8080));
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0xed9fbb));
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0xefa480));
  ASSERT_EQ(bais.readByte4(), static_cast<int32_t>(0xf09083ba));
  ASSERT_EQ(bais.readByte4(), static_cast<int32_t>(0xf0a08080));
  ASSERT_EQ(bais.readByte4(), static_cast<int32_t>(0xf0afa89c));
  ASSERT_EQ(bais.readByte4(), static_cast<int32_t>(0xf0b0bb9d));
  ASSERT_EQ(bais.readByte4(), static_cast<int32_t>(0xf0b181ac));
  ASSERT_EQ(bais.read(), static_cast<char>(0x0));
  ASSERT_EQ(bais.readByte2(), static_cast<int16_t>(0x0));
  ASSERT_EQ(bais.readByte3(), static_cast<int32_t>(0x0));
  ASSERT_EQ(bais.readByte4(), static_cast<int32_t>(0x0));
};
