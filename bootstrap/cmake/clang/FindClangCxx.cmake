find_program(CLANG_CXX_COMPILER clang++ clang++.exe
  PATHS
  ENV CLANG_ROOT
  ${CLANG_ROOT}
  /usr
  /usr/local
  /opt
  /opt/local
  ${VCINSTALLDIR}/Tools/LLVM
  C:/Program\ Files/LLVM
  C:/Program\ Files\ \(x86\)/LLVM
  C:/msys64/mingw64/
  C:/msys64/clang64/
  PATH_SUFFIXES
  "bin"
)

mark_as_advanced(CLANG_CXX_COMPILER)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ClangCxx
  REQUIRED_VARS
  CLANG_CXX_COMPILER
)

if(CLANGCXX_FOUND AND NOT TARGET CLANGCXX::CLANGCXX)
  set(CMAKE_CXX_COMPILER "${CLANG_CXX_COMPILER}")
elseif(CLANGXX_NOTFOUND)
  include(SetShCmdVar)
  execute_process(
    COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} clang++"
    OUTPUT_VARIABLE CMAKE_CXX_COMPILER
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

message("Clang C++ Compiler\t\t\t: ${CMAKE_CXX_COMPILER}")
