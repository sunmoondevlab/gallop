#include "charset/translate/utf16.hpp"

using namespace gallop::CharSet::Translate;

Utf16Encoder::Utf16Encoder(const std::string &buffer_,
                           const bool littleEndianFlag_,
                           const bool utf16BomFlag_)
    : buffer(buffer_), bufferLen(buffer_.size()), bufferPtr(buffer_.c_str()),
      littleEndianFlag(littleEndianFlag_), utf16BomFlag(utf16BomFlag_) {
  encode();
};

Utf16Encoder::Utf16Encoder(const Utf16Encoder &rhs)
    : buffer(rhs.buffer), bufferLen(rhs.bufferLen),
      littleEndianFlag(rhs.littleEndianFlag), utf16BomFlag(rhs.utf16BomFlag),
      utf16RunesBuffer(rhs.utf16RunesBuffer),
      utf16RunesBufferLen(rhs.utf16RunesBufferLen),
      utf16Buffer(rhs.utf16Buffer), utf16BufferLen(rhs.utf16BufferLen) {
  bufferPtr = buffer.c_str();
};

Utf16Encoder &Utf16Encoder::operator=(const Utf16Encoder &rhs) {
  buffer = rhs.buffer;
  bufferLen = rhs.bufferLen;
  bufferPtr = buffer.c_str();
  littleEndianFlag = rhs.littleEndianFlag;
  utf16BomFlag = rhs.utf16BomFlag;
  utf16RunesBuffer = rhs.utf16RunesBuffer;
  utf16RunesBufferLen = rhs.utf16RunesBufferLen;
  utf16Buffer = rhs.utf16Buffer;
  utf16BufferLen = rhs.utf16BufferLen;
  return *this;
};
std::vector<int32_t> Utf16Encoder::getUtf16RunesBuffer() const {
  return utf16RunesBuffer;
};
std::vector<char> Utf16Encoder::getUtf16Buffer() const { return utf16Buffer; };
size_t Utf16Encoder::getUtf16RunesBufferLen() const {
  return utf16RunesBufferLen;
};
size_t Utf16Encoder::getUtf16BufferLen() const { return utf16BufferLen; };

void Utf16Encoder::encode() {
  size_t utf16Pos = (utf16BomFlag ? 1 : 0), utf16BufPos = utf16Pos << 1;
  utf16RunesBuffer.resize(bufferLen + utf16Pos);
  utf16Buffer.resize((bufferLen + utf16Pos) << 2);
  int32_t *utf16RunesBufferPtr = (int32_t *)utf16RunesBuffer.data();
  char *utf16BufferPtr = (char *)utf16Buffer.data();
  if (utf16BomFlag) {
    if (littleEndianFlag) {
      *(utf16RunesBufferPtr) = static_cast<int32_t>(0xfffe);
      *(utf16BufferPtr + 0) = static_cast<char>(0xff);
      *(utf16BufferPtr + 1) = static_cast<char>(0xfe);
    } else {
      *(utf16RunesBufferPtr) = static_cast<int32_t>(0xfeff);
      *(utf16BufferPtr + 0) = static_cast<char>(0xfe);
      *(utf16BufferPtr + 1) = static_cast<char>(0xff);
    }
  }
  uint8_t chr0 = 0, chr1 = 0, chr2 = 0, chr3 = 0;
  uint32_t utf16Ucp = 0, utf32Ucp = 0, utf32UcpHigh = 0, utf32UcpMid = 0,
           utf32UcpLow = 0;
  for (size_t pos = 0; pos < bufferLen; pos++) {
    chr0 = *(bufferPtr + pos);
    // 1 byte (U+0000 - U+007f)
    if ((chr0 & 0x80) == 0) {
      utf16Ucp = chr0;
      if (littleEndianFlag) {
        *(utf16RunesBufferPtr + utf16Pos) = utf16Ucp << 8;
        *(utf16BufferPtr + utf16BufPos + 0) = (char)(utf16Ucp & 0x000000ff);
      } else {
        *(utf16RunesBufferPtr + utf16Pos) = utf16Ucp;
        *(utf16BufferPtr + utf16BufPos + 1) = (char)(utf16Ucp & 0x000000ff);
      }
      utf16Pos++;
      utf16BufPos += 2;
    }
    // 2 byte (U+0080 - U+07ff)
    else if ((chr0 & 0xe0) == 0xc0) {
      chr1 = *(bufferPtr + pos + 1);
      if ((chr1 & 0xc0) == 0x80) {
        utf16Ucp = ((chr0 & 0x1f) << 6) | (chr1 & 0x3f);
        if (littleEndianFlag) {
          *(utf16RunesBufferPtr + utf16Pos) =
              (((utf16Ucp & 0x000000ff) << 8) | ((utf16Ucp & 0x0000ff00) >> 8));
          *(utf16BufferPtr + utf16BufPos + 0) = (char)(utf16Ucp & 0x000000ff);
          *(utf16BufferPtr + utf16BufPos + 1) =
              (char)((utf16Ucp & 0x0000ff00) >> 8);
        } else {
          *(utf16RunesBufferPtr + utf16Pos) = utf16Ucp;
          *(utf16BufferPtr + utf16BufPos + 0) =
              (char)((utf16Ucp & 0x0000ff00) >> 8);
          *(utf16BufferPtr + utf16BufPos + 1) = (char)(utf16Ucp & 0x000000ff);
        }
        utf16Pos++;
        utf16BufPos += 2;
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
          utf16Ucp =
              ((chr0 & 0x0f) << 12) | ((chr1 & 0x3f) << 6) | (chr2 & 0x3f);
          if (littleEndianFlag) {
            *(utf16RunesBufferPtr + utf16Pos) =
                (((utf16Ucp & 0x000000ff) << 8) |
                 ((utf16Ucp & 0x0000ff00) >> 8));
            *(utf16BufferPtr + utf16BufPos + 0) = (char)(utf16Ucp & 0x000000ff);
            *(utf16BufferPtr + utf16BufPos + 1) =
                (char)((utf16Ucp & 0x0000ff00) >> 8);
          } else {
            *(utf16RunesBufferPtr + utf16Pos) = utf16Ucp;
            *(utf16BufferPtr + utf16BufPos + 0) =
                (char)((utf16Ucp & 0x0000ff00) >> 8);
            *(utf16BufferPtr + utf16BufPos + 1) = (char)(utf16Ucp & 0x000000ff);
          }
          utf16Pos++;
          utf16BufPos += 2;
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
            utf32UcpHigh = ((utf32Ucp & 0x001f0000) >> 16) - 1;
            utf32UcpMid = utf32Ucp & 0x0000fc00;
            utf32UcpLow = utf32Ucp & 0x000003ff;
            utf16Ucp = 0xd8000000 | utf32UcpHigh << 22 | utf32UcpMid << 6 |
                       0x0000dc00 | utf32UcpLow;
            if (littleEndianFlag) {
              *(utf16RunesBufferPtr + utf16Pos) =
                  (utf16Ucp << 24 | ((utf16Ucp & 0x0000ff00) << 8) |
                   ((utf16Ucp & 0x00ff0000) >> 8) |
                   ((utf16Ucp & 0xff000000) >> 24));
              *(utf16BufferPtr + utf16BufPos + 0) =
                  (char)(utf16Ucp & 0x000000ff);
              *(utf16BufferPtr + utf16BufPos + 1) =
                  (char)((utf16Ucp & 0x0000ff00) >> 8);
              *(utf16BufferPtr + utf16BufPos + 2) =
                  (char)((utf16Ucp & 0x00ff0000) >> 16);
              *(utf16BufferPtr + utf16BufPos + 3) =
                  (char)((utf16Ucp & 0xff000000) >> 24);
            } else {
              *(utf16RunesBufferPtr + utf16Pos) = utf16Ucp;
              *(utf16BufferPtr + utf16BufPos + 0) =
                  (char)((utf16Ucp & 0xff000000) >> 24);
              *(utf16BufferPtr + utf16BufPos + 1) =
                  (char)((utf16Ucp & 0x00ff0000) >> 16);
              *(utf16BufferPtr + utf16BufPos + 2) =
                  (char)((utf16Ucp & 0x0000ff00) >> 8);
              *(utf16BufferPtr + utf16BufPos + 3) =
                  (char)((utf16Ucp & 0x000000ff));
            }
            utf16Pos++;
            utf16BufPos += 4;
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
  utf16RunesBufferLen = utf16Pos;
  utf16BufferLen = utf16BufPos;
  utf16RunesBuffer.resize(utf16RunesBufferLen);
  utf16Buffer.resize(utf16BufferLen);
};
