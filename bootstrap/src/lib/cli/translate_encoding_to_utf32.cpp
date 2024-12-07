// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "cli/translate_encoding_to_utf32.hpp"
#include "charset/char_code/utf16_char_code.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "charset/char_code/utf8_char_code.hpp"
#include "charset/string/utf16_string.hpp"
#include "charset/string/utf32_string.hpp"
#include "charset/string/utf8_string.hpp"
#include "io/stream/byte_array_output_stream.hpp"
#include "io/stream/utf16_input_stream.hpp"
#include "io/stream/utf32_input_stream.hpp"

using namespace gallop::Cli;
using namespace gallop::CharSet;
using namespace gallop::IO::Stream;

Utf32InputStream
TranslateEncodingToUtf32::translate(const enum EncodingCharsetEnum &charset_,
                                    const std::vector<char> &buffer_) {
  Utf32InputStream uis;
  std::vector<int32_t> i32data;
  ByteArrayOutputStream baos;
  if (charset_ == EncodingCharsetEnum::InvalidTextEncoding) {
    return uis;
  }
  if (charset_ == EncodingCharsetEnum::UTF8 ||
      charset_ == EncodingCharsetEnum::UTF8_BOM) {
    i32data = String::Utf8::toUtf32Data(buffer_);
  } else if (charset_ == EncodingCharsetEnum::UTF16BE ||
             charset_ == EncodingCharsetEnum::UTF16BE_BOM) {
    Utf16InputStream u16is(buffer_);
    i32data = String::Utf16::toUtf32Data(u16is.data());
  } else if (charset_ == EncodingCharsetEnum::UTF16LE ||
             charset_ == EncodingCharsetEnum::UTF16LE_BOM) {
    Utf16InputStream u16is(buffer_);
    i32data = String::Utf16::toUtf32Data(u16is.data(), true, false, true);
  } else if (charset_ == EncodingCharsetEnum::UTF32BE ||
             charset_ == EncodingCharsetEnum::UTF32BE_BOM) {
    Utf32InputStream u32is(buffer_);
    i32data = String::Utf32::toUtf32Data(u32is.data());
  } else if (charset_ == EncodingCharsetEnum::UTF32LE ||
             charset_ == EncodingCharsetEnum::UTF32LE_BOM) {
    Utf32InputStream u32is(buffer_);
    i32data = String::Utf32::toUtf32Data(u32is.data(), true, false, true);
  }
  uis = Utf32InputStream(i32data);
  return uis;
};
