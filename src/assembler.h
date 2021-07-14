#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <array>
#include <memory>
#include <string>
#include <regex>
#include <bitset>
#include <iostream>
#include "errors.cpp"
#include "util.h"

class command;

class assembler {
  util u;

  public:
  std::array<bool, 32> assemble(std::unique_ptr<command> c);

  private:
  std::string assembleR(std::unique_ptr<command> c);
  std::string assembleI(std::unique_ptr<command> c);
  std::string assembleB(std::unique_ptr<command> c);
  std::string assembleS(std::unique_ptr<command> c);
  std::string getRegisterInBits(std::string reg);
  std::string getImmInBits(std::string imm, int bitStringSize=12);
};
#endif
