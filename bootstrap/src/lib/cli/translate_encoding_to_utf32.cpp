// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "cli/translate_encoding_to_utf32.hpp"

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/string/utf16_string.hpp"
#include "char_set/string/utf32_string.hpp"
#include "char_set/string/utf8_string.hpp"
#include "io/stream/byte_array_output_stream.hpp"
#include "io/stream/utf16_input_stream.hpp"

using namespace gallop::Cli;
using namespace gallop::CharSet;
using namespace gallop::IO::Stream;

Utf32InputStream
TranslateEncodingToU32::translate(const enum EncodingCharsetEnum &charset_,
                                  const std::vector<char> &buffer_) {
  Utf32InputStream uis;
  std::vector<int32_t> i32data;
  ByteArrayOutputStream baos;
  if (charset_ == EncodingCharsetEnum::InvalidTextEncoding) {
    return uis;
  }
  if (charset_ == EncodingCharsetEnum::UTF8 ||
      charset_ == EncodingCharsetEnum::UTF8_BOM) {
    i32data = String::Utf8::toU32Data(buffer_);
  } else if (charset_ == EncodingCharsetEnum::UTF16BE ||
             charset_ == EncodingCharsetEnum::UTF16BE_BOM) {
    Utf16InputStream u16is(buffer_);
    i32data = String::Utf16::toU32Data(u16is.data());
  } else if (charset_ == EncodingCharsetEnum::UTF16LE ||
             charset_ == EncodingCharsetEnum::UTF16LE_BOM) {
    Utf16InputStream u16is(buffer_);
    i32data = String::Utf16::toU32Data(u16is.data(), true, false, false);
  } else if (charset_ == EncodingCharsetEnum::UTF32BE ||
             charset_ == EncodingCharsetEnum::UTF32BE_BOM) {
    Utf32InputStream u32is(buffer_);
    i32data = String::Utf32::toU32Data(u32is.data());
  } else if (charset_ == EncodingCharsetEnum::UTF32LE ||
             charset_ == EncodingCharsetEnum::UTF32LE_BOM) {
    Utf32InputStream u32is(buffer_);
    i32data = String::Utf32::toU32Data(u32is.data(), true, false, false);
  }
  uis = Utf32InputStream(i32data);
  return uis;
};
