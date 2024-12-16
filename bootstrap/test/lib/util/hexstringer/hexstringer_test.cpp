#if 0
#include "util/hexstringer/hexstringer.hpp"
#include <gtest/gtest.h>
#include <llvm/Support/raw_ostream.h>

namespace gallop::Util::HexStringer {

class HexStringerTest : public ::testing::Test {};

TEST_F(HexStringerTest, DumpCharCharCheck) {
  EXPECT_EQ(dumpChar((int8_t)0), "");
  EXPECT_EQ(dumpChar((int8_t)'\n'), "0a");
  EXPECT_EQ(dumpChar((int8_t)'\r'), "0d");
  EXPECT_EQ(dumpChar((int8_t)' '), "20");
  EXPECT_EQ(dumpChar((int8_t)'0'), "30");
  EXPECT_EQ(dumpChar((int8_t)'a'), "61");
  EXPECT_EQ(dumpChar((int8_t)'~'), "7e");

  EXPECT_EQ(dumpChar((uint8_t)0, true), "00");
  EXPECT_EQ(dumpChar((uint8_t)0), "");
  EXPECT_EQ(dumpChar((uint8_t)'\n', true), "0a");
  EXPECT_EQ(dumpChar((uint8_t)'\n'), "0a");
  EXPECT_EQ(dumpChar((uint8_t)'\r'), "0d");
  EXPECT_EQ(dumpChar((uint8_t)' '), "20");
  EXPECT_EQ(dumpChar((uint8_t)'0'), "30");
  EXPECT_EQ(dumpChar((uint8_t)'a'), "61");
  EXPECT_EQ(dumpChar((uint8_t)'~'), "7e");
};

TEST_F(HexStringerTest, DumpCharShortCheck) {
  EXPECT_EQ(dumpChar((int16_t)0), "");
  EXPECT_EQ(dumpChar((int16_t)'\n'), "00 0a");
  EXPECT_EQ(dumpChar((int16_t)'\r'), "00 0d");
  EXPECT_EQ(dumpChar((int16_t)' '), "00 20");
  EXPECT_EQ(dumpChar((int16_t)'0'), "00 30");
  EXPECT_EQ(dumpChar((int16_t)'a'), "00 61");
  EXPECT_EQ(dumpChar((int16_t)'~'), "00 7e");
  EXPECT_EQ(dumpChar((int16_t)0xfffe), "ff fe");

  EXPECT_EQ(dumpChar((uint16_t)0), "");
  EXPECT_EQ(dumpChar((uint16_t)'\n'), "00 0a");
  EXPECT_EQ(dumpChar((uint16_t)'\r'), "00 0d");
  EXPECT_EQ(dumpChar((uint16_t)' '), "00 20");
  EXPECT_EQ(dumpChar((uint16_t)'0'), "00 30");
  EXPECT_EQ(dumpChar((uint16_t)'a'), "00 61");
  EXPECT_EQ(dumpChar((uint16_t)'~'), "00 7e");
  EXPECT_EQ(dumpChar((uint16_t)0xfffe), "ff fe");
};

TEST_F(HexStringerTest, DumpCharIntCheck) {
  EXPECT_EQ(dumpChar((int32_t)0), "");
  EXPECT_EQ(dumpChar((int32_t)'\n'), "00 00 00 0a");
  EXPECT_EQ(dumpChar((int32_t)'\r'), "00 00 00 0d");
  EXPECT_EQ(dumpChar((int32_t)' '), "00 00 00 20");
  EXPECT_EQ(dumpChar((int32_t)'0'), "00 00 00 30");
  EXPECT_EQ(dumpChar((int32_t)'a'), "00 00 00 61");
  EXPECT_EQ(dumpChar((int32_t)'~'), "00 00 00 7e");
  EXPECT_EQ(dumpChar((int32_t)0xfffefdfc), "ff fe fd fc");

  EXPECT_EQ(dumpChar((uint32_t)0), "");
  EXPECT_EQ(dumpChar((uint32_t)'\n'), "00 00 00 0a");
  EXPECT_EQ(dumpChar((uint32_t)'\r'), "00 00 00 0d");
  EXPECT_EQ(dumpChar((uint32_t)' '), "00 00 00 20");
  EXPECT_EQ(dumpChar((uint32_t)'0'), "00 00 00 30");
  EXPECT_EQ(dumpChar((uint32_t)'a'), "00 00 00 61");
  EXPECT_EQ(dumpChar((uint32_t)'~'), "00 00 00 7e");
  EXPECT_EQ(dumpChar((uint32_t)0xfffefdfc), "ff fe fd fc");
};

TEST_F(HexStringerTest, DumpCharLongCheck) {
  EXPECT_EQ(dumpChar((int64_t)0), "");
  EXPECT_EQ(dumpChar((int64_t)'\n'), "00 00 00 00 00 00 00 0a");
  EXPECT_EQ(dumpChar((int64_t)'\r'), "00 00 00 00 00 00 00 0d");
  EXPECT_EQ(dumpChar((int64_t)' '), "00 00 00 00 00 00 00 20");
  EXPECT_EQ(dumpChar((int64_t)'0'), "00 00 00 00 00 00 00 30");
  EXPECT_EQ(dumpChar((int64_t)'a'), "00 00 00 00 00 00 00 61");
  EXPECT_EQ(dumpChar((int64_t)'~'), "00 00 00 00 00 00 00 7e");
  EXPECT_EQ(dumpChar((int64_t)0xfffefdfcfbfaf9f8), "ff fe fd fc fb fa f9 f8");

  EXPECT_EQ(dumpChar((uint64_t)0), "");
  EXPECT_EQ(dumpChar((uint64_t)'\n'), "00 00 00 00 00 00 00 0a");
  EXPECT_EQ(dumpChar((uint64_t)'\r'), "00 00 00 00 00 00 00 0d");
  EXPECT_EQ(dumpChar((uint64_t)' '), "00 00 00 00 00 00 00 20");
  EXPECT_EQ(dumpChar((uint64_t)'0'), "00 00 00 00 00 00 00 30");
  EXPECT_EQ(dumpChar((uint64_t)'a'), "00 00 00 00 00 00 00 61");
  EXPECT_EQ(dumpChar((uint64_t)'~'), "00 00 00 00 00 00 00 7e");
  EXPECT_EQ(dumpChar((uint64_t)0xfffefdfcfbfaf9f8), "ff fe fd fc fb fa f9 f8");
};

TEST_F(HexStringerTest, DumpStringCheck) {
  EXPECT_EQ(dumpString(std::string("\n")), "0a");
  EXPECT_EQ(dumpString(std::string("\r")), "0d");
  EXPECT_EQ(dumpString(std::string(" ")), "20");
  EXPECT_EQ(dumpString(std::string("0")), "30");
  EXPECT_EQ(dumpString(std::string("a")), "61");
  EXPECT_EQ(dumpString(std::string("~")), "7e");
  EXPECT_EQ(dumpString(std::string("abcdef")), "61 62 63 64 65 66");
  EXPECT_EQ(dumpString(std::string("abcdefghij")),
            "61 62 63 64 65 66 67 68\n69 6a");

  EXPECT_EQ(dumpString(std::vector<char>{0x0a}), "0a");
  EXPECT_EQ(dumpString(std::vector<char>{0x0d}), "0d");
  EXPECT_EQ(dumpString(std::vector<char>{0x20}), "20");
  EXPECT_EQ(dumpString(std::vector<char>{0x30}), "30");
  EXPECT_EQ(dumpString(std::vector<char>{0x61}), "61");
  EXPECT_EQ(dumpString(std::vector<char>{0x7e}), "7e");
  EXPECT_EQ(dumpString(std::vector<char>{0x61, 0x62, 0x63, 0x64, 0x65, 0x66}),
            "61 62 63 64 65 66");
  EXPECT_EQ(dumpString(std::vector<char>{0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                                         0x67, 0x68, 0x69, 0x6a}),
            "61 62 63 64 65 66 67 68\n69 6a");
  EXPECT_EQ(dumpString(std::vector<char>{
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
  EXPECT_EQ(dumpString(std::vector<char>{
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

TEST_F(HexStringerTest, CodeGenVectorCheck) {
  EXPECT_EQ(codeGenVector(std::string("\n")),
            "std::vector<char>{static_cast<char>(0x0a),}");
  EXPECT_EQ(codeGenVector(std::string("\r")),
            "std::vector<char>{static_cast<char>(0x0d),}");
  EXPECT_EQ(codeGenVector(std::string(" ")),
            "std::vector<char>{static_cast<char>(0x20),}");
  EXPECT_EQ(codeGenVector(std::string("0")),
            "std::vector<char>{static_cast<char>(0x30),}");
  EXPECT_EQ(codeGenVector(std::string("a")),
            "std::vector<char>{static_cast<char>(0x61),}");
  EXPECT_EQ(codeGenVector(std::string("~")),
            "std::vector<char>{static_cast<char>(0x7e),}");
  EXPECT_EQ(
      codeGenVector(std::string("abcdef")),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66),}");
  EXPECT_EQ(
      codeGenVector(std::string("abcdefghij")),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66), "
      "static_cast<char>(0x67), static_cast<char>(0x68), "
      "static_cast<char>(0x69), static_cast<char>(0x6a),}");

  EXPECT_EQ(codeGenVector(std::vector<char>{0x0a}),
            "std::vector<char>{static_cast<char>(0x0a),}");
  EXPECT_EQ(codeGenVector(std::vector<char>{0x0d}),
            "std::vector<char>{static_cast<char>(0x0d),}");
  EXPECT_EQ(codeGenVector(std::vector<char>{0x20}),
            "std::vector<char>{static_cast<char>(0x20),}");
  EXPECT_EQ(codeGenVector(std::vector<char>{0x30}),
            "std::vector<char>{static_cast<char>(0x30),}");
  EXPECT_EQ(codeGenVector(std::vector<char>{0x61}),
            "std::vector<char>{static_cast<char>(0x61),}");
  EXPECT_EQ(codeGenVector(std::vector<char>{0x7e}),
            "std::vector<char>{static_cast<char>(0x7e),}");
  EXPECT_EQ(
      codeGenVector(std::vector<char>{0x61, 0x62, 0x63, 0x64, 0x65, 0x66}),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66),}");
  EXPECT_EQ(
      codeGenVector(std::vector<char>{0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                                      0x68, 0x69, 0x6a}),
      "std::vector<char>{static_cast<char>(0x61), static_cast<char>(0x62), "
      "static_cast<char>(0x63), static_cast<char>(0x64), "
      "static_cast<char>(0x65), static_cast<char>(0x66), "
      "static_cast<char>(0x67), static_cast<char>(0x68), "
      "static_cast<char>(0x69), static_cast<char>(0x6a),}");
  EXPECT_EQ(
      codeGenVector(std::vector<char>{
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
  EXPECT_EQ(
      codeGenVector(std::vector<char>{
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

#endif