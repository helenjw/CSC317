#include "transformed_tips.h"
#include "forward_kinematics.h"
using namespace Eigen;
using namespace std;

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  VectorXd transformed_tips = VectorXd::Zero( 3*b.size() );

  // Compute transformations
  vector<Affine3d, aligned_allocator<Affine3d> > T;
  forward_kinematics(skeleton, T);

  for (int i = 0; i < b.size(); i++) {
    Bone bone = skeleton[ b[i] ]; // b[i]: index of skeleton endpoint
    Vector4d tip = T[ b[i] ] * bone.rest_T * Vector4d(skeleton[b[i]].length, 0, 0, 1);

    transformed_tips[3 * i] = tip[0];
    transformed_tips[3 * i + 1] = tip[1];
    transformed_tips[3 * i + 2] = tip[1];
  }

  return transformed_tips;
}

