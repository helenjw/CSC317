#include "demosaic.h"
#include <iostream>
using namespace std;

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  
  for (int row = 1; row < height - 1; row++) {
    for (int col = 1; col < width - 1; col++) {
      int r = 0;
      int g = 0;
      int b = 0;

      // on a green bayer pixel
      if ((row + col) % 2 == 0) {
        g = bayer[col + width * row];
        r = (bayer[col + width * (row - 1)] + bayer[col + width * (row + 1)]) / 2;
        b = (bayer[(col + 1) + width * row] + bayer[(col - 1) + width * row]) / 2;
      }

      // on a blue bayer pixel
      else if (row % 2 == 0) {
        b = bayer[col + width * row];
        g = (bayer[col + width * (row - 1)] + bayer[col + width * (row + 1)] + bayer[(col + 1) + width * row] + bayer[(col - 1) + width * row]) / 4;
        r = (bayer[(col - 1) + width * (row - 1)] + bayer[(col + 1) + width * (row + 1)] + bayer[(col + 1) + width * (row - 1)] + bayer[(col - 1) + width * (row + 1)]) / 4;
      }

      // on a red pixel 
      else if (row % 2 == 1)
      {
        r = bayer[col + width * row];
        g = (bayer[col + width * (row - 1)] + bayer[col + width * (row + 1)] + bayer[(col + 1) + width * row] + bayer[(col - 1) + width * row]) / 4;
        b = (bayer[(col - 1) + width * (row - 1)] + bayer[(col + 1) + width * (row + 1)] + bayer[(col + 1) + width * (row - 1)] + bayer[(col - 1) + width * (row + 1)]) / 4;
      }
      
      rgb[3 * (col + width * row) + 0] = r;
      rgb[3 * (col + width * row) + 1] = g;
      rgb[3 * (col + width * row) + 2] = b;
    }
  }
}
