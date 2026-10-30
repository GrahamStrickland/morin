#include <array>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numbers>

#include "../include/euler.h"

int main(int argc, char *argv[]) {
  const double g = 9.8;          // gravitational constant (m/s^2)
  const double l = 1.0;          // length of pendulum (m)
  const double theta_target = 0; // target angle
  const double err = 0.001;      // acceptable absolute error

  double eps = 0.1; // small time interval
  double t1 = 0.0;  // first approximation
  double t2 = 0.0;  // second approximation
  std::array<std::function<double(std::array<double, 1>, std::array<double, 1>,
                                  double)>,
             1>
      d2thetas = {[g, l](std::array<double, 1> _theta1s,
                         std::array<double, 1> thetas,
                         double _t) { return -g * std::sin(thetas[0]) / l; }};
  std::array<double, 1> thetas = {std::numbers::pi / 2.0};
  auto cond = [theta_target](std::array<double, 1> thetas) {
    return thetas[0] <= theta_target;
  };

  do {
    t1 = t2;
    auto res = euler_2nd_approx(d2thetas, cond, thetas, eps);
    t2 = res.second;
    eps *= 0.1;
  } while (abs(t2 - t1) > err);

  std::cout << "Time taken for pendulum to reach vertical at " << theta_target
            << " radians: " << t2 << "s, epsilon = " << eps << "s\n";

  return EXIT_SUCCESS;
}
