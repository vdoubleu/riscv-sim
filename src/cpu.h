#ifndef CPU_H
#define CPU_H
#include <array>
#include <vector>
#include <memory>
#include <string>
#include "registers.h"
#include "instrComp.h"
#include "commands.cpp"
#include "util.h"
#include "errors.cpp"
#include "disassembler.h"
#include "alu.h"
#include "action.h"

class cpu {
  registers r;
  disassembler d;
  util u;
  alu a;

  public:
    cpu();
    void processInstr(std::array<bool, 32> data, registers *r);

  private:
    commandType getCommandType(std::vector<bool> opCode);
    std::unique_ptr<baseAction> createBaseAction(instrComp *ic, commandType ct);
    std::unique_ptr<baseAction> createRAction(instrComp *ic);
};
#endif
