#include <dio/dio.hpp>

#include <strstream>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

std::vector<std::string> test_strings{
  "First test strin.",
  "Second test string.\n\r\tWith second line."
};

TEST_CASE("[dio] - diostrb") {
  DioStrB str;
  std::ostringstream ostrm;
  str.val() = test_strings[0];
  ostrm << str;
  str.val() = test_strings[1];
  ostrm << str;
  str.val().clear();
  ostrm << str;

  std::istringstream istrm(ostrm.str());
  istrm >> str;
  CHECK(str.val() == test_strings[0]);
  istrm >> str;
  CHECK(str.val() == test_strings[1]);
  istrm >> str;
  CHECK(str.val() == std::string{});
}