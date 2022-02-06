#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <limits>
using namespace std;

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  // Construct the leaf nodes if we are <= 2 objects
  int n = objects.size();
  this->left = NULL;
  this->right = NULL;

  if (n == 2) {
    this->left = objects[0];
    insert_box_into_box(objects[0]->box, this->box);

    this->right = objects[1];
    insert_box_into_box(objects[1]->box, this->box);
    return;
  }
  else if (n == 1)
  {
    this->left = objects[0];
    insert_box_into_box(objects[0]->box, this->box);
    return;
  }

  // Find the longest axis
  int axis;
  double longest_len = -1;

  for (int a = 0; a < 3; a++) {
    double length = abs(this->box.max_corner(a) - this->box.min_corner(a));

    if (length > longest_len){
      longest_len = length;
      axis = a;
    }
  }

  double mid = this->box.center()[axis];

  // Split objects along the axis
  vector< shared_ptr<Object> > leftside;
  vector< shared_ptr<Object> > rightside;

  for (int i = 0; i < objects.size(); i++) {
    // Left box
    if (objects[i]->box.center()[axis] < mid) {
      leftside.push_back(objects[i]);
    } 

    // Right box
    else {
      rightside.push_back(objects[i]);
    }
  }

  if (leftside.empty() || rightside.empty()) throw;

  this->left = make_shared<AABBTree>(leftside, a_depth + 1);
  this->right = make_shared<AABBTree>(rightside, a_depth + 1);
}
