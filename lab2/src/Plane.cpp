#include "Plane.h"
#include "Ray.h"
#include <iostream>
using namespace Eigen;
using namespace std;

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d n_plane, d, e, po;
  n_plane = this->normal;
  d = ray.direction;
  e = ray.origin;
  po = this->point;

  // t = ( -n · (e - po) ) / ( n · d ) - but first check division by 0
  double denom = n_plane.dot(d);
  t = denom != 0 ? -n_plane.dot(e - po) / denom : numeric_limits<double>::min();
  n = n_plane.normalized();

  return t >=  min_t ? true : false;
}
