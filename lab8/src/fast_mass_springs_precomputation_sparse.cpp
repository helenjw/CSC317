#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>
using namespace std;
using namespace Eigen;
#define w 1e10

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  // Populate r - list of edge lengths
  r.resize(E.rows());
  for (int i = 0; i < E.rows(); i++) {
    auto V0 = V.row( E(i, 0) );
    auto V1 = V.row( E(i, 1) );
    r(i) = (V0 - V1).norm();
  }

  vector<Triplet<double> > ijv; // used to populate (row, col, val) triplets in SparseMatrix
  const int n = V.rows();

  // Populate M - mass matrix
  M.resize(n, n);
  for (int i = 0; i < V.rows(); i++) {
    ijv.emplace_back(i, i, m[i]);
  }
  M.setFromTriplets(ijv.begin(), ijv.end());
  ijv.clear();

  // Construct A - signed incidence matrix
  signed_incidence_matrix_sparse(n, E, A);

  // Populate C - selection matrix for pinned vertices
  C.resize(b.rows(), n);
  for (int i = 0; i < b.rows(); i++) {
    ijv.emplace_back(i, b(i), 1);
  }
  C.setFromTriplets(ijv.begin(), ijv.end());

  // Q = (kAᵀA) + (M / ΔT²) + Qc
  SparseMatrix<double> Q = k * A.transpose() * A + M / (delta_t * delta_t);

  // Pin vertices - Reference: https://lihd1003.github.io/notebook/csc418/mass_spring_system.html
  SparseMatrix<double> Qc = w * C.transpose() * C; // Qc = wCᵀC
  
  Q += Qc;
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
