#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function
using namespace std;
using namespace Eigen;

void transform(int i, const Skeleton & skeleton, vector<Affine3d, aligned_allocator<Affine3d> > & T, vector<bool> & assigned);

void forward_kinematics(
  const Skeleton & skeleton,
  vector<Affine3d, aligned_allocator<Affine3d> > & T)
{
  // Transformations should be the same size as skeleton
  T.resize(skeleton.size(), Affine3d::Identity());
  vector<bool> assigned = vector<bool>(skeleton.size(), false); 

  // From each bone, recursively call to assign transformations
  for (int i = 0; i < skeleton.size(); i++) {
    transform(i, skeleton, T, assigned);
  }
}

void transform(int i, const Skeleton & skeleton, vector<Affine3d, aligned_allocator<Affine3d> > & T, vector<bool> & assigned) {
  Bone bone = skeleton[i];
  
  // Base case: at root
  if (bone.parent_index == -1) return;

  // Work is already done
  if (assigned[i]) return;

  // Figure out what transforms the parents go through
  transform(bone.parent_index, skeleton, T, assigned);

  T[i] = T[ bone.parent_index ] * bone.rest_T * euler_angles_to_transform(bone.xzx) * bone.rest_T.inverse();
  assigned[i] = true;
  return;
}

