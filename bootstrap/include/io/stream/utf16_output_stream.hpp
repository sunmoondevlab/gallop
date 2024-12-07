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
  Utf16OutputStream(const bool &isDstLE);
  Utf16OutputStream(const bool &isSrcLE, const bool &isDstLE);
  ~Utf16OutputStream() {};
  Utf16OutputStream(const Utf16OutputStream &rhs);
  Utf16OutputStream &operator=(const Utf16OutputStream &rhs);
  void reserve(const size_t &size);
  void write(const int32_t &charCode);
  void writeString(const std::string &string);
  void reset();
  std::string toString();
  std::vector<int16_t> data();
  size_t size() const;
  size_t stringLen() const;

private:
  std::vector<int16_t> buffer;
  bool isSrcLE;
  bool isDstLE;
  size_t bufferSize;
  size_t stringLength;
};
} // namespace Stream
} // namespace IO
} // namespace gallop
#endif