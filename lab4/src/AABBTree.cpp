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
  this->left = NULL;
  this->right = NULL;

  switch (num_leaves) {
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
  for (int i = 0; i < num_leaves; i++) {
    insert_box_into_box(objects[i]->box, this->box);
  }

  // Find the longest axis
  vector<double> axis_lengths;
  for (int a = 0; a < 3; a++) {
    axis_lengths.push_back( abs(this->box.max_corner(a) - this->box.min_corner(a)) );
  }
  int axis = distance(axis_lengths.begin(),max_element(axis_lengths.begin(), axis_lengths.end()));

  // Split objects along the axis
  double mid = this->box.center()[axis];

  vector< shared_ptr<Object> > leftside;
  vector< shared_ptr<Object> > rightside;

  for (int i = 0; i < num_leaves; i++) {
    if (objects[i]->box.center()[axis] < mid) {
      leftside.push_back(objects[i]);
    } else {
      rightside.push_back(objects[i]);
    }
  }

  // If nothing was done previously, we need to split the list by 2 to avoid infinite recursion
  if (leftside.size() == 0 || rightside.size() == 0) {
    leftside.clear();
    rightside.clear();

    // Lambda function to sort the list by locations of centers
    vector< shared_ptr<Object> > sortedObjects(objects);
    auto fct = [&axis](const shared_ptr<Object> &a, const shared_ptr<Object> &b) {
      return a->box.center()[axis] < b->box.center()[axis];
    };
    sort(sortedObjects.begin(), sortedObjects.end(), fct);

    // Put half the sorted list on the left and the other on the right
    for (int i = 0; i < num_leaves; i++) {
      if (i < num_leaves / 2) {
        leftside.push_back(sortedObjects[i]);
      }
      else {
        rightside.push_back(sortedObjects[i]);
      }
    }
  }

  this->left = make_shared<AABBTree>(leftside, a_depth + 1);
  this->right = make_shared<AABBTree>(rightside, a_depth + 1);
}
