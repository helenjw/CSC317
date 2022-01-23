#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {

      int index = 3 * (col + row * width);
      double h = 0.0;
      double s = 0.0; 
      double v = 0.0;
      double r = rgb[index + 0];
      double g = rgb[index + 1];
      double b = rgb[index + 2];
      
      rgb_to_hsv(r, g, b, h, s, v);

      // shift the hue, then make sure new h is between 0 and 360 degrees
      s *= 1 - factor;

      hsv_to_rgb(h, s, v, r, g, b);

      desaturated[index + 0] = r;
      desaturated[index + 1] = g;
      desaturated[index + 2] = b;
    }
  }

  return;
}
