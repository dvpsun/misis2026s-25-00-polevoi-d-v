// 2026 by Polevoi Dmitry under Unlicense

#include <bitsetd/bitsetd.hpp>

//#include <doctest/doctest.h>

#include <array>
#include <chrono>
#include <utility>

template<typename T, typename D = std::chrono::nanoseconds>
inline double duration(const T& t_end, const T& t_beg)
{
  return static_cast<double>(std::chrono::duration_cast<D>(t_end - t_beg).count());
}

int main() {
  const auto bits_val = static_cast<uint64_t>(0b1010'0101'1111'0000);

  double t_copy = 0.0;
  double t_move = 0.0;
  int32_t bit_count = 175;
  BitsetD s(bits_val, bit_count);

  int32_t n_repeats = 1;
  const int32_t n_shots = 11;
  
  std::array<double, n_shots> t_shots{0.0};

  for (int i_shot = 0; i_shot < n_shots; i_shot += 1) {
    for (int i = 0; i < n_repeats; i += 1) {
      const auto beg_copy{ std::chrono::steady_clock::now() };
      auto r = s;
      const auto end_copy{ std::chrono::steady_clock::now() };
      t_copy += duration(end_copy, beg_copy);
      const auto beg_move{ std::chrono::steady_clock::now() };
      BitsetD c(std::move(s));
      const auto end_move{ std::chrono::steady_clock::now() };
      t_move += duration(end_move, beg_move);
      //
    }
  }

}