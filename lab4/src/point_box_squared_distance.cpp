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

    // point is left of box
    if (query[axis] < box.min_corner(axis)) {
      ans += (box.min_corner(axis) - query[axis]) * (box.min_corner(axis) - query[axis]);
    }

    // point is right of box
    else {
      ans += (query[axis] - box.max_corner(axis)) * (query[axis] - box.max_corner(axis));
    }
  }

  return ans;
}

