#include "sphere.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace Eigen;

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  // Reference: https://en.wikipedia.org/wiki/Spherical_coordinate_system#Cartesian_coordinates
  double THETA_INCREMENT = M_PI / num_faces_u;  // inclination level increment - [0, pi]
  double PHI_INCREMENT = (2 * M_PI) / num_faces_v;  // azimuthal angle increment - [0, 2pi]

  // Projection - split png equally lengthwise and widthwise
  double U_INCREMENT = 1.0 / (num_faces_v + 1); // horizontal
  double V_INCREMENT = 1.0 / (num_faces_u + 1); // vertical
  
  V.resize((num_faces_u + 1) * (num_faces_v + 1), 3);
  NV.resize((num_faces_u + 1) * (num_faces_v + 1), 3);
  UV.resize((num_faces_u + 1) * (num_faces_v + 1), 2);

  // Store all vertex info - V, UV, NV
  for (int row = 0; row < num_faces_u + 1; row++) { // + 1 to get the lower and upper vertices
    for (int col = 0; col < num_faces_v + 1; col++) { // + 1 to get the left and right vertices
      double theta = row * THETA_INCREMENT;
      double phi = col * PHI_INCREMENT;
      
      // Transform each vertex into cartesian
      double x = cos(phi) * sin(theta);
      double y = sin(phi) * sin(theta);
      double z = cos(theta);

      // Store into matrix
      int vertex = row * (num_faces_v + 1) + col; 
      V.row(vertex) = Vector3d(y, z, x); // stores duplicates at col = 0, col = end to simplify face code
      NV.row(vertex) = Vector3d(y, z, x); // vector from origin to (x, y, z) is also the normal

      // Calculate (u,v) mapping
      UV.row(vertex) = Vector2d(U_INCREMENT * col, V_INCREMENT * (num_faces_u + 1 - row));
    }
  }

  F.resize(num_faces_u * num_faces_v, 4);
  NF.resize(num_faces_u * num_faces_v, 4);
  UF.resize(num_faces_u * num_faces_v, 4);

  // Store all face info - F, UF, NF
  for (int row = 0; row < num_faces_u; row++) {
    for (int col = 0; col < num_faces_v; col++) {

      // Store in CCW direction (bottom-left vertext first)
      int v1 = row * (num_faces_v + 1) + col;
      int v2 = row * (num_faces_v + 1) + col + 1;
      int v3 = (row + 1) * (num_faces_v + 1) + col + 1;
      int v4 = (row + 1) * (num_faces_v + 1) + col;

      int face = row * num_faces_v + col;
      F.row(face) = Vector4i(v1, v2, v3, v4);
      NF.row(face) = Vector4i(v1, v2, v3, v4);
      UF.row(face) = Vector4i(v1, v2, v3, v4);
    }
  }

  return;
}

