#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include <list>
using namespace std;
typedef pair< shared_ptr<Object>, shared_ptr<Object> > Node;

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & leaf_pairs)
{
  list<Node> Q;
  Q.push_back(make_pair(rootA, rootB));

  while( !Q.empty() ) {
    Node curr_node = Q.front();
    Q.pop_front();

    shared_ptr<AABBTree> A = dynamic_pointer_cast<AABBTree>(curr_node.first);
    shared_ptr<AABBTree> B = dynamic_pointer_cast<AABBTree>(curr_node.second);

    // A and B both leaves
    if (!A && !B) {
      leaf_pairs.push_back( make_pair(curr_node.first, curr_node.second) ); // use curr.first and second because leaf_pairs takes <Object>
    }

    // A is a leaf and B isn't
    else if (!A && B) {
      if ( B->left && box_box_intersect(curr_node.first->box, B->left->box) ) {
        Q.push_back( make_pair(curr_node.first, B->left) );
      }

      if ( B->right && box_box_intersect(curr_node.first->box, B->right->box) ) {
        Q.push_back( make_pair(curr_node.first, B->right) );
      }
    }

    // A isn't and B is
    else if (A && !B) {
      if ( A->left && box_box_intersect(A->left->box, curr_node.second->box) ) {
        Q.push_back( make_pair(A->left, curr_node.second) );
      }

      if ( A->right && box_box_intersect(A->right->box,  curr_node.second->box) ) {
        Q.push_back( make_pair(A->right, curr_node.second) );
      }
    }

    // We are not at any leaf nodes
    else {
      if ( A->left && B->left && box_box_intersect(A->left->box, B->left->box) ) {
        Q.push_back( make_pair(A->left, B->left) );
      }

      if ( A->left && B->right && box_box_intersect(A->left->box, B->right->box) ) {
        Q.push_back( make_pair(A->left, B->right) );
      }

      if ( A->right && B->left && box_box_intersect(A->right->box, B->left->box) ) {
        Q.push_back( make_pair(A->right, B->left) );
      }

      if ( A->right && B->right && box_box_intersect(A->right->box, B->right->box) ) {
        Q.push_back( make_pair(A->right, B->right) );
      }
    }
  }

  return;
}

