#ifndef _CHARSET_TRANSLATE_UTF7_
#define _CHARSET_TRANSLATE_UTF7_

#include "charset/encoding_charset/encoding_charset.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace Translate {
class Utf7Base64 {

private:
  static std::map<char, char> base64DecodeMap;
  static std::map<char, char> base64EncodeMap;
  static std::map<char, char> base64ImapDecodeMap;
  static std::map<char, char> base64ImapEncodeMap;
};
class Utf7Decoder {
public:
  Utf7Decoder(const std::vector<char> &buffer);
  ~Utf7Decoder() {};
  Utf7Decoder(const Utf7Decoder &rhs);
  Utf7Decoder &operator=(const Utf7Decoder &rhs);

private:
  std::vector<char> buffer;
  size_t bufferLen;
  const char *bufferPtr;
  bool validDecodeFlag;
  bool utf7ImapFlag;

  void decode();
};

class Utf7Encoder {
public:
  Utf7Encoder(const std::string &buffer, const bool utf7ImapFlag,
              const bool utf7BomFlag, const bool strictUtf7Flag);
  ~Utf7Encoder() {};
  Utf7Encoder(const Utf7Encoder &rhs);
  Utf7Encoder &operator=(const Utf7Encoder &rhs);

private:
  std::string buffer;
  size_t bufferLen;
  const char *bufferPtr;
  const bool strictUtf7Flag;
  const bool utf7ImapFlag;
  const bool utf7BomFlag;
  std::string utf7String;

  void encode();
};

} // namespace Translate

} // namespace CharSet

} // namespace gallop

#endif