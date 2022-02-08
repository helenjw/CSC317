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
  sqrd = numeric_limits<double>::infinity();

  // Queue has the minimum distance on top - initialized with root values
  priority_queue< Node, vector<Node>, greater<Node> > Q;
  Q.push( make_pair(point_box_squared_distance(query, root->box), root) );
  
  while (!Q.empty()) {
    Node curr = Q.top();
    Q.pop();

    double curr_dist = curr.first;
    shared_ptr<AABBTree> aabb = dynamic_pointer_cast<AABBTree>(curr.second);
    
    // Check if the subtree distance is smaller than what we currently have
    if (curr_dist < sqrd) {

      // Leaf node not yet reached
      if (aabb) {
        if (aabb->left)
          Q.push( make_pair(point_box_squared_distance(query, aabb->left->box), aabb->left) );
        
        if (aabb->right)
          Q.push( make_pair(point_box_squared_distance(query, aabb->right->box), aabb->right) );
      }

      // reached leaf node
      else {
        sqrd = curr_dist;
        descendant = curr.second; // cannot pass "aabb" since descendant is of type <Object>
      }
    }
  }

  return (min_sqrd <= sqrd && sqrd <= max_sqrd);
}
