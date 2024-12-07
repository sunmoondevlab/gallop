#include "file/file.hpp"
#include "charset/detector/detector.hpp"

using namespace gallop;

bool File::isExists(const std::string filename_) {
  return (std::filesystem::exists(filename_));
};

bool File::matchExtension(const std::string filename_,
                          const std::string extension_) {
  int32_t extPos = filename_.find_last_of('.');
  std::string extFilename =
      filename_.substr(extPos + 1, filename_.size() - extPos - 1);
  return (extension_ == extFilename);
};

std::string File::replaceExtension(const std::string filename_,
                                   const std::string newExtension_) {
  int32_t extPos = filename_.find_last_of('.');
  std::string basename = filename_.substr(0, extPos + 1);
  return basename.append(newExtension_);
};

std::string File::getDirectory(const std::string filename_) {
  int32_t slashPos = filename_.find_last_of('/');
  return filename_.substr(0, slashPos);
};
std::string File::getBasename(const std::string filename_) {
  int32_t slashPos = filename_.find_last_of('/');
  return filename_.substr(slashPos + 1, filename_.size() - slashPos);
};
std::string File::getBasename(const std::string filename_,
                              const bool isOmitExt_) {
  std::string basename = getBasename(filename_);
  if (!isOmitExt_) {
    return basename;
  }
  int32_t extPos = basename.find_last_of('.');
  return basename.substr(0, extPos);
};

std::vector<char> File::readAllBinary(const std::string filename_) {
  FILE *file = fopen(filename_.c_str(), "rb");
  if (file == nullptr) {
    throw "file not fount " + filename_;
  }
  fpos_t fsize;
  fseek(file, 0, SEEK_END);
  fgetpos(file, &fsize);
  fseek(file, 0, SEEK_SET);
  std::vector<char> fbuff(fsize);
  fread(&fbuff[0], fsize, 1, file);
  fclose(file);
  return fbuff;
}
