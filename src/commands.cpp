#ifndef COMMANDS_CPP
#define COMMANDS_CPP

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

enum commandName {
  ADD,
  SUB,
  OR,
  AND,

  JALR,

  ADDI,
  XORI,
  ORI,
  ANDI,

  BEQ,
  BNE,
  BLT,
  BGE,

  SB,
  SH,
  SW,

  None
};

enum commandType { NA, R, I, S, B, U, J };

static const std::unordered_map<std::string, std::pair<commandType, commandName>> commandMapping 
  {
    {"ADD", {R, ADD}},
    {"SUB", {R, SUB}},
    {"OR", {R, OR}},
    {"AND", {R, AND}},

    {"JALR", {I, JALR}},

    {"ADDI", {I, ADDI}},
    {"XORI", {I, XORI}},
    {"ORI", {I, ORI}},
    {"ANDI", {I, ANDI}},

    {"BEQ", {B, BEQ}},
    {"BNE", {B, BNE}},
    {"BLT", {B, BLT}},
    {"BGE", {B, BGE}},

    {"SB", {S, SB}},
    {"SH", {S, SH}},
    {"SW", {S, SW}}
  };

static const std::unordered_map<commandName, std::vector<std::string>> machineIdMapping 
  {
    {ADD, {"0000000", "000"}},
    {SUB, {"0100000", "000"}},
    {OR, {"0000000", "110"}},
    {AND, {"0000000", "111"}},

    {JALR, {"000"}},

    {ADDI, {"000"}},
    {XORI, {"100"}},
    {ORI, {"110"}},
    {ANDI, {"111"}},

    {BEQ, {"000"}},
    {BNE, {"001"}},
    {BLT, {"100"}},
    {BGE, {"101"}},

    {SB, {"000"}},
    {SH, {"001"}},
    {SW, {"010"}}
  };

struct command {
  commandType type;
  commandName name;
  std::string field1;
  std::string field2;
  std::string field3;

  command(commandType t, commandName n, std::vector<std::string> params): type{t}, name{n} {
    if (params.size() == 3) {
      field1 = params[0];
      field2 = params[1];
      field3 = params[2];
    } else if (params.size() == 2) {
      field1 = params[0];
      field2 = params[1];
      field3 = "";
    } else if (params.size() == 1) {
      field1 = params[1];
      field2 = "";
      field3 = "";
    }
  }
  command(commandType t, commandName n): 
    type{t}, name{n}, field1{""}, field2{""}, field3{""} {}
};
#endif
