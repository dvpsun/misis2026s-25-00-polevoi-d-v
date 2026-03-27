// 2026 by Polevoi Dmitry under Unlicense

#include <arrayt/arrayt.hpp>
#include <climits>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

static const float eps = std::numeric_limits<float>::epsilon() * 2;

template<typename T>
bool compre_eq(const T& lhs, const T& rhs) {
  return lhs == rhs;
}

template<>
bool compre_eq<float>(const float& lhs, const float& rhs) {
  return doctest::Approx(lhs).epsilon(eps) == rhs;
}

TEST_CASE_TEMPLATE("[arrayr] - ctor default", T, int, int32_t, float, std::string) {
  ArrayT<float> a;
  CHECK(0 == a.size());
}

using ArrayD = ArrayT<float>;

#define TYPES int, int32_t, float, std::string

TEST_CASE_TEMPLATE("[arrayd] - ctor copy", T, TYPES) {
  const int size = 10;
  ArrayD src(size);
  for (int i = 0; i < size; i += 1) {
    src[i] = i;
  }
  ArrayD tgt(src);
  CHECK(tgt.size() == size);
  bool is_equal = true;
  for (int i = 0; i < size && is_equal; i += 1) {
    is_equal = compre_eq(src[i], tgt[i]);
  }
  CHECK(is_equal);
  for (int i = 0; i < size; i += 1) {
    tgt[i] += 1;
  }
  is_equal = true;
  for (int i = 0; i < size && is_equal; i += 1) {
    is_equal = compre_eq(src[i], tgt[i]);
  }
  CHECK(!is_equal);
}