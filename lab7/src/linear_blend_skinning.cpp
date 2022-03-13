#include "linear_blend_skinning.h"
using namespace Eigen;

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  U.resize(V.rows(), V.cols());

  // Iterate through every vertex
  for (int i = 0; i < V.rows(); i++) {
    Vector4d v_affine = Vector4d( V(i,0), V(i,1), V(i,2), 1);
    Vector4d pos = Vector4d::Zero();

    // Iterate through every bone
    for (int j = 0; j < skeleton.size(); j++) {
      Bone bone = skeleton[j];
      if (bone.weight_index != -1) {
        pos += W(i, bone.weight_index) * ( T[j] * v_affine );
      }
    }

    U(i,0) = pos[0];
    U(i,1) = pos[1];
    U(i,2) = pos[2];
  }
}

