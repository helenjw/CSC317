#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  // Orthographic viewing ray - chapter 4.3.1
  // u = l + (r - l)(j + 0.5)/nx
  int u = -camera.width / 2 + camera.width * (j + 0.5) / width;

  // v = b + (t - b)(i + 0.5)/ny
  int v = -camera.height / 2 + camera.height * (i + 0.5) / height;

  ray.direction = -camera.w;
  ray.origin = camera.u * u + camera.v * v - camera.d * camera.w;
}

