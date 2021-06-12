#ifndef INPUTCLEANER_H
#define INPUTCLEANER_H

#include <string>

class inputCleaner {
  public:
    std::string cleanInput(std::string input);

  private:
    std::string ltrim(std::string s);
    std::string rtrim(std::string s);
    std::string trim(std::string s);
};

#endif
