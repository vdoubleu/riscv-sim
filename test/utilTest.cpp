#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <array>
#include "../src/assembler.h"
#include "../src/util.h"

BOOST_AUTO_TEST_CASE(test_bitArr_bitString) {
  assembler a;
  util u;

  std::array<bool, 32> bitArr;
  std::string bitString = "";

  for (int i  = 0; i < 32; ++i) {
    bitArr[i] = i % 2 == 0;
    bitString += i % 2 == 0? "1" : "0";
  }

  std::array<bool, 32> resArr = u.bitStringToBitArr(bitString);
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr.begin(), bitArr.end(), resArr.begin(), resArr.end());
}

BOOST_AUTO_TEST_CASE(test_bitString_bitArr) {
  assembler a;
  util u;

  std::array<bool, 32> bitArr;
  std::string bitString = "";

  for (int i  = 0; i < 32; ++i) {
    bitArr[i] = i % 2 == 0;
    bitString += i % 2 == 0? "1" : "0";
  }

  BOOST_CHECK_EQUAL(u.bitArrToBitString(bitArr), bitString);
}

BOOST_AUTO_TEST_CASE(test_unsignedBin_num) {
  util u;

  BOOST_CHECK_EQUAL(u.unsignedBitStringToNum("0011"), 3);

  BOOST_CHECK_EQUAL(u.unsignedBitStringToNum("1001"), 9);
}

BOOST_AUTO_TEST_CASE(test_signedBin_num) {
  util u;

  BOOST_CHECK_EQUAL(u.signedBitStringToNum("0011"), 3);
  BOOST_CHECK_EQUAL(u.signedBitStringToNum("1001"), -7);
  BOOST_CHECK_EQUAL(u.signedBitStringToNum("0000"), 0);
  BOOST_CHECK_EQUAL(u.signedBitStringToNum("100000"), -32);
}
