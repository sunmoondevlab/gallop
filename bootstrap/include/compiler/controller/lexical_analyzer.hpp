// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_CONTROLLER_LEXICAL_ANALYZER_
#define _COMPILER_CONTROLLER_LEXICAL_ANALYZER_

#include "compiler/model/compiler_mode.hpp"
#include "compiler/model/src_lines.hpp"
#include "compiler/model/tokens_input_stream.hpp"
#include "io/stream/utf32_input_stream.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <vector>

using namespace gallop::IO::Stream;

namespace gallop {
namespace Compiler {
namespace Controller {

class LexicalAnalyzer {
public:
  LexicalAnalyzer(const SrcLines &lines, const enum CompilerModeEnum &mode);
  // copier
  LexicalAnalyzer(const LexicalAnalyzer &rhs);
  // setter
  LexicalAnalyzer &operator=(const LexicalAnalyzer &rhs);
  ~LexicalAnalyzer() {};
  void tokenizeNextBuffer(const std::vector<int32_t> &buffer);
  bool isInterpreter() const;
  bool isFromFile() const;
  std::string getFilename() const;
  size_t getLineCount() const;
  std::string getLineString(const size_t &line) const;
  TokensInputStream getTokensInputStream();

private:
  SrcLines &lines;
  CompilerModeEnum &mode;
  Utf32InputStream uis;
  Tokens tokens;
  TokensInputStream tis;
  Location location;
  Location tokenBeginLocation;

  void tokenize();

  void toNextToken();
  void scanningSpaces();
  void scanningLineBreaks();
  void scanningIdentifier();
  void scanningSymbol();
  void scanningOnelineComment(const enum TokenTypeEnum &tokenType);
  void scanningBlockComment(const enum TokenTypeEnum &tokenType);
  void scanningSingleCharacterLiteral();
  void scanningStringLiteral();
  void scanningRawStringLiteral();
  void scanningEscapeSequence(const enum TokenTypeEnum &tokenType);
  void scanningEscapeSequenceUtf8CodeOctal(const bool &isInBrackets,
                                           const bool &isSingleCharacter);
  void scanningEscapeSequenceUtf8CodeHexadecimal(const bool &isInBrackets,
                                                 const bool &isSingleCharacter);
  void
  scanningEscapeSequenceUtf16CodeHexadecimal(const bool &isInBrackets,
                                             const bool &isSingleCharacter);
  void
  scanningEscapeSequenceUtf32CodeHexadecimal(const bool &isInBrackets,
                                             const bool &isSingleCharacter);
  void pushToken(const enum TokenTypeEnum &tokenType, const size_t &tokenSize);
  void pushToken(const enum TokenTypeEnum &tokenType);
  Token *createToken(const enum TokenTypeEnum &tokenType,
                     const size_t &tokenSize);
  Token *createToken(const enum TokenTypeEnum &tokenType);
  void pushTokenEscapeCharCode(const enum TokenTypeEnum &tokenType,
                               const size_t &tokenSize,
                               const int32_t &escapeCharCode);
  void pushTokenEscapeUtfCharCode(const enum TokenTypeEnum &defaultTokenType,
                                  const size_t &tokenSize,
                                  const int32_t &escapeUtf32CharCode,
                                  const bool &isInBrackets);

  // size_t scanningToken(const size_t &pos);
  // size_t scanningIdentifier(const size_t &pos);
  // size_t scanningNonDecimal(const size_t &pos);
  // size_t scanningDecimalNumber(const size_t &pos);
  // size_t scanningBinaryNumber(const size_t &pos);
  // size_t scanningOctalNumber(const size_t &pos);
  // size_t scanningHexadecimalNumber(const size_t &pos);
};

} // namespace Controller
} // namespace Compiler
} // namespace gallop
#endif