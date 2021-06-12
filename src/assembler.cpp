#include <array>
#include <memory>
#include <string>
#include <regex>
#include <bitset>
#include <iostream>
#include "commands.cpp"
#include "errors.cpp"
#include "assembler.h"

std::array<bool, 32> assembler::assemble(std::unique_ptr<command> c) {
  std::string outputBitString = "";
  switch(c->type) {
    case R:
      outputBitString = assembleR(std::move(c));
      break;
    case I:
      outputBitString = assembleI(std::move(c));
      break;
    case B:
      outputBitString = assembleB(std::move(c));
      break;
    case S:
      outputBitString = assembleS(std::move(c));
      break;
    case NA:
      outputBitString = "00000000000000000000000000000000";
      break;
    default:
      throw unexpectedCommandType();
  }

  return bitStringToBitArr(outputBitString);
}

std::array<bool, 32> assembler::bitStringToBitArr(std::string bitString) {
  std::array<bool, 32> bitArr;

  for (size_t pos = 0; pos < bitString.length(); ++pos) {
    bitArr[pos] = (bitString.at(pos) == '1');
  }

  return bitArr;
}

std::string assembler::bitArrToBitString(std::array<bool, 32> bitArr) {
  std::string bitStr = "";

  for (bool b : bitArr)
    bitStr += b ? "1" : "0";

  return bitStr;
}

std::string assembler::assembleR(std::unique_ptr<command> c) {
  std::string rd = getRegisterInBits(c->field1);
  std::string rs1 = getRegisterInBits(c->field2);
  std::string rs2 = getRegisterInBits(c->field3);

  std::string rCode = "0110011";

  if (machineIdMapping.find(c->name) == machineIdMapping.end()) {
    throw unexpectedCommandType();
  } else {
    std::vector<std::string> bitId = machineIdMapping.at(c->name);
    return bitId.at(0) + rs2 + rs1 + bitId.at(1) + rd + rCode;
  }
}

std::string assembler::assembleI(std::unique_ptr<command> c) {
  std::string rd = getRegisterInBits(c->field1);
  std::string rs1 = getRegisterInBits(c->field2);
  std::string imm = getImmInBits(c->field3);

  std::string iCode = c->name == JALR ? "1100111" : "0010011";

  if (machineIdMapping.find(c->name) == machineIdMapping.end()) {
    throw unexpectedCommandType();
  } else {
    return imm + rs1 + machineIdMapping.at(c->name).at(0) + rd + iCode;
  }
}

std::string assembler::assembleB(std::unique_ptr<command> c) {
  std::string rs1 = getRegisterInBits(c->field1);
  std::string rs2 = getRegisterInBits(c->field2);
  std::string imm = getImmInBits(c->field3, 13);

  if (std::stoi(c->field3) % 4 != 0) throw invalidBranchImmediate();

  std::string imm12 = imm.substr(0, 1);
  std::string imm11 = imm.substr(1, 1);
  std::string imm105 = imm.substr(2, 6);
  std::string imm41 = imm.substr(8, 4);

  std::string bCode = "1100011";

  if (machineIdMapping.find(c->name) == machineIdMapping.end()) {
    throw unexpectedCommandType();
  } else {
    return imm12 + imm105 + rs2 + rs1 + machineIdMapping.at(c->name).at(0) + imm41 + imm11 + bCode;
  }
}

std::string assembler::assembleS(std::unique_ptr<command> c) {
  std::string rs1 = getRegisterInBits(c->field1);
  std::string rs2 = getRegisterInBits(c->field2);
  std::string imm = getImmInBits(c->field3);

  std::string imm115 = imm.substr(0, 7);
  std::string imm40 = imm.substr(8, 5);

  std::string sCode = "0100011";

   if (machineIdMapping.find(c->name) == machineIdMapping.end()) {
    throw unexpectedCommandType();
  } else {
    return imm115 + rs2 + rs1 + machineIdMapping.at(c->name).at(0) + imm40 + sCode;
  }
}

std::string assembler::getRegisterInBits(std::string reg) {
  std::regex isReg ("x([0-9]|[0-2][0-9]|3[0-1])");
  bool matches = std::regex_match(reg, isReg);
  if (matches) {
    return std::bitset<5>(std::stoi(reg.substr(1, reg.length()))).to_string();
  } else
    throw unrecognisedReg();
}

std::string assembler::getImmInBits(std::string imm, int bitStringSize) {
  std::regex allNumber("\\-?[0-9]+");
  bool matches = std::regex_match(imm, allNumber);
  if (matches) {
    if (bitStringSize == 12)
      return std::bitset<12>(std::stoi(imm)).to_string();
    else if (bitStringSize == 13)
      return std::bitset<13>(std::stoi(imm)).to_string();
    else
      throw unrecognisedImm();
  } else
    throw unrecognisedImm();
}