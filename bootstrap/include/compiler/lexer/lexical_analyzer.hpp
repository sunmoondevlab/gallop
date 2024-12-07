#ifndef _COMPILER_LEXER_LEXICAL_ANALYZER_
#define _COMPILER_LEXER_LEXICAL_ANALYZER_
#include "compiler/lexer/token.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace Compiler {
namespace Lexer {

class LexicalAnalyzer {
public:
  // interpreter
  LexicalAnalyzer();
  // compiler from stdin
  LexicalAnalyzer(const std::vector<char> &buffer_);
  // compiler from file
  LexicalAnalyzer(const std::vector<char> &buffer_,
                  const std::string &filename_);
  // copier
  LexicalAnalyzer(const LexicalAnalyzer &rhs);
  // setter
  LexicalAnalyzer &operator=(const LexicalAnalyzer &rhs);
  ~LexicalAnalyzer() {};
  void tokenizeNextBuffer(const std::vector<char> &buffer_);
  uint64_t getLexAnlzFlag();
  bool isInterpreter();
  bool isFromFile();
  size_t getLineCnt();
  std::string getLineString(const size_t lineLoc_);
  Tokens *getTokens();
  bool isLexAnlzContinue();

private:
  std::string buffer;
  size_t bufferLen;
  size_t lineLoc;
  size_t colLoc;
  const char *bufferPtr;
  bool interpreterFlag;
  uint64_t laContFlags;
  std::string filename;
  size_t lineCnt;
  std::vector<std::string> lines;
  Tokens *tokens;
  Token *nextToken;

  enum LaContFlags : uint64_t {
    LaContFlagsInLiteralRune = 0x1l,
    LaContFlagsInLiteralString = 0x1l << 1,
    LaContFlagsInLiteralRegularExpressionPattern = 0x1l << 2,
    LaContFlagsInCommentOutOneline = 0x1l << 3,
    LaContFlagsInCommentOutBlock = 0x1l << 4,
    LaContFlagsInCommentOutBlockDoc = 0x1l << 5,
  };

  void tokenize();
  void splitLinesFromBuffer();

  size_t skipTokenSeparator(const size_t pos_);
  size_t toNextLine(const size_t pos_);
  void pushToken(const size_t pos_, const size_t tokenLen_,
                 const TokenTypeEnum tokenType);

  size_t scanningToken(const size_t pos_);
  size_t scanningIdentifier(const size_t pos_);
  size_t scanningSymbolCharacters(const size_t pos_);
  size_t scanningNonDecimalNumber(const size_t pos_);
  size_t scanningDecimalNumber(const size_t pos_);
  size_t scanningBinaryNumber(const size_t pos_);
  size_t scanningOctalNumber(const size_t pos_);
  size_t scanningHexadecimalNumber(const size_t pos_);
  size_t scanningRunes(const size_t pos_);
  size_t scanningOnelineComment(const size_t pos_);
  size_t scanningBlockComment(const size_t pos_);
};

} // namespace Lexer
} // namespace Compiler
} // namespace gallop
#endif