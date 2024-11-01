find_package(LlvmConfig REQUIRED)
include(SetShCmdVar)
execute_process(
  COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "llvm-config${EXEC_CMD_EXT} --includedir"
  OUTPUT_VARIABLE LLVM_INCLUDEDIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
  COMMAND ${EXEC_TERMINAL_CMD} ${EXEC_TERMINAL_CMD_OPT} "llvm-config${EXEC_CMD_EXT} --libfiles"
  OUTPUT_VARIABLE LLVM_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REPLACE "-l" "" LLVM_LIBS "${LLVM_LIBS}")

message("LLVM include dir\t\t\t: ${LLVM_INCLUDEDIR}")
message("LLVM libs file\t\t\t\t: ${LLVM_LIBS}")
