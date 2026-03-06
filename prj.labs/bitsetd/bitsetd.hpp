// 2026 by Dmitrconsty Polevoy 

#pragma once
#ifndef BITSETD_BITSETD_HPP_20260214
#define BITSETD_BITSETD_HPP_20260214

#include <cstdint>
#include <vector>

class BitsetD;

//namespace std {
//  void swap(BitsetD::BitW&& lhs, BitsetD::BitW&& rhs);
//}

class BitsetD {
public:
  class BitR {
    friend class BitsetD;
  public:
    operator bool() const { return val_; }
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
    void operator=(const BitW& rhs) { bs_.set(idx_, rhs.operator bool()); }
    //void operator=(BitW&& rhs) { bs_.set(idx_, rhs.operator bool()); }
    void operator=(const BitR& rhs) { bs_.set(idx_, rhs.operator bool()); }
    operator bool() const { return bs_.get(idx_); }
    void operator=(const bool val) { bs_.set(idx_, val); }
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

//namespace std {
//  inline void swap(BitsetD::BitW&& lhs, BitsetD::BitW&& rhs) {
//    bool val = lhs.operator bool();
//    lhs.operator=(rhs.operator bool());
//    rhs.operator=(val);
//  }
//}

#endif