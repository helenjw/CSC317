#include "first_hit.h"
using namespace std;

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  double smallest_t = numeric_limits<double>::max();
  hit_id = -1;
  Eigen::Vector3d normal;

  // Iterate through each object and see if ray intersects with anything. Update if it does
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i] -> intersect(ray, min_t, t, n)) {
      if (smallest_t > t) {
        smallest_t = t;
        hit_id = i;
        normal = n;
      }
    }
  }

  if (hit_id < 0) {
    return false;
  }

  t = smallest_t;
  n = normal;
  return true;
}

