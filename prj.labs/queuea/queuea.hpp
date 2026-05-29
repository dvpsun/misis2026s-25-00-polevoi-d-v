// 2026 by Polevoi Dmitry under Unlicense

#pragma once
#ifndef QUEUEA_QUEUEA_HPP_20261207
#define QUEUEA_QUEUEA_HPP_20261207

#include <cstdint>

class QueueA final {
public:
  using T = std::int64_t;

  QueueA() = default;

  QueueA(const QueueA& src);

  QueueA(QueueA&& src) noexcept;
  
  ~QueueA();
  
  QueueA& operator=(const QueueA& src);

  QueueA& operator=(QueueA&& src);

  [[nodiscard]] bool is_empty() const noexcept;

  void pop() noexcept;

  void push(const T val);
  
  [[nodiscard]] T& top();

  [[nodiscard]] const T& top() const;

  void clear() noexcept;

};

#endif
