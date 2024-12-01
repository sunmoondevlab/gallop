find_program(LLVM_RANLIB llvm-ranlib llvm-ranlib.exe
  PATHS
  ENV LLVM_ROOT
  ${LLVM_ROOT}
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

mark_as_advanced(LLVM_RANLIB)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LlvmRanlib
  REQUIRED_VARS
  LLVM_RANLIB
)

if(LLVMRANLIB_FOUND AND NOT TARGET LLVMRANLIB::LLVMRANLIB)
  set(CMAKE_CXX_COMPILER_AR "${LLVM_RANLIB}")
elseif(LLVMRANLIB_NOTFOUND)
  include(SetShCmdVar)
  execute_process(
    COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} llvm-ranlib"
    OUTPUT_VARIABLE CMAKE_CXX_COMPILER_AR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if("" STREQUAL "${CMAKE_CXX_COMPILER_AR}")
    execute_process(
      COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} ranlib"
      OUTPUT_VARIABLE CMAKE_CXX_COMPILER_AR
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  endif()
endif()
message("ranlib \t\t\t\t\t: ${CMAKE_CXX_COMPILER_AR}")
