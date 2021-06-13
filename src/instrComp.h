#ifndef INSTRCOMP_H
#define INSTRCOMP_H

#include <array>
#include <vector>

struct instrComp {
  std::vector<bool> opCode;
  std::array<std::vector<bool>, 5> groups;
  instrComp(std::vector<bool> oc, std::array<std::vector<bool>, 5> g);
};
#endif
