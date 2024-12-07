#ifndef _FILE_FILE_
#define _FILE_FILE_

#include "charset/encoding_charset/encoding_charset.hpp"
#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

#define BUFFSIZE 1024

namespace gallop {

class File {
public:
  // static func
  static bool isExists(const std::string filename);
  static bool matchExtension(const std::string filename,
                             const std::string extension);
  static std::string replaceExtension(const std::string filename,
                                      const std::string newExtension);
  static std::string getDirectory(const std::string filename);
  static std::string getBasename(const std::string filename);
  static std::string getBasename(const std::string filename,
                                 const bool isOmitExt);
  // public func
  File() = delete;
  ~File() = delete;
  static std::vector<char> readAllBinary(const std::string filename);
};

} // namespace gallop

#endif