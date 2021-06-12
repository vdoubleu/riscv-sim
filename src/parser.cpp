#include <string>
#include <memory>
#include <cctype>
#include <algorithm>
#include <vector>
#include "commands.cpp"
#include "parser.h"

std::unique_ptr<command> parser::parseCommand(std::string s) {
  if (s == "")
    return std::make_unique<command>(NA, None);

  std::string instrCmd = toUpperCase(popInstrPart(s));

  if (commandMapping.find(instrCmd) == commandMapping.end()) {
    return std::make_unique<command>(NA, None);
  } else {
    std::pair<commandType, commandName> commandInfo = commandMapping.at(instrCmd);
    std::vector<std::string> params = parseParms(s);
    return std::make_unique<command>(commandInfo.first, commandInfo.second, params);
  }
}

std::string parser::popInstrPart(std::string &s) {
  std::size_t endOfFirstWord = s.find(" ");

  // checks if string is just one word. e.g. "hello"
  std::string out = "";
  if (endOfFirstWord == std::string::npos && s.length() > 0) {
    out = s;
    s.clear();
  } else {
    out = s.substr(0, endOfFirstWord);
    s.erase(0, endOfFirstWord + 1); // plus 1 to get rid of white space as well
  }

  return out;
}

std::vector<std::string> parser::parseParms(std::string &s) {
  std::vector<std::string> out;

  std::string firstParam;
  std::size_t firstParamEnd;
  while (!s.empty()) {
    firstParamEnd = s.find(",");

    if (firstParamEnd == std::string::npos) {
      firstParam = ic.cleanInput(s);
      s.clear();
    } else {
      firstParam = ic.cleanInput(s.substr(0, firstParamEnd));
      s.erase(0, firstParamEnd + 1);
    }
    out.push_back(firstParam);
  }

  return out;
}

std::string parser::toUpperCase(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
    [](unsigned char c) {return std::toupper(c);});

  return s;
}
