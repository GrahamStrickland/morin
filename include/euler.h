// Generic Euler's method implementations for numerical solutions of
// differential equations.
#ifndef EULER_H
#define EULER_H

#include <array>
#include <utility>

/*
 * @brief Euler's method for solution of second order IVPs with templated
 * dimension `D` and value type `T`.
 * @param `d2xs` Array of functions f(dx/dt, x, t) for d^2x / dt^2 in each
 * dimension, passed `x1s`, `xs`, and `t` as arguments.
 * @param `x1s` Array of initial velocities dx / dt in each dimension.
 * @param `xs` Array  of initial positions x in each dimension.
 * @param `cond` Stopping condition, passed `x1s`, `xs`, and `t` as arguments.
 * @param `eps` Small time interval to be used in approximation.
 * @return `std::pair` containing an array of approximations to x in the
 * first position and the final time in the second.
 */
template <std::size_t D, typename F, typename P, typename T>
std::pair<std::array<T, D>, T>
euler_2d_ivp(std::array<F, D> d2xs, std::array<T, D> x1s, std::array<T, D> xs,
             P cond, T eps) {
  std::array<T, D> x2s{}; // array of approximations to dx^2 / dt^2
  T t = 0.0;

  while (cond(x1s, xs, t)) {
    for (std::size_t i = 0; i < D; i++) {
      x2s[i] = d2xs[i](x1s, xs, t);
      xs[i] = xs[i] + eps * x1s[i];
      x1s[i] = x1s[i] + eps * x2s[i];
    }
    t += eps;
  }

  return {xs, t};
}

#endif // EULER_H
