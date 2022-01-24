#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int index = col + width * row;

      // Even row - green/red
      if (row % 2 == 0) {
        bayer[index] = (col % 2 == 0) ? rgb[3 * index + 2] : rgb[3 * index + 0];
      }

      // Odd row - blue/green
      else {
        bayer[index] = (col % 2 == 0) ? rgb[3 * index + 2] : rgb[3 * index + 1];
      }

    }
  }
}
