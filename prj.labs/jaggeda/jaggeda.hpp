// 2026 by Polevoi Dmitry under Unlicense

#pragma once
#ifndef JAGGEDA_JAGGEDA_HPP_20260521
#define JAGGEDA_JAGGEDA_HPP_20260521

#include <cstddef>

class JaggedA final {
public:
  JaggedA() noexcept;
  JaggedA(const JaggedA&) noexcept;
  JaggedA(JaggedA&&) noexcept;
  JaggedA(const int size);

  JaggedA& operator=(const JaggedA&) noexcept;
  JaggedA& operator=(JaggedA&&) noexcept;

  ~JaggedA() noexcept;

  bool operator==(const JaggedA& rhs) const noexcept;

  [[nodiscard]] int32_t size() const noexcept;
  void resize(const int32_t size);

  [[nodiscard]] int32_t size(const int32_t i) const;
  void resize(const int32_t i, const int32_t size);

  [[nodiscard]] int32_t& at(const int32_t i, const int32_t j);
  [[nodiscard]] const int32_t& at(const int32_t i, const int32_t j) const;
  
  void swap(const int32_t i_l, const int32_t i_r);

  void insert(const int32_t i);
  void remove(const int32_t i);

  void insert(const int32_t i, const int32_t j);
  void remove(const int32_t i, const int32_t j);
};

#endif