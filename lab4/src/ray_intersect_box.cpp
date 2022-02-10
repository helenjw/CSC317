#include "ray_intersect_box.h"
#include <vector>
using namespace std;

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  vector<double> all_tmin;
  vector<double> all_tmax;

  for (int axis = 0; axis < 3; axis++) {
    // bounds of the box on axis
    double min = box.min_corner(axis);
    double max = box.max_corner(axis);

    // Direction of the ray
    double e = ray.origin(axis);
    double a = 1 / ray.direction(axis);

    // Ch. 12.3: use a = 1/d to avoid numerical issues
    double tmin = (a >= 0) ? a * (min - e) : a * (max - e);
    double tmax = (a >= 0) ? a * (max - e) : a * (min - e);
    
    all_tmin.push_back(tmin);
    all_tmax.push_back(tmax);
  }

  double tmin = *max_element(all_tmin.begin(), all_tmin.end());
  double tmax = *min_element(all_tmax.begin(), all_tmax.end());
  
  // no intersection
  if (tmax < tmin) return false;

  // out of bounds
  if (tmax < min_t || tmin > max_t) return false;
  
  return true;
}
