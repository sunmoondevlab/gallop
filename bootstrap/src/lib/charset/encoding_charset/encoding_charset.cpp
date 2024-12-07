#include "charset/encoding_charset/encoding_charset.hpp"

using namespace gallop::CharSet;

const std::string EncodingCharset::_list[] = {
    "Unknown",
    // 1 byte charcode
    // ASCII
    "ASCII",
    // UTF-7
    "UTF-7",
    "UTF-7 for IMAP",
    // UTF-8
    "UTF-8(with BOM)",
    "UTF-8",
    // UTF-16
    "UTF-16 BE(with BOM)",
    "UTF-16 LE(with BOM)",
    "UTF-16 BE",
    "UTF-16 LE",
    // UTF-32
    "UTF-32 BE(with BOM)",
    "UTF-32 LE(with BOM)",
    "UTF-32 BE",
    "UTF-32 LE",
};

std::string
EncodingCharset::getString(const enum EncodingCharsetEnum charset_) {
  return EncodingCharset::_list[int(charset_)];
};
