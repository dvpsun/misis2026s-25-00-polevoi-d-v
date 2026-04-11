// 2026 by Dmitry Polevoy 
// ÌÈÑÈÑ 2026 âåñíà êóðñ ÎÎÏ

#pragma once
#ifndef DIO_DIO_HPP_20260402
#define DIO_DIO_HPP_20260402

#include <string>
#include <iosfwd>

class DioStrB {
public:
  DioStrB() = default;
  DioStrB(const DioStrB&) = default;
  DioStrB(DioStrB&&) = default;
  DioStrB& operator=(const DioStrB&) = default;
  DioStrB& operator=(DioStrB&&) = default;
  ~DioStrB() = default;
  std::string& val() { return str_; }
  const std::string& val() const { return str_; }
  std::ostream& write_to(std::ostream& strm) const;
  std::istream& read_from(std::istream& istrm);

private:
  std::string str_;
  static const char mrk_ = 's';
};

std::ostream& operator<<(std::ostream& strm, const DioStrB& str);

std::istream& operator>>(std::istream& istrm, DioStrB& str);


class DioStrT {
public:
  DioStrT() = default;
  DioStrT(const DioStrT&) = default;
  DioStrT(DioStrT&&) = default;
  DioStrT& operator=(const DioStrT&) = default;
  DioStrT& operator=(DioStrT&&) = default;
  ~DioStrT() = default;
  std::string& val() { return str_; }
  const std::string& val() const { return str_; }
  std::ostream& write_to(std::ostream& strm) const;
  std::istream& read_from(std::istream& istrm);

private:
  std::string str_;
  static const char mrk_ = 's';
};

std::ostream& operator<<(std::ostream& strm, const DioStrT& str);

std::istream& operator>>(std::istream& istrm, DioStrT& str);

#endif
