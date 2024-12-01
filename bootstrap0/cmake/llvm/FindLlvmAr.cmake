find_program(LLVM_ARCHIVER llvm-ar llvm-ar.exe
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

mark_as_advanced(LLVM_ARCHIVER)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LlvmAr
  REQUIRED_VARS
  LLVM_ARCHIVER
)

if(LLVMAR_FOUND AND NOT TARGET LLVMAR::LLVMAR)
  set(CMAKE_CXX_COMPILER_AR "${LLVM_ARCHIVER}")
elseif(LLVMAR_NOTFOUND)
  include(SetShCmdVar)
  execute_process(
    COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} llvm-ar"
    OUTPUT_VARIABLE CMAKE_CXX_COMPILER_AR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if("" STREQUAL "${CMAKE_CXX_COMPILER_AR}")
    execute_process(
      COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} ar"
      OUTPUT_VARIABLE CMAKE_CXX_COMPILER_AR
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  endif()
endif()
message("Archiver \t\t\t\t: ${CMAKE_CXX_COMPILER_AR}")
