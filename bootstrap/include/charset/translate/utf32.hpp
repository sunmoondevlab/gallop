#ifndef _CHARSET_TRANSLATE_UTF32_
#define _CHARSET_TRANSLATE_UTF32_

#include "charset/encoding_charset/encoding_charset.hpp"
#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace Translate {

class Utf32Decoder {
public:
  Utf32Decoder(const std::vector<char> &buffer_);
  ~Utf32Decoder() {};
  Utf32Decoder(const Utf32Decoder &rhs);
  Utf32Decoder &operator=(const Utf32Decoder &rhs);

private:
  std::vector<char> buffer;
  size_t bufferLen;
  const char *bufferPtr;
  bool validDecodeFlag;

  void decode();
};

class Utf32Encoder {
public:
  Utf32Encoder(const std::string &buffer_, const bool littleEndianFlag_,
               const bool utf32BomFlag_);
  ~Utf32Encoder() {};
  Utf32Encoder(const Utf32Encoder &rhs);
  Utf32Encoder &operator=(const Utf32Encoder &rhs);
  std::vector<int32_t> getUtf32RunesBuffer();
  std::vector<char> getUtf32Buffer();
  size_t getUtf32RunesBufferLen();
  size_t getUtf32BufferLen();

private:
  std::string buffer;
  size_t bufferLen;
  const char *bufferPtr;
  bool littleEndianFlag;
  bool utf32BomFlag;
  std::vector<int32_t> utf32RunesBuffer;
  size_t utf32RunesBufferLen;
  std::vector<char> utf32Buffer;
  size_t utf32BufferLen;
  void encode();
};

} // namespace Translate

} // namespace CharSet

} // namespace gallop

#endif