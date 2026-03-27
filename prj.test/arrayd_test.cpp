// 2025 by Polevoi Dmitry under Unlicense

#include <arrayd/arrayd.hpp>
#include <climits>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

static const float eps = std::numeric_limits<float>::epsilon() * 2;

TEST_CASE("[arrayd] - ctor") {
  CHECK(ArrayD().size() == 0);
}

TEST_CASE("[arrayd] - ctor copy") {
  const int size = 10;
  ArrayD src(size);
  for (int i = 0; i < size; i += 1) {
    src[i] = i;
  }
  ArrayD tgt(src);
  CHECK(tgt.size() == size);
  bool is_equal = true;
  for (int i = 0; i < size && is_equal; i += 1) {
    is_equal = doctest::Approx(src[i]).epsilon(eps) == tgt[i];
  }
  CHECK(is_equal);
  for (int i = 0; i < size; i += 1) {
    tgt[i] += 1;
  }
  is_equal = true;
  for (int i = 0; i < size && is_equal; i += 1) {
    is_equal = doctest::Approx(src[i]).epsilon(eps) == tgt[i];
  }
  CHECK(!is_equal);
}
