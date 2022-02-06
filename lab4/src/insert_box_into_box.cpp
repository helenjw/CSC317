#include "insert_box_into_box.h"
using namespace std;

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  for (int axis = 0; axis < 3; axis++) {
    // Min corner: take the smallest
    B.min_corner(axis) = min(B.min_corner(axis), A.min_corner(axis));

    // Max corner: take the largest
    B.max_corner(axis) = max(B.max_corner(axis), A.max_corner(axis));
  }

  return;
}

