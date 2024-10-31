find_program(LLVM_CONFIG llvm-config llvm-config.exe
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

mark_as_advanced(LLVM_CONFIG)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LlvmConfig
  REQUIRED_VARS
  LLVM_CONFIG
)

if(LLVMCONFIG_NOTFOUND)
  include(SetShCmdVar)
  execute_process(
    COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "which${EXEC_CMD_EXT} llvm-config"
    OUTPUT_VARIABLE LLVM_CONFIG
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()
