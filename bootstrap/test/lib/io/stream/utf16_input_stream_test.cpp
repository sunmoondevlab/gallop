// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf16_input_stream.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"

using namespace gallop::IO::Stream;

class Utf16InputStreamTest : public ::testing::Test {};
TEST_F(Utf16InputStreamTest, String) {
  std::u16string str = u"";
  Utf16InputStream uis(str);

  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);

  str = u"1234567890";

  uis = Utf16InputStream(str);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 10);
  ASSERT_EQ(uis.read(), static_cast<int16_t>(u'1'));
  ASSERT_EQ(uis.read(), static_cast<int16_t>(u'2'));
  ASSERT_EQ(uis.current(), static_cast<int16_t>(u'3'));
  ASSERT_EQ(uis.readable(), 8);
  ASSERT_EQ(uis.undo(), static_cast<int16_t>(u'2'));
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(), static_cast<int16_t>(u'3'));
  ASSERT_EQ(uis.ahead(1), static_cast<int16_t>(u'4'));
  ASSERT_EQ(uis.ahead(7), static_cast<int16_t>(u'0'));
  ASSERT_EQ(uis.readable(), 9);
  ASSERT_EQ(uis.ahead(16), static_cast<int16_t>(u'\0'));
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
  ASSERT_EQ(uis.read(), static_cast<int16_t>(u'5'));
  uis.markAt(4);
  uis.rewindToMark();
  ASSERT_EQ(uis.currentPos(), 4ul);
  ASSERT_EQ(uis.read(), static_cast<int16_t>(u'5'));
  ASSERT_EQ(uis.currentPos(), 5ul);
  ASSERT_EQ(uis.current(), static_cast<int16_t>(u'6'));
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int16_t>(u'1'));
  uis.markAt(11);
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int16_t>(u'0'));
};

TEST_F(Utf16InputStreamTest, ByteVector) {
  std::vector<char> buf;
  Utf16InputStream uis(buf);

  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);

  // 1 byte
  buf = {
      static_cast<char>(0xfe),
  };
  uis = Utf16InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 1);
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0xfe00));

  // BE BOM
  buf = {
      static_cast<char>(0xfe),
      static_cast<char>(0xff),
  };
  uis = Utf16InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 1);
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0xfeff));
  // LE BOM
  buf = {
      static_cast<char>(0xff),
      static_cast<char>(0xfe),
  };
  uis = Utf16InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 1);
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0xfffe));

  // BE
  buf = {
      static_cast<char>(0xfe),
      static_cast<char>(0xff), // BOM
      static_cast<char>(0x00),
      static_cast<char>(0x09), //
      static_cast<char>(0x00),
      static_cast<char>(0x20), //
      static_cast<char>(0x00),
      static_cast<char>(0x30), //
      static_cast<char>(0x00),
      static_cast<char>(0x41), // 4
      static_cast<char>(0x00),
      static_cast<char>(0x61), //
      static_cast<char>(0x00),
      static_cast<char>(0x7e), //
      static_cast<char>(0x00),
      static_cast<char>(0x80), //
      static_cast<char>(0x00),
      static_cast<char>(0x81), //
      static_cast<char>(0x00),
      static_cast<char>(0xa0), // 9
      static_cast<char>(0x00),
      static_cast<char>(0xa1), //
      static_cast<char>(0x00),
      static_cast<char>(0xff), //
      static_cast<char>(0x01),
      static_cast<char>(0x00), //
      static_cast<char>(0x01),
      static_cast<char>(0x00), //
      static_cast<char>(0x00),
      static_cast<char>(0x80), // 14
      static_cast<char>(0x00),
      static_cast<char>(0x81), //
      static_cast<char>(0x00),
      static_cast<char>(0xa0), //
      static_cast<char>(0x00),
      static_cast<char>(0xa1), //
      static_cast<char>(0x00),
      static_cast<char>(0xff), //
      static_cast<char>(0x01),
      static_cast<char>(0x00), // 19
      static_cast<char>(0x07),
      static_cast<char>(0xfa), //
      static_cast<char>(0x08),
      static_cast<char>(0x00), //
      static_cast<char>(0x08),
      static_cast<char>(0x01), //
      static_cast<char>(0x10),
      static_cast<char>(0x00), //
      static_cast<char>(0xd7),
      static_cast<char>(0xfb), // 24
      static_cast<char>(0xd8),
      static_cast<char>(0x00), //
      static_cast<char>(0xdf),
      static_cast<char>(0xff), //
      static_cast<char>(0xf9),
      static_cast<char>(0x00), //
      static_cast<char>(0xff),
      static_cast<char>(0xfd), //
      static_cast<char>(0xd7),
      static_cast<char>(0xff), // 29
      static_cast<char>(0xdc),
      static_cast<char>(0x00), //
      static_cast<char>(0xd8),
      static_cast<char>(0x00), //
      static_cast<char>(0xdb),
      static_cast<char>(0xff), //
      static_cast<char>(0xd8),
      static_cast<char>(0x00), //
      static_cast<char>(0xdc),
      static_cast<char>(0x00), // 34
      static_cast<char>(0xd8),
      static_cast<char>(0x00), //
      static_cast<char>(0xdc),
      static_cast<char>(0x01), //
      static_cast<char>(0xd8),
      static_cast<char>(0x3e), //
      static_cast<char>(0xdd),
      static_cast<char>(0xff), //
      static_cast<char>(0xd8),
      static_cast<char>(0x7e), // 39
      static_cast<char>(0xde),
      static_cast<char>(0x1c), //
      static_cast<char>(0xdb),
      static_cast<char>(0xff), //
      static_cast<char>(0xdf),
      static_cast<char>(0xff), //
      static_cast<char>(0xdc),
      static_cast<char>(0x00), //
      static_cast<char>(0xdf),
      static_cast<char>(0xff), // 44
      static_cast<char>(0xdb),
      static_cast<char>(0xff), //
      static_cast<char>(0xe0),
      static_cast<char>(0x00), //
  };
  uis = Utf16InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 47);
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0xfeff));
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0x0009));
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0x0020));
  ASSERT_EQ(uis.readable(), 44);
  ASSERT_EQ(uis.undo(), static_cast<int16_t>(0x0020));
  ASSERT_EQ(uis.readable(), 45);
  ASSERT_EQ(uis.ahead(), static_cast<int16_t>(0x0030));
  ASSERT_EQ(uis.ahead(1), static_cast<int16_t>(0x0041));
  ASSERT_EQ(uis.ahead(43), static_cast<int16_t>(0xe000));
  ASSERT_EQ(uis.ahead(44), static_cast<int16_t>(0));
  uis.skip();
  uis.skip();
  uis.skip();
  ASSERT_EQ(uis.readable(), 42);
  uis.markAt(41);
  uis.rewindToMark();
  ASSERT_EQ(uis.current(), static_cast<int16_t>(0xdbff));
  uis.rewind();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 47);
  uis.rewind(30);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 47);
  uis.skip(46);
  uis.rewind(16);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 17);
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xdc00d800));
  uis.markCurrent();
  uis.skip();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 14);
  uis.skip();
  uis.rewindToMark();
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xdbffd800));
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0xfeff));

  // LE
  buf = {
      static_cast<char>(0xff),
      static_cast<char>(0xfe), // BOM
      static_cast<char>(0x09),
      static_cast<char>(0x00), //
      static_cast<char>(0x20),
      static_cast<char>(0x00), //
      static_cast<char>(0x30),
      static_cast<char>(0x00), //
      static_cast<char>(0x41),
      static_cast<char>(0x00), // 4
      static_cast<char>(0x61),
      static_cast<char>(0x00), //
      static_cast<char>(0x7e),
      static_cast<char>(0x00), //
      static_cast<char>(0x80),
      static_cast<char>(0x00), //
      static_cast<char>(0x81),
      static_cast<char>(0x00), //
      static_cast<char>(0xa0),
      static_cast<char>(0x00), // 9
      static_cast<char>(0xa1),
      static_cast<char>(0x00), //
      static_cast<char>(0xff),
      static_cast<char>(0x00), //
      static_cast<char>(0x00),
      static_cast<char>(0x01), //
      static_cast<char>(0x00),
      static_cast<char>(0x01), //
      static_cast<char>(0x80),
      static_cast<char>(0x00), // 14
      static_cast<char>(0x81),
      static_cast<char>(0x00), //
      static_cast<char>(0xa0),
      static_cast<char>(0x00), //
      static_cast<char>(0xa1),
      static_cast<char>(0x00), //
      static_cast<char>(0xff),
      static_cast<char>(0x00), //
      static_cast<char>(0x00),
      static_cast<char>(0x01), // 19
      static_cast<char>(0xfa),
      static_cast<char>(0x07), //
      static_cast<char>(0x00),
      static_cast<char>(0x08), //
      static_cast<char>(0x01),
      static_cast<char>(0x08), //
      static_cast<char>(0x00),
      static_cast<char>(0x10), //
      static_cast<char>(0xfb),
      static_cast<char>(0xd7), // 24
      static_cast<char>(0x00),
      static_cast<char>(0xd8), //
      static_cast<char>(0xff),
      static_cast<char>(0xdf), //
      static_cast<char>(0x00),
      static_cast<char>(0xf9), //
      static_cast<char>(0xfd),
      static_cast<char>(0xff), //
      static_cast<char>(0xff),
      static_cast<char>(0xd7), // 29
      static_cast<char>(0x00),
      static_cast<char>(0xdc), //
      static_cast<char>(0x00),
      static_cast<char>(0xd8), //
      static_cast<char>(0xff),
      static_cast<char>(0xdb), //
      static_cast<char>(0x00),
      static_cast<char>(0xd8), //
      static_cast<char>(0x00),
      static_cast<char>(0xdc), // 34
      static_cast<char>(0x00),
      static_cast<char>(0xd8), //
      static_cast<char>(0x01),
      static_cast<char>(0xdc), //
      static_cast<char>(0x3e),
      static_cast<char>(0xd8), //
      static_cast<char>(0xff),
      static_cast<char>(0xdd), //
      static_cast<char>(0x7e),
      static_cast<char>(0xd8), // 39
      static_cast<char>(0x1c),
      static_cast<char>(0xde), //
      static_cast<char>(0xff),
      static_cast<char>(0xdb), //
      static_cast<char>(0xff),
      static_cast<char>(0xdf), //
      static_cast<char>(0x00),
      static_cast<char>(0xdc), //
      static_cast<char>(0xff),
      static_cast<char>(0xdf), // 44
      static_cast<char>(0xff),
      static_cast<char>(0xdb), //
      static_cast<char>(0x00),
      static_cast<char>(0xe0), //
  };
  uis = Utf16InputStream(buf);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 47);
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0xfffe));
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0x0900));
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0x2000));
  ASSERT_EQ(uis.readable(), 44);
  ASSERT_EQ(uis.undo(), static_cast<int16_t>(0x2000));
  ASSERT_EQ(uis.readable(), 45);
  ASSERT_EQ(uis.ahead(), static_cast<int16_t>(0x3000));
  ASSERT_EQ(uis.ahead(1), static_cast<int16_t>(0x4100));
  ASSERT_EQ(uis.ahead(43), static_cast<int16_t>(0x00e0));
  ASSERT_EQ(uis.ahead(44), static_cast<int16_t>(0));
  uis.skip(3);
  ASSERT_EQ(uis.readable(), 42);
  uis.markAt(41);
  uis.rewind();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 47);
  uis.rewind(30);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 47);
  uis.skip(46);
  uis.rewind(16);
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 17);
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0x00dc00d8));
  uis.markCurrent();
  uis.skip();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 14);
  uis.skip();
  uis.rewindToMark();
  ASSERT_EQ(uis.readByte4(), static_cast<int32_t>(0xffdb00d8));
  uis.resetMark();
  uis.rewindToMark();
  ASSERT_EQ(uis.read(), static_cast<int16_t>(0xfffe));
};
