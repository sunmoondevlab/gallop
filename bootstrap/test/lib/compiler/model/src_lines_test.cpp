// Copyright © 2024- Sunmoon development laboratory. AlsrcLines Rights Reserved.
#include "compiler/model/src_lines.hpp"
#include <gtest/gtest.h>

#include "char_set/string/utf32_string.hpp"

using namespace gallop::Compiler;
using namespace gallop::IO::Stream;

class SrcLinesTest : public ::testing::Test {};

TEST_F(SrcLinesTest, BufferOperation) {
  SrcLines srcLines;
  Utf32InputStream uis;
  std::u32string str;
  std::vector<int32_t> buf;

  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);
  ASSERT_EQ(srcLines.isContinuingInterpreter(), false);

  str = U"";
  buf = std::vector<int32_t>(str.begin(), str.end());
  srcLines.appendBuffer(buf);
  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.hasReadable(), false);
  ASSERT_EQ(uis.readable(), 0);
  ASSERT_EQ(srcLines.getLineString(1), "");
  ASSERT_EQ(srcLines.isContinuingInterpreter(), false);

  str = U"a:i32=1;\nfmain{\n exit 0;\n}\n  ";
  buf = std::vector<int32_t>(str.begin(), str.end());
  srcLines.appendBuffer(buf);
  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 29);
  ASSERT_EQ(srcLines.getLineString(1), "a:i32=1;");
  ASSERT_EQ(srcLines.getLineString(2), "fmain{");
  ASSERT_EQ(srcLines.getLineString(3), " exit 0;");
  ASSERT_EQ(srcLines.getLineString(4), "}");
  ASSERT_EQ(srcLines.getLineString(5), "  ");
  ASSERT_EQ(srcLines.getLinesCount(), 5ul);
  ASSERT_EQ(srcLines.isContinuingInterpreter(), false);

  str = U"/#\r//\r\n// \n// コメントアウト\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  srcLines.appendBuffer(buf);
  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.hasReadable(), true);
  ASSERT_EQ(uis.readable(), 22);
  ASSERT_EQ(srcLines.getLineString(1), "a:i32=1;");
  ASSERT_EQ(srcLines.getLineString(2), "fmain{");
  ASSERT_EQ(srcLines.getLineString(3), " exit 0;");
  ASSERT_EQ(srcLines.getLineString(4), "}");
  ASSERT_EQ(srcLines.getLineString(5), "  /#");
  ASSERT_EQ(srcLines.getLineString(6), "//");
  ASSERT_EQ(srcLines.getLineString(7), "// ");
  ASSERT_EQ(srcLines.getLineString(8), "// コメントアウト");
  ASSERT_EQ(srcLines.getLineString(9), "");
  ASSERT_EQ(srcLines.getLinesCount(), 9ul);
  ASSERT_EQ(srcLines.isContinuingInterpreter(), true);

  str = U"\n fn nop(){}\n";
  buf = std::vector<int32_t>(str.begin(), str.end());
  srcLines.appendBuffer(buf);
  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.readable(), 13);
  ASSERT_EQ(srcLines.getLineString(1), "a:i32=1;");
  ASSERT_EQ(srcLines.getLineString(2), "fmain{");
  ASSERT_EQ(srcLines.getLineString(3), " exit 0;");
  ASSERT_EQ(srcLines.getLineString(4), "}");
  ASSERT_EQ(srcLines.getLineString(5), "  /#");
  ASSERT_EQ(srcLines.getLineString(6), "//");
  ASSERT_EQ(srcLines.getLineString(7), "// ");
  ASSERT_EQ(srcLines.getLineString(8), "// コメントアウト");
  ASSERT_EQ(srcLines.getLineString(9), "");
  ASSERT_EQ(srcLines.getLineString(10), " fn nop(){}");
  ASSERT_EQ(srcLines.getLineString(11), "");
  ASSERT_EQ(srcLines.getLinesCount(), 11ul);
  ASSERT_EQ(srcLines.isContinuingInterpreter(), true);

  srcLines.shrinkBuffer(63);
  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.readable(), 12);
  ASSERT_EQ(srcLines.getLineString(11), "");
  ASSERT_EQ(srcLines.getLinesCount(), 10ul);
  ASSERT_EQ(srcLines.isContinuingInterpreter(), true);

  srcLines.shrinkBuffer(58);
  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.readable(), 7);
  ASSERT_EQ(srcLines.getLineString(10), " fn no");
  ASSERT_EQ(srcLines.getLinesCount(), 10ul);
  ASSERT_EQ(srcLines.isContinuingInterpreter(), true);

  srcLines.shrinkBuffer(49);
  uis = srcLines.createUtf32InputStream();
  ASSERT_EQ(uis.readable(), 0);
  ASSERT_EQ(srcLines.getLineString(8), "// コメントアウ");
  ASSERT_EQ(srcLines.getLinesCount(), 8ul);

  srcLines.shrinkBuffer(35);
  ASSERT_EQ(srcLines.getLineString(6), "//");
  ASSERT_EQ(srcLines.getLineString(7), "");
  ASSERT_EQ(srcLines.getLinesCount(), 6ul);

  srcLines.shrinkBuffer(32);
  ASSERT_EQ(srcLines.getLineString(6), "");
  ASSERT_EQ(srcLines.getLinesCount(), 6ul);

  srcLines.shrinkBuffer(9);
  ASSERT_EQ(srcLines.getLineString(2), "");
  ASSERT_EQ(srcLines.getLinesCount(), 2ul);

  srcLines.shrinkBuffer(7);
  ASSERT_EQ(srcLines.getLineString(1), "a:i32=1");
  ASSERT_EQ(srcLines.getLineString(2), "");
  ASSERT_EQ(srcLines.getLinesCount(), 1ul);

  srcLines.resetBuffer();
  ASSERT_EQ(srcLines.getLineString(1), "");
  ASSERT_EQ(srcLines.getLinesCount(), 0ul);
  ASSERT_EQ(srcLines.isContinuingInterpreter(), false);

  srcLines = SrcLines("a.trot");
  ASSERT_EQ(srcLines.getFilename(), "a.trot");
  ASSERT_EQ(srcLines.isContinuingInterpreter(), false);
};
