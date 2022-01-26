#include "Sphere.h"
#include "Ray.h"
#include <cmath>
using namespace Eigen;

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Vector3d d = ray.direction;
  Vector3d e = ray.origin;
  Vector3d c = this->center;
  double r = this->radius;

  // Ch. 4.4.1: [(d · d)]t^2 + [2d·(e - c)]t + [(e - c) · (e - c) - r^2] = 0 -> At^2 + Bt + C = 0
  double A, B, C;
  A = d.dot(d);
  B = 2 * d.dot(e - c);
  C = (e - c).dot(e - c) - r * r;

  // Calculate discriminant: B^2 - 4AC
  int disc = B * B - 4 * A * C;

  // no intersection
  if (disc < 0) {
    return false;
  }

  // Ray grazes sphere
  else if (disc == 0) {
    t = - B / (2 * A);
  }

  // Ray enters AND leaves sphere - choose closest one
  else {
    double t1 = (-B - sqrt(disc)) / (2 * A);
    double t2 = (-B + sqrt(disc)) / (2 * A);
    
    // if both points behind the camera
    if (t1 < min_t && t2 < min_t) {
      return false;
    }

    // point at t1 behind camera, but t2 is visible
    else if (t1 < min_t)
    {
      t = t2;
    }

    // both t1 and t2 are visible - take min time since that would be closer
    else {
      t = std::min(t1, t2);
    }
  }

  // Normalize: n = (p - c).normalized(), p = point of intersection
  Eigen::Vector3d p = e + t * d;
  n = (p - c).normalized();

  return true;
}
