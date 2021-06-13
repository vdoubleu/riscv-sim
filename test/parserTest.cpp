#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../src/inputCleaner.h"
#include "../src/parser.h"
#include "../src/commands.cpp"

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
