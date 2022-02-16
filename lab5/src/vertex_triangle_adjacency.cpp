#include "vertex_triangle_adjacency.h"
using namespace std;

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  
  for (int face = 0; face < F.rows(); face++) {
    for (int corner = 0; corner < 3; corner++) {

      // f = VF[i][j] means f is the jth face that shares vertex i
      int vertex = F(face, corner);

      if ( find(VF[vertex].begin(), VF[vertex].end(), face) == VF[vertex].end() )
        VF[vertex].push_back(face);
    }
  }

  return;
}

