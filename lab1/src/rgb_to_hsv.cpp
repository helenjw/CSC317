#include "rgb_to_hsv.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  double r_prime = r / 255.0;
  double g_prime = g / 255.0;
  double b_prime = b / 255.0;

  double cmax = max({r_prime, g_prime, b_prime});
  double cmin = min({r_prime, g_prime, b_prime});
  double diff = cmax - cmin;

  // Compute H
  if (diff == 0) {
    h = 0;
  }
  else if (cmax == r_prime)
  {
    h = 60.0 * (0.0 + ((g_prime - b_prime) / diff));
  }
  else if (cmax == g_prime)
  {
    h = 60.0 * (2.0 + ((b_prime - r_prime) / diff));
  }
  else if (cmax == b_prime)
  {
    h = 60.0 * (4.0 + ((r_prime - g_prime) / diff));
  }

  // Compute S
  s = (cmax != 0) ? diff / cmax : 0.0;

  // Compute V
  v = cmax; 
}

