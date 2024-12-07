#if 0
#include "charset/detector/detector.hpp"
#include <gtest/gtest.h>
#include <llvm/Support/raw_ostream.h>

using namespace gallop::CharSet;

class DetectorTest : public ::testing::Test {};
TEST(DetectorTest, DetectUTFWithBOM) {
  // Detector d;
  // UTF-32BE
  std::vector<char> buf{
      /*BOM end*/ static_cast<char>(0xff),
      static_cast<char>(0xfe),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      /*BOM end*/ static_cast<char>(0x20),
      static_cast<char>(0x21),
      static_cast<char>(0x00),
      static_cast<char>(0x00),
  };
  Detector d(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF32LE_BOM);
  // UTF-32LE
  buf = {
      /*BOM start*/ static_cast<char>(0x00),
      static_cast<char>(0x00),
      static_cast<char>(0xfe),
      static_cast<char>(0xff),
      /*BOM end*/
      static_cast<char>(0x00),
      static_cast<char>(0x00),
      static_cast<char>(0x21),
      static_cast<char>(0x20),
  };
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF32BE_BOM);
  // UTF-7
  std::string bufStr = "+/v8wQg"; // あ
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);

  bufStr = "+/v9AAA"; // 䀀
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);

  bufStr = "+/v+QAA"; // 退
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);

  bufStr = "+/v/pq5kK"; // 髙
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);

  bufStr = "+/v8";
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);

  // UTF-8
  buf = {
      /*BOM start*/ static_cast<char>(0xef),
      static_cast<char>(0xbb),
      static_cast<char>(0xbf), /*BOM end*/
      static_cast<char>(0x61),
      static_cast<char>(0xe3),
      static_cast<char>(0x81),
      static_cast<char>(0x82),
      static_cast<char>(0x0a),
  };
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF8_BOM);
  // UTF-16
  // UTF-16BE
  buf = {
      /*BOM end*/ static_cast<char>(0xff),
      static_cast<char>(0xfe),
      /*BOM end*/ static_cast<char>(0x20),
      static_cast<char>(0x21),
  };
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF16LE_BOM);
  // UTF-16LE
  buf = {
      /*BOM start*/ static_cast<char>(0xfe),
      static_cast<char>(0xff),
      /*BOM end*/
      static_cast<char>(0x21),
      static_cast<char>(0x20),
  };
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF16BE_BOM);
};

// TEST(DetectorTest, DetectUtf7) {
//   // ASCII
//   std::string bufStr = "+/v/";
//   std::vector<char> buf;
//   std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
//   Detector d = Detector(buf);
//   EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::ASCII);

//   bufStr = "+/v8A";
//   buf.clear();
//   std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
//   d = Detector(buf);
//   EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::ASCII);
//   EXPECT_EQ(d.getRuneCount(), 5ul);

//   bufStr = "+/v9-";
//   buf.clear();
//   std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
//   d = Detector(buf);
//   EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::ASCII);
//   EXPECT_EQ(d.getRuneCount(), 5ul);

//   bufStr = "+/v/jgYLkgIDpgIAg-afewahui";
//   buf.clear();
//   std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
//   d = Detector(buf);
//   EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);
//   EXPECT_EQ(d.getRuneCount(), 12ul);

//   bufStr = "+/v8CgA\n+\n\r+44GCCjAA-";
//   buf.clear();
//   std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
//   d = Detector(buf);
//   EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);
//   EXPECT_EQ(d.getRuneCount(), 7ul);

//   bufStr = "+/v8CgA\n+\n\r+44GCCjAA-A-Za-z0-9'(),-./:?!\"#$%&*;<=>@[]^_`{|}";
//   buf.clear();
//   std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
//   d = Detector(buf);
//   EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);
//   EXPECT_EQ(d.getRuneCount(), 45ul);
// };

TEST(DetectorTest, Detect7BitChar) {
  // ASCII
  std::string bufStr = "\t\r\n 0a~";
  std::vector<char> buf;
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  Detector d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::ASCII);

  // UTF-7

  //   bufStr = "\t\r\n 0a+MEJAAJAAmtk-a\n+/ws-s"; // 0aあ䀀退髙\n＋s
  //   buf.clear();
  //   std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //   EncodingCharsetEnum::ASCII);
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF7);

  //   // UTF-7 for IMAP
  //   std::vector<char> buf;
  //   buf = {
  //       static_cast<char>(0x09), static_cast<char>(0x0a),
  //       static_cast<char>(0x0d), static_cast<char>(0x20),
  //       static_cast<char>(0x31), static_cast<char>(0x41),
  //       static_cast<char>(0x61), static_cast<char>(0x20),
  //       static_cast<char>(0x2b), static_cast<char>(0x4d),
  //       static_cast<char>(0x45), static_cast<char>(0x49),
  //       static_cast<char>(0x41), static_cast<char>(0x4b),
  //       static_cast<char>(0x77), static_cast<char>(0x2d),
  //       static_cast<char>(0x61), static_cast<char>(0x26),
  //       static_cast<char>(0x2d),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::UTF7_IMAP);

  //   // UTF-7
  //   buf = {
  //       static_cast<char>(0x09), static_cast<char>(0x0a),
  //       static_cast<char>(0x0d), static_cast<char>(0x20),
  //       static_cast<char>(0x31), static_cast<char>(0x41),
  //       static_cast<char>(0x61), static_cast<char>(0x20),
  //       static_cast<char>(0x2b), static_cast<char>(0x4d),
  //       static_cast<char>(0x45), static_cast<char>(0x49),
  //       static_cast<char>(0x41), static_cast<char>(0x4b),
  //       static_cast<char>(0x77), static_cast<char>(0x61),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //   EncodingCharsetEnum::ASCII);

  //   // UTF-7 for IMAP
  //   buf = {
  //       static_cast<char>(0x09), static_cast<char>(0x0a),
  //       static_cast<char>(0x0d), static_cast<char>(0x20),
  //       static_cast<char>(0x31), static_cast<char>(0x41),
  //       static_cast<char>(0x61), static_cast<char>(0x20),
  //       static_cast<char>(0x2b), static_cast<char>(0x77),
  //       static_cast<char>(0x4d), static_cast<char>(0x61),
  //       static_cast<char>(0x26), static_cast<char>(0x4d),
  //       static_cast<char>(0x4d), static_cast<char>(0x45),
  //       static_cast<char>(0x49), static_cast<char>(0x41),
  //       static_cast<char>(0x4b), static_cast<char>(0x61),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //   EncodingCharsetEnum::ASCII);

  //   // Unknown
  //   std::vector<char> buf;
  //   buf = {static_cast<char>(0x00),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0x80),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0x01),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0x08),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0x0b),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0x0c),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0x0e),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0x1f),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
  //   buf = {static_cast<char>(0xff),};
  //   d=Detector(buf);
  // EXPECT_EQ(d.getEncodingCharset(),
  //             EncodingCharsetEnum::Unknown);
};

TEST(DetectorTest, DetectUtf8Char) {
  // ASCII
  std::string bufStr = "09AZaz\t\r\n !/:@[`{~";
  std::vector<char> buf;
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  Detector d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::ASCII);

  bufStr = "ÀÿĀǿȀ˿Ͽӿߺ";
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF8);

  bufStr = "ࠀऀကჿ ⮕、䀀鿿ꀀퟻ豈﫿ﬀ￯";
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF8);

  bufStr = "𐀀𐃺𠀀鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf";
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF8);

  bufStr =
      "09ÀÿĀAZazࠀऀကჿ ⮕、𐀀𐃺𠀀\t\r\n "
      "鼻𰻝𱁬\xf4\x80\x80\x80\xf4\x8f\xbf\xbf䀀鿿ꀀퟻ豈﫿ﬀ"
      "￯"
      "!"
      "ǿȀ˿Ͽӿߺ/"
      ":@[`{~";
  buf.clear();
  std::copy(bufStr.begin(), bufStr.end(), std::back_inserter(buf));
  d = Detector(buf);
  EXPECT_EQ(d.getEncodingCharset(), EncodingCharsetEnum::UTF8);
};

#endif