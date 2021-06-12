#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "parser.h"
#include "assembler.cpp"

BOOST_AUTO_TEST_CASE(test_assemble_2){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("BEQ x19,x10,16"));
  std::array<bool, 32> res = a.bitStringToBitArr("00000000101010011000100001100011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr.begin(), bitArr.end(), res.begin(), res.end());

  std::array<bool, 32> bitArr2 = a.assemble(p.parseCommand("BEQ x19,x10,-8"));
  std::array<bool, 32> res2 = a.bitStringToBitArr("11111110101010011000110011100011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr2.begin(), bitArr2.end(), res2.begin(), res2.end());
}
