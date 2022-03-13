#include "copy_skeleton_at.h"
Skeleton copy_skeleton_at(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{
  Skeleton copy = skeleton;
  for (int i = 0; i < skeleton.size(); i++) {
    copy[i].xzx.x() = A[3 * i];
    copy[i].xzx.y() = A[3 * i + 1];
    copy[i].xzx.z() = A[3 * i + 2];
  }
  return copy;
}
