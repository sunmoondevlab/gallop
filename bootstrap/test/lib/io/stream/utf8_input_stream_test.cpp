// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf8_input_stream.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;

class Utf8InputStreamTest : public ::testing::Test {};
TEST_F(Utf8InputStreamTest, String) {
  std::string str = "";
  Utf8InputStream uis(str);

  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);

  str = "1234567890";

  uis = Utf8InputStream(str);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 10);
  ASSERT_EQ(uis.read(), '1');
  ASSERT_EQ(uis.read(), '2');
  ASSERT_EQ(uis.current(), '3');
  ASSERT_EQ(uis.readable(), 8);
  ASSERT_EQ(uis.undo(), '2');
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(), '3');
  ASSERT_EQ(uis.ahead(1), '4');
  ASSERT_EQ(uis.ahead(7), '0');
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(8), '\0');
  uis.rewind();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 10);
  uis.rewind(3);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 10);
  uis.skip();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 9);
  uis.skip(3);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 6);
  uis.markCurrent();
  uis.skip(3);
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), '5');
  uis.markAt(4);
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), '5');
  ASSERT_EQ(uis.current(), '6');
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), '1');
  uis.markAt(11);
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), '0');
};

TEST_F(Utf8InputStreamTest, Vector) {
  std::vector<char> buf;
  Utf8InputStream uis(buf);

  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);

  std::string str = "\xef"
                    "\xbb"
                    "\xbf"
                    "1234567890";
  uis = Utf8InputStream(std::vector<char>(str.begin(), str.end()));
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 13);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x000000ef));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x000000bb));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x000000bf));
  ASSERT_EQ(uis.read(), '1');
  ASSERT_EQ(uis.read(), '2');
  ASSERT_EQ(uis.readable(), 8);
  ASSERT_EQ(uis.undo(), '2');
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(), '3');
  ASSERT_EQ(uis.ahead(1), '4');
  ASSERT_EQ(uis.ahead(7), '0');
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(8), '\0');
  uis.rewind();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 13);
  uis.rewind(3);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 13);
  uis.skip();
  uis.skip();
  uis.skip();
  uis.skip();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 9);
  uis.skip(3);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 6);
  uis.markCurrent();
  uis.skip(3);
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), '5');
  uis.markAt(4);
  uis.rewindToMark();
  ASSERT_EQ(uis.currentPos(), 4ul);
  ASSERT_EQ(uis.read(), '2');
  ASSERT_EQ(uis.currentPos(), 5ul);
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x000000ef));
  uis.markAt(15);
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), '0');
};

TEST_F(Utf8InputStreamTest, Utf8String) {
  std::vector<char> buf = {
      /*BOM start*/ static_cast<char>(0xef), static_cast<char>(0xbb),
      static_cast<char>(0xbf), /*BOM end*/
  };
  Utf8InputStream uis(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 3);
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00efbbbf));
  std::string str = "\xef"
                    "\xbb"
                    "\xbf"
                    "0Aa\t\nÀÿĀǿ䀀鿿ꀀퟻ豈𐃺𠀀鼻𰻝𱁬";
  uis = Utf8InputStream(std::vector<char>(str.begin(), str.end()));
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 53);
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00efbbbf));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00000030));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00000041));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00000061));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00000009));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x0000000a));
  ASSERT_EQ(uis.readByte2(), static_cast<int32_t>(0x0000c280));
  ASSERT_EQ(uis.readByte2(), static_cast<int32_t>(0x0000c380));
  ASSERT_EQ(uis.readByte2(), static_cast<int32_t>(0x0000c3bf));
  ASSERT_EQ(uis.readByte2(), static_cast<int32_t>(0x0000c480));
  ASSERT_EQ(uis.readByte2(), static_cast<int32_t>(0x0000c7bf));
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00e48080));
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00e9bfbf));
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00ea8080));
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00ed9fbb));
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00efa480));
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xf09083ba));
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xf0a08080));
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xf0afa89c));
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xf0b0bb9d));
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xf0b181ac));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00000000));
  ASSERT_EQ(uis.readByte2(), static_cast<int32_t>(0x00000000));
  ASSERT_EQ(uis.readByte3(), static_cast<int32_t>(0x00000000));
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0x00000000));
};
