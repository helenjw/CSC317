#include "Plane.h"
#include "Ray.h"
using namespace Eigen;

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d n_plane, d, e, po;
  n_plane = this->normal.normalized();
  d = ray.direction.normalized();
  e = ray.origin;
  po = this->point;

  // t = ( -n · (e - po) ) / ( n · d )
  t = n_plane.dot(d) != 0 ? ( -n_plane.dot(e - po) ) / ( n_plane.dot(d) ) : std::numeric_limits<double>::min();
  n = n_plane.normalized();

  if (t < min_t) {
    return false;
  }

  return true;
}

