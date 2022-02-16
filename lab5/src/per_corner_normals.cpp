#include "per_corner_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <math.h>
using namespace Eigen;
using namespace std;

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = MatrixXd::Zero(F.rows()*3,3);

  // f = VF[i][j] means f is the jth face that shares vertex i
  vector< vector<int> > VF; 
  vertex_triangle_adjacency(F, V.rows(), VF);

  // Threshold for nf · ng
  double EPSILON = cos((M_PI * corner_threshold) / 180);

  // Calculate for each face & corner
  for (int face = 0; face < F.rows(); face++) {
    RowVector3d nf = triangle_area_normal( V.row(F(face,0)), V.row(F(face,1)), V.row(F(face,2)) );

    // Iterate through each corner of the face - there's only 3
    for (int corner = 0; corner < 3; corner++) {
      vector<int> neighbors = VF[F(face,corner)];
      RowVector3d n(0, 0, 0);

      // Go through neighbor faces of this corner
      for (int i = 0; i < neighbors.size(); i++) {
        int n_face = neighbors[i];
        RowVector3d ng = triangle_area_normal( V.row(F(n_face,0)), V.row(F(n_face,1)), V.row(F(n_face,2)) );

        if ( ng.normalized().dot(nf.normalized()) > EPSILON ) {
          n += ng;
        }
      }

      N.row(face * 3 + corner) = n.normalized();
    }
  }

  return;
}

