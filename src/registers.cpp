#include <array>
#include <memory>
#include "registers.h"

registers::registers(): pc{0} {
  for(std::size_t ind = 0; ind < regs.size(); ++ind) {
    regs.at(ind) = std::make_unique<std::array<bool, 32>>();
  }
}
std::size_t registers::increasePC() { return pc += 4; }
std::size_t registers::jumpPc(int jump) { return pc = pc + jump; }
void registers::setRegister(std::unique_ptr<std::array<bool, 32>> val, int reg) { if (reg != 0) regs.at(reg) = std::move(val); }
std::unique_ptr<std::array<bool, 32>> registers::getRegister(int reg) { 
  return std::make_unique<std::array<bool, 32>>(*(regs.at(reg).get()));
}
