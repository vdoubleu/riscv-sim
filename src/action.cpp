#include "action.h"
#include "commands.cpp"

baseAction::baseAction(commandType c): ct{c} {}

RAction::RAction(int rs1, int rs2, int rd, commandName name, commandType type): 
  rs1{rs1}, rs2{rs2}, rd{rd}, cn{name}, baseAction{type} {}
