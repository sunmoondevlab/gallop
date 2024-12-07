#include "cli/compiler_from_stdin.hpp"
#include "charset/detector/detector.hpp"
#include "compiler/lexer/lexical_analyzer.hpp"

namespace gallop {
namespace Cli {
void CompilerFromStdin::execute() {
  std::vector<char> buf;
  while (std::cin) {
    std::string str;
    getline(std::cin, str);
    std::copy(str.begin(), str.end(), std::back_inserter(buf));
    if (str.size() > 0) {
      buf.push_back('\n');
    }
  }
  CharSet::Detector d(buf);
  if (d.getEncodingCharset() != CharSet::EncodingCharsetEnum::ASCII &&
      d.getEncodingCharset() != CharSet::EncodingCharsetEnum::UTF8 &&
      d.getEncodingCharset() != CharSet::EncodingCharsetEnum::UTF8_BOM) {
    std::cerr << "Unsupport charcter set\n";
    return;
  }
};
} // namespace Cli
} // namespace gallop
