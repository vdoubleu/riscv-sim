#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <array>
#include "../src/assembler.h"
#include "../src/util.h"
#include "../src/disassembler.h"
#include "../src/instrComp.h"


BOOST_AUTO_TEST_CASE(test_disassemble_basic) {
  disassembler d;
  assembler a;
  util u;

  std::array<bool, 32> bitArr = u.bitStringToBitArr("01011011101111011111011111101111");
  std::unique_ptr<instrComp> ic = d.disassemble(bitArr);

  BOOST_CHECK_EQUAL(u.bitArrToBitString(ic->opCode), "1101111");
  BOOST_CHECK_EQUAL(u.bitArrToBitString(ic->groups.at(0)), "0101101");
  BOOST_CHECK_EQUAL(u.bitArrToBitString(ic->groups.at(1)), "11011");
  BOOST_CHECK_EQUAL(u.bitArrToBitString(ic->groups.at(2)), "11011");
  BOOST_CHECK_EQUAL(u.bitArrToBitString(ic->groups.at(3)), "111");
  BOOST_CHECK_EQUAL(u.bitArrToBitString(ic->groups.at(4)), "01111");
}
