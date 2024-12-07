#include "cli/interpreter.hpp"
#include "charset/detector/detector.hpp"
#include "compiler/lexer/lexical_analyzer.hpp"

namespace gallop {
namespace Cli {
void Interpreter::execute() {
  // size_t lineLoc = 1, colLoc = 1;
  // Parser::LexicalAnalyzer l(buf, lineLoc, 0l);
  while (std::cin) {
    std::cout << "> ";
    std::string str;
    getline(std::cin, str);
    std::vector<char> buf;
    std::copy(str.begin(), str.end(), std::back_inserter(buf));
    buf.push_back('\n');
    CharSet::Detector d(buf);
    if (d.getEncodingCharset() != CharSet::EncodingCharsetEnum::ASCII &&
        d.getEncodingCharset() != CharSet::EncodingCharsetEnum::UTF8 &&
        d.getEncodingCharset() != CharSet::EncodingCharsetEnum::UTF8_BOM) {
      std::cerr << "Unsupport charcter set\n";
      continue;
    }
    // l.tokenize();
    // lineLoc = l.getLineLoc();
    // colLoc = l.getColLoc();
  }
};
} // namespace Cli
} // namespace gallop
