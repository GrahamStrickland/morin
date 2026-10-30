#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>

double euler_approx(double g, double eps, double l, double theta,
                    double thetatarget);

int main(int argc, char *argv[]) {
  const double g = 9.8;         // gravitational constant (m/s^2)
  const double l = 1.0;         // length of pendulum (m)
  const double thetatarget = 0; // target angle
  const double err = 0.001;     // acceptable absolute error

  double theta = std::numbers::pi / 2.0; // initial angle (radians)
  double eps = 0.1;                      // small time interval
  double t1 = 0.0;                       // first approximation
  double t2 = 0.0;                       // second approximation

  do {
    t1 = t2;
    t2 = euler_approx(g, eps, l, theta, thetatarget);
    eps *= 0.1;
  } while (abs(t2 - t1) > err);

  std::cout << "Time taken to reach angle " << thetatarget << ": " << t2
            << "s, epsilon = " << eps << "s\n";

  return EXIT_SUCCESS;
}

double euler_approx(double g, double eps, double l, double theta,
                    double thetatarget) {
  double theta1 = 0.0; // dtheta / dt
  double theta2;       // given equation for d^2theta / dt^2
  double t = 0.0;      // time (s)

  while (theta > thetatarget) {
    theta2 = -g * std::sin(theta) / l;
    theta = theta + eps * theta1;
    theta1 = theta1 + eps * theta2;
    t += eps;
  }

  return t;
}
