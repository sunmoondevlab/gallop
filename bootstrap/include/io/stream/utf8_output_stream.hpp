// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.

#ifndef _IO_STREAM_UTF8_OUTPUT_STREAM_
#define _IO_STREAM_UTF8_OUTPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {

class Utf8OutputStream {
public:
  Utf8OutputStream();
  ~Utf8OutputStream() {};
  Utf8OutputStream(const Utf8OutputStream &rhs);
  Utf8OutputStream &operator=(const Utf8OutputStream &rhs);
  void reserve(const size_t &size);
  void write(const int32_t &charCode);
  void writeString(const std::string &string);
  void reset();
  std::string toString();
  std::vector<char> data();
  size_t size() const;
  size_t stringLen() const;

private:
  std::vector<char> buffer;
  size_t bufferSize;
  size_t stringLength;
};
} // namespace Stream
} // namespace IO
} // namespace gallop
#endif