#include "point_AABBTree_squared_distance.h"
#include <queue> 
using namespace std;
typedef pair< double, shared_ptr<Object> > Node; // used to store (distance, AABB node)

bool point_AABBTree_squared_distance(
  const Eigen::RowVector3d & query,
  const std::shared_ptr<AABBTree> & root,
  const double min_sqrd,
  const double max_sqrd,
  double & sqrd,
  std::shared_ptr<Object> & descendant)
{
  double min_dist = numeric_limits<double>::infinity();

  // Queue has the minimum distance on top - initialized with root values
  priority_queue< Node, vector<Node>, greater<Node> > Q;
  Q.push( make_pair(point_box_squared_distance(query, root->box), root) );
  
  while (!Q.empty()) {
    Node curr = Q.top();
    Q.pop();

    double curr_dist = curr.first;
    shared_ptr<AABBTree> aabb = dynamic_pointer_cast<AABBTree>(curr.second);
    
    // Check if the subtree distance is smaller than what we currently have
    if (curr_dist < min_dist) {
      min_dist = curr_dist;
      
      // Leaf node not yet reached
      if (aabb) {
        // Check left
        if (aabb->left) {
          double l_d = point_box_squared_distance(query, aabb->left->box);
          if (l_d <= max_sqrd) Q.push( make_pair(l_d, aabb->left) );
        }

        // Check right
        if (aabb->right) {
          double r_d = point_box_squared_distance(query, aabb->right->box);
          if (r_d <= max_sqrd) Q.push( make_pair(r_d, aabb->right) );
        }
      }

      // reached leaf node
      else {
        if (min_sqrd <= curr_dist && curr_dist <= max_sqrd) {
          sqrd = min_dist;
          descendant = curr.second; // cannot pass "aabb" since descendant is of type <Object>
        }

        return false;
      }
    }
  }

  return false;
}
