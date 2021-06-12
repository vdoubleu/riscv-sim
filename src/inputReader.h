#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <string>
#include <iostream>
#include "inputCleaner.h"

class inputReader{
  inputCleaner cleaner;
  public:
    std::string readInput();
  private:
    std::string readFromCmd();
};

#endif
