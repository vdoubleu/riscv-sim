#include <array>
#include <memory>
#include <iostream>
#include "instrComp.h"
#include "disassembler.h"

std::unique_ptr<instrComp> disassembler::disassemble(std::array<bool, 32> bitArr) {
  std::array<std::vector<bool>, 5> groups;

  std::vector<bool> opCode(bitArr.end() - 7, bitArr.end());

  groups.at(0) = std::vector<bool>(bitArr.begin(), bitArr.begin() + 7);
  groups.at(1) = std::vector<bool>(bitArr.begin() + 7, bitArr.begin() + 12);
  groups.at(2) = std::vector<bool>(bitArr.begin() + 12, bitArr.begin() + 17);
  groups.at(3) = std::vector<bool>(bitArr.begin() + 17, bitArr.begin() + 20);
  groups.at(4) = std::vector<bool>(bitArr.begin() + 20, bitArr.begin() + 25);

  return std::make_unique<instrComp>(opCode, groups);
}
