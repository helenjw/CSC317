#include "AABBTree.h"
using namespace std;

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  // Check if the ray hits the box before considering descendants
  if ( !ray_intersect_box(ray, this->box, min_t, max_t) ) return false;

  // Check the left and right children and see if we have a hit
  shared_ptr<Object> leftChildren = this->left, rightChildren = this->right;
  double t_right, t_left;

  bool left_hit = (this->left) ? this->left->ray_intersect(ray, min_t, max_t, t_left, leftChildren) : false;
  bool right_hit = (this->right) ? this->right->ray_intersect(ray, min_t, max_t, t_right, rightChildren) : false;

  // No hit
  if ( !left_hit && !right_hit ) return false;

  // 1+ hit(s)
  if (left_hit && right_hit) {
    t = min(t_left, t_right);
    descendant = (t_left < t_right) ? leftChildren : rightChildren;

  } else if (left_hit) {
    t = t_left;
    descendant = leftChildren;

  } else if (right_hit) {
    t = t_right;
    descendant = rightChildren;
  } 
  
  return true;
}

