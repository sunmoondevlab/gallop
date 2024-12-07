// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf16_input_stream.hpp"
#include "charset/char_code/utf32_char_code.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf16InputStream::Utf16InputStream()
    : buffer(std::vector<int16_t>()), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
Utf16InputStream::Utf16InputStream(const std::vector<char> &buffer_)
    : buffer(toByte2Buffer(buffer_)), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
std::vector<int16_t>
Utf16InputStream::toByte2Buffer(const std::vector<char> &buffer_) {
  size_t byteBufferSize = buffer_.size();
  if ((byteBufferSize % 2) > 0) {
    bufferSize = (byteBufferSize + 1) / 2;
  } else {
    bufferSize = byteBufferSize / 2;
  }
  std::vector<int16_t> byte2buffer;
  byte2buffer.reserve(bufferSize);
  const char *byteBufferPtr = buffer_.data();
  for (size_t pos = 0, bPos = 0; pos < bufferSize; pos++, bPos += 2) {
    uint16_t elm = (((uint16_t)*(byteBufferPtr + bPos)) << 8) &
                   static_cast<uint16_t>(0xff00);
    if (bPos + 1 < byteBufferSize) {
      elm |= ((uint16_t)(*(byteBufferPtr + bPos + 1)) &
              static_cast<uint16_t>(0x00ff));
    }
    byte2buffer.push_back((int16_t)elm);
  }
  return byte2buffer;
};
Utf16InputStream::Utf16InputStream(const std::vector<int16_t> &buffer_)
    : buffer(buffer_), bufferPtr(buffer_.data()), pos(0), mark(0),
      bufferSize(buffer_.size()) {};
Utf16InputStream::Utf16InputStream(const Utf16InputStream &rhs)
    : buffer(rhs.buffer), bufferPtr(buffer.data()), pos(rhs.pos),
      mark(rhs.mark), bufferSize(rhs.bufferSize) {};
Utf16InputStream &Utf16InputStream::operator=(const Utf16InputStream &rhs) {
  buffer = rhs.buffer;
  bufferPtr = buffer.data();
  pos = rhs.pos;
  mark = rhs.mark;
  bufferSize = rhs.bufferSize;
  return *this;
};
std::vector<int16_t> Utf16InputStream::data() { return buffer; };
int16_t Utf16InputStream::current() {
  if (hasReadable()) {
    int16_t i16 = *(bufferPtr + (pos));
    return i16;
  }
  return static_cast<int16_t>(0);
};
int16_t Utf16InputStream::read() {
  if (hasReadable()) {
    int16_t i16 = *(bufferPtr + (pos));
    pos++;
    return i16;
  }
  return static_cast<int16_t>(0);
};
int32_t Utf16InputStream::readByte4() {
  if (readable() >= 2) {
    uint32_t readI32 = 0;
    int16_t i16 = *(bufferPtr + (pos));
    pos++;
    readI32 = (uint32_t)(i16 << 16);
    i16 = *(bufferPtr + (pos));
    pos++;
    readI32 |= ((uint32_t)(i16) & static_cast<uint32_t>(0x0000ffff));
    return (int32_t)readI32;
  }
  return static_cast<int32_t>(0);
};

std::vector<int16_t> Utf16InputStream::readChunk(const size_t &chunkSize_) {
  return readChunk(chunkSize_, false);
};
std::vector<int16_t> Utf16InputStream::readChunk(const size_t &chunkSize_,
                                                 const bool &isForward_) {
  size_t chunkSize = chunkSize_;
  size_t readableSize = readable();
  if (readableSize < chunkSize) {
    chunkSize = readableSize;
  }
  std::vector<int16_t> chunk;
  if (chunkSize > 0) {
    std::copy(buffer.begin() + pos, buffer.begin() + pos + chunkSize,
              std::back_inserter(chunk));
    if (isForward_) {
      pos += chunkSize;
    }
  }
  return chunk;
};
int16_t Utf16InputStream::undo() {
  if (pos == 0) {
    return static_cast<int16_t>(0);
  }
  pos--;
  return *(bufferPtr + (pos));
};
int16_t Utf16InputStream::ahead() {
  if (readable() > 1) {
    return *(bufferPtr + (pos + 1));
  };
  return static_cast<int16_t>(0);
};
int16_t Utf16InputStream::ahead(const size_t &offset_) {
  if (readable() > (int64_t)(1 + offset_)) {
    return *(bufferPtr + (pos + 1 + offset_));
  };
  return static_cast<int16_t>(0);
};
void Utf16InputStream::skip() {
  if (hasReadable()) {
    pos++;
  }
};
void Utf16InputStream::skip(const size_t &skipSize_) {
  size_t skipSize = skipSize_;
  size_t readableSize = readable();
  if (readableSize < skipSize) {
    skipSize = readableSize;
  }
  if (skipSize > 0) {
    pos += skipSize;
  }
};
void Utf16InputStream::markCurrent() { mark = pos; };
void Utf16InputStream::markAt(const size_t &markPos_) {
  if (markPos_ >= bufferSize) {
    mark = bufferSize - 1;
  } else {
    mark = markPos_;
  }
};
void Utf16InputStream::resetMark() { mark = 0; };
void Utf16InputStream::rewind() { pos = 0; };
void Utf16InputStream::rewind(const size_t &rewindSize_) {
  if (pos >= rewindSize_) {
    pos -= rewindSize_;
  } else {
    pos = 0;
  }
};
void Utf16InputStream::rewindToMark() { pos = mark; };
bool Utf16InputStream::hasReadable() const { return bufferSize > pos; };
int64_t Utf16InputStream::readable() const {
  return bufferSize - (int64_t)(pos);
};
size_t Utf16InputStream::size() const { return bufferSize; };
