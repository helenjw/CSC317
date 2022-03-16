#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>
using namespace Eigen;
using namespace std;

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  // function handle that computes the least-squares objective value given a list of Euler angles
  f = [&](const VectorXd & A)->double
  {
    Skeleton new_skeleton = copy_skeleton_at(skeleton, A); // copy skeleton with euler angle list A
    return ( transformed_tips(new_skeleton, b) - xb0 ).squaredNorm(); // see diff between new position and goal
  };

  // function handle that computes the least-squares objective gradient given a list of Euler angles 
  grad_f = [&](const VectorXd & A)->VectorXd
  {
    Skeleton new_skeleton = copy_skeleton_at(skeleton, A); 
    VectorXd new_tips = transformed_tips(new_skeleton, b);

    // Reference: Projected gradient descent - https://github.com/alecjacobson/computer-graphics-kinematics
    MatrixXd J;
    kinematics_jacobian(new_skeleton, b, J);

    VectorXd dE_dx = VectorXd::Zero( b.size() * 3 );
    for (int i = 0; i < dE_dx.rows(); i++) {
      dE_dx[i] = 2 * (new_tips[i] - xb0[i]); // derivative of squared dist
    }

    return J.transpose() * dE_dx;
  };

  // function handle that projects a given set of Euler angles onto the input skeleton's joint angles
  proj_z = [&](VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());

    // Reference: Projected gradient descent - https://github.com/alecjacobson/computer-graphics-kinematics
    for (int i = 0; i < skeleton.size(); i++) {
      A[3 * i + 0] = max( skeleton[i].xzx_min[0], min( skeleton[i].xzx_max[0], A[3*i + 0] ) );
      A[3 * i + 1] = max( skeleton[i].xzx_min[1], min( skeleton[i].xzx_max[1], A[3*i + 1] ) );;
      A[3 * i + 2] = max( skeleton[i].xzx_min[2], min( skeleton[i].xzx_max[2], A[3*i + 2] ) );;
    }
  };
}

