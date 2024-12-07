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
  Utf32OutputStream(const bool &isDstLE);
  Utf32OutputStream(const bool &isSrcLE, const bool &isDstLE);
  ~Utf32OutputStream() {};
  Utf32OutputStream(const Utf32OutputStream &rhs);
  Utf32OutputStream &operator=(const Utf32OutputStream &rhs);
  void reserve(const size_t &size);
  void write(const int32_t &charCode);
  void writeString(const std::string &string);
  void reset();
  std::string toString();
  std::vector<int32_t> data();
  size_t size() const;
  size_t stringLen() const;

private:
  std::vector<int32_t> buffer;
  bool isSrcLE;
  bool isDstLE;
  size_t bufferSize;
  size_t stringLength;
};
} // namespace Stream
} // namespace IO
} // namespace gallop
#endif