#include <string>
#include "inputCleaner.h"

std::string inputCleaner::cleanInput(std::string input) {
  std::string out = trim(input);
  return out;
}

std::string inputCleaner::ltrim(std::string s) {
  std::size_t found = s.find_first_not_of(" \t\f\v\n\r");
  if (found != std::string::npos)
    s.erase(0, found);
  else
    s.clear();
  return s;
}

std::string inputCleaner::rtrim(std::string s) {
  std::size_t found = s.find_last_not_of(" \t\f\v\n\r");
  if (found != std::string::npos)
    s.erase(found + 1);
  else
    s.clear();

  return s;
}

std::string inputCleaner::trim(std::string s) {
  return ltrim(rtrim(s));
}
