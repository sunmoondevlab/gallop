// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf32_input_stream.hpp"
#include <gtest/gtest.h>

namespace gallop::IO::Stream {

class Utf32InputStreamTest : public ::testing::Test {};
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
  std::vector<int32_t> expectChunk{static_cast<int32_t>(0x00000020),
                                   static_cast<int32_t>(0x00000030),
                                   static_cast<int32_t>(0x00000041)};
  ASSERT_EQ(uis.readChunk(3), expectChunk);
  ASSERT_EQ(uis.readable(), 38);
  ASSERT_EQ(uis.readChunk(3, true), expectChunk);
  ASSERT_EQ(uis.readable(), 35);
  uis.markAt(34);
  uis.rewindToMark();
  ASSERT_EQ(uis.current(), static_cast<int32_t>(0x00010001));
  expectChunk = {
      static_cast<int32_t>(0x00010001), static_cast<int32_t>(0x0001f9ff),
      static_cast<int32_t>(0x0002fa1c), static_cast<int32_t>(0x0003106c),
      static_cast<int32_t>(0x0010ffff), static_cast<int32_t>(0x00110000),
  };
  ASSERT_EQ(uis.readChunk(7, true), expectChunk);
  ASSERT_EQ(uis.current(), static_cast<int32_t>(0));
  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);
  ASSERT_EQ(uis.read(), '\0');
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
  expectChunk = {static_cast<int32_t>(0x20000000),
                 static_cast<int32_t>(0x30000000),
                 static_cast<int32_t>(0x41000000)};
  ASSERT_EQ(uis.readChunk(3), expectChunk);
  ASSERT_EQ(uis.readable(), 38);
  ASSERT_EQ(uis.readChunk(3, true), expectChunk);
  ASSERT_EQ(uis.readable(), 35);
  uis.markAt(34);
  uis.rewindToMark();
  ASSERT_EQ(uis.current(), static_cast<int32_t>(0x01000100));
  expectChunk = {
      static_cast<int32_t>(0x01000100), static_cast<int32_t>(0xfff90100),
      static_cast<int32_t>(0x1cfa0200), static_cast<int32_t>(0x6c100300),
      static_cast<int32_t>(0xffff1000), static_cast<int32_t>(0x00001100),
  };
  ASSERT_EQ(uis.readChunk(7, true), expectChunk);
  ASSERT_EQ(uis.current(), static_cast<int32_t>(0));
  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);
  ASSERT_EQ(uis.read(), '\0');
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

} // namespace gallop::IO::Stream