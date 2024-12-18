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
  LexicalAnalyzer(const std::vector<char> &buffer);
  // compiler from file
  LexicalAnalyzer(const std::vector<char> &buffer, const std::string &filename);
  // copier
  LexicalAnalyzer(const LexicalAnalyzer &rhs);
  // setter
  LexicalAnalyzer &operator=(const LexicalAnalyzer &rhs);
  ~LexicalAnalyzer() {};
  void tokenizeNextBuffer(const std::vector<char> &buffer);
  uint64_t getLexAnlzFlag() const;
  bool isInterpreter() const;
  bool isFromFile() const;
  size_t getLineCnt() const;
  std::string getLineString(const size_t line) const;
  Tokens *getTokens();
  bool isLexAnlzContinue() const;

private:
  std::string buffer;
  size_t bufferLen;
  Location location;
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

  size_t toNextToken(const size_t pos);
  Location computeLocation(const size_t pos, const size_t tokenLen,
                           const Location location);
  void pushToken(const size_t pos, const size_t tokenLen,
                 const TokenTypeEnum tokenType);

  size_t scanningToken(const size_t pos);
  size_t scanningIdentifier(const size_t pos);
  size_t scanningSymbolCharacters(const size_t pos);
  size_t scanningNonDecimalNumber(const size_t pos);
  size_t scanningDecimalNumber(const size_t pos);
  size_t scanningBinaryNumber(const size_t pos);
  size_t scanningOctalNumber(const size_t pos);
  size_t scanningHexadecimalNumber(const size_t pos);
  size_t scanningRunes(const size_t pos);
  size_t scanningOnelineComment(const size_t pos);
  size_t scanningBlockComment(const size_t pos);
};

} // namespace Lexer
} // namespace Compiler
} // namespace gallop
#endif