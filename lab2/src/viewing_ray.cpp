#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  // Perspective viewing ray - chapter 4.3.2
  // u = l + (r - l)(j + 0.5)/nx
  int u = -camera.width / 2 + camera.width * (j + 0.5) / width;

  // v = b + (t - b)(i + 0.5)/ny
  int v = -camera.height / 2 + camera.height * (i + 0.5) / height;

  ray.origin = camera.e;
  ray.direction = Eigen::Vector3d(u * camera.u + v * camera.v - camera.d * camera.w); // ray.direction = uU + vV - dW
  return;
}

