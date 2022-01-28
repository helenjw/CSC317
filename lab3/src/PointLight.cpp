#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  d = (this->p - q).normalized();
  max_t = (this->p - q).norm();
  return;
}
