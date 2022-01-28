#include "blinn_phong_shading.h"
#include "first_hit.h"
#include <iostream>
#include <cmath>
#define EPSILON 1e-6
using namespace Eigen;
using namespace std;

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  // RGB value for the specific pixel in question
  Vector3d rgb = Vector3d(0, 0, 0);

  // relevant paramenters for blinn-phong
  Vector3d ka = objects[hit_id]->material->ka; // ambient
  Vector3d kd = objects[hit_id]->material->kd; // diffuse
  Vector3d ks = objects[hit_id]->material->ks; // specular
  double pe = objects[hit_id]->material->phong_exponent;

  // Create a Ray object from POI towards the direction of the light
  Ray toLight;
  toLight.origin = ray.origin + t * ray.direction + n * EPSILON;
  double t_toLight;
  
  for (int i = 0; i < lights.size(); i++) {
    // set the direction of the toLight vector in Ray object
    lights[i]->direction(toLight.origin, toLight.direction, t_toLight);

    int temp_hit_id;
    double temp_t;
    Vector3d temp_n;

    // If we don't hit anything, we have reached a light source (not in shadow)
    if ( !first_hit(toLight, EPSILON, objects, temp_hit_id, temp_t, temp_n) ) {
      Vector3d I = lights[i]->I;
      Vector3d h = (ray.direction + toLight.direction) / (ray.direction + toLight.direction).norm();

      Vector3d ambiant = (ka.array() * Vector3d(0.1, 0.1, 0.1).array()).matrix();
      Vector3d diffuse = max(0.0, n.dot(toLight.direction)) * (kd.array() * I.array()).matrix();
      Vector3d specular = pow( max( 0.0, n.dot(h) ), pe )  * (ks.array() * I.array()).matrix();

      rgb += ambiant;
    }
  }
  
  return rgb;
}
