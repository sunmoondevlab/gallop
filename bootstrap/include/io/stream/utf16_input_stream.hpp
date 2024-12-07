// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.

#ifndef _IO_STREAM_UTF16_INPUT_STREAM_
#define _IO_STREAM_UTF16_INPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {
class Utf16InputStream {
public:
  Utf16InputStream();
  Utf16InputStream(const std::vector<char> &buffer);
  Utf16InputStream(const std::vector<int16_t> &buffer);
  ~Utf16InputStream() {};
  Utf16InputStream(const Utf16InputStream &rhs);
  Utf16InputStream &operator=(const Utf16InputStream &rhs);
  std::vector<int16_t> data();
  int16_t current();
  int16_t read();
  int32_t readByte4();
  std::vector<int16_t> readChunk(const size_t &chunkSize,
                                 const bool &isForward);
  std::vector<int16_t> readChunk(const size_t &chunkSize);
  int16_t undo();
  int16_t ahead();
  int16_t ahead(const size_t &offset);
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

private:
  std::vector<int16_t> buffer;
  const int16_t *bufferPtr;
  size_t pos;
  size_t mark;
  std::vector<int16_t> toByte2Buffer(const std::vector<char> &buffer);
  size_t bufferSize;
};

} // namespace Stream
} // namespace IO
} // namespace gallop
#endif