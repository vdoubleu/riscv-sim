#ifndef DISPLAY_H
#define DISPLAY_H
#include "util.h"
#include <string>

class registers;
class memory;

class display {
  util u;
  bool disablePrint;

  public:
  display(): disablePrint{false} {}
  display(bool d): disablePrint{d} {}
  std::string displayState(registers *r, memory *m);
};

#endif
