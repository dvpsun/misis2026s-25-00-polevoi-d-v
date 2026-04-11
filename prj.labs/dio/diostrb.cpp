// 2026 by Dmitry Polevoy
// ÌÈÑÈÑ 2026 âåñíà êóğñ ÎÎÏ

#include "dio.hpp"
#include <iostream>


std::ostream& operator<<(std::ostream& ostrm, const DioStrB& str) {
  return str.write_to(ostrm);
}


std::istream& operator>>(std::istream& istrm, DioStrB& str) {
  return str.read_from(istrm);
}


std::ostream& DioStrB::write_to(std::ostream& ostrm) const {
  int32_t size = str_.size();
  size += 1;
  ostrm.put(mrk_);
  ostrm.write(reinterpret_cast<char*>(&size), sizeof(size));
  ostrm.write(str_.data(), size);
  return ostrm;
}


std::istream& DioStrB::read_from(std::istream& istrm) {
  char mark = istrm.get();
  if (mrk_ == mark) {
    int32_t size = 0;
    istrm.read(reinterpret_cast<char*>(&size), sizeof(size));
    str_.resize(size - 1);
    istrm.read(str_.data(), size);
  } else {
    istrm.setstate(std::ios::badbit);
  }
  return istrm;
}

std::ostream& operator<<(std::ostream& ostrm, const DioStrT& str) {
  return str.write_to(ostrm);
}


std::istream& operator>>(std::istream& istrm, DioStrT& str) {
  return str.read_from(istrm);
}

std::ostream& DioStrT::write_to(std::ostream& ostrm) const {

  return ostrm;
}


std::istream& DioStrT::read_from(std::istream& istrm) {

  return istrm;
}