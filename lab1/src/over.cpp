#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  
  // Overlay A on top of B
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int i = 4 * (col + row * width);

      double alpha_a = A[i + 3] / 255.0;
      double alpha_b = B[i + 3] / 255.0;
      double alpha_c = alpha_a + alpha_b * (1 - alpha_a);
      C[i + 3] = 255.0 * alpha_c;

      for (int color = 0; color < 3; color++) {
        double c_a = A[i + color];
        double c_b = B[i + color];
        C[i + color] = ((alpha_a * c_a) + (c_b * alpha_b * (1 - alpha_a))) / alpha_c;
      }
    }
  }
  
  return;
}

