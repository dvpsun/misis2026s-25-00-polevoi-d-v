// 2026 by Dmitry Polevoy
// МИСИС 2026 весна курс ООП

#include "bitsetd.hpp"

#include <stdexcept>

BitsetD::BitsetD(const std::int32_t size, const bool val)
  : size_(size)
  , chunks_(chunks_count())
{
  if (val) {
    std::fill(chunks_.begin(), chunks_.end(), 0xFFFFFFFFU);
  }
}

BitsetD::BitsetD(const std::uint64_t mask, const std::int32_t size) 
  : size_(size)
  , chunks_{static_cast<uint32_t>(mask ),
            static_cast<uint32_t>(mask >> chunk_bi_s)} {
  chunks_.resize(chunks_count());
}

bool BitsetD::operator==(const BitsetD& rhs) const noexcept {
  bool is_equal = size_ == rhs.size_;
  for (int32_t i = 0; is_equal && i < size_; i += 1) {
    is_equal = operator[](i) == rhs[i];
  }
  return is_equal;
}

void BitsetD::resize(const std::int32_t new_size, const bool val) {
  if (new_size <= 0) {
    throw std::invalid_argument("BitsetD::resize non positive new size");
  }
  // TODO
  //if (size_ < new_size) {
  //  bits_.resize(bits_size());
  //  if (size_ % 32 != 0) {
  //    uint32_t& val = bits_[bits_size() - 1];
  //    val
  //  }
  //}
  size_ = new_size;
}

bool BitsetD::get(const std::int32_t idx) const {
  if (idx < 0 || size_ <= idx) {
    throw std::out_of_range("BitsetD::get invalid index");
  }
  return chunks_[idx / chunk_bi_s] & (UINT32_C(1) << idx % chunk_bi_s);
}

void BitsetD::set(const std::int32_t idx, const bool val) {
  if (idx < 0 || size_ <= idx) {
    throw std::out_of_range("BitsetD::set invalid index");
  }
  if (val) {
    chunks_[idx / chunk_bi_s] |= UINT32_C(1) << idx % chunk_bi_s;
  } else {
    chunks_[idx / chunk_bi_s] &= ~(UINT32_C(1) << idx % chunk_bi_s);
  }
}

BitsetD& BitsetD::invert() noexcept {
  for (auto& bits : chunks_) {
    bits = ~bits;
  }
  return *this;
}

BitsetD& BitsetD::shift(const std::int32_t shift) noexcept {
  const std::int32_t s = size();
  BitsetD copy(s);
  for (int32_t i = 0; i < s; i += 1) {
    copy[(i - shift) % s] = operator[](i);
  }
  std::swap(chunks_, copy.chunks_);
  return *this;
}

BitsetD& BitsetD::operator<<=(const std::int32_t shift) {
  for (int32_t i = size() - 1; shift <= i; i -= 1) {
    operator[](i - shift) = operator[](i);
  }
  for (int32_t i = shift; 0 <= i; i -= 1) {
    operator[](i) = false;
  }
  return *this;
}

BitsetD& BitsetD::operator>>=(const std::int32_t shift) {
  for (int32_t i = 0; i < size() - shift; i += 1) {
    operator[](i) = operator[](i + shift);
  }
  for (int32_t i = shift; i < size() - 1; i += 1) {
    operator[](i) = false;
  }
  return *this;
}

BitsetD& BitsetD::operator&=(const BitsetD& rhs) {
  if (size_ != rhs.size_) {
    throw std::invalid_argument("BitsetD::operator&= different size");
  }
  const std::int32_t chunks_count = rhs.chunks_count();
  for (int32_t i_u = 0; i_u < chunks_count; i_u += 1) {
    chunks_[i_u] |= rhs.chunks_[i_u];
  }
  return *this;
}

BitsetD& BitsetD::operator|=(const BitsetD& rhs) {
  if (size_ != rhs.size_) {
    throw std::invalid_argument("BitsetD::operator|= different size");
  }
  const std::int32_t chunks_count = rhs.chunks_count();
  for (int32_t i_u = 0; i_u < chunks_count; i_u += 1) {
    chunks_[i_u] |= rhs.chunks_[i_u];
  }
  return *this;
}

BitsetD& BitsetD::operator^=(const BitsetD& rhs) {
  if (size_ != rhs.size_) {
    throw std::invalid_argument("BitsetD::operator^= different size");
  }
  const std::int32_t chunks_count = rhs.chunks_count();
  for (int32_t i_u = 0; i_u < chunks_count; i_u += 1) {
    chunks_[i_u] ^= rhs.chunks_[i_u];
  }
  return *this;
}

std::string BitsetD::to_string(const BitsetD::StrFormat fmt, const int32_t len) const {
  return "empty";
}
