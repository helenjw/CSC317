#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  for (int axis = 0; axis < 3; axis++) {
    // if A & B intersect, then A's largest corner cannot be smaller than B's smallest corner
    if (B.min_corner(axis) > A.max_corner(axis)) return false;

    // also, if A & B intersect, then A's smallest corner cannot be larger than B's largest corner
    if (B.max_corner(axis) < A.min_corner(axis)) return false;
  }

  return true;
}
