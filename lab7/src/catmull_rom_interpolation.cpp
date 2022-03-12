#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

Vector3d catmull_rom_interpolation(
  const vector<pair<double, Vector3d> > & keyframes,
  double t)
{
  // Reference: https://qroph.github.io/2018/07/30/smooth-paths-using-catmull-rom-splines.html
  if (keyframes.size() == 0) return Vector3d(0, 0, 0);

  if (keyframes.size() == 1) return keyframes[0].second; // only 1 keyframe means no animation

  // Mod query time so that we can plan animation continuously
  t = fmod(t, keyframes.back().first);

  // To draw a curve that runs through all 4 points
  vector<Vector3d> point = vector<Vector3d>(4, Vector3d(0, 0, 0)); // pn-1, pn, pn+1, pn+2
  vector<double> time = vector<double>(4, 0.0); // tn-1, tn, tn+1, tn+2

  Vector3d m0, m1, theta0, theta1;

  // Find the two keyframes query time is in between
  for (int i = 0; i < keyframes.size() - 1; i++) {

    // we queried the exact time of a keyframe
    if (t == keyframes[i].first) {
      return keyframes[i].second; 
    }

    // Time queried is between these two frames
    if (keyframes[i].first < t && t < keyframes[i + 1].first) {
      // t(n - 1) and p(n - 1)
      time[0] = (i == 0) ? keyframes[i].first : keyframes[i - 1].first;
      point[0] = (i == 0) ? keyframes[i].second : keyframes[i - 1].second;

      // t(n), p(n)
      time[1] = keyframes[i].first;
      point[1] = keyframes[i].second;

      // t(n + 1), p(n + 1)
      time[2] = keyframes[i + 1].first;
      point[2] = keyframes[i + 1].second;

      // t(n + 2), p(n + 2)
      time[3] = (i == keyframes.size() - 2) ? keyframes[i + 1].first : keyframes[i + 2].first;
      point[3] = (i == keyframes.size() - 2) ? keyframes[i + 1].second : keyframes[i + 2].second;

      m0 = (point[2] - point[0]) / (time[2] - time[0]);
      m1 = (point[3] - point[1]) / (time[3] - time[1]);

      theta0 = point[1];
      theta1 = point[2];

      t = (t - time[1]) / (time[2] - time[1]);

      break; // no need to look anymore
    }
  }

  // 3d interpolated point = (2t³ - 3t² + 1) * theta0 + (t³ - 2t² + t) * m0 + (-2t³ + 3t²) * theta1 + (t³ - t²) * m1
  double t2 = pow(t, 2), t3 = pow(t,3);
  return (2 * t3 - 3 * t2 + 1) * theta0 + (t3 - 2 * t2 + t) * m0 + (-2 * t3 + 3 * t2) * theta1 + (t3 - t2) * m1;
}