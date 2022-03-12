#include "euler_angles_to_transform.h"
using namespace Eigen;

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  // Reference: http://eecs.qmul.ac.uk/~gslabaugh/publications/euler.pdf

  // Turn angles into rad
  float x = xzx[0] * M_PI / 180.0;
  float y = xzx[1] * M_PI / 180.0;
  float z = xzx[2] * M_PI / 180.0;

  Affine3d Rx, Ry, Rz;

  // Rotation by x radians about x-axis
  Rx.matrix() << 
    1, 0, 0, 0,
    0, cos(x), -sin(x), 0,
    0, sin(x), cos(x), 0,
    0, 0, 0, 1;
  
  // Rotation by y radians about y-axis
  Ry.matrix() << 
    cos(y), 0, sin(y), 0,
    0, 1, 0, 0,
    -sin(y), 0, cos(y), 0,
    0, 0, 0, 1;
  
  // Rotation by z radians about z-axis
  Rz.matrix() << 
    cos(z), -sin(z), 0, 0,
    sin(z), cos(z), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1;
  
  return Rz * Ry * Rx;
}
