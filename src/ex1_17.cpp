#include <array>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numbers>

#include "euler.h"
#include "ex1_17.h"
#include "utils.h"

void ex1_17() {
  const double g = 9.8;          // Earth's gravitational constant (m/s^2)
  const double l = 1.0;          // length of pendulum (m)
  const double theta_target = 0; // target angle (radians)
  const double err = 0.001;      // acceptable relative error

  double eps = 0.1; // small time interval
  double t1 = 0.0;  // first approximation to t
  double t2 = 0.0;  // second approximation to t
  std::array<std::function<double(std::array<double, 1>, std::array<double, 1>,
                                  double)>,
             1>
      d2thetas = {[g, l]([[maybe_unused]] std::array<double, 1> _theta1s,
                         std::array<double, 1> thetas,
                         [[maybe_unused]] double _t) {
        return -g * std::sin(thetas[0]) / l;
      }}; // d^2theta / dt^2
  std::array<double, 1> theta1s = {
      0.0}; // initial velocity dtheta / dt (radians/s)
  std::array<double, 1> thetas = {std::numbers::pi /
                                  2.0}; // initial angle theta (radians)
  auto cond = [theta_target]([[maybe_unused]] std::array<double, 1> _theta1s,
                             std::array<double, 1> thetas,
                             [[maybe_unused]] double _t) {
    return thetas[0] > theta_target;
  };

  print_heading("Exercise 1.17");

  do {
    t1 = t2;
    auto res = euler_2d_ivp(d2thetas, theta1s, thetas, cond, eps);
    t2 = res.second;
    eps *= 0.1;
  } while (abs(t2 - t1) / abs(t2) > err);

  std::cout << "Time taken for pendulum to reach vertical at " << theta_target
            << " radians: " << t2 << "s, epsilon = " << eps << "s\n";
}
