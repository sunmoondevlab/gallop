// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "util/hexstringer/hexstringer.hpp"
#include <gtest/gtest.h>

using namespace gallop::Util;

class HexStringerTest : public ::testing::Test {};

TEST_F(HexStringerTest, DumpCharChar) {
  ASSERT_EQ(HexStringer::dumpChar(static_cast<char>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<char>('\n')), "0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<char>('\r')), "0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<char>(' ')), "20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<char>('0')), "30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<char>('a')), "61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<char>('~')), "7e");

  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>(0), true), "00");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>('\n'), true), "0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>('\n')), "0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>('\r')), "0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>(' ')), "20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>('0')), "30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>('a')), "61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint8_t>('~')), "7e");
};

TEST_F(HexStringerTest, DumpCharShort) {
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>(0), true), "00 00");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>(0), true, true), "0000");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>('\n')), "00 0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>('\r')), "00 0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>(' ')), "00 20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>('0')), "00 30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>('a')), "00 61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>('~')), "00 7e");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int16_t>(0xfffe)), "ff fe");

  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>(0), true), "00 00");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>(0), true, true),
            "0000");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>('\n')), "00 0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>('\r')), "00 0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>(' ')), "00 20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>('0')), "00 30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>('a')), "00 61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>('~')), "00 7e");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint16_t>(0xfffe)), "ff fe");
};

TEST_F(HexStringerTest, DumpCharInt) {
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>(0), true),
            "00 00 00 00");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>(0), true, true),
            "00000000");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>('\n')), "00 00 00 0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>('\r')), "00 00 00 0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>(' ')), "00 00 00 20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>('0')), "00 00 00 30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>('a')), "00 00 00 61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>('~')), "00 00 00 7e");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int32_t>(0xfffefdfc)),
            "ff fe fd fc");

  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>(0), true),
            "00 00 00 00");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>(0), true, true),
            "00000000");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>('\n')), "00 00 00 0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>('\r')), "00 00 00 0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>(' ')), "00 00 00 20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>('0')), "00 00 00 30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>('a')), "00 00 00 61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>('~')), "00 00 00 7e");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint32_t>(0xfffefdfc)),
            "ff fe fd fc");
};

TEST_F(HexStringerTest, DumpCharLong) {
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>('\n')),
            "00 00 00 00 00 00 00 0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>('\r')),
            "00 00 00 00 00 00 00 0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>(' ')),
            "00 00 00 00 00 00 00 20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>('0')),
            "00 00 00 00 00 00 00 30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>('a')),
            "00 00 00 00 00 00 00 61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>('~')),
            "00 00 00 00 00 00 00 7e");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<int64_t>(0xfffefdfcfbfaf9f8)),
            "ff fe fd fc fb fa f9 f8");

  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>(0)), "");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>('\n')),
            "00 00 00 00 00 00 00 0a");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>('\r')),
            "00 00 00 00 00 00 00 0d");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>(' ')),
            "00 00 00 00 00 00 00 20");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>('0')),
            "00 00 00 00 00 00 00 30");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>('a')),
            "00 00 00 00 00 00 00 61");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>('~')),
            "00 00 00 00 00 00 00 7e");
  ASSERT_EQ(HexStringer::dumpChar(static_cast<uint64_t>(0xfffefdfcfbfaf9f8)),
            "ff fe fd fc fb fa f9 f8");
};

TEST_F(HexStringerTest, DumpString) {
  ASSERT_EQ(HexStringer::dumpString(std::string("\n")), "0a");
  ASSERT_EQ(HexStringer::dumpString(std::string("\r")), "0d");
  ASSERT_EQ(HexStringer::dumpString(std::string(" ")), "20");
  ASSERT_EQ(HexStringer::dumpString(std::string("0")), "30");
  ASSERT_EQ(HexStringer::dumpString(std::string("a")), "61");
  ASSERT_EQ(HexStringer::dumpString(std::string("~")), "7e");
  ASSERT_EQ(HexStringer::dumpString(std::string("abcdef")),
            "61 62 63 64 65 66");
  ASSERT_EQ(HexStringer::dumpString(std::string("abcdefghij")),
            "61 62 63 64 65 66 67 68\n69 6a");

  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{0x0a}), "0a");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{0x0d}), "0d");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{0x20}), "20");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{0x30}), "30");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{0x61}), "61");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{0x7e}), "7e");
  ASSERT_EQ(HexStringer::dumpString(
                std::vector<char>{0x61, 0x62, 0x63, 0x64, 0x65, 0x66}),
            "61 62 63 64 65 66");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{
                0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a}),
            "61 62 63 64 65 66 67 68\n69 6a");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{
                static_cast<char>(0xff),
                static_cast<char>(0xfe),
                0x61,
                0x62,
                0x63,
                0x64,
                0x65,
                0x66,
                0x67,
                0x68,
                0x69,
                0x6a,
                static_cast<char>(0xff),
                static_cast<char>(0x00),
                static_cast<char>(0xfe),
                static_cast<char>(0x00),
            }),
            "ff fe 61 62 63 64 65 66\n67 68 69 6a ff 00 fe 00");
  ASSERT_EQ(HexStringer::dumpString(std::vector<char>{
                0x00,
                0x00,
                static_cast<char>(0xfe),
                static_cast<char>(0xff),
                0x61,
                0x62,
                0x63,
                0x64,
                0x65,
                0x66,
                0x67,
                0x68,
                0x69,
                0x6a,
                static_cast<char>(0xff),
                static_cast<char>(0x00),
                static_cast<char>(0xfe),
                static_cast<char>(0x00),
            }),
            "00 00 fe ff 61 62 63 64\n65 66 67 68 69 6a ff 00\nfe 00");
};

TEST_F(HexStringerTest, CodeGenCharVector) {
  ASSERT_EQ(HexStringer::codeGenVector(std::string("\n")),
            "std::vector<char>{static_cast<char>(0x0a),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::string("\r")),
            "std::vector<char>{static_cast<char>(0x0d),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::string(" ")),
            "std::vector<char>{static_cast<char>(0x20),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::string("0")),
            "std::vector<char>{static_cast<char>(0x30),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::string("a")),
            "std::vector<char>{static_cast<char>(0x61),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::string("~")),
            "std::vector<char>{static_cast<char>(0x7e),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::string("abcdef")),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::string("abcdefghij")),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66), "
      "static_cast<char>(0x67), static_cast<char>(0x68), "
      "static_cast<char>(0x69), static_cast<char>(0x6a),}");

  ASSERT_EQ(HexStringer::codeGenVector(std::vector<char>{0x0a}),
            "std::vector<char>{static_cast<char>(0x0a),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<char>{0x0d}),
            "std::vector<char>{static_cast<char>(0x0d),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<char>{0x20}),
            "std::vector<char>{static_cast<char>(0x20),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<char>{0x30}),
            "std::vector<char>{static_cast<char>(0x30),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<char>{0x61}),
            "std::vector<char>{static_cast<char>(0x61),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<char>{0x7e}),
            "std::vector<char>{static_cast<char>(0x7e),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(
          std::vector<char>{0x61, 0x62, 0x63, 0x64, 0x65, 0x66}),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::vector<char>{
          0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a}),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66), "
      "static_cast<char>(0x67), static_cast<char>(0x68), "
      "static_cast<char>(0x69), static_cast<char>(0x6a),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::vector<char>{
          static_cast<char>(0xff),
          static_cast<char>(0xfe),
          0x61,
          0x62,
          0x63,
          0x64,
          0x65,
          0x66,
          0x67,
          0x68,
          0x69,
          0x6a,
          static_cast<char>(0xff),
          static_cast<char>(0x00),
          static_cast<char>(0xfe),
          static_cast<char>(0x00),
      }),
      "std::vector<char>{static_cast<char>(0xff), static_cast<char>(0xfe), "
      "static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66), "
      "static_cast<char>(0x67), static_cast<char>(0x68), "
      "static_cast<char>(0x69), static_cast<char>(0x6a), "
      "static_cast<char>(0xff), static_cast<char>(0x00), "
      "static_cast<char>(0xfe), static_cast<char>(0x00),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::vector<char>{
          0x00,
          0x00,
          static_cast<char>(0xfe),
          static_cast<char>(0xff),
          0x61,
          0x62,
          0x63,
          0x64,
          0x65,
          0x66,
          0x67,
          0x68,
          0x69,
          0x6a,
          static_cast<char>(0xff),
          static_cast<char>(0x00),
          static_cast<char>(0xfe),
          static_cast<char>(0x00),
      }),
      "std::vector<char>{static_cast<char>(0x00), static_cast<char>(0x00), "
      "static_cast<char>(0xfe), static_cast<char>(0xff), "
      "static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66), "
      "static_cast<char>(0x67), static_cast<char>(0x68), "
      "static_cast<char>(0x69), static_cast<char>(0x6a), "
      "static_cast<char>(0xff), static_cast<char>(0x00), "
      "static_cast<char>(0xfe), static_cast<char>(0x00),}");
};
TEST_F(HexStringerTest, CodeGenU16Vector) {
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u"\n")),
            "std::vector<int16_t>{static_cast<int16_t>(0x000a),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u"\r")),
            "std::vector<int16_t>{static_cast<int16_t>(0x000d),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u" ")),
            "std::vector<int16_t>{static_cast<int16_t>(0x0020),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u"0")),
            "std::vector<int16_t>{static_cast<int16_t>(0x0030),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u"a")),
            "std::vector<int16_t>{static_cast<int16_t>(0x0061),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u"~")),
            "std::vector<int16_t>{static_cast<int16_t>(0x007e),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u"abcdef")),
            "std::vector<int16_t>{static_cast<int16_t>(0x0061), "
            "static_cast<int16_t>(0x0062), "
            "static_cast<int16_t>(0x0063), static_cast<int16_t>(0x0064), "
            "static_cast<int16_t>(0x0065), static_cast<int16_t>(0x0066),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u16string(u"abcdefghij")),
            "std::vector<int16_t>{static_cast<int16_t>(0x0061), "
            "static_cast<int16_t>(0x0062), "
            "static_cast<int16_t>(0x0063), static_cast<int16_t>(0x0064), "
            "static_cast<int16_t>(0x0065), static_cast<int16_t>(0x0066), "
            "static_cast<int16_t>(0x0067), static_cast<int16_t>(0x0068), "
            "static_cast<int16_t>(0x0069), static_cast<int16_t>(0x006a),}");

  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{0x000a}),
            "std::vector<int16_t>{static_cast<int16_t>(0x000a),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{0x000d}),
            "std::vector<int16_t>{static_cast<int16_t>(0x000d),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{0x0020}),
            "std::vector<int16_t>{static_cast<int16_t>(0x0020),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{0x0030}),
            "std::vector<int16_t>{static_cast<int16_t>(0x0030),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{0x0061}),
            "std::vector<int16_t>{static_cast<int16_t>(0x0061),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{0x007e}),
            "std::vector<int16_t>{static_cast<int16_t>(0x007e),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{
                0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066}),
            "std::vector<int16_t>{static_cast<int16_t>(0x0061), "
            "static_cast<int16_t>(0x0062), "
            "static_cast<int16_t>(0x0063), static_cast<int16_t>(0x0064), "
            "static_cast<int16_t>(0x0065), static_cast<int16_t>(0x0066),}");
  ASSERT_EQ(HexStringer::codeGenVector(
                std::vector<int16_t>{0x0061, 0x0062, 0x0063, 0x0064, 0x0065,
                                     0x0066, 0x0067, 0x0068, 0x0069, 0x006a}),
            "std::vector<int16_t>{static_cast<int16_t>(0x0061), "
            "static_cast<int16_t>(0x0062), "
            "static_cast<int16_t>(0x0063), static_cast<int16_t>(0x0064), "
            "static_cast<int16_t>(0x0065), static_cast<int16_t>(0x0066), "
            "static_cast<int16_t>(0x0067), static_cast<int16_t>(0x0068), "
            "static_cast<int16_t>(0x0069), static_cast<int16_t>(0x006a),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{
                static_cast<int16_t>(0x00ff),
                static_cast<int16_t>(0x00fe),
                0x0061,
                0x0062,
                0x0063,
                0x0064,
                0x0065,
                0x0066,
                0x0067,
                0x0068,
                0x0069,
                0x006a,
                static_cast<int16_t>(0x00ff),
                static_cast<int16_t>(0x0000),
                static_cast<int16_t>(0x00fe),
                static_cast<int16_t>(0x0000),
            }),
            "std::vector<int16_t>{static_cast<int16_t>(0x00ff), "
            "static_cast<int16_t>(0x00fe), "
            "static_cast<int16_t>(0x0061), static_cast<int16_t>(0x0062), "
            "static_cast<int16_t>(0x0063), static_cast<int16_t>(0x0064), "
            "static_cast<int16_t>(0x0065), static_cast<int16_t>(0x0066), "
            "static_cast<int16_t>(0x0067), static_cast<int16_t>(0x0068), "
            "static_cast<int16_t>(0x0069), static_cast<int16_t>(0x006a), "
            "static_cast<int16_t>(0x00ff), static_cast<int16_t>(0x0000), "
            "static_cast<int16_t>(0x00fe), static_cast<int16_t>(0x0000),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int16_t>{
                0x0000,
                0x0000,
                static_cast<int16_t>(0x00fe),
                static_cast<int16_t>(0x00ff),
                0x0061,
                0x0062,
                0x0063,
                0x0064,
                0x0065,
                0x0066,
                0x0067,
                0x0068,
                0x0069,
                0x006a,
                static_cast<int16_t>(0x00ff),
                static_cast<int16_t>(0x0000),
                static_cast<int16_t>(0x00fe),
                static_cast<int16_t>(0x0000),
            }),
            "std::vector<int16_t>{static_cast<int16_t>(0x0000), "
            "static_cast<int16_t>(0x0000), "
            "static_cast<int16_t>(0x00fe), static_cast<int16_t>(0x00ff), "
            "static_cast<int16_t>(0x0061), static_cast<int16_t>(0x0062), "
            "static_cast<int16_t>(0x0063), static_cast<int16_t>(0x0064), "
            "static_cast<int16_t>(0x0065), static_cast<int16_t>(0x0066), "
            "static_cast<int16_t>(0x0067), static_cast<int16_t>(0x0068), "
            "static_cast<int16_t>(0x0069), static_cast<int16_t>(0x006a), "
            "static_cast<int16_t>(0x00ff), static_cast<int16_t>(0x0000), "
            "static_cast<int16_t>(0x00fe), static_cast<int16_t>(0x0000),}");
};
TEST_F(HexStringerTest, CodeGenU32Vector) {
  ASSERT_EQ(HexStringer::codeGenVector(std::u32string(U"\n")),
            "std::vector<int32_t>{static_cast<int32_t>(0x0000000a),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u32string(U"\r")),
            "std::vector<int32_t>{static_cast<int32_t>(0x0000000d),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u32string(U" ")),
            "std::vector<int32_t>{static_cast<int32_t>(0x00000020),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u32string(U"0")),
            "std::vector<int32_t>{static_cast<int32_t>(0x00000030),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u32string(U"a")),
            "std::vector<int32_t>{static_cast<int32_t>(0x00000061),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::u32string(U"~")),
            "std::vector<int32_t>{static_cast<int32_t>(0x0000007e),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::u32string(U"abcdef")),
      "std::vector<int32_t>{static_cast<int32_t>(0x00000061), "
      "static_cast<int32_t>(0x00000062), "
      "static_cast<int32_t>(0x00000063), static_cast<int32_t>(0x00000064), "
      "static_cast<int32_t>(0x00000065), static_cast<int32_t>(0x00000066),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::u32string(U"abcdefghij")),
      "std::vector<int32_t>{static_cast<int32_t>(0x00000061), "
      "static_cast<int32_t>(0x00000062), "
      "static_cast<int32_t>(0x00000063), static_cast<int32_t>(0x00000064), "
      "static_cast<int32_t>(0x00000065), static_cast<int32_t>(0x00000066), "
      "static_cast<int32_t>(0x00000067), static_cast<int32_t>(0x00000068), "
      "static_cast<int32_t>(0x00000069), static_cast<int32_t>(0x0000006a),}");

  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int32_t>{0x0000000a}),
            "std::vector<int32_t>{static_cast<int32_t>(0x0000000a),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int32_t>{0x0000000d}),
            "std::vector<int32_t>{static_cast<int32_t>(0x0000000d),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int32_t>{0x00000020}),
            "std::vector<int32_t>{static_cast<int32_t>(0x00000020),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int32_t>{0x00000030}),
            "std::vector<int32_t>{static_cast<int32_t>(0x00000030),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int32_t>{0x00000061}),
            "std::vector<int32_t>{static_cast<int32_t>(0x00000061),}");
  ASSERT_EQ(HexStringer::codeGenVector(std::vector<int32_t>{0x0000007e}),
            "std::vector<int32_t>{static_cast<int32_t>(0x0000007e),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::vector<int32_t>{0x00000061, 0x00000062,
                                                      0x00000063, 0x00000064,
                                                      0x00000065, 0x00000066}),
      "std::vector<int32_t>{static_cast<int32_t>(0x00000061), "
      "static_cast<int32_t>(0x00000062), "
      "static_cast<int32_t>(0x00000063), static_cast<int32_t>(0x00000064), "
      "static_cast<int32_t>(0x00000065), static_cast<int32_t>(0x00000066),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::vector<int32_t>{
          0x00000061, 0x00000062, 0x00000063, 0x00000064, 0x00000065,
          0x00000066, 0x00000067, 0x00000068, 0x00000069, 0x0000006a}),
      "std::vector<int32_t>{static_cast<int32_t>(0x00000061), "
      "static_cast<int32_t>(0x00000062), "
      "static_cast<int32_t>(0x00000063), static_cast<int32_t>(0x00000064), "
      "static_cast<int32_t>(0x00000065), static_cast<int32_t>(0x00000066), "
      "static_cast<int32_t>(0x00000067), static_cast<int32_t>(0x00000068), "
      "static_cast<int32_t>(0x00000069), static_cast<int32_t>(0x0000006a),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::vector<int32_t>{
          static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x000000fe),
          0x00000061,
          0x00000062,
          0x00000063,
          0x00000064,
          0x00000065,
          0x00000066,
          0x00000067,
          0x00000068,
          0x00000069,
          0x0000006a,
          static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000000),
          static_cast<int32_t>(0x000000fe),
          static_cast<int32_t>(0x00000000),
      }),
      "std::vector<int32_t>{static_cast<int32_t>(0x000000ff), "
      "static_cast<int32_t>(0x000000fe), "
      "static_cast<int32_t>(0x00000061), static_cast<int32_t>(0x00000062), "
      "static_cast<int32_t>(0x00000063), static_cast<int32_t>(0x00000064), "
      "static_cast<int32_t>(0x00000065), static_cast<int32_t>(0x00000066), "
      "static_cast<int32_t>(0x00000067), static_cast<int32_t>(0x00000068), "
      "static_cast<int32_t>(0x00000069), static_cast<int32_t>(0x0000006a), "
      "static_cast<int32_t>(0x000000ff), static_cast<int32_t>(0x00000000), "
      "static_cast<int32_t>(0x000000fe), static_cast<int32_t>(0x00000000),}");
  ASSERT_EQ(
      HexStringer::codeGenVector(std::vector<int32_t>{
          0x00000000,
          0x00000000,
          static_cast<int32_t>(0x000000fe),
          static_cast<int32_t>(0x000000ff),
          0x00000061,
          0x00000062,
          0x00000063,
          0x00000064,
          0x00000065,
          0x00000066,
          0x00000067,
          0x00000068,
          0x00000069,
          0x0000006a,
          static_cast<int32_t>(0x000000ff),
          static_cast<int32_t>(0x00000000),
          static_cast<int32_t>(0x000000fe),
          static_cast<int32_t>(0x00000000),
      }),
      "std::vector<int32_t>{static_cast<int32_t>(0x00000000), "
      "static_cast<int32_t>(0x00000000), "
      "static_cast<int32_t>(0x000000fe), static_cast<int32_t>(0x000000ff), "
      "static_cast<int32_t>(0x00000061), static_cast<int32_t>(0x00000062), "
      "static_cast<int32_t>(0x00000063), static_cast<int32_t>(0x00000064), "
      "static_cast<int32_t>(0x00000065), static_cast<int32_t>(0x00000066), "
      "static_cast<int32_t>(0x00000067), static_cast<int32_t>(0x00000068), "
      "static_cast<int32_t>(0x00000069), static_cast<int32_t>(0x0000006a), "
      "static_cast<int32_t>(0x000000ff), static_cast<int32_t>(0x00000000), "
      "static_cast<int32_t>(0x000000fe), static_cast<int32_t>(0x00000000),}");
};
