// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "charset/encoding_charset/encoding_charset.hpp"
#include <gtest/gtest.h>
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet;

class EncodingCharsetTest : public ::testing::Test {};
TEST_F(EncodingCharsetTest, GetString) {
  ASSERT_EQ(
      EncodingCharset::getString(EncodingCharsetEnum::InvalidTextEncoding),
      "Invalid text encoding charset");
  ASSERT_EQ(EncodingCharset::getString(EncodingCharsetEnum::Unknown),
            "Unknown");
  ASSERT_EQ(EncodingCharset::getString(EncodingCharsetEnum::UTF32LE),
            "UTF-32 LE");
};
