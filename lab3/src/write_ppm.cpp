#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
using namespace std;

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert((num_channels == 3 || num_channels == 1 ) && ".ppm only supports RGB or grayscale images");

  ofstream file(filename);
  file << ((num_channels == 3) ? "P3\t" : "P2\t") << endl;
  file << width << "\t" << height << endl;
  file << "255" << endl;

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {

      for (int channel = 0; channel < num_channels; channel++) {
        file << (int)data[channel + num_channels * (col + row * width)] << " ";
      }

      file << "\t";
    }

    file << endl;
  }

  file.close();
  return true;
}