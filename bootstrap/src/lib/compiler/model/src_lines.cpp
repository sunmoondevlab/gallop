// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/src_lines.hpp"

#include "char_set/string/utf32_string.hpp"

using namespace gallop::Compiler;
using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

SrcLines::SrcLines()
    : filename(""), buffer(std::vector<int32_t>()), bufferPos(0), linesCount(0),
      linesData(std::vector<SrcLines::LineData>()) {};
SrcLines::SrcLines(const std::string &filename_)
    : filename(filename_), buffer(std::vector<int32_t>()), bufferPos(0),
      linesCount(0), linesData(std::vector<SrcLines::LineData>()) {};

// copier
SrcLines::SrcLines(const SrcLines &rhs)
    : filename(rhs.filename), buffer(rhs.buffer), bufferPos(rhs.bufferPos),
      linesCount(rhs.linesCount), linesData(rhs.linesData) {};

// setter
SrcLines &SrcLines::operator=(const SrcLines &rhs) {
  filename = rhs.filename;
  buffer = rhs.buffer;
  bufferPos = rhs.bufferPos;
  linesCount = rhs.linesCount;
  linesData = rhs.linesData;
  return *this;
};
std::string SrcLines::getFilename() const { return filename; };
void SrcLines::appendBuffer(std::vector<int32_t> &buffer_) {
  size_t prevBufferSize = buffer.size();
  buffer.reserve(prevBufferSize + buffer_.size());
  std::copy(buffer_.begin(), buffer_.end(), std::back_inserter(buffer));
  if (prevBufferSize != 0ul) {
    bufferPos = prevBufferSize;
  }
  buffer_.clear();
  analyzeLines();
};
void SrcLines::resetBuffer() {
  buffer.clear();
  bufferPos = 0;
  linesCount = 0;
  linesData.clear();
};
void SrcLines::shrinkBuffer(const size_t &pos_) {
  size_t bufferSize = buffer.size();
  if (pos_ >= bufferSize) {
    return;
  }
  buffer.erase(buffer.begin() + pos_, buffer.end());
  if (bufferPos > pos_) {
    bufferPos = pos_;
  }
  shrinkLines(pos_);
};

Utf32InputStream SrcLines::createUtf32InputStream() {
  Utf32InputStream uis(buffer);
  uis.markAt(bufferPos);
  uis.rewindToMark();
  return uis;
};
size_t SrcLines::getLinesCount() const { return linesCount; };
std::string SrcLines::getLineString(const size_t &line_) const {
  if (line_ == 0) {
    return "";
  }
  if (line_ <= linesData.size()) {
    SrcLines::LineData lineData = linesData.at(line_ - 1);
    return String::Utf32::toU8String(std::vector<int32_t>(
        buffer.begin() + lineData.beginPos,
        buffer.begin() + lineData.beginPos + lineData.lineSize));
  }
  return "";
};
bool SrcLines::isContinuingInterpreter() const { return bufferPos > 0; };

void SrcLines::analyzeLines() {
  Utf32InputStream uis = createUtf32InputStream();
  if (!uis.hasReadable()) {
    return;
  }
  if (bufferPos == 0) {
    linesCount++;
  }
  size_t lineNo = linesCount;
  size_t lineBeginPos = 0;
  size_t lineSize = 0;
  if (bufferPos > 0) {
    SrcLines::LineData lineData = linesData.back();
    lineNo = lineData.lineNo;
    lineBeginPos = lineData.beginPos;
    lineSize = lineData.lineSize;
    linesCount = lineNo;
    linesData.pop_back();
  }
  while (uis.hasReadable()) {
    int32_t charCode = uis.read();
    size_t lineBreakesSize = 1;
    if (CharCode::Utf32::isCarriageReturn(charCode)) {
      int32_t charCode1 = uis.current();
      if (CharCode::Utf32::isLineFeed(charCode1)) {
        lineBreakesSize++;
        uis.read();
      }
      linesData.push_back(SrcLines::LineData(lineNo, lineBeginPos, lineSize));
      linesCount++;
      lineNo++;
      lineBeginPos += (lineSize + lineBreakesSize);
      lineSize = 0;
    } else if (CharCode::Utf32::isLineFeed(charCode)) {
      linesData.push_back(SrcLines::LineData(lineNo, lineBeginPos, lineSize));
      linesCount++;
      lineNo++;
      lineBeginPos += (lineSize + lineBreakesSize);
      lineSize = 0;
    } else {
      lineSize++;
    }
  }
  linesData.push_back(SrcLines::LineData(lineNo, lineBeginPos, lineSize));
};
void SrcLines::shrinkLines(const size_t &pos_) {
  int64_t linesDataPos = linesCount;
  SrcLines::LineData *linesDataPtr = linesData.data();
  for (linesDataPos--; linesDataPos >= 0; linesDataPos--) {
    SrcLines::LineData *lineData = (linesDataPtr + linesDataPos);
    if (pos_ >= lineData->beginPos) {
      size_t shrinkLineSize = pos_ - lineData->beginPos;
      if (shrinkLineSize <= lineData->lineSize) {
        lineData->lineSize = shrinkLineSize;
      }
      break;
    } else {
      linesCount--;
      linesData.pop_back();
    }
  }
  linesData.shrink_to_fit();
};
SrcLines::LineData::LineData(const size_t &lineNo_, const size_t &beginPos_,
                             const size_t &lineSize_)
    : lineNo(lineNo_), beginPos(beginPos_), lineSize(lineSize_) {};
