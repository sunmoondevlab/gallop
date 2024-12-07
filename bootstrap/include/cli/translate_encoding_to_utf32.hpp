// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CLI_TRANSLATE_ENCODING_TO_UTF32_
#define _CLI_TRANSLATE_ENCODING_TO_UTF32_

#include "char_set/encoding_charset/encoding_charset.hpp"
#include "io/stream/utf32_input_stream.hpp"

#include <cstdint>
#include <string>
#include <vector>

using namespace gallop::CharSet;
using namespace gallop::IO::Stream;

namespace gallop {
namespace Cli {

class TranslateEncodingToU32 {
public:
  TranslateEncodingToU32() = delete;
  ~TranslateEncodingToU32() = delete;
  static Utf32InputStream translate(const enum EncodingCharsetEnum &charset,
                                    const std::vector<char> &buffer);
};

} // namespace Cli
} // namespace gallop
#endif