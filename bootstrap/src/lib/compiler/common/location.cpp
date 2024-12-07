#include "compiler/common/location.hpp"

using namespace gallop::Compiler;

Location::Location(const size_t line_, const size_t column_)
    : filename(""), line(line_), column(column_) {};
Location::Location(const std::string &filename_, const size_t line_,
                   const size_t column_)
    : filename(filename_), line(line_), column(column_) {};
Location::Location(const Location &rhs)
    : filename(rhs.filename), line(rhs.line), column(rhs.column) {};
Location &Location::operator=(const Location &rhs) {
  filename = rhs.filename;
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
size_t Location::getLine() const { return line; };
size_t Location::getColumn() const { return column; };
void Location::addLine(const size_t lineStep_) { line += lineStep_; };
void Location::addColumn(const size_t columnStep_) { column += columnStep_; };
void Location::rewindColumn() { column = 1; };