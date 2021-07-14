#include <array>
#include <vector>
#include <iostream>
#include "commands.cpp"
#include "alu.h"
#include "action.h"
#include "errors.cpp"
#include "registers.h"

void alu::updateState(baseAction *ba, registers *r) {
  switch(ba->ct){
    case R: {
      RAction *a = static_cast<RAction*>(ba);
      RUpdate(a, r);
      break;
    } default: {
      throw unexpectedCommandType();
    }
  }
}

void alu::RUpdate(RAction *ra, registers *r) {
  switch(ra->cn) {
    case ADD: {
      r->setRegister(add(r->getRegister(ra->rs1).get(), r->getRegister(ra->rs2).get()), ra->rd);
      break;
    } case SUB: {
      r->setRegister(sub(r->getRegister(ra->rs1).get(), r->getRegister(ra->rs2).get()), ra->rd);
      break;
    } case AND: {
      r->setRegister(andd(r->getRegister(ra->rs1).get(), r->getRegister(ra->rs2).get()), ra->rd);
      break;
    } case OR: {
      r->setRegister(orr(r->getRegister(ra->rs1).get(), r->getRegister(ra->rs2).get()), ra->rd);
      break;
    } default: {
      throw unexpectedCommandName();
    }
  }
}


std::unique_ptr<std::array<bool, 32>> alu::add(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2) {
  bool carry = false;
  std::unique_ptr<std::array<bool, 32>> res = std::make_unique<std::array<bool, 32>>();

  for (int pos = 31; pos >= 0; --pos) {
    res->at(pos) = carry != (rs1->at(pos) != rs2->at(pos));

    carry = (carry && rs1->at(pos)) 
      || (carry && rs2->at(pos))
      || (rs1->at(pos) && rs2->at(pos));
  }

  return res;
}

std::unique_ptr<std::array<bool, 32>> alu::sub(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2) {
  std::array<bool, 32> rs2Inv;
  for (int i = 0; i < 32; ++i) rs2Inv[i] = !(rs2->at(i));

  bool carry = true;
  std::unique_ptr<std::array<bool, 32>> res = std::make_unique<std::array<bool, 32>>();

  for (int pos = 31; pos >= 0; --pos) {
    res->at(pos) = carry != (rs1->at(pos) != rs2Inv.at(pos));

    carry = (carry && rs1->at(pos)) 
      || (carry && rs2Inv.at(pos))
      || (rs1->at(pos) && rs2Inv.at(pos));
  }

  return res;
}

std::unique_ptr<std::array<bool, 32>> alu::andd(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2) {
  std::unique_ptr<std::array<bool, 32>> res = std::make_unique<std::array<bool, 32>>();

  for (int pos = 0; pos < 32; ++pos) {
    res->at(pos) = rs1->at(pos) && rs2->at(pos);
  }

  return res;
}

std::unique_ptr<std::array<bool, 32>> alu::orr(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2) {
  std::unique_ptr<std::array<bool, 32>> res = std::make_unique<std::array<bool, 32>>();

  for (int pos = 0; pos < 32; ++pos) {
    res->at(pos) = rs1->at(pos) || rs2->at(pos);
  }

  return res;
}

