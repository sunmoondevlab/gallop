// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/byte_array_output_stream.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

ByteArrayOutputStream::ByteArrayOutputStream()
    : buffer(std::vector<char>()), bufferSize(0) {};
ByteArrayOutputStream::ByteArrayOutputStream(const ByteArrayOutputStream &rhs)
    : buffer(rhs.buffer), bufferSize(rhs.bufferSize) {};

ByteArrayOutputStream &
ByteArrayOutputStream::operator=(const ByteArrayOutputStream &rhs) {
  buffer = rhs.buffer;
  bufferSize = rhs.bufferSize;
  return *this;
};
void ByteArrayOutputStream::reserve(const size_t &size_) {
  buffer.reserve(size_);
};
void ByteArrayOutputStream::write(const int32_t &i32_) {
  return write(i32_, false);
};
void ByteArrayOutputStream::write(const int32_t &i32_,
                                  const bool &isSwapEndianness_) {
  uint32_t u32 = (uint32_t)i32_;
  if (isSwapEndianness_) {
    buffer.push_back((char)(u32 & MaskU32Low1Byte));
    buffer.push_back((char)((u32 >> ShiftByte1) & MaskU32Low1Byte));
    buffer.push_back((char)((u32 >> ShiftByte2) & MaskU32Low1Byte));
    buffer.push_back((char)(u32 >> ShiftByte3));
  } else {
    buffer.push_back((char)(u32 >> ShiftByte3));
    buffer.push_back((char)((u32 >> ShiftByte2) & MaskU32Low1Byte));
    buffer.push_back((char)((u32 >> ShiftByte1) & MaskU32Low1Byte));
    buffer.push_back((char)(u32 & MaskU32Low1Byte));
  }
  bufferSize += 4;
};
void ByteArrayOutputStream::write(const int16_t &i16_) {
  return write(i16_, false);
};
void ByteArrayOutputStream::write(const int16_t &i16_,
                                  const bool &isSwapEndianness_) {
  uint16_t u16 = (uint16_t)i16_;
  if (isSwapEndianness_) {
    buffer.push_back((char)(u16 & MaskU16Low1Byte));
    buffer.push_back((char)((u16 >> ShiftByte1) & MaskU16Low1Byte));
  } else {
    buffer.push_back((char)((u16 >> ShiftByte1) & MaskU16Low1Byte));
    buffer.push_back((char)(u16 & MaskU16Low1Byte));
  }
  bufferSize += 2;
};
void ByteArrayOutputStream::write(const char &i8_) {
  buffer.push_back(i8_);
  bufferSize++;
};
void ByteArrayOutputStream::write(const std::vector<int32_t> &i32v_) {
  return write(i32v_, false);
};
void ByteArrayOutputStream::write(const std::vector<int32_t> &i32v_,
                                  const bool &isSwapEndianness_) {
  size_t i32vSize = i32v_.size();
  const int32_t *i32vData = i32v_.data();
  for (size_t pos = 0; pos < i32vSize; pos++) {
    write(*(i32vData + pos), isSwapEndianness_);
  }
};
void ByteArrayOutputStream::write(const std::vector<int16_t> &i16v_) {
  return write(i16v_, false);
};
void ByteArrayOutputStream::write(const std::vector<int16_t> &i16v_,
                                  const bool &isSwapEndianness_) {
  size_t i16vSize = i16v_.size();
  const int16_t *i16vData = i16v_.data();
  for (size_t pos = 0; pos < i16vSize; pos++) {
    write(*(i16vData + pos), isSwapEndianness_);
  }
};
void ByteArrayOutputStream::write(const std::vector<char> &i8v_) {
  size_t i8vSize = i8v_.size();
  const char *i8vData = i8v_.data();
  for (size_t pos = 0; pos < i8vSize; pos++) {
    write(*(i8vData + pos));
  }
};
void ByteArrayOutputStream::reset() {
  buffer.clear();
  bufferSize = 0;
};
std::vector<char> ByteArrayOutputStream::data() { return buffer; };
std::vector<int16_t> ByteArrayOutputStream::dataByte2() {
  size_t byte2DataSize = buffer.size();
  if ((byte2DataSize % 2) > 0) {
    byte2DataSize = (byte2DataSize + 1) / 2;
  } else {
    byte2DataSize = byte2DataSize / 2;
  }
  std::vector<int16_t> byte2data;
  byte2data.reserve(byte2DataSize);
  const char *bufferDataPtr = buffer.data();
  for (size_t pos = 0, bPos = 0; pos < byte2DataSize; pos++, bPos += 2) {
    uint16_t elm =
        (((uint16_t)*(bufferDataPtr + bPos)) << ShiftByte1) & MaskU16High1Byte;
    if (bPos + 1 < bufferSize) {
      elm |= ((uint16_t)(*(bufferDataPtr + bPos + 1)) & MaskU16Low1Byte);
    }
    byte2data.push_back((int16_t)elm);
  }
  return byte2data;
};
std::vector<int32_t> ByteArrayOutputStream::dataByte4() {
  size_t byte4DataSize = buffer.size();
  if ((byte4DataSize % 4) > 0) {
    byte4DataSize = (byte4DataSize + 3) / 4;
  } else {
    byte4DataSize = byte4DataSize / 4;
  }
  std::vector<int32_t> byte4data;
  byte4data.reserve(byte4DataSize);
  const char *bufferDataPtr = buffer.data();
  for (size_t pos = 0, bPos = 0; pos < byte4DataSize; pos++, bPos += 4) {
    uint32_t elm =
        (((uint32_t)*(bufferDataPtr + bPos)) << ShiftByte3) & MaskU32High1Byte;
    if (bPos + 1 < bufferSize) {
      elm |= (((uint32_t)(*(bufferDataPtr + bPos + 1)) & MaskU32Low1Byte)
              << ShiftByte2);
    }
    if (bPos + 2 < bufferSize) {
      elm |= (((uint32_t)(*(bufferDataPtr + bPos + 2)) & MaskU32Low1Byte)
              << ShiftByte1);
    }
    if (bPos + 3 < bufferSize) {
      elm |= ((uint32_t)(*(bufferDataPtr + bPos + 3)) & MaskU32Low1Byte);
    }
    byte4data.push_back((int32_t)elm);
  }
  return byte4data;
};
size_t ByteArrayOutputStream::size() const { return bufferSize; };
