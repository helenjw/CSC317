#include "hsv_to_rgb.h"
#include <cmath>
#include <iostream>
using namespace std;

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  r = g = b = 0;
  double c = v * s;
  double h_prime = h / 60.0;
  double x = c * (1.0 - abs(fmod(h_prime, 2.0) - 1.0)); // X = C * (1 - \H' % 2 - 1\)

  if (0 <= h_prime && h_prime < 1) {
	  r = c;
	  g = x;
	  b = 0;
  }
  else if (1 <= h_prime && h_prime < 2) {
	  r = x;
	  g = c;
	  b = 0;
  }
  else if (2 <= h_prime && h_prime < 3) {
	  r = 0;
	  g = c;
	  b = x;
  }
  else if (3 <= h_prime && h_prime < 4) {
	  r = 0;
	  g = x;
	  b = c;
  }
  else if (4 <= h_prime && h_prime < 5) {
	  r = x;
	  g = 0;
	  b = c;
  }
  else if (5 <= h_prime && h_prime < 6) {
	  r = c;
	  g = 0;
	  b = x;
  }

  double m = v - c;
  r = 255.0 * (r + m);
  g = 255.0 * (g + m);
  b = 255.0 * (b + m);
  return;
}

