#include <array>
#include <memory>

struct instrComp;

class disassembler {
  public:
    std::unique_ptr<instrComp> disassemble(std::array<bool, 32> bitArr);
};
