#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <string>
#include <memory>
#include <iostream>
#include <string>
#include "../src/inputCleaner.h"
#include "../src/parser.h"
#include "../src/assembler.h"
#include "../src/util.h"
#include "../src/commands.cpp"
#include "../src/registers.h"
#include "../src/memory.h"
#include "../src/display.h"

BOOST_AUTO_TEST_CASE(test_display) {
  registers r;
  memory m;
  display d(true);

  d.displayState(&r, &m);
}

