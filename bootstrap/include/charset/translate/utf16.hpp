#ifndef _CHARSET_TRANSLATE_UTF16_
#define _CHARSET_TRANSLATE_UTF16_

#include "charset/encoding_charset/encoding_charset.hpp"
#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace Translate {

class Utf16Decoder {
public:
  Utf16Decoder(const std::vector<char> &buffer);
  ~Utf16Decoder() {};
  Utf16Decoder(const Utf16Decoder &rhs);
  Utf16Decoder &operator=(const Utf16Decoder &rhs);

private:
  std::vector<char> buffer;
  size_t bufferLen;
  const char *bufferPtr;
  bool validDecodeFlag;

  void decode();
};

class Utf16Encoder {
public:
  Utf16Encoder(const std::string &buffer, const bool littleEndianFlag,
               const bool utf16BomFlag);
  ~Utf16Encoder() {};
  Utf16Encoder(const Utf16Encoder &rhs);
  Utf16Encoder &operator=(const Utf16Encoder &rhs);
  std::vector<int32_t> getUtf16RunesBuffer() const;
  std::vector<char> getUtf16Buffer() const;
  size_t getUtf16RunesBufferLen() const;
  size_t getUtf16BufferLen() const;

private:
  std::string buffer;
  size_t bufferLen;
  const char *bufferPtr;
  bool littleEndianFlag;
  bool utf16BomFlag;
  std::vector<int32_t> utf16RunesBuffer;
  size_t utf16RunesBufferLen;
  std::vector<char> utf16Buffer;
  size_t utf16BufferLen;
  void encode();
};

} // namespace Translate

} // namespace CharSet

} // namespace gallop

#endif