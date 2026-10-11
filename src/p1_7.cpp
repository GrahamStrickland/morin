#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>

double euler_2nd_approx(double g, double eps, double rtarget, double theta,
                        double r);

int main(int argc, char *argv[]) {
  const double g = 9.8;       // gravitational constant (m/s^2)
  const double rtarget = 2.0; // target radius (m)
  const double err = 0.0001;  // acceptable absolute error

  double theta = std::numbers::pi / 18.0; // initial angle (radians)
  double r = 1.0;                         // initial radius (m)
  double eps = 0.1;                       // small time interval
  double t1 = 0.0;                        // first approximation
  double t2 = 0.0;                        // second approximation

  do {
    t1 = t2;
    t2 = euler_2nd_approx(g, eps, rtarget, theta, r);
    eps *= 0.1;
  } while (abs(t2 - t1) > err);

  std::cout << "Time taken to reach a length of " << rtarget << "m: " << t2
            << "s, epsilon = " << eps << "s\n";

  return EXIT_SUCCESS;
}

double euler_2nd_approx(double g, double eps, double rtarget, double theta,
                        double r) {
  double theta1 = 0.0; // dtheta / dt
  double theta2;       // given equation for d^2theta / dt^2
  double r1 = 0.0;     // dr / dt
  double r2;           // given equation for d^2r / dt^2
  double t = 0.0;      // time (s)

  while (r < rtarget) {
    r2 = 0.5 * (r * theta1 * theta1 - g * (1 - std::cos(theta)));
    r = r + eps * r1;
    r1 = r1 + eps * r2;
    theta2 = -(2.0 * r1 * theta1) / r - (g * std::sin(theta)) / r;
    theta = theta + eps * theta1;
    theta1 = theta1 + eps * theta2;
    t += eps;
  }

  return t;
}
