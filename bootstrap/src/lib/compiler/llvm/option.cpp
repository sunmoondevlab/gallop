#include "compiler/llvm/option.hpp"
using namespace gallop::Compiler::LLVM;

Option::Option() : entryPointId("") {};
Option::Option(const Option &rhs) : entryPointId(rhs.entryPointId) {};
Option &Option::operator=(const Option &rhs) {
  entryPointId = rhs.entryPointId;
  return *this;
};
std::string Option::getEntryPointId() const { return entryPointId; };
void Option::setEntryPointId(const std::string entryPointId_) {
  entryPointId = entryPointId_;
};
