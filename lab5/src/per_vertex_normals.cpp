#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"
using namespace Eigen;
using namespace std;

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  vector< vector<int> > VF; // f = VF[i][j] means f is the jth face that shares vertex i
  vertex_triangle_adjacency(F, V.rows(), VF);
  
  N = MatrixXd::Zero(V.rows(),3);
  
  // Corners of the triangles located at the same vertex should share the same normal
  for (int vertex = 0; vertex < V.rows(); vertex++) {
    
    // Iterate through all of the faces that share this vertex
    for (int i = 0; i < VF[vertex].size(); i++) {
      int triangle = VF[vertex][i];
      int a = F(triangle, 0);
      int b = F(triangle, 1);
      int c = F(triangle, 2);
      N.row(vertex) += triangle_area_normal(V.row(a), V.row(b), V.row(c));
    }

    // Now that we've checked every triangle, we can normalize the N value
    N.row(vertex) = N.row(vertex).normalized();
  }

  return;
}

