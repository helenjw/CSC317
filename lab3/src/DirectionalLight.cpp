#include "DirectionalLight.h"
#include <limits>
using namespace std;

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  d = -(this->d).normalized();
  max_t = numeric_limits<double>::infinity();
  return;
}

