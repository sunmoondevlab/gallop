// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.

#ifndef _IO_STREAM_BYTE_ARRAY_INPUT_STREAM_
#define _IO_STREAM_BYTE_ARRAY_INPUT_STREAM_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace IO {
namespace Stream {
class ByteArrayInputStream {
public:
  ByteArrayInputStream();
  ByteArrayInputStream(const std::string &buffer);
  ByteArrayInputStream(const std::vector<char> &buffer);
  ~ByteArrayInputStream() {};
  ByteArrayInputStream(const ByteArrayInputStream &rhs);
  ByteArrayInputStream &operator=(const ByteArrayInputStream &rhs);
  std::vector<char> data();
  char current();
  char read();
  int16_t readByte2();
  int32_t readByte3();
  int32_t readByte4();
  std::vector<char> readChunk(const size_t &chunkSize, const bool &isForward);
  std::vector<char> readChunk(const size_t &chunkSize);
  char undo();
  char ahead();
  char ahead(const size_t &offset);
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
  std::vector<char> buffer;
  const char *bufferPtr;
  size_t pos;
  size_t mark;
  size_t bufferSize;
};

} // namespace Stream
} // namespace IO
} // namespace gallop
#endif