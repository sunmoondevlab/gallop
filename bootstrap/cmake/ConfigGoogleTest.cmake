
# cmakeのFetchContent機能をinclude
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/googletest)
find_package(GoogleTest REQUIRED)
