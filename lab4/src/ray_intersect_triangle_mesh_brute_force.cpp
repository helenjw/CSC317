#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits>
using namespace Eigen;
using namespace std;

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  double smallest_t = numeric_limits<double>::infinity();
  int smallest_f = -1;
  RowVector3d A, B, C;

  // Iterate through all the triangles
  for (int i = 0; i < F.rows(); i++) {
    A = V.row(F(i, 0));
    B = V.row(F(i, 1));
    C = V.row(F(i, 2));

    // Check intersection
    double temp_hit_t;
    if ( ray_intersect_triangle(ray, A, B, C, min_t, max_t, temp_hit_t) ) {

      // Keep the smallest t and associated hit_id
      if (smallest_t > temp_hit_t) {
        smallest_t = temp_hit_t;
        smallest_f = i;
      }
    }
  }

  if (smallest_f > -1) {
    hit_t = smallest_t;
    hit_f = smallest_f;
    return true;
  }

  return false;
}

