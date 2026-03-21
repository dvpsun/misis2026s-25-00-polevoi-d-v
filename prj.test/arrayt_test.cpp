#include <arrayt/arrayt.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[arrayr] - ctor default") {
  ArrayT<float> a;
  CHECK(0 == a.size());
}
