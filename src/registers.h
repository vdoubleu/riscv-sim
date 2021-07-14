#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>
#include <memory>

class registers{
  std::size_t pc;
  std::array<std::unique_ptr<std::array<bool, 32>>, 32> regs;

  public:
  registers();
  std::size_t increasePC();
  std::size_t jumpPc(int jump);
  void setRegister(std::unique_ptr<std::array<bool, 32>> val, int reg);
  std::unique_ptr<std::array<bool, 32>> getRegister(int reg);
};
#endif
