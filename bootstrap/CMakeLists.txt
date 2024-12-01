cmake_minimum_required(VERSION 3.29)

# project setting
project(gallop0
    VERSION 0.1.0
    DESCRIPTION "'gallop' is a new programing language"
    HOMEPAGE_URL "https://github.com/sunmoondevlab/gallop"
    LANGUAGES CXX C
)

message("Project name\t\t\t\t: ${PROJECT_NAME}")
message("Project source directory\t\t: ${PROJECT_SOURCE_DIR}")
message("Project build directory\t\t\t: ${PROJECT_BINARY_DIR}")
message("Project version number\t\t\t: ${PROJECT_VERSION}")
message("Project description\t\t\t: ${PROJECT_DESCRIPTION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include("ConfigCLang")
include("ConfigLLVM")
include("ConfigGoogleTest")

# build script

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if("Debug" STREQUAL "${CMAKE_BUILD_TYPE}" OR "RelWithDebInfo" STREQUAL "${CMAKE_BUILD_TYPE}")
    add_compile_definitions("-DFOR_DEBUG")
endif()

include(LLVMConfig)
include(MLIRConfig)

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)


add_subdirectory(${CMAKE_SOURCE_DIR}/include)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${LLVM_INCLUDEDIR}
    ${GOOGLETEST_INCLUDEDIR}
)
file(GLOB_RECURSE LIB_SOURCE_FILES RELATIVE "${CMAKE_SOURCE_DIR}/" "src/lib/*")
add_library("${PROJECT_NAME}.a" STATIC ${LIB_SOURCE_FILES})
file(GLOB MAIN_SOURCE_FILES RELATIVE "${CMAKE_SOURCE_DIR}/" "src/*")

add_executable(${PROJECT_NAME} ${MAIN_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}.a" ${LLVM_LIBS})

if("Debug" STREQUAL "${CMAKE_BUILD_TYPE}")
    file(GLOB_RECURSE TEST_SOURCE_FILES RELATIVE "${CMAKE_SOURCE_DIR}/" "test/*")
    add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
    target_link_libraries("${PROJECT_NAME}_test"
        PUBLIC
        ${LLVM_LIBS}
        "${PROJECT_NAME}.a"
        ${GOOGLETEST_LIBDIR}/libgtest.a
        ${GOOGLETEST_LIBDIR}/libgtest_main.a
        ${GOOGLETEST_LIBDIR}/libgmock.a
        ${GOOGLETEST_LIBDIR}/libgmock_main.a
        pthread)
    add_test(NAME test COMMAND "${PROJECT_NAME}_test")
    enable_testing()
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

