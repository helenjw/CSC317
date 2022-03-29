#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>
using namespace Eigen;
#define w 1e10

void fast_mass_springs_step_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::MatrixXd & M,
  const Eigen::MatrixXd & A,
  const Eigen::MatrixXd & C,
  const Eigen::LLT<Eigen::MatrixXd> & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  MatrixXd l;
  MatrixXd d = MatrixXd::Zero(E.rows(), 3); // matrix to store all dij
  MatrixXd y = ( (M * (2 * Ucur - Uprev)) / (delta_t * delta_t) ) + fext; // needed for global step

  Unext = Ucur;

  for(int iter = 0;iter < 50;iter++)
  {
    // Local step: Given current values of p, determine dij for each spring
    for (int i = 0; i < E.rows(); i++) {
      d.row(i) = r[i] * (Unext.row( E(i,0) ) - Unext.row( E(i,1) )).normalized();
    }

    // Global step: given dij, find positions p that minimize quadratic energy
    // b = kAᵀd + y + wCᵀC * p_rest (for pinned points)
    l = k * A.transpose() * d + y + w * C.transpose() * C * V;
    Unext = prefactorization.solve(l);
  }

  return;
}
