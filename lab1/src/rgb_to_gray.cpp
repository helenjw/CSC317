#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int r = rgb[0 + 3 * (col + row * width)];
      int g = rgb[1 + 3 * (col + row * width)];
      int b = rgb[2 + 3 * (col + row * width)];
      gray[col + row * width] = 0.2126 * r + 0.7152 * g + 0.0722 * b;
    }
  }

  return;
}

