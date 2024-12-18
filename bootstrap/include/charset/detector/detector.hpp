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
  Detector(const std::vector<char> &buffer);
  ~Detector() {};
  Detector(const Detector &rhs);
  Detector &operator=(const Detector &rhs);
  EncodingCharsetEnum getEncodingCharset() const;
  size_t getRuneCount() const;

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
  size_t scanning7bitChars(const size_t pos);
  size_t scanningUtf8Chars(const size_t pos);
};

} // namespace CharSet

} // namespace gallop

#endif