// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf8_input_stream.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "charset/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf8InputStream::Utf8InputStream()
    : buffer(std::vector<char>()), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(0) {};
Utf8InputStream::Utf8InputStream(const std::string &buffer_)
    : buffer(std::vector<char>(buffer_.begin(), buffer_.end())),
      bufferPtr(buffer.data()), pos(0), mark(0), bufferSize(buffer.size()) {};
Utf8InputStream::Utf8InputStream(const std::vector<char> &buffer_)
    : buffer(buffer_), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
Utf8InputStream::Utf8InputStream(const Utf8InputStream &rhs)
    : buffer(rhs.buffer), bufferPtr(buffer.data()), pos(rhs.pos),
      mark(rhs.mark), bufferSize(rhs.bufferSize) {};
Utf8InputStream &Utf8InputStream::operator=(const Utf8InputStream &rhs) {
  buffer = rhs.buffer;
  bufferPtr = buffer.data();
  pos = rhs.pos;
  mark = rhs.mark;
  bufferSize = rhs.bufferSize;
  return *this;
};
std::vector<char> Utf8InputStream::data() { return buffer; };
char Utf8InputStream::current() {
  if (hasReadable()) {
    char chr = *(bufferPtr + (pos));
    return chr;
  }
  return '\0';
};
char Utf8InputStream::read() {
  if (hasReadable()) {
    char chr = *(bufferPtr + (pos));
    pos++;
    return chr;
  }
  return '\0';
};
int16_t Utf8InputStream::readByte2() {
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
int32_t Utf8InputStream::readByte3() {
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
int32_t Utf8InputStream::readByte4() {
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

std::vector<char> Utf8InputStream::readChunk(const size_t &chunkSize_) {
  return readChunk(chunkSize_, false);
};
std::vector<char> Utf8InputStream::readChunk(const size_t &chunkSize_,
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
char Utf8InputStream::undo() {
  if (pos == 0) {
    return '\0';
  }
  pos--;
  return *(bufferPtr + (pos));
};
char Utf8InputStream::ahead() {
  if (readable() > 1) {
    return *(bufferPtr + (pos + 1));
  };
  return '\0';
};
char Utf8InputStream::ahead(const size_t &offset_) {
  if (readable() > (int64_t)(1 + offset_)) {
    return *(bufferPtr + (pos + 1 + offset_));
  };
  return '\0';
};
void Utf8InputStream::skip() {
  if (hasReadable()) {
    pos++;
  }
};
void Utf8InputStream::skip(const size_t &skipSize_) {
  size_t skipSize = skipSize_;
  size_t readableSize = readable();
  if (readableSize < skipSize) {
    skipSize = readableSize;
  }
  if (skipSize > 0) {
    pos += skipSize;
  }
};
void Utf8InputStream::markCurrent() { mark = pos; };
void Utf8InputStream::markAt(const size_t &markPos_) {
  if (markPos_ >= bufferSize) {
    mark = bufferSize - 1;
  } else {
    mark = markPos_;
  }
};
void Utf8InputStream::resetMark() { mark = 0; };
void Utf8InputStream::rewind() { pos = 0; };
void Utf8InputStream::rewind(const size_t &rewindSize_) {
  if (pos >= rewindSize_) {
    pos -= rewindSize_;
  } else {
    pos = 0;
  }
};
void Utf8InputStream::rewindToMark() { pos = mark; };
bool Utf8InputStream::hasReadable() const { return bufferSize > pos; };
int64_t Utf8InputStream::readable() const {
  return bufferSize - (int64_t)(pos);
};
size_t Utf8InputStream::size() const { return bufferSize; };
