#include "cube.h"
using namespace Eigen;

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  // Reference: http://ilkinulas.github.io/development/unity/2016/05/06/uv-mapping.html#:~:text=UVs%20are%20simply%202D%20coordinates,of%20objects%20in%203D%20space
  
  // 8 vertices in a cube
  V.resize(8,3);
  V.row(0) = Vector3d(0, 0, 0);
  V.row(1) = Vector3d(0, 0, 1);
  V.row(2) = Vector3d(1, 0, 1);
  V.row(3) = Vector3d(1, 0, 0);
  V.row(4) = Vector3d(0, 1, 1);
  V.row(5) = Vector3d(0, 1, 0);
  V.row(6) = Vector3d(1, 1, 1);
  V.row(7) = Vector3d(1, 1, 0);
  
  // 6 faces on a cube
  F.resize(6,4);
  F.row(0) = Vector4i(0, 3, 2, 1); // Bottom
  F.row(1) = Vector4i(4, 5, 0, 1); // Left
  F.row(2) = Vector4i(5, 7, 3, 0); // Back
  F.row(3) = Vector4i(7, 6, 3, 2); // Right
  F.row(4) = Vector4i(6, 4, 1, 2); // Front
  F.row(5) = Vector4i(4, 6, 7, 5); // Top

  // Texture mapping for vertices (u, v)
  UV.resize(14,2);
  UV.row(0) = 0.25 * Vector2d(1, 0);
  UV.row(1) = 0.25 * Vector2d(2, 0);
  UV.row(2) = 0.25 * Vector2d(0, 1);
  UV.row(3) = 0.25 * Vector2d(1, 1);
  UV.row(4) = 0.25 * Vector2d(2, 1);
  UV.row(5) = 0.25 * Vector2d(3, 1);
  UV.row(6) = 0.25 * Vector2d(4, 1);
  UV.row(7) = 0.25 * Vector2d(0, 2);
  UV.row(8) = 0.25 * Vector2d(1, 2);
  UV.row(9) = 0.25 * Vector2d(2, 2);
  UV.row(10) = 0.25 * Vector2d(3, 2);
  UV.row(11) = 0.25 * Vector2d(4, 2);
  UV.row(12) = 0.25 * Vector2d(1, 3);
  UV.row(13) = 0.25 * Vector2d(2, 3);

  // Face indices into UV
  UF.resize(6,4);
  UF.row(0) = Vector4i(3, 4, 1, 0); // Bottom
  UF.row(1) = Vector4i(7, 8, 3, 2); // Left
  UF.row(2) = Vector4i(8, 9, 4, 3); // Back
  UF.row(3) = Vector4i(9, 10, 5, 4); // Right
  UF.row(4) = Vector4i(10, 11, 6, 5); // Front
  UF.row(5) = Vector4i(12, 13, 9, 8); // Top

  // Normal vectors
  NV.resize(6,3);
  NV.row(0) = Vector3d(0, -1, 0); // Bottom
  NV.row(1) = Vector3d(-1, 0, 0); // Left
  NV.row(2) = Vector3d(0, 0, -1); // Back
  NV.row(3) = Vector3d(1, 0, 0); // Right
  NV.row(4) = Vector3d(0, 0, 1); // Front
  NV.row(5) = Vector3d(0, 1, 0); // Top

  // Normal face indices
  NF.resize(6,4);
  NF.row(0) = Vector4i(0, 0, 0, 0);
  NF.row(1) = Vector4i(1, 1, 1, 1);
  NF.row(2) = Vector4i(2, 2, 2, 2);
  NF.row(3) = Vector4i(3, 3, 3, 3);
  NF.row(4) = Vector4i(4, 4, 4, 4);
  NF.row(5) = Vector4i(5, 5, 5, 5);

  return;
}


// #include "cube.h"

// void cube(
//   Eigen::MatrixXd & V,
//   Eigen::MatrixXi & F,
//   Eigen::MatrixXd & UV,
//   Eigen::MatrixXi & UF,
//   Eigen::MatrixXd & NV,
//   Eigen::MatrixXi & NF)
// {
//   ////////////////////////////////////////////////////////////////////////////
//   // Add your code here:
//   ////////////////////////////////////////////////////////////////////////////

//   ////Hint:
//    V.resize(8,3);

//    V.row(0) = Eigen::Vector3d(0, 0, 0);
//    V.row(1) = Eigen::Vector3d(1, 0, 0);
//    V.row(2) = Eigen::Vector3d(1, 1, 0);
//    V.row(3) = Eigen::Vector3d(0, 1, 0);
//    V.row(4) = Eigen::Vector3d(0, 0, 1);
//    V.row(5) = Eigen::Vector3d(1, 0, 1);
//    V.row(6) = Eigen::Vector3d(1, 1, 1);
//    V.row(7) = Eigen::Vector3d(0, 1, 1);


//    F.resize(6,4);
//    F.row(0) = Eigen::Vector4i(0, 4, 7, 3); // left red
//    F.row(1) = Eigen::Vector4i(4, 5, 6, 7); // top yellow
//    F.row(2) = Eigen::Vector4i(0, 1, 5, 4); // front green
//    F.row(3) = Eigen::Vector4i(0, 3, 2, 1); // bottom white
//    F.row(4) = Eigen::Vector4i(1, 2, 6, 5); // right blue
//    F.row(5) = Eigen::Vector4i(2, 3, 7, 6); // back orange

   
//    double num = 0.25;
//    UV.resize(14,2);
//    UV.row(0) = num * Eigen::Vector2d(1, 1);
//    UV.row(1) = num * Eigen::Vector2d(1, 0);
//    UV.row(2) = num * Eigen::Vector2d(2, 0);
//    UV.row(3) = num * Eigen::Vector2d(2, 1);
//    UV.row(4) = num * Eigen::Vector2d(3, 1);
//    UV.row(5) = num * Eigen::Vector2d(4, 1);
//    UV.row(6) = num * Eigen::Vector2d(4, 2);
//    UV.row(7) = num * Eigen::Vector2d(3, 2);
//    UV.row(8) = num * Eigen::Vector2d(2, 2);
//    UV.row(9) = num * Eigen::Vector2d(2, 3);
//    UV.row(10) = num * Eigen::Vector2d(1, 3);
//    UV.row(11) = num * Eigen::Vector2d(1, 2);
//    UV.row(12) = num * Eigen::Vector2d(0, 2);
//    UV.row(13) = num * Eigen::Vector2d(0, 1);


//    UF.resize(6,4);
//    UF.row(0) = Eigen::Vector4i(11, 10, 9, 8); // left red
//    UF.row(1) = Eigen::Vector4i(4, 7, 6, 5); // top yellow
//    UF.row(2) = Eigen::Vector4i(13, 12, 11, 0); // front green
//    UF.row(3) = Eigen::Vector4i(0, 11, 8, 3); // bottom white
//    UF.row(4) = Eigen::Vector4i(0, 3, 2, 1); // right blue
//    UF.row(5) = Eigen::Vector4i(3, 8, 7, 4); // back orange


//    NV.resize(6,3);
//    NV.row(0) = Eigen::Vector3d(0, -1, 0).normalized();
//    NV.row(1) = Eigen::Vector3d(0, 0, 1).normalized();
//    NV.row(2) = Eigen::Vector3d(1, 0, 0).normalized();
//    NV.row(3) = Eigen::Vector3d(0, 0, -1).normalized();
//    NV.row(4) = Eigen::Vector3d(0, 1, 0).normalized();
//    NV.row(5) = Eigen::Vector3d(-1, 0, 0).normalized();


//    NF.resize(6,4);
//    NF.row(0) = Eigen::Vector4i(0, 0, 0, 0); // red
//    NF.row(1) = Eigen::Vector4i(1, 1, 1, 1); // yellow
//    NF.row(2) = Eigen::Vector4i(2, 2, 2, 2); // green
//    NF.row(3) = Eigen::Vector4i(3, 3, 3, 3); // white
//    NF.row(4) = Eigen::Vector4i(4, 4, 4, 4); // blue
//    NF.row(5) = Eigen::Vector4i(5, 5, 5, 5); // orange

// }