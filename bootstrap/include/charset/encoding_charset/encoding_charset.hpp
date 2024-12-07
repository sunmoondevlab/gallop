
#ifndef _CHARSET_ENCODING_
#define _CHARSET_ENCODING_

#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
enum class EncodingCharsetEnum : int {
  Unknown = 0,
  // # Using char : 7bit
  // ASCII
  ASCII,
  // UTF-7
  UTF7,
  UTF7_IMAP,
  // # Using char : 8bit
  // UTF-8
  UTF8_BOM,
  UTF8,
  // # Using char : 16bit
  // UTF-16
  UTF16BE_BOM,
  UTF16LE_BOM,
  UTF16BE,
  UTF16LE,
  // # Using char : 32bit
  // UTF-32
  UTF32BE_BOM,
  UTF32LE_BOM,
  UTF32BE,
  UTF32LE,
};
class EncodingCharset final {
public:
  EncodingCharset() = delete;
  ~EncodingCharset() = delete;
  static std::string getString(const enum EncodingCharsetEnum charset);

private:
  static const std::string _list[];
};
} // namespace CharSet

} // namespace gallop

#endif