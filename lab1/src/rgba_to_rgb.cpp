#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      rgb[0 + 3 * (col + row * width)] = rgba[0 + 4 * (col + row * width)]; // r
      rgb[1 + 3 * (col + row * width)] = rgba[1 + 4 * (col + row * width)]; // g
      rgb[2 + 3 * (col + row * width)] = rgba[2 + 4 * (col + row * width)]; // b
    }
  }
}
