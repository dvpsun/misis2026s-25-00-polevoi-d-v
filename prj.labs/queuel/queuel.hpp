// 2026 by Polevoi Dmitry under Unlicense

#pragma once
#ifndef QUEUEA_QUEUEL_HPP_20261207
#define QUEUEA_QUEUEL_HPP_2026207

#include <cstdint>

class QueueL final {
public:
  using T = std::int64_t;

  QueueL() = default;

  QueueL(const QueueL& src);

  QueueL(QueueL&& src) noexcept;
  
  ~QueueL();
  
  QueueL& operator=(const QueueL& src);

  QueueL& operator=(QueueL&& src);

  [[nodiscard]] bool is_empty() const noexcept;

  void pop() noexcept;

  void push(const T val);
  
  [[nodiscard]] T& top();

  [[nodiscard]] const T& top() const;

  void clear() noexcept;
};

#endif
