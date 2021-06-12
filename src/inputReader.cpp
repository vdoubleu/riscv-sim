#include <string>
#include <iostream>
#include "inputCleaner.h"
#include "inputReader.h"

std::string inputReader::readInput() {
  std::string in = readFromCmd();
  return cleaner.cleanInput(in);
}

std::string inputReader::readFromCmd() {
  std::string inputLine = "";
  std::getline(std::cin, inputLine);
  return inputLine;
}
