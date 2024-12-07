// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.

#ifndef _IO_STREAM_BYTE_ARRAY_OUTPUT_STREAM_
#define _IO_STREAM_BYTE_ARRAY_OUTPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {

class ByteArrayOutputStream {
public:
  ByteArrayOutputStream();
  ~ByteArrayOutputStream() {};
  ByteArrayOutputStream(const ByteArrayOutputStream &rhs);
  ByteArrayOutputStream &operator=(const ByteArrayOutputStream &rhs);
  void reserve(const size_t &size);
  void write(const int32_t &i32);
  void write(const int32_t &i32, const bool &isSwapEndianness);
  void write(const int16_t &i16);
  void write(const int16_t &i16, const bool &isSwapEndianness);
  void write(const char &i8);
  void write(const std::vector<int32_t> &i32v);
  void write(const std::vector<int32_t> &i32v, const bool &isSwapEndianness);
  void write(const std::vector<int16_t> &i16v);
  void write(const std::vector<int16_t> &i16v, const bool &isSwapEndianness);
  void write(const std::vector<char> &i8v);
  void reset();
  std::vector<char> data();
  std::vector<int16_t> dataByte2();
  std::vector<int32_t> dataByte4();
  size_t size() const;

private:
  std::vector<char> buffer;
  size_t bufferSize;
};
} // namespace Stream
} // namespace IO
} // namespace gallop
#endif