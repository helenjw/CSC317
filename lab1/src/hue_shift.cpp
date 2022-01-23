#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>

#include <iostream>
using namespace std;

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {

      int index = 3 * (col + row * width);
      double h = 0.0;
      double s = 0.0; 
      double v = 0.0;
      double r = rgb[index + 0];
      double g = rgb[index + 1];
      double b = rgb[index + 2];
      
      // cout << r << " " << g << " " << b << endl;
      rgb_to_hsv(r, g, b, h, s, v);
      // cout << h << " " << s << " " << v << endl;

      // shift the hue, then make sure new h is between 0 and 360 degrees
      // h -= shift;
      // if (h > 360.0) {
      //   h = fmod(h, 360.0);
      // }
      // else if (h < 0.0)
      // {
      //   h = 360.0 - fmod(abs(h), 360.0);
      // }

      if (r < 0 || g < 0 || b < 0) {
        cout << h<<endl;
      }

      // cout << h << " " << s << " " << v << endl;
      hsv_to_rgb(h, s, v, r, g, b);
      // cout << r << " " << g << " " << b << endl<<endl;

      shifted[index + 0] = r;
      shifted[index + 1] = g;
      shifted[index + 2] = b;
    }
  }

  return;
}
