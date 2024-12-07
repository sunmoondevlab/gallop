// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _IO_STREAM_UTF32_INPUT_STREAM_
#define _IO_STREAM_UTF32_INPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {
class Utf32InputStream {
public:
  Utf32InputStream();
  Utf32InputStream(const std::u32string &buffer);
  Utf32InputStream(const std::vector<char> &buffer);
  Utf32InputStream(const std::vector<int32_t> &buffer);
  ~Utf32InputStream() {};
  Utf32InputStream(const Utf32InputStream &rhs);
  Utf32InputStream &operator=(const Utf32InputStream &rhs);
  std::vector<int32_t> &dataRef();
  std::vector<int32_t> data();
  int32_t current();
  int32_t read();
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
  std::vector<int32_t> buffer;
  const int32_t *bufferPtr;
  size_t pos;
  size_t mark;
  std::vector<int32_t> toByte4Buffer(const std::vector<char> &buffer);
  size_t bufferSize;
  // mask
  static constexpr uint32_t MaskHighestByte = 0xff000000;
  static constexpr uint32_t MaskLoe1Byte = 0x000000ff;
  // shift byte
  static constexpr int Shift3Byte = 24;
  static constexpr int Shift2Byte = 16;
  static constexpr int Shift1Byte = 8;
};

} // namespace Stream
} // namespace IO
} // namespace gallop
#endif