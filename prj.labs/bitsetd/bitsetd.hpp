// 2026 by Dmitry Polevoy 
// МИСИС 2026 весна курс ООП

#pragma once
#ifndef BITSETD_BITSETD_HPP_20260214
#define BITSETD_BITSETD_HPP_20260214

#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

class BitsetD {
public:
  class BitR {
    friend class BitsetD;
  public:
    ~BitR() = default;
    operator bool() const noexcept { return val_; }
  private:
    BitR() = delete;
    BitR(const BitR&) = delete;
    BitR(BitR&&) = delete;
    BitR(const BitsetD& bs, const int32_t idx) : val_(bs.get(idx)) {}
    BitR& operator=(const BitR&) = delete;
    BitR& operator=(BitR&&) = delete;
  private:
    bool val_ = false;
  };

  class BitW {
    friend class BitsetD;
  public:
    ~BitW() = default;
    operator bool() const noexcept { return bs_.get(idx_); }
    void operator=(const bool val) noexcept { bs_.set(idx_, val); }
    void operator=(const BitW& rhs) noexcept { operator=(rhs.operator bool()); }
    void operator=(BitW&& rhs) noexcept { operator=(rhs.operator bool()); }
  private:
    BitW(BitsetD& bs, const int32_t idx) : bs_(bs), idx_(idx) {}
    BitW() = delete;
    BitW(const BitW&) = delete;
    BitW(BitW&&) = delete;
  private:
    BitsetD& bs_;
    const int32_t idx_ = 0;
  };

public:
  BitsetD() = default;
  
  BitsetD(const BitsetD& src) = default;
  
  BitsetD(BitsetD&& src) = default;
  
  /*!
  /TODO
  \param  mask [in] - 
  \param  size [in] -
  \throws std::invalid_argument для неположительного size
  */
  BitsetD(const std::uint64_t mask, const int32_t size);
  
  /*!
  /TODO
  \param  size [in] -
  \param  val [in] -
  \throws std::invalid_argument для неположительного size
  */
  BitsetD(const int32_t size, const bool val = false);
  
  ~BitsetD() = default;
  
  BitsetD& operator=(const BitsetD& rhs) = default; // TODO:shrink if size small
  
  BitsetD& operator=(BitsetD&& rhs) = default;

  explicit operator std::uint64_t() const;
  
  explicit operator std::uint32_t() const { return chunks_[0]; }

  std::int32_t size() const noexcept { return size_; }
  
  void resize(const std::int32_t new_size, const bool val = false);
  
  /*!
  Прочитать значение бита по указанному индексу.
  \param  idx[in] - индекс бита
  \return Значение бита
  \throws std::out_of_range при выходе индекса за пределы допустимого
  */
  bool get(const std::int32_t idx) const;
  
  /*!
  Установить значение бита по указанному индексу.
  \param idx[in] - индекс бита
  \param val[in] - значение бита
  \throws std::out_of_range при выходе индекса за пределы допустимого
  */
  void set(const std::int32_t idx, const bool val);

  BitW operator[](const std::int32_t idx)       & { return BitW(*this, idx); }
  
  BitR operator[](const std::int32_t idx) const & { return BitR(*this, idx); }

  bool operator==(const BitsetD& rhs) const noexcept;

  BitsetD& invert() noexcept;
  
  void fill(const bool val) noexcept;
  
  BitsetD& shift(const std::int32_t s) noexcept;
  
  BitsetD& operator<<=(const std::int32_t shift);
  
  BitsetD& operator>>=(const std::int32_t shift);
  
  BitsetD& operator&=(const BitsetD& rhs);
  
  BitsetD& operator|=(const BitsetD& rhs);
  
  BitsetD& operator^=(const BitsetD& rhs);

  enum class StrFormat : int32_t {
    Bin = 1,      ///< суффикс "b0" и разделители по 4 от младших, пример: b0010'0001
    BinNoPreSep,  ///< без суффикса и разделителей, пример: 0100001
    Oct,
    Hex,
    Def = Bin,
    Default = Def
  };

  /*!
  Форматированное текстовое представление, "empty" - для пустого
  \param fmt [in] - формат представления
  \param len [in] - минимальная длина строки в символах выбранного формата
  */
  std::string to_string(const StrFormat fmt = StrFormat::Def, const int32_t len = 0) const;
  
  std::ostream& write_to(std::ostream& s) const { return s; }
  
  std::istream& read_from(std::istream& s) { return s; }

private:
  std::int32_t                size_ = 0;  ///< размер битсета (число доступных бит)
  std::vector<std::uint32_t>  chunks_;    ///< буфер для хранения бит в упакованном виде

private:
  // размер элемента буффера в битах (chunk bit size)
  static const int32_t chunk_bi_s = 32;
  // размер элемента буффера в байтах (chunk byte size)
  static const int32_t chunk_by_s = 4;
  // минимальный размер буфера для текущего размера битсета (chunk count for current bitset size)
  int32_t chunks_count() const { return (size_ + chunk_bi_s - 1) / chunk_bi_s; }
};

inline BitsetD::operator std::uint64_t() const {
  std::uint64_t val = chunk_bi_s < size_ ? chunks_[1] : 0;
  val <<= 32;
  val |= chunks_[0];
  return val;
}

inline BitsetD operator~(const BitsetD& val) noexcept {
  return BitsetD(val).invert();
}

inline BitsetD operator<<(const BitsetD& lhs, const std::int32_t shift) {
  return BitsetD(lhs).operator<<=(shift); 
}

inline BitsetD operator>>(const BitsetD& lhs, const std::int32_t shift) {
  return BitsetD(lhs).operator>>=(shift);
}

inline BitsetD operator&(const BitsetD& lhs, const BitsetD& rhs) {
  return BitsetD(lhs).operator&=(rhs);
}

inline BitsetD operator|(const BitsetD& lhs, const BitsetD& rhs) {
  return BitsetD(lhs).operator|=(rhs);
}

inline BitsetD operator^(const BitsetD& lhs, const BitsetD& rhs) {
  return BitsetD(lhs).operator^=(rhs);
}

#endif