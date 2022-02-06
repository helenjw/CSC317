#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  int left = 0;
  int right = width - 1;

  while (left <= right) {
    for (int row = 0; row < height; row++) {
      
      for (int channel = 0; channel < num_channels; channel++) {
        int l_val = input[channel + num_channels * (width * row + left)];
        int r_val = input[channel + num_channels * (width * row + right)];

        reflected[channel + num_channels * (width * row + left)] = r_val;
        reflected[channel + num_channels * (width * row + right)] = l_val;
      }

    }

    left++;
    right--;
  }

  return;
}

