// #include "projected_gradient_descent.h"
// #include "line_search.h"
// using namespace Eigen;
// #define MAX_STEP 1000

// void projected_gradient_descent(
//   const std::function<double(const Eigen::VectorXd &)> & f,
//   const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
//   const std::function<void(Eigen::VectorXd &)> & proj_z,
//   const int max_iters,
//   Eigen::VectorXd & z)
// {
//   VectorXd dz;

//   // only check for min <max_iters> amount of times
//   for (int i = 0; i < max_iters; i++) {
// 		dz = grad_f(z);

//     // Minimum already found
//     if (dz.isZero()) {
//       return;
//     }
		
//     // z = z - sigma * dz
// 		z -= line_search(f, proj_z, z, dz, MAX_STEP) * dz;
// 		proj_z(z);
//   } 
// }

#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  double max_step = 10000.0;
  for (int iters=0; iters<max_iters; ++iters) {
    Eigen::VectorXd dz = grad_f(z);
    if (f(z) <= 1e-5 || dz.isZero())
      return;
    // Not sure if max_step should be updated after
    // every iteration
    //max_step = line_search(f, proj_z, z, dz, max_step);
    //z = z - max_step * dz;
    z = z - line_search(f, proj_z, z, dz, max_step) * dz;
    proj_z(z);
  }
}
