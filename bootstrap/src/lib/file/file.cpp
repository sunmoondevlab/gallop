#include "file/file.hpp"
#include "charset/detector/detector.hpp"

using namespace gallop;

bool File::isExists(const std::string filename) {
  return (std::filesystem::exists(filename));
};

bool File::matchExtension(const std::string filename,
                          const std::string extension) {
  int32_t extPos = filename.find_last_of('.');
  std::string extFilename =
      filename.substr(extPos + 1, filename.size() - extPos - 1);
  return (extension == extFilename);
};

std::string File::replaceExtension(const std::string filename,
                                   const std::string newExtension) {
  int32_t extPos = filename.find_last_of('.');
  std::string basename = filename.substr(0, extPos + 1);
  return basename.append(newExtension);
};

std::string File::getDirectory(const std::string filename) {
  int32_t slashPos = filename.find_last_of('/');
  return filename.substr(0, slashPos);
};
std::string File::getBasename(const std::string filename) {
  int32_t slashPos = filename.find_last_of('/');
  return filename.substr(slashPos + 1, filename.size() - slashPos);
};
std::string File::getBasename(const std::string filename,
                              const bool isOmitExt) {
  std::string basename = getBasename(filename);
  if (!isOmitExt) {
    return basename;
  }
  int32_t extPos = basename.find_last_of('.');
  return basename.substr(0, extPos);
};

std::vector<char> File::readAllBinary(const std::string filename) {
  FILE *file = fopen(filename.c_str(), "rb");
  if (file == nullptr) {
    throw "file not fount " + filename;
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
