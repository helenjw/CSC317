#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <limits>
#include <iostream>
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

  switch (n) {
    case 0:
      return;

    case 1:
      this->left = objects[0];
      insert_box_into_box(objects[0]->box, this->box);
      return;
    
    case 2:
      this->left = objects[0];
      insert_box_into_box(objects[0]->box, this->box);

      this->right = objects[1];
      insert_box_into_box(objects[1]->box, this->box);
      return;
    
    default:
      break;
  }

  // Insert all the objects into current box
  for (int i = 0; i < n; i++) {
    insert_box_into_box(objects[i]->box, this->box);
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

  // Split objects along the axis
  double mid = this->box.center()[axis];

  // Lambda function to sort the list by items smaller than midpoint and larger
  vector< shared_ptr<Object> > sortedObjects(objects);
  auto fct = [&axis](const shared_ptr<Object> &a, const shared_ptr<Object> &b) {
    return a->box.center()[axis] < b->box.center()[axis];
  };
  sort(sortedObjects.begin(), sortedObjects.end(), fct);

  // Put half the sorted list on the left and the other on the right
  // I do this because if I partition objects on the l & r based on midpoint, one list can be empty and the function can infinitely recurse
  vector< shared_ptr<Object> > leftside;
  vector< shared_ptr<Object> > rightside;
  for (int i = 0; i < n; i++) {
    if (i < n / 2) {
      leftside.push_back(objects[i]);
    }
    else {
      rightside.push_back(objects[i]);
    }
  }

  this->left = make_shared<AABBTree>(leftside, a_depth + 1);
  this->right = make_shared<AABBTree>(rightside, a_depth + 1);
}
