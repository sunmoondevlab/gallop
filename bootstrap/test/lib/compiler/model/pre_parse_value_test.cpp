// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/pre_parse_value.hpp"
#include <gtest/gtest.h>

using namespace gallop::Compiler;

class PreParseValueTest : public ::testing::Test {};

TEST_F(PreParseValueTest, None) {
  PreParseValue ppv;
  ASSERT_EQ(ppv.escapeUtf32CharCode(), nullptr);
};

TEST_F(PreParseValueTest, CharCode) {
  PreParseValue ppv(static_cast<int32_t>(U'\n'));
  ASSERT_EQ(*(ppv.escapeUtf32CharCode()), static_cast<int32_t>(U'\n'));

  ppv = PreParseValue(static_cast<int32_t>(U'鼻'));
  ASSERT_EQ(*(ppv.escapeUtf32CharCode()), static_cast<int32_t>(U'鼻'));

  ppv = PreParseValue(static_cast<int32_t>(0x0010ffff));
  ASSERT_EQ(*(ppv.escapeUtf32CharCode()), static_cast<int32_t>(0x0010ffff));
};
