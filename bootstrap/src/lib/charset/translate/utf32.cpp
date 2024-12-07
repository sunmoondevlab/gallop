#include "charset/translate/utf32.hpp"

using namespace gallop::CharSet::Translate;

Utf32Encoder::Utf32Encoder(const std::string &buffer_,
                           const bool littleEndianFlag_,
                           const bool utf32BomFlag_)
    : buffer(buffer_), bufferLen(buffer_.size()), bufferPtr(buffer_.c_str()),
      littleEndianFlag(littleEndianFlag_), utf32BomFlag(utf32BomFlag_) {
  encode();
};

Utf32Encoder::Utf32Encoder(const Utf32Encoder &rhs)
    : buffer(rhs.buffer), bufferLen(rhs.bufferLen),
      littleEndianFlag(rhs.littleEndianFlag), utf32BomFlag(rhs.utf32BomFlag),
      utf32RunesBuffer(rhs.utf32RunesBuffer),
      utf32RunesBufferLen(rhs.utf32RunesBufferLen),
      utf32Buffer(rhs.utf32Buffer), utf32BufferLen(rhs.utf32BufferLen) {
  bufferPtr = buffer.c_str();
};

Utf32Encoder &Utf32Encoder::operator=(const Utf32Encoder &rhs) {
  buffer = rhs.buffer;
  bufferLen = rhs.bufferLen;
  bufferPtr = buffer.c_str();
  littleEndianFlag = rhs.littleEndianFlag;
  utf32BomFlag = rhs.utf32BomFlag;
  utf32RunesBuffer = rhs.utf32RunesBuffer;
  utf32RunesBufferLen = rhs.utf32RunesBufferLen;
  utf32Buffer = rhs.utf32Buffer;
  utf32BufferLen = rhs.utf32BufferLen;
  return *this;
};
std::vector<int32_t> Utf32Encoder::getUtf32RunesBuffer() const {
  return utf32RunesBuffer;
};
std::vector<char> Utf32Encoder::getUtf32Buffer() const { return utf32Buffer; };
size_t Utf32Encoder::getUtf32RunesBufferLen() const {
  return utf32RunesBufferLen;
};
size_t Utf32Encoder::getUtf32BufferLen() const { return utf32BufferLen; };

void Utf32Encoder::encode() {
  size_t utf32Pos = (utf32BomFlag ? 1 : 0), utf32BufPos = utf32Pos << 2;
  utf32RunesBuffer.resize(bufferLen + utf32Pos);
  utf32Buffer.resize((bufferLen + utf32Pos) << 2);
  int32_t *utf32RunesBufferPtr = (int32_t *)utf32RunesBuffer.data();
  char *utf32BufferPtr = (char *)utf32Buffer.data();
  if (utf32BomFlag) {
    if (littleEndianFlag) {
      *(utf32RunesBufferPtr) = static_cast<int32_t>(0xfffe0000);
      *(utf32BufferPtr + 0) = static_cast<char>(0xff);
      *(utf32BufferPtr + 1) = static_cast<char>(0xfe);
    } else {
      *(utf32RunesBufferPtr) = static_cast<int32_t>(0x0000feff);
      *(utf32BufferPtr + 2) = static_cast<char>(0xfe);
      *(utf32BufferPtr + 3) = static_cast<char>(0xff);
    }
  }
  uint8_t chr0 = 0, chr1 = 0, chr2 = 0, chr3 = 0;
  uint32_t utf32Ucp = 0;
  for (size_t pos = 0; pos < bufferLen; pos++) {
    chr0 = *(bufferPtr + pos);
    // 1 byte (U+0000 - U+007f)
    if ((chr0 & 0x80) == 0) {
      utf32Ucp = chr0;
      if (littleEndianFlag) {
        *(utf32RunesBufferPtr + utf32Pos) = utf32Ucp << 24;
        *(utf32BufferPtr + utf32BufPos + 0) = (char)(utf32Ucp & 0x000000ff);
      } else {
        *(utf32RunesBufferPtr + utf32Pos) = utf32Ucp;
        *(utf32BufferPtr + utf32BufPos + 3) = (char)(utf32Ucp & 0x000000ff);
      }
      utf32Pos++;
      utf32BufPos += 4;
    }
    // 2 byte (U+0080 - U+07ff)
    else if ((chr0 & 0xe0) == 0xc0) {
      chr1 = *(bufferPtr + pos + 1);
      if ((chr1 & 0xc0) == 0x80) {
        utf32Ucp = ((chr0 & 0x1f) << 6) | (chr1 & 0x3f);
        if (littleEndianFlag) {
          *(utf32RunesBufferPtr + utf32Pos) =
              (utf32Ucp << 24 | ((utf32Ucp & 0x0000ff00) << 8));
          *(utf32BufferPtr + utf32BufPos + 0) = (char)(utf32Ucp & 0x000000ff);
          *(utf32BufferPtr + utf32BufPos + 1) =
              (char)((utf32Ucp & 0x0000ff00) >> 8);
        } else {
          *(utf32RunesBufferPtr + utf32Pos) = utf32Ucp;
          *(utf32BufferPtr + utf32BufPos + 2) =
              (char)((utf32Ucp & 0x0000ff00) >> 8);
          *(utf32BufferPtr + utf32BufPos + 3) = (char)(utf32Ucp & 0x000000ff);
        }
        utf32Pos++;
        utf32BufPos += 4;
        pos++;
      } else {
        // invalid utf8(nop,dead code)
        break;
      }
    }
    // 3 byte (U+0800 - U+ffff)
    else if ((chr0 & 0xf0) == 0xe0) {
      chr1 = *(bufferPtr + pos + 1);
      if ((chr1 & 0xc0) == 0x80) {
        chr2 = *(bufferPtr + pos + 2);
        if ((chr2 & 0xc0) == 0x80) {
          utf32Ucp =
              ((chr0 & 0x0f) << 12) | ((chr1 & 0x3f) << 6) | (chr2 & 0x3f);
          if (littleEndianFlag) {
            *(utf32RunesBufferPtr + utf32Pos) =
                (utf32Ucp << 24 | ((utf32Ucp & 0x0000ff00) << 8));
            *(utf32BufferPtr + utf32BufPos + 0) = (char)(utf32Ucp & 0x000000ff);
            *(utf32BufferPtr + utf32BufPos + 1) =
                (char)((utf32Ucp & 0x0000ff00) >> 8);
          } else {
            *(utf32RunesBufferPtr + utf32Pos) = utf32Ucp;
            *(utf32BufferPtr + utf32BufPos + 2) =
                (char)((utf32Ucp & 0x0000ff00) >> 8);
            *(utf32BufferPtr + utf32BufPos + 3) = (char)(utf32Ucp & 0x000000ff);
          }
          utf32Pos++;
          utf32BufPos += 4;
          pos += 2;
        } else {
          // invalid utf8(nop,dead code)
          break;
        }
      } else {
        // invalid utf8(nop,dead code)
        break;
      }
    }
    // 4 byte (U+010000 - U+01ffff)
    else if ((chr0 & 0xf8) == 0xf0) {
      chr1 = *(bufferPtr + pos + 1);
      if ((chr1 & 0xc0) == 0x80) {
        chr2 = *(bufferPtr + pos + 2);
        if ((chr2 & 0xc0) == 0x80) {
          chr3 = *(bufferPtr + pos + 3);
          if ((chr3 & 0xc0) == 0x80) {
            utf32Ucp = ((chr0 & 0x07) << 18) | ((chr1 & 0x3f) << 12) |
                       ((chr2 & 0x3f) << 6) | (chr3 & 0x3f);
            if (0x0000d800 <= utf32Ucp && utf32Ucp <= 0x0000dfff) {
              break;
            }
            if (littleEndianFlag) {
              *(utf32RunesBufferPtr + utf32Pos) =
                  (utf32Ucp << 24 | ((utf32Ucp & 0x0000ff00) << 8) |
                   ((utf32Ucp & 0x00ff0000) >> 8) |
                   ((utf32Ucp & 0xff000000) >> 24));
              *(utf32BufferPtr + utf32BufPos + 0) =
                  (char)(utf32Ucp & 0x000000ff);
              *(utf32BufferPtr + utf32BufPos + 1) =
                  (char)((utf32Ucp & 0x0000ff00) >> 8);
              *(utf32BufferPtr + utf32BufPos + 2) =
                  (char)((utf32Ucp & 0x00ff0000) >> 16);
            } else {
              *(utf32RunesBufferPtr + utf32Pos) = utf32Ucp;
              *(utf32BufferPtr + utf32BufPos + 1) =
                  (char)((utf32Ucp & 0x00ff0000) >> 16);
              *(utf32BufferPtr + utf32BufPos + 2) =
                  (char)((utf32Ucp & 0x0000ff00) >> 8);
              *(utf32BufferPtr + utf32BufPos + 3) =
                  (char)((utf32Ucp & 0x000000ff));
            }
            utf32Pos++;
            utf32BufPos += 4;
            pos += 3;
          } else {
            // invalid utf8(nop,dead code)
            break;
          }
        } else {
          // invalid utf8(nop,dead code)
          break;
        }
      } else {
        // invalid utf8(nop,dead code)
        break;
      }
    }
  }
  utf32RunesBufferLen = utf32Pos;
  utf32BufferLen = utf32BufPos;
  utf32RunesBuffer.resize(utf32RunesBufferLen);
  utf32Buffer.resize(utf32BufferLen);
};
