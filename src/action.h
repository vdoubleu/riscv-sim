#ifndef ACTION_H
#define ACTION_H
#include "commands.cpp"

struct baseAction {
  commandType ct;
  baseAction(commandType c);
};

struct RAction : public baseAction {
  int rs1;
  int rs2;
  int rd;
  commandName cn;
  RAction(int rs1, int rs2, int rd, commandName name, commandType type);
};
#endif
