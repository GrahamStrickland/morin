#include <array>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>

#include "euler.h"
#include "ex1_18.h"
#include "utils.h"

std::pair<double, double> distance_travelled(auto d2xs, auto x1s, auto xs,
                                             auto cond, auto err);
void print_distance_travelled(auto t_target, auto d2xs, auto x1s, auto xs,
                              auto cond, auto err);

void ex1_18() {
  const double A = 1.0; // s^-1
  const double err = 0.001;

  double t_target = 1.0; // target time (s)
  std::array<std::function<double(std::array<double, 1>, std::array<double, 1>,
                                  double)>,
             1>
      d2xs = {[A](std::array<double, 1> x1s,
                  [[maybe_unused]] std::array<double, 1> _xs,
                  [[maybe_unused]] double _t) { return -A * x1s[0]; }};
  std::array<double, 1> x1s = {2.0}; // initial speed dx / dt (m/s)
  std::array<double, 1> xs = {0.0};  // initial position x (m)
  auto cond = [&t_target]([[maybe_unused]] std::array<double, 1> _x1s,
                          [[maybe_unused]] std::array<double, 1> _xs,
                          double t) { return t < t_target; };

  print_heading("Exercise 1.18");

  std::cout << "d^2x/dt^2 = -" << A << "dx/dt:" << '\n';
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 10.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 100.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  std::cout << "d^2x/dt^2 = -" << A << "(dx/dt)^2:" << '\n';
  d2xs = {[A](std::array<double, 1> x1s,
              [[maybe_unused]] std::array<double, 1> _xs,
              [[maybe_unused]] double _t) { return -A * x1s[0] * x1s[0]; }};

  t_target = 1.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 10.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 100.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 1'000.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 10'000.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 100'000.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);

  t_target = 1'000'000.0;
  print_distance_travelled(t_target, d2xs, x1s, xs, cond, err);
}

std::pair<double, double> distance_travelled(auto d2xs, auto x1s, auto xs,
                                             auto cond, auto err) {
  double t1 = 0.0;  // first approximation to t
  double t2 = 0.0;  // second approximation to t
  double eps = 0.1; // small time interval
  double x;         // distance travelled (m)

  do {
    t1 = t2;
    auto res = euler_2d_ivp(d2xs, x1s, xs, cond, eps);
    x = res.first[0];
    t2 = res.second;
    eps *= 0.1;
  } while (abs(t2 - t1) / abs(t2) > err);

  return {x, eps};
}

void print_distance_travelled(auto t_target, auto d2xs, auto x1s, auto xs,
                              auto cond, auto err) {
  auto [x, eps] = distance_travelled(d2xs, x1s, xs, cond, err);

  std::cout << "Distance travelled by mass in " << t_target << "s: " << x
            << "m, epsilon = " << eps << "s\n";
}
