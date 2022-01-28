#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#define EPSILON 1e-6
#define MAX_NUM_CALLS 5
using namespace Eigen;

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  // if max number of "bounces" reached, stop
  if (num_recursive_calls > MAX_NUM_CALLS) return false;

  // check there is a ray-object intersection
  int hit_id;
  double t;
  Vector3d n;
  bool hit = first_hit(ray, min_t, objects, hit_id, t, n);

  if (hit) {
    // Add color of the current object our ray hits to the pixel
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

    // Recursively call on reflected ray - if we hit anything, we add that color on with a coef
    Ray reflectedRay;
    reflectedRay.origin = ray.origin + t * ray.direction;
    reflectedRay.direction = reflect(ray.origin + t * ray.direction, n).normalized();
    Vector3d reflected_rgb;

    if ( raycolor(reflectedRay, EPSILON, objects, lights, num_recursive_calls + 1, reflected_rgb) ) {
      Vector3d km = objects[hit_id]->material->km; // mirror coefficient
      rgb += (reflected_rgb.array() * km.array()).matrix();
    }
  }

  return hit;
}
