// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _IO_FILE_FILE_
#define _IO_FILE_FILE_

#include "charset/encoding_charset/encoding_charset.hpp"
#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <llvm/Support/raw_ostream.h>
#include <string>
#include <vector>

#define BUFFSIZE 1024

namespace gallop {
namespace IO {

class File {
public:
  // public func
  File() = delete;
  ~File() = delete;

  // static func
  static bool exists(const std::string &filename);
  static bool isFile(const std::string &filename);
  static bool isDirectory(const std::string &filename);
  static bool mkdir(const std::string &filename);
  static bool rmdir(const std::string &filename);
  static bool rmdir(const std::string &filename, const bool &isRecursive);
  static bool isRemovableDirectory(const std::string &filename);
  static bool touch(const std::string &filename);
  static bool rm(const std::string &filename);
  static bool isRemovableFile(const std::string &filename);
  static bool matchExtension(const std::string &filename,
                             const std::string &extension);
  static std::string getSingleExtension(const std::string &filename);
  static std::string replaceExtension(const std::string &filename,
                                      const std::string &newExtension);
  static std::string replaceExtension(const std::string &filename,
                                      const std::string &oldExtension,
                                      const std::string &newExtension);
  static std::string parentPath(const std::string &filename);
  static std::string absoluteCanonicalPath(const std::string &filename);
  static std::string replacePathDirectory(const std::string &filename,
                                          const std::string &srcDir,
                                          const std::string &destDir);
  static std::vector<std::string> splitPath(const std::string &filename);
  static std::vector<std::string> splitPath(const std::string &filename,
                                            const bool &isContainsFilename);
  static std::string filename(const std::string &filename);
  static std::string filenameOrStem(const std::string &filename,
                                    const bool &isStem);
  static std::string filenameOrStem(const std::string &filename,
                                    const std::string &extension,
                                    const bool &isStem);
  static std::string getCurrentDir();
  static std::vector<char> readAllBinary(const std::string &filename);
};

} // namespace IO
} // namespace gallop
#endif