// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "compiler/model/location.hpp"

using namespace gallop::Compiler;

Location::Location() : filename(""), bufferPos(0), line(1ul), column(1ul) {};
Location::Location(const std::string &filename_)
    : filename(filename_), bufferPos(0), line(1ul), column(1ul) {};
Location::Location(const size_t &bufferPos_, const size_t &line_,
                   const size_t &column_)
    : filename(""), bufferPos(bufferPos_), line(line_), column(column_) {
  initializeCursor();
};
Location::Location(const std::string &filename_, const size_t &bufferPos_,
                   const size_t &line_, const size_t &column_)
    : filename(filename_), bufferPos(bufferPos_), line(line_), column(column_) {
  initializeCursor();
};
Location::Location(const Location &rhs)
    : filename(rhs.filename), bufferPos(rhs.bufferPos), line(rhs.line),
      column(rhs.column) {};
Location &Location::operator=(const Location &rhs) {
  filename = rhs.filename;
  bufferPos = rhs.bufferPos;
  line = rhs.line;
  column = rhs.column;
  return *this;
};
std::string Location::getString() const {
  return line > 0 ? (filename + ":" + std::to_string(line) + ":" +
                     std::to_string(column))
                  : filename;
};
std::string Location::getFilename() const { return filename; };
size_t Location::getBufferPos() const { return bufferPos; };
size_t Location::getLine() const { return line; };
size_t Location::getColumn() const { return column; };

void Location::initializeCursor() {
  if (line == 0) {
    line++;
  }
  if (column == 0) {
    column++;
  }
};
