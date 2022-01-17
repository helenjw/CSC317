#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      
      for (int channel = 0; channel < num_channels; channel++) {
        rotated[num_channels * ((width - col - 1) * height + row) + channel] = input[num_channels * (row * width + col) + channel];
      }
    }
  }

  return;
}
