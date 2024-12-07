// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _COMPILER_MODEL_LOCATION_
#define _COMPILER_MODEL_LOCATION_

#include <cstdint>
#include <string>

namespace gallop {
namespace Compiler {

class Location {
public:
  Location();
  Location(const std::string &filename);
  Location(const size_t &bufferPos, const size_t &line, const size_t &column);
  Location(const std::string &filename, const size_t &bufferPos,
           const size_t &line, const size_t &column);
  ~Location() {};
  Location(const Location &rhs);
  Location &operator=(const Location &rhs);
  std::string getString() const;
  size_t getBufferPos() const;
  std::string getFilename() const;
  size_t getLine() const;
  size_t getColumn() const;

private:
  std::string filename;
  size_t bufferPos;
  size_t line;
  size_t column;
  void initializeCursor();
};

} // namespace Compiler
} // namespace gallop
#endif