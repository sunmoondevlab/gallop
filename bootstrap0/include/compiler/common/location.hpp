#ifndef _COMPILER_COMMON_LOCATION_
#define _COMPILER_COMMON_LOCATION_
#include <cstdint>
#include <string>

namespace gallop {
namespace Compiler {

class Location {
public:
  Location(const size_t lineLoc_, const size_t colLoc_);
  Location(const std::string &filename_, const size_t lineLoc_,
           const size_t colLoc_);
  ~Location() {};
  Location(const Location &rhs);
  Location &operator=(const Location &rhs);
  std::string getString();
  std::string getFilename();
  size_t getLineLoc();
  size_t getColLoc();

private:
  std::string filename;
  size_t lineLoc;
  size_t colLoc;
};

} // namespace Compiler
} // namespace gallop
#endif