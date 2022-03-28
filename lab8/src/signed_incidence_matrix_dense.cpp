#include "signed_incidence_matrix_dense.h"
using namespace Eigen;

void signed_incidence_matrix_dense(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::MatrixXd & A)
{
  A = MatrixXd::Zero(E.rows(), n);
  for (int i = 0; i < E.rows(); i++) {
    A(i, E(i, 0)) = 1;
    A(i, E(i, 1)) = -1;
  }
}
