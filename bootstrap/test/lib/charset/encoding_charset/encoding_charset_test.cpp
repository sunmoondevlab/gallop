#if 0
#include "charset/encoding_charset/encoding_charset.hpp"
#include <gtest/gtest.h>
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet;

class EncodingCharsetTest : public ::testing::Test {};
TEST_F(EncodingCharsetTest, GetStringCheck) {
  EXPECT_EQ(EncodingCharset::getString(EncodingCharsetEnum::Unknown),
            "Unknown");
  EXPECT_EQ(EncodingCharset::getString(EncodingCharsetEnum::UTF32LE),
            "UTF-32 LE");
};

#endif