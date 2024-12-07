// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_SRC_LINES_
#define _COMPILER_MODEL_SRC_LINES_

#include "char_set/char_code/utf32_char_code.hpp"
#include "io/stream/utf32_input_stream.hpp"

#include <cstdint>
#include <string>
#include <vector>

using namespace gallop::IO::Stream;

namespace gallop {
namespace Compiler {

class SrcLines {
public:
  SrcLines();
  SrcLines(const std::string &filename);
  // copier
  SrcLines(const SrcLines &rhs);
  // setter
  SrcLines &operator=(const SrcLines &rhs);
  ~SrcLines() {};
  std::string getFilename() const;
  void appendBuffer(std::vector<int32_t> &buffer);
  void resetBuffer();
  void shrinkBuffer(const size_t &pos);
  Utf32InputStream createUtf32InputStream();
  size_t getLinesCount() const;
  std::string getLineString(const size_t &line) const;
  bool isContinuingInterpreter() const;

private:
  std::string filename;
  std::vector<int32_t> buffer;
  size_t bufferPos;
  size_t linesCount;
  struct LineData {
  public:
    LineData(const size_t &lineNo, const size_t &beginPos,
             const size_t &lineSize);
    ~LineData() {};
    size_t lineNo;
    size_t beginPos;
    size_t lineSize;
  };
  std::vector<LineData> linesData;
  void analyzeLines();
  void shrinkLines(const size_t &pos);
};

} // namespace Compiler
} // namespace gallop
#endif