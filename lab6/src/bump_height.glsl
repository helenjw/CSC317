// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  // Reference: 11.5.3 - Turbulence
  // Reference: http://web.cse.ohio-state.edu/~wang.3602/courses/cse5542-2013-spring/14-noise.pdf
  float w = is_moon ? 2 : 3;
  float k1 = is_moon ? 4 : 5; // twist factor
  float k2 = is_moon ? 2 : 4; // density of twists
  float noise = sqrt( abs (1 + sin( s.x + k1 * improved_perlin_noise(k2 * s) ) / w) );

  return smooth_heaviside(noise, is_moon ? 1 : 0.5);
}
