#ifndef _CHARSET_DETECTER_
#define _CHARSET_DETECTER_

#include "charset/encoding_charset/encoding_charset.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
class Detector {
public:
  Detector(const std::vector<char> &buffer_);
  ~Detector() {};
  Detector(const Detector &rhs);
  Detector &operator=(const Detector &rhs);
  EncodingCharsetEnum getEncodingCharset();
  size_t getRuneCount();

private:
  std::vector<char> buffer;
  size_t bufferLen;
  const char *bufferPtr;
  EncodingCharsetEnum charset;
  size_t runeCnt;
  std::map<EncodingCharsetEnum, size_t> validCharSets;

  std::map<EncodingCharsetEnum, size_t> initValidCharSets();
  void scanningBuffer();
  void detectEcsUtfWithBom();
  void detectEcsByChars();
  size_t scanning7bitChars(const size_t pos_);
  size_t scanningUtf8Chars(const size_t pos_);
  void detectEcsUtf7();

  bool isCharAscii(size_t pos);
  bool isCharUtf8(size_t pos);

  EncodingCharsetEnum toEncodingCharsetEnumAscii();
};

} // namespace CharSet

} // namespace gallop

#endif