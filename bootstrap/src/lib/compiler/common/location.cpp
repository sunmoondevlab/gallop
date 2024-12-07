#include "compiler/common/location.hpp"

using namespace gallop::Compiler;

Location::Location(const size_t lineLoc_, const size_t colLoc_)
    : filename(""), lineLoc(lineLoc_), colLoc(colLoc_) {};
Location::Location(const std::string &filename_, const size_t lineLoc_,
                   const size_t colLoc_)
    : filename(filename_), lineLoc(lineLoc_), colLoc(colLoc_) {};
Location::Location(const Location &rhs)
    : filename(rhs.filename), lineLoc(rhs.lineLoc), colLoc(rhs.colLoc) {};
Location &Location::operator=(const Location &rhs) {
  filename = rhs.filename;
  lineLoc = rhs.lineLoc;
  colLoc = rhs.colLoc;
  return *this;
};

std::string Location::getString() {
  return lineLoc > 0 ? (filename + ":" + std::to_string(lineLoc) + ":" +
                        std::to_string(colLoc))
                     : filename;
};

std::string Location::getFilename() { return filename; };

size_t Location::getLineLoc() { return lineLoc; };

size_t Location::getColLoc() { return colLoc; };
