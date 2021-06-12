#include <iostream>
#include <memory>
#include <array>
#include "parser.h"
#include "assembler.h"
#include "commands.cpp"

int main() {
  parser p;
  assembler a;

  std::array<bool, 32> instr = a.assemble(p.parseCommand("ADD x1,x2,x3"));
  for (bool i : instr) {
    std::cout << i;
  }
  std::cout << std::endl;
}
