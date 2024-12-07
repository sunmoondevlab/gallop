// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/byte_array_input_stream.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "charset/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

ByteArrayInputStream::ByteArrayInputStream()
    : buffer(std::vector<char>()), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(0) {};
ByteArrayInputStream::ByteArrayInputStream(const std::string &buffer_)
    : buffer(std::vector<char>(buffer_.begin(), buffer_.end())),
      bufferPtr(buffer.data()), pos(0), mark(0), bufferSize(buffer.size()) {};
ByteArrayInputStream::ByteArrayInputStream(const std::vector<char> &buffer_)
    : buffer(buffer_), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
ByteArrayInputStream::ByteArrayInputStream(const ByteArrayInputStream &rhs)
    : buffer(rhs.buffer), bufferPtr(buffer.data()), pos(rhs.pos),
      mark(rhs.mark), bufferSize(rhs.bufferSize) {};
ByteArrayInputStream &
ByteArrayInputStream::operator=(const ByteArrayInputStream &rhs) {
  buffer = rhs.buffer;
  bufferPtr = buffer.data();
  pos = rhs.pos;
  mark = rhs.mark;
  bufferSize = rhs.bufferSize;
  return *this;
};
std::vector<char> ByteArrayInputStream::data() { return buffer; };
char ByteArrayInputStream::current() {
  if (hasReadable()) {
    char chr = *(bufferPtr + (pos));
    return chr;
  }
  return '\0';
};
char ByteArrayInputStream::read() {
  if (hasReadable()) {
    char chr = *(bufferPtr + (pos));
    pos++;
    return chr;
  }
  return '\0';
};
int16_t ByteArrayInputStream::readByte2() {
  if (readable() >= 2) {
    uint16_t readI16 = 0;
    char chr = *(bufferPtr + (pos));
    pos++;
    readI16 = ((uint16_t)(chr << 8) & static_cast<uint16_t>(0x0000ffff));
    chr = *(bufferPtr + (pos));
    pos++;
    readI16 |= ((uint16_t)(chr) & static_cast<uint16_t>(0x000000ff));
    return (int16_t)readI16;
  }
  return static_cast<int16_t>(0);
};
int32_t ByteArrayInputStream::readByte3() {
  if (readable() >= 3) {
    uint32_t readI24 = 0;
    char chr = *(bufferPtr + (pos));
    pos++;
    readI24 = ((uint32_t)(chr << 16) & static_cast<uint32_t>(0x00ffffff));
    chr = *(bufferPtr + (pos));
    pos++;
    readI24 |= (((uint32_t)(chr) & static_cast<uint32_t>(0x000000ff)) << 8);
    chr = *(bufferPtr + (pos));
    pos++;
    readI24 |= ((uint32_t)(chr) & static_cast<uint32_t>(0x000000ff));
    return (int32_t)readI24;
  }
  return static_cast<int32_t>(0);
};
int32_t ByteArrayInputStream::readByte4() {
  if (readable() >= 4) {
    uint32_t readI32 = 0;
    char chr = *(bufferPtr + (pos));
    pos++;
    readI32 = (uint32_t)(chr << 24);
    chr = *(bufferPtr + (pos));
    pos++;
    readI32 |= (((uint32_t)(chr) & static_cast<uint32_t>(0x000000ff)) << 16);
    chr = *(bufferPtr + (pos));
    pos++;
    readI32 |= (((uint32_t)(chr) & static_cast<uint32_t>(0x000000ff)) << 8);
    chr = *(bufferPtr + (pos));
    pos++;
    readI32 |= ((uint32_t)(chr) & static_cast<uint32_t>(0x000000ff));
    return (int32_t)readI32;
  }
  return static_cast<int32_t>(0);
};

std::vector<char> ByteArrayInputStream::readChunk(const size_t &chunkSize_) {
  return readChunk(chunkSize_, false);
};
std::vector<char> ByteArrayInputStream::readChunk(const size_t &chunkSize_,
                                                  const bool &isForward_) {
  size_t chunkSize = chunkSize_;
  size_t readableSize = readable();
  if (readableSize < chunkSize) {
    chunkSize = readableSize;
  }
  std::vector<char> chunk;
  if (chunkSize > 0) {
    std::copy(buffer.begin() + pos, buffer.begin() + pos + chunkSize,
              std::back_inserter(chunk));
    if (isForward_) {
      pos += chunkSize;
    }
  }
  return chunk;
};
char ByteArrayInputStream::undo() {
  if (pos == 0) {
    return '\0';
  }
  pos--;
  return *(bufferPtr + (pos));
};
char ByteArrayInputStream::ahead() {
  if (readable() > 1) {
    return *(bufferPtr + (pos + 1));
  };
  return '\0';
};
char ByteArrayInputStream::ahead(const size_t &offset_) {
  if (readable() > (int64_t)(1 + offset_)) {
    return *(bufferPtr + (pos + 1 + offset_));
  };
  return '\0';
};
void ByteArrayInputStream::skip() {
  if (hasReadable()) {
    pos++;
  }
};
void ByteArrayInputStream::skip(const size_t &skipSize_) {
  size_t skipSize = skipSize_;
  size_t readableSize = readable();
  if (readableSize < skipSize) {
    skipSize = readableSize;
  }
  if (skipSize > 0) {
    pos += skipSize;
  }
};
void ByteArrayInputStream::markCurrent() { mark = pos; };
void ByteArrayInputStream::markAt(const size_t &markPos_) {
  if (markPos_ >= bufferSize) {
    mark = bufferSize - 1;
  } else {
    mark = markPos_;
  }
};
void ByteArrayInputStream::resetMark() { mark = 0; };
void ByteArrayInputStream::rewind() { pos = 0; };
void ByteArrayInputStream::rewind(const size_t &rewindSize_) {
  if (pos >= rewindSize_) {
    pos -= rewindSize_;
  } else {
    pos = 0;
  }
};
void ByteArrayInputStream::rewindToMark() { pos = mark; };
bool ByteArrayInputStream::hasReadable() const { return bufferSize > pos; };
int64_t ByteArrayInputStream::readable() const {
  return bufferSize - (int64_t)(pos);
};
size_t ByteArrayInputStream::size() const { return bufferSize; };
