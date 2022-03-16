#include "line_search.h"
#include <iostream>
using namespace Eigen;

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  double step = max_step;
  VectorXd z_prime = z - step * dz;
  proj_z(z_prime);

  while (f(z_prime) > f(z)) {
    step /= 2;
    z_prime = z - step * dz;
    proj_z(z_prime);
  }

  // at this point, f(z) > f(z'), and we have found our semi-optimal step
  return step;
}

