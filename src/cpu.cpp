#include <array>
#include <vector>
#include <memory>
#include <string>
#include "registers.h"
#include "instrComp.h"
#include "commands.cpp"
#include "util.h"
#include "errors.cpp"
#include "cpu.h"
#include "action.h"

cpu::cpu() {}

void cpu::processInstr(std::array<bool, 32> data, registers *r) {
  std::unique_ptr<instrComp> ic = d.disassemble(data);
  commandType ct = getCommandType(ic->opCode);

  std::unique_ptr<baseAction> ba = createBaseAction(ic.get(), ct);
  a.updateState(ba.get(), r);
}

commandType cpu::getCommandType(std::vector<bool> opCode) {
  std::string ocStr = u.bitArrToBitString(opCode);

  if (ocStr == machineTypeMapping.at(R))
    return R;
  else if (ocStr == machineTypeMapping.at(I))
    return I;
  else if (ocStr == machineTypeMapping.at(B))
    return B;
  else if (ocStr == machineTypeMapping.at(S))
    return S;
  else
    throw unrecognisedOpCode();
}

std::unique_ptr<baseAction> cpu::createBaseAction(instrComp *ic, commandType ct) {
  switch (ct) {
    case R: {
      return createRAction(ic);
      break;
    } default:
      throw unrecognisedOpCode();
  }
}

std::unique_ptr<baseAction> cpu::createRAction(instrComp *ic) {
  int rs1 = u.unsignedBitArrToNum(ic->groups.at(2));
  int rs2 = u.unsignedBitArrToNum(ic->groups.at(1));
  int rd = u.unsignedBitArrToNum(ic->groups.at(4));
  std::string funCode = u.bitArrToBitString(ic->groups.at(0)) + u.bitArrToBitString(ic->groups.at(3));
  commandName cn = None;

  for (std::pair<commandName, std::vector<std::string>> mapping : machineIdMapping) {
    if (mapping.second.size() == 2) {
      std::string resFuncCode = mapping.second.at(0) + mapping.second.at(1);
      if (funCode == resFuncCode) 
        cn = mapping.first;
    }
  }

  if (cn == None)
    throw unexpectedRCommand();
 
  return std::make_unique<RAction>(rs1, rs2, rd, cn, R);
}
