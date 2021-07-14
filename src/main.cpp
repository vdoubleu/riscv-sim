#include <iostream>
#include <memory>
#include <array>
#include <regex>
#include "parser.h"
#include "assembler.h"
#include "inputReader.h"
#include "util.h"
#include "inputCleaner.h"
#include "commands.cpp"
#include "registers.h"
#include "cpu.h"
#include "display.h"

int parseInitRegVal(std::string inpt) {
  std::regex expr ("x[0-9]|x[1-2][0-9]|x3[0-1]");

  if (std::regex_match(inpt, expr)) {
    return stoi(inpt.substr(1, inpt.length() - 1));
  } else if (inpt == "c") {
    return -1;
  } else if (inpt == "") {
    return -2;
  } else {
    std::cerr << "invalid command, registers must be in this format: \"x12 = 2\"";
    return -3;
  }
}

int main() {
  parser p;
  assembler a;
  inputCleaner ic;
  inputReader ir;
  util u;
  registers r;
  cpu c;
  display d;

  bool exit = false;

  while(!exit) {
    std::string inpt;
    int val;
    std::string x;
    std::cout << "Enter initial register values (<register> = <value>) or enter 'c' to continue:" << std::endl;
    std::cin >> inpt;
    int parsedRes = parseInitRegVal(inpt);
    if (parsedRes == -1) break;
    else if (parsedRes == -2) { exit = true; break; }
    else if (parsedRes == -3) continue;

    std::cin >> x >> val;
    r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(val)), parsedRes);

    d.displayState(&r, nullptr);
    std::cout << "\n\n" << std::endl;
  }

  std::cout << "Initial registers set:" << std::endl;
  d.displayState(&r, nullptr);
  std::cout << "\n\n" << std::endl;

  std::cin >> std::ws;
  while (!exit) {
    std::string in = ir.readInput();
    if (in == "") break;
    std::array<bool, 32> comm = a.assemble(p.parseCommand(ic.cleanInput(in)));
    c.processInstr(comm, &r);
    d.displayState(&r, nullptr);
    std::cout << "\n\n" << std::endl;
  }
}
