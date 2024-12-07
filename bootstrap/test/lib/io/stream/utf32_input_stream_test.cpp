// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf32_input_stream.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"

using namespace gallop::IO::Stream;

class Utf32InputStreamTest : public ::testing::Test {};
TEST_F(Utf32InputStreamTest, String) {
  std::u32string str = U"";
  Utf32InputStream uis(str);

  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);

  str = U"1234567890";

  uis = Utf32InputStream(str);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 10);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(U'1'));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(U'2'));
  ASSERT_EQ(uis.current(), static_cast<int32_t>(U'3'));
  ASSERT_EQ(uis.readable(), 8);
  ASSERT_EQ(uis.undo(), static_cast<int32_t>(U'2'));
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(), static_cast<int32_t>(U'3'));
  ASSERT_EQ(uis.ahead(1), static_cast<int32_t>(U'4'));
  ASSERT_EQ(uis.ahead(7), static_cast<int32_t>(U'0'));
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(32), static_cast<int32_t>(U'\0'));
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
  ASSERT_EQ(uis.read(), static_cast<int32_t>(U'5'));
  uis.markAt(4);
  uis.rewindToMark();
  ASSERT_EQ(uis.currentPos(), 4ul);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(U'5'));
  ASSERT_EQ(uis.currentPos(), 5ul);
  ASSERT_EQ(uis.current(), static_cast<int32_t>(U'6'));
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int32_t>(U'1'));
  uis.markAt(11);
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int32_t>(U'0'));
};

TEST_F(Utf32InputStreamTest, ByteVector) {
  std::vector<char> buf;
  Utf32InputStream uis(buf);

  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);

  // 1 byte
  buf = {
      static_cast<char>(0xfe),
  };
  uis = Utf32InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 1);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0xfe000000));

  // BE BOM
  buf = {
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      static_cast<char>(0xfe),
      static_cast<char>(0xff),
  };
  uis = Utf32InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 1);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x0000feff));
  // LE BOM
  buf = {
      static_cast<char>(0xff),
      static_cast<char>(0xfe),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
  };
  uis = Utf32InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 1);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0xfffe0000));

  // BE
  buf = {
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xfe), static_cast<char>(0xff), // BOM
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x09), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x20), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x30), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x41), // 4
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x61), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x7e), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x80), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x81), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xa0), // 9
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xa1), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x80), // 14
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x81), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xa0), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xa1), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0xff), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), // 19
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x07), static_cast<char>(0xfa), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x08), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x08), static_cast<char>(0x01), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x10), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xd7), static_cast<char>(0xfb), // 24
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xd8), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xdf), static_cast<char>(0xff), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xf9), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xff), static_cast<char>(0xfd), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xd7), static_cast<char>(0xff), // 29
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xdc), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xd8), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0xdb), static_cast<char>(0xff), //
      static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x01), // 34
      static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0xf9), static_cast<char>(0xff), //
      static_cast<char>(0x00), static_cast<char>(0x02),
      static_cast<char>(0xfa), static_cast<char>(0x1c), //
      static_cast<char>(0x00), static_cast<char>(0x03),
      static_cast<char>(0x10), static_cast<char>(0x6c), //
      static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0xff), static_cast<char>(0xff), //
      static_cast<char>(0x00), static_cast<char>(0x11),
      static_cast<char>(0x00), static_cast<char>(0x00), // 39
  };
  uis = Utf32InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 40);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x0000feff));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00000009));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00000020));
  ASSERT_EQ(uis.readable(), 37);
  ASSERT_EQ(uis.undo(), static_cast<int32_t>(0x00000020));
  ASSERT_EQ(uis.readable(), 38);
  ASSERT_EQ(uis.ahead(), static_cast<int32_t>(0x00000030));
  ASSERT_EQ(uis.ahead(1), static_cast<int32_t>(0x00000041));
  ASSERT_EQ(uis.ahead(36), static_cast<int32_t>(0x00110000));
  ASSERT_EQ(uis.ahead(37), static_cast<int32_t>(0));
  uis.skip();
  uis.skip();
  uis.skip();
  ASSERT_EQ(uis.readable(), 35);
  uis.markAt(34);
  uis.rewindToMark();
  ASSERT_EQ(uis.current(), static_cast<int32_t>(0x00010001));
  uis.resetMark();
  uis.rewind();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 40);
  uis.rewind(30);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 40);
  uis.skip(39);
  uis.rewind(16);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 17);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00001000));
  uis.markCurrent();
  uis.skip();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 15);
  uis.skip();
  uis.rewindToMark();
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x0000feff));

  // LE
  buf = {
      static_cast<char>(0xff), static_cast<char>(0xfe),
      static_cast<char>(0x00), static_cast<char>(0x00), // BOM
      static_cast<char>(0x09), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x20), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x30), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x41), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), // 4
      static_cast<char>(0x61), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x7e), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x81), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xa0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), // 9
      static_cast<char>(0xa1), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), // 14
      static_cast<char>(0x81), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xa0), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xa1), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xff), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x01),
      static_cast<char>(0x00), static_cast<char>(0x00), // 19
      static_cast<char>(0xfa), static_cast<char>(0x07),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x01), static_cast<char>(0x08),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x10),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xfb), static_cast<char>(0xd7),
      static_cast<char>(0x00), static_cast<char>(0x00), // 24
      static_cast<char>(0x00), static_cast<char>(0xd8),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xff), static_cast<char>(0xdf),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0xf9),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xfd), static_cast<char>(0xff),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xff), static_cast<char>(0xd7),
      static_cast<char>(0x00), static_cast<char>(0x00), // 29
      static_cast<char>(0x00), static_cast<char>(0xdc),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0xd8),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0xff), static_cast<char>(0xdb),
      static_cast<char>(0x00), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), //
      static_cast<char>(0x01), static_cast<char>(0x00),
      static_cast<char>(0x01), static_cast<char>(0x00), // 34
      static_cast<char>(0xff), static_cast<char>(0xf9),
      static_cast<char>(0x01), static_cast<char>(0x00), //
      static_cast<char>(0x1c), static_cast<char>(0xfa),
      static_cast<char>(0x02), static_cast<char>(0x00), //
      static_cast<char>(0x6c), static_cast<char>(0x10),
      static_cast<char>(0x03), static_cast<char>(0x00), //
      static_cast<char>(0xff), static_cast<char>(0xff),
      static_cast<char>(0x10), static_cast<char>(0x00), //
      static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x11), static_cast<char>(0x00), // 39
  };
  uis = Utf32InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 40);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0xfffe0000));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x09000000));
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x20000000));
  ASSERT_EQ(uis.readable(), 37);
  ASSERT_EQ(uis.undo(), static_cast<int32_t>(0x20000000));
  ASSERT_EQ(uis.readable(), 38);
  ASSERT_EQ(uis.ahead(), static_cast<int32_t>(0x30000000));
  ASSERT_EQ(uis.ahead(1), static_cast<int32_t>(0x41000000));
  ASSERT_EQ(uis.ahead(36), static_cast<int32_t>(0x00001100));
  ASSERT_EQ(uis.ahead(37), static_cast<int32_t>(0));
  uis.skip(3);
  uis.markAt(34);
  uis.rewindToMark();
  ASSERT_EQ(uis.current(), static_cast<int32_t>(0x01000100));
  uis.rewind();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 40);
  uis.rewind(30);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 40);
  uis.skip(39);
  uis.rewind(16);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 17);
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0x00100000));
  uis.markCurrent();
  uis.skip();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 15);
  uis.skip();
  uis.rewindToMark();
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int32_t>(0xfffe0000));
};
