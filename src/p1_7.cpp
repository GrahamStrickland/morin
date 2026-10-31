#include <array>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numbers>

#include "../include/euler.h"

int main(int argc, char *argv[]) {
  const double g = 9.8;        // Earth's gravitational constant (m/s^2)
  const double r_target = 2.0; // target radius (m)
  const double err = 0.0001;   // acceptable relative error

  double eps = 0.1; // small time interval
  double t1 = 0.0;  // first approximation to t
  double t2 = 0.0;  // second approximation to t
  std::array<std::function<double(std::array<double, 2>, std::array<double, 2>,
                                  double)>,
             2>
      d2xs = {
          [g](std::array<double, 2> x1s, std::array<double, 2> xs, double _t) {
            return (xs[0] * x1s[1] * x1s[1] - g * (1 - std::cos(xs[1]))) / 2;
          }, // dr^2 / dt^2
          [g](std::array<double, 2> x1s, std::array<double, 2> xs, double _t) {
            return (-2.0 * x1s[0] * x1s[1] - g * std::sin(xs[1])) / xs[0];
          }, // dtheta^2 / dt^2
      };
  std::array<double, 2> xs = {
      1.0, std::numbers::pi /
               18.0}; // initial radius r (m) and angle theta (radians)
  std::array<double, 2> x1s = {
      0.0, 0.0}; // initial velocities -- r (m/s) and dtheta / dt (radians/s)
  auto cond = [r_target](std::array<double, 2> _x1s, std::array<double, 2> xs,
                         double _t) { return xs[0] < r_target; };

  do {
    t1 = t2;
    auto res = euler_2d_ivp(d2xs, x1s, xs, cond, eps);
    t2 = res.second;
    eps *= 0.1;
  } while (abs(t2 - t1) / abs(t2) > err);

  std::cout << "Time taken to reach a length of " << r_target << "m: " << t2
            << "s, delta t = " << eps << "s\n";

  return EXIT_SUCCESS;
}
