#include "charset/detector/detector.hpp"

using namespace gallop::CharSet;

Detector::Detector(const std::vector<char> &buffer_)
    : buffer(buffer_), bufferLen(buffer_.size()), bufferPtr(buffer_.data()),
      charset(EncodingCharsetEnum::Unknown), runeCnt(0) {
  scanningBuffer();
};

Detector::Detector(const Detector &rhs)
    : buffer(rhs.buffer), bufferLen(rhs.bufferLen), charset(rhs.charset),
      runeCnt(rhs.runeCnt) {
  bufferPtr = buffer.data();
};

Detector &Detector::operator=(const Detector &rhs) {
  buffer = rhs.buffer;
  bufferLen = rhs.bufferLen;
  bufferPtr = buffer.data();
  charset = rhs.charset;
  runeCnt = rhs.runeCnt;
  return *this;
};

std::map<EncodingCharsetEnum, size_t> Detector::initValidCharSets() {
  return std::map<EncodingCharsetEnum, size_t>{
      // 7bit
      {EncodingCharsetEnum::ASCII, 0},
      {EncodingCharsetEnum::UTF7, 0},
      {EncodingCharsetEnum::UTF7_IMAP, 0},
      // 8bit
      {EncodingCharsetEnum::UTF8, 0},
      // 16bit
      {EncodingCharsetEnum::UTF16BE, 0},
      {EncodingCharsetEnum::UTF16LE, 0},
      // 32bit
      {EncodingCharsetEnum::UTF32BE, 0},
      {EncodingCharsetEnum::UTF32LE, 0},
  };
};

EncodingCharsetEnum Detector::getEncodingCharset() const { return charset; };
size_t Detector::getRuneCount() const { return runeCnt; };

void Detector::scanningBuffer() {
  if (bufferLen == 0) {
    charset = EncodingCharsetEnum::ASCII;
    return;
  }
  detectEcsUtfWithBom();
  if (charset == EncodingCharsetEnum::ASCII ||
      charset == EncodingCharsetEnum::UTF7) {
    return;
  }
  if (charset > EncodingCharsetEnum::Unknown) {
    return;
  }
  detectEcsByChars();
};

void Detector::detectEcsUtfWithBom() {
  if (bufferLen >= 4) {
    char chr0 = *(bufferPtr), chr1 = *(bufferPtr + 1), chr2 = *(bufferPtr + 2),
         chr3 = *(bufferPtr + 3);
    if ((bufferLen % 4) == 0) {
      if (chr0 == static_cast<char>(0x00) && chr1 == static_cast<char>(0x00) &&
          chr2 == static_cast<char>(0xfe) && chr3 == static_cast<char>(0xff)) {
        charset = EncodingCharsetEnum::UTF32BE_BOM;
        return;
      } else if (chr0 == static_cast<char>(0xff) &&
                 chr1 == static_cast<char>(0xfe) &&
                 chr2 == static_cast<char>(0x00) &&
                 chr3 == static_cast<char>(0x00)) {
        charset = EncodingCharsetEnum::UTF32LE_BOM;
        return;
      }
    }
    if (chr0 == '+' && chr1 == '/' && chr2 == 'v' &&
        (chr3 == '8' || chr3 == '9' || chr3 == '+' || chr3 == '/')) {
      charset = EncodingCharsetEnum::UTF7;
      return;
    }
  }
  if (bufferLen >= 3) {
    char chr0 = *(bufferPtr), chr1 = *(bufferPtr + 1), chr2 = *(bufferPtr + 2);
    if (chr0 == static_cast<char>(0xef) && chr1 == static_cast<char>(0xbb) &&
        chr2 == static_cast<char>(0xbf)) {
      charset = EncodingCharsetEnum::UTF8_BOM;
      return;
    }
  }
  if (bufferLen >= 2 && (bufferLen % 2) == 0) {
    char chr0 = *(bufferPtr), chr1 = *(bufferPtr + 1);
    if (chr0 == static_cast<char>(0xfe) && chr1 == static_cast<char>(0xff)) {
      charset = EncodingCharsetEnum::UTF16BE_BOM;
      return;
    }
    if (chr0 == static_cast<char>(0xff) && chr1 == static_cast<char>(0xfe)) {
      charset = EncodingCharsetEnum::UTF16LE_BOM;
      return;
    }
  }
};

void Detector::detectEcsByChars() {
  size_t readLen = 0;
  readLen = scanning7bitChars(0);
  if (readLen == bufferLen) {
    charset = EncodingCharsetEnum::ASCII;
    return;
  }
  readLen += scanningUtf8Chars(readLen);
  if (readLen == bufferLen) {
    charset = EncodingCharsetEnum::UTF8;
    return;
  }
};

size_t Detector::scanning7bitChars(const size_t pos_) {
  size_t readLen = 0;
  char chr = *(bufferPtr + pos_);
  for (size_t pos = pos_;
       pos < bufferLen && ((chr == '\t' || chr == '\v' || chr == '\f' ||
                            chr == '\r' || chr == '\n') ||
                           (' ' <= chr && chr <= '~'));
       pos++, chr = *(bufferPtr + pos), readLen++, runeCnt++)
    ;
  return readLen;
};

size_t Detector::scanningUtf8Chars(const size_t pos_) {
  size_t readLen = 0;
  uint8_t chr0 = 0, chr1 = 0, chr2 = 0, chr3 = 0;
  uint32_t utf32Ucp = 0;
  for (size_t pos = pos_; pos < bufferLen; pos++) {
    chr0 = *(bufferPtr + pos);
    // 1 byte (U+0000 - U+007f)
    if ((chr0 & 0x80) == 0) {
      readLen++;
      runeCnt++;
    }
    // 2 byte (U+0080 - U+07ff)
    else if ((chr0 & 0xe0) == 0xc0) {
      chr1 = *(bufferPtr + pos + 1);
      if ((chr1 & 0xc0) == 0x80) {
        readLen += 2;
        runeCnt++;
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
          readLen += 3;
          runeCnt++;
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
            readLen += 4;
            runeCnt++;
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
  return readLen;
};
