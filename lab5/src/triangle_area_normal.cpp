#include "triangle_area_normal.h"
#include <Eigen/Geometry>
using namespace Eigen;

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  RowVector3d l1 = b - a;
  RowVector3d l2 = c - a;
  return 0.5 * l1.cross(l2);
}
