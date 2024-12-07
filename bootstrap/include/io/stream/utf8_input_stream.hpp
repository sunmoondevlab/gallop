// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _IO_STREAM_UTF8_INPUT_STREAM_
#define _IO_STREAM_UTF8_INPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {
class Utf8InputStream {
public:
  Utf8InputStream();
  Utf8InputStream(const std::string &buffer);
  Utf8InputStream(const std::vector<char> &buffer);
  ~Utf8InputStream() {};
  Utf8InputStream(const Utf8InputStream &rhs);
  Utf8InputStream &operator=(const Utf8InputStream &rhs);
  std::vector<char> &dataRef();
  std::vector<char> data();
  int32_t current();
  int32_t read();
  int32_t readByte2();
  int32_t readByte3();
  int32_t readByte4();
  int32_t undo();
  int32_t ahead();
  int32_t ahead(const size_t &offset);
  void skip();
  void skip(const size_t &skipSize);
  void markCurrent();
  void markAt(const size_t &markPos);
  void resetMark();
  void rewind();
  void rewind(const size_t &rewindSize);
  void rewindToMark();
  bool hasReadable() const;
  int64_t readable() const;
  size_t size() const;
  size_t currentPos() const;

private:
  std::vector<char> buffer;
  const char *bufferPtr;
  size_t pos;
  size_t mark;
  size_t bufferSize;
  static constexpr uint32_t MaskLow1byte = 0x000000ff;
  static constexpr uint32_t MaskLow2byte = 0x0000ffff;
  static constexpr uint32_t MaskLow3byte = 0x00ffffff;
  // shift
  static constexpr int ShiftByte1 = 8;
  static constexpr int ShiftByte2 = 16;
  static constexpr int ShiftByte3 = 24;
};

} // namespace Stream
} // namespace IO
} // namespace gallop
#endif