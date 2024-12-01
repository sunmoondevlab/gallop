set(GOOGLETEST_INCLUDEDIR "${CMAKE_SOURCE_DIR}/googletest/include")
set(GOOGLETEST_LIBDIR "${CMAKE_SOURCE_DIR}/googletest/lib")
mark_as_advanced(GOOGLETEST_INCLUDEDIR GOOGLETEST_LIBDIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GoogleTest
    REQUIRED_VARS
    GOOGLETEST_INCLUDEDIR
    GOOGLETEST_LIBDIR
)

message("Google test include dir\t\t\t: ${GOOGLETEST_INCLUDEDIR}")
message("Google test lib dir\t\t\t: ${GOOGLETEST_LIBDIR}")
