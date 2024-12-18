#ifndef _COMPILER_COMMON_LOCATION_
#define _COMPILER_COMMON_LOCATION_
#include <cstdint>
#include <string>

namespace gallop {
namespace Compiler {

class Location {
public:
  Location(const size_t line, const size_t column);
  Location(const std::string &filename, const size_t line, const size_t column);
  ~Location() {};
  Location(const Location &rhs);
  Location &operator=(const Location &rhs);
  std::string getString() const;
  std::string getFilename() const;
  size_t getLine() const;
  size_t getColumn() const;
  void addLine(const size_t lineStep);
  void addColumn(const size_t columnStep);
  void rewindColumn();

private:
  std::string filename;
  size_t line;
  size_t column;
};

} // namespace Compiler
} // namespace gallop
#endif