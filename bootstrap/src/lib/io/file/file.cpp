// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/file/file.hpp"

#include "error/common_errors.hpp"

using namespace gallop::Error;
using namespace gallop::IO;

bool File::exists(const std::string &filename_) {
  return (std::filesystem::exists(filename_));
};
bool File::isFile(const std::string &filename_) {
  return (exists(filename_) && std::filesystem::is_regular_file(filename_));
};
bool File::isDirectory(const std::string &filename_) {
  return (exists(filename_) && std::filesystem::is_directory(filename_));
};
bool File::mkdir(const std::string &filename_) {
  return std::filesystem::create_directories(filename_);
};
bool File::rmdir(const std::string &filename_) {
  return rmdir(filename_, false);
};
bool File::rmdir(const std::string &filename_, const bool &isRecursive_) {
  if (!isRemovableDirectory(filename_)) {
    return false;
  }
  std::filesystem::path filepath(filename_);
  size_t direcotyEntrySize = 0;
  for ([[maybe_unused]] const std::filesystem::directory_entry &i :
       std::filesystem::directory_iterator(filepath)) {
    direcotyEntrySize++;
  }
  if (!isRecursive_ && direcotyEntrySize > 0) {
    return false;
  } else if (!isRecursive_) {
    return std::filesystem::remove(filename_);
  }
  std::filesystem::remove_all(filename_);
  return true;
};
bool File::isRemovableDirectory(const std::string &filename_) {
  if (!exists(filename_)) {
    return false;
  }
  if (isFile(filename_)) {
    return false;
  }
  std::string absDirname = absoluteCanonicalPath(filename_);
  std::vector<std::string> dirVec = splitPath(absDirname, true);
  size_t dirVecSize = dirVec.size();
  if (dirVecSize <= 1) {
    return false;
  }
  return true;
};
bool File::touch(const std::string &filename_) {
  FILE *file = fopen(filename_.c_str(), "w");
  if (file == nullptr) {
    return false;
  }
  return true;
};
bool File::rm(const std::string &filename_) {
  if (!isRemovableFile(filename_)) {
    return false;
  }
  return std::filesystem::remove(filename_);
};
bool File::isRemovableFile(const std::string &filename_) {
  if (!exists(filename_)) {
    return false;
  }
  if (isDirectory(filename_)) {
    return false;
  }
  return true;
};
bool File::matchExtension(const std::string &filename_,
                          const std::string &extension_) {
  if (extension_.size() == 0) {
    return false;
  }
  std::string extension = extension_[0] == '.' ? extension_ : "." + extension_;
  size_t substrPos = 0;
  if (filename_.size() >= extension.size()) {
    substrPos = filename_.size() - extension.size();
  }
  std::string fileExtension = filename_.substr(substrPos);
  return (extension == fileExtension);
};
std::string File::getSingleExtension(const std::string &filename_) {
  std::filesystem::path filepath(filename_);
  return filepath.extension();
};
std::string File::replaceExtension(const std::string &filename_,
                                   const std::string &newExtension_) {
  return replaceExtension(filename_, getSingleExtension(filename_),
                          newExtension_);
};
std::string File::replaceExtension(const std::string &filename_,
                                   const std::string &oldExtension_,
                                   const std::string &newExtension_) {
  std::string oldExtension =
      oldExtension_[0] == '.' ? oldExtension_ : "." + oldExtension_;
  std::string newExtension =
      newExtension_[0] == '.' ? newExtension_ : "." + newExtension_;
  if (!matchExtension(filename_, oldExtension)) {
    return filename_;
  }
  size_t replacePos = filename_.size() - oldExtension.size();
  std::string filename = filename_;
  return filename.replace(replacePos, oldExtension.size(), newExtension);
};
std::string File::parentPath(const std::string &filename_) {
  std::filesystem::path filepath(absoluteCanonicalPath(filename_));
  return filepath.parent_path().string();
};
std::string File::absoluteCanonicalPath(const std::string &filename_) {
  std::filesystem::path filepath(filename_);
  if (!filepath.is_absolute()) {
    filepath = std::filesystem::absolute(filepath);
  }
  if (exists(filename_)) {
    return std::filesystem::canonical(filepath).string();
  }
  return std::filesystem::weakly_canonical(filepath).string();
};
std::vector<std::string> File::splitPath(const std::string &filename_) {
  return splitPath(filename_, false);
};
std::vector<std::string> File::splitPath(const std::string &filename_,
                                         const bool &isContainsFilename_) {
  std::string absFilePath = absoluteCanonicalPath(filename_);
  if (isDirectory(absFilePath)) {
    absFilePath.push_back(std::filesystem::path::preferred_separator);
  }
  std::vector<std::string> splittedPath;
  std::string basename;
  for (const char c : absFilePath) {
    if (c == ':') {
      basename.clear();
    } else if (c == '/' || c == '\\') {
      if (basename == "") {
        continue;
      }
      splittedPath.push_back(basename);
      basename.clear();
    } else {
      basename += c;
    }
  }
  if (isContainsFilename_ && basename != "") {
    splittedPath.push_back(basename);
  }
  return splittedPath;
};
std::string File::replacePathDirectory(const std::string &filename_,
                                       const std::string &srcDir_,
                                       const std::string &dstDir_) {
  std::string absFilename = absoluteCanonicalPath(filename_);
  std::string absSrcDir = absoluteCanonicalPath(srcDir_);
  std::string absDstDir = absoluteCanonicalPath(dstDir_);
  size_t pos = absFilename.find(absSrcDir);
  if (pos == std::string::npos || absSrcDir.empty()) {
    return absFilename;
  }
  if (!isDirectory(absSrcDir)) {
    return absFilename;
  } else {
    absSrcDir.push_back(std::filesystem::path::preferred_separator);
  }
  if (absDstDir.size() > 1) {
    absDstDir.push_back(std::filesystem::path::preferred_separator);
  }
  size_t len = absSrcDir.length();
  std::string dstFilename = absFilename;
  std::filesystem::path dstFilepath(dstFilename.replace(pos, len, absDstDir));
  return dstFilepath.string();
};
std::string File::filename(const std::string &filename_) {
  return filenameOrStem(filename_, false);
};
std::string File::filenameOrStem(const std::string &filename_,
                                 const bool &isStem_) {
  return filenameOrStem(filename_, getSingleExtension(filename_), isStem_);
};
std::string File::filenameOrStem(const std::string &filename_,
                                 const std::string &extension_,
                                 const bool &isStem_) {
  std::filesystem::path filepath(filename_);
  std::string filename = filepath.filename().string();
  if (!isStem_) {
    return filename;
  }
  std::string extension = extension_[0] == '.' ? extension_ : "." + extension_;
  if (matchExtension(filename, extension)) {
    size_t stemPos = filename.size() - extension.size();
    return filename.substr(0, stemPos);
  }
  return filepath.stem().string();
};
std::vector<char> File::readAllBinary(const std::string &filename_) {
  FILE *file = fopen(filename_.c_str(), "rb");
  if (file == nullptr) {
    throw new IOError("file not found " + filename_ + "\n");
  }
  fpos_t fsize;
  fseek(file, 0, SEEK_END);
  fgetpos(file, &fsize);
  fseek(file, 0, SEEK_SET);
  std::vector<char> fbuff(fsize);
  fread(&fbuff[0], fsize, 1, file);
  fclose(file);
  return fbuff;
};
std::string File::getCurrentDir() { return std::filesystem::current_path(); };
