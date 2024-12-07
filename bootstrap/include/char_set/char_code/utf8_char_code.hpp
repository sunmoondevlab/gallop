// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHAR_SET_CHAR_CODE_UTF8_
#define _CHAR_SET_CHAR_CODE_UTF8_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace CharCode {

class Utf8 {
public:
  Utf8() = delete;
  ~Utf8() = delete;
  static bool isNullCharCode(const char &charCode);
  static bool isBom(const int32_t &charCode);
  static int32_t utf8FetchLength(const char &charCode);
  static bool isContinuationByte(const char &charCode);
  static bool isLineBreak(const char &charCode);
  static bool isLineFeed(const char &charCode);
  static bool isCarriageReturn(const char &charCode);
  static bool isAscii(const char &charCode);
  static bool isValidCharCode(const int32_t &charCode);
  static std::vector<char> getBomChunk();
  static std::vector<char> getReplacementCharChunk();
  static std::vector<char> toU8(const int32_t &charCode);
  static std::vector<int16_t> toU16(const int32_t &charCode);
  static std::vector<int16_t> toU16(const int32_t &charCode,
                                    const bool &isDstLe);
  static int32_t toU32(const int32_t &charCode);
  static int32_t toU32(const int32_t &charCode, const bool &isDstLe);
  static std::string toU8String(const int32_t &charCode);
  static std::u16string toU16String(const int32_t &charCode);
  static std::u32string toU32String(const int32_t &charCode);

private:
  // BOM
  static constexpr uint32_t BomCode = 0x00efbbbf;
  // BOM for ToU8
  static const char BomCharCode0 = 0xef;
  static const char BomCharCode1 = 0xbb;
  static const char BomCharCode2 = 0xbf;
  // Replacement Char for ToU8
  static const char ReplacementCharCode0 = 0xef;
  static const char ReplacementCharCode1 = 0xbf;
  static const char ReplacementCharCode2 = 0xbd;
  // for fetch
  static constexpr uint8_t HighestChar4ByteMax = 0xf4;
  static constexpr uint8_t HighestChar4ByteMin = 0xf0;
  static constexpr uint8_t HighestChar3ByteMax = 0xef;
  static constexpr uint8_t HighestChar3ByteMin = 0xe0;
  static constexpr uint8_t HighestChar2ByteMax = 0xdf;
  static constexpr uint8_t HighestChar2ByteMin = 0xc2;
  static constexpr uint8_t AsciiByteMax = 0x7f;
  static constexpr uint8_t AsciiByteMin = 0x00;
  static constexpr uint8_t ContinuationByteMax = 0xbf;
  static constexpr uint8_t ContinuationByteMin = 0x80;
  // mask for valid
  static constexpr uint32_t WeaklyMask4byteCode = 0xff000000;
  static constexpr uint32_t StrictMask4byteCode = 0xf8000000;
  static constexpr uint32_t ActualBit4byteCode = 0xf0000000;
  static constexpr uint32_t WeaklyMask3byteCode = 0xffff0000;
  static constexpr uint32_t StrictMask3byteCode = 0xfff00000;
  static constexpr uint32_t ActualBit3byteCode = 0x00e00000;
  static constexpr uint32_t WeaklyMask2byteCode = 0xffffff00;
  static constexpr uint32_t StrictMask2byteCode = 0xffffe000;
  static constexpr uint32_t ActualBit2byteCode = 0x0000c000;
  static constexpr uint32_t MaskNon1byteCode = 0xffffff80;
  static constexpr uint32_t ActualBit1byteCode = 0x00000000;
  static constexpr uint32_t MaskContinuationByte3 = 0x00c00000;
  static constexpr uint32_t ActualBitContinuationByte3 = 0x00800000;
  static constexpr uint32_t MaskContinuationByte2 = 0x0000c000;
  static constexpr uint32_t ActualBitContinuationByte2 = 0x00008000;
  static constexpr uint32_t MaskContinuationByte1 = 0x000000c0;
  static constexpr uint32_t ActualBitContinuationByte1 = 0x00000080;
  static constexpr uint32_t CharCode4ByteMax = 0xf48fbfbf;
  static constexpr uint32_t CharCode4ByteMin = 0xf0908080;
  static constexpr uint32_t CharCode3ByteMin = 0x00e0a080;
  static constexpr uint32_t CharCode3SurrogateByteMax = 0x00edbfbf;
  static constexpr uint32_t CharCode3SurrogateByteMin = 0x00eda080;
  static constexpr uint32_t CharCode2ByteMin = 0x0000c280;
  // mask for toU32
  static constexpr uint32_t ToU32CodePointMaskHighest4 = 0x07000000;
  static constexpr uint32_t ToU32CodePointMaskHighest3 = 0x000f0000;
  static constexpr uint32_t ToU32CodePointMaskHighest2 = 0x00001f00;
  static constexpr uint32_t ToU32CodePointMaskContinuation3 = 0x003f0000;
  static constexpr uint32_t ToU32CodePointMaskContinuation2 = 0x00003f00;
  static constexpr uint32_t ToU32CodePointMaskContinuation1 = 0x0000003f;
  // shift for toU32
  static constexpr int ToU32BitShift4 = 6;
  static constexpr int ToU32BitShift3 = 4;
  static constexpr int ToU32BitShift2 = 2;
  // mask for toU8
  static constexpr uint8_t ToU8CodePointMask1 = 0xff;
  // shift for toU8
  static constexpr int ToU8ByteShift3 = 24;
  static constexpr int ToU8ByteShift2 = 16;
  static constexpr int ToU8ByteShift1 = 8;
};

} // namespace CharCode
} // namespace CharSet
} // namespace gallop
#endif