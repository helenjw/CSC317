// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  // Reference: https://tutorial.math.lamar.edu/classes/calciii/TangentNormalVectors.aspx
  T = normalize( cross(vec3(1, 0, 0), N) );
  B = normalize( cross(N, T) );
}
