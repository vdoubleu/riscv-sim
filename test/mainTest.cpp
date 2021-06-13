#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <string>
#include <memory>
#include <iostream>
#include "../src/inputCleaner.h"
#include "../src/parser.h"
#include "../src/assembler.h"
#include "../src/commands.cpp"

BOOST_AUTO_TEST_CASE(test_full_1) {
  inputCleaner cleaner;
  parser p;
  assembler a;

  std::string input = " ADD x1, x2, x3   ";
  std::string out = "00000000001100010000000010110011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(a.assemble(p.parseCommand(cleaner.cleanInput(input)))), out);
}

BOOST_AUTO_TEST_CASE(test_full_2) {
  inputCleaner cleaner;
  parser p;
  assembler a;

  std::string input = " XORI x1, x1, 12   ";
  std::string out = "00000000110000001100000010010011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(a.assemble(p.parseCommand(cleaner.cleanInput(input)))), out);
}
