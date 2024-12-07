// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHARSET_DETECTER_
#define _CHARSET_DETECTER_

#include "charset/encoding_charset/encoding_charset.hpp"
#include "io/stream/utf16_input_stream.hpp"
#include "io/stream/utf32_input_stream.hpp"
#include "io/stream/utf8_input_stream.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

using namespace gallop::IO::Stream;

namespace gallop {
namespace CharSet {
class Detector {
public:
  Detector(const std::vector<char> &buffer);
  ~Detector() {};
  Detector(const Detector &rhs);
  Detector &operator=(const Detector &rhs);
  EncodingCharsetEnum encodingCharSet() const;

private:
  EncodingCharsetEnum charset;
  std::vector<char> buffer;

  void scanningBuffer();
  void detectEcsUtfBom(Utf8InputStream &bais, Utf32InputStream &u32is,
                       Utf16InputStream &u16is);
  void detectEcsUtf8(Utf8InputStream &bais);
  void detectEcsUtf32(Utf32InputStream &u32is);
  void detectEcsUtf16(Utf16InputStream &u16is);
};

} // namespace CharSet
} // namespace gallop
#endif