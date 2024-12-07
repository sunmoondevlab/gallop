// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/file/file.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
using ::testing::EndsWith;
using ::testing::HasSubstr;

namespace gallop::IO {
class FileTest : public ::testing::Test {};
TEST_F(FileTest, Exists) {
  ASSERT_EQ(File::exists("gallop/example/bootstrap/commentout_bom.trot"),
            false);
  ASSERT_EQ(File::exists("../example/bootstrap/commentout_bom.trot"), true);
};
TEST_F(FileTest, IsFile) {
  ASSERT_EQ(File::isFile("../example/bootstrapo"), false);
  ASSERT_EQ(File::isFile("../example/bootstrap/commentout_bom.trot"), true);
  ASSERT_EQ(File::isFile("../example/bootstrap/"), false);
};
TEST_F(FileTest, IsDirectory) {
  ASSERT_EQ(File::isDirectory("../example/bootstrapo"), false);
  ASSERT_EQ(File::isDirectory("../example/bootstrap/commentout_bom.trot"),
            false);
  ASSERT_EQ(File::isDirectory("../example/bootstrap/"), true);
};
TEST_F(FileTest, IsRemovableDirectory) {
  ASSERT_EQ(File::isRemovableDirectory("/"), false);
  ASSERT_EQ(File::isRemovableDirectory("/Usr/"), false);
  ASSERT_EQ(File::isRemovableDirectory("/Windows/"), false);
  ASSERT_EQ(File::isRemovableDirectory("../example/bootstrap/"), true);
};
TEST_F(FileTest, IsRemovableFile) {
  ASSERT_EQ(File::isRemovableFile("/"), false);
  ASSERT_EQ(File::isRemovableFile("/Usr/"), false);
  ASSERT_EQ(File::isRemovableFile("/Windows/"), false);
  ASSERT_EQ(File::isRemovableFile("../example/bootstrap/commentout_bom.trot"),
            true);
};
TEST_F(FileTest, FileDirMkRm) {
  ASSERT_EQ(File::isDirectory("../example/file_dir_mkrm_test"), false);
  ASSERT_EQ(File::mkdir("../example/file_dir_mkrm_test/sub1"), true);
  ASSERT_EQ(File::isDirectory("../example/file_dir_mkrm_test/sub1"), true);
  ASSERT_EQ(File::mkdir("../example/file_dir_mkrm_test/sub2"), true);
  ASSERT_EQ(File::isDirectory("../example/file_dir_mkrm_test/sub2"), true);
  ASSERT_EQ(File::touch("../example/file_dir_mkrm_test/sub1/a.test"), true);
  std::vector<char> buffer =
      File::readAllBinary("../example/file_dir_mkrm_test/sub1/a.test");
  ASSERT_EQ(buffer.size(), (size_t)0);
  ASSERT_EQ(File::isFile("../example/file_dir_mkrm_test/sub1/a.test"), true);
  ASSERT_EQ(File::touch("../example/file_dir_mkrm_test/sub1/b.test"), true);
  ASSERT_EQ(File::isFile("../example/file_dir_mkrm_test/sub1/b.test"), true);
  ASSERT_EQ(File::rm("../example/file_dir_mkrm_test/sub1/b.test"), true);
  ASSERT_EQ(File::isFile("../example/file_dir_mkrm_test/sub1/b.test"), false);
  ASSERT_EQ(File::rm("../example/file_dir_mkrm_test/sub1/b.test"), false);
  ASSERT_EQ(File::rmdir("../example/file_dir_mkrm_test/sub2"), true);
  ASSERT_EQ(File::isDirectory("../example/file_dir_mkrm_test/sub2"), false);
  ASSERT_EQ(File::rmdir("../example/file_dir_mkrm_test/sub2"), false);
  ASSERT_EQ(File::rmdir("../example/file_dir_mkrm_test/sub1"), false);
  ASSERT_EQ(File::rmdir("../example/file_dir_mkrm_test", true), true);
  ASSERT_EQ(File::isDirectory("../example/file_dir_mkrm_test"), false);
  ASSERT_EQ(File::rmdir("../example/file_dir_mkrm_test", true), false);
};
TEST_F(FileTest, MatchExtension) {
  ASSERT_EQ(File::matchExtension("a.trot", ""), false);
  ASSERT_EQ(File::matchExtension("a.trot", ".trot"), true);
  ASSERT_EQ(File::matchExtension("a.tar.gz", ".tar.gz"), true);
  ASSERT_EQ(File::matchExtension("a.tar.gz", "tar.gz"), true);
  ASSERT_EQ(File::matchExtension(".tar.g", ".tar.gz"), false);
};
TEST_F(FileTest, GetSingleExtension) {
  ASSERT_EQ(File::getSingleExtension("a.trot"), ".trot");
  ASSERT_EQ(File::getSingleExtension("a.gz"), ".gz");
};
TEST_F(FileTest, ReplaceExtension) {
  ASSERT_EQ(File::replaceExtension("a.trot", "cpp"), "a.cpp");
  ASSERT_EQ(File::replaceExtension("a.tar.gz", "gz", "bz"), "a.tar.bz");
  ASSERT_EQ(File::replaceExtension("a.tar.gz", "tar.gz", "tgz"), "a.tgz");
  ASSERT_EQ(File::replaceExtension("a.tart.tar.gz", "tar.gz", "tgz"),
            "a.tart.tgz");
  ASSERT_EQ(File::replaceExtension("a.tart.tar.gz", "tar.bz", "tgz"),
            "a.tart.tar.gz");
  ASSERT_EQ(File::replaceExtension("ar.bz", "tar.bz", "tgz"), "ar.bz");
  ASSERT_EQ(File::replaceExtension("tar.bz", "tar.bz", "tgz"), "tar.bz");
};
TEST_F(FileTest, ParentPath) {
  ASSERT_THAT(File::parentPath("a.trot"), EndsWith("/gallop/bootstrap"));
  ASSERT_THAT(File::parentPath("../example/bootstrap/commentout_bom.trot"),
              EndsWith("/gallop/example/bootstrap"));
};
TEST_F(FileTest, AbsoluteCanonicalPath) {
  ASSERT_THAT(File::absoluteCanonicalPath("a.trot"),
              EndsWith("/gallop/bootstrap/a.trot"));
  ASSERT_THAT(
      File::absoluteCanonicalPath("../example/bootstrap/commentout_bom.trot"),
      EndsWith("/gallop/example/bootstrap/commentout_bom.trot"));
};
TEST_F(FileTest, ReplacePathDirectory) {
  ASSERT_THAT(File::replacePathDirectory("a.trot", "./boot", "../"),
              EndsWith("/gallop/bootstrap/a.trot"));
  ASSERT_THAT(File::replacePathDirectory("a.trot", ".", "/usr/../"),
              EndsWith("/a.trot"));
  ASSERT_THAT(File::replacePathDirectory("a.trot", ".", "../example/"),
              EndsWith("/gallop/example/a.trot"));
};
TEST_F(FileTest, SplitPath) {
  std::vector<std::string> splittedPath;
  size_t splittedPathDepth = 0;

  splittedPath = File::splitPath("/");
  splittedPathDepth = splittedPath.size();
  ASSERT_EQ(splittedPathDepth, (size_t)0);
  splittedPath = File::splitPath("/usr");
  splittedPathDepth = splittedPath.size();
  ASSERT_EQ(splittedPathDepth, (size_t)1);
  ASSERT_EQ(splittedPath[splittedPathDepth - 1], "usr");
  splittedPath = File::splitPath("/tmp/");
  splittedPathDepth = splittedPath.size();
  ASSERT_EQ(splittedPath[splittedPathDepth - 1], "tmp");
  splittedPath = File::splitPath("a.trot");
  splittedPathDepth = splittedPath.size();
  ASSERT_EQ(splittedPath[splittedPathDepth - 1], "bootstrap");
  EXPECT_NE(splittedPath[splittedPathDepth - 1], "a.trot");
  splittedPath = File::splitPath("a.trot", true);
  splittedPathDepth = splittedPath.size();
  ASSERT_EQ(splittedPath[splittedPathDepth - 2], "bootstrap");
  ASSERT_EQ(splittedPath[splittedPathDepth - 1], "a.trot");
  splittedPath = File::splitPath("/Windows", true);
  splittedPathDepth = splittedPath.size();
  ASSERT_EQ(splittedPathDepth, (size_t)1);
  splittedPath = File::splitPath("/Program files", true);
  splittedPathDepth = splittedPath.size();
  ASSERT_EQ(splittedPathDepth, (size_t)1);
};
TEST_F(FileTest, FilenameOrStem) {
  ASSERT_EQ(File::filename("./a.trot"), "a.trot");
  ASSERT_EQ(File::filenameOrStem("./a.trot", true), "a");
  ASSERT_EQ(File::filenameOrStem("./a.tar.gz", "tar.gz", true), "a");
  ASSERT_EQ(File::filenameOrStem("./a.tar.gz", "tgz", true), "a.tar");
};
TEST_F(FileTest, ReadAllBinary) {
  std::vector<char> buffer =
      File::readAllBinary("../example/bootstrap/commentout_bom.trot");
  EXPECT_NE(buffer.size(), (size_t)0);
  ASSERT_ANY_THROW(
      File::readAllBinary("../example/bootstrap/commentout_bom.trot1"));
}
TEST_F(FileTest, GetCurrentDir) {
  ASSERT_THAT(File::getCurrentDir(), EndsWith("/gallop/bootstrap"));
};

} // namespace gallop::IO