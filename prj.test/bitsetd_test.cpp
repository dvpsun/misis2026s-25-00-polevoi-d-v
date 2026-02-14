#include <bitsetd/bitsetd.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[bitsetd] - ctor default") {
  BitsetD b;
  CHECK(0 == b.size());
}