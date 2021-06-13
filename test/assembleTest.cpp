#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <array>
#include "../src/parser.h"
#include "../src/assembler.h"
#include "../src/commands.cpp"

BOOST_AUTO_TEST_CASE(test_bitArr_bitString) {
  assembler a;

  std::array<bool, 32> bitArr;
  std::string bitString = "";

  for (int i  = 0; i < 32; ++i) {
    bitArr[i] = i % 2 == 0;
    bitString += i % 2 == 0? "1" : "0";
  }

  std::array<bool, 32> resArr = a.bitStringToBitArr(bitString);
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr.begin(), bitArr.end(), resArr.begin(), resArr.end());
}

BOOST_AUTO_TEST_CASE(test_bitString_bitArr) {
  assembler a;

  std::array<bool, 32> bitArr;
  std::string bitString = "";

  for (int i  = 0; i < 32; ++i) {
    bitArr[i] = i % 2 == 0;
    bitString += i % 2 == 0? "1" : "0";
  }

  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), bitString);
}

BOOST_AUTO_TEST_CASE(test_assemble_add){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("ADD x1,x2,x3"));
  std::string res = "00000000001100010000000010110011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);
}

BOOST_AUTO_TEST_CASE(test_assemble_sub){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("SUB x1,x2,x3"));
  std::string res = "01000000001100010000000010110011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);
}

BOOST_AUTO_TEST_CASE(test_assemble_or) {
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("OR x1,x2,x3"));
  std::string res = "00000000001100010110000010110011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);
}

BOOST_AUTO_TEST_CASE(test_assemble_AND) {
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("AND x1,x2,x3"));
  std::string res = "00000000001100010111000010110011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);
}

BOOST_AUTO_TEST_CASE(test_assemble_jalr){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("JALR x1,x2,123"));
  std::string res = "00000111101100010000000011100111";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);

  std::array<bool, 32> bitArr2 = a.assemble(p.parseCommand("JALR x1,x2,-123"));
  std::string res2 = "11111000010100010000000011100111";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr2), res2);
}

BOOST_AUTO_TEST_CASE(test_assemble_addi){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("ADDI x1,x2,123"));
  std::string res = "00000111101100010000000010010011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);

  std::array<bool, 32> bitArr2 = a.assemble(p.parseCommand("ADDI x1,x2,-123"));
  std::string res2 = "11111000010100010000000010010011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr2), res2);
}

BOOST_AUTO_TEST_CASE(test_assemble_beq){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("BEQ x19,x10,16"));
  std::string res = "00000000101010011000100001100011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);

  std::array<bool, 32> bitArr2 = a.assemble(p.parseCommand("BEQ x19,x10,-8"));
  std::string res2 = "11111110101010011000110011100011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr2), res2);
}

BOOST_AUTO_TEST_CASE(test_assemble_sb){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("SB x1,x2,123"));
  std::string res = "00000110001000001000110110100011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);

  std::array<bool, 32> bitArr2 = a.assemble(p.parseCommand("SB x1,x2,-123"));
  std::string res2 = "11111000001000001000001010100011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr2), res2);
}

BOOST_AUTO_TEST_CASE(test_assemble_sh){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("SH x1,x2,123"));
  std::string res = "00000110001000001001110110100011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);
}

BOOST_AUTO_TEST_CASE(test_assemble_sw){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("SW x1,x2,123"));
  std::string res = "00000110001000001010110110100011";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);
}

BOOST_AUTO_TEST_CASE(test_assemble_none){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("   "));
  std::string res = "00000000000000000000000000000000";
  BOOST_CHECK_EQUAL(a.bitArrToBitString(bitArr), res);
}
