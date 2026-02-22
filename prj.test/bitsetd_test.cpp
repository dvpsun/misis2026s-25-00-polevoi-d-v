#include <bitsetd/bitsetd.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[bitsetd] - ctor default") {
  BitsetD b;
  CHECK(0 == b.size());
}

//TEST_CASE("[bitsetd] - ctor copy") {
//  BitsetD s;
//  BitsetD t0(s);
//  CHECK(s.size() == t0.size());
//}

TEST_CASE("[bitsetd] - ctor uint64_t") {
  BitsetD b64(0xAAAABBBBCCCCDDDDUL);
  CHECK(64 == b64.size());
  BitsetD b33(0xAAAABBBBCCCCDDDDUL, 33);
  CHECK(33 == b33.size());
}

TEST_CASE("[bitsetd] - set and get contracts") {
  BitsetD b0;
  CHECK_THROWS(b0.get(-1));
  CHECK_THROWS(b0.get(0));
  CHECK_THROWS(b0.set(-1, true));
  CHECK_THROWS(b0.set(0, true));
  BitsetD b64(0xCDULL);
  CHECK_THROWS(b0.get(-1));
  CHECK_THROWS(b0.get(64));
  CHECK_THROWS(b0.set(-1, true));
  CHECK_THROWS(b0.set(64, true));
}

TEST_CASE("[bitsetd] - set and get") {
  BitsetD b1{ static_cast<uint64_t>(0b1010'0101'1111'0000) };
  CHECK(!b1.get(0));
  CHECK(!b1.get(3));
  CHECK(b1.get(4));
  CHECK(b1.get(8));

  //BitsetD b64(0x0ULL);
  //bool v = false;
  //for (std::int32_t i = 0; i < b64.size(); i += 1) {
  //  CHECK(!b64.get(i));
  //  v = b64.get(i);
  //  b64.set(true, i); ;
  //  CHECK(b64.get(i));
  //  b64.set(false, i); ;
  //  CHECK(!b64.get(i));
  //}
}

TEST_CASE("[bitsetd] - op[]") {
  BitsetD b64(0xAAAABBBBCCCCDDDDULL);
  CHECK(b64[0] == b64.get(0));
  for (std::int32_t i = 0; i < b64.size(); i += 1) {
    auto v = b64[i];
    b64[i] = true;
    CHECK(b64[i]);
    b64[i] = false;
    CHECK(!b64[i]);

  }
  CHECK(b64.get(0) == b64[0]);


  CHECK(64 == b64.size());
  BitsetD b33(0xAAAABBBBCCCCDDDDUL, 33);
  CHECK(33 == b33.size());
}

TEST_CASE("[bitsetd] - op[] const") {
  uint64_t mask = 1ull;
  const auto bits = 0b0101'1010'1111'0000ull;
  const BitsetD b1(bits);
  for (int32_t i = 0; i < sizeof(bits) * 8; i += 1) {
    CHECK(b1[i] == bool(bits & mask));
    std::cout << b1[i] << std::endl;
    mask <<= 1;
  }
}