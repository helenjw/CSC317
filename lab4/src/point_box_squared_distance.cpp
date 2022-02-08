#include "point_box_squared_distance.h"
using namespace Eigen;
using namespace std;

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  double ans = 0;

  for (int axis = 0; axis < 3; axis++) {
    // If we are already inside the box, the distance is 0
    if (box.min_corner(axis) <= query[axis] && query[axis] <= box.max_corner(axis)){
      continue;
    }

    double dist_to_min = abs(query[axis] - box.min_corner(axis));
    double dist_to_max = abs(query[axis] - box.max_corner(axis));

    // Add the square of which ever distance is smaller
    ans += (dist_to_max > dist_to_min) ? dist_to_max * dist_to_max : dist_to_min * dist_to_min;
  }

  return ans;
}
