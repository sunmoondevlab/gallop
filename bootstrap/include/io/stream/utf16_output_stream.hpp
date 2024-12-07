// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _IO_STREAM_UTF16_OUTPUT_STREAM_
#define _IO_STREAM_UTF16_OUTPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {

class Utf16OutputStream {
public:
  Utf16OutputStream();
  Utf16OutputStream(const bool &isDstLe);
  Utf16OutputStream(const bool &isSrcLe, const bool &isDstLe);
  ~Utf16OutputStream() {};
  Utf16OutputStream(const Utf16OutputStream &rhs);
  Utf16OutputStream &operator=(const Utf16OutputStream &rhs);
  void reserve(const size_t &size);
  void write(const int32_t &charCode);
  void writeBom();
  void writeReplacementChar();
  void writeString(const std::u16string &u16string);
  void reset();
  std::u16string toU16String();
  std::vector<int16_t> data();
  size_t size() const;
  size_t stringLen() const;

private:
  std::vector<int16_t> buffer;
  bool isSrcLe;
  bool isDstLe;
  size_t bufferSize;
  size_t stringLength;
};
} // namespace Stream
} // namespace IO
} // namespace gallop
#endif