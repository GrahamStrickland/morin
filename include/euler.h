// Generic Euler's method for use in numerical solutions
#ifndef EULER_H
#define EULER_H

#include <array>
#include <utility>

template <std::size_t N, typename F, typename P, typename T>
std::pair<std::array<T, N>, T> euler_2nd_approx(std::array<F, N> d2xs, P cond,
                                                std::array<T, N> xs, T delta) {
  std::array<T, N> x1s{}; // array of approximations to dx / dt
  std::array<T, N> x2s{}; // array of approximations to dx^2 / dt^2
  T t = 0.0;

  while (!cond(xs)) {
    for (std::size_t i = 0; i < N; i++) {
      x2s[i] = d2xs[i](x1s, xs, t);
      xs[i] = xs[i] + delta * x1s[i];
      x1s[i] = x1s[i] + delta * x2s[i];
    }
    t += delta;
  }

  return {xs, t};
}

#endif // EULER_H
