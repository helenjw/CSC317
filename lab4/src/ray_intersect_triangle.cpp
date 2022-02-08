#include "ray_intersect_triangle.h"
using namespace Eigen;

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  // Ch. 4.4.2 - intersection with triangle
  // Corners
  Vector3d A_T = A.transpose();
  Vector3d B_T = B.transpose();
  Vector3d C_T = C.transpose();

  // Ray
  Vector3d D = ray.direction;
  Vector3d E = ray.origin;

  // System of equations
  Vector3d A_minus_B = A_T - B_T;
  Vector3d A_minus_C = A_T - C_T;
  Vector3d A_minus_E = A_T - E;

  double a = A_minus_B[0];
  double b = A_minus_B[1];
  double c = A_minus_B[2];
  double d = A_minus_C[0];
  double e = A_minus_C[1];
  double f = A_minus_C[2];
  double g = D[0];
  double h = D[1];
  double i = D[2];
  double j = A_minus_E[0];
  double k = A_minus_E[1];
  double l = A_minus_E[2];
  double m = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

  t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / m;

  if (t < min_t) {
    return false;
  }

  double gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / m;
  if (gamma < 0 || gamma > 1) {
    return false;
  }

  double beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / m;
  if (beta < 0 || beta > (1 - gamma)) {
    return false;
  }

  return true;
}

