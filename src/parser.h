#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <cctype>
#include <algorithm>
#include <vector>
#include "inputCleaner.h"

class command;

class parser {
  inputCleaner ic;

  public:
    std::unique_ptr<command> parseCommand(std::string s);

  private:
    std::string popInstrPart(std::string &s);
    std::vector<std::string> parseParms(std::string &s);
    std::string toUpperCase(std::string s);
};
#endif
