#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>
using namespace Eigen;
#define w 1e10

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  // Populate r - list of edge lengths
  r.resize(E.rows());
  for (int i = 0; i < E.rows(); i++) {
    auto V0 = V.row( E(i, 0) );
    auto V1 = V.row( E(i, 1) );
    r(i) = (V0 - V1).norm();
  }

  // Populate M - mass matrix
  M = MatrixXd::Zero(V.rows(), V.rows());
  for (int i = 0; i < V.rows(); i++) {
    M(i, i) = m[i];
  }

  // Construct A - signed incidence matrix
  signed_incidence_matrix_dense(V.rows(), E, A);

  // Populate C - selection matrix for pinned vertices
  C = MatrixXd::Zero(b.rows(), V.rows());

  // Q = (kAᵀA) + (M / ΔT²) + Qc
  MatrixXd Q = k * A.transpose() * A + M / (delta_t * delta_t) + w * C.transpose() * C;

  // Pin vertices - Reference: https://lihd1003.github.io/notebook/csc418/mass_spring_system.html
  MatrixXd Qc = w * C.transpose() * C; // Qc = wCᵀC

  Q += Qc;
  prefactorization.compute(Q);
  return prefactorization.info() != NumericalIssue;
}
