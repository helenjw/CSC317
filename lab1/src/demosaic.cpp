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
  
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int r = 0;
      int g = 0;
      int b = 0;

      int rtotal = 0;
      int gtotal = 0;
      int btotal = 0;

        // bfs on neighbors
        for (int i = row - 1; i <= row + 1; i++) {
          for (int j = col - 1; j <= col + 1; j++) {

            if (0 <= i && i < height && 0 <= j && j < width) {
              int val = bayer[j + width * i];
              // green bayer pixel
              if ((i + j) % 2 == 0) {
                g += val;
                gtotal++;
              }
              else if (i % 2 == 0)
              {
                b += val;
                btotal++;
              }
              else {
                r += val;
                rtotal++;
              }
            }
          }
        }
      
      rgb[3 * (col + width * row) + 0] = rtotal == 0 ? 0 : (r / rtotal);
      rgb[3 * (col + width * row) + 1] = gtotal == 0 ? 0 : (g / gtotal);
      rgb[3 * (col + width * row) + 2] = btotal == 0 ? 0 : (b / btotal);
    }
  }

  return;
}

