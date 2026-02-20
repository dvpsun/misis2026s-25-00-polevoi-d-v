// 2026 by Dmitrconsty Polevoy 

#pragma once
#ifndef BITSETD_BITSETD_HPP_20260214
#define BITSETD_BITSETD_HPP_20260214

#include <cstdint>
#include <vector>

class BitsetD {
public:
  BitsetD() = default;
  BitsetD(const BitsetD& src);
  BitsetD(const std::uint64_t mask, const int32_t size);
  BitsetD(const int32_t size, const bool val = false);
  ~BitsetD() = default;
  BitsetD& operator=(const BitsetD& rhs) = default; // TODO:shrink if size small

  std::int32_t size() const noexcept { return size_; }
  void resize(const std::int32_t new_size, const bool val = false);
  bool get(const std::int32_t idx) const;
  void set(const std::int32_t idx, const bool val);

  bool operator==(const BitsetD& rhs) noexcept;

  void invert() noexcept;
  void fill(const bool val) noexcept;
  BitsetD& shift(const std::int32_t idx) noexcept;
  BitsetD& operator<<=(const std::int32_t shift);
  BitsetD& operator>>=(const std::int32_t shift);
  BitsetD& operator&=(const BitsetD& rhs);
  BitsetD& operator|=(const BitsetD& rhs);
  BitsetD& operator^=(const BitsetD& rhs);
private:
  std::int32_t size_ = 0;
  std::vector<std::uint32_t> bits_;
};


BitsetD operator~(const BitsetD& rhs) noexcept;

BitsetD operator<<(const BitsetD& lhs, const std::int32_t shift);

BitsetD operator>>(const BitsetD& lhs, const std::int32_t shift);

BitsetD operator&(const BitsetD& lhs, const BitsetD& rhs);

BitsetD operator|(const BitsetD& lhs, const BitsetD& rhs);

BitsetD operator^(const BitsetD& lhs, const BitsetD& rhs);

#endif