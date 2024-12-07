// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _IO_STREAM_UTF32_OUTPUT_STREAM_
#define _IO_STREAM_UTF32_OUTPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {

class Utf32OutputStream {
public:
  Utf32OutputStream();
  Utf32OutputStream(const bool &isDstLe);
  Utf32OutputStream(const bool &isSrcLe, const bool &isDstLe);
  ~Utf32OutputStream() {};
  Utf32OutputStream(const Utf32OutputStream &rhs);
  Utf32OutputStream &operator=(const Utf32OutputStream &rhs);
  void reserve(const size_t &size);
  void write(const int32_t &charCode);
  void writeBom();
  void writeReplacementChar();
  void writeString(const std::u32string &u32string);
  void reset();
  std::u32string toU32String();
  std::vector<int32_t> data();
  size_t size() const;
  size_t stringLen() const;

private:
  std::vector<int32_t> buffer;
  bool isSrcLe;
  bool isDstLe;
  size_t bufferSize;
  size_t stringLength;
};
} // namespace Stream
} // namespace IO
} // namespace gallop
#endif