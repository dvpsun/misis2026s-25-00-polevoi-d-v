// 2026 by Dmitrconsty Polevoy 

#pragma once
#ifndef BITSETD_BITSETD_HPP_20260214
#define BITSETD_BITSETD_HPP_20260214

#include <cstdint>
#include <vector>

class BitsetD {
public:
  class BitProx {
  public:
    BitProx() = delete;
    BitProx(const BitProx&) = delete;
    ~BitProx() = default;
    BitProx& operator=(const BitProx&) = delete;
    BitProx(BitsetD& bs, const int32_t idx) : bs_(bs), idx_(idx) {}
    operator bool() const { return bs_.get(idx_); }
    void operator=(const bool val) { bs_.set(idx_, val); }
  private:
    BitsetD& bs_;
    const int32_t idx_ = 0;
  };
  class BitProxC {
  public:
    BitProxC() = delete;
    BitProxC(const BitProxC&) = delete;
    ~BitProxC() = default;
    BitProxC& operator=(const BitProxC&) = delete;
    BitProxC(const BitsetD& bs, const int32_t idx) : val_(bs.get(idx)) {}
    operator bool() const { return val_; }
  private:
    bool val_ = false;
  };
public:
  BitsetD() = default;
  BitsetD(const BitsetD& src) = default;
  BitsetD(const std::uint64_t mask, const int32_t size = 64);
  BitsetD(const int32_t size, const bool val);
  ~BitsetD() = default;
  BitsetD& operator=(const BitsetD& rhs) = default; // TODO:shrink if size small

  std::int32_t size() const noexcept { return size_; }
  void resize(const std::int32_t new_size, const bool val = false);
  bool get(const std::int32_t idx) const;
  void set(const std::int32_t idx, const bool val);

  BitProx operator[](const std::int32_t idx) { return BitProx(*this, idx); }
  BitProxC operator[](const std::int32_t idx) const { return BitProxC(*this, idx); }

  bool operator==(const BitsetD& rhs) noexcept;

  BitsetD& invert() noexcept;
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


inline BitsetD operator~(const BitsetD& rhs) noexcept { return BitsetD(rhs).invert(); }

BitsetD operator<<(const BitsetD& lhs, const std::int32_t shift);

BitsetD operator>>(const BitsetD& lhs, const std::int32_t shift);

BitsetD operator&(const BitsetD& lhs, const BitsetD& rhs);

BitsetD operator|(const BitsetD& lhs, const BitsetD& rhs);

BitsetD operator^(const BitsetD& lhs, const BitsetD& rhs);

#endif