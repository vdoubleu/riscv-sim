#ifndef ALU_H
#define ALU_H
#include <memory>
#include <array>
#include "action.h"

class registers;

class alu {
  public:
  void updateState(baseAction *ba, registers *r);
  private:
  void RUpdate(RAction *ra, registers *r);
  std::unique_ptr<std::array<bool, 32>> add(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2);
  std::unique_ptr<std::array<bool, 32>> sub(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2);
  std::unique_ptr<std::array<bool, 32>> orr(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2);
  std::unique_ptr<std::array<bool, 32>> andd(std::array<bool, 32> *rs1, std::array<bool, 32> *rs2);
};
#endif
