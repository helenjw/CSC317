#include "per_face_normals.h"
#include "triangle_area_normal.h"
using namespace Eigen;

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = MatrixXd::Zero(F.rows(),3);

  for (int triangle = 0; triangle < F.rows(); triangle++) {
    int a = F(triangle, 0);
    int b = F(triangle, 1);
    int c = F(triangle, 2);

    N.row(triangle) = triangle_area_normal(V.row(a), V.row(b), V.row(c));
  }

  return;
}

