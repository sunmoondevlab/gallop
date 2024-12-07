// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "math/big_uint.hpp"
#include <gtest/gtest.h>

#include "char_set/char_code/utf_ascii_table.hpp"
#include "char_set/string/utf32_string.hpp"
#include "error/common_errors.hpp"

using namespace gallop::Math;
using namespace gallop::Error;

class BigUintTest : public ::testing::Test {};

TEST_F(BigUintTest, Uint) {
  BigUint nat(0x0ul);
  std::vector<uint32_t> chunk;
  nat = BigUint(0x0ul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0x1ul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1u);

  nat = BigUint(0x2ul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x2u);

  nat = BigUint(0x3ul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x3u);

  nat = BigUint(0xaul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xau);

  nat = BigUint(0x7ffful);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x7fffu);

  nat = BigUint(0x10000ul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x10000u);

  nat = BigUint(0xfffffffful);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffffffffu);

  nat = BigUint(0x100000000ul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0x1u);

  nat = BigUint(0xfffffffffffffffeul);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfffffffeu);
  ASSERT_EQ(chunk.at(1), 0xffffffffu);

  nat = BigUint(0xfffffffffffffffful);
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffffffffu);
  ASSERT_EQ(chunk.at(1), 0xffffffffu);
};

TEST_F(BigUintTest, StrToUintRadix) {
  std::vector<uint32_t> chunk;
  BigUint nat(0x0ul);
  nat = BigUint(U"0", 10);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(U"00000000000000", 10);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
};

TEST_F(BigUintTest, StrToUintRadixError) {
  try {
    BigUint(U"0000", 1);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 1.\n",
                 err->what());
    delete err;
  }

  try {
    BigUint(U"0000", 63);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 63.\n",
                 err->what());
    delete err;
  }

  try {
    BigUint(U"0o0000", 2);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 2 are 0b or "
                 "0B. "
                 "prefix = 0o.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0O0000", 2);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 2 are 0b or "
                 "0B. "
                 "prefix = 0O.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0x0000", 2);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 2 are 0b or "
                 "0B. "
                 "prefix = 0x.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0X0000", 2);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 2 are 0b or "
                 "0B. "
                 "prefix = 0X.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0b0000", 8);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 8 are 0o or "
                 "0O. "
                 "prefix = 0b.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0B0000", 8);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 8 are 0o or "
                 "0O. "
                 "prefix = 0B.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0x0000", 8);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 8 are 0o or "
                 "0O. "
                 "prefix = 0x.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0X0000", 8);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 8 are 0o or "
                 "0O. "
                 "prefix = 0X.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0b0000", 16);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 16 are 0x or "
                 "0X. "
                 "prefix = 0b.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0B0000", 16);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 16 are 0x or "
                 "0X. "
                 "prefix = 0B.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0o0000", 16);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 16 are 0x or "
                 "0X. "
                 "prefix = 0o.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0O0000", 16);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid prefix in number string. "
                 "only prefixes allowed for the specified radix 16 are 0x or "
                 "0X. "
                 "prefix = 0O.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0x", 16);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number string. empty numeric string is not "
                 "allowed with prefix. prefix = 0x\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"", 2);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number string. empty numeric string is not "
                 "allowed.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"", 10);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number string. empty numeric string is not "
                 "allowed.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'0');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "alphanumeric characters cannot be used as the "
                 "number format delimiter. "
                 "number format delimiter = '0'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'a');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "alphanumeric characters cannot be used as the "
                 "number format delimiter. "
                 "number format delimiter = 'a'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'+');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '+'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'-');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '-'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'*');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '*'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'%');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '%'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'/');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '/'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'=');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '='.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'!');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '!'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'&');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '&'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'|');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '|'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'^');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '^'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'~');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '~'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'<');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '<'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"01", 10, U'>');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '>'.\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"__01", 10, U'_');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number string. "
                 "cannot start with number format delimiter('_'). "
                 "number "
                 "string = \"__01\".\n",
                 err->what());
    delete err;
  }
  try {
    BigUint(U"0x__01", 16, U'_');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number string. "
                 "cannot consecutive number format delimiter('_'). "
                 "number "
                 "string = \"0x__01\".\n",
                 err->what());
    delete err;
  }
};

TEST_F(BigUintTest, DigitLength) {
  BigUint nat(0x0ul);

  nat = BigUint(0x0ul);
  ASSERT_EQ(nat.getBitLength(), 0x1u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  try {
    nat.getDigitLengthByRadix(1);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 1.\n",
                 err->what());
    delete err;
  }
  try {
    nat.getDigitLengthByRadix(63);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. radix is only between 2 and 62 are allowed. "
                 "radix = 63.\n",
                 err->what());
    delete err;
  }
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x1ul);
  ASSERT_EQ(nat.getBitLength(), 0x1u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x2ul);
  ASSERT_EQ(nat.getBitLength(), 0x2u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x3ul);
  ASSERT_EQ(nat.getBitLength(), 0x2u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x4ul);
  ASSERT_EQ(nat.getBitLength(), 0x3u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x8ul);
  ASSERT_EQ(nat.getBitLength(), 0x4u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0xaul);
  ASSERT_EQ(nat.getBitLength(), 0x4u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0xbul);
  ASSERT_EQ(nat.getBitLength(), 0x4u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x10ul);
  ASSERT_EQ(nat.getBitLength(), 0x5u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x5u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x1u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x24ul);
  ASSERT_EQ(nat.getBitLength(), 0x6u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x6u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x1u);

  nat = BigUint(0x3eul);
  ASSERT_EQ(nat.getBitLength(), 0x6u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x6u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x2u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x2u);

  nat = BigUint(0x7ffful);
  ASSERT_EQ(nat.getBitLength(), 0xfu);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x5u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x5u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0xfu);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0xau);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x8u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x5u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x5u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x3u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x3u);

  nat = BigUint(0x10000ul);
  ASSERT_EQ(nat.getBitLength(), 0x11u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x6u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x5u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x5u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x11u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0xbu);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x9u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x6u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x5u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x5u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x4u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x3u);

  nat = BigUint(0xfffffffful);
  ASSERT_EQ(nat.getBitLength(), 0x20u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0xbu);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0xau);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x8u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x20u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x15u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x10u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0xbu);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0xau);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x8u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x7u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x6u);

  nat = BigUint(0x100000000ul);
  ASSERT_EQ(nat.getBitLength(), 0x21u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0xbu);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0xau);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x9u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x21u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x15u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x11u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0xbu);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0xau);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x9u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0x7u);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0x6u);

  nat = BigUint(0xfffffffffffffffeul);
  ASSERT_EQ(nat.getBitLength(), 0x40u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x16u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x14u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x10u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x40u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x29u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x20u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x16u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x13u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x10u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0xdu);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0xbu);

  nat = BigUint(0xfffffffffffffffful);
  ASSERT_EQ(nat.getBitLength(), 0x40u);
  ASSERT_EQ(nat.getOctalDigitLength(), 0x16u);
  ASSERT_EQ(nat.getDecimalDigitLength(), 0x14u);
  ASSERT_EQ(nat.getHexadecimalDigitLength(), 0x10u);
  ASSERT_EQ(nat.getDigitLengthByRadix(2), 0x40u);
  ASSERT_EQ(nat.getDigitLengthByRadix(3), 0x29u);
  ASSERT_EQ(nat.getDigitLengthByRadix(4), 0x20u);
  ASSERT_EQ(nat.getDigitLengthByRadix(8), 0x16u);
  ASSERT_EQ(nat.getDigitLengthByRadix(11), 0x13u);
  ASSERT_EQ(nat.getDigitLengthByRadix(16), 0x10u);
  ASSERT_EQ(nat.getDigitLengthByRadix(36), 0xdu);
  ASSERT_EQ(nat.getDigitLengthByRadix(62), 0xbu);
};
TEST_F(BigUintTest, ToString) {
  BigUint nat(0x0ul);
  nat = BigUint(0x0ul);

  try {
    nat.toStringByRadix(1);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. "
                 "radix is only between 2 and 62 are allowed. "
                 "radix = 1.\n",
                 err->what());
    delete err;
  }
  try {
    nat.toStringByRadix(63);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid radix. "
                 "radix is only between 2 and 62 are allowed. "
                 "radix = 63.\n",
                 err->what());
    delete err;
  }
  try {
    nat.toStringByRadix(2, 1);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid right alignment length. "
                 "right alignment length is only "
                 "zero or greater than equals 2 allowed. "
                 "right alignment length = 1.\n",
                 err->what());
    delete err;
  }
  try {
    nat.toStringByRadix(2, 2, 1);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ(
        "invalid format chunk length. "
        "format chunk length is only "
        "zero or greater than equals 2 allowed. format chunk length = 1.\n",
        err->what());
    delete err;
  }
  try {
    nat.toStringByRadix(2, 2, 2, '0');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "alphanumeric characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '0'.\n",
                 err->what());
    delete err;
  }
  try {
    nat.toStringByRadix(2, 2, 2, 'a');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "alphanumeric characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = 'a'.\n",
                 err->what());
    delete err;
  }
  try {
    nat.toStringByRadix(2, 2, 2, '+');
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid number format delimiter. "
                 "operator symbol characters cannot"
                 " be used as the number format delimiter. "
                 "number format delimiter = '+'.\n",
                 err->what());
    delete err;
  }
  ASSERT_EQ(nat.toBinaryString(), "0b0");
  ASSERT_EQ(nat.toBinaryString(0), "0b0");
  ASSERT_EQ(nat.toBinaryString(4), "0b0000");
  ASSERT_EQ(nat.toBinaryString(4, 2), "0b00_00");
  ASSERT_EQ(nat.toBinaryString(4, 2, ','), "   0");
  ASSERT_EQ(nat.toBinaryString(5, 2, '_'), "0b0_00_00");
  ASSERT_EQ(nat.toBinaryString(0, 2, '_', false), "0");
  ASSERT_EQ(nat.toBinaryString(5, 0, '_', false), "    0");
  ASSERT_EQ(nat.toBinaryString(0, 2, '_', false, true), "0");
  ASSERT_EQ(nat.toBinaryString(5, 0, '_', false, true), "00000");
  ASSERT_EQ(nat.toBinaryString(5, 0, '_', true, true), "0b00000");

  ASSERT_EQ(nat.toOctalString(), "0o0");
  ASSERT_EQ(nat.toOctalString(0), "0o0");
  ASSERT_EQ(nat.toOctalString(4), "0o0000");
  ASSERT_EQ(nat.toOctalString(4, 2), "0o00_00");
  ASSERT_EQ(nat.toOctalString(4, 2, ','), "   0");
  ASSERT_EQ(nat.toOctalString(5, 2, '_'), "0o0_00_00");
  ASSERT_EQ(nat.toOctalString(0, 2, '_', false), "0");
  ASSERT_EQ(nat.toOctalString(5, 0, '_', false), "    0");
  ASSERT_EQ(nat.toOctalString(0, 2, '_', false, true), "0");
  ASSERT_EQ(nat.toOctalString(5, 0, '_', false, true), "00000");
  ASSERT_EQ(nat.toOctalString(5, 0, '_', true, true), "0o00000");

  ASSERT_EQ(nat.toDecimalString(0), "0");
  ASSERT_EQ(nat.toDecimalString(4), "   0");
  ASSERT_EQ(nat.toDecimalString(4, 2), "   0");
  ASSERT_EQ(nat.toDecimalString(4, 2, ','), "   0");
  ASSERT_EQ(nat.toDecimalString(5, 2, '_'), "    0");
  ASSERT_EQ(nat.toDecimalString(0, 2, '_', false), "0");
  ASSERT_EQ(nat.toDecimalString(5, 0, '_', false), "    0");
  ASSERT_EQ(nat.toDecimalString(0, 2, '_', true), "0");
  ASSERT_EQ(nat.toDecimalString(5, 0, '_', true), "00000");
  ASSERT_EQ(nat.toDecimalString(5, 2, '_', true), "0_00_00");

  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  ASSERT_EQ(nat.toHexadecimalString(0), "0x0");
  ASSERT_EQ(nat.toHexadecimalString(4), "0x0000");
  ASSERT_EQ(nat.toHexadecimalString(4, 2), "0x00_00");
  ASSERT_EQ(nat.toHexadecimalString(4, 2, ','), "   0");
  ASSERT_EQ(nat.toHexadecimalString(5, 2, '_'), "0x0_00_00");
  ASSERT_EQ(nat.toHexadecimalString(0, 2, '_', false), "0");
  ASSERT_EQ(nat.toHexadecimalString(5, 0, '_', false), "    0");
  ASSERT_EQ(nat.toHexadecimalString(0, 2, '_', false, true), "0");
  ASSERT_EQ(nat.toHexadecimalString(5, 0, '_', false, true), "00000");
  ASSERT_EQ(nat.toHexadecimalString(5, 0, '_', true, true), "0x00000");

  ASSERT_EQ(nat.toStringByRadix(2), "0");
  ASSERT_EQ(nat.toStringByRadix(3), "0");
  ASSERT_EQ(nat.toStringByRadix(4), "0");
  ASSERT_EQ(nat.toStringByRadix(8), "0");
  ASSERT_EQ(nat.toStringByRadix(11), "0");
  ASSERT_EQ(nat.toStringByRadix(16), "0");
  ASSERT_EQ(nat.toStringByRadix(36), "0");
  ASSERT_EQ(nat.toStringByRadix(62), "0");

  ASSERT_EQ(nat.toStringByRadix(2, 4), "   0");
  ASSERT_EQ(nat.toStringByRadix(2, 4, 2), "   0");
  ASSERT_EQ(nat.toStringByRadix(2, 4, 2, '_'), "   0");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, '_'), "    0");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, '_', true), "0_00_00");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, ' ', true), "0 00 00");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, ',', true), "0,00,00");

  nat = BigUint(0x1ul);
  ASSERT_EQ(nat.toBinaryString(), "0b1");
  ASSERT_EQ(nat.toBinaryString(0), "0b1");
  ASSERT_EQ(nat.toBinaryString(4), "0b0001");
  ASSERT_EQ(nat.toBinaryString(4, 2), "0b00_01");
  ASSERT_EQ(nat.toBinaryString(4, 2, ','), "   1");
  ASSERT_EQ(nat.toBinaryString(5, 2, '_'), "0b0_00_01");
  ASSERT_EQ(nat.toBinaryString(0, 2, '_', false), "1");
  ASSERT_EQ(nat.toBinaryString(5, 0, '_', false), "    1");
  ASSERT_EQ(nat.toBinaryString(0, 2, '_', false, true), "1");
  ASSERT_EQ(nat.toBinaryString(5, 0, '_', false, true), "00001");
  ASSERT_EQ(nat.toBinaryString(5, 0, '_', true, true), "0b00001");

  ASSERT_EQ(nat.toOctalString(), "0o1");
  ASSERT_EQ(nat.toOctalString(0), "0o1");
  ASSERT_EQ(nat.toOctalString(4), "0o0001");
  ASSERT_EQ(nat.toOctalString(4, 2), "0o00_01");
  ASSERT_EQ(nat.toOctalString(4, 2, ','), "   1");
  ASSERT_EQ(nat.toOctalString(5, 2, '_'), "0o0_00_01");
  ASSERT_EQ(nat.toOctalString(0, 2, '_', false), "1");
  ASSERT_EQ(nat.toOctalString(5, 0, '_', false), "    1");
  ASSERT_EQ(nat.toOctalString(0, 2, '_', false, true), "1");
  ASSERT_EQ(nat.toOctalString(5, 0, '_', false, true), "00001");
  ASSERT_EQ(nat.toOctalString(5, 0, '_', true, true), "0o00001");

  ASSERT_EQ(nat.toDecimalString(0), "1");
  ASSERT_EQ(nat.toDecimalString(4), "   1");
  ASSERT_EQ(nat.toDecimalString(4, 2), "   1");
  ASSERT_EQ(nat.toDecimalString(4, 2, ','), "   1");
  ASSERT_EQ(nat.toDecimalString(5, 2, '_'), "    1");
  ASSERT_EQ(nat.toDecimalString(0, 2, '_', false), "1");
  ASSERT_EQ(nat.toDecimalString(5, 0, '_', false), "    1");
  ASSERT_EQ(nat.toDecimalString(0, 2, '_', true), "1");
  ASSERT_EQ(nat.toDecimalString(5, 0, '_', true), "00001");
  ASSERT_EQ(nat.toDecimalString(5, 2, '_', true), "0_00_01");

  ASSERT_EQ(nat.toHexadecimalString(), "0x1");
  ASSERT_EQ(nat.toHexadecimalString(0), "0x1");
  ASSERT_EQ(nat.toHexadecimalString(4), "0x0001");
  ASSERT_EQ(nat.toHexadecimalString(4, 2), "0x00_01");
  ASSERT_EQ(nat.toHexadecimalString(4, 2, ','), "   1");
  ASSERT_EQ(nat.toHexadecimalString(5, 2, '_'), "0x0_00_01");
  ASSERT_EQ(nat.toHexadecimalString(0, 2, '_', false), "1");
  ASSERT_EQ(nat.toHexadecimalString(5, 0, '_', false), "    1");
  ASSERT_EQ(nat.toHexadecimalString(0, 2, '_', false, true), "1");
  ASSERT_EQ(nat.toHexadecimalString(5, 0, '_', false, true), "00001");
  ASSERT_EQ(nat.toHexadecimalString(5, 0, '_', true, true), "0x00001");

  ASSERT_EQ(nat.toStringByRadix(2), "1");
  ASSERT_EQ(nat.toStringByRadix(3), "1");
  ASSERT_EQ(nat.toStringByRadix(4), "1");
  ASSERT_EQ(nat.toStringByRadix(8), "1");
  ASSERT_EQ(nat.toStringByRadix(11), "1");
  ASSERT_EQ(nat.toStringByRadix(16), "1");
  ASSERT_EQ(nat.toStringByRadix(36), "1");
  ASSERT_EQ(nat.toStringByRadix(62), "1");

  ASSERT_EQ(nat.toStringByRadix(2, 4), "   1");
  ASSERT_EQ(nat.toStringByRadix(2, 4, 2), "   1");
  ASSERT_EQ(nat.toStringByRadix(2, 4, 2, '_'), "   1");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, '_'), "    1");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, '_', true), "0_00_01");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, ' ', true), "0 00 01");
  ASSERT_EQ(nat.toStringByRadix(2, 5, 2, ',', true), "0,00,01");

  nat = BigUint(0x2ul);
  ASSERT_EQ(nat.toBinaryString(2, 2), "0b10");

  ASSERT_EQ(nat.toStringByRadix(2), "10");
  ASSERT_EQ(nat.toStringByRadix(3), "2");
  ASSERT_EQ(nat.toStringByRadix(4), "2");
  ASSERT_EQ(nat.toStringByRadix(8), "2");
  ASSERT_EQ(nat.toStringByRadix(11), "2");
  ASSERT_EQ(nat.toStringByRadix(16), "2");
  ASSERT_EQ(nat.toStringByRadix(36), "2");
  ASSERT_EQ(nat.toStringByRadix(62), "2");

  nat = BigUint(0x3ul);
  ASSERT_EQ(nat.toStringByRadix(2), "11");
  ASSERT_EQ(nat.toStringByRadix(3), "10");
  ASSERT_EQ(nat.toStringByRadix(4), "3");
  ASSERT_EQ(nat.toStringByRadix(8), "3");
  ASSERT_EQ(nat.toStringByRadix(11), "3");
  ASSERT_EQ(nat.toStringByRadix(16), "3");
  ASSERT_EQ(nat.toStringByRadix(36), "3");
  ASSERT_EQ(nat.toStringByRadix(62), "3");

  nat = BigUint(0x4ul);
  ASSERT_EQ(nat.toStringByRadix(2), "100");
  ASSERT_EQ(nat.toStringByRadix(3), "11");
  ASSERT_EQ(nat.toStringByRadix(4), "10");
  ASSERT_EQ(nat.toStringByRadix(8), "4");
  ASSERT_EQ(nat.toStringByRadix(11), "4");
  ASSERT_EQ(nat.toStringByRadix(16), "4");
  ASSERT_EQ(nat.toStringByRadix(36), "4");
  ASSERT_EQ(nat.toStringByRadix(62), "4");

  nat = BigUint(0x8ul);
  ASSERT_EQ(nat.toBinaryString(2, 2), "0b10_00");
  ASSERT_EQ(nat.toOctalString(2, 2), "0o10");

  ASSERT_EQ(nat.toStringByRadix(2), "1000");
  ASSERT_EQ(nat.toStringByRadix(3), "22");
  ASSERT_EQ(nat.toStringByRadix(4), "20");
  ASSERT_EQ(nat.toStringByRadix(8), "10");
  ASSERT_EQ(nat.toStringByRadix(11), "8");
  ASSERT_EQ(nat.toStringByRadix(16), "8");
  ASSERT_EQ(nat.toStringByRadix(36), "8");
  ASSERT_EQ(nat.toStringByRadix(62), "8");

  nat = BigUint(0xaul);
  ASSERT_EQ(nat.toBinaryString(2, 2), "0b10_10");
  ASSERT_EQ(nat.toOctalString(2, 2), "0o12");
  ASSERT_EQ(nat.toDecimalString(2, 2), "10");

  ASSERT_EQ(nat.toStringByRadix(2), "1010");
  ASSERT_EQ(nat.toStringByRadix(3), "101");
  ASSERT_EQ(nat.toStringByRadix(4), "22");
  ASSERT_EQ(nat.toStringByRadix(8), "12");
  ASSERT_EQ(nat.toStringByRadix(11), "a");
  ASSERT_EQ(nat.toStringByRadix(16), "a");
  ASSERT_EQ(nat.toStringByRadix(36), "a");
  ASSERT_EQ(nat.toStringByRadix(62), "a");

  nat = BigUint(0xbul);
  ASSERT_EQ(nat.toStringByRadix(2), "1011");
  ASSERT_EQ(nat.toStringByRadix(3), "102");
  ASSERT_EQ(nat.toStringByRadix(4), "23");
  ASSERT_EQ(nat.toStringByRadix(8), "13");
  ASSERT_EQ(nat.toStringByRadix(11), "10");
  ASSERT_EQ(nat.toStringByRadix(16), "b");
  ASSERT_EQ(nat.toStringByRadix(36), "b");
  ASSERT_EQ(nat.toStringByRadix(62), "b");

  nat = BigUint(0x10ul);
  ASSERT_EQ(nat.toBinaryString(4, 4), "0b1_0000");
  ASSERT_EQ(nat.toOctalString(2, 2), "0o20");
  ASSERT_EQ(nat.toDecimalString(2, 2), "16");
  ASSERT_EQ(nat.toHexadecimalString(2, 2), "0x10");

  ASSERT_EQ(nat.toStringByRadix(2), "10000");
  ASSERT_EQ(nat.toStringByRadix(3), "121");
  ASSERT_EQ(nat.toStringByRadix(4), "100");
  ASSERT_EQ(nat.toStringByRadix(8), "20");
  ASSERT_EQ(nat.toStringByRadix(11), "15");
  ASSERT_EQ(nat.toStringByRadix(16), "10");
  ASSERT_EQ(nat.toStringByRadix(36), "g");
  ASSERT_EQ(nat.toStringByRadix(62), "g");

  nat = BigUint(0x24ul);
  ASSERT_EQ(nat.toBinaryString(4, 4), "0b10_0100");
  ASSERT_EQ(nat.toOctalString(2, 2), "0o44");
  ASSERT_EQ(nat.toDecimalString(2, 2), "36");
  ASSERT_EQ(nat.toHexadecimalString(2, 2), "0x24");

  ASSERT_EQ(nat.toStringByRadix(2), "100100");
  ASSERT_EQ(nat.toStringByRadix(3), "1100");
  ASSERT_EQ(nat.toStringByRadix(4), "210");
  ASSERT_EQ(nat.toStringByRadix(8), "44");
  ASSERT_EQ(nat.toStringByRadix(11), "33");
  ASSERT_EQ(nat.toStringByRadix(16), "24");
  ASSERT_EQ(nat.toStringByRadix(36), "10");
  ASSERT_EQ(nat.toStringByRadix(62), "A");

  nat = BigUint(0x3eul);
  ASSERT_EQ(nat.toBinaryString(4, 4), "0b11_1110");
  ASSERT_EQ(nat.toOctalString(2, 2), "0o76");
  ASSERT_EQ(nat.toDecimalString(2, 2), "62");
  ASSERT_EQ(nat.toHexadecimalString(2, 2), "0x3e");

  ASSERT_EQ(nat.toStringByRadix(2), "111110");
  ASSERT_EQ(nat.toStringByRadix(3), "2022");
  ASSERT_EQ(nat.toStringByRadix(4), "332");
  ASSERT_EQ(nat.toStringByRadix(8), "76");
  ASSERT_EQ(nat.toStringByRadix(11), "57");
  ASSERT_EQ(nat.toStringByRadix(16), "3e");
  ASSERT_EQ(nat.toStringByRadix(36), "1q");
  ASSERT_EQ(nat.toStringByRadix(62), "10");

  nat = BigUint(0x7ffful);
  ASSERT_EQ(nat.toBinaryString(4, 4), "0b111_1111_1111_1111");
  ASSERT_EQ(nat.toOctalString(6, 3), "0o077_777");
  ASSERT_EQ(nat.toDecimalString(4, 4), "3_2767");
  ASSERT_EQ(nat.toHexadecimalString(4, 4), "0x7fff");

  ASSERT_EQ(nat.toStringByRadix(2), "111111111111111");
  ASSERT_EQ(nat.toStringByRadix(3), "1122221121");
  ASSERT_EQ(nat.toStringByRadix(4), "13333333");
  ASSERT_EQ(nat.toStringByRadix(8), "77777");
  ASSERT_EQ(nat.toStringByRadix(11), "22689");
  ASSERT_EQ(nat.toStringByRadix(16), "7fff");
  ASSERT_EQ(nat.toStringByRadix(36), "pa7");
  ASSERT_EQ(nat.toStringByRadix(62), "8wv");

  nat = BigUint(0x10000ul);
  ASSERT_EQ(nat.toBinaryString(4, 4), "0b1_0000_0000_0000_0000");
  ASSERT_EQ(nat.toOctalString(6, 3), "0o200_000");
  ASSERT_EQ(nat.toDecimalString(4, 4), "6_5536");
  ASSERT_EQ(nat.toHexadecimalString(4, 4), "0x1_0000");

  ASSERT_EQ(nat.toStringByRadix(2), "10000000000000000");
  ASSERT_EQ(nat.toStringByRadix(3), "10022220021");
  ASSERT_EQ(nat.toStringByRadix(4), "100000000");
  ASSERT_EQ(nat.toStringByRadix(8), "200000");
  ASSERT_EQ(nat.toStringByRadix(11), "45269");
  ASSERT_EQ(nat.toStringByRadix(16), "10000");
  ASSERT_EQ(nat.toStringByRadix(36), "1ekg");
  ASSERT_EQ(nat.toStringByRadix(62), "h32");

  nat = BigUint(0xfffffffful);
  ASSERT_EQ(nat.toBinaryString(32, 8), "0b11111111_11111111_11111111_11111111");
  ASSERT_EQ(nat.toOctalString(12, 6), "0o037777_777777");
  ASSERT_EQ(nat.toDecimalString(11, 4), " 42_9496_7295");
  ASSERT_EQ(nat.toHexadecimalString(9, 4), "0x0_ffff_ffff");

  ASSERT_EQ(nat.toStringByRadix(2), "11111111111111111111111111111111");
  ASSERT_EQ(nat.toStringByRadix(3), "102002022201221111210");
  ASSERT_EQ(nat.toStringByRadix(4), "3333333333333333");
  ASSERT_EQ(nat.toStringByRadix(8), "37777777777");
  ASSERT_EQ(nat.toStringByRadix(11), "1904440553");
  ASSERT_EQ(nat.toStringByRadix(16), "ffffffff");
  ASSERT_EQ(nat.toStringByRadix(36), "1z141z3");
  ASSERT_EQ(nat.toStringByRadix(62), "4GFfc3");

  nat = BigUint(0x100000000ul);
  ASSERT_EQ(nat.toBinaryString(32, 8),
            "0b1_00000000_00000000_00000000_00000000");
  ASSERT_EQ(nat.toOctalString(12, 6), "0o040000_000000");
  ASSERT_EQ(nat.toDecimalString(11, 4), " 42_9496_7296");
  ASSERT_EQ(nat.toHexadecimalString(9, 4), "0x1_0000_0000");

  ASSERT_EQ(nat.toStringByRadix(2), "100000000000000000000000000000000");
  ASSERT_EQ(nat.toStringByRadix(3), "102002022201221111211");
  ASSERT_EQ(nat.toStringByRadix(4), "10000000000000000");
  ASSERT_EQ(nat.toStringByRadix(8), "40000000000");
  ASSERT_EQ(nat.toStringByRadix(11), "1904440554");
  ASSERT_EQ(nat.toStringByRadix(16), "100000000");
  ASSERT_EQ(nat.toStringByRadix(36), "1z141z4");
  ASSERT_EQ(nat.toStringByRadix(62), "4GFfc4");

  nat = BigUint(0xfffffffffffffffeul);
  ASSERT_EQ(nat.toBinaryString(32, 8), "0b11111111_11111111_11111111_11111111_"
                                       "11111111_11111111_11111111_11111110");
  ASSERT_EQ(nat.toOctalString(12, 6), "0o1777_777777_777777_777776");
  ASSERT_EQ(nat.toDecimalString(11, 4), "1844_6744_0737_0955_1614");
  ASSERT_EQ(nat.toHexadecimalString(9, 4), "0xffff_ffff_ffff_fffe");

  ASSERT_EQ(nat.toStringByRadix(2), "11111111111111111111111111111111"
                                    "11111111111111111111111111111110");
  ASSERT_EQ(nat.toStringByRadix(3),
            "11112220022122120101211020120210210211212");
  ASSERT_EQ(nat.toStringByRadix(4), "33333333333333333333333333333332");
  ASSERT_EQ(nat.toStringByRadix(8), "1777777777777777777776");
  ASSERT_EQ(nat.toStringByRadix(11), "335500516a429071283");
  ASSERT_EQ(nat.toStringByRadix(16), "fffffffffffffffe");
  ASSERT_EQ(nat.toStringByRadix(36), "3w5e11264sgse");
  ASSERT_EQ(nat.toStringByRadix(62), "lYGhA16ahye");

  nat = BigUint(0xfffffffffffffffful);
  ASSERT_EQ(nat.toBinaryString(32, 8), "0b11111111_11111111_11111111_11111111_"
                                       "11111111_11111111_11111111_11111111");
  ASSERT_EQ(nat.toBinaryString(0), "0b11111111111111111111111111111111"
                                   "11111111111111111111111111111111");
  ASSERT_EQ(nat.toBinaryString(65), "0b011111111111111111111111111111111"
                                    "11111111111111111111111111111111");
  ASSERT_EQ(nat.toBinaryString(65, 8),
            "0b0_11111111_11111111_11111111_11111111_"
            "11111111_11111111_11111111_11111111");
  ASSERT_EQ(nat.toBinaryString(64, 8, ','),
            "11111111,11111111,11111111,11111111,"
            "11111111,11111111,11111111,11111111");
  ASSERT_EQ(nat.toBinaryString(65, 8, '_'),
            "0b0_11111111_11111111_11111111_11111111_"
            "11111111_11111111_11111111_11111111");
  ASSERT_EQ(nat.toBinaryString(0, 8, '_', false),
            "11111111_11111111_11111111_11111111_"
            "11111111_11111111_11111111_11111111");
  ASSERT_EQ(nat.toBinaryString(65, 0, '_', false),
            " 11111111111111111111111111111111"
            "11111111111111111111111111111111");
  ASSERT_EQ(nat.toBinaryString(0, 8, '_', false, true),
            "11111111_11111111_11111111_11111111_"
            "11111111_11111111_11111111_11111111");
  ASSERT_EQ(nat.toBinaryString(65, 0, '_', false, true),
            "011111111111111111111111111111111"
            "11111111111111111111111111111111");
  ASSERT_EQ(nat.toBinaryString(65, 0, '_', true, true),
            "0b011111111111111111111111111111111"
            "11111111111111111111111111111111");

  ASSERT_EQ(nat.toOctalString(12, 6), "0o1777_777777_777777_777777");
  ASSERT_EQ(nat.toOctalString(0), "0o1777777777777777777777");
  ASSERT_EQ(nat.toOctalString(24), "0o001777777777777777777777");
  ASSERT_EQ(nat.toOctalString(24, 6), "0o001777_777777_777777_777777");
  ASSERT_EQ(nat.toOctalString(22, 6, ','), "1777,777777,777777,777777");
  ASSERT_EQ(nat.toOctalString(24, 6, '_'), "0o001777_777777_777777_777777");
  ASSERT_EQ(nat.toOctalString(0, 6, '_', false), "1777_777777_777777_777777");
  ASSERT_EQ(nat.toOctalString(24, 0, '_', false), "  1777777777777777777777");
  ASSERT_EQ(nat.toOctalString(0, 6, '_', false, true),
            "1777_777777_777777_777777");
  ASSERT_EQ(nat.toOctalString(24, 0, '_', false, true),
            "001777777777777777777777");
  ASSERT_EQ(nat.toOctalString(24, 0, '_', true, true),
            "0o001777777777777777777777");

  ASSERT_EQ(nat.toDecimalString(11, 4), "1844_6744_0737_0955_1615");
  ASSERT_EQ(nat.toDecimalString(0), "18446744073709551615");
  ASSERT_EQ(nat.toDecimalString(21), " 18446744073709551615");
  ASSERT_EQ(nat.toDecimalString(21, 4), " 1844_6744_0737_0955_1615");
  ASSERT_EQ(nat.toDecimalString(20, 4, ','), "1844,6744,0737,0955,1615");
  ASSERT_EQ(nat.toDecimalString(21, 4, '_'), " 1844_6744_0737_0955_1615");
  ASSERT_EQ(nat.toDecimalString(0, 4, '_', false), "1844_6744_0737_0955_1615");
  ASSERT_EQ(nat.toDecimalString(21, 0, '_', false), " 18446744073709551615");
  ASSERT_EQ(nat.toDecimalString(21, 0, '_', true), "018446744073709551615");

  ASSERT_EQ(nat.toHexadecimalString(9, 4), "0xffff_ffff_ffff_ffff");
  ASSERT_EQ(nat.toHexadecimalString(0), "0xffffffffffffffff");
  ASSERT_EQ(nat.toHexadecimalString(17), "0x0ffffffffffffffff");
  ASSERT_EQ(nat.toHexadecimalString(17, 4), "0x0_ffff_ffff_ffff_ffff");
  ASSERT_EQ(nat.toHexadecimalString(16, 4, ','), "ffff,ffff,ffff,ffff");
  ASSERT_EQ(nat.toHexadecimalString(17, 4, '_'), "0x0_ffff_ffff_ffff_ffff");
  ASSERT_EQ(nat.toHexadecimalString(0, 4, '_', false), "ffff_ffff_ffff_ffff");
  ASSERT_EQ(nat.toHexadecimalString(17, 0, '_', false), " ffffffffffffffff");
  ASSERT_EQ(nat.toHexadecimalString(0, 4, '_', false, true),
            "ffff_ffff_ffff_ffff");
  ASSERT_EQ(nat.toHexadecimalString(17, 0, '_', false, true),
            "0ffffffffffffffff");
  ASSERT_EQ(nat.toHexadecimalString(17, 0, '_', true, true),
            "0x0ffffffffffffffff");

  ASSERT_EQ(nat.toStringByRadix(2), "11111111111111111111111111111111"
                                    "11111111111111111111111111111111");
  ASSERT_EQ(nat.toStringByRadix(3),
            "11112220022122120101211020120210210211220");
  ASSERT_EQ(nat.toStringByRadix(4), "33333333333333333333333333333333");
  ASSERT_EQ(nat.toStringByRadix(8), "1777777777777777777777");
  ASSERT_EQ(nat.toStringByRadix(11), "335500516a429071284");
  ASSERT_EQ(nat.toStringByRadix(16), "ffffffffffffffff");
  ASSERT_EQ(nat.toStringByRadix(36), "3w5e11264sgsf");
  ASSERT_EQ(nat.toStringByRadix(62), "lYGhA16ahyf");
};

TEST_F(BigUintTest, OpAdd) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;
  nat = BigUint(0x0ul) + BigUint(0xaul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xa");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xau);

  nat = BigUint(0xaul) + BigUint(0x0ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xa");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xau);

  nat = BigUint(0xfffffffffffffffful) + BigUint(0xaul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x10000000000000009");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x9u);
  ASSERT_EQ(chunk.at(1), 0x0u);
  ASSERT_EQ(chunk.at(2), 0x1u);

  nat = BigUint(0xfffffffffffffffful) + BigUint(0xfffffffffffffffful);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1fffffffffffffffe");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfffffffeu);
  ASSERT_EQ(chunk.at(1), 0xffffffffu);
  ASSERT_EQ(chunk.at(2), 0x1u);

  nat += BigUint(0x400);
  ASSERT_EQ(nat.toHexadecimalString(), "0x200000000000003fe");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x000003feu);
  ASSERT_EQ(chunk.at(1), 0x00000000u);
  ASSERT_EQ(chunk.at(2), 0x2u);

  ++nat;
  ASSERT_EQ(nat.toHexadecimalString(), "0x200000000000003ff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x000003ffu);
  ASSERT_EQ(chunk.at(1), 0x00000000u);
  ASSERT_EQ(chunk.at(2), 0x2u);
};

TEST_F(BigUintTest, OpSub) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  try {
    nat = BigUint(0x0ul) - BigUint(0xaul);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid sub operand."
                 " allow only first operand greater than or equal second."
                 " first = 0x0."
                 " second = 0xa.\n",
                 err->what());
    delete err;
  }

  try {
    nat = BigUint(0x0ul) - BigUint(0xfffffffffffffffful);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ("invalid sub operand."
                 " allow only first operand greater than or equal second."
                 " first = 0x0."
                 " second = 0xffffffffffffffff.\n",
                 err->what());
    delete err;
  }

  nat = BigUint(0xaul) - BigUint(0x0ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xa");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xau);

  nat = BigUint(0x10000) - BigUint(0x400);
  ASSERT_EQ(nat.toHexadecimalString(), "0xfc00");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfc00u);

  nat = BigUint(0x100000001ul) - BigUint(0x2ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xffffffff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffffffffu);

  nat = BigUint(0xfffffffffffffffful) - BigUint(0xfffful);
  ASSERT_EQ(nat.toHexadecimalString(), "0xffffffffffff0000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffff0000u);
  ASSERT_EQ(chunk.at(1), 0xffffffffu);

  nat = BigUint(0xfffffffffffffffful) - BigUint(0xfffffffffffffffful);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0xfffffffffffefffful) - BigUint(0xffeffffffffffffful);
  ASSERT_EQ(nat.toHexadecimalString(), "0xfffffffff0000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffff0000u);
  ASSERT_EQ(chunk.at(1), 0xfffffu);

  nat = BigUint(0xfefffefffeff0000ul) - BigUint(0xfefffefeffff00feul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xfeffff02");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfeffff02u);

  nat -= BigUint(0xff02);
  ASSERT_EQ(nat.toHexadecimalString(), "0xfeff0000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfeff0000u);

  --nat;
  ASSERT_EQ(nat.toHexadecimalString(), "0xfefeffff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfefeffffu);
};

TEST_F(BigUintTest, OpMul) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  nat = BigUint(0x0ul) * BigUint(0xfefffefeffff00feul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0xfefffefeffff00feul) * BigUint(0x0ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0xfffful) * BigUint(0x2ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1fffe");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1fffeu);

  nat = BigUint(0xfffful) * BigUint(0x4ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x3fffc");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x3fffcu);

  nat = BigUint(0xfffful) * BigUint(0x8ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x7fff8");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x7fff8u);

  nat = BigUint(0xfffful) * BigUint(0x10ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xffff0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffff0u);

  nat = BigUint(0xfffful) * BigUint(0x1000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xffff000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffff000u);

  nat = BigUint(0xfffful) * BigUint(0x24ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x23ffdc");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x23ffdcu);

  nat = BigUint(0xffffffffful) * BigUint(0x24ul);
  chunk = nat.getChunks();
  ASSERT_EQ(nat.toHexadecimalString(), "0x23fffffffdc");
  ASSERT_EQ(chunk.at(0), 0xffffffdcu);
  ASSERT_EQ(chunk.at(1), 0x23fu);

  nat = BigUint(0xffffffffful) * BigUint(0x29263224ul);
  chunk = nat.getChunks();
  ASSERT_EQ(nat.toHexadecimalString(), "0x29263223fd6d9cddc");
  ASSERT_EQ(chunk.at(0), 0xd6d9cddcu);
  ASSERT_EQ(chunk.at(1), 0x9263223fu);
  ASSERT_EQ(chunk.at(2), 0x2u);

  nat *= BigUint(0xf224ul);
  chunk = nat.getChunks();
  ASSERT_EQ(nat.toHexadecimalString(), "0x26ebe4c512a141b3aeaf0");
  ASSERT_EQ(chunk.at(0), 0x1b3aeaf0u);
  ASSERT_EQ(chunk.at(1), 0x4c512a14u);
  ASSERT_EQ(chunk.at(2), 0x26ebeu);

  nat = BigUint(0xfffful) * BigUint(0x800000000000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x7fff800000000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0x7fff8000u);
};

TEST_F(BigUintTest, OpDiv) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  try {
    nat = BigUint(0x1ul) / BigUint(0x0ul);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ(
        "invalid div operand. allow only second operand greater than zero.\n",
        err->what());
    delete err;
  }

  nat = BigUint(0x0ul) / BigUint(0xfefffefeffff00feul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0xaul) / BigUint(0x1ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xa");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xau);

  nat = BigUint(0xaul) / BigUint(0xbul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0xbul) / BigUint(0xbul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1u);

  nat = BigUint(0xfffful) / BigUint(0x2ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x7fff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x7fffu);

  nat = BigUint(0xfffful) / BigUint(0x4ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x3fff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x3fffu);

  nat = BigUint(0xfffful) / BigUint(0x8ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1fff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1fffu);

  nat = BigUint(0xfffful) / BigUint(0x10ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xfff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfffu);

  nat = BigUint(0xfffful) / BigUint(0x1000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xf");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfu);

  nat = BigUint(0xfffful) / BigUint(0xccccul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1u);

  nat = BigUint(0xfeeeeffffeeeeul) / BigUint(0xddddul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1262889d9c");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x62889d9cu);
  ASSERT_EQ(chunk.at(1), 0x12u);

  nat = BigUint(0xfeeeeffffeeeeul) / BigUint(0x2eeeeffffeeeeul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x5");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x5u);

  nat = (BigUint(0xfeeeeffffeeeeul) * BigUint(0x2eeeeffffeeeeul)) /
        BigUint(0xffffeeeeul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x2ebce360f41f5dafa3");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1f5dafa3u);
  ASSERT_EQ(chunk.at(1), 0xbce360f4u);
  ASSERT_EQ(chunk.at(2), 0x2eu);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) /
        BigUint(0x20000000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xf00000000000000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0x0u);
  ASSERT_EQ(chunk.at(2), 0xf0u);

  nat /= BigUint(0x1000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xf00000000000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0xf000000u);

  nat = (BigUint(0xfeeeeffffeeeeul) * BigUint(0x2eeeeffffeeeeul)) /
        BigUint(0x80000000000l);
  ASSERT_EQ(nat.toHexadecimalString(), "0x5d79c0863f7be15");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x63f7be15u);
  ASSERT_EQ(chunk.at(1), 0x5d79c08u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) /
        (BigUint(0xf000000000000ul) * BigUint(0x1fffffffffffful));
  ASSERT_EQ(nat.toHexadecimalString(), "0x1");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) /
        (BigUint(0x20000001ul) * BigUint(0x20000001ul));
  ASSERT_EQ(nat.toHexadecimalString(), "0x77fffff8800");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffff8800u);
  ASSERT_EQ(chunk.at(1), 0x77fu);
};

TEST_F(BigUintTest, OpMod) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  try {
    nat = BigUint(0x1ul) % BigUint(0x0ul);
    FAIL();
  } catch (InvalidArgumentError *err) {
    // check exception
    ASSERT_STREQ(
        "invalid mod operand. allow only second operand greater than zero.\n",
        err->what());
    delete err;
  }

  nat = BigUint(0x0ul) % BigUint(0xfefffefeffff00feul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0xaul) % BigUint(0x1ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0xaul) % BigUint(0xbul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xa");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xau);

  nat = BigUint(0xfffful) % BigUint(0x2ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1u);

  nat = BigUint(0xfffful) % BigUint(0x4ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x3");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x3u);

  nat = BigUint(0xfffful) % BigUint(0x8ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x7");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x7u);

  nat = BigUint(0xfffful) % BigUint(0x10ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xf");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfu);

  nat = BigUint(0xfffful) % BigUint(0x1000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xfff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xfffu);

  nat = BigUint(0xfffful) % BigUint(0xccccul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x3333");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x3333u);

  nat = BigUint(0xfeeeeffffeeeeul) % BigUint(0xddddul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x3342");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x3342u);

  nat = BigUint(0xfeeeeffffeeeeul) % BigUint(0x2eeeeffffeeeeul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1444400004448");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x4448u);
  ASSERT_EQ(chunk.at(1), 0x14444u);

  nat = (BigUint(0xfeeeeffffeeeeul) * BigUint(0x2eeeeffffeeeeul)) %
        BigUint(0xffffeeeeul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x6e6391ba");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x6e6391bau);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) %
        BigUint(0x20000000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) %
        BigUint(0x1ffffefful);
  nat %= BigUint(0xcul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x9");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x9u);

  nat = (BigUint(0xfeeeeffffeeeeul) * BigUint(0x2eeeeffffeeeeul)) %
        BigUint(0x80000000000l);
  ASSERT_EQ(nat.toHexadecimalString(), "0x6401236544");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1236544u);
  ASSERT_EQ(chunk.at(1), 0x64u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) %
        (BigUint(0x20000001ul) * BigUint(0x20000001ul));
  ASSERT_EQ(nat.toHexadecimalString(), "0x168000007800");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x00007800u);
  ASSERT_EQ(chunk.at(1), 0x1680u);
};

TEST_F(BigUintTest, Compare) {
  ASSERT_TRUE(BigUint(0x0ul) < BigUint(0xfffffffffffffffful));
  ASSERT_TRUE(BigUint(0x100000000ul) <= BigUint(0xfffffffffffffffful));
  ASSERT_TRUE(BigUint(0xfffffffffffffffeul) < BigUint(0xfffffffffffffffful));
  ASSERT_TRUE(BigUint(0xfffffffffffffffeul) <= BigUint(0xfffffffffffffffful));
  ASSERT_TRUE(BigUint(0xfffffffffffffffful) <= BigUint(0xfffffffffffffffful));

  ASSERT_FALSE(BigUint(0x0ul) > BigUint(0xfffffffffffffffful));
  ASSERT_FALSE(BigUint(0x100000000ul) >= BigUint(0xfffffffffffffffful));
  ASSERT_FALSE(BigUint(0xfffffffffffffffeul) > BigUint(0xfffffffffffffffful));
  ASSERT_FALSE(BigUint(0xfffffffffffffffeul) >= BigUint(0xfffffffffffffffful));

  ASSERT_TRUE(BigUint(0xfffffffffffffffful) > BigUint(0x0ul));
  ASSERT_TRUE(BigUint(0xfffffffffffffffful) >= BigUint(0x100000000ul));
  ASSERT_TRUE(BigUint(0xfffffffffffffffful) > BigUint(0xfffffffffffffffeul));
  ASSERT_TRUE(BigUint(0xfffffffffffffffful) >= BigUint(0xfffffffffffffffeul));
  ASSERT_TRUE(BigUint(0xfffffffffffffffful) >= BigUint(0xfffffffffffffffful));

  ASSERT_FALSE(BigUint(0xfffffffffffffffful) < BigUint(0x0ul));
  ASSERT_FALSE(BigUint(0xfffffffffffffffful) <= BigUint(0x100000000ul));
  ASSERT_FALSE(BigUint(0xfffffffffffffffful) < BigUint(0xfffffffffffffffeul));
  ASSERT_FALSE(BigUint(0xfffffffffffffffful) <= BigUint(0xfffffffffffffffeul));

  ASSERT_TRUE(BigUint(0xfffffffffffffffful) == BigUint(0xfffffffffffffffful));
  ASSERT_TRUE(BigUint(0x100000000ul) == BigUint(0x100000000ul));
  ASSERT_TRUE(BigUint(0x0ul) == BigUint(0x0ul));
  ASSERT_FALSE(BigUint(0xfffffffffffffffful) == BigUint(0xfffffffffffffffeul));
  ASSERT_FALSE(BigUint(0x100000000ul) == BigUint(0xfffffffful));
  ASSERT_FALSE(BigUint(0x1ul) == BigUint(0x0ul));

  ASSERT_TRUE(BigUint(0xfffffffffffffffful) != BigUint(0xfffffffffffffffeul));
  ASSERT_TRUE(BigUint(0x100000000ul) != BigUint(0xfffffffful));
  ASSERT_TRUE(BigUint(0x1ul) != BigUint(0x0ul));
  ASSERT_FALSE(BigUint(0xfffffffffffffffful) != BigUint(0xfffffffffffffffful));
  ASSERT_FALSE(BigUint(0x100000000ul) != BigUint(0x100000000ul));
  ASSERT_FALSE(BigUint(0x0ul) != BigUint(0x0ul));
};
TEST_F(BigUintTest, OpShiftLeft) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  nat = BigUint(0x0ul) << 1;
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0x1024ul) << 1;
  ASSERT_EQ(nat.toHexadecimalString(), "0x2048");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x2048u);

  nat = BigUint(0xffffffful) << 16;
  ASSERT_EQ(nat.toHexadecimalString(), "0xfffffff0000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffff0000u);
  ASSERT_EQ(chunk.at(1), 0xfffu);

  nat = BigUint(0x4fffffful) << 22;
  ASSERT_EQ(nat.toHexadecimalString(), "0x13fffffc00000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffc00000u);
  ASSERT_EQ(chunk.at(1), 0x13fffu);

  nat = BigUint(0x4fffffful) << 54;
  ASSERT_EQ(nat.toHexadecimalString(), "0x13fffffc0000000000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0xffc00000u);
  ASSERT_EQ(chunk.at(2), 0x13fffu);

  nat <<= 8;
  ASSERT_EQ(nat.toHexadecimalString(), "0x13fffffc000000000000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0xc0000000u);
  ASSERT_EQ(chunk.at(2), 0x13fffffu);
};

TEST_F(BigUintTest, OpShiftRight) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  nat = BigUint(0x0ul) >> 1;
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);

  nat = BigUint(0x1024ul) >> 1;
  ASSERT_EQ(nat.toHexadecimalString(), "0x812");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x812u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) >> 24;
  ASSERT_EQ(nat.toHexadecimalString(), "0x1e000000000000000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0x0u);
  ASSERT_EQ(chunk.at(2), 0x1e00u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) >> 64;
  ASSERT_EQ(nat.toHexadecimalString(), "0x1e00000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0x1eu);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) >> 92;
  ASSERT_EQ(nat.toHexadecimalString(), "0x1e0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1e0u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) >> 100;
  ASSERT_EQ(nat.toHexadecimalString(), "0x1");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1u);

  nat = (BigUint(0xf000000000000ul) * BigUint(0x2000000000000ul)) >> 10;
  nat >>= 80;
  ASSERT_EQ(nat.toHexadecimalString(), "0x780");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x780u);
};

TEST_F(BigUintTest, OpAnd) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  nat = BigUint(0x1111111100000000ul) & BigUint(0x0000011100000000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x11100000000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
  ASSERT_EQ(chunk.at(1), 0x111u);

  nat = BigUint(0x1111111100001111ul) & BigUint(0x1000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x1000u);

  nat &= BigUint(0x001ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x0");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x0u);
};

TEST_F(BigUintTest, OpOr) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  nat = BigUint(0x1111111100000000ul) | BigUint(0x0000011100111000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1111111100111000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x111000u);
  ASSERT_EQ(chunk.at(1), 0x11111111u);

  nat = BigUint(0x1111111100000000ul) | BigUint(0x111ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1111111100000111");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x111u);
  ASSERT_EQ(chunk.at(1), 0x11111111u);

  nat |= BigUint(0x11111000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1111111111111111");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x11111111u);
  ASSERT_EQ(chunk.at(1), 0x11111111u);
};

TEST_F(BigUintTest, OpXor) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  nat = BigUint(0x1111111100000000ul) ^ BigUint(0x1100011100111000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x11100000111000");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x00111000u);
  ASSERT_EQ(chunk.at(1), 0x111000u);

  nat = BigUint(0x1111111100000000ul) ^ BigUint(0x111ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1111111100000111");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x111u);
  ASSERT_EQ(chunk.at(1), 0x11111111u);

  nat ^= BigUint(0x11111000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0x1111111111111111");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0x11111111u);
  ASSERT_EQ(chunk.at(1), 0x11111111u);
};

TEST_F(BigUintTest, OpCmpl) {
  BigUint nat(0);
  std::vector<uint32_t> chunk;

  nat = ~BigUint(0x1111111100000000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xeeeeeeeeffffffff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffffffffu);
  ASSERT_EQ(chunk.at(1), 0xeeeeeeeeu);

  nat = ~BigUint(0xffffffffff000000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xffffff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xffffffu);

  nat = ~BigUint(0x11111000ul);
  ASSERT_EQ(nat.toHexadecimalString(), "0xeeeeefff");
  chunk = nat.getChunks();
  ASSERT_EQ(chunk.at(0), 0xeeeeefffu);
};
