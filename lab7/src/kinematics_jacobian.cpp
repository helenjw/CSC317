#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>
using namespace Eigen;
#define h 10e-7

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  // Reference: Finite Differencing - https://github.com/alecjacobson/computer-graphics-kinematics
  J = MatrixXd::Zero( b.size() * 3, skeleton.size() * 3 );
  
  VectorXd tip = transformed_tips(skeleton, b);
  
  // Go through each bone and move bone angle-by angle
  for (int i = 0; i < skeleton.size(); i++) {
    for (int angle = 0; angle < 3; angle++) {
      Skeleton new_skeleton = skeleton;
      new_skeleton[i].xzx[angle] += h;
      VectorXd new_tip = transformed_tips(new_skeleton, b);

      // Populate the Jacobian
      // J[i][j] = [ xi(a + h * ∂j) - xi(a) ] / h where xi(a + h * ∂j) is the new tip position
      for (int j = 0; j < 3 * b.size(); j++) {
        J(j, 3 * i + angle) = ( (new_tip - tip) / h )[j];
      }

    }
  }
}

