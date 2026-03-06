// 2026 by Dmitry Polevoy 

#pragma once
#ifndef BITSETD_BITSETD_HPP_20260214
#define BITSETD_BITSETD_HPP_20260214

#include <cstdint>
#include <vector>

class BitsetD {
public:
  class BitR {
    friend class BitsetD;
  public:
    operator bool() const noexcept { return val_; }
  private:
    BitR() = delete;
    BitR(const BitR&) = delete;
    BitR(BitR&&) = delete;
    BitR(const BitsetD& bs, const int32_t idx) : val_(bs.get(idx)) {}
    ~BitR() = default;
    BitR& operator=(const BitR&) = delete;
    BitR& operator=(BitR&&) = delete;
  private:
    bool val_ = false;
  };

  class BitW {
    friend class BitsetD;
  public:
    operator bool() const noexcept { return bs_.get(idx_); }
    void operator=(const bool val) noexcept { bs_.set(idx_, val); }
    void operator=(const BitW& rhs) noexcept { operator=(rhs.operator bool()); }
    void operator=(BitW&& rhs) noexcept { operator=(rhs.operator bool()); }
  private:
    BitW(BitsetD& bs, const int32_t idx) : bs_(bs), idx_(idx) {}
    BitW() = delete;
    BitW(const BitW&) = delete;
    BitW(BitW&&) = delete;
    ~BitW() = default;
  private:
    BitsetD& bs_;
    const int32_t idx_ = 0;
  };

public:
  BitsetD() = default;
  BitsetD(const BitsetD& src) = default;
  BitsetD(BitsetD&& src) = default;
  BitsetD(const std::uint64_t mask, const int32_t size);
  BitsetD(const int32_t size, const bool val = false);
  ~BitsetD() = default;
  BitsetD& operator=(const BitsetD& rhs) = default; // TODO:shrink if size small
  BitsetD& operator=(BitsetD&& rhs) = default;

  std::int32_t size() const noexcept { return size_; }
  void resize(const std::int32_t new_size, const bool val = false);
  bool get(const std::int32_t idx) const;
  void set(const std::int32_t idx, const bool val);

  BitW operator[](const std::int32_t idx)       & { return BitW(*this, idx); }
  BitR operator[](const std::int32_t idx) const & { return BitR(*this, idx); }

  bool operator==(const BitsetD& rhs) const noexcept;

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