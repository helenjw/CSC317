#include "insert_triangle_into_box.h"
using namespace Eigen;
using namespace std;

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  for (int axis = 0; axis < 3; axis++) {
    // Compare a, b, c, and B and take smallest for min
    B.min_corner(axis) = min({B.min_corner(axis), a[axis], b[axis], c[axis]});

    // Compare a, b, c, and B and take largest for max
    B.max_corner(axis) = max({B.max_corner(axis), a[axis], b[axis], c[axis]});
  }
}


