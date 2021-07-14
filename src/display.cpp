#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "display.h"
#include "registers.h"
#include "memory.h"
#include "util.h"

std::string display::displayState(registers *r, memory *m) {
  std::string output = "";
  output += "| Register | Value |\n";
  output += "--------------------\n";

  for (int regNum = 0; regNum < 32; ++regNum) {
    std::array<bool, 32> val = *(r->getRegister(regNum));
    std::string padding = regNum >= 10 ? "" : " ";
    output += "   x" + std::to_string(regNum) + padding + "     |   " + std::to_string(u.signedBitArrToNum(std::vector<bool>(val.begin(), val.end()))) + "  \n";
  }

  if (!disablePrint)
    std::cout << output;

  return output;
}
