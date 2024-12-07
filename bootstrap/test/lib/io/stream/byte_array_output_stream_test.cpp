// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/byte_array_output_stream.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;

class ByteArrayOutputStreamTest : public ::testing::Test {};
TEST_F(ByteArrayOutputStreamTest, Vector) {
  ByteArrayOutputStream baos;
  // 4byte
  baos.write(static_cast<int32_t>(0x11223344));
  baos.write(static_cast<int32_t>(0x11223344), true);
  // 2byte
  baos.write(static_cast<int16_t>(0x5566));
  baos.write(static_cast<int16_t>(0x5566), true);
  // 1byte
  baos.write(static_cast<char>(0x77));
  std::vector<char> expectByteArray{
      static_cast<char>(0x11), static_cast<char>(0x22),
      static_cast<char>(0x33), static_cast<char>(0x44), //
      static_cast<char>(0x44), static_cast<char>(0x33),
      static_cast<char>(0x22), static_cast<char>(0x11), //
      static_cast<char>(0x55), static_cast<char>(0x66), //
      static_cast<char>(0x66), static_cast<char>(0x55), //
      static_cast<char>(0x77),                          //
  };
  std::vector<int16_t> expectByte2Array{
      static_cast<int16_t>(0x1122), //
      static_cast<int16_t>(0x3344), //
      static_cast<int16_t>(0x4433), //
      static_cast<int16_t>(0x2211), //
      static_cast<int16_t>(0x5566), //
      static_cast<int16_t>(0x6655), //
      static_cast<int16_t>(0x7700), //
  };
  std::vector<int32_t> expectByte4Array{
      static_cast<int32_t>(0x11223344), //
      static_cast<int32_t>(0x44332211), //
      static_cast<int32_t>(0x55666655), //
      static_cast<int32_t>(0x77000000), //
  };
  ASSERT_EQ(baos.data(), expectByteArray);
  ASSERT_EQ(baos.dataByte2(), expectByte2Array);
  ASSERT_EQ(baos.dataByte4(), expectByte4Array);
  baos.reset();
  expectByteArray = {};
  ASSERT_EQ(baos.data(), expectByteArray);
  baos = ByteArrayOutputStream();
  ASSERT_EQ(baos.data(), expectByteArray);
  // 4byte vector
  baos.write(std::vector<int32_t>{static_cast<int32_t>(0x11223344),
                                  static_cast<int32_t>(0x55667788)});
  baos.write(std::vector<int32_t>{static_cast<int32_t>(0x11223344),
                                  static_cast<int32_t>(0x55667788)},
             true);
  // 2byte vector
  baos.write(std::vector<int16_t>{static_cast<int16_t>(0x99aa),
                                  static_cast<int16_t>(0xbbcc)});
  baos.write(std::vector<int16_t>{static_cast<int16_t>(0x99aa),
                                  static_cast<int16_t>(0xbbcc)},
             true);
  // 1byte vector
  baos.write(
      std::vector<char>{static_cast<char>(0xdd), static_cast<char>(0xee)});
  expectByteArray = {
      static_cast<char>(0x11), static_cast<char>(0x22),
      static_cast<char>(0x33), static_cast<char>(0x44), //
      static_cast<char>(0x55), static_cast<char>(0x66),
      static_cast<char>(0x77), static_cast<char>(0x88), //
      static_cast<char>(0x44), static_cast<char>(0x33),
      static_cast<char>(0x22), static_cast<char>(0x11), //
      static_cast<char>(0x88), static_cast<char>(0x77),
      static_cast<char>(0x66), static_cast<char>(0x55), //
      static_cast<char>(0x99), static_cast<char>(0xaa), //
      static_cast<char>(0xbb), static_cast<char>(0xcc), //
      static_cast<char>(0xaa), static_cast<char>(0x99), //
      static_cast<char>(0xcc), static_cast<char>(0xbb), //
      static_cast<char>(0xdd),                          //
      static_cast<char>(0xee),                          //
  };
  expectByte2Array = {
      static_cast<int16_t>(0x1122), //
      static_cast<int16_t>(0x3344), //
      static_cast<int16_t>(0x5566), //
      static_cast<int16_t>(0x7788), //
      static_cast<int16_t>(0x4433), //
      static_cast<int16_t>(0x2211), //
      static_cast<int16_t>(0x8877), //
      static_cast<int16_t>(0x6655), //
      static_cast<int16_t>(0x99aa), //
      static_cast<int16_t>(0xbbcc), //
      static_cast<int16_t>(0xaa99), //
      static_cast<int16_t>(0xccbb), //
      static_cast<int16_t>(0xddee), //
  };
  expectByte4Array = {
      static_cast<int32_t>(0x11223344), //
      static_cast<int32_t>(0x55667788), //
      static_cast<int32_t>(0x44332211), //
      static_cast<int32_t>(0x88776655), //
      static_cast<int32_t>(0x99aabbcc), //
      static_cast<int32_t>(0xaa99ccbb), //
      static_cast<int32_t>(0xddee0000), //
  };
  ASSERT_EQ(baos.data(), expectByteArray);
  ASSERT_EQ(baos.dataByte2(), expectByte2Array);
  ASSERT_EQ(baos.dataByte4(), expectByte4Array);
};
