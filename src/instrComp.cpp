#include <string>
#include <array>
#include <vector>
#include "instrComp.h"

instrComp::instrComp(std::vector<bool> oc, std::array<std::vector<bool>, 5> g): opCode {oc}, groups{g} {}
