find_program(LLVM_ASSEMBLER llvm-as llvm-as.exe
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

mark_as_advanced(LLVM_ASSEMBLER)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LlvmAs
  REQUIRED_VARS
  LLVM_ASSEMBLER
)

if(LLVMAS_FOUND AND NOT TARGET LLVMAS::LLVMAS)
  set(CMAKE_CXX_COMPILER_AS "${LLVM_ASSEMBLER}")
elseif(LLVMAS_NOTFOUND)
  include(SetShCmdVar)
  execute_process(
    COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} llvm-as"
    OUTPUT_VARIABLE CMAKE_CXX_COMPILER_AS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if("" STREQUAL "${CMAKE_CXX_COMPILER_AS}")
    execute_process(
      COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} as"
      OUTPUT_VARIABLE CMAKE_CXX_COMPILER_AS
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  endif()
endif()
message("Assembler \t\t\t\t: ${CMAKE_CXX_COMPILER_AS}")
