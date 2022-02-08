#include "nearest_neighbor_brute_force.h"
#include <limits>
using namespace std;

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  double smallest_dist = numeric_limits<double>::infinity();
  int smallest_I = -1;

  for (int i = 0; i < points.rows(); i++) {
    double temp_dist = (points.row(i) - query).squaredNorm();

    if (temp_dist < smallest_dist) {
      smallest_dist = temp_dist;
      smallest_I = i;
    }
  }

  I = smallest_I;
  sqrD = smallest_dist;
  return;
}
