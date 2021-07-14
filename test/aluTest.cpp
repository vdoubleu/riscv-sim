#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <array>
#include <memory>
#include <string>
#include "../src/util.h"
#include "../src/alu.h"
#include "../src/action.h"
#include "../src/commands.cpp"
#include "../src/registers.h"

BOOST_AUTO_TEST_CASE(test_alu_add) {
  alu a;
  util u;
  registers r;

  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(3)), 3);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(1)), 2);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(1)), 1);

  std::unique_ptr<RAction> ra = std::make_unique<RAction>(1, 2, 3, ADD, R);
  a.updateState(ra.get(), &r);

  auto res = *(r.getRegister(3));
  int n = u.signedBitArrToNum(std::vector<bool>(res.begin(), res.end()));
  BOOST_CHECK_EQUAL(n, 2);
}

BOOST_AUTO_TEST_CASE(test_alu_add2) {
  alu a;
  util u;
  registers r;

  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(3)), 3);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(-3)), 2);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(1)), 1);

  std::unique_ptr<RAction> ra = std::make_unique<RAction>(1, 2, 3, ADD, R);
  a.updateState(ra.get(), &r);

  auto res = *(r.getRegister(3));
  int n = u.signedBitArrToNum(std::vector<bool>(res.begin(), res.end()));
  BOOST_CHECK_EQUAL(n, -2);
}

BOOST_AUTO_TEST_CASE(test_alu_sub) {
  alu a;
  util u;
  registers r;

  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(2)), 3);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(4)), 2);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(6)), 1);

  std::unique_ptr<RAction> ra = std::make_unique<RAction>(1, 2, 3, SUB, R);
  a.updateState(ra.get(), &r);

  auto res = *(r.getRegister(3));
  int n = u.signedBitArrToNum(std::vector<bool>(res.begin(), res.end()));
  BOOST_CHECK_EQUAL(n, 2);
}

BOOST_AUTO_TEST_CASE(test_alu_and) {
  alu a;
  util u;
  registers r;

  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(2)), 3);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(10)), 2);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(12)), 1);

  std::unique_ptr<RAction> ra = std::make_unique<RAction>(1, 2, 3, AND, R);
  a.updateState(ra.get(), &r);

  auto res = *(r.getRegister(3));
  int n = u.signedBitArrToNum(std::vector<bool>(res.begin(), res.end()));
  BOOST_CHECK_EQUAL(n, 8);
}

BOOST_AUTO_TEST_CASE(test_alu_or) {
  alu a;
  util u;
  registers r;

  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(2)), 3);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(10)), 2);
  r.setRegister(std::make_unique<std::array<bool, 32>>(u.numToBitArr(12)), 1);

  std::unique_ptr<RAction> ra = std::make_unique<RAction>(1, 2, 3, OR, R);
  a.updateState(ra.get(), &r);

  auto res = *(r.getRegister(3));
  int n = u.signedBitArrToNum(std::vector<bool>(res.begin(), res.end()));
  BOOST_CHECK_EQUAL(n, 14);
}
