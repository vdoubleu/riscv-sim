#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <string>
#include <memory>
#include "inputCleaner.h"
#include "parser.h"
#include "assembler.cpp"

BOOST_AUTO_TEST_CASE(test_inputCleaner){
  inputCleaner cleaner;

  BOOST_CHECK_EQUAL(cleaner.cleanInput("   hello   "), "hello");
  BOOST_CHECK_EQUAL(cleaner.cleanInput("hello   "), "hello");
  BOOST_CHECK_EQUAL(cleaner.cleanInput("   hello"), "hello");
  BOOST_CHECK_EQUAL(cleaner.cleanInput("      "), "");
}

BOOST_AUTO_TEST_CASE(test_parser_add){
  parser p;

  std::unique_ptr<command> c = p.parseCommand("ADD x1, x2, x3");
  BOOST_CHECK_EQUAL(c->type, R);
  BOOST_CHECK_EQUAL(c->name, ADD);
  BOOST_CHECK_EQUAL(c->field1, "x1");
  BOOST_CHECK_EQUAL(c->field2, "x2");
  BOOST_CHECK_EQUAL(c->field3, "x3");
}

BOOST_AUTO_TEST_CASE(test_parser_sub){
  parser p;

  std::unique_ptr<command> c = p.parseCommand("SUB x1,x2,x3");
  BOOST_CHECK_EQUAL(c->type, R);
  BOOST_CHECK_EQUAL(c->name, SUB);
  BOOST_CHECK_EQUAL(c->field1, "x1");
  BOOST_CHECK_EQUAL(c->field2, "x2");
  BOOST_CHECK_EQUAL(c->field3, "x3");

  std::unique_ptr<command> c2 = p.parseCommand("sub x1,x2,x3");
  BOOST_CHECK_EQUAL(c2->type, R);
  BOOST_CHECK_EQUAL(c2->name, SUB);
  BOOST_CHECK_EQUAL(c2->field1, "x1");
  BOOST_CHECK_EQUAL(c2->field2, "x2");
  BOOST_CHECK_EQUAL(c2->field3, "x3");

}

BOOST_AUTO_TEST_CASE(test_parser_addi){
  parser p;

  std::unique_ptr<command> c = p.parseCommand("ADDI x1,x2,x3");
  BOOST_CHECK_EQUAL(c->type, I);
  BOOST_CHECK_EQUAL(c->name, ADDI);
  BOOST_CHECK_EQUAL(c->field1, "x1");
  BOOST_CHECK_EQUAL(c->field2, "x2");
  BOOST_CHECK_EQUAL(c->field3, "x3");
}

BOOST_AUTO_TEST_CASE(test_assemble_add){
  assembler a;
  parser p;

  std::unique_ptr<command> c = p.parseCommand("ADD x1,x2,x3");
  std::array<bool, 32> bitArr = a.assemble(std::move(c));
  std::array<bool, 32> res = a.bitStringToBitArr("00000000001100010000000010110011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr.begin(), bitArr.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(test_assemble_sub){
  assembler a;
  parser p;

  std::unique_ptr<command> c = p.parseCommand("SUB x1,x2,x3");
  std::array<bool, 32> bitArr = a.assemble(std::move(c));
  std::array<bool, 32> res = a.bitStringToBitArr("01000000001100010000000010110011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr.begin(), bitArr.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(test_assemble_addi){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("ADDI x1,x2,123"));
  std::array<bool, 32> res = a.bitStringToBitArr("00000111101100010000000010010011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr.begin(), bitArr.end(), res.begin(), res.end());

  std::array<bool, 32> bitArr2 = a.assemble(p.parseCommand("ADDI x1,x2,-123"));
  std::array<bool, 32> res2 = a.bitStringToBitArr("11111000010100010000000010010011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr2.begin(), bitArr2.end(), res2.begin(), res2.end());
}

BOOST_AUTO_TEST_CASE(test_assemble_beq){
  assembler a;
  parser p;

  std::array<bool, 32> bitArr = a.assemble(p.parseCommand("BEQ x19,x10,16"));
  std::array<bool, 32> res = a.bitStringToBitArr("00000000101010011000100001100011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr.begin(), bitArr.end(), res.begin(), res.end());

  std::array<bool, 32> bitArr2 = a.assemble(p.parseCommand("BEQ x19,x10,-8"));
  std::array<bool, 32> res2 = a.bitStringToBitArr("11111110101010011000110011100011");
  BOOST_CHECK_EQUAL_COLLECTIONS(bitArr2.begin(), bitArr2.end(), res2.begin(), res2.end());
}
