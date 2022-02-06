#include <Eigen/Core>
using namespace Eigen;

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  Vector3d reflected = in - 2 * in.dot(n) * n; // Ch. 4.8: r = in - 2(in · n)n
  return reflected.normalized();
}

