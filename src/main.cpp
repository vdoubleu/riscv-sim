#include <iostream>
#include <memory>
#include <array>
#include "parser.h"
#include "assembler.h"
#include "inputReader.h"
#include "inputCleaner.h"
#include "commands.cpp"

int main() {
  parser p;
  assembler a;
  inputCleaner ic;
  inputReader ir;
/*
  std::array<bool, 32> instr = a.assemble(p.parseCommand("ADD x1,x2,x3"));
  for (bool i : instr) {
    std::cout << i;
  }
  */

  while (true) {
    std::string in = ir.readInput();
    std::string bitStr = a.bitArrToBitString(a.assemble(p.parseCommand(ic.cleanInput(in))));
    std::cout << bitStr << std::endl;
  }

  /*
  std::array<bool, 32> bitArr;
  std::string bitString = "";

  for (int i  = 0; i < 32; ++i) {
    bitArr[i] = i % 2 == 0;
    bitString += i % 2 == 0? "1" : "0";
  }
  */


  //std::cout << std::endl;
}
